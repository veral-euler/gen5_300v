/*
 * File: rt_nonfinite.c
 *
 * Code generated for Simulink model 'Open_FOC0'.
 *
 * Model version                  : 1.51
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Feb 23 20:36:54 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stdbool.h>
#include "rt_nonfinite.h"
#include "math.h"

float rtNaN = -(float)NAN;
float rtInf = (float)INFINITY;
float rtMinusInf = -(float)INFINITY;
float rtNaNF = -(float)NAN;
float rtInfF = (float)INFINITY;
float rtMinusInfF = -(float)INFINITY;

/* Test if value is infinite */
bool rtIsInf(float value)
{
  return (bool)isinf(value);
}

/* Test if single-precision value is infinite */
bool rtIsInfF(float value)
{
  return (bool)isinf(value);
}

/* Test if value is not a number */
bool rtIsNaN(float value)
{
  return (bool)(isnan(value) != 0);
}

/* Test if single-precision value is not a number */
bool rtIsNaNF(float value)
{
  return (bool)(isnan(value) != 0);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
