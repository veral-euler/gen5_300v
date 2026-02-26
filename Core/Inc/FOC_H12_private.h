/*
 * File: FOC_H12_private.h
 *
 * Code generated for Simulink model 'FOC_H12'.
 *
 * Model version                  : 19.6
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Feb  5 14:49:42 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef FOC_H12_private_h_
#define FOC_H12_private_h_
#include <stdbool.h>
#include <stdint.h>
#include "complex_types.h"
#include "FOC_H12_types.h"
#include "FOC_H12.h"

extern float look2_pbinlxpw(float u0, float u1, const float bp0[], const
  float bp1[], const float table[], uint32_t prevIndex[], const uint32_t
  maxIndex[], uint32_t stride);

#endif                                 /* FOC_H12_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
