/*
 * File: FOC_MTPA_FF.c
 *
 * Code generated for Simulink model 'FOC_MTPA_FF'.
 *
 * Model version                  : 18.293
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Tue Feb  3 14:27:04 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_MTPA_FF.h"
#include <math.h>

/* Block states (default storage) */
DW_FOC_MTPA_FF_T FOC_MTPA_FF_DW;

/* External inputs (root inport signals with default storage) */
ExtU_FOC_MTPA_FF_T FOC_MTPA_FF_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_FOC_MTPA_FF_T FOC_MTPA_FF_Y;

/* Real-time model */
static RT_MODEL_FOC_MTPA_FF_T FOC_MTPA_FF_M_;
RT_MODEL_FOC_MTPA_FF_T *const FOC_MTPA_FF_M = &FOC_MTPA_FF_M_;

/* Model step function for TID0 */
void FOC_MTPA_FF_step0(void)           /* Sample time: [0.0001s, 0.0s] */
{
  double rtb_Add1_l;
  double rtb_Add3;
  double rtb_Sum;
  double rtb_Sum_f;
  double rtb_Switch2_d;
  double rtb_Switch_f_idx_0;
  double rtb_VdFF_unsat;
  double rtb_VqFF_unsat;
  float rtb_Gain_j;
  float rtb_MathFunction2;
  float rtb_algDD_o1_d;
  float rtb_algDD_o2_o;

  /* Update the flag to indicate when data transfers from
   *  Sample time: [0.0001s, 0.0s] to Sample time: [0.001s, 0.0s]  */
  (FOC_MTPA_FF_M->Timing.RateInteraction.TID0_1)++;
  if ((FOC_MTPA_FF_M->Timing.RateInteraction.TID0_1) > 9) {
    FOC_MTPA_FF_M->Timing.RateInteraction.TID0_1 = 0;
  }

  /* Switch: '<S131>/Switch2' incorporates:
   *  DataTypeConversion: '<S28>/Data Type Conversion4'
   *  Inport: '<Root>/MTPA_PID'
   */
  FOC_MTPA_FF_Y.Vd_PID = FOC_MTPA_FF_U.MTPA_PID.Up_Limit_flux_PID;

  /* Sum: '<S28>/Sum3' incorporates:
   *  Gain: '<S7>/Gain2'
   *  Inport: '<Root>/Lambda'
   *  Inport: '<Root>/Ld'
   *  Inport: '<Root>/Lq'
   *  Product: '<S7>/Divide1'
   *  Sum: '<S7>/Subtract2'
   */
  FOC_MTPA_FF_Y.Id_error = FOC_MTPA_FF_U.Lambda / ((FOC_MTPA_FF_U.Lq -
    FOC_MTPA_FF_U.Ld) * 4.0);

  /* RateTransition: '<S2>/Rate Transition' */
  if (FOC_MTPA_FF_M->Timing.RateInteraction.TID0_1 == 1) {
    /* Outport: '<Root>/Iq_ref' */
    FOC_MTPA_FF_Y.Iq_ref = FOC_MTPA_FF_DW.RateTransition_Buffer0;
  }

  /* End of RateTransition: '<S2>/Rate Transition' */

  /* Switch: '<S7>/Switch' incorporates:
   *  Inport: '<Root>/Iq_Torque_ratio'
   *  Inport: '<Root>/Speed_1_Torque_0'
   *  Inport: '<Root>/T_ref'
   *  Outport: '<Root>/Iq_ref'
   *  Product: '<S7>/Product1'
   */
  if (FOC_MTPA_FF_U.Speed_1_Torque_0 > 0.0) {
    rtb_Switch2_d = FOC_MTPA_FF_Y.Iq_ref * FOC_MTPA_FF_U.Iq_Torque_ratio;
  } else {
    rtb_Switch2_d = FOC_MTPA_FF_U.RefTrq;
  }

  /* DataTypeConversion: '<S7>/Data Type Conversion' incorporates:
   *  Abs: '<S7>/Abs1'
   *  Constant: '<S7>/Constant1'
   *  Gain: '<S7>/Gain'
   *  Inport: '<Root>/Lambda'
   *  Inport: '<Root>/Pole_pairs'
   *  Product: '<S7>/Divide'
   *  Product: '<S7>/Product'
   *  Switch: '<S7>/Switch'
   */
  rtb_MathFunction2 = (float)(fabs(2.0 * rtb_Switch2_d) / (FOC_MTPA_FF_U.Lambda *
    FOC_MTPA_FF_U.p * 3.0));

  /* Switch: '<S154>/Switch2' incorporates:
   *  DataTypeConversion: '<S7>/Data Type Conversion'
   *  Inport: '<Root>/Id_Iq_MTPA_limit'
   *  RelationalOperator: '<S154>/LowerRelop1'
   *  RelationalOperator: '<S154>/UpperRelop'
   *  Switch: '<S154>/Switch'
   */
  if (rtb_MathFunction2 > FOC_MTPA_FF_U.Id_Iq_MTPA_limit.Iq_up_limit) {
    rtb_MathFunction2 = FOC_MTPA_FF_U.Id_Iq_MTPA_limit.Iq_up_limit;
  } else if (rtb_MathFunction2 < FOC_MTPA_FF_U.Id_Iq_MTPA_limit.Iq_low_limit) {
    /* Switch: '<S154>/Switch' */
    rtb_MathFunction2 = FOC_MTPA_FF_U.Id_Iq_MTPA_limit.Iq_low_limit;
  }

  /* End of Switch: '<S154>/Switch2' */

  /* Math: '<S7>/Math Function2' */
  rtb_MathFunction2 *= rtb_MathFunction2;

  /* Sum: '<S7>/Subtract' incorporates:
   *  Abs: '<S7>/Abs2'
   *  Gain: '<S7>/Gain4'
   *  Math: '<S7>/Math Function'
   *  Sqrt: '<S7>/Sqrt'
   *  Sum: '<S7>/Add'
   */
  FOC_MTPA_FF_Y.Id_ref = FOC_MTPA_FF_Y.Id_error - sqrt(fabs
    (FOC_MTPA_FF_Y.Id_error * FOC_MTPA_FF_Y.Id_error + 0.5F * rtb_MathFunction2));

  /* Switch: '<S153>/Switch2' incorporates:
   *  Inport: '<Root>/Id_Iq_MTPA_limit'
   *  RelationalOperator: '<S153>/LowerRelop1'
   *  RelationalOperator: '<S153>/UpperRelop'
   *  Switch: '<S153>/Switch'
   */
  if (FOC_MTPA_FF_Y.Id_ref > FOC_MTPA_FF_U.Id_Iq_MTPA_limit.Id_up_limit) {
    /* Sum: '<S7>/Subtract' */
    FOC_MTPA_FF_Y.Id_ref = FOC_MTPA_FF_U.Id_Iq_MTPA_limit.Id_up_limit;
  } else if (FOC_MTPA_FF_Y.Id_ref < FOC_MTPA_FF_U.Id_Iq_MTPA_limit.Id_low_limit)
  {
    /* Sum: '<S7>/Subtract' incorporates:
     *  Switch: '<S153>/Switch'
     */
    FOC_MTPA_FF_Y.Id_ref = FOC_MTPA_FF_U.Id_Iq_MTPA_limit.Id_low_limit;
  }

  /* End of Switch: '<S153>/Switch2' */

  /* Outputs for Atomic SubSystem: '<S14>/Two phase CRL wrap' */
  /* Gain: '<S15>/one_by_sqrt3' incorporates:
   *  Inport: '<Root>/Phase Current'
   *  Sum: '<S15>/a_plus_2b'
   */
  rtb_Switch2_d = ((FOC_MTPA_FF_U.PhaseCurrent[0] + FOC_MTPA_FF_U.PhaseCurrent[1])
                   + FOC_MTPA_FF_U.PhaseCurrent[1]) * 0.57735026918962584;

  /* End of Outputs for SubSystem: '<S14>/Two phase CRL wrap' */

  /* Trigonometry: '<S4>/Trigonometric Function' incorporates:
   *  Inport: '<Root>/angle'
   *  Trigonometry: '<S6>/Trigonometric Function1'
   */
  rtb_Add3 = sin(FOC_MTPA_FF_U.MtrElcPos);

  /* Trigonometry: '<S4>/Trigonometric Function1' incorporates:
   *  Inport: '<Root>/angle'
   *  Trigonometry: '<S6>/Trigonometric Function'
   */
  rtb_Add1_l = cos(FOC_MTPA_FF_U.MtrElcPos);

  /* Outputs for Atomic SubSystem: '<S13>/Two inputs CRL' */
  /* Outputs for Atomic SubSystem: '<S14>/Two phase CRL wrap' */
  /* AlgorithmDescriptorDelegate generated from: '<S22>/a16' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S15>/a16'
   *  Inport: '<Root>/Phase Current'
   *  Product: '<S22>/acos'
   *  Product: '<S22>/asin'
   *  Product: '<S22>/bcos'
   *  Product: '<S22>/bsin'
   *  Sum: '<S22>/sum_Ds'
   *  Sum: '<S22>/sum_Qs'
   *  Switch: '<S23>/Switch'
   *  Trigonometry: '<S4>/Trigonometric Function'
   *  Trigonometry: '<S4>/Trigonometric Function1'
   */
  rtb_algDD_o1_d = (float)(FOC_MTPA_FF_U.PhaseCurrent[0] * rtb_Add1_l +
    rtb_Switch2_d * rtb_Add3);
  rtb_algDD_o2_o = (float)(rtb_Switch2_d * rtb_Add1_l -
    FOC_MTPA_FF_U.PhaseCurrent[0] * rtb_Add3);

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
  FOC_MTPA_FF_DW.UnitDelay_DSTATE = (1.0F -
    FOC_MTPA_FF_U.IIR_Filter_Coefficient.Id_Filter_coefficient) *
    FOC_MTPA_FF_DW.UnitDelay_DSTATE + rtb_algDD_o1_d *
    FOC_MTPA_FF_U.IIR_Filter_Coefficient.Id_Filter_coefficient;

  /* Switch: '<S4>/Switch' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   *  UnitDelay: '<S18>/Unit Delay'
   */
  if (FOC_MTPA_FF_U.IIR_Filter_Coefficient.Id_Filter_switch > 0.0F) {
    rtb_Gain_j = FOC_MTPA_FF_DW.UnitDelay_DSTATE;
  } else {
    rtb_Gain_j = rtb_algDD_o1_d;
  }

  /* Sum: '<S28>/Sum3' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion'
   *  Switch: '<S4>/Switch'
   */
  FOC_MTPA_FF_Y.Id_error = FOC_MTPA_FF_Y.Id_ref - rtb_Gain_j;

  /* Product: '<S126>/NProd Out' incorporates:
   *  DataTypeConversion: '<S28>/Data Type Conversion2'
   *  DataTypeConversion: '<S28>/Data Type Conversion3'
   *  DiscreteIntegrator: '<S118>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S116>/DProd Out'
   *  Sum: '<S118>/SumD'
   */
  rtb_Switch2_d = (FOC_MTPA_FF_Y.Id_error *
                   FOC_MTPA_FF_U.MTPA_PID.Flux_PID_MTPA.Kd_flux_PID_MTPA -
                   FOC_MTPA_FF_DW.Filter_DSTATE) *
    FOC_MTPA_FF_U.MTPA_PID.Flux_PID_MTPA.Filter_flux_PID_MTPA;

  /* Sum: '<S133>/Sum' incorporates:
   *  DataTypeConversion: '<S28>/Data Type Conversion'
   *  DiscreteIntegrator: '<S123>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S128>/PProd Out'
   */
  rtb_Sum = (FOC_MTPA_FF_Y.Id_error *
             FOC_MTPA_FF_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA +
             FOC_MTPA_FF_DW.Integrator_DSTATE) + rtb_Switch2_d;

  /* Switch: '<S131>/Switch2' incorporates:
   *  DataTypeConversion: '<S28>/Data Type Conversion4'
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S131>/LowerRelop1'
   */
  if (!(rtb_Sum > FOC_MTPA_FF_U.MTPA_PID.Up_Limit_flux_PID)) {
    /* Switch: '<S131>/Switch' incorporates:
     *  DataTypeConversion: '<S28>/Data Type Conversion5'
     *  RelationalOperator: '<S131>/UpperRelop'
     */
    if (rtb_Sum < FOC_MTPA_FF_U.MTPA_PID.Low_Limit_flux_PID) {
      /* Switch: '<S131>/Switch2' */
      FOC_MTPA_FF_Y.Vd_PID = FOC_MTPA_FF_U.MTPA_PID.Low_Limit_flux_PID;
    } else {
      /* Switch: '<S131>/Switch2' */
      FOC_MTPA_FF_Y.Vd_PID = rtb_Sum;
    }

    /* End of Switch: '<S131>/Switch' */
  }

  /* End of Switch: '<S131>/Switch2' */

  /* Gain: '<S5>/Gain' incorporates:
   *  Inport: '<Root>/Bus_Voltage'
   */
  rtb_Gain_j = 0.577350259F * FOC_MTPA_FF_U.BusVoltage_V;

  /* Sum: '<S27>/Sum2' incorporates:
   *  Abs: '<S7>/Abs'
   *  Math: '<S7>/Math Function3'
   *  Sqrt: '<S7>/Sqrt1'
   *  Sum: '<S7>/Subtract1'
   */
  FOC_MTPA_FF_Y.Iq_error = sqrt(fabs(rtb_MathFunction2 - FOC_MTPA_FF_Y.Id_ref *
    FOC_MTPA_FF_Y.Id_ref));

  /* Switch: '<S77>/Switch2' incorporates:
   *  Gain: '<S30>/wm_pu2si_mech2elec'
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   */
  FOC_MTPA_FF_Y.Vq_PID = POLEPAIRS * FOC_MTPA_FF_U.MtrSpd;

  /* Gain: '<S30>/NegSign' incorporates:
   *  Inport: '<Root>/Lq'
   *  Product: '<S30>/prod1'
   */
  rtb_VdFF_unsat = -(FOC_MTPA_FF_U.Lq * FOC_MTPA_FF_Y.Iq_error *
                     FOC_MTPA_FF_Y.Vq_PID);

  /* Switch: '<S32>/Switch2' incorporates:
   *  RelationalOperator: '<S32>/LowerRelop1'
   *  RelationalOperator: '<S32>/UpperRelop'
   *  Switch: '<S30>/Switch'
   *  Switch: '<S32>/Switch'
   *  UnaryMinus: '<S30>/Unary Minus'
   */
  if (rtb_VdFF_unsat > rtb_Gain_j) {
    rtb_VdFF_unsat = rtb_Gain_j;
  } else if (rtb_VdFF_unsat < -rtb_Gain_j) {
    /* Switch: '<S32>/Switch' incorporates:
     *  UnaryMinus: '<S30>/Unary Minus'
     */
    rtb_VdFF_unsat = -rtb_Gain_j;
  }

  /* Sum: '<S5>/Add' incorporates:
   *  Switch: '<S32>/Switch2'
   */
  FOC_MTPA_FF_Y.Vd = FOC_MTPA_FF_Y.Vd_PID + rtb_VdFF_unsat;

  /* Switch: '<S25>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S25>/LowerRelop1'
   *  RelationalOperator: '<S25>/UpperRelop'
   *  Switch: '<S25>/Switch'
   */
  if (FOC_MTPA_FF_Y.Vd > FOC_MTPA_FF_U.MTPA_PID.Up_Limit_flux_PID) {
    /* Sum: '<S5>/Add' incorporates:
     *  DataTypeConversion: '<S28>/Data Type Conversion4'
     */
    FOC_MTPA_FF_Y.Vd = FOC_MTPA_FF_U.MTPA_PID.Up_Limit_flux_PID;
  } else if (FOC_MTPA_FF_Y.Vd < FOC_MTPA_FF_U.MTPA_PID.Low_Limit_flux_PID) {
    /* Sum: '<S5>/Add' incorporates:
     *  Switch: '<S25>/Switch'
     */
    FOC_MTPA_FF_Y.Vd = FOC_MTPA_FF_U.MTPA_PID.Low_Limit_flux_PID;
  }

  /* End of Switch: '<S25>/Switch2' */

  /* Product: '<S30>/prod2' incorporates:
   *  Inport: '<Root>/Lambda'
   *  Inport: '<Root>/Ld'
   *  Product: '<S30>/prod3'
   *  Sum: '<S30>/add1'
   */
  rtb_VqFF_unsat = (FOC_MTPA_FF_U.Ld * FOC_MTPA_FF_Y.Id_ref +
                    FOC_MTPA_FF_U.Lambda) * FOC_MTPA_FF_Y.Vq_PID;

  /* Switch: '<S77>/Switch2' incorporates:
   *  DataTypeConversion: '<S27>/Data Type Conversion10'
   *  Inport: '<Root>/MTPA_PID'
   */
  FOC_MTPA_FF_Y.Vq_PID = FOC_MTPA_FF_U.MTPA_PID.Up_Limit_torque_PID;

  /* Sum: '<S21>/Add1' incorporates:
   *  Constant: '<S12>/One'
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   *  Product: '<S21>/Product'
   *  Product: '<S21>/Product1'
   *  Sum: '<S12>/Sum'
   *  Switch: '<S12>/Switch1'
   *  UnitDelay: '<S21>/Unit Delay'
   */
  FOC_MTPA_FF_DW.UnitDelay_DSTATE_f = (1.0F -
    FOC_MTPA_FF_U.IIR_Filter_Coefficient.Iq_Filter_coefficient) *
    FOC_MTPA_FF_DW.UnitDelay_DSTATE_f + rtb_algDD_o2_o *
    FOC_MTPA_FF_U.IIR_Filter_Coefficient.Iq_Filter_coefficient;

  /* Switch: '<S4>/Switch1' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   */
  if (FOC_MTPA_FF_U.IIR_Filter_Coefficient.Iq_Filter_switch > 0.0F) {
    rtb_algDD_o2_o = FOC_MTPA_FF_DW.UnitDelay_DSTATE_f;
  }

  /* End of Switch: '<S4>/Switch1' */

  /* Sum: '<S27>/Sum2' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion1'
   */
  FOC_MTPA_FF_Y.Iq_error -= rtb_algDD_o2_o;

  /* Product: '<S72>/NProd Out' incorporates:
   *  DataTypeConversion: '<S27>/Data Type Conversion8'
   *  DataTypeConversion: '<S27>/Data Type Conversion9'
   *  DiscreteIntegrator: '<S64>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S62>/DProd Out'
   *  Sum: '<S64>/SumD'
   */
  rtb_VdFF_unsat = (FOC_MTPA_FF_Y.Iq_error *
                    FOC_MTPA_FF_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA -
                    FOC_MTPA_FF_DW.Filter_DSTATE_d) *
    FOC_MTPA_FF_U.MTPA_PID.Torque_PID_MTPA.Filter_torque_PID_MTPA;

  /* Sum: '<S79>/Sum' incorporates:
   *  DataTypeConversion: '<S27>/Data Type Conversion6'
   *  DiscreteIntegrator: '<S69>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S74>/PProd Out'
   */
  rtb_Sum_f = (FOC_MTPA_FF_Y.Iq_error *
               FOC_MTPA_FF_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA +
               FOC_MTPA_FF_DW.Integrator_DSTATE_h) + rtb_VdFF_unsat;

  /* Switch: '<S77>/Switch2' incorporates:
   *  DataTypeConversion: '<S27>/Data Type Conversion10'
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S77>/LowerRelop1'
   */
  if (!(rtb_Sum_f > FOC_MTPA_FF_U.MTPA_PID.Up_Limit_torque_PID)) {
    /* Switch: '<S77>/Switch' incorporates:
     *  DataTypeConversion: '<S27>/Data Type Conversion11'
     *  RelationalOperator: '<S77>/UpperRelop'
     */
    if (rtb_Sum_f < FOC_MTPA_FF_U.MTPA_PID.Low_Limit_torque_PID) {
      /* Switch: '<S77>/Switch2' */
      FOC_MTPA_FF_Y.Vq_PID = FOC_MTPA_FF_U.MTPA_PID.Low_Limit_torque_PID;
    } else {
      /* Switch: '<S77>/Switch2' */
      FOC_MTPA_FF_Y.Vq_PID = rtb_Sum_f;
    }

    /* End of Switch: '<S77>/Switch' */
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
  FOC_MTPA_FF_Y.Vq = rtb_VqFF_unsat + FOC_MTPA_FF_Y.Vq_PID;

  /* Switch: '<S26>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S26>/LowerRelop1'
   *  RelationalOperator: '<S26>/UpperRelop'
   *  Switch: '<S26>/Switch'
   */
  if (FOC_MTPA_FF_Y.Vq > FOC_MTPA_FF_U.MTPA_PID.Up_Limit_torque_PID) {
    /* Sum: '<S5>/Add1' incorporates:
     *  DataTypeConversion: '<S27>/Data Type Conversion10'
     */
    FOC_MTPA_FF_Y.Vq = FOC_MTPA_FF_U.MTPA_PID.Up_Limit_torque_PID;
  } else if (FOC_MTPA_FF_Y.Vq < FOC_MTPA_FF_U.MTPA_PID.Low_Limit_torque_PID) {
    /* Sum: '<S5>/Add1' incorporates:
     *  Switch: '<S26>/Switch'
     */
    FOC_MTPA_FF_Y.Vq = FOC_MTPA_FF_U.MTPA_PID.Low_Limit_torque_PID;
  }

  /* End of Switch: '<S26>/Switch2' */

  /* Outputs for Atomic SubSystem: '<S143>/Two inputs CRL' */
  /* Switch: '<S147>/Switch' incorporates:
   *  Product: '<S146>/dcos'
   *  Product: '<S146>/qsin'
   *  Sum: '<S146>/sum_alpha'
   */
  rtb_Switch_f_idx_0 = FOC_MTPA_FF_Y.Vd * rtb_Add1_l - FOC_MTPA_FF_Y.Vq *
    rtb_Add3;

  /* Gain: '<S145>/one_by_two' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S146>/a16'
   */
  rtb_VqFF_unsat = 0.5 * rtb_Switch_f_idx_0;

  /* Gain: '<S145>/sqrt3_by_two' incorporates:
   *  Product: '<S146>/dsin'
   *  Product: '<S146>/qcos'
   *  Sum: '<S146>/sum_beta'
   */
  rtb_Add3 = (FOC_MTPA_FF_Y.Vq * rtb_Add1_l + FOC_MTPA_FF_Y.Vd * rtb_Add3) *
    0.8660254037844386;

  /* End of Outputs for SubSystem: '<S143>/Two inputs CRL' */

  /* Sum: '<S145>/add_b' */
  rtb_Add1_l = rtb_Add3 - rtb_VqFF_unsat;

  /* Sum: '<S145>/add_c' */
  rtb_VqFF_unsat = (0.0 - rtb_VqFF_unsat) - rtb_Add3;

  /* Outputs for Atomic SubSystem: '<S143>/Two inputs CRL' */
  /* Gain: '<S151>/one_by_two' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S146>/a16'
   *  MinMax: '<S151>/Max'
   *  MinMax: '<S151>/Min'
   *  Sum: '<S151>/Add'
   */
  rtb_Add3 = (fmax(fmax(rtb_Switch_f_idx_0, rtb_Add1_l), rtb_VqFF_unsat) + fmin
              (fmin(rtb_Switch_f_idx_0, rtb_Add1_l), rtb_VqFF_unsat)) * -0.5;

  /* Outport: '<Root>/Va' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S146>/a16'
   *  Gain: '<S150>/Gain'
   *  Sum: '<S150>/Add3'
   */
  FOC_MTPA_FF_Y.Va = (rtb_Switch_f_idx_0 + rtb_Add3) * 1.1547005383792517;

  /* End of Outputs for SubSystem: '<S143>/Two inputs CRL' */

  /* Outport: '<Root>/Vb' incorporates:
   *  Gain: '<S150>/Gain'
   *  Sum: '<S150>/Add1'
   */
  FOC_MTPA_FF_Y.Vb = (rtb_Add1_l + rtb_Add3) * 1.1547005383792517;

  /* Outport: '<Root>/Vc' incorporates:
   *  Gain: '<S150>/Gain'
   *  Sum: '<S150>/Add2'
   */
  FOC_MTPA_FF_Y.Vc = (rtb_Add3 + rtb_VqFF_unsat) * 1.1547005383792517;

  /* Outport: '<Root>/Iq' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion1'
   */
  FOC_MTPA_FF_Y.Iq = rtb_algDD_o2_o;

  /* Switch: '<S4>/Switch' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   */
  if (FOC_MTPA_FF_U.IIR_Filter_Coefficient.Id_Filter_switch > 0.0F) {
    /* Outport: '<Root>/Id' incorporates:
     *  UnitDelay: '<S18>/Unit Delay'
     */
    FOC_MTPA_FF_Y.Id = FOC_MTPA_FF_DW.UnitDelay_DSTATE;
  } else {
    /* Outport: '<Root>/Id' */
    FOC_MTPA_FF_Y.Id = rtb_algDD_o1_d;
  }

  /* Product: '<S3>/delta rise limit' incorporates:
   *  Inport: '<Root>/Ref_Speed_rate_up'
   *  SampleTimeMath: '<S3>/sample time'
   *
   * About '<S3>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_Add3 = FOC_MTPA_FF_U.Ref_Speed_rate_up * 0.0001;

  /* Delay: '<S3>/Delay' */
  if (FOC_MTPA_FF_DW.icLoad) {
    /* Sum: '<S3>/Difference Inputs2' incorporates:
     *  Inport: '<Root>/Ref_Speed_mech_rpm'
     *
     * Block description for '<S3>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_MTPA_FF_DW.Delay_DSTATE = FOC_MTPA_FF_U.Ref_Speed_mech_rpm;
  }

  /* Sum: '<S3>/Difference Inputs1' incorporates:
   *  Delay: '<S3>/Delay'
   *  Inport: '<Root>/Ref_Speed_mech_rpm'
   *
   * Block description for '<S3>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_VqFF_unsat = FOC_MTPA_FF_U.Ref_Speed_mech_rpm -
    FOC_MTPA_FF_DW.Delay_DSTATE;

  /* Switch: '<S210>/Switch2' incorporates:
   *  RelationalOperator: '<S210>/LowerRelop1'
   */
  if (!(rtb_VqFF_unsat > rtb_Add3)) {
    /* Product: '<S3>/delta fall limit' incorporates:
     *  Inport: '<Root>/Ref_Speed_rate_down'
     *  SampleTimeMath: '<S3>/sample time'
     *
     * About '<S3>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_Add3 = 0.0001 * FOC_MTPA_FF_U.Ref_Speed_rate_down;

    /* Switch: '<S210>/Switch' incorporates:
     *  RelationalOperator: '<S210>/UpperRelop'
     */
    if (!(rtb_VqFF_unsat < rtb_Add3)) {
      rtb_Add3 = rtb_VqFF_unsat;
    }

    /* End of Switch: '<S210>/Switch' */
  }

  /* End of Switch: '<S210>/Switch2' */

  /* Sum: '<S3>/Difference Inputs2' incorporates:
   *  Delay: '<S3>/Delay'
   *
   * Block description for '<S3>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_MTPA_FF_DW.Delay_DSTATE += rtb_Add3;

  /* Outport: '<Root>/Speed_error' incorporates:
   *  Gain: '<S1>/rpm to Rad//sec'
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   *  Sum: '<S9>/Subtract'
   */
  FOC_MTPA_FF_Y.Speed_error = 0.10471975511965977 * FOC_MTPA_FF_DW.Delay_DSTATE
    - FOC_MTPA_FF_U.MtrSpd;

  /* Update for DiscreteIntegrator: '<S123>/Integrator' incorporates:
   *  DataTypeConversion: '<S28>/Data Type Conversion1'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S120>/IProd Out'
   *  Sum: '<S115>/SumI2'
   *  Sum: '<S115>/SumI4'
   *  Sum: '<S135>/SumI3'
   *  Sum: '<S136>/SumI1'
   */
  FOC_MTPA_FF_DW.Integrator_DSTATE += ((FOC_MTPA_FF_Y.Id_error *
    FOC_MTPA_FF_U.MTPA_PID.Flux_PID_MTPA.Ki_flux_PID_MTPA +
    (FOC_MTPA_FF_Y.Vd_PID - FOC_MTPA_FF_Y.Vd_PID)) + (FOC_MTPA_FF_Y.Vd_PID -
    rtb_Sum)) * 0.0001;
  if (FOC_MTPA_FF_DW.Integrator_DSTATE > SVM_VOLTAGE_LIMIT) {
    FOC_MTPA_FF_DW.Integrator_DSTATE = SVM_VOLTAGE_LIMIT;
  } else if (FOC_MTPA_FF_DW.Integrator_DSTATE < -SVM_VOLTAGE_LIMIT) {
    FOC_MTPA_FF_DW.Integrator_DSTATE = -SVM_VOLTAGE_LIMIT;
  }

  /* End of Update for DiscreteIntegrator: '<S123>/Integrator' */

  /* Update for DiscreteIntegrator: '<S118>/Filter' */
  FOC_MTPA_FF_DW.Filter_DSTATE += 0.0001 * rtb_Switch2_d;

  /* Update for DiscreteIntegrator: '<S69>/Integrator' incorporates:
   *  DataTypeConversion: '<S27>/Data Type Conversion7'
   *  Gain: '<S81>/Kt'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S66>/IProd Out'
   *  Sum: '<S61>/SumI2'
   *  Sum: '<S61>/SumI4'
   *  Sum: '<S81>/SumI3'
   *  Sum: '<S82>/SumI1'
   */
  FOC_MTPA_FF_DW.Integrator_DSTATE_h += (((FOC_MTPA_FF_Y.Vq_PID -
    FOC_MTPA_FF_Y.Vq_PID) * -10.0 + FOC_MTPA_FF_Y.Iq_error *
    FOC_MTPA_FF_U.MTPA_PID.Torque_PID_MTPA.Ki_torque_PID_MTPA) +
    (FOC_MTPA_FF_Y.Vq_PID - rtb_Sum_f)) * 0.0001;
  if (FOC_MTPA_FF_DW.Integrator_DSTATE_h > SVM_VOLTAGE_LIMIT) {
    FOC_MTPA_FF_DW.Integrator_DSTATE_h = SVM_VOLTAGE_LIMIT;
  } else if (FOC_MTPA_FF_DW.Integrator_DSTATE_h < -SVM_VOLTAGE_LIMIT) {
    FOC_MTPA_FF_DW.Integrator_DSTATE_h = -SVM_VOLTAGE_LIMIT;
  }

  /* End of Update for DiscreteIntegrator: '<S69>/Integrator' */

  /* Update for DiscreteIntegrator: '<S64>/Filter' */
  FOC_MTPA_FF_DW.Filter_DSTATE_d += 0.0001 * rtb_VdFF_unsat;

  /* Update for Delay: '<S3>/Delay' */
  FOC_MTPA_FF_DW.icLoad = false;
}

/* Model step function for TID1 */
void FOC_MTPA_FF_step1(void)           /* Sample time: [0.001s, 0.0s] */
{
  double rtb_NProdOut_j;
  double rtb_Sum;
  double rtb_UkYk1_l;
  double rtb_deltafalllimit_d;

  /* Product: '<S194>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S186>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S184>/DProd Out'
   *  Sum: '<S186>/SumD'
   */
  rtb_NProdOut_j = (FOC_MTPA_FF_Y.Speed_error *
                    FOC_MTPA_FF_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA -
                    FOC_MTPA_FF_DW.Filter_DSTATE_i) *
    FOC_MTPA_FF_U.MTPA_PID.Speed_PID_MTPA.Filter_speed_PID_MTPA;

  /* Sum: '<S201>/Sum' incorporates:
   *  DiscreteIntegrator: '<S191>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S196>/PProd Out'
   */
  rtb_Sum = (FOC_MTPA_FF_Y.Speed_error *
             FOC_MTPA_FF_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA +
             FOC_MTPA_FF_DW.Integrator_DSTATE_b) + rtb_NProdOut_j;

  /* Switch: '<S199>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S199>/LowerRelop1'
   *  RelationalOperator: '<S199>/UpperRelop'
   *  Switch: '<S199>/Switch'
   */
  if (rtb_Sum > FOC_MTPA_FF_U.MTPA_PID.Up_Limit_speed_PID_MTPA) {
    /* Switch: '<S199>/Switch2' */
    FOC_MTPA_FF_Y.Iq_gen = FOC_MTPA_FF_U.MTPA_PID.Up_Limit_speed_PID_MTPA;
  } else if (rtb_Sum < FOC_MTPA_FF_U.MTPA_PID.Low_Limit_speed_PID_MTPA) {
    /* Switch: '<S199>/Switch2' incorporates:
     *  Switch: '<S199>/Switch'
     */
    FOC_MTPA_FF_Y.Iq_gen = FOC_MTPA_FF_U.MTPA_PID.Low_Limit_speed_PID_MTPA;
  } else {
    /* Switch: '<S199>/Switch2' incorporates:
     *  Switch: '<S199>/Switch'
     */
    FOC_MTPA_FF_Y.Iq_gen = rtb_Sum;
  }

  if (d.forward_pin == GPIO_PIN_RESET && d.reverse_pin == GPIO_PIN_SET)
    FOC_MTPA_FF_Y.Iq_gen *= 1.0f;
  else if (d.forward_pin == GPIO_PIN_SET && d.reverse_pin == GPIO_PIN_RESET)
    FOC_MTPA_FF_Y.Iq_gen *= -1.0f;
  else
    FOC_MTPA_FF_Y.Iq_gen = 0.0f;

  /* End of Switch: '<S199>/Switch2' */

  /* Delay: '<S8>/Delay' */
  if (FOC_MTPA_FF_DW.icLoad_p) {
    /* Sum: '<S8>/Difference Inputs2'
     *
     * Block description for '<S8>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_MTPA_FF_DW.Delay_DSTATE_h = FOC_MTPA_FF_Y.Iq_gen;
  }

  /* Sum: '<S8>/Difference Inputs1' incorporates:
   *  Delay: '<S8>/Delay'
   *
   * Block description for '<S8>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_UkYk1_l = FOC_MTPA_FF_Y.Iq_gen - FOC_MTPA_FF_DW.Delay_DSTATE_h;

  /* Product: '<S8>/delta rise limit' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  SampleTimeMath: '<S8>/sample time'
   *
   * About '<S8>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_deltafalllimit_d = FOC_MTPA_FF_U.Rate_limiter.Torque_gen_ramp_up * 0.001;

  /* Switch: '<S155>/Switch2' incorporates:
   *  RelationalOperator: '<S155>/LowerRelop1'
   */
  if (!(rtb_UkYk1_l > rtb_deltafalllimit_d)) {
    /* Product: '<S8>/delta fall limit' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  SampleTimeMath: '<S8>/sample time'
     *
     * About '<S8>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_deltafalllimit_d = 0.001 *
      FOC_MTPA_FF_U.Rate_limiter.Torque_gen_ramp_down;

    /* Switch: '<S155>/Switch' incorporates:
     *  RelationalOperator: '<S155>/UpperRelop'
     */
    if (!(rtb_UkYk1_l < rtb_deltafalllimit_d)) {
      rtb_deltafalllimit_d = rtb_UkYk1_l;
    }

    /* End of Switch: '<S155>/Switch' */
  }

  /* End of Switch: '<S155>/Switch2' */

  /* Sum: '<S8>/Difference Inputs2' incorporates:
   *  Delay: '<S8>/Delay'
   *
   * Block description for '<S8>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_MTPA_FF_DW.Delay_DSTATE_h += rtb_deltafalllimit_d;

  /* RateTransition: '<S2>/Rate Transition' */
  FOC_MTPA_FF_DW.RateTransition_Buffer0 = FOC_MTPA_FF_DW.Delay_DSTATE_h;

  /* Update for DiscreteIntegrator: '<S191>/Integrator' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S188>/IProd Out'
   *  Sum: '<S183>/SumI2'
   *  Sum: '<S183>/SumI4'
   *  Sum: '<S203>/SumI3'
   *  Sum: '<S204>/SumI1'
   */
  FOC_MTPA_FF_DW.Integrator_DSTATE_b += ((FOC_MTPA_FF_Y.Speed_error *
    FOC_MTPA_FF_U.MTPA_PID.Speed_PID_MTPA.Ki_speed_PID_MTPA +
    (FOC_MTPA_FF_Y.Iq_gen - FOC_MTPA_FF_Y.Iq_gen)) + (FOC_MTPA_FF_Y.Iq_gen -
    rtb_Sum)) * 0.001;
  if (FOC_MTPA_FF_DW.Integrator_DSTATE_b > 500.0) {
    FOC_MTPA_FF_DW.Integrator_DSTATE_b = 500.0;
  } else if (FOC_MTPA_FF_DW.Integrator_DSTATE_b < -500.0) {
    FOC_MTPA_FF_DW.Integrator_DSTATE_b = -500.0;
  }

  /* End of Update for DiscreteIntegrator: '<S191>/Integrator' */

  /* Update for DiscreteIntegrator: '<S186>/Filter' */
  FOC_MTPA_FF_DW.Filter_DSTATE_i += 0.001 * rtb_NProdOut_j;

  /* Update for Delay: '<S8>/Delay' */
  FOC_MTPA_FF_DW.icLoad_p = false;
}

/* Model initialize function */
void FOC_MTPA_FF_initialize(void)
{
  /* InitializeConditions for Delay: '<S3>/Delay' */
  FOC_MTPA_FF_DW.icLoad = true;

  /* InitializeConditions for Delay: '<S8>/Delay' */
  FOC_MTPA_FF_DW.icLoad_p = true;

  /*Motor Params*/
  FOC_MTPA_FF_U.BusVoltage_V = OP_VOLTAGE;
  FOC_MTPA_FF_U.p = POLEPAIRS;
  FOC_MTPA_FF_U.Lq = LQ;
  FOC_MTPA_FF_U.Ld = LD;
  FOC_MTPA_FF_U.Lambda = LAMBDA;
  FOC_MTPA_FF_U.Rs = RS;
  FOC_MTPA_FF_U.Iq_Torque_ratio = CURR_TORQUE_RATIO;

  /* Rate limiter settings */
  FOC_MTPA_FF_U.Ref_Speed_rate_down = -1000.0f * 10000.0f;
  FOC_MTPA_FF_U.Ref_Speed_rate_up = 10.0f * 10000.0f;
  FOC_MTPA_FF_U.Rate_limiter.Torque_gen_ramp_down = -50.0f * 10000.0f;
  FOC_MTPA_FF_U.Rate_limiter.Torque_gen_ramp_up = 50.0f * 10000.0f;

  /* Limits and PID settings */
  /* Speed PID */
  FOC_MTPA_FF_U.MTPA_PID.Up_Limit_speed_PID_MTPA = 500.0f;
  FOC_MTPA_FF_U.MTPA_PID.Low_Limit_speed_PID_MTPA = 0.0f;
  FOC_MTPA_FF_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA = 4.0f;
  FOC_MTPA_FF_U.MTPA_PID.Speed_PID_MTPA.Ki_speed_PID_MTPA = 9.0f;
  FOC_MTPA_FF_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA = 0.00001f;
  FOC_MTPA_FF_U.MTPA_PID.Speed_PID_MTPA.Filter_speed_PID_MTPA = 5.0f;
  /* Torque PID */
  FOC_MTPA_FF_U.MTPA_PID.Up_Limit_torque_PID = SVM_VOLTAGE_LIMIT;
  FOC_MTPA_FF_U.MTPA_PID.Low_Limit_torque_PID = -SVM_VOLTAGE_LIMIT;
  FOC_MTPA_FF_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA = 0.1f;
  FOC_MTPA_FF_U.MTPA_PID.Torque_PID_MTPA.Ki_torque_PID_MTPA = 6.0f;
  FOC_MTPA_FF_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA = 0.00001f;
  FOC_MTPA_FF_U.MTPA_PID.Torque_PID_MTPA.Filter_torque_PID_MTPA = 5.0f;
  /* Flux PID */
  FOC_MTPA_FF_U.MTPA_PID.Up_Limit_flux_PID = SVM_VOLTAGE_LIMIT;
  FOC_MTPA_FF_U.MTPA_PID.Low_Limit_flux_PID = -SVM_VOLTAGE_LIMIT;
  FOC_MTPA_FF_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA = 0.2f;
  FOC_MTPA_FF_U.MTPA_PID.Flux_PID_MTPA.Ki_flux_PID_MTPA = 8.0f;
  FOC_MTPA_FF_U.MTPA_PID.Flux_PID_MTPA.Kd_flux_PID_MTPA = 0.00001f;
  FOC_MTPA_FF_U.MTPA_PID.Flux_PID_MTPA.Filter_flux_PID_MTPA = 5.0f;

  /* Id Iq limits */
  FOC_MTPA_FF_U.Id_Iq_MTPA_limit.Iq_up_limit = 250.0f;
  FOC_MTPA_FF_U.Id_Iq_MTPA_limit.Iq_low_limit = -250.0f;
  FOC_MTPA_FF_U.Id_Iq_MTPA_limit.Id_up_limit = 150.0f;
  FOC_MTPA_FF_U.Id_Iq_MTPA_limit.Id_low_limit = -150.0f;

  /* Speed/Torque Mode setting */
  FOC_MTPA_FF_U.Speed_1_Torque_0 = 1.0f;
  FOC_MTPA_FF_U.RefTrq = 0.0f;

  /* IIR Filter Setting */
  FOC_MTPA_FF_U.IIR_Filter_Coefficient.Iq_Filter_coefficient = 0.9f;
  FOC_MTPA_FF_U.IIR_Filter_Coefficient.Id_Filter_coefficient = 0.9f;
  FOC_MTPA_FF_U.IIR_Filter_Coefficient.Iq_Filter_switch = 1.0f;
  FOC_MTPA_FF_U.IIR_Filter_Coefficient.Id_Filter_switch = 1.0f;

}

/* Model terminate function */
void FOC_MTPA_FF_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
