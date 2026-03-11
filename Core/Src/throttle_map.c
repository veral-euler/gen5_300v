/**
 * @file throttle_map.c
 * @brief Throttle voltage to RPM mapping with ECO/THUNDER mode support
 * @target STM32H743ZIT6
 *
 * Mapping formula (linear):
 *
 *   rpm = (v_mv - v_min) / (v_max - v_min)  *  rpm_cap_active
 *
 * All intermediate math is done in uint64_t to avoid overflow on
 * the H743's 32-bit core without needing floating point.
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
 * @brief  Return the active RPM cap for the current mode.
 */
static inline uint32_t get_active_rpm_cap(const ThrottleMapConfig_t *cfg)
{
    return (cfg->mode == DRIVE_MODE_ECO) ? cfg->rpm_cap_eco
                                         : cfg->rpm_cap_thunder;
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
    cfg->mode            = DRIVE_MODE_ECO;          /* Safe default            */
}

/**
 * @brief  Dynamically switch between ECO and THUNDER.
 *         RPM cap takes effect on the very next ThrottleMap_GetRPM() call.
 *
 * @param  cfg   Pointer to config struct.
 * @param  mode  DRIVE_MODE_ECO or DRIVE_MODE_THUNDER.
 */
void ThrottleMap_SetMode(ThrottleMapConfig_t *cfg, DriveMode_t mode)
{
    assert(cfg != NULL);
    cfg->mode = mode;
}

/**
 * @brief  Update the RPM cap for a specific mode at runtime.
 *         Useful for OTA config updates or calibration routines.
 *
 * @param  cfg      Pointer to config struct.
 * @param  mode     Which mode's cap to update.
 * @param  rpm_cap  New RPM cap. Clamped to [0, RPM_ABS_MAX] internally.
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
 * @brief  Map a raw throttle voltage (mV) to a target RPM.
 *
 *         - Voltages below v_min  → 0 RPM   (dead-band / released throttle)
 *         - Voltages above v_max  → rpm_cap  (full throttle, clamped)
 *         - Linear interpolation in between
 *
 * @param  cfg   Pointer to config struct (read-only).
 * @param  v_mv  Raw ADC-derived throttle voltage in millivolts.
 * @return       Target RPM in range [0, active_rpm_cap].
 */
uint32_t ThrottleMap_GetRPM(const ThrottleMapConfig_t *cfg, uint32_t v_mv)
{
    assert(cfg != NULL);
    assert(cfg->v_max_mv > cfg->v_min_mv);  /* Guard against bad config        */

    /* ── 1. Hard clamp voltage to [v_min, v_max] ─────────────────────────── */
    v_mv = clamp_u32(v_mv, cfg->v_min_mv, cfg->v_max_mv);

    /* ── 2. Dead-band: below minimum → zero RPM ──────────────────────────── */
    if (v_mv <= cfg->v_min_mv) {
        return RPM_MIN;
    }

    /* ── 3. Resolve active RPM cap based on current mode ─────────────────── */
    uint32_t rpm_cap = get_active_rpm_cap(cfg);

    /* ── 4. Linear map using 64-bit to prevent overflow ──────────────────── *
     *                                                                         *
     *   rpm = (v_mv - v_min) * rpm_cap / (v_max - v_min)                    *
     *                                                                         *
     *   Max intermediate: (4000 - 900) * 6000 = 18,600,000 → fits uint32,   *
     *   but use uint64_t for safety if caps are ever raised above 6000.      *
     * ──────────────────────────────────────────────────────────────────────  */
    uint64_t numerator   = (uint64_t)(v_mv - cfg->v_min_mv) * rpm_cap;
    uint32_t denominator = cfg->v_max_mv - cfg->v_min_mv;
    uint32_t rpm         = (uint32_t)(numerator / denominator);

    /* ── 5. Final clamp (defensive) ──────────────────────────────────────── */
    return clamp_u32(rpm, RPM_MIN, rpm_cap);
}

void App_Init(void)
{
    ThrottleMap_Init(&g_throttle_cfg);

    /* Optional: override caps at startup (e.g., from flash/EEPROM config) */
    ThrottleMap_SetRpmCap(&g_throttle_cfg, DRIVE_MODE_ECO,     ECO_MAX_SPEED);
    ThrottleMap_SetRpmCap(&g_throttle_cfg, DRIVE_MODE_THUNDER, SPORTS_MAX_SPEED);

    /* Start in ECO */
    ThrottleMap_SetMode(&g_throttle_cfg, ECO);
}
