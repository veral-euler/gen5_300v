/**
 * @file    torque_management.c
 * @brief   Torque scaling based on speed and temperature derating
 *          for Pegasus 96V Motor Controller
 */

#include "Torque_Management.h"

SpeedTaperState_t taper_state;
TempDerateResult_t derate_result;

/* =========================================================================
 * TORQUE-SPEED CHARACTERISTIC TABLE
 * Populate with actual motor datasheet values. Ascending speed order REQUIRED.
 * ========================================================================= */

static const TorqueSpeedPoint_t TORQUE_SPEED_TABLE[TORQUE_SPEED_TABLE_SIZE] = {
    {  500.0f,  80.0f },
    { 1000.0f,  75.0f },
    { 1500.0f,  68.0f },
    { 2000.0f,  55.0f },
    { 2500.0f,  45.0f },
    { 3500.0f,  35.0f },
    { 4500.0f,  25.0f },
    { 6000.0f,  15.0f }
};

/* =========================================================================
 * TORQUE-SPEED CHARACTERISTIC LIMIT
 * ========================================================================= */

/**
 * @brief   Get maximum allowable torque at a given speed from the
 *          torque-speed characteristic table using linear interpolation.
 *
 * @details Below the first table entry  → returns first entry max torque
 *          Above the last table entry   → returns last entry max torque
 *          Between two entries          → linear interpolation
 *
 * @param   speed_rad_s   Speed feedback (rad/s), sign handled internally.
 * @return  Maximum allowable torque (Nm) at given speed.
 */
float get_torque_speed_limit(float speed_rad_s)
{
    float speed_rpm = RADS_TO_RPM(fabsf(speed_rad_s));

    /* Below first breakpoint — return first entry max torque */
    if (speed_rpm <= TORQUE_SPEED_TABLE[0U].speed_rpm)
        return TORQUE_SPEED_TABLE[0U].max_torque_nm;

    /* Above last breakpoint — return last entry max torque */
    if (speed_rpm >= TORQUE_SPEED_TABLE[TORQUE_SPEED_TABLE_SIZE - 1U].speed_rpm)
        return TORQUE_SPEED_TABLE[TORQUE_SPEED_TABLE_SIZE - 1U].max_torque_nm;

    /* Find segment containing speed_rpm and interpolate */
    for (uint32_t i = 0U; i < (TORQUE_SPEED_TABLE_SIZE - 1U); i++)
    {
        float spd_lo = TORQUE_SPEED_TABLE[i].speed_rpm;
        float spd_hi = TORQUE_SPEED_TABLE[i + 1U].speed_rpm;

        if (speed_rpm >= spd_lo && speed_rpm < spd_hi)
        {
            float trq_lo = TORQUE_SPEED_TABLE[i].max_torque_nm;
            float trq_hi = TORQUE_SPEED_TABLE[i + 1U].max_torque_nm;

            float t = (speed_rpm - spd_lo) / (spd_hi - spd_lo);
            return trq_lo + t * (trq_hi - trq_lo);
        }
    }

    /* Should never reach here — return last entry as fallback */
    return TORQUE_SPEED_TABLE[TORQUE_SPEED_TABLE_SIZE - 1U].max_torque_nm;
}

/* =========================================================================
 * SPEED TAPER SCALE
 * ========================================================================= */

/**
 * @brief   Compute torque scale factor based on speed and drive mode.
 *
 * @details Linearly tapers torque from 1.0 to 0.0 within TAPER_BAND_RPM
 *          below the mode speed limit. Hysteresis prevents oscillation
 *          at the taper entry/exit boundary when torque_ref is marginal.
 *
 *          ECO mode:    limit = 4500 RPM, taper starts at 4100 RPM
 *          SPORTS mode: limit = 6000 RPM, taper starts at 5600 RPM
 *
 * @param   speed_rad_s  Signed or unsigned speed feedback (rad/s).
 * @param   drive_mode   ECO or SPORTS.
 * @param   state        Persistent taper state — zero-init before first call.
 * @return  Torque scale factor [0.0, 1.0].
 */
float get_speed_taper_scale(float speed_rad_s, power_mode_t drive_mode,
                             fnr_state_t direction, SpeedTaperState_t *state)
{
    /* -------------------------------------------------------------------
     * Select speed limit:
     * REVERSE — fixed limit, ECO/SPORTS irrelevant
     * FORWARD — ECO or SPORTS limit
     * NEUTRAL — taper not applicable, return 1.0 (torque_ref will be 0 anyway)
     * ------------------------------------------------------------------- */
    float speed_limit_rpm;
    switch (direction)
    {
        case REVERSE:
            speed_limit_rpm = SPEED_LIMIT_REVERSE_RPM;
            break;

        case FORWARD:
            speed_limit_rpm = (drive_mode == ECO) ? SPEED_LIMIT_ECO_RPM
                                                  : SPEED_LIMIT_SPORTS_RPM;
            break;

        case NEUTRAL:
        default:
            return 1.0f;
    }

    float speed_rpm       = RADS_TO_RPM(fabsf(speed_rad_s));
    float taper_start_rpm = speed_limit_rpm - TAPER_BAND_RPM;

    /* -------------------------------------------------------------------
     * Hysteresis on taper entry / exit
     * Entry: speed crosses (taper_start + hysteresis) going up
     * Exit:  speed drops below (taper_start - hysteresis)
     * ------------------------------------------------------------------- */
    if (!state->in_taper &&
        (speed_rpm > (taper_start_rpm + TAPER_HYSTERESIS_RPM)))
    {
        state->in_taper = true;
    }
    else if (state->in_taper &&
             (speed_rpm < (taper_start_rpm - TAPER_HYSTERESIS_RPM)))
    {
        state->in_taper = false;
    }

    /* -------------------------------------------------------------------
     * Compute scale
     * ------------------------------------------------------------------- */
    if (!state->in_taper)
        return 1.0f;    /* Below taper band — full torque */

    float speed_headroom = speed_limit_rpm - speed_rpm;

    if (speed_headroom <= 0.0f)
        return 0.0f;    /* At or above speed limit — zero torque */

    /* Inside taper band — linear scale 1.0 → 0.0 */
    float scale = speed_headroom / TAPER_BAND_RPM;

    /* Clamp for floating point safety */
    if (scale > 1.0f) scale = 1.0f;
    if (scale < 0.0f) scale = 0.0f;

    return scale;
}

/* =========================================================================
 * TEMPERATURE DERATING SCALE
 * ========================================================================= */

/**
 * @brief   Compute torque derating scale from motor and controller temperatures.
 *
 * @details Motor temperature is priority — fminf of both scales is returned.
 *          Linear derating from 1.0 to 0.0 between derate start and end thresholds.
 *          Hard cutoff zeroes torque immediately above cutoff threshold.
 *
 *          Motor:      derate 80–100°C, cutoff 105°C
 *          Controller: derate 70–90°C,  cutoff 95°C
 *
 * @param   motor_temp  Motor temperature (°C).
 * @param   ctrl_temp   Controller temperature (°C).
 * @return  TempDerateResult_t with combined scale, individual scales, and status.
 */
TempDerateResult_t get_temp_derate_scale(float motor_temp, float ctrl_temp)
{
    TempDerateResult_t result;

    /* -------------------------------------------------------------------
     * Hard cutoff — zero torque immediately
     * ------------------------------------------------------------------- */
    if (motor_temp >= MOTOR_TEMP_CUTOFF || ctrl_temp >= CTRL_TEMP_CUTOFF)
    {
        result.motor_scale = 0.0f;
        result.ctrl_scale  = 0.0f;
        result.scale       = 0.0f;
        result.status      = TEMP_STATUS_CUTOFF;
        return result;
    }

    /* -------------------------------------------------------------------
     * Motor temperature scale (priority)
     * ------------------------------------------------------------------- */
    if (motor_temp <= MOTOR_TEMP_DERATE_START)
        result.motor_scale = 1.0f;
    else if (motor_temp >= MOTOR_TEMP_DERATE_END)
        result.motor_scale = 0.0f;
    else
        result.motor_scale = (MOTOR_TEMP_DERATE_END - motor_temp) /
                             (MOTOR_TEMP_DERATE_END - MOTOR_TEMP_DERATE_START);

    /* -------------------------------------------------------------------
     * Controller temperature scale
     * ------------------------------------------------------------------- */
    if (ctrl_temp <= CTRL_TEMP_DERATE_START)
        result.ctrl_scale = 1.0f;
    else if (ctrl_temp >= CTRL_TEMP_DERATE_END)
        result.ctrl_scale = 0.0f;
    else
        result.ctrl_scale = (CTRL_TEMP_DERATE_END - ctrl_temp) /
                            (CTRL_TEMP_DERATE_END - CTRL_TEMP_DERATE_START);

    /* -------------------------------------------------------------------
     * Combined scale — motor temperature is priority, take minimum
     * ------------------------------------------------------------------- */
    result.scale = fminf(result.motor_scale, result.ctrl_scale);

    result.status = (result.scale < 1.0f) ? TEMP_STATUS_DERATING
                                           : TEMP_STATUS_NORMAL;

    return result;
}

/* =========================================================================
 * COMBINED TORQUE SCALING
 * ========================================================================= */

/**
 * @brief   Apply torque-speed limit, temperature derating, and speed taper.
 *
 * @details Order of operations:
 *          1. Torque-speed characteristic limit  (motor capability)
 *          2. Temperature derating               (safety priority)
 *          3. Speed taper                        (mode speed limit)
 *
 *          torque_out = clamp(torque_ref, 0, T_spd_limit) * temp_scale * spd_scale
 *
 * @param   torque_ref          Raw torque reference (always positive, Nm).
 * @param   speed_rad_s         Speed feedback (rad/s).
 * @param   drive_mode          ECO or SPORTS.
 * @param   motor_temp          Motor temperature (°C).
 * @param   ctrl_temp           Controller temperature (°C).
 * @param   taper_state         Persistent speed taper state.
 * @param   derate_result_out   Optional output for derating result (NULL = ignore).
 * @return  Scaled torque reference (Nm) to pass to FOC model.
 */
float apply_torque_scaling(float torque_ref, float speed_rad_s,
                            power_mode_t drive_mode, fnr_state_t direction,
                            float motor_temp, float ctrl_temp,
                            SpeedTaperState_t *taper_state,
                            TempDerateResult_t *derate_result_out)
{
    /* Step 1: Torque-speed characteristic limit (motor capability) */
    float torque_limit   = get_torque_speed_limit(speed_rad_s);
    float torque_limited = fminf(torque_ref, torque_limit);

    /* Step 2: Temperature derating (safety priority) */
    TempDerateResult_t derate = get_temp_derate_scale(motor_temp, ctrl_temp);

    if (derate_result_out != NULL)
        *derate_result_out = derate;

    /* Hard cutoff — return immediately, no further computation */
    if (derate.status == TEMP_STATUS_CUTOFF)
        return 0.0f;

    float torque_derated = torque_limited * derate.scale;

    /* Step 3: Speed taper on derated torque */
    float speed_scale = get_speed_taper_scale(speed_rad_s, drive_mode,
                                               direction, taper_state);

    return torque_derated * speed_scale;
}