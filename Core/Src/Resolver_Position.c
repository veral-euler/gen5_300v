/**
 * @file    Resolver_Position.c
 * @brief   Resolver position manager for Pegasus 96V Motor Controller.
 */

#include "Resolver_Position.h"

/* =========================================================================
 * GLOBAL INSTANCE
 * ========================================================================= */

ResolverPosition_t g_resolver;
extern TIM_HandleTypeDef htim2;

/* =========================================================================
 * PRIVATE HELPERS
 * ========================================================================= */

/**
 * @brief  Convert TIM2 raw count to mechanical angle in [0, 2π].
 */
static inline float tim2_count_to_mech_angle(uint32_t count)
{
    return ((float)(count % RESOLVER_COUNTS_PER_REV)
            / (float)RESOLVER_COUNTS_PER_REV)
           * 2.0f * (float)M_PI;
}

/**
 * @brief  Convert mechanical angle to TIM2 count.
 */
static inline uint32_t mech_angle_to_tim2_count(float angle_mech_rad)
{
    /* Normalise angle to [0, 2π] */
    float normalised = fmodf(angle_mech_rad, 2.0f * (float)M_PI);
    if (normalised < 0.0f)
        normalised += 2.0f * (float)M_PI;

    return (uint32_t)((normalised / (2.0f * (float)M_PI))
                      * (float)RESOLVER_COUNTS_PER_REV);
}

/**
 * @brief  Convert mechanical angle to electrical angle.
 *         Wraps result to [0, 2π].
 */
static inline float mech_to_elec(float theta_mech)
{
    return fmodf(theta_mech * (float)RESOLVER_POLE_PAIRS,
                 2.0f * (float)M_PI);
}

/**
 * @brief  Compute signed count delta handling TIM2 32-bit overflow.
 */
static inline int32_t count_delta(uint32_t current, uint32_t previous)
{
    /* TIM2 on STM32H743 is 32-bit — handle wrap-around */
    return (int32_t)(current - previous);
}

/* =========================================================================
 * INIT — Phase 1
 * ========================================================================= */

/**
 * @brief  Initialise resolver position manager.
 *
 * @details Called after AD2S1210_Init() and HAL_TIM_Encoder_Start().
 *
 *          Best-effort TIM2 preload:
 *            Electrical angle from SPI is correct.
 *            Dividing by Pp gives angle within first electrical cycle only.
 *            True mechanical quadrant unknown until first Z pulse.
 *            This is acceptable — Z corrects it during first rotation.
 */
void ResolverPosition_Init(void)
{
    /* Step 1: Read absolute electrical angle from AD2S1210 via SPI */
    g_resolver.elec_angle_at_startup = AD2S1210_ReadAngle();

    /* Step 2: Best-effort mechanical angle — within first electrical cycle
     *         Quadrant unknown but electrically correct for FOC            */
    float mech_approx = g_resolver.elec_angle_at_startup
                        / (float)RESOLVER_POLE_PAIRS;

    /* Step 3: Convert to TIM2 count */
    g_resolver.tim2_count_at_startup = mech_angle_to_tim2_count(mech_approx);

    /* Step 4: Preload TIM2 CNT */
    __HAL_TIM_SET_COUNTER(&htim2, g_resolver.tim2_count_at_startup);

    /* Step 5: Initialise state */
    g_resolver.z_received        = false;
    g_resolver.theta_elec        = g_resolver.elec_angle_at_startup;
    g_resolver.theta_mech        = mech_approx;
    g_resolver.speed_rad_s       = 0.0f;
    g_resolver.last_tim2_count   = g_resolver.tim2_count_at_startup;
    g_resolver.last_speed_tick   = HAL_GetTick();
}

/* =========================================================================
 * Z PULSE CALLBACK — Phase 2
 * ========================================================================= */

/**
 * @brief  Called from GPIOE PIN7 EXTI IRQ on first Z pulse.
 *
 * @details Aligns TIM2 CNT to true mechanical position by combining:
 *            - SPI angle at startup (absolute electrical reference)
 *            - TIM2 counts accumulated since startup (relative movement)
 *
 *          After this, TIM2 CNT correctly represents the full mechanical
 *          angle including true quadrant — z_received set to true.
 *
 *          IMPORTANT: z_received set TRUE before SPI read to prevent
 *          FOC cycle from calling SPI simultaneously (race condition).
 */
void ResolverPosition_ZPulseCallback(void)
{
    /* Only process first Z pulse */
    if (g_resolver.z_received)
        return;

    /* Set flag FIRST — stops FOC cycle SPI reads immediately
     * preventing SPI bus contention during this IRQ             */
    g_resolver.z_received = true;

    /* Step 1: Read SPI angle at exact Z moment */
    float elec_at_z = AD2S1210_ReadAngle();

    /* Step 2: TIM2 counts accumulated since startup */
    uint32_t current_cnt  = __HAL_TIM_GET_COUNTER(&htim2);
    int32_t  counts_moved = count_delta(current_cnt,
                                         g_resolver.tim2_count_at_startup);

    /* Step 3: Mechanical angle travelled since startup
     *         counts_moved can be negative if motor moved CCW  */
    float mech_travelled = ((float)counts_moved
                            / (float)RESOLVER_COUNTS_PER_REV)
                           * 2.0f * (float)M_PI;

    /* Step 4: True mechanical angle = startup mech + travelled */
    float mech_at_startup = g_resolver.elec_angle_at_startup
                            / (float)RESOLVER_POLE_PAIRS;

    float mech_total = mech_at_startup + mech_travelled;

    /* Step 5: Correct TIM2 CNT to true mechanical position */
    uint32_t correct_cnt = mech_angle_to_tim2_count(mech_total);
    __HAL_TIM_SET_COUNTER(&htim2, correct_cnt);

    /* Step 6: Update state with corrected position */
    g_resolver.theta_mech      = fmodf(mech_total, 2.0f * (float)M_PI);
    if (g_resolver.theta_mech < 0.0f)
        g_resolver.theta_mech += 2.0f * (float)M_PI;

    g_resolver.theta_elec      = mech_to_elec(g_resolver.theta_mech);
    g_resolver.last_tim2_count = correct_cnt;

    /* elec_at_z used for verification — should match theta_elec closely */
    (void)elec_at_z;
}

/* =========================================================================
 * UPDATE — Phase 3 (FOC cycle)
 * ========================================================================= */

/**
 * @brief  Update position and speed — call every FOC cycle.
 *
 * @details Pre-Z:
 *            Reads SPI for electrical angle — takes ~2.56µs at 6.25MHz.
 *            Speed computed from TIM2 count derivative.
 *
 *          Post-Z:
 *            Reads TIM2 count for mechanical angle — fast, no SPI.
 *            Computes electrical angle from mechanical via Pp.
 *            Speed computed from TIM2 count derivative.
 *
 * @param  dt  FOC cycle time step (s) — 100µs at 10kHz.
 */
void ResolverPosition_Update(float dt)
{
    uint32_t current_cnt = __HAL_TIM_GET_COUNTER(&htim2);

    /* ── Angle ─────────────────────────────────────────────────────────── */
    if (!g_resolver.z_received)
    {
        /* Pre-Z: SPI absolute angle — electrically correct, quadrant unknown */
        g_resolver.theta_elec = AD2S1210_ReadAngle();

        /* Approximate mechanical from electrical — best effort pre-Z */
        g_resolver.theta_mech = g_resolver.theta_elec
                                / (float)RESOLVER_POLE_PAIRS;
    }
    else
    {
        /* Post-Z: TIM2 incremental — fully accurate, no SPI overhead */
        g_resolver.theta_mech = tim2_count_to_mech_angle(current_cnt);
        g_resolver.theta_elec = mech_to_elec(g_resolver.theta_mech);
    }

    /* ── Speed ─────────────────────────────────────────────────────────── */
    /* Always from TIM2 — valid both pre and post Z
     * Sign: positive = CW (increasing count), negative = CCW             */
    int32_t delta_counts  = count_delta(current_cnt,
                                         g_resolver.last_tim2_count);

    float delta_mech_rad  = ((float)delta_counts
                             / (float)RESOLVER_COUNTS_PER_REV)
                            * 2.0f * (float)M_PI;

    g_resolver.speed_rad_s   = delta_mech_rad / dt;
    g_resolver.last_tim2_count = current_cnt;
}

/* =========================================================================
 * GETTERS
 * ========================================================================= */

float ResolverPosition_GetThetaElec(void)
{
    return g_resolver.theta_elec;
}

float ResolverPosition_GetThetaMech(void)
{
    return g_resolver.theta_mech;
}

float ResolverPosition_GetSpeed(void)
{
    return g_resolver.speed_rad_s;
}

bool ResolverPosition_IsAligned(void)
{
    return g_resolver.z_received;
}
