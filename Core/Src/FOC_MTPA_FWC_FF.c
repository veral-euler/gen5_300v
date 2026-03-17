/*
 * File: FOC_MTPA_FWC_FF.c
 *
 * Code generated for Simulink model 'FOC_MTPA_FWC_FF'.
 *
 * Model version                  : 18.345
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Tue Mar 17 15:55:35 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_MTPA_FWC_FF.h"
#include <stdint.h>
#include <math.h>
#include "FOC_MTPA_FWC_FF_private.h"
#include <stdbool.h>
#include "FOC_MTPA_FWC_FF_types.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"

/* Named constants for Chart: '<S160>/Chart' */
#define FOC_MTPA_FWC_FF_IN_FWC         ((uint8_t)1U)
#define FOC_MTPA_FWC_FF_IN_MTPA        ((uint8_t)2U)

/* Named constants for Chart: '<S161>/FNR_switching' */
#define FOC_MTPA_FWC_FF_IN_Forward     ((uint8_t)1U)
#define FOC_MTPA_FWC_FF_IN_Initial     ((uint8_t)2U)
#define FOC_MTPA_FWC_FF_IN_Neutral     ((uint8_t)4U)
#define FOC_MTPA_FWC_FF_IN_Reverse     ((uint8_t)5U)
#define FOC_MTPA_FWC__IN_Throttle_error ((uint8_t)6U)
#define FOC_MTPA__IN_Invalid_transition ((uint8_t)3U)

/* Block signals (default storage) */
B_FOC_MTPA_FWC_FF_T FOC_MTPA_FWC_FF_B;

/* Block states (default storage) */
DW_FOC_MTPA_FWC_FF_T FOC_MTPA_FWC_FF_DW;

/* External inputs (root inport signals with default storage) */
ExtU_FOC_MTPA_FWC_FF_T FOC_MTPA_FWC_FF_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_FOC_MTPA_FWC_FF_T FOC_MTPA_FWC_FF_Y;

/* Real-time model */
static RT_MODEL_FOC_MTPA_FWC_FF_T FOC_MTPA_FWC_FF_M_;
RT_MODEL_FOC_MTPA_FWC_FF_T *const FOC_MTPA_FWC_FF_M = &FOC_MTPA_FWC_FF_M_;
float rt_atan2f_snf(float u0, float u1)
{
  float y;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = (rtNaNF);
  } else if (rtIsInfF(u0) && rtIsInfF(u1)) {
    int32_t tmp;
    int32_t tmp_0;
    if (u0 > 0.0F) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    if (u1 > 0.0F) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    y = atan2f((float)tmp, (float)tmp_0);
  } else if (u1 == 0.0F) {
    if (u0 > 0.0F) {
      y = RT_PIF / 2.0F;
    } else if (u0 < 0.0F) {
      y = -(RT_PIF / 2.0F);
    } else {
      y = 0.0F;
    }
  } else {
    y = atan2f(u0, u1);
  }

  return y;
}

float rt_hypotf_snf(float u0, float u1)
{
  float a;
  float b;
  float y;
  a = fabsf(u0);
  b = fabsf(u1);
  if (a < b) {
    a /= b;
    y = sqrtf(a * a + 1.0F) * b;
  } else if (a > b) {
    b /= a;
    y = sqrtf(b * b + 1.0F) * a;
  } else if (rtIsNaNF(b)) {
    y = (rtNaNF);
  } else {
    y = a * 1.41421354F;
  }

  return y;
}

/* Model step function for TID0 */
void FOC_MTPA_FWC_FF_step0(void)       /* Sample time: [0.0001s, 0.0s] */
{
  double rtb_TrigonometricFunction1_tmp;
  double rtb_TrigonometricFunction_tmp;
  double rtb_sum_Ds;
  float rtb_Add1_l;
  float rtb_Gain;
  float rtb_Sum_f;
  float rtb_TmpSignalConversionAtMath_0;
  float rtb_UkYk1;
  float rtb_UkYk1_k;
  float rtb_V_qo;
  float rtb_add_c;
  int32_t rtb_State;
  bool guard1;
  bool guard2;
  bool tmp;

  /* Update the flag to indicate when data transfers from
   *  Sample time: [0.0001s, 0.0s] to Sample time: [0.001s, 0.0s]  */
  (FOC_MTPA_FWC_FF_M->Timing.RateInteraction.TID0_1)++;
  if ((FOC_MTPA_FWC_FF_M->Timing.RateInteraction.TID0_1) > 9) {
    FOC_MTPA_FWC_FF_M->Timing.RateInteraction.TID0_1 = 0;
  }

  /* Sum: '<S160>/Subtract' incorporates:
   *  Gain: '<S160>/Gain1'
   *  Inport: '<Root>/Bus_Voltage'
   *  Inport: '<Root>/Is_max'
   *  Inport: '<Root>/Motor_Parameters'
   *  Product: '<S160>/Product4'
   */
  FOC_MTPA_FWC_FF_Y.V_max = 0.577350259F * FOC_MTPA_FWC_FF_U.BusVoltage_V -
    (float)(FOC_MTPA_FWC_FF_U.Is_max * FOC_MTPA_FWC_FF_U.Motor_Parameters.Rs);

  /* Sum: '<S28>/Sum3' incorporates:
   *  Gain: '<S155>/Gain2'
   *  Inport: '<Root>/Motor_Parameters'
   *  Product: '<S155>/Divide1'
   *  Sum: '<S155>/Subtract2'
   */
  FOC_MTPA_FWC_FF_Y.Id_error = FOC_MTPA_FWC_FF_U.Motor_Parameters.Lambda /
    ((FOC_MTPA_FWC_FF_U.Motor_Parameters.Lq -
      FOC_MTPA_FWC_FF_U.Motor_Parameters.Ld) * 4.0F);

  /* Delay: '<S9>/Delay' incorporates:
   *  Constant: '<S9>/Constant'
   */
  if (FOC_MTPA_FWC_FF_DW.icLoad) {
    FOC_MTPA_FWC_FF_DW.Delay_DSTATE = 0.0F;
  }

  /* AlgorithmDescriptorDelegate generated from: '<S22>/a16' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  Product: '<S9>/delta rise limit'
   *  SampleTimeMath: '<S9>/sample time'
   *
   * About '<S9>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  FOC_MTPA_FWC_FF_Y.Id = FOC_MTPA_FWC_FF_U.Rate_limiter.Torque_gen_ramp_up *
    0.0001F;

  /* RateTransition: '<S2>/Rate Transition' */
  if (FOC_MTPA_FWC_FF_M->Timing.RateInteraction.TID0_1 == 1) {
    /* RateTransition: '<S2>/Rate Transition' */
    FOC_MTPA_FWC_FF_B.Iq_gen = FOC_MTPA_FWC_FF_DW.RateTransition_Buffer0;
  }

  /* End of RateTransition: '<S2>/Rate Transition' */

  /* Switch: '<S2>/Switch' incorporates:
   *  Delay: '<S1>/Delay One Step'
   *  Inport: '<Root>/Iq_Torque_ratio'
   *  Inport: '<Root>/Speed_1_Torque_0'
   *  Inport: '<Root>/T_ref'
   *  Product: '<S2>/Product1'
   *  Switch: '<S1>/Switch2'
   */
  if (FOC_MTPA_FWC_FF_U.Speed_1_Torque_0 > 0.0F) {
    rtb_Gain = (float)(FOC_MTPA_FWC_FF_B.Iq_gen *
                       FOC_MTPA_FWC_FF_U.Iq_Torque_ratio);
  } else if (FOC_MTPA_FWC_FF_DW.DelayOneStep_DSTATE > 2.0F) {
    /* Switch: '<S1>/Switch2' incorporates:
     *  Constant: '<S1>/Constant1'
     */
    rtb_Gain = 0.0F;
  } else {
    rtb_Gain = FOC_MTPA_FWC_FF_U.RefTrq;
  }

  /* Sum: '<S9>/Difference Inputs1' incorporates:
   *  Delay: '<S9>/Delay'
   *  Switch: '<S2>/Switch'
   *
   * Block description for '<S9>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_UkYk1 = rtb_Gain - FOC_MTPA_FWC_FF_DW.Delay_DSTATE;

  /* Switch: '<S227>/Switch2' incorporates:
   *  RelationalOperator: '<S227>/LowerRelop1'
   */
  if (!(rtb_UkYk1 > FOC_MTPA_FWC_FF_Y.Id)) {
    /* AlgorithmDescriptorDelegate generated from: '<S22>/a16' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  Product: '<S9>/delta fall limit'
     *  SampleTimeMath: '<S9>/sample time'
     *
     * About '<S9>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    FOC_MTPA_FWC_FF_Y.Id = 0.0001F *
      FOC_MTPA_FWC_FF_U.Rate_limiter.Torque_gen_ramp_down;

    /* Switch: '<S227>/Switch' incorporates:
     *  RelationalOperator: '<S227>/UpperRelop'
     */
    if (!(rtb_UkYk1 < FOC_MTPA_FWC_FF_Y.Id)) {
      /* AlgorithmDescriptorDelegate generated from: '<S22>/a16' */
      FOC_MTPA_FWC_FF_Y.Id = rtb_UkYk1;
    }

    /* End of Switch: '<S227>/Switch' */
  }

  /* End of Switch: '<S227>/Switch2' */

  /* Sum: '<S9>/Difference Inputs2' incorporates:
   *  Delay: '<S9>/Delay'
   *
   * Block description for '<S9>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_MTPA_FWC_FF_Y.T_gen = FOC_MTPA_FWC_FF_Y.Id +
    FOC_MTPA_FWC_FF_DW.Delay_DSTATE;

  /* Product: '<S156>/delta fall limit' incorporates:
   *  Abs: '<S155>/Abs1'
   *  Constant: '<S155>/Constant1'
   *  Gain: '<S155>/Gain'
   *  Inport: '<Root>/Motor_Parameters'
   *  Product: '<S155>/Divide'
   *  Product: '<S155>/Product'
   */
  FOC_MTPA_FWC_FF_Y.Id_ref_final = fabsf(2.0F * FOC_MTPA_FWC_FF_Y.T_gen) /
    (float)(FOC_MTPA_FWC_FF_U.Motor_Parameters.Lambda *
            FOC_MTPA_FWC_FF_U.Motor_Parameters.Pole_Pairs * 3.0);

  /* Switch: '<S168>/Switch2' incorporates:
   *  Inport: '<Root>/Id_Iq_MTPA_limit'
   *  RelationalOperator: '<S168>/LowerRelop1'
   *  RelationalOperator: '<S168>/UpperRelop'
   *  Switch: '<S168>/Switch'
   */
  if (FOC_MTPA_FWC_FF_Y.Id_ref_final >
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_up_limit) {
    /* Product: '<S156>/delta fall limit' */
    FOC_MTPA_FWC_FF_Y.Id_ref_final =
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_up_limit;
  } else if (FOC_MTPA_FWC_FF_Y.Id_ref_final <
             FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_low_limit) {
    /* Product: '<S156>/delta fall limit' incorporates:
     *  Switch: '<S168>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Id_ref_final =
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_low_limit;
  }

  /* End of Switch: '<S168>/Switch2' */

  /* Product: '<S156>/delta fall limit' incorporates:
   *  Math: '<S155>/Math Function2'
   */
  FOC_MTPA_FWC_FF_Y.Id_ref_final *= FOC_MTPA_FWC_FF_Y.Id_ref_final;

  /* Sum: '<S155>/Subtract' incorporates:
   *  Abs: '<S155>/Abs2'
   *  Gain: '<S155>/Gain4'
   *  Math: '<S155>/Math Function'
   *  Sqrt: '<S155>/Sqrt'
   *  Sum: '<S155>/Add'
   */
  FOC_MTPA_FWC_FF_Y.Id_ref_MTPA = FOC_MTPA_FWC_FF_Y.Id_error - sqrtf(fabsf
    (FOC_MTPA_FWC_FF_Y.Id_error * FOC_MTPA_FWC_FF_Y.Id_error + 0.5F *
     FOC_MTPA_FWC_FF_Y.Id_ref_final));

  /* Switch: '<S167>/Switch2' incorporates:
   *  Inport: '<Root>/Id_Iq_MTPA_limit'
   *  RelationalOperator: '<S167>/LowerRelop1'
   *  RelationalOperator: '<S167>/UpperRelop'
   *  Switch: '<S167>/Switch'
   */
  if (FOC_MTPA_FWC_FF_Y.Id_ref_MTPA >
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_up_limit) {
    /* Sum: '<S155>/Subtract' */
    FOC_MTPA_FWC_FF_Y.Id_ref_MTPA =
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_up_limit;
  } else if (FOC_MTPA_FWC_FF_Y.Id_ref_MTPA <
             FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_low_limit) {
    /* Sum: '<S155>/Subtract' incorporates:
     *  Switch: '<S167>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Id_ref_MTPA =
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_low_limit;
  }

  /* End of Switch: '<S167>/Switch2' */

  /* Sqrt: '<S155>/Sqrt1' incorporates:
   *  Abs: '<S155>/Abs'
   *  Math: '<S155>/Math Function3'
   *  Sum: '<S155>/Subtract1'
   */
  FOC_MTPA_FWC_FF_Y.Iq_ref_MTPA = sqrtf(fabsf(FOC_MTPA_FWC_FF_Y.Id_ref_final -
    FOC_MTPA_FWC_FF_Y.Id_ref_MTPA * FOC_MTPA_FWC_FF_Y.Id_ref_MTPA));

  /* Product: '<S156>/delta fall limit' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion'
   *  Inport: '<Root>/Actual Speed_mech_rpm'
   *  Inport: '<Root>/Motor_Parameters'
   *  Product: '<S160>/Product'
   */
  FOC_MTPA_FWC_FF_Y.Id_ref_final = FOC_MTPA_FWC_FF_U.Motor_Parameters.Pole_Pairs
    * (float)FOC_MTPA_FWC_FF_U.MtrSpd;

  /* Gain: '<S160>/Gain' incorporates:
   *  Inport: '<Root>/Motor_Parameters'
   *  Product: '<S160>/Product1'
   */
  rtb_UkYk1 = -(FOC_MTPA_FWC_FF_Y.Id_ref_final *
                FOC_MTPA_FWC_FF_U.Motor_Parameters.Lq *
                FOC_MTPA_FWC_FF_Y.Iq_ref_MTPA);

  /* Product: '<S160>/Product3' incorporates:
   *  Inport: '<Root>/Motor_Parameters'
   *  Product: '<S160>/Product2'
   *  Sum: '<S160>/Add'
   */
  rtb_V_qo = (FOC_MTPA_FWC_FF_U.Motor_Parameters.Ld *
              FOC_MTPA_FWC_FF_Y.Id_ref_MTPA +
              FOC_MTPA_FWC_FF_U.Motor_Parameters.Lambda) *
    FOC_MTPA_FWC_FF_Y.Id_ref_final;

  /* Outputs for IfAction SubSystem: '<S7>/If Action Subsystem1' incorporates:
   *  ActionPort: '<S154>/Action Port'
   */
  /* If: '<S7>/If' incorporates:
   *  Math: '<S160>/Square'
   *  Math: '<S160>/Square1'
   *  Sqrt: '<S160>/Sqrt'
   *  Sqrt: '<S164>/Sqrt'
   *  Sum: '<S160>/Add1'
   */
  FOC_MTPA_FWC_FF_Y.V_s = sqrtf(rtb_UkYk1 * rtb_UkYk1 + rtb_V_qo * rtb_V_qo);

  /* End of Outputs for SubSystem: '<S7>/If Action Subsystem1' */

  /* Chart: '<S160>/Chart' */
  guard1 = false;
  guard2 = false;
  if (FOC_MTPA_FWC_FF_DW.is_active_c3_FOC_MTPA_FWC_FF == 0) {
    FOC_MTPA_FWC_FF_DW.is_active_c3_FOC_MTPA_FWC_FF = 1U;
    FOC_MTPA_FWC_FF_DW.is_c3_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_MTPA;
    rtb_State = 0;
    guard2 = true;
  } else if (FOC_MTPA_FWC_FF_DW.is_c3_FOC_MTPA_FWC_FF == FOC_MTPA_FWC_FF_IN_FWC)
  {
    if (FOC_MTPA_FWC_FF_Y.V_s < 0.8F * FOC_MTPA_FWC_FF_Y.V_max) {
      FOC_MTPA_FWC_FF_DW.is_c3_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_MTPA;
      rtb_State = 0;
      guard2 = true;
    } else {
      rtb_State = 1;
      guard1 = true;
    }

    /* case IN_MTPA: */
  } else if (FOC_MTPA_FWC_FF_Y.V_s > 0.9F * FOC_MTPA_FWC_FF_Y.V_max) {
    FOC_MTPA_FWC_FF_DW.is_c3_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_FWC;
    rtb_State = 1;
    guard1 = true;
  } else {
    rtb_State = 0;
    guard2 = true;
  }

  if (guard2) {
    /* Outputs for IfAction SubSystem: '<S7>/If Action Subsystem' incorporates:
     *  ActionPort: '<S153>/Action Port'
     */
    /* If: '<S7>/If' incorporates:
     *  Merge: '<S7>/Merge'
     *  SignalConversion generated from: '<S153>/Id_ref'
     *  SignalConversion generated from: '<S153>/Iq_ref'
     */
    FOC_MTPA_FWC_FF_B.Merge[0] = FOC_MTPA_FWC_FF_Y.Id_ref_MTPA;
    FOC_MTPA_FWC_FF_B.Merge[1] = FOC_MTPA_FWC_FF_Y.Iq_ref_MTPA;

    /* End of Outputs for SubSystem: '<S7>/If Action Subsystem' */
  }

  if (guard1) {
    /* Outputs for IfAction SubSystem: '<S7>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S154>/Action Port'
     */
    /* If: '<S7>/If' incorporates:
     *  Constant: '<S162>/Constant'
     *  Constant: '<S162>/Constant1'
     *  Constant: '<S162>/Modulation index threshold'
     *  Constant: '<S166>/Constant1'
     *  DiscreteIntegrator: '<S162>/Discrete-Time Integrator'
     *  Fcn: '<S163>/x->r'
     *  Fcn: '<S163>/x->theta'
     *  Fcn: '<S165>/r->x'
     *  Fcn: '<S165>/theta->y'
     *  Gain: '<S162>/Gain'
     *  Gain: '<S162>/Gain1'
     *  Merge: '<S7>/Merge'
     *  Product: '<S162>/Product'
     *  Product: '<S164>/Product'
     *  Saturate: '<S162>/Saturation'
     *  SignalConversion generated from: '<S154>/Out1'
     *  Sum: '<S162>/Sum'
     *  Sum: '<S162>/Sum1'
     *  Sum: '<S162>/Sum2'
     *  Sum: '<S162>/Sum3'
     *  Sum: '<S162>/Sum4'
     *  Switch: '<S166>/Switch'
     *  UnitDelay: '<S162>/Unit Delay'
     */
    if (FOC_MTPA_FWC_FF_Y.V_max > 0.1F) {
      rtb_Gain = FOC_MTPA_FWC_FF_Y.V_max;
    } else {
      rtb_Gain = 0.1F;
    }

    FOC_MTPA_FWC_FF_DW.DiscreteTimeIntegrator_DSTATE += ((float)(1.0 -
      FOC_MTPA_FWC_FF_Y.V_s / rtb_Gain) * can_d.Kfw + can_d.Kaw *
      FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE_p) * 0.0001F;
    if (FOC_MTPA_FWC_FF_DW.DiscreteTimeIntegrator_DSTATE > 1.0F) {
      rtb_UkYk1 = 1.0F;
    } else if (FOC_MTPA_FWC_FF_DW.DiscreteTimeIntegrator_DSTATE < 0.0F) {
      rtb_UkYk1 = 0.0F;
    } else {
      rtb_UkYk1 = FOC_MTPA_FWC_FF_DW.DiscreteTimeIntegrator_DSTATE;
    }

    FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE_p = rtb_UkYk1 -
      FOC_MTPA_FWC_FF_DW.DiscreteTimeIntegrator_DSTATE;
    rtb_UkYk1 = (float)(3.1415926535897931 - (float)(3.1415926535897931 -
      rt_atan2f_snf(FOC_MTPA_FWC_FF_Y.Iq_ref_MTPA, FOC_MTPA_FWC_FF_Y.Id_ref_MTPA))
                        * rtb_UkYk1);
    rtb_V_qo = rt_hypotf_snf(FOC_MTPA_FWC_FF_Y.Id_ref_MTPA,
      FOC_MTPA_FWC_FF_Y.Iq_ref_MTPA);
    FOC_MTPA_FWC_FF_B.Merge[0] = rtb_V_qo * cosf(rtb_UkYk1);
    FOC_MTPA_FWC_FF_B.Merge[1] = rtb_V_qo * sinf(rtb_UkYk1);

    /* End of Outputs for SubSystem: '<S7>/If Action Subsystem1' */
  }

  /* End of Chart: '<S160>/Chart' */

  /* Logic: '<S161>/Logical Operator' incorporates:
   *  Inport: '<Root>/Throttle_input'
   *  RelationalOperator: '<S161>/Relational Operator'
   *  RelationalOperator: '<S161>/Relational Operator1'
   */
  FOC_MTPA_FWC_FF_Y.Throttle_error =
    ((FOC_MTPA_FWC_FF_U.Throttle_input.Throttle_Inst_Voltage >=
      FOC_MTPA_FWC_FF_U.Throttle_input.Max_Throttle_Voltage) ||
     (FOC_MTPA_FWC_FF_U.Throttle_input.Throttle_Inst_Voltage <=
      FOC_MTPA_FWC_FF_U.Throttle_input.Min_Throttle_Voltage));

  /* Chart: '<S161>/FNR_switching' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion'
   *  Inport: '<Root>/Actual Speed_mech_rpm'
   *  Inport: '<Root>/Drive_State'
   *  Inport: '<Root>/RPM_min_limit'
   */
  if (FOC_MTPA_FWC_FF_DW.is_active_c1_FOC_MTPA_FWC_FF == 0) {
    FOC_MTPA_FWC_FF_DW.is_active_c1_FOC_MTPA_FWC_FF = 1U;
    FOC_MTPA_FWC_FF_DW.is_c1_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Initial;

    /* Outport: '<Root>/Throttle_en' */
    FOC_MTPA_FWC_FF_Y.Throttle_en = 0.0;
    FOC_MTPA_FWC_FF_Y.Throttle_State = Neutral;
    FOC_MTPA_FWC_FF_B.Iq_ref = 0.0F;
    FOC_MTPA_FWC_FF_B.Id_ref = 0.0F;
  } else {
    switch (FOC_MTPA_FWC_FF_DW.is_c1_FOC_MTPA_FWC_FF) {
     case FOC_MTPA_FWC_FF_IN_Forward:
      /* Outport: '<Root>/Throttle_en' */
      FOC_MTPA_FWC_FF_Y.Throttle_en = 1.0;
      FOC_MTPA_FWC_FF_Y.Throttle_State = Forward;
      if (!FOC_MTPA_FWC_FF_Y.Throttle_error) {
        FOC_MTPA_FWC_FF_DW.durationCounter_1 = 0U;
      }

      if (FOC_MTPA_FWC_FF_DW.durationCounter_1 > 1000U) {
        FOC_MTPA_FWC_FF_DW.is_c1_FOC_MTPA_FWC_FF =
          FOC_MTPA_FWC__IN_Throttle_error;

        /* Outport: '<Root>/Throttle_en' */
        FOC_MTPA_FWC_FF_Y.Throttle_en = 0.0;
        FOC_MTPA_FWC_FF_Y.Throttle_State = Throttle_Error;
        FOC_MTPA_FWC_FF_B.Iq_ref = 0.0F;
        FOC_MTPA_FWC_FF_B.Id_ref = 0.0F;
      } else if (FOC_MTPA_FWC_FF_U.Drive_State == 2.0F) {
        FOC_MTPA_FWC_FF_DW.is_c1_FOC_MTPA_FWC_FF =
          FOC_MTPA__IN_Invalid_transition;

        /* Outport: '<Root>/Throttle_en' */
        FOC_MTPA_FWC_FF_Y.Throttle_en = 0.0;
        FOC_MTPA_FWC_FF_Y.Throttle_State = Neutral;
        FOC_MTPA_FWC_FF_B.Iq_ref = 0.0F;
        FOC_MTPA_FWC_FF_B.Id_ref = 0.0F;
      } else if (FOC_MTPA_FWC_FF_U.Drive_State == 3.0F) {
        FOC_MTPA_FWC_FF_DW.is_c1_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Neutral;

        /* Outport: '<Root>/Throttle_en' */
        FOC_MTPA_FWC_FF_Y.Throttle_en = 0.0;
        FOC_MTPA_FWC_FF_Y.Throttle_State = Neutral;
        FOC_MTPA_FWC_FF_B.Iq_ref = 0.0F;
        FOC_MTPA_FWC_FF_B.Id_ref = 0.0F;
      } else {
        FOC_MTPA_FWC_FF_B.Iq_ref = FOC_MTPA_FWC_FF_B.Merge[1];
        FOC_MTPA_FWC_FF_B.Id_ref = FOC_MTPA_FWC_FF_B.Merge[0];
      }
      break;

     case FOC_MTPA_FWC_FF_IN_Initial:
      /* Outport: '<Root>/Throttle_en' */
      FOC_MTPA_FWC_FF_Y.Throttle_en = 0.0;
      FOC_MTPA_FWC_FF_Y.Throttle_State = Neutral;
      if (FOC_MTPA_FWC_FF_U.Drive_State == 3.0F) {
        FOC_MTPA_FWC_FF_DW.is_c1_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Neutral;
        FOC_MTPA_FWC_FF_Y.Throttle_State = Neutral;
        FOC_MTPA_FWC_FF_B.Iq_ref = 0.0F;
        FOC_MTPA_FWC_FF_B.Id_ref = 0.0F;
      } else {
        tmp = !FOC_MTPA_FWC_FF_Y.Throttle_error;
        if ((FOC_MTPA_FWC_FF_U.Drive_State == 2.0F) && ((float)
             FOC_MTPA_FWC_FF_U.MtrSpd <= FOC_MTPA_FWC_FF_U.RPM_min_limit) && tmp)
        {
          FOC_MTPA_FWC_FF_DW.durationCounter_1_n = 0U;
          FOC_MTPA_FWC_FF_DW.is_c1_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Reverse;

          /* Outport: '<Root>/Throttle_en' */
          FOC_MTPA_FWC_FF_Y.Throttle_en = 1.0;
          FOC_MTPA_FWC_FF_Y.Throttle_State = Reverse;
        } else if ((FOC_MTPA_FWC_FF_U.Drive_State == 1.0F) && ((float)
                    FOC_MTPA_FWC_FF_U.MtrSpd <= FOC_MTPA_FWC_FF_U.RPM_min_limit)
                   && tmp) {
          FOC_MTPA_FWC_FF_DW.durationCounter_1 = 0U;
          FOC_MTPA_FWC_FF_DW.is_c1_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Forward;

          /* Outport: '<Root>/Throttle_en' */
          FOC_MTPA_FWC_FF_Y.Throttle_en = 1.0;
          FOC_MTPA_FWC_FF_Y.Throttle_State = Forward;
        }
      }
      break;

     case FOC_MTPA__IN_Invalid_transition:
      /* Outport: '<Root>/Throttle_en' */
      FOC_MTPA_FWC_FF_Y.Throttle_en = 0.0;
      FOC_MTPA_FWC_FF_Y.Throttle_State = Neutral;
      if (FOC_MTPA_FWC_FF_U.Drive_State == 3.0F) {
        FOC_MTPA_FWC_FF_DW.is_c1_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Neutral;
        FOC_MTPA_FWC_FF_Y.Throttle_State = Neutral;
        FOC_MTPA_FWC_FF_B.Iq_ref = 0.0F;
        FOC_MTPA_FWC_FF_B.Id_ref = 0.0F;
      }
      break;

     case FOC_MTPA_FWC_FF_IN_Neutral:
      /* Outport: '<Root>/Throttle_en' */
      FOC_MTPA_FWC_FF_Y.Throttle_en = 0.0;
      FOC_MTPA_FWC_FF_Y.Throttle_State = Neutral;
      if (((FOC_MTPA_FWC_FF_U.Drive_State == 1.0F) &&
           FOC_MTPA_FWC_FF_Y.Throttle_error) || ((FOC_MTPA_FWC_FF_U.Drive_State ==
            2.0F) && FOC_MTPA_FWC_FF_Y.Throttle_error)) {
        FOC_MTPA_FWC_FF_DW.is_c1_FOC_MTPA_FWC_FF =
          FOC_MTPA_FWC__IN_Throttle_error;
        FOC_MTPA_FWC_FF_Y.Throttle_State = Throttle_Error;
        FOC_MTPA_FWC_FF_B.Iq_ref = 0.0F;
        FOC_MTPA_FWC_FF_B.Id_ref = 0.0F;
      } else {
        tmp = !FOC_MTPA_FWC_FF_Y.Throttle_error;
        if ((FOC_MTPA_FWC_FF_U.Drive_State == 2.0F) && ((float)
             FOC_MTPA_FWC_FF_U.MtrSpd <= FOC_MTPA_FWC_FF_U.RPM_min_limit) && tmp)
        {
          FOC_MTPA_FWC_FF_DW.durationCounter_1_n = 0U;
          FOC_MTPA_FWC_FF_DW.is_c1_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Reverse;

          /* Outport: '<Root>/Throttle_en' */
          FOC_MTPA_FWC_FF_Y.Throttle_en = 1.0;
          FOC_MTPA_FWC_FF_Y.Throttle_State = Reverse;
        } else if ((FOC_MTPA_FWC_FF_U.Drive_State == 1.0F) && ((float)
                    FOC_MTPA_FWC_FF_U.MtrSpd <= FOC_MTPA_FWC_FF_U.RPM_min_limit)
                   && tmp) {
          FOC_MTPA_FWC_FF_DW.durationCounter_1 = 0U;
          FOC_MTPA_FWC_FF_DW.is_c1_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Forward;

          /* Outport: '<Root>/Throttle_en' */
          FOC_MTPA_FWC_FF_Y.Throttle_en = 1.0;
          FOC_MTPA_FWC_FF_Y.Throttle_State = Forward;
        }
      }
      break;

     case FOC_MTPA_FWC_FF_IN_Reverse:
      /* Outport: '<Root>/Throttle_en' */
      FOC_MTPA_FWC_FF_Y.Throttle_en = 1.0;
      FOC_MTPA_FWC_FF_Y.Throttle_State = Reverse;
      if (!FOC_MTPA_FWC_FF_Y.Throttle_error) {
        FOC_MTPA_FWC_FF_DW.durationCounter_1_n = 0U;
      }

      if (FOC_MTPA_FWC_FF_DW.durationCounter_1_n > 1000U) {
        FOC_MTPA_FWC_FF_DW.is_c1_FOC_MTPA_FWC_FF =
          FOC_MTPA_FWC__IN_Throttle_error;

        /* Outport: '<Root>/Throttle_en' */
        FOC_MTPA_FWC_FF_Y.Throttle_en = 0.0;
        FOC_MTPA_FWC_FF_Y.Throttle_State = Throttle_Error;
        FOC_MTPA_FWC_FF_B.Iq_ref = 0.0F;
        FOC_MTPA_FWC_FF_B.Id_ref = 0.0F;
      } else if (FOC_MTPA_FWC_FF_U.Drive_State == 3.0F) {
        FOC_MTPA_FWC_FF_DW.is_c1_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Neutral;

        /* Outport: '<Root>/Throttle_en' */
        FOC_MTPA_FWC_FF_Y.Throttle_en = 0.0;
        FOC_MTPA_FWC_FF_Y.Throttle_State = Neutral;
        FOC_MTPA_FWC_FF_B.Iq_ref = 0.0F;
        FOC_MTPA_FWC_FF_B.Id_ref = 0.0F;
      } else if (FOC_MTPA_FWC_FF_U.Drive_State == 1.0F) {
        FOC_MTPA_FWC_FF_DW.is_c1_FOC_MTPA_FWC_FF =
          FOC_MTPA__IN_Invalid_transition;

        /* Outport: '<Root>/Throttle_en' */
        FOC_MTPA_FWC_FF_Y.Throttle_en = 0.0;
        FOC_MTPA_FWC_FF_Y.Throttle_State = Neutral;
        FOC_MTPA_FWC_FF_B.Iq_ref = 0.0F;
        FOC_MTPA_FWC_FF_B.Id_ref = 0.0F;
      } else {
        FOC_MTPA_FWC_FF_B.Iq_ref = -FOC_MTPA_FWC_FF_B.Merge[1];
        FOC_MTPA_FWC_FF_B.Id_ref = FOC_MTPA_FWC_FF_B.Merge[0];
      }
      break;

     default:
      /* Outport: '<Root>/Throttle_en' */
      /* case IN_Throttle_error: */
      FOC_MTPA_FWC_FF_Y.Throttle_en = 0.0;
      FOC_MTPA_FWC_FF_Y.Throttle_State = Throttle_Error;
      if ((FOC_MTPA_FWC_FF_U.Drive_State == 3.0F) && ((float)
           FOC_MTPA_FWC_FF_U.MtrSpd <= FOC_MTPA_FWC_FF_U.RPM_min_limit) &&
          (!FOC_MTPA_FWC_FF_Y.Throttle_error)) {
        FOC_MTPA_FWC_FF_DW.is_c1_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Neutral;
        FOC_MTPA_FWC_FF_Y.Throttle_State = Neutral;
        FOC_MTPA_FWC_FF_B.Iq_ref = 0.0F;
        FOC_MTPA_FWC_FF_B.Id_ref = 0.0F;
      }
      break;
    }
  }

  if (FOC_MTPA_FWC_FF_Y.Throttle_error) {
    FOC_MTPA_FWC_FF_DW.durationCounter_1++;
    FOC_MTPA_FWC_FF_DW.durationCounter_1_n++;
  } else {
    FOC_MTPA_FWC_FF_DW.durationCounter_1 = 0U;
    FOC_MTPA_FWC_FF_DW.durationCounter_1_n = 0U;
  }

  /* End of Chart: '<S161>/FNR_switching' */

  /* Delay: '<S156>/Delay' */
  if (FOC_MTPA_FWC_FF_DW.icLoad_p) {
    /* Sum: '<S156>/Difference Inputs2'
     *
     * Block description for '<S156>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_MTPA_FWC_FF_DW.Delay_DSTATE_h = FOC_MTPA_FWC_FF_B.Id_ref;
  }

  /* Product: '<S156>/delta fall limit' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  Product: '<S156>/delta rise limit'
   *  SampleTimeMath: '<S156>/sample time'
   *
   * About '<S156>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  FOC_MTPA_FWC_FF_Y.Id_ref_final = FOC_MTPA_FWC_FF_U.Rate_limiter.Id_ramp_up *
    0.0001F;

  /* Sum: '<S156>/Difference Inputs1' incorporates:
   *  Delay: '<S156>/Delay'
   *
   * Block description for '<S156>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_UkYk1 = FOC_MTPA_FWC_FF_B.Id_ref - FOC_MTPA_FWC_FF_DW.Delay_DSTATE_h;

  /* Switch: '<S169>/Switch2' incorporates:
   *  RelationalOperator: '<S169>/LowerRelop1'
   */
  if (!(rtb_UkYk1 > FOC_MTPA_FWC_FF_Y.Id_ref_final)) {
    /* Product: '<S156>/delta fall limit' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  SampleTimeMath: '<S156>/sample time'
     *
     * About '<S156>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    FOC_MTPA_FWC_FF_Y.Id_ref_final = 0.0001F *
      FOC_MTPA_FWC_FF_U.Rate_limiter.Id_ramp_down;

    /* Switch: '<S169>/Switch' incorporates:
     *  RelationalOperator: '<S169>/UpperRelop'
     */
    if (!(rtb_UkYk1 < FOC_MTPA_FWC_FF_Y.Id_ref_final)) {
      /* Product: '<S156>/delta fall limit' */
      FOC_MTPA_FWC_FF_Y.Id_ref_final = rtb_UkYk1;
    }

    /* End of Switch: '<S169>/Switch' */
  }

  /* End of Switch: '<S169>/Switch2' */

  /* Sum: '<S156>/Difference Inputs2' incorporates:
   *  Delay: '<S156>/Delay'
   *
   * Block description for '<S156>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_MTPA_FWC_FF_DW.Delay_DSTATE_h += FOC_MTPA_FWC_FF_Y.Id_ref_final;

  /* Switch: '<S158>/Switch2' incorporates:
   *  Inport: '<Root>/Id_Iq_MTPA_limit'
   *  RelationalOperator: '<S158>/LowerRelop1'
   *  RelationalOperator: '<S158>/UpperRelop'
   *  Switch: '<S158>/Switch'
   */
  if (FOC_MTPA_FWC_FF_DW.Delay_DSTATE_h >
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_up_limit) {
    /* Product: '<S156>/delta fall limit' */
    FOC_MTPA_FWC_FF_Y.Id_ref_final =
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_up_limit;
  } else if (FOC_MTPA_FWC_FF_DW.Delay_DSTATE_h <
             FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_low_limit) {
    /* Product: '<S156>/delta fall limit' incorporates:
     *  Switch: '<S158>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Id_ref_final =
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_low_limit;
  } else {
    /* Product: '<S156>/delta fall limit' incorporates:
     *  Switch: '<S158>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Id_ref_final = FOC_MTPA_FWC_FF_DW.Delay_DSTATE_h;
  }

  /* End of Switch: '<S158>/Switch2' */

  /* Outputs for Atomic SubSystem: '<S14>/Two phase CRL wrap' */
  /* Gain: '<S15>/one_by_sqrt3' incorporates:
   *  Inport: '<Root>/Phase Current'
   *  Sum: '<S15>/a_plus_2b'
   */
  rtb_sum_Ds = ((FOC_MTPA_FWC_FF_U.PhaseCurrent[0] +
                 FOC_MTPA_FWC_FF_U.PhaseCurrent[1]) +
                FOC_MTPA_FWC_FF_U.PhaseCurrent[1]) * 0.57735026918962584;

  /* End of Outputs for SubSystem: '<S14>/Two phase CRL wrap' */

  /* Trigonometry: '<S4>/Trigonometric Function' incorporates:
   *  Inport: '<Root>/angle'
   *  Trigonometry: '<S6>/Trigonometric Function1'
   */
  rtb_TrigonometricFunction_tmp = sinf(FOC_MTPA_FWC_FF_U.MtrElcPos);

  /* Trigonometry: '<S4>/Trigonometric Function1' incorporates:
   *  Inport: '<Root>/angle'
   *  Trigonometry: '<S6>/Trigonometric Function'
   */
  rtb_TrigonometricFunction1_tmp = cosf(FOC_MTPA_FWC_FF_U.MtrElcPos);

  /* Outputs for Atomic SubSystem: '<S13>/Two inputs CRL' */
  /* Outputs for Atomic SubSystem: '<S14>/Two phase CRL wrap' */
  /* AlgorithmDescriptorDelegate generated from: '<S22>/a16' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S15>/a16'
   *  Inport: '<Root>/Phase Current'
   *  Product: '<S22>/acos'
   *  Product: '<S22>/bsin'
   *  Sum: '<S22>/sum_Ds'
   *  Switch: '<S23>/Switch'
   *  Trigonometry: '<S4>/Trigonometric Function'
   *  Trigonometry: '<S4>/Trigonometric Function1'
   */
  FOC_MTPA_FWC_FF_Y.Id = (float)(FOC_MTPA_FWC_FF_U.PhaseCurrent[0] *
    rtb_TrigonometricFunction1_tmp + rtb_sum_Ds * rtb_TrigonometricFunction_tmp);

  /* AlgorithmDescriptorDelegate generated from: '<S22>/a16' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S15>/a16'
   *  Inport: '<Root>/Phase Current'
   *  Product: '<S22>/asin'
   *  Product: '<S22>/bcos'
   *  Sum: '<S22>/sum_Qs'
   *  Switch: '<S23>/Switch'
   *  Trigonometry: '<S4>/Trigonometric Function'
   *  Trigonometry: '<S4>/Trigonometric Function1'
   */
  FOC_MTPA_FWC_FF_Y.Iq = (float)(rtb_sum_Ds * rtb_TrigonometricFunction1_tmp -
    FOC_MTPA_FWC_FF_U.PhaseCurrent[0] * rtb_TrigonometricFunction_tmp);

  /* End of Outputs for SubSystem: '<S14>/Two phase CRL wrap' */
  /* End of Outputs for SubSystem: '<S13>/Two inputs CRL' */

  /* Sum: '<S18>/Add1' incorporates:
   *  Constant: '<S11>/One'
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   *  Product: '<S18>/Product'
   *  Product: '<S18>/Product1'
   *  Sum: '<S11>/Sum'
   *  Switch: '<S11>/Switch1'
   *  UnitDelay: '<S18>/Unit Delay'
   */
  FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE = (1.0F -
    FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Id_Filter_coefficient) *
    FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE + FOC_MTPA_FWC_FF_Y.Id *
    FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Id_Filter_coefficient;

  /* Switch: '<S4>/Switch' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   */
  if (FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Id_Filter_switch > 0.0F) {
    /* AlgorithmDescriptorDelegate generated from: '<S22>/a16' incorporates:
     *  UnitDelay: '<S18>/Unit Delay'
     */
    FOC_MTPA_FWC_FF_Y.Id = FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE;
  }

  /* End of Switch: '<S4>/Switch' */

  /* Sum: '<S28>/Sum3' */
  FOC_MTPA_FWC_FF_Y.Id_error = FOC_MTPA_FWC_FF_Y.Id_ref_final -
    FOC_MTPA_FWC_FF_Y.Id;

  /* Product: '<S126>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S118>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S116>/DProd Out'
   *  Sum: '<S118>/SumD'
   */
  rtb_UkYk1 = (FOC_MTPA_FWC_FF_Y.Id_error *
               FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Kd_flux_PID_MTPA -
               FOC_MTPA_FWC_FF_DW.Filter_DSTATE) *
    FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Filter_flux_PID_MTPA;

  /* Sum: '<S133>/Sum' incorporates:
   *  DiscreteIntegrator: '<S123>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S128>/PProd Out'
   */
  rtb_V_qo = (FOC_MTPA_FWC_FF_Y.Id_error *
              FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA +
              FOC_MTPA_FWC_FF_DW.Integrator_DSTATE) + rtb_UkYk1;

  /* Switch: '<S131>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S131>/LowerRelop1'
   *  RelationalOperator: '<S131>/UpperRelop'
   *  Switch: '<S131>/Switch'
   */
  if (rtb_V_qo > FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_flux_PID) {
    /* Switch: '<S131>/Switch2' */
    FOC_MTPA_FWC_FF_Y.Vd_PID = FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_flux_PID;
  } else if (rtb_V_qo < FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_flux_PID) {
    /* Switch: '<S131>/Switch2' incorporates:
     *  Switch: '<S131>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Vd_PID = FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_flux_PID;
  } else {
    /* Switch: '<S131>/Switch2' incorporates:
     *  Switch: '<S131>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Vd_PID = rtb_V_qo;
  }

  /* End of Switch: '<S131>/Switch2' */

  /* Gain: '<S5>/Gain' incorporates:
   *  Inport: '<Root>/Bus_Voltage'
   */
  rtb_Gain = 0.577350259F * FOC_MTPA_FWC_FF_U.BusVoltage_V;

  /* Delay: '<S157>/Delay' */
  if (FOC_MTPA_FWC_FF_DW.icLoad_l) {
    /* Sum: '<S157>/Difference Inputs2'
     *
     * Block description for '<S157>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_MTPA_FWC_FF_DW.Delay_DSTATE_b = FOC_MTPA_FWC_FF_B.Iq_ref;
  }

  /* Product: '<S157>/delta fall limit' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  Product: '<S157>/delta rise limit'
   *  SampleTimeMath: '<S157>/sample time'
   *
   * About '<S157>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  FOC_MTPA_FWC_FF_Y.Iq_ref_final = FOC_MTPA_FWC_FF_U.Rate_limiter.Iq_ramp_up *
    0.0001F;

  /* Sum: '<S157>/Difference Inputs1' incorporates:
   *  Delay: '<S157>/Delay'
   *
   * Block description for '<S157>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_UkYk1_k = FOC_MTPA_FWC_FF_B.Iq_ref - FOC_MTPA_FWC_FF_DW.Delay_DSTATE_b;

  /* Switch: '<S170>/Switch2' incorporates:
   *  RelationalOperator: '<S170>/LowerRelop1'
   */
  if (!(rtb_UkYk1_k > FOC_MTPA_FWC_FF_Y.Iq_ref_final)) {
    /* Product: '<S157>/delta fall limit' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  SampleTimeMath: '<S157>/sample time'
     *
     * About '<S157>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    FOC_MTPA_FWC_FF_Y.Iq_ref_final = 0.0001F *
      FOC_MTPA_FWC_FF_U.Rate_limiter.Iq_ramp_down;

    /* Switch: '<S170>/Switch' incorporates:
     *  RelationalOperator: '<S170>/UpperRelop'
     */
    if (!(rtb_UkYk1_k < FOC_MTPA_FWC_FF_Y.Iq_ref_final)) {
      /* Product: '<S157>/delta fall limit' */
      FOC_MTPA_FWC_FF_Y.Iq_ref_final = rtb_UkYk1_k;
    }

    /* End of Switch: '<S170>/Switch' */
  }

  /* End of Switch: '<S170>/Switch2' */

  /* Sum: '<S157>/Difference Inputs2' incorporates:
   *  Delay: '<S157>/Delay'
   *
   * Block description for '<S157>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_MTPA_FWC_FF_DW.Delay_DSTATE_b += FOC_MTPA_FWC_FF_Y.Iq_ref_final;

  /* Switch: '<S159>/Switch2' incorporates:
   *  Inport: '<Root>/Id_Iq_MTPA_limit'
   *  RelationalOperator: '<S159>/LowerRelop1'
   *  RelationalOperator: '<S159>/UpperRelop'
   *  Switch: '<S159>/Switch'
   */
  if (FOC_MTPA_FWC_FF_DW.Delay_DSTATE_b >
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_up_limit) {
    /* Product: '<S157>/delta fall limit' */
    FOC_MTPA_FWC_FF_Y.Iq_ref_final =
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_up_limit;
  } else if (FOC_MTPA_FWC_FF_DW.Delay_DSTATE_b <
             FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_low_limit) {
    /* Product: '<S157>/delta fall limit' incorporates:
     *  Switch: '<S159>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Iq_ref_final =
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_low_limit;
  } else {
    /* Product: '<S157>/delta fall limit' incorporates:
     *  Switch: '<S159>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Iq_ref_final = FOC_MTPA_FWC_FF_DW.Delay_DSTATE_b;
  }

  /* End of Switch: '<S159>/Switch2' */

  /* Sum: '<S27>/Sum2' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion'
   *  Gain: '<S30>/wm_pu2si_mech2elec'
   *  Inport: '<Root>/Actual Speed_mech_rpm'
   */
  FOC_MTPA_FWC_FF_Y.Iq_error = POLEPAIRS * (float)FOC_MTPA_FWC_FF_U.MtrSpd;

  /* Gain: '<S30>/NegSign' incorporates:
   *  Inport: '<Root>/Motor_Parameters'
   *  Product: '<S30>/prod1'
   *  Switch: '<S31>/Switch1'
   */
  rtb_UkYk1_k = -(FOC_MTPA_FWC_FF_U.Motor_Parameters.Lq *
                  FOC_MTPA_FWC_FF_Y.Iq_ref_final * FOC_MTPA_FWC_FF_Y.Iq_error);

  /* Switch: '<S32>/Switch2' incorporates:
   *  RelationalOperator: '<S32>/LowerRelop1'
   *  RelationalOperator: '<S32>/UpperRelop'
   *  Switch: '<S30>/Switch'
   *  Switch: '<S32>/Switch'
   *  UnaryMinus: '<S30>/Unary Minus'
   */
  if (rtb_UkYk1_k > rtb_Gain) {
    rtb_UkYk1_k = rtb_Gain;
  } else if (rtb_UkYk1_k < -rtb_Gain) {
    /* Switch: '<S32>/Switch' incorporates:
     *  UnaryMinus: '<S30>/Unary Minus'
     */
    rtb_UkYk1_k = -rtb_Gain;
  }

  /* Sum: '<S5>/Add' incorporates:
   *  Switch: '<S32>/Switch2'
   */
  FOC_MTPA_FWC_FF_Y.Vd = FOC_MTPA_FWC_FF_Y.Vd_PID + rtb_UkYk1_k;

  /* Switch: '<S25>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S25>/LowerRelop1'
   *  RelationalOperator: '<S25>/UpperRelop'
   *  Switch: '<S25>/Switch'
   */
  if (FOC_MTPA_FWC_FF_Y.Vd > FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_flux_PID) {
    /* Sum: '<S5>/Add' */
    FOC_MTPA_FWC_FF_Y.Vd = FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_flux_PID;
  } else if (FOC_MTPA_FWC_FF_Y.Vd <
             FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_flux_PID) {
    /* Sum: '<S5>/Add' incorporates:
     *  Switch: '<S25>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Vd = FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_flux_PID;
  }

  /* End of Switch: '<S25>/Switch2' */

  /* Product: '<S30>/prod2' incorporates:
   *  Inport: '<Root>/Motor_Parameters'
   *  Product: '<S30>/prod3'
   *  Sum: '<S30>/add1'
   *  Switch: '<S31>/Switch'
   *  Switch: '<S31>/Switch2'
   */
  rtb_UkYk1_k = (FOC_MTPA_FWC_FF_U.Motor_Parameters.Ld *
                 FOC_MTPA_FWC_FF_Y.Id_ref_final +
                 FOC_MTPA_FWC_FF_U.Motor_Parameters.Lambda) *
    FOC_MTPA_FWC_FF_Y.Iq_error;

  /* Switch: '<S33>/Switch2' incorporates:
   *  RelationalOperator: '<S33>/LowerRelop1'
   *  Switch: '<S30>/Switch'
   */
  if (!(rtb_UkYk1_k > rtb_Gain)) {
    /* Switch: '<S33>/Switch' incorporates:
     *  RelationalOperator: '<S33>/UpperRelop'
     *  UnaryMinus: '<S30>/Unary Minus'
     */
    if (rtb_UkYk1_k < -rtb_Gain) {
      rtb_Gain = -rtb_Gain;
    } else {
      rtb_Gain = rtb_UkYk1_k;
    }

    /* End of Switch: '<S33>/Switch' */
  }

  /* End of Switch: '<S33>/Switch2' */

  /* Sum: '<S21>/Add1' incorporates:
   *  Constant: '<S12>/One'
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   *  Product: '<S21>/Product'
   *  Product: '<S21>/Product1'
   *  Sum: '<S12>/Sum'
   *  Switch: '<S12>/Switch1'
   *  UnitDelay: '<S21>/Unit Delay'
   */
  FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE_f = (1.0F -
    FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Iq_Filter_coefficient) *
    FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE_f + FOC_MTPA_FWC_FF_Y.Iq *
    FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Iq_Filter_coefficient;

  /* Switch: '<S4>/Switch1' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   */
  if (FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Iq_Filter_switch > 0.0F) {
    /* AlgorithmDescriptorDelegate generated from: '<S22>/a16' incorporates:
     *  UnitDelay: '<S21>/Unit Delay'
     */
    FOC_MTPA_FWC_FF_Y.Iq = FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE_f;
  }

  /* End of Switch: '<S4>/Switch1' */

  /* Sum: '<S27>/Sum2' */
  FOC_MTPA_FWC_FF_Y.Iq_error = FOC_MTPA_FWC_FF_Y.Iq_ref_final -
    FOC_MTPA_FWC_FF_Y.Iq;

  /* Product: '<S72>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S64>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S62>/DProd Out'
   *  Sum: '<S64>/SumD'
   */
  rtb_UkYk1_k = (FOC_MTPA_FWC_FF_Y.Iq_error *
                 FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA -
                 FOC_MTPA_FWC_FF_DW.Filter_DSTATE_d) *
    FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Filter_torque_PID_MTPA;

  /* Sum: '<S79>/Sum' incorporates:
   *  DiscreteIntegrator: '<S69>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S74>/PProd Out'
   */
  rtb_Sum_f = (FOC_MTPA_FWC_FF_Y.Iq_error *
               FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA +
               FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_h) + rtb_UkYk1_k;

  /* Switch: '<S77>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S77>/LowerRelop1'
   *  RelationalOperator: '<S77>/UpperRelop'
   *  Switch: '<S77>/Switch'
   */
  if (rtb_Sum_f > FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_torque_PID) {
    /* Switch: '<S77>/Switch2' */
    FOC_MTPA_FWC_FF_Y.Vq_PID = FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_torque_PID;
  } else if (rtb_Sum_f < FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_torque_PID) {
    /* Switch: '<S77>/Switch2' incorporates:
     *  Switch: '<S77>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Vq_PID = FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_torque_PID;
  } else {
    /* Switch: '<S77>/Switch2' incorporates:
     *  Switch: '<S77>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Vq_PID = rtb_Sum_f;
  }

  /* End of Switch: '<S77>/Switch2' */

  /* Sum: '<S5>/Add1' */
  FOC_MTPA_FWC_FF_Y.Vq = rtb_Gain + FOC_MTPA_FWC_FF_Y.Vq_PID;

  /* Switch: '<S26>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S26>/LowerRelop1'
   *  RelationalOperator: '<S26>/UpperRelop'
   *  Switch: '<S26>/Switch'
   */
  if (FOC_MTPA_FWC_FF_Y.Vq > FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_torque_PID) {
    /* Sum: '<S5>/Add1' */
    FOC_MTPA_FWC_FF_Y.Vq = FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_torque_PID;
  } else if (FOC_MTPA_FWC_FF_Y.Vq <
             FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_torque_PID) {
    /* Sum: '<S5>/Add1' incorporates:
     *  Switch: '<S26>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Vq = FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_torque_PID;
  }

  /* End of Switch: '<S26>/Switch2' */

  /* Outputs for Atomic SubSystem: '<S143>/Two inputs CRL' */
  /* Switch: '<S147>/Switch' incorporates:
   *  Product: '<S146>/dcos'
   *  Product: '<S146>/qsin'
   *  Sum: '<S146>/sum_alpha'
   */
  rtb_TmpSignalConversionAtMath_0 = (float)(FOC_MTPA_FWC_FF_Y.Vd *
    rtb_TrigonometricFunction1_tmp) - (float)(FOC_MTPA_FWC_FF_Y.Vq *
    rtb_TrigonometricFunction_tmp);

  /* Gain: '<S145>/one_by_two' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S146>/a16'
   */
  rtb_add_c = 0.5F * rtb_TmpSignalConversionAtMath_0;

  /* Gain: '<S145>/sqrt3_by_two' incorporates:
   *  Product: '<S146>/dsin'
   *  Product: '<S146>/qcos'
   *  Sum: '<S146>/sum_beta'
   */
  rtb_Gain = ((float)(FOC_MTPA_FWC_FF_Y.Vq * rtb_TrigonometricFunction1_tmp) +
              (float)(FOC_MTPA_FWC_FF_Y.Vd * rtb_TrigonometricFunction_tmp)) *
    0.866025388F;

  /* End of Outputs for SubSystem: '<S143>/Two inputs CRL' */

  /* Sum: '<S145>/add_b' */
  rtb_Add1_l = rtb_Gain - rtb_add_c;

  /* Sum: '<S145>/add_c' */
  rtb_add_c = (0.0F - rtb_add_c) - rtb_Gain;

  /* Outputs for Atomic SubSystem: '<S143>/Two inputs CRL' */
  /* Gain: '<S151>/one_by_two' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S146>/a16'
   *  MinMax: '<S151>/Max'
   *  MinMax: '<S151>/Min'
   *  Sum: '<S151>/Add'
   */
  rtb_Gain = (fmaxf(fmaxf(rtb_TmpSignalConversionAtMath_0, rtb_Add1_l),
                    rtb_add_c) + fminf(fminf(rtb_TmpSignalConversionAtMath_0,
    rtb_Add1_l), rtb_add_c)) * -0.5F;

  /* Outport: '<Root>/Va' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S146>/a16'
   *  Gain: '<S150>/Gain'
   *  Sum: '<S150>/Add3'
   */
  FOC_MTPA_FWC_FF_Y.Va = (rtb_TmpSignalConversionAtMath_0 + rtb_Gain) *
    1.15470052F;

  /* End of Outputs for SubSystem: '<S143>/Two inputs CRL' */

  /* Outport: '<Root>/Vb' incorporates:
   *  Gain: '<S150>/Gain'
   *  Sum: '<S150>/Add1'
   */
  FOC_MTPA_FWC_FF_Y.Vb = (rtb_Add1_l + rtb_Gain) * 1.15470052F;

  /* Outport: '<Root>/Vc' incorporates:
   *  Gain: '<S150>/Gain'
   *  Sum: '<S150>/Add2'
   */
  FOC_MTPA_FWC_FF_Y.Vc = (rtb_Gain + rtb_add_c) * 1.15470052F;

  /* DataTypeConversion: '<S1>/Data Type Conversion1' incorporates:
   *  Delay: '<S1>/Delay One Step'
   */
  FOC_MTPA_FWC_FF_DW.DelayOneStep_DSTATE = (float)
    FOC_MTPA_FWC_FF_Y.Throttle_State;

  /* Delay: '<S3>/Delay' incorporates:
   *  Constant: '<S3>/Constant'
   */
  if (FOC_MTPA_FWC_FF_DW.icLoad_k) {
    FOC_MTPA_FWC_FF_DW.Delay_DSTATE_c = 0.0F;
  }

  /* Switch: '<S1>/Switch' incorporates:
   *  Constant: '<S1>/Constant'
   *  Delay: '<S1>/Delay One Step'
   *  Inport: '<Root>/Ref_Speed_mech_rpm'
   */
  if (FOC_MTPA_FWC_FF_DW.DelayOneStep_DSTATE > 2.0F) {
    rtb_sum_Ds = 0.0;
  } else {
    rtb_sum_Ds = FOC_MTPA_FWC_FF_U.Ref_Speed_mech_rpm;
  }

  /* Sum: '<S3>/Difference Inputs1' incorporates:
   *  Delay: '<S3>/Delay'
   *  Switch: '<S1>/Switch'
   *
   * Block description for '<S3>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_add_c = (float)(rtb_sum_Ds - FOC_MTPA_FWC_FF_DW.Delay_DSTATE_c);

  /* Product: '<S3>/delta rise limit' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  SampleTimeMath: '<S3>/sample time'
   *
   * About '<S3>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_Gain = FOC_MTPA_FWC_FF_U.Rate_limiter.Ref_Speed_rate_up * 0.0001F;

  /* Switch: '<S228>/Switch2' incorporates:
   *  RelationalOperator: '<S228>/LowerRelop1'
   */
  if (!(rtb_add_c > rtb_Gain)) {
    /* Switch: '<S1>/Switch1' incorporates:
     *  Delay: '<S1>/Delay One Step'
     *  Inport: '<Root>/Rate_limiter'
     */
    if (FOC_MTPA_FWC_FF_DW.DelayOneStep_DSTATE > 2.0F) {
      rtb_Gain = FOC_MTPA_FWC_FF_U.Rate_limiter.Ref_Speed_rate_down_neutral;
    } else {
      rtb_Gain = FOC_MTPA_FWC_FF_U.Rate_limiter.Ref_Speed_rate_down;
    }

    /* Product: '<S3>/delta fall limit' incorporates:
     *  SampleTimeMath: '<S3>/sample time'
     *  Switch: '<S1>/Switch1'
     *
     * About '<S3>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_Gain *= 0.0001F;

    /* Switch: '<S228>/Switch' incorporates:
     *  RelationalOperator: '<S228>/UpperRelop'
     */
    if (!(rtb_add_c < rtb_Gain)) {
      rtb_Gain = rtb_add_c;
    }

    /* End of Switch: '<S228>/Switch' */
  }

  /* End of Switch: '<S228>/Switch2' */

  /* Sum: '<S3>/Difference Inputs2' incorporates:
   *  Delay: '<S3>/Delay'
   *
   * Block description for '<S3>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_MTPA_FWC_FF_Y.Ref_speed_out_RPM = rtb_Gain +
    FOC_MTPA_FWC_FF_DW.Delay_DSTATE_c;

  /* Outport: '<Root>/Speed_error' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion'
   *  Gain: '<S1>/rpm to Rad//sec'
   *  Inport: '<Root>/Actual Speed_mech_rpm'
   *  Sum: '<S8>/Subtract'
   */
  FOC_MTPA_FWC_FF_Y.Speed_error = 0.104719758F *
    FOC_MTPA_FWC_FF_Y.Ref_speed_out_RPM - (float)FOC_MTPA_FWC_FF_U.MtrSpd;

  /* Outport: '<Root>/MTPA_FWC_condition' */
  FOC_MTPA_FWC_FF_Y.MTPA_FWC_condition = rtb_State;

  /* Update for Delay: '<S9>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad = false;
  FOC_MTPA_FWC_FF_DW.Delay_DSTATE = FOC_MTPA_FWC_FF_Y.T_gen;

  /* Update for Delay: '<S156>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad_p = false;

  /* Update for DiscreteIntegrator: '<S123>/Integrator' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S120>/IProd Out'
   *  Sum: '<S115>/SumI2'
   *  Sum: '<S115>/SumI4'
   *  Sum: '<S135>/SumI3'
   *  Sum: '<S136>/SumI1'
   */
  FOC_MTPA_FWC_FF_DW.Integrator_DSTATE += ((FOC_MTPA_FWC_FF_Y.Id_error *
    FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Ki_flux_PID_MTPA +
    (FOC_MTPA_FWC_FF_Y.Vd_PID - FOC_MTPA_FWC_FF_Y.Vd_PID)) +
    (FOC_MTPA_FWC_FF_Y.Vd_PID - rtb_V_qo)) * 0.0001F;
  if (FOC_MTPA_FWC_FF_DW.Integrator_DSTATE > SVM_VOLTAGE_LIMIT) {
    FOC_MTPA_FWC_FF_DW.Integrator_DSTATE = SVM_VOLTAGE_LIMIT;
  } else if (FOC_MTPA_FWC_FF_DW.Integrator_DSTATE < -SVM_VOLTAGE_LIMIT) {
    FOC_MTPA_FWC_FF_DW.Integrator_DSTATE = -SVM_VOLTAGE_LIMIT;
  }

  /* End of Update for DiscreteIntegrator: '<S123>/Integrator' */

  /* Update for DiscreteIntegrator: '<S118>/Filter' */
  FOC_MTPA_FWC_FF_DW.Filter_DSTATE += 0.0001F * rtb_UkYk1;

  /* Update for Delay: '<S157>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad_l = false;

  /* Update for DiscreteIntegrator: '<S69>/Integrator' incorporates:
   *  Gain: '<S81>/Kt'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S66>/IProd Out'
   *  Sum: '<S61>/SumI2'
   *  Sum: '<S61>/SumI4'
   *  Sum: '<S81>/SumI3'
   *  Sum: '<S82>/SumI1'
   */
  FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_h += (((FOC_MTPA_FWC_FF_Y.Vq_PID -
    FOC_MTPA_FWC_FF_Y.Vq_PID) * -10.0F + FOC_MTPA_FWC_FF_Y.Iq_error *
    FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Ki_torque_PID_MTPA) +
    (FOC_MTPA_FWC_FF_Y.Vq_PID - rtb_Sum_f)) * 0.0001F;
  if (FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_h > SVM_VOLTAGE_LIMIT) {
    FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_h = SVM_VOLTAGE_LIMIT;
  } else if (FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_h < -SVM_VOLTAGE_LIMIT) {
    FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_h = -SVM_VOLTAGE_LIMIT;
  }

  /* End of Update for DiscreteIntegrator: '<S69>/Integrator' */

  /* Update for DiscreteIntegrator: '<S64>/Filter' */
  FOC_MTPA_FWC_FF_DW.Filter_DSTATE_d += 0.0001F * rtb_UkYk1_k;

  /* Update for Delay: '<S3>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad_k = false;
  FOC_MTPA_FWC_FF_DW.Delay_DSTATE_c = FOC_MTPA_FWC_FF_Y.Ref_speed_out_RPM;
}

/* Model step function for TID1 */
void FOC_MTPA_FWC_FF_step1(void)       /* Sample time: [0.001s, 0.0s] */
{
  float rtb_NProdOut_j;
  float rtb_Sum_o;

  /* Product: '<S211>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S203>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S201>/DProd Out'
   *  Sum: '<S203>/SumD'
   */
  rtb_NProdOut_j = (FOC_MTPA_FWC_FF_Y.Speed_error *
                    FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA
                    - FOC_MTPA_FWC_FF_DW.Filter_DSTATE_i) *
    FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Filter_speed_PID_MTPA;

  /* Sum: '<S218>/Sum' incorporates:
   *  DiscreteIntegrator: '<S208>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S213>/PProd Out'
   */
  rtb_Sum_o = (FOC_MTPA_FWC_FF_Y.Speed_error *
               FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA +
               FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_b) + rtb_NProdOut_j;

  /* Switch: '<S216>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S216>/LowerRelop1'
   *  RelationalOperator: '<S216>/UpperRelop'
   *  Switch: '<S216>/Switch'
   */
  if (rtb_Sum_o > FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_speed_PID_MTPA) {
    /* Switch: '<S216>/Switch2' */
    FOC_MTPA_FWC_FF_Y.Iq_gen =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_speed_PID_MTPA;
  } else if (rtb_Sum_o < FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_speed_PID_MTPA) {
    /* Switch: '<S216>/Switch2' incorporates:
     *  Switch: '<S216>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Iq_gen =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_speed_PID_MTPA;
  } else {
    /* Switch: '<S216>/Switch2' incorporates:
     *  Switch: '<S216>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Iq_gen = rtb_Sum_o;
  }

  /* End of Switch: '<S216>/Switch2' */

  /* RateTransition: '<S2>/Rate Transition' */
  FOC_MTPA_FWC_FF_DW.RateTransition_Buffer0 = FOC_MTPA_FWC_FF_Y.Iq_gen;

  /* Update for DiscreteIntegrator: '<S208>/Integrator' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S205>/IProd Out'
   *  Sum: '<S200>/SumI2'
   *  Sum: '<S200>/SumI4'
   *  Sum: '<S220>/SumI3'
   *  Sum: '<S221>/SumI1'
   */
  FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_b += ((FOC_MTPA_FWC_FF_Y.Speed_error *
    FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Ki_speed_PID_MTPA +
    (FOC_MTPA_FWC_FF_Y.Iq_gen - FOC_MTPA_FWC_FF_Y.Iq_gen)) +
    (FOC_MTPA_FWC_FF_Y.Iq_gen - rtb_Sum_o)) * 0.001F;
  if (FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_b > MOTOR_PEAK_AC) {
    FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_b = MOTOR_PEAK_AC;
  } else if (FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_b < -MOTOR_PEAK_AC) {
    FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_b = -MOTOR_PEAK_AC;
  }

  /* End of Update for DiscreteIntegrator: '<S208>/Integrator' */

  /* Update for DiscreteIntegrator: '<S203>/Filter' */
  FOC_MTPA_FWC_FF_DW.Filter_DSTATE_i += 0.001F * rtb_NProdOut_j;
}

/* Model initialize function */
void FOC_MTPA_FWC_FF_initialize(void)
{
  /* Registration code */

  /* external outputs */
  FOC_MTPA_FWC_FF_Y.Throttle_State = Forward;

  /* InitializeConditions for Delay: '<S9>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad = true;

  /* InitializeConditions for Delay: '<S1>/Delay One Step' */
  FOC_MTPA_FWC_FF_DW.DelayOneStep_DSTATE = 3.0F;

  /* InitializeConditions for Delay: '<S156>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad_p = true;

  /* InitializeConditions for Delay: '<S157>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad_l = true;

  /* InitializeConditions for Delay: '<S3>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad_k = true;

  /* SystemInitialize for IfAction SubSystem: '<S7>/If Action Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S162>/Discrete-Time Integrator' */
  FOC_MTPA_FWC_FF_DW.DiscreteTimeIntegrator_DSTATE = 1.0F;

  FOC_MTPA_FWC_FF_U.BusVoltage_V = OP_VOLTAGE;
  FOC_MTPA_FWC_FF_U.Iq_Torque_ratio = CURR_TORQUE_RATIO;
  FOC_MTPA_FWC_FF_U.Motor_Parameters.Pole_Pairs = POLEPAIRS;
  FOC_MTPA_FWC_FF_U.Motor_Parameters.Lambda = can_d.can_Lambda;
  FOC_MTPA_FWC_FF_U.Motor_Parameters.Ld = can_d.can_Ld;
  FOC_MTPA_FWC_FF_U.Motor_Parameters.Lq = can_d.can_Lq;
  FOC_MTPA_FWC_FF_U.Is_max = MOTOR_PEAK_AC;
  FOC_MTPA_FWC_FF_U.RPM_min_limit = MIN_RPM_CHANGE_LIM;

  /* Throttle Settings */
  FOC_MTPA_FWC_FF_U.Throttle_input.Max_Output_Value = SPORTS_MAX_SPEED;
  FOC_MTPA_FWC_FF_U.Throttle_input.Max_Throttle_Voltage = THR_MAX_VAL;
  FOC_MTPA_FWC_FF_U.Throttle_input.Min_Throttle_Voltage = THR_MIN_VAL;

  /* Id Iq Limits */
  FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_up_limit = 512.0f;
  FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_low_limit = -512.0f;
  FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_up_limit = 512.0f;
  FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_low_limit = -512.0f;
  
  /* Speed Ref Rate Limiter Settings */
  FOC_MTPA_FWC_FF_U.Rate_limiter.Ref_Speed_rate_up = 100.0f * 10000.0f;
  FOC_MTPA_FWC_FF_U.Rate_limiter.Ref_Speed_rate_down = -500.0f * 10000.0f;
  FOC_MTPA_FWC_FF_U.Rate_limiter.Ref_Speed_rate_down_neutral = -600.0f * 10000.0f;

  /* Rate Limiter Settings */
  FOC_MTPA_FWC_FF_U.Rate_limiter.Torque_gen_ramp_up = 5.0f * 10000.0f;
  FOC_MTPA_FWC_FF_U.Rate_limiter.Torque_gen_ramp_down = -5.0f * 10000.0f;
  FOC_MTPA_FWC_FF_U.Rate_limiter.Iq_ramp_up = 50.0f * 10000.0f;
  FOC_MTPA_FWC_FF_U.Rate_limiter.Iq_ramp_down = -50.0f * 10000.0f;
  FOC_MTPA_FWC_FF_U.Rate_limiter.Id_ramp_up = 50.0f * 10000.0f;
  FOC_MTPA_FWC_FF_U.Rate_limiter.Id_ramp_down = -50.0f * 10000.0f;

  /* Speed PID Values */
  FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_speed_PID_MTPA = can_d.canSpeed_PID.Output_Up_Limit;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_speed_PID_MTPA = can_d.canSpeed_PID.Output_Low_Limit;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA = can_d.canSpeed_PID.Kp;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Ki_speed_PID_MTPA = can_d.canSpeed_PID.Ki;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA = can_d.canSpeed_PID.Kd;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Filter_speed_PID_MTPA = can_d.canSpeed_PID.Kd_Filter;

  /* Iq PID Values */
  FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_torque_PID = can_d.canIq_PID.Output_Up_Limit;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_torque_PID = can_d.canIq_PID.Output_Low_Limit;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA = can_d.canIq_PID.Kp;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Ki_torque_PID_MTPA = can_d.canIq_PID.Ki;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA = can_d.canId_PID.Kd;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Filter_torque_PID_MTPA = can_d.canIq_PID.Kd_Filter;

  /* Id PID Values */
  FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_flux_PID = can_d.canId_PID.Output_Up_Limit;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_flux_PID = can_d.canId_PID.Output_Low_Limit;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA = can_d.canId_PID.Kp;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Ki_flux_PID_MTPA = can_d.canId_PID.Ki;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Kd_flux_PID_MTPA = can_d.canId_PID.Kd;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Filter_flux_PID_MTPA = can_d.canId_PID.Kd_Filter;

  /* IIR Filter Coefficients */
  FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Id_Filter_switch = 1.0f;
  FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Iq_Filter_switch = 1.0f;
  FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Id_Filter_coefficient = 0.9f;
  FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Iq_Filter_coefficient = 0.9f; 

  FOC_MTPA_FWC_FF_U.Speed_1_Torque_0 = 1.0f;
  FOC_MTPA_FWC_FF_U.RefTrq = 0.0f;

  /* End of SystemInitialize for SubSystem: '<S7>/If Action Subsystem1' */
}

/* Model terminate function */
void FOC_MTPA_FWC_FF_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
