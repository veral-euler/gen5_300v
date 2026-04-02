/**
 * @file    Resolver_Position.h
 * @brief   Resolver position manager for Pegasus 96V Motor Controller.
 *
 * Manages transition from SPI absolute angle (pre-Z) to
 * TIM2 incremental encoder tracking (post-Z).
 *
 * Phase 1 — Pre-Z (startup):
 *   Source: AD2S1210 SPI absolute electrical angle
 *   Used for: autotune initial angle, early FOC cycles
 *   Limitation: mechanical quadrant unknown, electrically correct
 *
 * Phase 2 — Z received (GPIOE PIN7 EXTI):
 *   Action: align TIM2 CNT to true mechanical position
 *           using SPI angle at startup + accumulated TIM2 counts
 *
 * Phase 3 — Post-Z (normal operation):
 *   Source: TIM2 incremental encoder counts
 *   Used for: all FOC cycles, speed calculation
 *   Benefit: fast (no SPI), quadrant resolved, fully accurate
 */

#ifndef RESOLVER_POSITION_H
#define RESOLVER_POSITION_H

#include "main.h"

/* =========================================================================
 * CONFIGURATION
 * ========================================================================= */

/** TIM2 encoder counts per full mechanical revolution
 *  = PPR × 4 (quadrature) — set to match your resolver PPR */
#define RESOLVER_COUNTS_PER_REV     16384U   /* Example: 1024 PPR × 4 */

/** Motor pole pairs */
#define RESOLVER_POLE_PAIRS         4U      /* Update to your motor Pp */

/** TIM2 period register — must match CubeMX TIM2 ARR setting */
#define RESOLVER_TIM2_ARR           TIM2_ARR   /* TIM2 is 32-bit on H743 */

/* =========================================================================
 * STRUCTURE
 * ========================================================================= */

typedef struct {
    bool     z_received;               /* True after first Z pulse           */
    float    elec_angle_at_startup;    /* SPI angle read at system init (rad) */
    uint32_t tim2_count_at_startup;    /* TIM2 CNT value set at startup       */
    float    theta_elec;               /* Last computed electrical angle (rad)*/
    float    theta_mech;               /* Last computed mechanical angle (rad)*/
    float    speed_rad_s;              /* Mechanical speed (rad/s), signed    */
    uint32_t last_tim2_count;          /* TIM2 CNT at last speed calculation  */
    uint32_t last_speed_tick;          /* HAL_GetTick() at last speed calc    */
} ResolverPosition_t;

/* =========================================================================
 * GLOBAL INSTANCE
 * ========================================================================= */

extern ResolverPosition_t g_resolver;

/* =========================================================================
 * API
 * ========================================================================= */

/**
 * @brief  Initialise resolver position manager.
 *
 * @details Call after AD2S1210_Init() and HAL_TIM_Encoder_Start().
 *          Steps:
 *            1. Read SPI absolute electrical angle
 *            2. Compute best-effort TIM2 CNT preload
 *            3. Preload TIM2 CNT
 *            4. Store startup values for Z alignment
 */
void ResolverPosition_Init(void);

/**
 * @brief  Call from GPIOE PIN7 EXTI IRQ handler on Z pulse.
 *
 * @details First Z pulse only — subsequent Z pulses ignored.
 *          Steps:
 *            1. Read SPI angle at Z moment
 *            2. Compute counts moved since startup
 *            3. Compute true mechanical angle
 *            4. Correct TIM2 CNT to true position
 *            5. Set z_received flag → switch angle source
 */
void ResolverPosition_ZPulseCallback(void);

/**
 * @brief  Update position and speed — call every FOC cycle.
 *
 * @details Pre-Z:  reads SPI angle directly (electrically correct)
 *          Post-Z: computes angle from TIM2 counts (fully accurate)
 *          Always: computes speed from TIM2 count derivative
 *
 * @param  dt  FOC cycle time step (s).
 */
void ResolverPosition_Update(float dt);

/**
 * @brief  Get compensated electrical angle for FOC model.
 * @return Electrical angle (rad), range [0, 2π].
 */
float ResolverPosition_GetThetaElec(void);

/**
 * @brief  Get mechanical angle.
 * @return Mechanical angle (rad), range [0, 2π].
 */
float ResolverPosition_GetThetaMech(void);

/**
 * @brief  Get mechanical speed.
 * @return Signed mechanical speed (rad/s).
 *         Positive = CW, Negative = CCW.
 */
float ResolverPosition_GetSpeed(void);

/**
 * @brief  Check if Z has been received and TIM2 is aligned.
 * @return true if post-Z (TIM2 source), false if pre-Z (SPI source).
 */
bool ResolverPosition_IsAligned(void);

#endif /* RESOLVER_POSITION_H */
