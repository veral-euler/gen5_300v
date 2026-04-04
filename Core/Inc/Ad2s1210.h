/**
 * @file    AD2S1210.h
 * @brief   AD2S1210 Resolver-to-Digital Converter driver
 *          for Pegasus 96V Motor Controller
 *
 * Hardware configuration:
 *   SPI1        — Full-Duplex Master, Mode 3, 6.25MHz, 8-bit, MSB first
 *   NSS         — Hardware Output → WR/FSYNC (Pin 4)
 *   CS          — Hardwired GND on PCB (always selected)
 *   SOE         — Hardwired GND on PCB (SPI mode always active)
 *   PG3 RESET   — GPIO Output High, Pull-Up (PCB 10kΩ + internal)
 *   PG4 RES1    — GPIO Output High, Pull-Up   (14-bit: RES1=1, RES0=0)
 *   PG5 RES0    — GPIO Output Low,  Pull-Down (14-bit: RES1=1, RES0=0)
 *   PG6 A1      — GPIO Output Low,  Pull-Down (Normal mode: A0=0, A1=0)
 *   PG7 A0      — GPIO Output Low,  Pull-Down (Normal mode: A0=0, A1=0)
 *   PG8 SAMPLE  — GPIO Output High, Pull-Up (internal pull-up, no PCB resistor)
 *
 * AD2S1210 Pin mapping:
 *   Pin 2  CS        → GND (PCB hardwired)
 *   Pin 4  WR/FSYNC  → SPI1 NSS (hardware auto-toggled)
 *   Pin 9  SOE       → GND (PCB hardwired, SPI mode always active)
 *   Pin 10 SAMPLE    → PG8
 *   Pin 11 DB15/SDO  → SPI1 MISO
 *   Pin 12 DB14/SDI  → SPI1 MOSI
 *   Pin 13 SCLK      → SPI1 SCLK
 *   Pin 33 RESET     → PG3 (PCB 10kΩ pull-up to VDD)
 *   Pin 36 A1        → PG6
 *   Pin 37 A0        → PG7
 *   Pin 48 RES0      → PG5
 *   Pin 1  RES1      → PG4
 *
 * Normal Mode SPI Read (datasheet page 28, Figure 35):
 *   A0=0, A1=0 → position output
 *   A0=0, A1=1 → velocity output
 *
 *   1. Pulse SAMPLE low ≥ 2×tCK + 20ns  (264ns at CLKIN=8.192MHz)
 *   2. Wait ≥ 6×tCK + 20ns after SAMPLE (752ns at CLKIN=8.192MHz)
 *   3. WR/FSYNC low → clock 24 bits out → WR/FSYNC high
 *
 *   24-bit output word (MSB first, no address byte):
 *     Bit 23-8 : 16-bit angular data (position or velocity)
 *     Bit  7-0 : 8-bit fault register
 *
 *   RX bytes:
 *     rx[0] = D15-D8  (angular high byte)
 *     rx[1] = D7-D0   (angular low  byte)
 *     rx[2] = fault register
 */

#ifndef AD2S1210_H
#define AD2S1210_H

#include "main.h"

/* =========================================================================
 * HARDWARE GPIO DEFINES
 * ========================================================================= */

#define AD2S1210_SAMPLE_PORT        GPIOG
#define AD2S1210_SAMPLE_PIN         GPIO_PIN_8      /* PG8 — SAMPLE             */

#define AD2S1210_RESET_PORT         GPIOG
#define AD2S1210_RESET_PIN          GPIO_PIN_3      /* PG3 — RESET (active low) */

#define AD2S1210_A0_PORT            GPIOG
#define AD2S1210_A0_PIN             GPIO_PIN_7      /* PG7 — A0 mode select     */

#define AD2S1210_A1_PORT            GPIOG
#define AD2S1210_A1_PIN             GPIO_PIN_6      /* PG6 — A1 mode select     */

/* =========================================================================
 * TIMING — based on CLKIN = 8.192MHz (tCK = 122ns)
 *
 * t16: SAMPLE pulse width min = 2×tCK + 20ns = 264ns
 *      At 100MHz sysclock (10ns/NOP): need 27 NOPs → use 30
 *
 * t30: Delay SAMPLE↑ to WR/FSYNC↓ min = 6×tCK + 20ns = 752ns
 *      At 100MHz sysclock (10ns/NOP): need 76 NOPs → use 80
 *
 * If your CLKIN differs, recalculate:
 *   t16_NOPs = ceil((2/fCLKIN + 20e-9) / 10e-9)
 *   t30_NOPs = ceil((6/fCLKIN + 20e-9) / 10e-9)
 * ========================================================================= */

#define AD2S1210_T16_NOPS           30U     /* SAMPLE low width: 30×10ns=300ns  */
#define AD2S1210_T30_NOPS           80U     /* SAMPLE to SPI:    80×10ns=800ns  */

/* =========================================================================
 * RESOLUTION — 14-bit (RES1=1, RES0=0)
 *
 * Position register is 16-bit. At 14-bit resolution:
 *   D15-D2: 14-bit position data (with hysteresis enabled, D1-D0=0)
 *   Shift right 2 to get [0, 16383]
 * ========================================================================= */

#define AD2S1210_RESOLUTION         16384U  /* 2^14 counts per electrical rev   */
#define AD2S1210_RAW_SHIFT          2U      /* Shift right 2 to extract 14-bit  */

/* =========================================================================
 * REGISTER ADDRESSES (for configuration mode reads/writes)
 * ========================================================================= */

#define AD2S1210_REG_POSITION       0x80U   /* Position register address        */
#define AD2S1210_REG_VELOCITY       0x82U   /* Velocity register address        */
#define AD2S1210_REG_LOS_THRESH     0x88U   /* LOS threshold      (read/write)  */
#define AD2S1210_REG_DOS_OVR_THRESH 0x89U   /* DOS overrange      (read/write)  */
#define AD2S1210_REG_DOS_MIS_THRESH 0x8AU   /* DOS mismatch       (read/write)  */
#define AD2S1210_REG_DOS_RST_MAX    0x8BU   /* DOS reset maximum  (read/write)  */
#define AD2S1210_REG_DOS_RST_MIN    0x8CU   /* DOS reset minimum  (read/write)  */
#define AD2S1210_REG_LOT_HI_THRESH  0x8DU   /* LOT high threshold (read/write)  */
#define AD2S1210_REG_LOT_LO_THRESH  0x8EU   /* LOT low  threshold (read/write)  */
#define AD2S1210_REG_EXCIT_FREQ     0x91U   /* Excitation frequency(read/write) */
#define AD2S1210_REG_CONTROL        0x92U   /* Control register   (read/write)  */
#define AD2S1210_REG_SOFT_RESET     0xF0U   /* Software reset     (write only, config mode) */
#define AD2S1210_REG_FAULT          0xFFU   /* Fault register     (read only,  config mode) */
#define AD2S1210_NOP                0x00U   /* No operation byte                */

/* =========================================================================
 * FAULT REGISTER BIT MASKS — Table 26, page 23
 * Active HIGH: bit set = fault active
 * ========================================================================= */

#define AD2S1210_FAULT_CLIPPED      (1U << 7)   /* D7: Sin/cos inputs clipped        */
#define AD2S1210_FAULT_LOS          (1U << 6)   /* D6: Sin/cos below LOS threshold   */
#define AD2S1210_FAULT_DOS_OVR      (1U << 5)   /* D5: Sin/cos exceed DOS overrange  */
#define AD2S1210_FAULT_DOS_MIS      (1U << 4)   /* D4: Sin/cos exceed DOS mismatch   */
#define AD2S1210_FAULT_LOT          (1U << 3)   /* D3: Tracking error exceeds LOT    */
#define AD2S1210_FAULT_VELOCITY     (1U << 2)   /* D2: Velocity exceeds max rate     */
#define AD2S1210_FAULT_PHASE        (1U << 1)   /* D1: Phase error exceeds lock range*/
#define AD2S1210_FAULT_CONFIG       (1U << 0)   /* D0: Configuration parity error    */

/* =========================================================================
 * A0/A1 MODE SELECT — Table 8, page 20
 * ========================================================================= */

#define AD2S1210_MODE_POSITION      0U          /* A0=0, A1=0: Normal, position out  */
#define AD2S1210_MODE_VELOCITY      1U          /* A0=0, A1=1: Normal, velocity out  */
#define AD2S1210_MODE_CONFIG        3U          /* A0=1, A1=1: Configuration mode    */

/* =========================================================================
 * RESULT STRUCT
 * ========================================================================= */

typedef struct {
    float    angle_rad;         /* Electrical angle [0, 2π] (rad)            */
    int16_t  velocity_raw;      /* Raw signed velocity (twos complement)      */
    uint8_t  fault;             /* Fault register byte (Table 26)             */
    bool     valid;             /* True if last SPI read succeeded            */
} AD2S1210_Result_t;

/* =========================================================================
 * GLOBAL INSTANCE
 * ========================================================================= */

extern AD2S1210_Result_t g_rdc;

/* =========================================================================
 * API
 * ========================================================================= */

/**
 * @brief  Initialise AD2S1210.
 *         Call after MX_SPI1_Init() and MX_GPIO_Init().
 *         Performs hardware reset and waits for tracking loop to settle.
 */
void AD2S1210_Init(void);

/**
 * @brief  Read absolute electrical angle — call every FOC cycle (pre-Z only).
 *
 * @details Normal mode read (A0=0, A1=0 → position output):
 *            1. Pulse SAMPLE ≥264ns → latch position into registers
 *            2. Wait ≥752ns        → t30 delay before SPI
 *            3. SPI 3-byte receive → [ang_hi][ang_lo][fault]
 *            4. Shift >>2, scale to [0, 2π]
 *            5. Apply π correction for swapped SIN/COS differential pair
 *
 * @return  Motor electrical angle [0, 2π] (rad).
 */
float AD2S1210_ReadAngle(void);

/**
 * @brief  Read angle + velocity + fault in one call.
 *         Use for diagnostics / CAN logging at lower rate.
 * @param  result  Pointer to result struct.
 */
void AD2S1210_ReadAll(AD2S1210_Result_t *result);

/**
 * @brief  Read fault register via configuration mode.
 * @return Fault byte per Table 26. 0x00 = no fault.
 */
uint8_t AD2S1210_ReadFault(void);

/**
 * @brief  Issue software reset (requires configuration mode).
 */
void AD2S1210_SoftReset(void);

/**
 * @brief  Check if any fault bit is set.
 * @return true if faulted.
 */
bool AD2S1210_IsFaulted(void);

#endif /* AD2S1210_H */