/**
 * @file    throttle_map.h
 * @brief   Throttle voltage → RPM and throttle voltage → Torque mapping
 *          with ECO/SPORTS drive mode and FORWARD/REVERSE/NEUTRAL direction.
 * @target  STM32H743ZIT6
 *
 * @note    DriveMode and Direction enums are NOT redefined here.
 *          They are sourced from the application-level enums:
 *            power_mode_t  { ECO = 0, SPORTS = 1 }
 *            fnr_state_t   { FORWARD = 1, REVERSE = 2, NEUTRAL = 3 }
 */

#ifndef THROTTLE_MAP_H
#define THROTTLE_MAP_H

#include "main.h"   /* power_mode_t, fnr_state_t, project-wide defines */

/* =========================================================================
 * THROTTLE HARDWARE LIMITS
 * ========================================================================= */

#define THROTTLE_V_MIN_MV           980U
#define THROTTLE_V_MAX_MV           4100U

/* =========================================================================
 * RPM ABSOLUTE LIMITS
 * ========================================================================= */

#define RPM_MIN                     0U
#define RPM_ABS_MAX                 SPORTS_MAX_SPEED

/* =========================================================================
 * DEFAULT RPM CAPS PER MODE
 * ========================================================================= */

#define RPM_CAP_ECO_DEFAULT         ECO_MAX_SPEED
#define RPM_CAP_SPORTS_DEFAULT      SPORTS_MAX_SPEED
#define RPM_CAP_REVERSE_DEFAULT     REV_MAX_SPEED

/* =========================================================================
 * DEFAULT TORQUE CAPS PER MODE (Nm)
 * Adjust to match motor datasheet and application requirements.
 * ========================================================================= */

#define TORQUE_CAP_ECO_DEFAULT_NM       50.0f   /* ECO mode max torque (Nm)     */
#define TORQUE_CAP_SPORTS_DEFAULT_NM    80.0f   /* SPORTS mode max torque (Nm)  */
#define TORQUE_CAP_REVERSE_DEFAULT_NM   80.0f   /* REVERSE max torque (Nm)      */

/* =========================================================================
 * THROTTLE MAP CONFIG
 * ========================================================================= */

typedef struct {
    /* Hardware voltage range */
    uint32_t          v_min_mv;             /* Throttle dead-low  (mV)              */
    uint32_t          v_max_mv;             /* Throttle full-open (mV)              */

    /* RPM caps */
    uint32_t          rpm_cap_eco;          /* RPM ceiling — FORWARD ECO            */
    uint32_t          rpm_cap_sports;       /* RPM ceiling — FORWARD SPORTS         */
    uint32_t          rpm_cap_reverse;      /* RPM ceiling — REVERSE (any mode)     */

    /* Torque caps (Nm) */
    float             torque_cap_eco_nm;    /* Torque ceiling — FORWARD ECO (Nm)    */
    float             torque_cap_sports_nm; /* Torque ceiling — FORWARD SPORTS (Nm) */
    float             torque_cap_reverse_nm;/* Torque ceiling — REVERSE (Nm)        */

    /* State */
    power_mode_t  drive_mode;           /* ECO or SPORTS                        */
    fnr_state_t   direction;            /* FORWARD, REVERSE, or NEUTRAL         */
} ThrottleMapConfig_t;

/* =========================================================================
 * API — INITIALISATION
 * ========================================================================= */

void     ThrottleMap_Init(ThrottleMapConfig_t *cfg);

/* =========================================================================
 * API — SETTERS
 * ========================================================================= */

void     ThrottleMap_SetDriveMode(ThrottleMapConfig_t *cfg, power_mode_t mode);
void     ThrottleMap_SetDirection(ThrottleMapConfig_t *cfg, fnr_state_t direction);

void     ThrottleMap_SetRpmCap(ThrottleMapConfig_t *cfg,
                                power_mode_t mode, uint32_t rpm_cap);
void     ThrottleMap_SetReverseRpmCap(ThrottleMapConfig_t *cfg, uint32_t rpm_cap);

void     ThrottleMap_SetTorqueCap(ThrottleMapConfig_t *cfg,
                                   power_mode_t mode, float torque_cap_nm);
void     ThrottleMap_SetReverseTorqueCap(ThrottleMapConfig_t *cfg,
                                          float torque_cap_nm);

/* =========================================================================
 * API — MAPPING
 * ========================================================================= */

/**
 * @brief  Map throttle voltage → target RPM.7.
 * @param  cfg   Config struct (read-only).
 * @param  v_mv  ADC-derived throttle voltage in millivolts.
 * @return Target RPM magnitude. Direction conveyed by cfg->direction separately.
 */
uint32_t ThrottleMap_GetRPM(const ThrottleMapConfig_t *cfg, uint32_t v_mv);

/**
 * @brief  Map throttle voltage → torque reference (Nm).
 *
 * @details Effective torque cap = min(mode_cap, max_torque_nm).
 *          Caller should supply max_torque_nm from get_torque_speed_limit()
 *          so that the motor's torque-speed characteristic is respected.
 *
 *          NEUTRAL  → always returns 0.0f regardless of voltage or max_torque_nm.
 *          REVERSE  → uses torque_cap_reverse_nm, capped at max_torque_nm.
 *          FORWARD  → uses ECO or SPORTS cap based on drive_mode, capped at max_torque_nm.
 *
 * @param  cfg            Config struct (read-only).
 * @param  v_mv           ADC-derived throttle voltage in millivolts.
 * @param  max_torque_nm  Motor capability limit at current speed (Nm),
 *                        from get_torque_speed_limit(). Pass FLT_MAX if unused.
 * @return Torque reference in Nm (always >= 0.0f, direction in cfg->direction).
 */
float    ThrottleMap_GetTorque(const ThrottleMapConfig_t *cfg, uint32_t v_mv,
                                float max_torque_nm);

/* =========================================================================
 * API — APP INIT
 * ========================================================================= */

void App_Init(void);

/* =========================================================================
 * GLOBAL CONFIG INSTANCE
 * ========================================================================= */

extern ThrottleMapConfig_t g_throttle_cfg;

#endif /* THROTTLE_MAP_H */