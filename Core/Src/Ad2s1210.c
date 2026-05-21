/**
 * @file    AD2S1210.c
 * @brief   AD2S1210 Resolver-to-Digital Converter driver
 *          for Pegasus 96V Motor Controller
 *
 * Key datasheet references:
 *   Page 20 Table 8  : A0/A1 mode select
 *   Page 23 Table 26 : Fault register bit definitions
 *   Page 28          : Serial interface normal mode description
 *   Page 30 Figure 35: Serial interface read timing
 *   Page 31 Table 27 : tTRACK settling time after reset
 */

#include "Ad2s1210.h"

/* =========================================================================
 * GLOBAL INSTANCE
 * ========================================================================= */

AD2S1210_Result_t g_rdc;
extern SPI_HandleTypeDef hspi1;

/* =========================================================================
 * PRIVATE — TIMING HELPERS
 * ========================================================================= */

/**
 * @brief  Delay by executing N NOPs.
 *         At 100MHz sysclock: 1 NOP = 10ns.
 */
static void delay_nops(uint32_t n)
{
    for (uint32_t i = 0U; i < n; i++)
        __NOP();
}

/* =========================================================================
 * PRIVATE — A0/A1 MODE SELECT
 * ========================================================================= */

/**
 * @brief  Set A0/A1 mode per Table 8 (page 20):
 *           AD2S1210_MODE_POSITION (0): A0=0, A1=0 → normal, position out
 *           AD2S1210_MODE_VELOCITY (1): A0=0, A1=1 → normal, velocity out
 *           AD2S1210_MODE_CONFIG   (3): A0=1, A1=1 → configuration mode
 */
static void AD2S1210_SetMode(uint8_t mode)
{
    /* A0 */
    HAL_GPIO_WritePin(AD2S1210_A0_PORT, AD2S1210_A0_PIN,
                      (mode & 0x01U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    /* A1 */
    HAL_GPIO_WritePin(AD2S1210_A1_PORT, AD2S1210_A1_PIN,
                      (mode & 0x02U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

/* =========================================================================
 * PRIVATE — SAMPLE PULSE
 * ========================================================================= */

/**
 * @brief  Pulse SAMPLE HIGH → LOW → HIGH to latch resolver position.
 *
 * @details Per datasheet Figure 35 (page 30):
 *          t16: SAMPLE must be held low ≥ 2×tCK + 20ns
 *          At CLKIN=8.192MHz (tCK=122ns): min = 264ns
 *          At 100MHz sysclock (10ns/NOP): 30 NOPs = 300ns ✅
 *
 *          After SAMPLE goes high, must wait t30 before WR/FSYNC falls:
 *          t30 ≥ 6×tCK + 20ns = 752ns → 80 NOPs = 800ns ✅
 *          Caller is responsible for the t30 delay.
 */
static void AD2S1210_PulseSample(void)
{
    /* Ensure SAMPLE starts high */
    HAL_GPIO_WritePin(AD2S1210_SAMPLE_PORT, AD2S1210_SAMPLE_PIN,
                      GPIO_PIN_SET);
    __NOP();

    /* Falling edge — latch position, velocity and fault into registers */
    HAL_GPIO_WritePin(AD2S1210_SAMPLE_PORT, AD2S1210_SAMPLE_PIN,
                      GPIO_PIN_RESET);

    /* Hold low for t16: 30 NOPs = 300ns ≥ 264ns minimum ✅ */
    delay_nops(AD2S1210_T16_NOPS);

    /* Rising edge — complete pulse */
    HAL_GPIO_WritePin(AD2S1210_SAMPLE_PORT, AD2S1210_SAMPLE_PIN,
                      GPIO_PIN_SET);

    /* t30: Wait before WR/FSYNC can fall (SPI NSS)
     * 80 NOPs = 800ns ≥ 752ns minimum ✅                */
    delay_nops(AD2S1210_T30_NOPS);
}

/* =========================================================================
 * PRIVATE — NORMAL MODE READ
 * ========================================================================= */

/**
 * @brief  Read 24-bit normal mode frame from AD2S1210.
 *
 * @details Per datasheet page 28 (Serial Interface Normal Mode):
 *
 *          In normal mode NO address byte is needed.
 *          WR/FSYNC going low immediately starts 24-bit SDO output.
 *          SDI is don't care — nothing needs to be transmitted.
 *
 *          24-bit output word (MSB first):
 *            rx[0] = D15-D8  (angular high byte)
 *            rx[1] = D7-D0   (angular low  byte)
 *            rx[2] = fault register byte
 *
 *          NSS (WR/FSYNC) auto-toggled by SPI hardware:
 *            LOW at start → 24 SCLK pulses → HIGH at end
 *
 * @param  angular_out  Pointer for 16-bit angular value (NULL to discard)
 * @param  fault_out    Pointer for fault byte (NULL to discard)
 * @return HAL_OK on success
 */
static HAL_StatusTypeDef AD2S1210_ReadNormalFrame(uint16_t *angular_out,
                                                    uint8_t  *fault_out)
{
    uint8_t rx[3] = {0U, 0U, 0U};

    /* Receive only — no address, no TX needed in normal mode
     * NSS (WR/FSYNC) pulled LOW by hardware → 24 bits clocked out → HIGH */
    HAL_StatusTypeDef status = HAL_SPI_Receive(&hspi1, rx, 3U, 10U);

    if (status != HAL_OK)
        return HAL_ERROR;

    /* rx[0] = D15-D8 (angular high byte)
     * rx[1] = D7-D0  (angular low  byte)
     * rx[2] = fault register             */
    if (angular_out != NULL)
        *angular_out = ((uint16_t)rx[0] << 8U) | (uint16_t)rx[1];

    if (fault_out != NULL)
        *fault_out = rx[2];

    return HAL_OK;
}

/* =========================================================================
 * PRIVATE — CONFIGURATION MODE READ/WRITE
 * ========================================================================= */

/**
 * @brief  Write 8-bit data to a configuration register.
 *         Requires configuration mode (A0=1, A1=1).
 *
 * @details Per datasheet page 28 (Writing to AD2S1210):
 *          MSB of address = 1 (already set in register defines).
 *          MSB of data    = 0 (user data is 7-bit D6-D0).
 *
 *          Frame 1: send 8-bit address
 *          Frame 2: send 8-bit data
 *          Each frame: WR/FSYNC LOW → 8 SCLK pulses → WR/FSYNC HIGH
 */
void AD2S1210_WriteConfig(uint8_t reg, uint8_t data)
{
    uint8_t tx_addr = reg;
    uint8_t tx_data = data & 0x7FU;   /* MSB must be 0 for data writes */

    HAL_SPI_Transmit(&hspi1, &tx_addr, 1U, 10U);
    HAL_SPI_Transmit(&hspi1, &tx_data, 1U, 10U);
}

/**
 * @brief  Read 8-bit data from a configuration register.
 *         Requires configuration mode (A0=1, A1=1).
 *
 * @details Per datasheet page 28, Figure 34:
 *          In config mode, output shift register is 8 bits wide.
 *          Frame 1: send address → chip loads register into output shift reg
 *          Frame 2: send NOP    → receive 8-bit data on SDO
 *
 * @param  reg  Register address
 * @return 8-bit register data (D7=error bit, D6-D0=data)
 */
uint8_t AD2S1210_ReadConfig(uint8_t reg)
{
    uint8_t tx  = reg;
    uint8_t rx  = 0U;
    uint8_t nop = AD2S1210_NOP;

    HAL_SPI_Transmit(&hspi1, &tx, 1U, 10U);     /* Send address     */
    HAL_SPI_TransmitReceive(&hspi1, &nop, &rx,  /* Receive data     */
                             1U, 10U);
    return rx;
}

/* =========================================================================
 * PUBLIC API
 * ========================================================================= */

/**
 * @brief  Initialise AD2S1210.
 *
 * @details Per datasheet page 31, Figure 37 and Table 27:
 *          - RESET must be held low until VDD is stable
 *          - After RESET releases, wait tTRACK for tracking loop to settle
 *          - At 14-bit resolution: tTRACK = 25ms (Table 27)
 *          - After tTRACK, read and clear fault register
 *
 *          A0/A1 set to position mode (0,0) for normal operation.
 */
void AD2S1210_Init(void)
{
    /* Set normal mode: A0=0, A1=0 → position output */
    AD2S1210_SetMode(AD2S1210_MODE_CONFIG);

    /* Hardware reset — assert low */
    HAL_GPIO_WritePin(AD2S1210_RESET_PORT, AD2S1210_RESET_PIN,
                      GPIO_PIN_RESET);
    HAL_Delay(1U);      /* Hold low: 1ms >> 10µs minimum (page 31) */

    /* Release reset — tracking loop begins */
    HAL_GPIO_WritePin(AD2S1210_RESET_PORT, AD2S1210_RESET_PIN,
                      GPIO_PIN_SET);

    /* Wait tTRACK: 25ms at 14-bit resolution (Table 27, page 31)
     * Use 30ms for margin                                         */
    HAL_Delay(30U);

    AD2S1210_WriteConfig(AD2S1210_REG_CONTROL, 0x72);
    volatile uint8_t rx_ctrl_reg = AD2S1210_ReadConfig(AD2S1210_REG_CONTROL);

    AD2S1210_SetMode(AD2S1210_MODE_POSITION);

    /* Read initial fault status
     * Fault comes free with every normal mode read                */
    uint16_t dummy  = 0U;
    uint8_t  fault  = 0U;
    AD2S1210_PulseSample();
    AD2S1210_ReadNormalFrame(&dummy, &fault);
    g_rdc.fault = fault;
    g_rdc.valid = true;
}

/**
 * @brief  Read absolute electrical angle — call every FOC cycle (pre-Z only).
 *
 * @details Normal mode read sequence (Figure 35, page 30):
 *            1. A0=0, A1=0 (position mode — set in Init, stays static)
 *            2. Pulse SAMPLE ≥264ns → latch registers
 *            3. Wait ≥752ns (t30) → already inside PulseSample()
 *            4. SPI 3 bytes: RX=[ang_hi][ang_lo][fault]
 *            5. raw = (rx[0]<<8)|rx[1]  (16-bit unsigned binary)
 *            6. raw >>= 2               (discard D1-D0, get 14-bit [0,16383])
 *            7. angle = raw/16384 × 2π → [0, 2π]
 *            8. Apply π correction (swapped SIN/COS differential pair)
 *
 * @return  Electrical angle [0, 2π] rad. Last valid value on SPI error.
 */
float AD2S1210_ReadAngle(void)
{
    /* Pulse SAMPLE + wait t30 */
    AD2S1210_PulseSample();

    uint16_t raw   = 0U;
    uint8_t  fault = 0U;

    if (AD2S1210_ReadNormalFrame(&raw, &fault) != HAL_OK)
    {
        g_rdc.valid = false;
        return g_rdc.angle_rad;   /* Return last valid angle on SPI error */
    }

    /* Update fault — free with every read */
    g_rdc.fault = fault;

    /* At 14-bit resolution with hysteresis enabled (default):
     * D15-D2 = 14-bit position, D1-D0 = 0
     * Shift right 2 → [0, 16383]                                */
    raw >>= AD2S1210_RAW_SHIFT;

    /* Scale to [0, 2π] */
    float angle = ((float)raw / (float)AD2S1210_RESOLUTION)
                  * 2.0f * (float)M_PI;

    /* NOTE: If output is observed as [π, 2π] instead of [0, 2π],
     * the SIN or COS differential pair is physically swapped on PCB.
     * In that case uncomment the correction below:
     *
     * angle -= (float)M_PI;
     * if (angle < 0.0f) angle += 2.0f * (float)M_PI;
     */

    g_rdc.angle_rad = angle;
    g_rdc.valid     = true;

    return angle;
}

/**
 * @brief  Read angle, velocity and fault in one call.
 *
 * @details Pulses SAMPLE once — latches position, velocity and fault
 *          simultaneously. Reads position frame, then switches to velocity
 *          mode temporarily to read velocity frame.
 *
 *          Use for CAN logging / diagnostics at lower rate (e.g. 100Hz).
 *          For FOC cycle use AD2S1210_ReadAngle() instead.
 */
void AD2S1210_ReadAll(AD2S1210_Result_t *result)
{
    if (result == NULL)
        return;

    /* ── Position read ──────────────────────────────────────────────────── */
    /* A0=0, A1=0 already set */
    AD2S1210_PulseSample();   /* Latches ALL registers (pos + vel + fault) */

    uint16_t pos_raw = 0U;
    uint8_t  fault   = 0U;

    if (AD2S1210_ReadNormalFrame(&pos_raw, &fault) == HAL_OK)
    {
        pos_raw >>= AD2S1210_RAW_SHIFT;
        float angle = ((float)pos_raw / (float)AD2S1210_RESOLUTION)
                      * 2.0f * (float)M_PI;
        /* Uncomment if π offset correction needed (swapped differential pair):
         * angle -= (float)M_PI;
         * if (angle < 0.0f) angle += 2.0f * (float)M_PI;
         */
        result->angle_rad = angle;
        result->valid     = true;
    }
    else
    {
        result->valid = false;
    }
    result->fault = fault;

    /* ── Velocity read ───────────────────────────────────────────────────── */
    /* Switch to velocity mode: A0=0, A1=1 */
    AD2S1210_SetMode(AD2S1210_MODE_VELOCITY);

    /* No SAMPLE needed — already latched above.
     * Wait t30 before WR/FSYNC can fall (NSS)   */
    delay_nops(AD2S1210_T30_NOPS);

    uint16_t vel_raw = 0U;
    AD2S1210_ReadNormalFrame(&vel_raw, NULL);
    /* Velocity — full 16-bit twos complement, no shift
     * Per datasheet page 21: velocity register is always full 16-bit
     * regardless of resolution. D5-D0 are noise at 14-bit but cast
     * directly — shifting would corrupt the sign bit.              */
    result->velocity_raw = (int16_t)vel_raw;

    /* Restore position mode */
    AD2S1210_SetMode(AD2S1210_MODE_POSITION);

    /* Update global instance */
    g_rdc = *result;
}

/**
 * @brief  Read fault register via configuration mode.
 *
 * @details Per datasheet page 25 (Clearing the Fault Register):
 *          To read fault:
 *            1. Enter configuration mode (A0=1, A1=1)
 *            2. Write fault register address (0xFF)
 *            3. Read back 8-bit fault data
 *            4. Return to normal mode (A0=0, A1=0)
 *
 * @return Fault byte per Table 26. 0x00 = no fault.
 */
uint8_t AD2S1210_ReadFault(void)
{
    /* Enter configuration mode */
    AD2S1210_SetMode(AD2S1210_MODE_CONFIG);
    delay_nops(10U);   /* Short settle */

    /* Read fault register */
    uint8_t fault = AD2S1210_ReadConfig(AD2S1210_REG_FAULT);

    /* Return to normal position mode */
    AD2S1210_SetMode(AD2S1210_MODE_POSITION);

    g_rdc.fault = fault;   /* All 8 bits are valid fault flags per Table 26 */
    return g_rdc.fault;
}

/**
 * @brief  Issue software reset.
 *
 * @details Per datasheet page 23:
 *          Software reset requires configuration mode (A0=1, A1=1).
 *          Reinitialises excitation frequency and tracking loop.
 *          Configuration register data is preserved.
 *          Fault register is cleared.
 *
 *          Note: hardware RESET (PG3) is preferred and used in Init().
 *          Use software reset only for runtime fault clearing.
 */
void AD2S1210_SoftReset(void)
{
    /* Enter configuration mode */
    AD2S1210_SetMode(AD2S1210_MODE_CONFIG);
    delay_nops(10U);

    /* Write to software reset register (just addressing it triggers reset) */
    uint8_t tx = AD2S1210_REG_SOFT_RESET;
    HAL_SPI_Transmit(&hspi1, &tx, 1U, 10U);

    /* Return to normal position mode */
    AD2S1210_SetMode(AD2S1210_MODE_POSITION);

    HAL_Delay(5U);   /* Allow tracking loop to re-stabilise */
}

/**
 * @brief  Check if any fault bit is set.
 *
 * @details Reads fault from last normal mode read (g_rdc.fault).
 *          Does NOT trigger a new SPI read — uses the fault byte
 *          that comes free with every AD2S1210_ReadAngle() call.
 *
 * @return true if any fault bit set, false if clean.
 */
bool AD2S1210_IsFaulted(void)
{
    return (g_rdc.fault != 0x00U);
}