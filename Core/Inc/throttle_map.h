/**
 * @file throttle_map.h
 * @brief Throttle voltage to RPM mapping with ECO/THUNDER and FORWARD/REVERSE/NEUTRAL
 * @target STM32H743ZIT6
 */

#ifndef THROTTLE_MAP_H
#define THROTTLE_MAP_H

#include "main.h"

/* ─── Throttle Hardware Limits ─────────────────────────────────────────────── */
#define THROTTLE_V_MIN_MV           900U
#define THROTTLE_V_MAX_MV           4000U

/* ─── RPM Absolute Limits ───────────────────────────────────────────────────  */
#define RPM_MIN                     0U
#define RPM_ABS_MAX                 SPORTS_MAX_SPEED

/* ─── Default Mode RPM Caps ─────────────────────────────────────────────────  */
#define RPM_CAP_ECO_DEFAULT         ECO_MAX_SPEED
#define RPM_CAP_THUNDER_DEFAULT     SPORTS_MAX_SPEED
#define RPM_CAP_REVERSE_DEFAULT     REV_MAX_SPEED   /* Fixed cap for REVERSE — configurable */

/* ─── Drive Mode (ECO / THUNDER) ────────────────────────────────────────────  */
typedef enum {
    DRIVE_MODE_ECO     = 0,
    DRIVE_MODE_THUNDER = 1
} DriveMode_t;

/* ─── Direction (FORWARD / REVERSE / NEUTRAL) ───────────────────────────────  */
typedef enum {
    DIRECTION_NEUTRAL = 3,
    DIRECTION_FORWARD = 1,
    DIRECTION_REVERSE = 2
} Direction_t;

/* ─── Throttle Map Config ───────────────────────────────────────────────────  */
typedef struct {
    uint32_t    v_min_mv;           /* Throttle dead-low  (mV)                 */
    uint32_t    v_max_mv;           /* Throttle full-open (mV)                 */
    uint32_t    rpm_cap_eco;        /* RPM ceiling — FORWARD ECO               */
    uint32_t    rpm_cap_thunder;    /* RPM ceiling — FORWARD THUNDER           */
    uint32_t    rpm_cap_reverse;    /* RPM ceiling — REVERSE (any drive mode)  */
    DriveMode_t drive_mode;         /* ECO or THUNDER                          */
    Direction_t direction;          /* FORWARD, REVERSE, or NEUTRAL            */
} ThrottleMapConfig_t;

/* ─── API ───────────────────────────────────────────────────────────────────  */
void     ThrottleMap_Init(ThrottleMapConfig_t *cfg);
void     ThrottleMap_SetDriveMode(ThrottleMapConfig_t *cfg, DriveMode_t mode);
void     ThrottleMap_SetDirection(ThrottleMapConfig_t *cfg, Direction_t direction);
void     ThrottleMap_SetRpmCap(ThrottleMapConfig_t *cfg, DriveMode_t mode, uint32_t rpm_cap);
void     ThrottleMap_SetReverseRpmCap(ThrottleMapConfig_t *cfg, uint32_t rpm_cap);
uint32_t ThrottleMap_GetRPM(const ThrottleMapConfig_t *cfg, uint32_t v_mv);
void App_Init(void);

extern ThrottleMapConfig_t g_throttle_cfg;

#endif /* THROTTLE_MAP_H */