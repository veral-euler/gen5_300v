/**
 * @file throttle_map.h
 * @brief Throttle voltage to RPM mapping with ECO/THUNDER mode support
 * @target STM32H743ZIT6
 */

#ifndef THROTTLE_MAP_H
#define THROTTLE_MAP_H

#include "main.h"

/* ─── Throttle Hardware Limits ─────────────────────────────────────────────── */
#define THROTTLE_V_MIN_MV       900U    /* 0.9 V in millivolts                 */
#define THROTTLE_V_MAX_MV       4000U   /* 4.0 V in millivolts                 */

/* ─── RPM Absolute Limits ───────────────────────────────────────────────────  */
#define RPM_MIN                 0U
#define RPM_ABS_MAX             SPORTS_MAX_SPEED   /* Physical max of the motor            */

/* ─── Default Mode RPM Caps (configurable at runtime) ──────────────────────  */
#define RPM_CAP_ECO_DEFAULT     ECO_MAX_SPEED
#define RPM_CAP_THUNDER_DEFAULT SPORTS_MAX_SPEED

/* ─── Drive Mode ────────────────────────────────────────────────────────────  */
typedef enum {
    DRIVE_MODE_ECO     = 0,
    DRIVE_MODE_THUNDER = 1
} DriveMode_t;

/* ─── Throttle Map Config ───────────────────────────────────────────────────  */
typedef struct {
    uint32_t    v_min_mv;           /* Throttle dead-low  (mV)                 */
    uint32_t    v_max_mv;           /* Throttle full-open (mV)                 */
    uint32_t    rpm_cap_eco;        /* RPM ceiling in ECO mode                 */
    uint32_t    rpm_cap_thunder;    /* RPM ceiling in THUNDER mode             */
    DriveMode_t mode;               /* Active drive mode                       */
} ThrottleMapConfig_t;

/* ─── API ───────────────────────────────────────────────────────────────────  */
void     ThrottleMap_Init(ThrottleMapConfig_t *cfg);
void     ThrottleMap_SetMode(ThrottleMapConfig_t *cfg, DriveMode_t mode);
void     ThrottleMap_SetRpmCap(ThrottleMapConfig_t *cfg, DriveMode_t mode, uint32_t rpm_cap);
uint32_t ThrottleMap_GetRPM(const ThrottleMapConfig_t *cfg, uint32_t v_mv);
void App_Init(void);

extern ThrottleMapConfig_t g_throttle_cfg;

#endif /* THROTTLE_MAP_H */