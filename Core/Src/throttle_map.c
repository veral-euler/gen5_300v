/**
 * @file throttle_map.c
 *
 * RPM resolution matrix:
 * ┌───────────────┬──────────────────────────────────┐
 * │  Direction    │  Effective RPM Cap               │
 * ├───────────────┼──────────────────────────────────┤
 * │  NEUTRAL      │  0 (always)                      │
 * │  FORWARD ECO  │  rpm_cap_eco                     │
 * │  FORWARD THU  │  rpm_cap_thunder                 │
 * │  REVERSE      │  rpm_cap_reverse (ECO/THU ignore)│
 * └───────────────┴──────────────────────────────────┘
 */

#include "throttle_map.h"
#include <assert.h>

ThrottleMapConfig_t g_throttle_cfg;

/* ─── Private Helpers ───────────────────────────────────────────────────────  */

/**
 * @brief  Clamp a uint32 value between lo and hi.
 */
static inline uint32_t clamp_u32(uint32_t val, uint32_t lo, uint32_t hi)
{
    if (val < lo) return lo;
    if (val > hi) return hi;
    return val;
}

/**
 * @brief  Resolve the active RPM cap from both flags.
 *         This is the single decision point — direction takes priority.
 */
static inline uint32_t resolve_rpm_cap(const ThrottleMapConfig_t *cfg)
{
    switch (cfg->direction)
    {
        case DIRECTION_NEUTRAL:
            return RPM_MIN;

        case DIRECTION_REVERSE:
            return cfg->rpm_cap_reverse;   /* ECO/THUNDER irrelevant in REVERSE */

        case DIRECTION_FORWARD:
        default:
            return (cfg->drive_mode == DRIVE_MODE_ECO) ? cfg->rpm_cap_eco
                                                        : cfg->rpm_cap_thunder;
    }
}

/* ─── Public API ────────────────────────────────────────────────────────────  */

/**
 * @brief  Initialise config with safe defaults.
 * @param  cfg  Pointer to the config struct to initialise.
 */
void ThrottleMap_Init(ThrottleMapConfig_t *cfg)
{
    assert(cfg != NULL);

    cfg->v_min_mv        = THROTTLE_V_MIN_MV;
    cfg->v_max_mv        = THROTTLE_V_MAX_MV;
    cfg->rpm_cap_eco     = RPM_CAP_ECO_DEFAULT;
    cfg->rpm_cap_thunder = RPM_CAP_THUNDER_DEFAULT;
    cfg->rpm_cap_reverse = RPM_CAP_REVERSE_DEFAULT;
    cfg->drive_mode      = DRIVE_MODE_ECO;
    cfg->direction       = DIRECTION_NEUTRAL;       /* Safe power-on default   */
}

/**
 * @brief  Switch ECO ↔ THUNDER. Only affects FORWARD direction output.
 *         Calling this while in REVERSE has no immediate effect on RPM output
 *         but the new mode is latched and applies instantly if FORWARD is selected.
 */
void ThrottleMap_SetDriveMode(ThrottleMapConfig_t *cfg, DriveMode_t mode)
{
    assert(cfg != NULL);
    cfg->drive_mode = mode;
}

/**
 * @brief  Switch FORWARD / REVERSE / NEUTRAL.
 *         RPM cap resolves on the very next ThrottleMap_GetRPM() call.
 */
void ThrottleMap_SetDirection(ThrottleMapConfig_t *cfg, Direction_t direction)
{
    assert(cfg != NULL);
    cfg->direction = direction;
}

/**
 * @brief  Update ECO or THUNDER RPM cap at runtime (e.g. CAN command / OTA).
 */
void ThrottleMap_SetRpmCap(ThrottleMapConfig_t *cfg, DriveMode_t mode, uint32_t rpm_cap)
{
    assert(cfg != NULL);
    rpm_cap = clamp_u32(rpm_cap, RPM_MIN, RPM_ABS_MAX);

    if (mode == DRIVE_MODE_ECO) {
        cfg->rpm_cap_eco = rpm_cap;
    } else {
        cfg->rpm_cap_thunder = rpm_cap;
    }
}

/**
 * @brief  Update the REVERSE RPM cap at runtime.
 */
void ThrottleMap_SetReverseRpmCap(ThrottleMapConfig_t *cfg, uint32_t rpm_cap)
{
    assert(cfg != NULL);
    cfg->rpm_cap_reverse = clamp_u32(rpm_cap, RPM_MIN, RPM_ABS_MAX);
}

/**
 * @brief  Map throttle voltage (mV) → target RPM, honouring both flags.
 *
 * @param  cfg   Config struct (read-only).
 * @param  v_mv  ADC-derived throttle voltage in millivolts.
 * @return       Target RPM. Caller should treat this as an unsigned magnitude;
 *               direction of rotation is conveyed by cfg->direction separately.
 */
uint32_t ThrottleMap_GetRPM(const ThrottleMapConfig_t *cfg, uint32_t v_mv)
{
    assert(cfg != NULL);
    assert(cfg->v_max_mv > cfg->v_min_mv);

    /* ── 1. Resolve active cap from both flags in one place ──────────────── */
    uint32_t rpm_cap = resolve_rpm_cap(cfg);

    /* ── 2. NEUTRAL: ignore throttle entirely ────────────────────────────── */
    if (rpm_cap == RPM_MIN) {
        return RPM_MIN;
    }

    /* ── 3. Clamp voltage to hardware range ──────────────────────────────── */
    v_mv = clamp_u32(v_mv, cfg->v_min_mv, cfg->v_max_mv);

    if (v_mv <= cfg->v_min_mv) {
        return RPM_MIN;
    }

    /* ── 4. Linear interpolation (64-bit numerator, safe on H743) ────────── */
    uint64_t numerator   = (uint64_t)(v_mv - cfg->v_min_mv) * rpm_cap;
    uint32_t denominator = cfg->v_max_mv - cfg->v_min_mv;
    uint32_t rpm         = (uint32_t)(numerator / denominator);

    return clamp_u32(rpm, RPM_MIN, rpm_cap);
}

void App_Init(void)
{
    ThrottleMap_Init(&g_throttle_cfg);

    /* Optional: override caps at startup (e.g., from flash/EEPROM config) */
    ThrottleMap_SetRpmCap(&g_throttle_cfg, DRIVE_MODE_ECO,     ECO_MAX_SPEED);
    ThrottleMap_SetRpmCap(&g_throttle_cfg, DRIVE_MODE_THUNDER, SPORTS_MAX_SPEED);
    ThrottleMap_SetReverseRpmCap(&g_throttle_cfg, REV_MAX_SPEED);
    ThrottleMap_SetDirection(&g_throttle_cfg, NEUTRAL);

    /* Start in ECO */
    ThrottleMap_SetDriveMode(&g_throttle_cfg, ECO);
}
