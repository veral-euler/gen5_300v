/**
 * @file    torque_management.h
 * @brief   Torque scaling based on speed and temperature derating
 *          for Pegasus 96V Motor Controller
 *
 * @note    DriveMode enum is NOT redefined here.
 *          Uses power_mode_t { ECO = 0, SPORTS = 1 } from main.h.
 */

#ifndef TORQUE_MANAGEMENT_H
#define TORQUE_MANAGEMENT_H

#include "main.h"   /* power_mode_t, project-wide defines */
/* =========================================================================
 * MACROS
 * ========================================================================= */

#define RPM_TO_RADS(x)      ((x) * 2.0f * (float)M_PI / 60.0f)
#define RADS_TO_RPM(x)      ((x) * 60.0f / (2.0f * (float)M_PI))

/* =========================================================================
 * TORQUE-SPEED CHARACTERISTIC LOOKUP TABLE
 * ========================================================================= */

/**
 * Number of points in the torque-speed characteristic table.
 * Add or remove points to match your motor datasheet curve.
 */
#define TORQUE_SPEED_TABLE_SIZE     8U

/**
 * @brief  Torque-speed characteristic lookup table entry.
 *
 * Populate TORQUE_SPEED_TABLE in torque_management.c with actual values.
 * Points MUST be in ascending speed order.
 *
 * Example curve (replace with actual motor data):
 *    500 RPM → 80 Nm
 *   1000 RPM → 75 Nm
 *   1500 RPM → 68 Nm
 *   2000 RPM → 55 Nm
 *   2500 RPM → 45 Nm
 *   3500 RPM → 35 Nm
 *   4500 RPM → 25 Nm
 *   6000 RPM → 15 Nm
 */
typedef struct {
    float speed_rpm;        /* Speed breakpoint (RPM)            */
    float max_torque_nm;    /* Maximum torque at this speed (Nm) */
} TorqueSpeedPoint_t;

/* =========================================================================
 * SPEED TAPER CONFIGURATION
 * ========================================================================= */

/* Speed limits per drive mode (RPM) */
#define SPEED_LIMIT_ECO_RPM         ECO_MAX_SPEED
#define SPEED_LIMIT_SPORTS_RPM      SPORTS_MAX_SPEED

/* Taper band — linear scale from 1.0 to 0.0 within this band below limit */
#define TAPER_BAND_RPM              400.0f

/* Hysteresis to prevent oscillation at taper boundary */
#define TAPER_HYSTERESIS_RPM        100.0f

/* =========================================================================
 * TEMPERATURE DERATING CONFIGURATION
 * ========================================================================= */

/* Motor temperature thresholds (°C) — priority */
#define MOTOR_TEMP_DERATE_START     100.0f
#define MOTOR_TEMP_DERATE_END       115.0f
#define MOTOR_TEMP_CUTOFF           MOTOR_TEMP_OT_LIMIT

/* Controller temperature thresholds (°C) */
#define CTRL_TEMP_DERATE_START      70.0f
#define CTRL_TEMP_DERATE_END        75.0f
#define CTRL_TEMP_CUTOFF            CONTRL_TEMP_OT_LIMIT

/* =========================================================================
 * ENUMERATIONS
 * ========================================================================= */

typedef enum {
    TEMP_STATUS_NORMAL   = 0,    /* All temperatures within nominal range */
    TEMP_STATUS_DERATING = 1,    /* At least one sensor in derating zone   */
    TEMP_STATUS_CUTOFF   = 2     /* Hard cutoff — torque zeroed, fault set */
} TempDerateStatus_t;

/* =========================================================================
 * STRUCTURES
 * ========================================================================= */

/**
 * @brief  Speed taper state — must persist across calls for hysteresis.
 *         Zero-initialise before first use.
 */
typedef struct {
    bool in_taper;          /* True when operating inside taper band */
} SpeedTaperState_t;

/**
 * @brief  Temperature derating result — individual and combined scales.
 */
typedef struct {
    float              scale;          /* Combined scale [0.0, 1.0]   */
    float              motor_scale;    /* Individual motor scale       */
    float              ctrl_scale;     /* Individual controller scale  */
    TempDerateStatus_t status;         /* NORMAL / DERATING / CUTOFF  */
} TempDerateResult_t;

/* =========================================================================
 * FUNCTION PROTOTYPES
 * ========================================================================= */

/**
 * @brief  Get max allowable torque at given speed from torque-speed table.
 * @param  speed_rad_s  Speed feedback (rad/s), sign handled internally.
 * @return Max torque (Nm) at current speed via linear interpolation.
 */
float get_torque_speed_limit(float speed_rad_s);

/**
 * @brief  Compute torque scale factor based on speed and drive mode.
 * @param  speed_rad_s  Speed feedback (rad/s), sign handled internally.
 * @param  drive_mode   ECO or SPORTS.
 * @param  state        Persistent taper state (must not be on stack in loop).
 * @return Torque scale factor [0.0, 1.0].
 */
float get_speed_taper_scale(float speed_rad_s, power_mode_t drive_mode,
                             SpeedTaperState_t *state);

/**
 * @brief  Compute torque derating scale from motor and controller temperatures.
 * @param  motor_temp  Motor temperature (°C).
 * @param  ctrl_temp   Controller temperature (°C).
 * @return TempDerateResult_t with combined scale, individual scales, and status.
 */
TempDerateResult_t get_temp_derate_scale(float motor_temp, float ctrl_temp);

/**
 * @brief  Apply torque-speed limit, temperature derating, and speed taper.
 *
 * @details Order of operations:
 *          1. Torque-speed characteristic limit  (motor capability)
 *          2. Temperature derating               (safety priority)
 *          3. Speed taper                        (mode speed limit)
 *
 * @param  torque_ref          Raw torque reference (always positive, Nm).
 * @param  speed_rad_s         Speed feedback (rad/s).
 * @param  drive_mode          ECO or SPORTS.
 * @param  motor_temp          Motor temperature (°C).
 * @param  ctrl_temp           Controller temperature (°C).
 * @param  taper_state         Persistent speed taper state.
 * @param  derate_result_out   Optional output for derating result (NULL = ignore).
 * @return Scaled torque reference (Nm) to pass to FOC model.
 */
float apply_torque_scaling(float torque_ref, float speed_rad_s,
                            power_mode_t drive_mode, float motor_temp,
                            float ctrl_temp, SpeedTaperState_t *taper_state,
                            TempDerateResult_t *derate_result_out);


extern SpeedTaperState_t taper_state;
extern TempDerateResult_t derate_result;
#endif /* TORQUE_MANAGEMENT_H */