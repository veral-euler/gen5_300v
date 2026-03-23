/**
 * @file throttle_map.c
 *
 * RPM and Torque resolution matrix:
 * ┌───────────────┬──────────────────────────────────────────────────────────┐
 * │  Direction    │  Effective Cap                                           │
 * ├───────────────┼──────────────────────────────────────────────────────────┤
 * │  NEUTRAL      │  RPM = 0, Torque = 0.0f (always)                        │
 * │  FORWARD ECO  │  rpm_cap_eco    / min(torque_cap_eco_nm,    max_trq_nm) │
 * │  FORWARD SPT  │  rpm_cap_sports / min(torque_cap_sports_nm, max_trq_nm) │
 * │  REVERSE      │  rpm_cap_reverse/ min(torque_cap_reverse_nm,max_trq_nm) │
 * └───────────────┴──────────────────────────────────────────────────────────┘
 */

#include "throttle_map.h"
#include <assert.h>

ThrottleMapConfig_t g_throttle_cfg;

/* =========================================================================
 * PRIVATE HELPERS
 * ========================================================================= */

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
 * @brief  Clamp a float value between lo and hi.
 */
static inline float clamp_f(float val, float lo, float hi)
{
    if (val < lo) return lo;
    if (val > hi) return hi;
    return val;
}

/**
 * @brief  Resolve the active RPM cap from direction and drive mode.
 *         Single decision point — direction takes priority over drive mode.
 */
static inline uint32_t resolve_rpm_cap(const ThrottleMapConfig_t *cfg)
{
    switch (cfg->direction)
    {
        case NEUTRAL:
            return RPM_MIN;

        case REVERSE:
            return cfg->rpm_cap_reverse;      /* Drive mode irrelevant in REVERSE */

        case FORWARD:
        default:
            return (cfg->drive_mode == ECO) ? cfg->rpm_cap_eco
                                            : cfg->rpm_cap_sports;
    }
}

/**
 * @brief  Resolve the active torque cap (Nm) from direction and drive mode.
 *         Effective cap = min(mode_cap, max_torque_nm) — respects both the
 *         mode limit and the motor's torque-speed capability at current speed.
 *
 * @param  cfg            Config struct.
 * @param  max_torque_nm  Motor capability at current speed from torque-speed curve.
 */
static inline float resolve_torque_cap(const ThrottleMapConfig_t *cfg,
                                        float max_torque_nm)
{
    float mode_cap;

    switch (cfg->direction)
    {
        case NEUTRAL:
            return 0.0f;

        case REVERSE:
            mode_cap = cfg->torque_cap_reverse_nm;
            break;

        case FORWARD:
        default:
            mode_cap = (cfg->drive_mode == ECO) ? cfg->torque_cap_eco_nm
                                                 : cfg->torque_cap_sports_nm;
            break;
    }

    /* Motor capability at current speed takes precedence if lower */
    return (mode_cap < max_torque_nm) ? mode_cap : max_torque_nm;
}

/* =========================================================================
 * PUBLIC API — INITIALISATION
 * ========================================================================= */

/**
 * @brief  Initialise config with safe defaults.
 */
void ThrottleMap_Init(ThrottleMapConfig_t *cfg)
{
    assert(cfg != NULL);

    cfg->v_min_mv               = THROTTLE_V_MIN_MV;
    cfg->v_max_mv               = THROTTLE_V_MAX_MV;

    cfg->rpm_cap_eco            = RPM_CAP_ECO_DEFAULT;
    cfg->rpm_cap_sports         = RPM_CAP_SPORTS_DEFAULT;
    cfg->rpm_cap_reverse        = RPM_CAP_REVERSE_DEFAULT;

    cfg->torque_cap_eco_nm      = TORQUE_CAP_ECO_DEFAULT_NM;
    cfg->torque_cap_sports_nm   = TORQUE_CAP_SPORTS_DEFAULT_NM;
    cfg->torque_cap_reverse_nm  = TORQUE_CAP_REVERSE_DEFAULT_NM;

    cfg->drive_mode             = ECO;
    cfg->direction              = NEUTRAL;          /* Safe power-on default */
}

/* =========================================================================
 * PUBLIC API — SETTERS
 * ========================================================================= */

/**
 * @brief  Switch ECO ↔ SPORTS.
 *         Only affects FORWARD direction output. Mode is latched and applies
 *         instantly when FORWARD is next selected.
 */
void ThrottleMap_SetDriveMode(ThrottleMapConfig_t *cfg, power_mode_t mode)
{
    assert(cfg != NULL);
    cfg->drive_mode = mode;
}

/**
 * @brief  Switch FORWARD / REVERSE / NEUTRAL.
 *         RPM and torque caps resolve on the next GetRPM / GetTorque call.
 */
void ThrottleMap_SetDirection(ThrottleMapConfig_t *cfg, fnr_state_t direction)
{
    assert(cfg != NULL);
    cfg->direction = direction;
}

/**
 * @brief  Update ECO or SPORTS RPM cap at runtime (e.g. CAN command / OTA).
 */
void ThrottleMap_SetRpmCap(ThrottleMapConfig_t *cfg,
                            power_mode_t mode, uint32_t rpm_cap)
{
    assert(cfg != NULL);
    rpm_cap = clamp_u32(rpm_cap, RPM_MIN, RPM_ABS_MAX);

    if (mode == ECO)
        cfg->rpm_cap_eco = rpm_cap;
    else
        cfg->rpm_cap_sports = rpm_cap;
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
 * @brief  Update ECO or SPORTS torque cap at runtime (Nm).
 */
void ThrottleMap_SetTorqueCap(ThrottleMapConfig_t *cfg,
                               power_mode_t mode, float torque_cap_nm)
{
    assert(cfg != NULL);
    torque_cap_nm = clamp_f(torque_cap_nm, 0.0f, TORQUE_CAP_SPORTS_DEFAULT_NM);

    if (mode == ECO)
        cfg->torque_cap_eco_nm = torque_cap_nm;
    else
        cfg->torque_cap_sports_nm = torque_cap_nm;
}

/**
 * @brief  Update the REVERSE torque cap at runtime (Nm).
 */
void ThrottleMap_SetReverseTorqueCap(ThrottleMapConfig_t *cfg,
                                      float torque_cap_nm)
{
    assert(cfg != NULL);
    cfg->torque_cap_reverse_nm = clamp_f(torque_cap_nm, 0.0f,
                                          TORQUE_CAP_SPORTS_DEFAULT_NM);
}

/* =========================================================================
 * PUBLIC API — MAPPING
 * ========================================================================= */

/**
 * @brief  Map throttle voltage (mV) → target RPM, honouring direction and mode.
 */
uint32_t ThrottleMap_GetRPM(const ThrottleMapConfig_t *cfg, uint32_t v_mv)
{
    assert(cfg != NULL);
    assert(cfg->v_max_mv > cfg->v_min_mv);

    /* 1. Resolve active RPM cap */
    uint32_t rpm_cap = resolve_rpm_cap(cfg);

    /* 2. NEUTRAL — ignore throttle entirely */
    if (rpm_cap == RPM_MIN)
        return RPM_MIN;

    /* 3. Clamp voltage to hardware range */
    v_mv = clamp_u32(v_mv, cfg->v_min_mv, cfg->v_max_mv);

    if (v_mv <= cfg->v_min_mv)
        return RPM_MIN;

    /* 4. Linear interpolation (64-bit numerator, safe on H743) */
    uint64_t numerator   = (uint64_t)(v_mv - cfg->v_min_mv) * rpm_cap;
    uint32_t denominator = cfg->v_max_mv - cfg->v_min_mv;
    uint32_t rpm         = (uint32_t)(numerator / denominator);

    return clamp_u32(rpm, RPM_MIN, rpm_cap);
}

/**
 * @brief  Map throttle voltage (mV) → torque reference (Nm).
 *
 * @details Effective cap = min(mode_torque_cap, max_torque_nm).
 *          Linear interpolation: v_min_mv → 0 Nm, v_max_mv → effective_cap.
 *          NEUTRAL always returns 0.0f.
 *          Direction of rotation is conveyed by cfg->direction separately.
 */
float ThrottleMap_GetTorque(const ThrottleMapConfig_t *cfg, uint32_t v_mv,
                             float max_torque_nm)
{
    assert(cfg != NULL);
    assert(cfg->v_max_mv > cfg->v_min_mv);

    /* 1. Resolve effective torque cap — direction + mode + motor curve */
    float torque_cap = resolve_torque_cap(cfg, max_torque_nm);

    /* 2. NEUTRAL — always zero torque */
    if (cfg->direction == NEUTRAL || torque_cap <= 0.0f)
        return 0.0f;

    /* 3. Clamp voltage to hardware range */
    v_mv = clamp_u32(v_mv, cfg->v_min_mv, cfg->v_max_mv);

    if (v_mv <= cfg->v_min_mv)
        return 0.0f;

    /* 4. Linear interpolation: voltage → [0, torque_cap] */
    float numerator   = (float)(v_mv - cfg->v_min_mv) * torque_cap;
    float denominator = (float)(cfg->v_max_mv - cfg->v_min_mv);
    float torque_nm   = numerator / denominator;

    return clamp_f(torque_nm, 0.0f, torque_cap);
}

/* =========================================================================
 * APP INIT
 * ========================================================================= */

void App_Init(void)
{
    ThrottleMap_Init(&g_throttle_cfg);

    /* Override caps at startup (e.g., from flash / EEPROM config) */
    ThrottleMap_SetRpmCap(&g_throttle_cfg, ECO,    ECO_MAX_SPEED);
    ThrottleMap_SetRpmCap(&g_throttle_cfg, SPORTS,  SPORTS_MAX_SPEED);
    ThrottleMap_SetReverseRpmCap(&g_throttle_cfg,   REV_MAX_SPEED);

    ThrottleMap_SetTorqueCap(&g_throttle_cfg, ECO,    TORQUE_CAP_ECO_DEFAULT_NM);
    ThrottleMap_SetTorqueCap(&g_throttle_cfg, SPORTS,  TORQUE_CAP_SPORTS_DEFAULT_NM);
    ThrottleMap_SetReverseTorqueCap(&g_throttle_cfg,   TORQUE_CAP_REVERSE_DEFAULT_NM);

    ThrottleMap_SetDirection(&g_throttle_cfg, NEUTRAL);
    ThrottleMap_SetDriveMode(&g_throttle_cfg, ECO);
}
