/*
 * File: Angle_to_Speed.c
 *
 * Code generated for Simulink model 'Angle_to_Speed'.
 *
 * Model version                  : 1.15
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Fri May 22 16:16:07 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Angle_to_Speed.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

/* Block signals and states (default storage) */
Angle_to_Speed_DW rtAngle_to_Speed_DW;

/* External inputs (root inport signals with default storage) */
Angle_to_Speed_ExtU rtAngle_to_Speed_U;

/* External outputs (root outports fed by signals with default storage) */
Angle_to_Speed_ExtY rtAngle_to_Speed_Y;

/* Real-time model */
static Angle_to_Speed_RT_MODEL rtAngle_to_Speed_M_;
Angle_to_Speed_RT_MODEL *const rtAngle_to_Speed_M = &rtAngle_to_Speed_M_;

/* Model step function */
void Angle_to_Speed_step(void)
{
  float rtb_SpeedGain;
  uint16_t rtb_AlgoDataType;
  bool rtb_LogicalOperator;

  /* Logic: '<S4>/Logical Operator' incorporates:
   *  Constant: '<S4>/Time constant'
   *  Constant: '<S8>/Constant'
   *  RelationalOperator: '<S8>/Compare'
   *  Sum: '<S4>/Sum1'
   */
  rtb_LogicalOperator = ((float)(0.00086813365565862276 -
    rtAngle_to_Speed_DW.Probe[0]) <= 0.0F);

  /* DataTypeConversion: '<S3>/AlgoDataType' incorporates:
   *  Constant: '<S3>/PositionToCount'
   *  Inport: '<Root>/Theta'
   *  Product: '<S3>/Product'
   */
  rtb_AlgoDataType = (uint16_t)(10430.353959765725 * rtAngle_to_Speed_U.Theta);

  /* Gain: '<S3>/SpeedGain' incorporates:
   *  DataTypeConversion: '<S12>/DTC'
   *  Delay: '<S3>/Delay'
   *  Sum: '<S3>/SpeedCount'
   */
  rtb_SpeedGain = (float)(int16_t)((int16_t)rtb_AlgoDataType - (int16_t)
    rtAngle_to_Speed_DW.Delay_DSTATE[rtAngle_to_Speed_DW.CircBufIdx]) *
    0.326974064F; // for 10 khz 0.315699071F,  0.157849535F for 5kHz

  /* DiscreteIntegrator: '<S10>/Integrator' */
  if (rtAngle_to_Speed_DW.Integrator_IC_LOADING != 0) {
    rtAngle_to_Speed_DW.Integrator_DSTATE = rtb_SpeedGain;
    if (rtAngle_to_Speed_DW.Integrator_DSTATE > 10000.0F) {
      rtAngle_to_Speed_DW.Integrator_DSTATE = 10000.0F;
    } else if (rtAngle_to_Speed_DW.Integrator_DSTATE < -10000.0F) {
      rtAngle_to_Speed_DW.Integrator_DSTATE = -10000.0F;
    }
  }

  if (rtb_LogicalOperator || (rtAngle_to_Speed_DW.Integrator_PrevResetState != 0))
  {
    rtAngle_to_Speed_DW.Integrator_DSTATE = rtb_SpeedGain;
    if (rtAngle_to_Speed_DW.Integrator_DSTATE > 10000.0F) {
      rtAngle_to_Speed_DW.Integrator_DSTATE = 10000.0F;
    } else if (rtAngle_to_Speed_DW.Integrator_DSTATE < -10000.0F) {
      rtAngle_to_Speed_DW.Integrator_DSTATE = -10000.0F;
    }
  }

  /* Outport: '<Root>/Speed_filtered' incorporates:
   *  DiscreteIntegrator: '<S10>/Integrator'
   */
  rtAngle_to_Speed_Y.Speed_filtered = rtAngle_to_Speed_DW.Integrator_DSTATE;

  /* Outport: '<Root>/Speed' */
  rtAngle_to_Speed_Y.Speed = rtb_SpeedGain;

  /* Update for Delay: '<S3>/Delay' */
  rtAngle_to_Speed_DW.Delay_DSTATE[rtAngle_to_Speed_DW.CircBufIdx] =
    rtb_AlgoDataType;
  if (rtAngle_to_Speed_DW.CircBufIdx < 13U) /*28U*/
    rtAngle_to_Speed_DW.CircBufIdx++;
  } else {
    rtAngle_to_Speed_DW.CircBufIdx = 0U;
  }

  /* End of Update for Delay: '<S3>/Delay' */

  /* Update for DiscreteIntegrator: '<S10>/Integrator' incorporates:
   *  Constant: '<S4>/Time constant'
   *  MinMax: '<S4>/Max'
   *  Product: '<S2>/1//T'
   *  Sum: '<S2>/Sum1'
   */
  rtAngle_to_Speed_DW.Integrator_IC_LOADING = 0U;
  rtAngle_to_Speed_DW.Integrator_DSTATE += 1.0F / (float)fmax
    (rtAngle_to_Speed_DW.Probe[0], 0.00086813365565862276) * (rtb_SpeedGain -
    rtAngle_to_Speed_DW.Integrator_DSTATE) * 0.0002F;
  if (rtAngle_to_Speed_DW.Integrator_DSTATE > 10000.0F) {
    rtAngle_to_Speed_DW.Integrator_DSTATE = 10000.0F;
  } else if (rtAngle_to_Speed_DW.Integrator_DSTATE < -10000.0F) {
    rtAngle_to_Speed_DW.Integrator_DSTATE = -10000.0F;
  }

  rtAngle_to_Speed_DW.Integrator_PrevResetState = (int8_t)rtb_LogicalOperator;

  /* End of Update for DiscreteIntegrator: '<S10>/Integrator' */
}

/* Model initialize function */
void Angle_to_Speed_initialize(void)
{
  /* Start for Probe: '<S4>/Probe' */
  rtAngle_to_Speed_DW.Probe[0] = 0.0002F;
  rtAngle_to_Speed_DW.Probe[1] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S10>/Integrator' */
  rtAngle_to_Speed_DW.Integrator_IC_LOADING = 1U;
  
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
