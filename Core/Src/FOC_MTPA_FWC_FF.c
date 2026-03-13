/*
 * File: FOC_MTPA_FWC_FF.c
 *
 * Code generated for Simulink model 'FOC_MTPA_FWC_FF'.
 *
 * Model version                  : 18.318
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Tue Mar 10 17:52:30 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_MTPA_FWC_FF.h"
#include <stdint.h>
#include <math.h>

/* Named constants for Chart: '<S160>/Chart' */
#define FOC_MTPA_FWC_FF_IN_FWC         ((uint8_t)1U)
#define FOC_MTPA_FWC_FF_IN_MTPA        ((uint8_t)2U)

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

/* Model step function for TID0 */
void FOC_MTPA_FWC_FF_step0(void)       /* Sample time: [0.0001s, 0.0s] */
{
  float rtb_Add1_l;
  float rtb_Add_e;
  float rtb_IProdOut;
  float rtb_NProdOut_l;
  float rtb_Sum_h;
  float rtb_Switch_f_idx_0;
  float rtb_UkYk1;
  float rtb_VqFF_unsat;
  float rtb_Gain_j;
  int32_t rtb_State;
  bool guard1;
  bool guard2;

  /* Sum: '<S160>/Subtract' incorporates:
   *  Gain: '<S160>/Gain1'
   *  Inport: '<Root>/Bus_Voltage'
   *  Inport: '<Root>/Is_max'
   *  Inport: '<Root>/Rs'
   *  Product: '<S160>/Product4'
   */
  FOC_MTPA_FWC_FF_Y.V_max = 0.577350259F * FOC_MTPA_FWC_FF_U.BusVoltage_V -
    FOC_MTPA_FWC_FF_U.Is_max * FOC_MTPA_FWC_FF_U.Rs;

  /* Delay: '<S8>/Delay' */
  if (FOC_MTPA_FWC_FF_DW.icLoad) {
    FOC_MTPA_FWC_FF_DW.Delay_DSTATE = FOC_MTPA_FWC_FF_B.Switch2;
  }

  /* Product: '<S8>/delta fall limit' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  Product: '<S8>/delta rise limit'
   */
  FOC_MTPA_FWC_FF_Y.Id_error = FOC_MTPA_FWC_FF_U.Rate_limiter.Torque_gen_ramp_up
    * FOC_MTPA_FWC_FF_B.sampletime;

  /* Sum: '<S8>/Difference Inputs1' incorporates:
   *  Delay: '<S8>/Delay'
   *
   * Block description for '<S8>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_UkYk1 = FOC_MTPA_FWC_FF_B.Switch2 - FOC_MTPA_FWC_FF_DW.Delay_DSTATE;

  /* Switch: '<S220>/Switch2' incorporates:
   *  RelationalOperator: '<S220>/LowerRelop1'
   */
  if (!(rtb_UkYk1 > FOC_MTPA_FWC_FF_Y.Id_error)) {
    /* Product: '<S8>/delta fall limit' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     */
    FOC_MTPA_FWC_FF_Y.Id_error = FOC_MTPA_FWC_FF_B.sampletime *
      FOC_MTPA_FWC_FF_U.Rate_limiter.Torque_gen_ramp_down;

    /* Switch: '<S220>/Switch' incorporates:
     *  RelationalOperator: '<S220>/UpperRelop'
     */
    if (!(rtb_UkYk1 < FOC_MTPA_FWC_FF_Y.Id_error)) {
      /* Product: '<S8>/delta fall limit' */
      FOC_MTPA_FWC_FF_Y.Id_error = rtb_UkYk1;
    }

    /* End of Switch: '<S220>/Switch' */
  }

  /* End of Switch: '<S220>/Switch2' */

  /* Sum: '<S8>/Difference Inputs2' incorporates:
   *  Delay: '<S8>/Delay'
   *
   * Block description for '<S8>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_MTPA_FWC_FF_Y.Iq_PID = FOC_MTPA_FWC_FF_Y.Id_error +
    FOC_MTPA_FWC_FF_DW.Delay_DSTATE;

  /* Switch: '<S2>/Switch' incorporates:
   *  Inport: '<Root>/Iq_Torque_ratio'
   *  Inport: '<Root>/Speed_1_Torque_0'
   *  Inport: '<Root>/T_ref'
   *  Product: '<S2>/Product1'
   */
  if (FOC_MTPA_FWC_FF_U.Speed_1_Torque_0 > 0.0) {
    rtb_UkYk1 = FOC_MTPA_FWC_FF_Y.Iq_PID * FOC_MTPA_FWC_FF_U.Iq_Torque_ratio;
  } else {
    rtb_UkYk1 = FOC_MTPA_FWC_FF_U.RefTrq;
  }

  /* Product: '<S155>/Divide' incorporates:
   *  Abs: '<S155>/Abs1'
   *  Constant: '<S155>/Constant1'
   *  Gain: '<S155>/Gain'
   *  Inport: '<Root>/Lambda'
   *  Inport: '<Root>/Pole_pairs'
   *  Product: '<S155>/Product'
   *  Switch: '<S2>/Switch'
   */
  rtb_UkYk1 = fabs(2.0 * rtb_UkYk1) / (FOC_MTPA_FWC_FF_U.Lambda *
    FOC_MTPA_FWC_FF_U.p * 3.0);

  /* Switch: '<S216>/Switch2' incorporates:
   *  Inport: '<Root>/Id_Iq_MTPA_limit'
   *  RelationalOperator: '<S216>/LowerRelop1'
   *  RelationalOperator: '<S216>/UpperRelop'
   *  Switch: '<S216>/Switch'
   */
  if (rtb_UkYk1 > FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_up_limit) {
    rtb_UkYk1 = FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_up_limit;
  } else if (rtb_UkYk1 < FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_low_limit) {
    /* Switch: '<S216>/Switch' */
    rtb_UkYk1 = FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_low_limit;
  }

  /* End of Switch: '<S216>/Switch2' */

  /* AlgorithmDescriptorDelegate generated from: '<S22>/a16' incorporates:
   *  Gain: '<S155>/Gain2'
   *  Inport: '<Root>/Lambda'
   *  Inport: '<Root>/Ld'
   *  Inport: '<Root>/Lq'
   *  Product: '<S155>/Divide1'
   *  Sum: '<S155>/Subtract2'
   */
  FOC_MTPA_FWC_FF_Y.Id = FOC_MTPA_FWC_FF_U.Lambda / ((FOC_MTPA_FWC_FF_U.Lq -
    FOC_MTPA_FWC_FF_U.Ld) * 4.0);

  /* Outputs for IfAction SubSystem: '<S7>/If Action Subsystem1' incorporates:
   *  ActionPort: '<S154>/Action Port'
   */
  /* If: '<S7>/If' incorporates:
   *  Math: '<S154>/Square'
   *  Math: '<S155>/Math Function2'
   */
  rtb_UkYk1 *= rtb_UkYk1;

  /* End of Outputs for SubSystem: '<S7>/If Action Subsystem1' */

  /* Sum: '<S155>/Subtract' incorporates:
   *  Abs: '<S155>/Abs2'
   *  Gain: '<S155>/Gain4'
   *  Math: '<S155>/Math Function'
   *  Math: '<S155>/Math Function2'
   *  Sqrt: '<S155>/Sqrt'
   *  Sum: '<S155>/Add'
   */
  FOC_MTPA_FWC_FF_Y.Id_ref_MTPA = FOC_MTPA_FWC_FF_Y.Id - sqrtf(fabs
    (FOC_MTPA_FWC_FF_Y.Id * FOC_MTPA_FWC_FF_Y.Id + 0.5 * rtb_UkYk1));

  /* Switch: '<S215>/Switch2' incorporates:
   *  Inport: '<Root>/Id_Iq_MTPA_limit'
   *  RelationalOperator: '<S215>/LowerRelop1'
   *  RelationalOperator: '<S215>/UpperRelop'
   *  Switch: '<S215>/Switch'
   */
  if (FOC_MTPA_FWC_FF_Y.Id_ref_MTPA >
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_up_limit) {
    /* Sum: '<S155>/Subtract' */
    FOC_MTPA_FWC_FF_Y.Id_ref_MTPA =
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_up_limit;
  } else if (FOC_MTPA_FWC_FF_Y.Id_ref_MTPA <
             FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_low_limit) {
    /* Sum: '<S155>/Subtract' incorporates:
     *  Switch: '<S215>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Id_ref_MTPA =
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_low_limit;
  }

  /* End of Switch: '<S215>/Switch2' */

  /* Sqrt: '<S155>/Sqrt1' incorporates:
   *  Abs: '<S155>/Abs'
   *  Math: '<S155>/Math Function2'
   *  Math: '<S155>/Math Function3'
   *  Sum: '<S155>/Subtract1'
   */
  FOC_MTPA_FWC_FF_Y.Iq_ref_MTPA = sqrtf(fabs(rtb_UkYk1 -
    FOC_MTPA_FWC_FF_Y.Id_ref_MTPA * FOC_MTPA_FWC_FF_Y.Id_ref_MTPA));

  /* Switch: '<S158>/Switch2' incorporates:
   *  Inport: '<Root>/Actual Speed_mech_rpm'
   *  Inport: '<Root>/Pole_pairs'
   *  Product: '<S160>/Product'
   */
  FOC_MTPA_FWC_FF_Y.Id_ref_final = FOC_MTPA_FWC_FF_U.p *
    FOC_MTPA_FWC_FF_U.MtrSpd;

  /* AlgorithmDescriptorDelegate generated from: '<S22>/a16' incorporates:
   *  Gain: '<S160>/Gain'
   *  Inport: '<Root>/Lq'
   *  Product: '<S160>/Product1'
   */
  FOC_MTPA_FWC_FF_Y.Id = -(FOC_MTPA_FWC_FF_Y.Id_ref_final * FOC_MTPA_FWC_FF_U.Lq
    * FOC_MTPA_FWC_FF_Y.Iq_ref_MTPA);

  /* Switch: '<S158>/Switch2' incorporates:
   *  Inport: '<Root>/Lambda'
   *  Inport: '<Root>/Ld'
   *  Product: '<S160>/Product2'
   *  Product: '<S160>/Product3'
   *  Sum: '<S160>/Add'
   */
  FOC_MTPA_FWC_FF_Y.Id_ref_final *= FOC_MTPA_FWC_FF_U.Ld *
    FOC_MTPA_FWC_FF_Y.Id_ref_MTPA + FOC_MTPA_FWC_FF_U.Lambda;

  if (FOC_MTPA_FWC_FF_Y.Id >= SVM_VOLTAGE_LIMIT) {
    FOC_MTPA_FWC_FF_Y.Id = SVM_VOLTAGE_LIMIT;
  } else if (FOC_MTPA_FWC_FF_Y.Id <= -SVM_VOLTAGE_LIMIT) {
    FOC_MTPA_FWC_FF_Y.Id = -SVM_VOLTAGE_LIMIT;
  }

  if (FOC_MTPA_FWC_FF_Y.Id_ref_final >= SVM_VOLTAGE_LIMIT) {
    FOC_MTPA_FWC_FF_Y.Id_ref_final = SVM_VOLTAGE_LIMIT;
  } else if (FOC_MTPA_FWC_FF_Y.Id_ref_final <= -SVM_VOLTAGE_LIMIT) {
    FOC_MTPA_FWC_FF_Y.Id_ref_final = -SVM_VOLTAGE_LIMIT;
  }

  /* Sqrt: '<S160>/Sqrt' incorporates:
   *  Math: '<S160>/Square'
   *  Math: '<S160>/Square1'
   *  Sum: '<S160>/Add1'
   */
  FOC_MTPA_FWC_FF_Y.V_s = sqrtf(FOC_MTPA_FWC_FF_Y.Id * FOC_MTPA_FWC_FF_Y.Id +
    FOC_MTPA_FWC_FF_Y.Id_ref_final * FOC_MTPA_FWC_FF_Y.Id_ref_final);

  FOC_MTPA_FWC_FF_Y.V_s = fmin(FOC_MTPA_FWC_FF_Y.V_s, (2.0f * FOC_MTPA_FWC_FF_Y.V_max));

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
    if (FOC_MTPA_FWC_FF_Y.V_s < 0.8 * FOC_MTPA_FWC_FF_Y.V_max) {
      FOC_MTPA_FWC_FF_DW.is_c3_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_MTPA;
      rtb_State = 0;
      guard2 = true;
    } else {
      rtb_State = 1;
      guard1 = true;
    }

    /* case IN_MTPA: */
  } else if (FOC_MTPA_FWC_FF_Y.V_s > 0.9 * FOC_MTPA_FWC_FF_Y.V_max) {
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
     *  DiscreteIntegrator: '<S191>/Filter'
     *  DiscreteIntegrator: '<S196>/Integrator'
     *  Inport: '<Root>/MTPA_PID'
     *  Math: '<S154>/Square1'
     *  Merge: '<S7>/Merge'
     *  Product: '<S189>/DProd Out'
     *  Product: '<S193>/IProd Out'
     *  Product: '<S199>/NProd Out'
     *  Product: '<S201>/PProd Out'
     *  RelationalOperator: '<S204>/LowerRelop1'
     *  RelationalOperator: '<S204>/UpperRelop'
     *  SignalConversion generated from: '<S154>/Out1'
     *  Sqrt: '<S154>/Sqrt'
     *  Sum: '<S154>/Add'
     *  Sum: '<S154>/Subtract'
     *  Sum: '<S154>/Subtract1'
     *  Sum: '<S188>/SumI2'
     *  Sum: '<S188>/SumI4'
     *  Sum: '<S191>/SumD'
     *  Sum: '<S206>/Sum'
     *  Switch: '<S204>/Switch'
     *  Switch: '<S204>/Switch2'
     * */
    rtb_IProdOut = FOC_MTPA_FWC_FF_Y.V_max - FOC_MTPA_FWC_FF_Y.V_s;
    rtb_NProdOut_l = (rtb_IProdOut *
                      FOC_MTPA_FWC_FF_U.MTPA_PID.FWC_PID_MTPA.Kd_FWC_PID_MTPA -
                      FOC_MTPA_FWC_FF_DW.Filter_DSTATE_e) *
      FOC_MTPA_FWC_FF_U.MTPA_PID.FWC_PID_MTPA.Filter_FWC_PID_MTPA;
    rtb_Sum_h = (rtb_IProdOut *
                 FOC_MTPA_FWC_FF_U.MTPA_PID.FWC_PID_MTPA.Kp_FWC_PID_MTPA +
                 FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_i) + rtb_NProdOut_l;
    if (rtb_Sum_h > FOC_MTPA_FWC_FF_U.MTPA_PID.FWC_Up_limit) {
      rtb_Add_e = FOC_MTPA_FWC_FF_U.MTPA_PID.FWC_Up_limit;
    } else if (rtb_Sum_h < FOC_MTPA_FWC_FF_U.MTPA_PID.FWC_Low_limit) {
      /* Switch: '<S204>/Switch' */
      rtb_Add_e = FOC_MTPA_FWC_FF_U.MTPA_PID.FWC_Low_limit;
    } else {
      rtb_Add_e = rtb_Sum_h;
    }

    rtb_Sum_h = rtb_Add_e - rtb_Sum_h;
    rtb_Add_e += FOC_MTPA_FWC_FF_Y.Id_ref_MTPA;
    FOC_MTPA_FWC_FF_B.Merge[0] = rtb_Add_e;
    FOC_MTPA_FWC_FF_B.Merge[1] = sqrtf(rtb_UkYk1 - rtb_Add_e * rtb_Add_e);
    FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_i += (rtb_IProdOut *
      FOC_MTPA_FWC_FF_U.MTPA_PID.FWC_PID_MTPA.Ki_FWC_PID_MTPA + rtb_Sum_h) *
      0.0001;
    FOC_MTPA_FWC_FF_DW.Filter_DSTATE_e += 0.0001 * rtb_NProdOut_l;

    /* End of Outputs for SubSystem: '<S7>/If Action Subsystem1' */
  }

  /* End of Chart: '<S160>/Chart' */

  /* Delay: '<S156>/Delay' */
  if (FOC_MTPA_FWC_FF_DW.icLoad_p) {
    /* Sum: '<S156>/Difference Inputs2'
     *
     * Block description for '<S156>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_MTPA_FWC_FF_DW.Delay_DSTATE_h = FOC_MTPA_FWC_FF_B.Merge[0];
  }

  /* AlgorithmDescriptorDelegate generated from: '<S22>/a16' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  Product: '<S156>/delta rise limit'
   *  SampleTimeMath: '<S156>/sample time'
   *
   * About '<S156>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  FOC_MTPA_FWC_FF_Y.Id = FOC_MTPA_FWC_FF_U.Rate_limiter.Id_ramp_up * 0.0001;

  /* Sum: '<S156>/Difference Inputs1' incorporates:
   *  Delay: '<S156>/Delay'
   *
   * Block description for '<S156>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_UkYk1 = FOC_MTPA_FWC_FF_B.Merge[0] - FOC_MTPA_FWC_FF_DW.Delay_DSTATE_h;

  /* Switch: '<S217>/Switch2' incorporates:
   *  RelationalOperator: '<S217>/LowerRelop1'
   */
  if (!(rtb_UkYk1 > FOC_MTPA_FWC_FF_Y.Id)) {
    /* AlgorithmDescriptorDelegate generated from: '<S22>/a16' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  Product: '<S156>/delta fall limit'
     *  SampleTimeMath: '<S156>/sample time'
     *
     * About '<S156>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    FOC_MTPA_FWC_FF_Y.Id = 0.0001 * FOC_MTPA_FWC_FF_U.Rate_limiter.Id_ramp_down;

    /* Switch: '<S217>/Switch' incorporates:
     *  RelationalOperator: '<S217>/UpperRelop'
     */
    if (!(rtb_UkYk1 < FOC_MTPA_FWC_FF_Y.Id)) {
      /* AlgorithmDescriptorDelegate generated from: '<S22>/a16' */
      FOC_MTPA_FWC_FF_Y.Id = rtb_UkYk1;
    }

    /* End of Switch: '<S217>/Switch' */
  }

  /* End of Switch: '<S217>/Switch2' */

  /* Sum: '<S156>/Difference Inputs2' incorporates:
   *  Delay: '<S156>/Delay'
   *
   * Block description for '<S156>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_MTPA_FWC_FF_DW.Delay_DSTATE_h += FOC_MTPA_FWC_FF_Y.Id;

  /* Switch: '<S158>/Switch2' incorporates:
   *  Inport: '<Root>/Id_Iq_MTPA_limit'
   *  RelationalOperator: '<S158>/LowerRelop1'
   *  RelationalOperator: '<S158>/UpperRelop'
   *  Switch: '<S158>/Switch'
   */
  if (FOC_MTPA_FWC_FF_DW.Delay_DSTATE_h >
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_up_limit) {
    /* Switch: '<S158>/Switch2' */
    FOC_MTPA_FWC_FF_Y.Id_ref_final =
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_up_limit;
  } else if (FOC_MTPA_FWC_FF_DW.Delay_DSTATE_h <
             FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_low_limit) {
    /* Switch: '<S158>/Switch2' incorporates:
     *  Switch: '<S158>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Id_ref_final =
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_low_limit;
  } else {
    /* Switch: '<S158>/Switch2' incorporates:
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
  rtb_UkYk1 = ((FOC_MTPA_FWC_FF_U.PhaseCurrent[0] +
                FOC_MTPA_FWC_FF_U.PhaseCurrent[1]) +
               FOC_MTPA_FWC_FF_U.PhaseCurrent[1]) * 0.57735026918962584;

  /* End of Outputs for SubSystem: '<S14>/Two phase CRL wrap' */

  /* Trigonometry: '<S4>/Trigonometric Function' incorporates:
   *  Inport: '<Root>/angle'
   *  Trigonometry: '<S6>/Trigonometric Function1'
   */
  rtb_Sum_h = sinf(FOC_MTPA_FWC_FF_U.MtrElcPos);

  /* Trigonometry: '<S4>/Trigonometric Function1' incorporates:
   *  Inport: '<Root>/angle'
   *  Trigonometry: '<S6>/Trigonometric Function'
   */
  rtb_Add1_l = cosf(FOC_MTPA_FWC_FF_U.MtrElcPos);

  /* Outputs for Atomic SubSystem: '<S13>/Two inputs CRL' */
  /* Outputs for Atomic SubSystem: '<S14>/Two phase CRL wrap' */
  /* AlgorithmDescriptorDelegate generated from: '<S22>/a16' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S15>/a16'
   *  Inport: '<Root>/Phase Current'
   *  Product: '<S22>/acos'
   *  Product: '<S22>/bsin'
   *  Sum: '<S22>/sum_Ds'
   *  Trigonometry: '<S4>/Trigonometric Function'
   *  Trigonometry: '<S4>/Trigonometric Function1'
   */
  FOC_MTPA_FWC_FF_Y.Id = FOC_MTPA_FWC_FF_U.PhaseCurrent[0] * rtb_Add1_l +
    rtb_UkYk1 * rtb_Sum_h;

  /* AlgorithmDescriptorDelegate generated from: '<S22>/a16' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S15>/a16'
   *  Inport: '<Root>/Phase Current'
   *  Product: '<S22>/asin'
   *  Product: '<S22>/bcos'
   *  Sum: '<S22>/sum_Qs'
   *  Trigonometry: '<S4>/Trigonometric Function'
   *  Trigonometry: '<S4>/Trigonometric Function1'
   */
  rtb_NProdOut_l = rtb_UkYk1 * rtb_Add1_l - FOC_MTPA_FWC_FF_U.PhaseCurrent[0] *
    rtb_Sum_h;

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
  FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE = (1.0 -
    FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Id_Filter_coefficient) *
    FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE + FOC_MTPA_FWC_FF_Y.Id *
    FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Id_Filter_coefficient;

  /* Switch: '<S4>/Switch' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   */
  if (FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Id_Filter_switch > 0.0) {
    /* AlgorithmDescriptorDelegate generated from: '<S22>/a16' incorporates:
     *  UnitDelay: '<S18>/Unit Delay'
     */
    FOC_MTPA_FWC_FF_Y.Id = FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE;
  }

  /* End of Switch: '<S4>/Switch' */

  /* Product: '<S8>/delta fall limit' incorporates:
   *  Sum: '<S28>/Sum3'
   */
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
  rtb_IProdOut = (FOC_MTPA_FWC_FF_Y.Id_error *
                  FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA +
                  FOC_MTPA_FWC_FF_DW.Integrator_DSTATE) + rtb_UkYk1;

  /* Switch: '<S131>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S131>/LowerRelop1'
   *  RelationalOperator: '<S131>/UpperRelop'
   *  Switch: '<S131>/Switch'
   */
  if (rtb_IProdOut > FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_flux_PID) {
    /* Switch: '<S131>/Switch2' */
    FOC_MTPA_FWC_FF_Y.Vd_PID = FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_flux_PID;
  } else if (rtb_IProdOut < FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_flux_PID) {
    /* Switch: '<S131>/Switch2' incorporates:
     *  Switch: '<S131>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Vd_PID = FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_flux_PID;
  } else {
    /* Switch: '<S131>/Switch2' incorporates:
     *  Switch: '<S131>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Vd_PID = rtb_IProdOut;
  }

  /* End of Switch: '<S131>/Switch2' */

  /* Gain: '<S5>/Gain' incorporates:
   *  Inport: '<Root>/Bus_Voltage'
   */
  rtb_Gain_j = 0.577350259F * FOC_MTPA_FWC_FF_U.BusVoltage_V;

  /* Delay: '<S157>/Delay' */
  if (FOC_MTPA_FWC_FF_DW.icLoad_l) {
    /* Sum: '<S157>/Difference Inputs2'
     *
     * Block description for '<S157>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_MTPA_FWC_FF_DW.Delay_DSTATE_b = FOC_MTPA_FWC_FF_B.Merge[1];
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
    0.0001;

  /* Sum: '<S157>/Difference Inputs1' incorporates:
   *  Delay: '<S157>/Delay'
   *
   * Block description for '<S157>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Add_e = FOC_MTPA_FWC_FF_B.Merge[1] - FOC_MTPA_FWC_FF_DW.Delay_DSTATE_b;

  /* Switch: '<S218>/Switch2' incorporates:
   *  RelationalOperator: '<S218>/LowerRelop1'
   */
  if (!(rtb_Add_e > FOC_MTPA_FWC_FF_Y.Iq_ref_final)) {
    /* Product: '<S157>/delta fall limit' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  SampleTimeMath: '<S157>/sample time'
     *
     * About '<S157>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    FOC_MTPA_FWC_FF_Y.Iq_ref_final = 0.0001 *
      FOC_MTPA_FWC_FF_U.Rate_limiter.Iq_ramp_down;

    /* Switch: '<S218>/Switch' incorporates:
     *  RelationalOperator: '<S218>/UpperRelop'
     */
    if (!(rtb_Add_e < FOC_MTPA_FWC_FF_Y.Iq_ref_final)) {
      /* Product: '<S157>/delta fall limit' */
      FOC_MTPA_FWC_FF_Y.Iq_ref_final = rtb_Add_e;
    }

    /* End of Switch: '<S218>/Switch' */
  }

  /* End of Switch: '<S218>/Switch2' */

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

  /* Switch: '<S4>/Switch1' incorporates:
   *  Gain: '<S30>/wm_pu2si_mech2elec'
   *  Inport: '<Root>/Actual Speed_mech_rpm'
   */
  FOC_MTPA_FWC_FF_Y.Iq = POLEPAIRS * FOC_MTPA_FWC_FF_U.MtrSpd;

  /* Gain: '<S30>/NegSign' incorporates:
   *  Inport: '<Root>/Lq'
   *  Product: '<S30>/prod1'
   */
  rtb_Add_e = -(FOC_MTPA_FWC_FF_U.Lq * FOC_MTPA_FWC_FF_Y.Iq_ref_final *
                FOC_MTPA_FWC_FF_Y.Iq);

  /* Switch: '<S32>/Switch2' incorporates:
   *  RelationalOperator: '<S32>/LowerRelop1'
   *  RelationalOperator: '<S32>/UpperRelop'
   *  Switch: '<S30>/Switch'
   *  Switch: '<S32>/Switch'
   *  UnaryMinus: '<S30>/Unary Minus'
   */
  if (rtb_Add_e > rtb_Gain_j) {
    rtb_Add_e = rtb_Gain_j;
  } else if (rtb_Add_e < -rtb_Gain_j) {
    /* Switch: '<S32>/Switch' incorporates:
     *  UnaryMinus: '<S30>/Unary Minus'
     */
    rtb_Add_e = -rtb_Gain_j;
  }

  /* Sum: '<S5>/Add' incorporates:
   *  Switch: '<S32>/Switch2'
   */
  FOC_MTPA_FWC_FF_Y.Vd = FOC_MTPA_FWC_FF_Y.Vd_PID + rtb_Add_e;

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
   *  Inport: '<Root>/Lambda'
   *  Inport: '<Root>/Ld'
   *  Product: '<S30>/prod3'
   *  Sum: '<S30>/add1'
   */
  rtb_VqFF_unsat = (FOC_MTPA_FWC_FF_U.Ld * FOC_MTPA_FWC_FF_Y.Id_ref_final +
                    FOC_MTPA_FWC_FF_U.Lambda) * FOC_MTPA_FWC_FF_Y.Iq;

  /* Sum: '<S21>/Add1' incorporates:
   *  Constant: '<S12>/One'
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   *  Product: '<S21>/Product'
   *  Product: '<S21>/Product1'
   *  Sum: '<S12>/Sum'
   *  Switch: '<S12>/Switch1'
   *  UnitDelay: '<S21>/Unit Delay'
   */
  FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE_f = (1.0 -
    FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Iq_Filter_coefficient) *
    FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE_f + rtb_NProdOut_l *
    FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Iq_Filter_coefficient;

  /* Switch: '<S4>/Switch1' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   */
  if (FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Iq_Filter_switch > 0.0) {
    /* Switch: '<S4>/Switch1' incorporates:
     *  UnitDelay: '<S21>/Unit Delay'
     */
    FOC_MTPA_FWC_FF_Y.Iq = FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE_f;
  } else {
    /* Switch: '<S4>/Switch1' */
    FOC_MTPA_FWC_FF_Y.Iq = rtb_NProdOut_l;
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
  rtb_NProdOut_l = (FOC_MTPA_FWC_FF_Y.Iq_error *
                    FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA
                    - FOC_MTPA_FWC_FF_DW.Filter_DSTATE_d) *
    FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Filter_torque_PID_MTPA;

  /* Sum: '<S79>/Sum' incorporates:
   *  DiscreteIntegrator: '<S69>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S74>/PProd Out'
   */
  rtb_Add_e = (FOC_MTPA_FWC_FF_Y.Iq_error *
               FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA +
               FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_h) + rtb_NProdOut_l;

  /* Switch: '<S77>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S77>/LowerRelop1'
   *  RelationalOperator: '<S77>/UpperRelop'
   *  Switch: '<S77>/Switch'
   */
  if (rtb_Add_e > FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_torque_PID) {
    /* Switch: '<S77>/Switch2' */
    FOC_MTPA_FWC_FF_Y.Vq_PID = FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_torque_PID;
  } else if (rtb_Add_e < FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_torque_PID) {
    /* Switch: '<S77>/Switch2' incorporates:
     *  Switch: '<S77>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Vq_PID = FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_torque_PID;
  } else {
    /* Switch: '<S77>/Switch2' incorporates:
     *  Switch: '<S77>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Vq_PID = rtb_Add_e;
  }

  /* End of Switch: '<S77>/Switch2' */

  /* Switch: '<S33>/Switch2' incorporates:
   *  RelationalOperator: '<S33>/LowerRelop1'
   *  RelationalOperator: '<S33>/UpperRelop'
   *  Switch: '<S30>/Switch'
   *  Switch: '<S33>/Switch'
   *  UnaryMinus: '<S30>/Unary Minus'
   */
  if (rtb_VqFF_unsat > rtb_Gain_j) {
    rtb_VqFF_unsat = rtb_Gain_j;
  } else if (rtb_VqFF_unsat < -rtb_Gain_j) {
    /* Switch: '<S33>/Switch' incorporates:
     *  UnaryMinus: '<S30>/Unary Minus'
     */
    rtb_VqFF_unsat = -rtb_Gain_j;
  }

  /* Sum: '<S5>/Add1' incorporates:
   *  Switch: '<S33>/Switch2'
   */
  FOC_MTPA_FWC_FF_Y.Vq = rtb_VqFF_unsat + FOC_MTPA_FWC_FF_Y.Vq_PID;

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
  rtb_Switch_f_idx_0 = FOC_MTPA_FWC_FF_Y.Vd * rtb_Add1_l - FOC_MTPA_FWC_FF_Y.Vq *
    rtb_Sum_h;

  /* Gain: '<S145>/one_by_two' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S146>/a16'
   */
  rtb_VqFF_unsat = 0.5 * rtb_Switch_f_idx_0;

  /* Gain: '<S145>/sqrt3_by_two' incorporates:
   *  Product: '<S146>/dsin'
   *  Product: '<S146>/qcos'
   *  Sum: '<S146>/sum_beta'
   */
  rtb_Sum_h = (FOC_MTPA_FWC_FF_Y.Vq * rtb_Add1_l + FOC_MTPA_FWC_FF_Y.Vd *
               rtb_Sum_h) * 0.8660254037844386;

  /* End of Outputs for SubSystem: '<S143>/Two inputs CRL' */

  /* Sum: '<S145>/add_b' */
  rtb_Add1_l = rtb_Sum_h - rtb_VqFF_unsat;

  /* Sum: '<S145>/add_c' */
  rtb_VqFF_unsat = (0.0 - rtb_VqFF_unsat) - rtb_Sum_h;

  /* Outputs for Atomic SubSystem: '<S143>/Two inputs CRL' */
  /* Gain: '<S151>/one_by_two' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S146>/a16'
   *  MinMax: '<S151>/Max'
   *  MinMax: '<S151>/Min'
   *  Sum: '<S151>/Add'
   */
  rtb_Sum_h = (fmax(fmax(rtb_Switch_f_idx_0, rtb_Add1_l), rtb_VqFF_unsat) + fmin
               (fmin(rtb_Switch_f_idx_0, rtb_Add1_l), rtb_VqFF_unsat)) * -0.5;

  /* Outport: '<Root>/Va' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S146>/a16'
   *  Gain: '<S150>/Gain'
   *  Sum: '<S150>/Add3'
   */
  FOC_MTPA_FWC_FF_Y.Va = (rtb_Switch_f_idx_0 + rtb_Sum_h) * 1.1547005383792517;

  /* End of Outputs for SubSystem: '<S143>/Two inputs CRL' */

  /* Outport: '<Root>/Vb' incorporates:
   *  Gain: '<S150>/Gain'
   *  Sum: '<S150>/Add1'
   */
  FOC_MTPA_FWC_FF_Y.Vb = (rtb_Add1_l + rtb_Sum_h) * 1.1547005383792517;

  /* Outport: '<Root>/Vc' incorporates:
   *  Gain: '<S150>/Gain'
   *  Sum: '<S150>/Add2'
   */
  FOC_MTPA_FWC_FF_Y.Vc = (rtb_Sum_h + rtb_VqFF_unsat) * 1.1547005383792517;

  /* Outport: '<Root>/MTPA_FWC_condition' */
  FOC_MTPA_FWC_FF_Y.MTPA_FWC_condition = rtb_State;

  /* Delay: '<S3>/Delay' */
  if (FOC_MTPA_FWC_FF_DW.icLoad_k) {
    /* Sum: '<S3>/Difference Inputs2' incorporates:
     *  Constant: '<S3>/Constant'
     *
     * Block description for '<S3>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_MTPA_FWC_FF_DW.Delay_DSTATE_c = 0.0;
  }

  /* Sum: '<S3>/Difference Inputs1' incorporates:
   *  Delay: '<S3>/Delay'
   *  Inport: '<Root>/Ref_Speed_mech_rpm'
   *
   * Block description for '<S3>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Add1_l = FOC_MTPA_FWC_FF_U.Ref_Speed_mech_rpm -
    FOC_MTPA_FWC_FF_DW.Delay_DSTATE_c;

  /* Product: '<S3>/delta rise limit' incorporates:
   *  Inport: '<Root>/Ref_Speed_rate_up'
   *  SampleTimeMath: '<S3>/sample time'
   *
   * About '<S3>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_Sum_h = FOC_MTPA_FWC_FF_U.Ref_Speed_rate_up * 0.0001;

  /* Switch: '<S275>/Switch2' incorporates:
   *  RelationalOperator: '<S275>/LowerRelop1'
   */
  if (!(rtb_Add1_l > rtb_Sum_h)) {
    /* Product: '<S3>/delta fall limit' incorporates:
     *  Inport: '<Root>/Ref_Speed_rate_down'
     *  SampleTimeMath: '<S3>/sample time'
     *
     * About '<S3>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_Sum_h = 0.0001 * FOC_MTPA_FWC_FF_U.Ref_Speed_rate_down;

    /* Switch: '<S275>/Switch' incorporates:
     *  RelationalOperator: '<S275>/UpperRelop'
     */
    if (!(rtb_Add1_l < rtb_Sum_h)) {
      rtb_Sum_h = rtb_Add1_l;
    }

    /* End of Switch: '<S275>/Switch' */
  }

  /* End of Switch: '<S275>/Switch2' */

  /* Sum: '<S3>/Difference Inputs2' incorporates:
   *  Delay: '<S3>/Delay'
   *
   * Block description for '<S3>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_MTPA_FWC_FF_DW.Delay_DSTATE_c += rtb_Sum_h;

  /* Outport: '<Root>/Speed_error' incorporates:
   *  Gain: '<S1>/rpm to Rad//sec'
   *  Inport: '<Root>/Actual Speed_mech_rpm'
   *  Sum: '<S9>/Subtract'
   */
  FOC_MTPA_FWC_FF_Y.Speed_error = 0.10471975511965977 *
    FOC_MTPA_FWC_FF_DW.Delay_DSTATE_c - FOC_MTPA_FWC_FF_U.MtrSpd;

  /* Update for Delay: '<S8>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad = false;
  FOC_MTPA_FWC_FF_DW.Delay_DSTATE = FOC_MTPA_FWC_FF_Y.Iq_PID;

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
    (FOC_MTPA_FWC_FF_Y.Vd_PID - rtb_IProdOut)) * 0.0001;
  if (FOC_MTPA_FWC_FF_DW.Integrator_DSTATE > SVM_VOLTAGE_LIMIT) {
    FOC_MTPA_FWC_FF_DW.Integrator_DSTATE = SVM_VOLTAGE_LIMIT;
  } else if (FOC_MTPA_FWC_FF_DW.Integrator_DSTATE < -SVM_VOLTAGE_LIMIT) {
    FOC_MTPA_FWC_FF_DW.Integrator_DSTATE = -SVM_VOLTAGE_LIMIT;
  }

  /* End of Update for DiscreteIntegrator: '<S123>/Integrator' */

  /* Update for DiscreteIntegrator: '<S118>/Filter' */
  FOC_MTPA_FWC_FF_DW.Filter_DSTATE += 0.0001 * rtb_UkYk1;

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
    FOC_MTPA_FWC_FF_Y.Vq_PID) * -10.0 + FOC_MTPA_FWC_FF_Y.Iq_error *
    FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Ki_torque_PID_MTPA) +
    (FOC_MTPA_FWC_FF_Y.Vq_PID - rtb_Add_e)) * 0.0001;
  if (FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_h > SVM_VOLTAGE_LIMIT) {
    FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_h = SVM_VOLTAGE_LIMIT;
  } else if (FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_h < -SVM_VOLTAGE_LIMIT) {
    FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_h = -SVM_VOLTAGE_LIMIT;
  }

  /* End of Update for DiscreteIntegrator: '<S69>/Integrator' */

  /* Update for DiscreteIntegrator: '<S64>/Filter' */
  FOC_MTPA_FWC_FF_DW.Filter_DSTATE_d += 0.0001 * rtb_NProdOut_l;

  /* Update for Delay: '<S3>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad_k = false;
}

/* Model step function for TID1 */
void FOC_MTPA_FWC_FF_step1(void)       /* Sample time: [0.001s, 0.0s] */
{
  float rtb_NProdOut_n;
  float rtb_Sum_o;

  /* Product: '<S259>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S251>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S249>/DProd Out'
   *  Sum: '<S251>/SumD'
   */
  rtb_NProdOut_n = (FOC_MTPA_FWC_FF_Y.Speed_error *
                    FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA
                    - FOC_MTPA_FWC_FF_DW.Filter_DSTATE_i) *
    FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Filter_speed_PID_MTPA;

  /* Sum: '<S266>/Sum' incorporates:
   *  DiscreteIntegrator: '<S256>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S261>/PProd Out'
   */
  rtb_Sum_o = (FOC_MTPA_FWC_FF_Y.Speed_error *
               FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA +
               FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_b) + rtb_NProdOut_n;

  /* Switch: '<S264>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S264>/LowerRelop1'
   *  RelationalOperator: '<S264>/UpperRelop'
   *  Switch: '<S264>/Switch'
   */
  if (rtb_Sum_o > FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_speed_PID_MTPA) {
    /* Switch: '<S264>/Switch2' */
    FOC_MTPA_FWC_FF_B.Switch2 =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_speed_PID_MTPA;
  } else if (rtb_Sum_o < FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_speed_PID_MTPA) {
    /* Switch: '<S264>/Switch' incorporates:
     *  Switch: '<S264>/Switch2'
     */
    FOC_MTPA_FWC_FF_B.Switch2 =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_speed_PID_MTPA;
  } else {
    /* Switch: '<S264>/Switch2' incorporates:
     *  Switch: '<S264>/Switch'
     */
    FOC_MTPA_FWC_FF_B.Switch2 = rtb_Sum_o;
  }

  /* End of Switch: '<S264>/Switch2' */

  /* Outport: '<Root>/Iq_gen' */
  FOC_MTPA_FWC_FF_Y.Iq_gen = FOC_MTPA_FWC_FF_B.Switch2;

  /* SampleTimeMath: '<S8>/sample time'
   *
   * About '<S8>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  FOC_MTPA_FWC_FF_B.sampletime = 0.001;

  /* Update for DiscreteIntegrator: '<S256>/Integrator' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S253>/IProd Out'
   *  Sum: '<S248>/SumI2'
   *  Sum: '<S248>/SumI4'
   *  Sum: '<S268>/SumI3'
   *  Sum: '<S269>/SumI1'
   */
  FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_b += ((FOC_MTPA_FWC_FF_Y.Speed_error *
    FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Ki_speed_PID_MTPA +
    (FOC_MTPA_FWC_FF_B.Switch2 - FOC_MTPA_FWC_FF_B.Switch2)) +
    (FOC_MTPA_FWC_FF_B.Switch2 - rtb_Sum_o)) * 0.001;
  if (FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_b > MOTOR_PEAK_AC) {
    FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_b = MOTOR_PEAK_AC;
  } else if (FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_b < -MOTOR_PEAK_AC) {
    FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_b = -MOTOR_PEAK_AC;
  }

  /* End of Update for DiscreteIntegrator: '<S256>/Integrator' */

  /* Update for DiscreteIntegrator: '<S251>/Filter' */
  FOC_MTPA_FWC_FF_DW.Filter_DSTATE_i += 0.001 * rtb_NProdOut_n;
}

/* Model initialize function */
void FOC_MTPA_FWC_FF_initialize(void)
{
  /* InitializeConditions for Delay: '<S8>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad = true;

  /* InitializeConditions for Delay: '<S156>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad_p = true;

  /* InitializeConditions for Delay: '<S157>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad_l = true;

  /* InitializeConditions for Delay: '<S3>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad_k = true;

  FOC_MTPA_FWC_FF_U.BusVoltage_V = OP_VOLTAGE;
  FOC_MTPA_FWC_FF_U.Iq_Torque_ratio = CURR_TORQUE_RATIO;
  FOC_MTPA_FWC_FF_U.p = POLEPAIRS;
  FOC_MTPA_FWC_FF_U.Lambda = can_d.can_Lambda;
  FOC_MTPA_FWC_FF_U.Ld = can_d.can_Ld;
  FOC_MTPA_FWC_FF_U.Lq = can_d.can_Lq;
  FOC_MTPA_FWC_FF_U.Is_max = MOTOR_PEAK_AC;

  /* Id Iq Limits */
  FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_up_limit = 512.0f;
  FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_low_limit = -512.0f;
  FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_up_limit = 512.0f;
  FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_low_limit = -512.0f;
  
  /* Speed Ref Rate Limiter Settings */
  FOC_MTPA_FWC_FF_U.Ref_Speed_rate_up = 0.1f * 10000.0f;
  FOC_MTPA_FWC_FF_U.Ref_Speed_rate_down = -0.1f * 10000.0f;

  /* Rate Limiter Settings */
  FOC_MTPA_FWC_FF_U.Rate_limiter.Torque_gen_ramp_up = 50.0f * 10000.0f;
  FOC_MTPA_FWC_FF_U.Rate_limiter.Torque_gen_ramp_down = -50.0f * 10000.0f;
  FOC_MTPA_FWC_FF_U.Rate_limiter.Iq_ramp_up = 50.0f * 10000.0f;
  FOC_MTPA_FWC_FF_U.Rate_limiter.Iq_ramp_down = -50.0f * 10000.0f;
  FOC_MTPA_FWC_FF_U.Rate_limiter.Id_ramp_up = 50.0f * 10000.0f;
  FOC_MTPA_FWC_FF_U.Rate_limiter.Id_ramp_down = -50.0f * 10000.0f;

  /* FWC PID Values */
  FOC_MTPA_FWC_FF_U.MTPA_PID.FWC_PID_MTPA.Kp_FWC_PID_MTPA = can_d.canFW_PID.Kp;
  FOC_MTPA_FWC_FF_U.MTPA_PID.FWC_PID_MTPA.Ki_FWC_PID_MTPA = can_d.canFW_PID.Ki;
  FOC_MTPA_FWC_FF_U.MTPA_PID.FWC_PID_MTPA.Kd_FWC_PID_MTPA = can_d.canFW_PID.Kd;
  FOC_MTPA_FWC_FF_U.MTPA_PID.FWC_PID_MTPA.Filter_FWC_PID_MTPA = can_d.canFW_PID.Kd_Filter;
  FOC_MTPA_FWC_FF_U.MTPA_PID.FWC_Up_limit = can_d.canFW_PID.Output_Up_Limit;
  FOC_MTPA_FWC_FF_U.MTPA_PID.FWC_Low_limit = can_d.canFW_PID.Output_Low_Limit;

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
