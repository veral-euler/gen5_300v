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
 *          SAMPLE → PG8, no PCB pull-up, internal pull-up configured.
 */
static inline void AD2S1210_PulseSample(void)
{
    /* Ensure SAMPLE is high before pulse */
    HAL_GPIO_WritePin(AD2S1210_SAMPLE_PORT, AD2S1210_SAMPLE_PIN,
                      GPIO_PIN_SET);
    __NOP();

    /* Falling edge — latch position into register */
    HAL_GPIO_WritePin(AD2S1210_SAMPLE_PORT, AD2S1210_SAMPLE_PIN,
                      GPIO_PIN_RESET);
    __NOP();   /* 10ns @ 100MHz > 5ns minimum ✅ */

    /* Return high — ready for next latch */
    HAL_GPIO_WritePin(AD2S1210_SAMPLE_PORT, AD2S1210_SAMPLE_PIN,
                      GPIO_PIN_SET);
}

/**
 * @brief  Read 16-bit register from AD2S1210 via SPI.
 *
 * @details Single HAL_SPI_TransmitReceive call with 3 bytes to keep
 *          NSS (WR/FSYNC) asserted low for the entire frame duration.
 *
 *          Two separate HAL calls would toggle NSS HIGH between them,
 *          breaking the AD2S1210 frame and returning no data.
 *
 *          3-byte frame:
 *            TX[0] = register address  RX[0] = ignored (addr phase)
 *            TX[1] = NOP               RX[1] = data high byte
 *            TX[2] = NOP               RX[2] = data low byte
 *
 *          CS  hardwired GND — always selected, no toggle needed.
 *          SOE hardwired GND — SPI mode always active.
 *
 * @param  reg   Register address (AD2S1210_REG_*)
 * @return 16-bit raw register value, 0xFFFF on SPI error.
 */
static uint16_t AD2S1210_ReadRegister(uint8_t reg)
{
    uint8_t tx[3] = {reg,          AD2S1210_NOP, AD2S1210_NOP};
    uint8_t rx[3] = {AD2S1210_NOP, AD2S1210_NOP, AD2S1210_NOP};

    /* Single call — NSS stays LOW for all 3 bytes */
    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(&hspi1, tx, rx,
                                                        3U, 10U);
    if (status != HAL_OK)
        return 0xFFFFU;

    /* rx[0] = garbage (chip processing address byte)
     * rx[1] = high byte of position/register data
     * rx[2] = low byte  of position/register data  */
    return ((uint16_t)rx[1] << 8U) | (uint16_t)rx[2];
}

/**
 * @brief  Write a byte to a register on the AD2S1210.
 *
 * @details Single HAL_SPI_Transmit call — address + data in one frame.
 *          NSS (WR/FSYNC) stays low for both bytes automatically.
 *          Used for software reset and configuration register writes.
 *
 * @param  reg   Register address.
 * @param  data  Byte to write.
 */
static void AD2S1210_WriteRegister(uint8_t reg, uint8_t data)
{
    uint8_t tx[2] = {reg, data};

    /* Single transfer — address + data, NSS low for both bytes */
    HAL_SPI_Transmit(&hspi1, tx, 2U, 10U);
}

/* =========================================================================
 * PUBLIC API
 * ========================================================================= */

/**
 * @brief  Initialise AD2S1210.
 *
 * @details GPIO and SPI already configured by CubeMX.
 *          RESET pin → PG3, Pull-Up, High (PCB 10kΩ + internal pull-up)
 *          SAMPLE pin → PG8, Pull-Up, High (internal pull-up only)
 *
 *          Steps:
 *            1. Assert hardware RESET low → full chip reset
 *            2. Release RESET high → chip begins initialising
 *            3. Wait 20ms settling — resolver tracking loop stabilises
 *            4. Read and store initial fault status
 */
void AD2S1210_Init(void)
{
    /* Step 1: Assert hardware RESET low — resets all internal registers,
     *         tracking loop, fault register and encoder emulation outputs */
    HAL_GPIO_WritePin(AD2S1210_RESET_PORT, AD2S1210_RESET_PIN,
                      GPIO_PIN_RESET);
    HAL_Delay(1U);      /* Hold low — 1ms >> 10ns minimum requirement */

    /* Step 2: Release RESET high — chip begins tracking resolver signals */
    HAL_GPIO_WritePin(AD2S1210_RESET_PORT, AD2S1210_RESET_PIN,
                      GPIO_PIN_SET);

    /* Step 3: Wait for tracking loop to settle
     *         AD2S1210 requires 15ms minimum — use 20ms for margin  */
    HAL_Delay(20U);

    /* Step 4: Read initial fault register — store in global result
     *         LOS fault expected initially if resolver not connected */
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