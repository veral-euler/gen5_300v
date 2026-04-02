/**
 * @file    AD2S1210.c
 * @brief   AD2S1210 Resolver-to-Digital Converter driver
 *          for Pegasus 96V Motor Controller
 */

#include "Ad2s1210.h"

/* =========================================================================
 * GLOBAL INSTANCE
 * ========================================================================= */

AD2S1210_Result_t g_rdc;
extern SPI_HandleTypeDef hspi1;

/* =========================================================================
 * PRIVATE HELPERS
 * ========================================================================= */

/**
 * @brief  Pulse SAMPLE pin HIGH → LOW → HIGH to latch resolver position.
 *
 * @details AD2S1210 latches position and velocity integrator outputs
 *          into registers on the HIGH-to-LOW transition of SAMPLE.
 *          Minimum SAMPLE low time: 5ns.
 *          At 100MHz sysclock: 1 NOP = 10ns > 5ns minimum.
 */
static inline void AD2S1210_PulseSample(void)
{
    /* Ensure SAMPLE is high before pulse */
    HAL_GPIO_WritePin(AD2S1210_SAMPLE_PORT, AD2S1210_SAMPLE_PIN,
                      GPIO_PIN_SET);
    delay_us(2);

    /* Falling edge — latch position into register */
    HAL_GPIO_WritePin(AD2S1210_SAMPLE_PORT, AD2S1210_SAMPLE_PIN,
                      GPIO_PIN_RESET);
    delay_us(2);   /* 10ns @ 100MHz > 5ns minimum ✅ */

    /* Return high — ready for next latch */
    HAL_GPIO_WritePin(AD2S1210_SAMPLE_PORT, AD2S1210_SAMPLE_PIN,
                      GPIO_PIN_SET);
}

/**
 * @brief  Read 16-bit register from AD2S1210 via SPI.
 *
 * @details Two-phase read:
 *          Phase 1: Transmit register address (1 byte)
 *                   NSS (WR/FSYNC) pulled low by hardware automatically
 *          Phase 2: Transmit NOP (0x00), receive 2 bytes of data
 *                   NSS released high by hardware after transfer
 *
 *          CS is hardwired GND — always selected.
 *          SOE is hardwired GND — SPI mode always active.
 *          No manual CS or SOE toggling needed.
 *
 * @param  reg   Register address (AD2S1210_REG_*)
 * @return 16-bit raw register value, 0xFFFF on error.
 */
static uint16_t AD2S1210_ReadRegister(uint8_t reg)
{
    HAL_StatusTypeDef status;
    uint8_t tx[2] = {reg,              AD2S1210_NOP};
    uint8_t rx[2] = {AD2S1210_NOP,     AD2S1210_NOP};

    /* Phase 1 — send register address
     * NSS (WR/FSYNC) pulled low automatically by SPI hardware */
    status = HAL_SPI_Transmit(&hspi1, &tx[0], 1U, 10U);
    if (status != HAL_OK)
        return 0xFFFFU;

    /* Phase 2 — send NOP, receive 16-bit register data */
    status = HAL_SPI_TransmitReceive(&hspi1, &tx[1], rx, 2U, 10U);
    if (status != HAL_OK)
        return 0xFFFFU;

    /* Combine two received bytes into 16-bit value */
    return ((uint16_t)rx[0] << 8U) | (uint16_t)rx[1];
}

/**
 * @brief  Write a byte to a register on the AD2S1210.
 *
 * @details Used for software reset and configuration register writes.
 *
 * @param  reg   Register address.
 * @param  data  Byte to write.
 */
static void AD2S1210_WriteRegister(uint8_t reg, uint8_t data)
{
    uint8_t tx[2] = {reg, data};

    /* Send address + data in single transfer */
    HAL_SPI_Transmit(&hspi1, tx, 2U, 10U);
}

/* =========================================================================
 * PUBLIC API
 * ========================================================================= */

/**
 * @brief  Initialise AD2S1210.
 *
 * @details GPIO and SPI already configured by CubeMX.
 *          This function:
 *            1. Waits for AD2S1210 power-on settling (20ms)
 *            2. Issues software reset
 *            3. Reads and stores initial fault status
 */
void AD2S1210_Init(void)
{
    /* Power-on settling — AD2S1210 requires 15ms minimum after VDD stable */
    HAL_Delay(20U);

    /* Software reset — clears any startup fault conditions */
    AD2S1210_SoftReset();
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_RESET);
    delay_us(1);
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_SET);

    /* Additional settling after reset */
    HAL_Delay(5U);

    /* Read initial fault register — store in global result */
    g_rdc.fault = AD2S1210_ReadFault();
    g_rdc.valid = true;
}

/**
 * @brief  Read absolute electrical angle.
 *
 * @details Steps:
 *          1. Pulse SAMPLE to latch current resolver position
 *          2. Read 16-bit position register
 *          3. Shift right by 2 (upper 14 bits are valid at 14-bit resolution)
 *          4. Scale to [0, 2π]
 *
 * @return Electrical angle in radians [0, 2π].
 */
float AD2S1210_ReadAngle(void)
{
    /* Step 1: Latch current resolver position */
    AD2S1210_PulseSample();

    /* Step 2: Read 16-bit position register */
    uint16_t raw = AD2S1210_ReadRegister(AD2S1210_REG_POSITION);

    if (raw == 0xFFFFU)
    {
        /* SPI error — return last valid angle */
        g_rdc.valid = false;
        return g_rdc.angle_rad;
    }

    /* Step 3: Shift right by 2 — upper 14 bits are position data
     *         Lower 2 bits are status/fault flags, not position */
    raw = raw >> AD2S1210_RAW_SHIFT;

    /* Step 4: Scale to [0, 2π] */
    float angle = ((float)raw / (float)AD2S1210_RESOLUTION)
                  * 2.0f * (float)M_PI;

    /* Store and return */
    g_rdc.angle_rad = angle;
    g_rdc.valid     = true;

    return angle;
}

/**
 * @brief  Read angle, velocity and fault in one call.
 *
 * @details Pulses SAMPLE once, then reads all three registers.
 *          Use for diagnostics or CAN logging — not needed every FOC cycle.
 */
void AD2S1210_ReadAll(AD2S1210_Result_t *result)
{
    if (result == NULL)
        return;

    /* Single SAMPLE pulse latches position, velocity and fault together */
    AD2S1210_PulseSample();

    /* Read position */
    uint16_t pos_raw = AD2S1210_ReadRegister(AD2S1210_REG_POSITION);
    if (pos_raw != 0xFFFFU)
    {
        pos_raw          >>= AD2S1210_RAW_SHIFT;
        result->angle_rad  = ((float)pos_raw / (float)AD2S1210_RESOLUTION)
                              * 2.0f * (float)M_PI;
        result->valid      = true;
    }
    else
    {
        result->valid = false;
    }

    /* Read velocity — signed 16-bit twos complement */
    uint16_t vel_raw      = AD2S1210_ReadRegister(AD2S1210_REG_VELOCITY);
    result->velocity_raw  = (int16_t)(vel_raw >> AD2S1210_RAW_SHIFT);

    /* Read fault register */
    result->fault = AD2S1210_ReadFault();

    /* Update global instance */
    g_rdc = *result;
}

/**
 * @brief  Read fault register.
 * @return Fault byte — 0x00 = no fault.
 */
uint8_t AD2S1210_ReadFault(void)
{
    uint16_t raw = AD2S1210_ReadRegister(AD2S1210_REG_FAULT);
    return (uint8_t)(raw & 0x00FFU);   /* Lower byte contains fault flags */
}

/**
 * @brief  Issue software reset.
 *         Clears fault register and reinitialises internal state machine.
 */
void AD2S1210_SoftReset(void)
{
    AD2S1210_WriteRegister(AD2S1210_REG_SOFT_RESET, 0x00U);
    HAL_Delay(1U);   /* Allow reset to complete */
}

/**
 * @brief  Check if any fault is active.
 * @return true if faulted, false if clean.
 */
bool AD2S1210_IsFaulted(void)
{
    return (AD2S1210_ReadFault() != 0x00U);
}