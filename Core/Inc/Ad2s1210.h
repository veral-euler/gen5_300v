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
 *   PG4 RES1    — GPIO Output High, Pull-Up   (14-bit resolution)
 *   PG5 RES0    — GPIO Output Low,  Pull-Down (14-bit resolution)
 *   PG6 A1      — GPIO Output Low,  Pull-Down (Normal mode)
 *   PG7 A0      — GPIO Output Low,  Pull-Down (Normal mode)
 *   PG8 SAMPLE  — GPIO Output High, Pull-Up (no PCB resistor, internal pull-up)
 *
 * AD2S1210 Pin mapping:
 *   Pin 2  CS        → GND (PCB hardwired)
 *   Pin 4  WR/FSYNC  → SPI1 NSS (hardware controlled)
 *   Pin 9  SOE       → GND (PCB hardwired, SPI mode always active)
 *   Pin 10 SAMPLE    → PG8
 *   Pin 11 DB15/SDO  → SPI1 MISO
 *   Pin 12 DB14/SDI  → SPI1 MOSI
 *   Pin 13 SCLK      → SPI1 SCLK
 *   Pin 33 RESET     → PG3 (PCB 10kΩ pull-up to VDD)
 *   Pin 1  RES1      → PG4
 *   Pin 36 (RES0)    → PG5
 *   Pin 36 A1        → PG6
 *   Pin 37 A0        → PG7
 */

#ifndef AD2S1210_H
#define AD2S1210_H

#include "main.h"

/* =========================================================================
 * HARDWARE DEFINES — update if GPIO pins change
 * ========================================================================= */

#define AD2S1210_SAMPLE_PORT        GPIOG
#define AD2S1210_SAMPLE_PIN         GPIO_PIN_8      /* PG8 — SAMPLE */

#define AD2S1210_RESET_PORT         GPIOG
#define AD2S1210_RESET_PIN          GPIO_PIN_3      /* PG3 — RESET  */

/* =========================================================================
 * RESOLUTION
 * RES1=1, RES0=0 → 14-bit → 16384 counts per electrical revolution
 * ========================================================================= */

#define AD2S1210_RESOLUTION         16384U      /* 2^14                          */
#define AD2S1210_RAW_SHIFT          2U          /* Upper 14 bits valid, shift >>2 */

/* =========================================================================
 * REGISTER ADDRESSES
 * ========================================================================= */

#define AD2S1210_REG_POSITION       0x80U       /* Absolute position (read)      */
#define AD2S1210_REG_VELOCITY       0x82U       /* Signed velocity   (read)      */
#define AD2S1210_REG_FAULT          0xFFU       /* Fault register    (read)      */
#define AD2S1210_REG_CONTROL        0x92U       /* Control register  (read/write)*/
#define AD2S1210_REG_SOFT_RESET     0xF0U       /* Software reset    (write)     */
#define AD2S1210_NOP                0x00U       /* No operation byte             */

/* =========================================================================
 * FAULT REGISTER BIT MASKS (Table 13 in datasheet)
 * ========================================================================= */

#define AD2S1210_FAULT_DOS_OVR      (1U << 7)   /* DOS overrange               */
#define AD2S1210_FAULT_DOS_MIS      (1U << 6)   /* DOS mismatch                */
#define AD2S1210_FAULT_LOT          (1U << 5)   /* Loss of tracking            */
#define AD2S1210_FAULT_VELOCITY     (1U << 4)   /* Velocity out of range       */
#define AD2S1210_FAULT_PHASE        (1U << 3)   /* Phase error                 */
#define AD2S1210_FAULT_CONFIG       (1U << 2)   /* Configuration parity error  */
#define AD2S1210_FAULT_LOS          (1U << 1)   /* Loss of signal              */
#define AD2S1210_FAULT_DEGRADE      (1U << 0)   /* Signal degradation          */

/* =========================================================================
 * RESULT STRUCT
 * ========================================================================= */

typedef struct {
    float    angle_rad;         /* Absolute electrical angle [0, 2π] (rad) */
    int16_t  velocity_raw;      /* Raw signed velocity from chip            */
    uint8_t  fault;             /* Fault register — 0x00 = no fault         */
    bool     valid;             /* True if read completed without HAL error  */
} AD2S1210_Result_t;

/* =========================================================================
 * GLOBAL INSTANCE
 * ========================================================================= */

extern AD2S1210_Result_t g_rdc;

/* =========================================================================
 * API
 * ========================================================================= */

/**
 * @brief  Initialise AD2S1210 — call once after HAL_SPI_Init().
 *         GPIO pins already configured by CubeMX.
 *         Performs power-on delay and software reset.
 */
void AD2S1210_Init(void);

/**
 * @brief  Read absolute electrical angle from position register.
 *
 * @details Pulses SAMPLE to latch current resolver position,
 *          then reads 16-bit position register via SPI.
 *          Upper 14 bits are valid — lower 2 bits shifted out.
 *
 * @return Absolute electrical angle in radians [0, 2π].
 *         Returns last valid reading on SPI error.
 */
float AD2S1210_ReadAngle(void);

/**
 * @brief  Read all data in one call — angle, velocity and fault.
 *         Use for diagnostics or CAN logging.
 *
 * @param  result  Pointer to result struct to populate.
 */
void AD2S1210_ReadAll(AD2S1210_Result_t *result);

/**
 * @brief  Read fault register.
 * @return Fault byte — 0x00 means no fault.
 *         Use AD2S1210_FAULT_* bitmasks to check individual faults.
 */
uint8_t AD2S1210_ReadFault(void);

/**
 * @brief  Issue software reset to AD2S1210.
 *         Call if fault register shows configuration error.
 */
void AD2S1210_SoftReset(void);

/**
 * @brief  Check if any fault is active.
 * @return true if any fault bit is set, false if clean.
 */
bool AD2S1210_IsFaulted(void);

#endif /* AD2S1210_H */