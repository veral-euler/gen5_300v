/**
 * @file    Offset_Scheduler.h
 * @brief   Dynamic electrical angle offset scheduling for Pegasus 96V FOC.
 *
 * Compensates for:
 *  1. Magnetic saturation — I_rms based blend between offset_low
 *     (light load) and offset_high (heavy load) with hysteresis.
 *  2. Transport delay — computation + PWM latency angle error,
 *     grows linearly with electrical speed.
 *
 * Call order every FOC cycle:
 *  1. OffsetScheduler_Update()   — updates internal state
 *  2. OffsetScheduler_GetTheta() — returns compensated theta_elec
 */

#ifndef OFFSET_SCHEDULER_H
#define OFFSET_SCHEDULER_H

#include "main.h"

/* =========================================================================
 * CONFIGURATION
 * ========================================================================= */

/* offset_low  (CW, light load) and offset_reverse (CCW) are read from
 * EEPROM every power cycle and passed into OffsetScheduler_Init().
 * They are NOT hardcoded here.                                              */

/* Heavy load CW offset — from hit and trial tuning (rad mech)             */
/* This is offset_high passed into OffsetScheduler_Init()                  */
#define OFFSET_HIGH_RAD             0.72f

/* I_rms at which blending toward offset_high begins (A) */
#define OFFSET_IRMS_ENTRY_A         250.0f

/* I_rms below which scheduler reverts toward offset_low — hysteresis (A) */
#define OFFSET_IRMS_EXIT_A          220.0f

/* I_rms at which full offset_high is applied (A) */
#define OFFSET_IRMS_FULL_A          350.0f

/* Max rate of offset change — prevents instantaneous angle jump (rad mech/s) */
#define OFFSET_RATE_LIMIT_RAD_S     0.5f

/* Transport delay — ADC sample to PWM register update (s)          */
/* Measure on STM32H743: timestamp HAL_GetTick() or DWT between     */
/* ADC injected conversion complete and TIM1 CCR write              */
/* Typical value at 10kHz FOC: 100-150µs                            */
#define OFFSET_TRANSPORT_DELAY_S    0.0001f

/* =========================================================================
 * STRUCTURE
 * ========================================================================= */

typedef struct {
    float        offset_low;         /* CW light load offset — from EEPROM (rad mech)  */
    float        offset_high;        /* CW heavy load offset — from tuning (rad mech)  */
    float        offset_reverse;     /* CCW fixed offset    — from EEPROM (rad mech)   */
    float        offset_current;     /* Rate-limited applied offset (rad mech)         */
    float        offset_target;      /* Scheduler output before rate limit             */
    bool         in_high_region;     /* Hysteresis state                               */
    fnr_state_t  last_direction;     /* Last active direction — detect changes         */
} OffsetScheduler_t;

/* =========================================================================
 * GLOBAL INSTANCE
 * ========================================================================= */

extern OffsetScheduler_t g_offset_sched;

/* =========================================================================
 * API
 * ========================================================================= */

/**
 * @brief  Initialise offset scheduler — call once at startup after EEPROM read.
 *
 * @param  sched           Scheduler struct.
 * @param  offset_cw_low   CW light load offset (rad mech) — d.offset_angle_mech_cw from EEPROM.
 * @param  offset_cw_high  CW heavy load offset (rad mech) — from hit and trial tuning.
 * @param  offset_ccw      CCW fixed offset (rad mech)     — d.offset_angle_mech_ccw from EEPROM.
 */
void OffsetScheduler_Init(OffsetScheduler_t *sched,
                           float offset_cw_low, float offset_cw_high,
                           float offset_ccw);

/**
 * @brief  Update scheduler — call every FOC cycle before GetTheta.
 *
 * @details FORWARD/NEUTRAL: I_rms blend between offset_low and offset_high
 *                           with hysteresis and rate limiting.
 *          REVERSE:         Fixed OFFSET_REVERSE_RAD — no scheduling.
 *                           Hysteresis state reset on direction change
 *                           so FORWARD resumes from offset_low cleanly.
 *
 * @param  sched      Scheduler struct.
 * @param  I_rms      Phase RMS current (A), always positive.
 * @param  direction  Active direction from FNR controller.
 * @param  dt         FOC cycle time step (s).
 */
void OffsetScheduler_Update(OffsetScheduler_t *sched, float I_rms,
                             fnr_state_t direction, float dt);

/**
 * @brief  Get compensated electrical angle — call after Update.
 *
 * @details Applies scheduled mechanical offset and transport delay:
 *          theta_elec = Pp * (theta_mech - offset_scheduled)
 *                       + omega_e * transport_delay
 *
 * @param  sched        Scheduler struct.
 * @param  theta_mech   Raw mechanical angle from encoder (rad).
 * @param  omega_e      Electrical angular velocity (rad/s), signed.
 * @param  pole_pairs   Motor pole pairs.
 * @return Compensated electrical angle (rad) for FOC model.
 */
float OffsetScheduler_GetTheta(const OffsetScheduler_t *sched,
                                float theta_mech, float omega_e,
                                uint32_t pole_pairs);

/**
 * @brief  Get current applied offset for CAN logging / debug.
 * @return Current mechanical offset (rad).
 */
float OffsetScheduler_GetCurrentOffset(const OffsetScheduler_t *sched);

#endif /* OFFSET_SCHEDULER_H */