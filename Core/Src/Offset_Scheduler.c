/**
 * @file    Offset_Scheduler.c
 * @brief   Dynamic electrical angle offset scheduling for Pegasus 96V FOC.
 */

#include "Offset_Scheduler.h"

/* =========================================================================
 * GLOBAL INSTANCE
 * ========================================================================= */

OffsetScheduler_t g_offset_sched;

/* =========================================================================
 * INIT
 * ========================================================================= */

/**
 * @brief  Initialise offset scheduler with configured offsets.
 */
void OffsetScheduler_Init(OffsetScheduler_t *sched,
                           float offset_cw_low, float offset_cw_high,
                           float offset_ccw)
{
    sched->offset_low      = offset_cw_low;
    sched->offset_high     = offset_cw_high;
    sched->offset_reverse  = offset_ccw;
    sched->offset_current  = offset_cw_low;   /* Start at CW light load offset */
    sched->offset_target   = offset_cw_low;
    sched->in_high_region  = false;
    sched->last_direction  = NEUTRAL;
}

/* =========================================================================
 * UPDATE — call every FOC cycle
 * ========================================================================= */

/**
 * @brief  Update offset scheduler.
 *
 * Step 1: Hysteresis — determine which region we are in based on I_rms.
 *         Entry into high region: I_rms crosses OFFSET_IRMS_ENTRY_A upward.
 *         Exit  from high region: I_rms drops below OFFSET_IRMS_EXIT_A.
 *
 * Step 2: Compute blend target between offset_low and offset_high
 *         using I_rms as the interpolation variable.
 *
 * Step 3: Rate limit the offset change to prevent instantaneous
 *         angle jumps causing torque disturbances.
 */
void OffsetScheduler_Update(OffsetScheduler_t *sched, float I_rms,
                             fnr_state_t direction, float dt)
{
    /* -------------------------------------------------------------------
     * Detect direction change — reset hysteresis state so FORWARD
     * always resumes scheduling from offset_low cleanly
     * ------------------------------------------------------------------- */
    if (direction != sched->last_direction)
    {
        sched->in_high_region = false;
        sched->last_direction = direction;
    }

    /* -------------------------------------------------------------------
     * REVERSE — fixed CCW offset from EEPROM, no I_rms scheduling
     * ------------------------------------------------------------------- */
    if (direction == REVERSE)
    {
        sched->offset_target = sched->offset_reverse;

        /* Rate limit toward fixed reverse offset */
        float delta    = sched->offset_target - sched->offset_current;
        float max_step = OFFSET_RATE_LIMIT_RAD_S * dt;

        if (delta > max_step)
            sched->offset_current += max_step;
        else if (delta < -max_step)
            sched->offset_current -= max_step;
        else
            sched->offset_current = sched->offset_target;

        return;
    }

    /* -------------------------------------------------------------------
     * FORWARD / NEUTRAL — I_rms based scheduling
     * Step 1: Hysteresis on region entry / exit
     * ------------------------------------------------------------------- */
    if (!sched->in_high_region && (I_rms > OFFSET_IRMS_ENTRY_A))
        sched->in_high_region = true;
    else if (sched->in_high_region && (I_rms < OFFSET_IRMS_EXIT_A))
        sched->in_high_region = false;

    /* -------------------------------------------------------------------
     * Step 2: Compute blend target
     * ------------------------------------------------------------------- */
    float t = 0.0f;

    if (sched->in_high_region)
    {
        t = (I_rms - OFFSET_IRMS_ENTRY_A) /
            (OFFSET_IRMS_FULL_A - OFFSET_IRMS_ENTRY_A);

        if (t < 0.0f) t = 0.0f;
        if (t > 1.0f) t = 1.0f;
    }

    sched->offset_target = sched->offset_low +
                           t * (sched->offset_high - sched->offset_low);

    /* -------------------------------------------------------------------
     * Step 3: Rate limit offset change
     * ------------------------------------------------------------------- */
    float delta    = sched->offset_target - sched->offset_current;
    float max_step = OFFSET_RATE_LIMIT_RAD_S * dt;

    if (delta > max_step)
        sched->offset_current += max_step;
    else if (delta < -max_step)
        sched->offset_current -= max_step;
    else
        sched->offset_current = sched->offset_target;
}

/* =========================================================================
 * GET THETA — call after Update
 * ========================================================================= */

/**
 * @brief  Compute compensated electrical angle.
 *
 * theta_elec = Pp * (theta_mech - offset_scheduled)
 *              + omega_e * transport_delay
 *
 * Transport delay correction:
 *   Between ADC sample and PWM taking effect, rotor has moved by:
 *   Δθ = omega_e * T_delay  (rad electrical)
 *   Adding this predicts where rotor will be when voltage is applied.
 *
 * Sign convention:
 *   omega_e is signed — positive CW, negative CCW.
 *   Transport delay correction automatically has correct sign.
 */
float OffsetScheduler_GetTheta(const OffsetScheduler_t *sched,
                                float theta_mech, float omega_e,
                                uint32_t pole_pairs)
{
    /* Scheduled offset applied in mechanical domain, then scaled */
    float theta_elec = (float)pole_pairs *
                       (theta_mech - sched->offset_current);

    /* Transport delay compensation — predict rotor position at PWM effect */
    float theta_delay = omega_e * OFFSET_TRANSPORT_DELAY_S;

    return theta_elec + theta_delay;
}

/* =========================================================================
 * GETTER
 * ========================================================================= */

float OffsetScheduler_GetCurrentOffset(const OffsetScheduler_t *sched)
{
    return sched->offset_current;
}