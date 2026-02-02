/*
 * File: FOC_Basic_FF.c
 *
 * Code generated for Simulink model 'FOC_Basic_FF'.
 *
 * Model version                  : 18.289
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Feb  2 14:22:29 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_Basic_FF.h"
#include <math.h>

/* Block states (default storage) */
DW_FOC_Basic_FF_T FOC_Basic_FF_DW;

/* External inputs (root inport signals with default storage) */
ExtU_FOC_Basic_FF_T FOC_Basic_FF_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_FOC_Basic_FF_T FOC_Basic_FF_Y;

/* Real-time model */
static RT_MODEL_FOC_Basic_FF_T FOC_Basic_FF_M_;
RT_MODEL_FOC_Basic_FF_T *const FOC_Basic_FF_M = &FOC_Basic_FF_M_;

/* Model step function for TID0 */
void FOC_Basic_FF_step0(void)          /* Sample time: [0.0001s, 0.0s] */
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
  float rtb_algDD_o1_d;
  float rtb_algDD_o2_o;

  /* Update the flag to indicate when data transfers from
   *  Sample time: [0.0001s, 0.0s] to Sample time: [0.001s, 0.0s]  */
  (FOC_Basic_FF_M->Timing.RateInteraction.TID0_1)++;
  if ((FOC_Basic_FF_M->Timing.RateInteraction.TID0_1) > 9) {
    FOC_Basic_FF_M->Timing.RateInteraction.TID0_1 = 0;
  }

  /* Switch: '<S130>/Switch2' incorporates:
   *  DataTypeConversion: '<S27>/Data Type Conversion4'
   *  Inport: '<Root>/MTPA_PID'
   */
  FOC_Basic_FF_Y.Vd_PID = FOC_Basic_FF_U.MTPA_PID.Up_Limit_flux_PID;

  /* Outputs for Atomic SubSystem: '<S13>/Two phase CRL wrap' */
  /* Gain: '<S14>/one_by_sqrt3' incorporates:
   *  Inport: '<Root>/Phase Current'
   *  Sum: '<S14>/a_plus_2b'
   */
  rtb_Switch2_d = ((FOC_Basic_FF_U.PhaseCurrent[0] +
                    FOC_Basic_FF_U.PhaseCurrent[1]) +
                   FOC_Basic_FF_U.PhaseCurrent[1]) * 0.57735026918962584;

  /* End of Outputs for SubSystem: '<S13>/Two phase CRL wrap' */

  /* Trigonometry: '<S4>/Trigonometric Function' incorporates:
   *  Inport: '<Root>/angle'
   *  Trigonometry: '<S6>/Trigonometric Function1'
   */
  rtb_Add3 = sin(FOC_Basic_FF_U.MtrElcPos);

  /* Trigonometry: '<S4>/Trigonometric Function1' incorporates:
   *  Inport: '<Root>/angle'
   *  Trigonometry: '<S6>/Trigonometric Function'
   */
  rtb_Add1_l = cos(FOC_Basic_FF_U.MtrElcPos);

  /* Outputs for Atomic SubSystem: '<S12>/Two inputs CRL' */
  /* Outputs for Atomic SubSystem: '<S13>/Two phase CRL wrap' */
  /* AlgorithmDescriptorDelegate generated from: '<S21>/a16' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S14>/a16'
   *  Inport: '<Root>/Phase Current'
   *  Product: '<S21>/acos'
   *  Product: '<S21>/asin'
   *  Product: '<S21>/bcos'
   *  Product: '<S21>/bsin'
   *  Sum: '<S21>/sum_Ds'
   *  Sum: '<S21>/sum_Qs'
   *  Switch: '<S22>/Switch'
   *  Trigonometry: '<S4>/Trigonometric Function'
   *  Trigonometry: '<S4>/Trigonometric Function1'
   */
  rtb_algDD_o1_d = (float)(FOC_Basic_FF_U.PhaseCurrent[0] * rtb_Add1_l +
    rtb_Switch2_d * rtb_Add3);
  rtb_algDD_o2_o = (float)(rtb_Switch2_d * rtb_Add1_l -
    FOC_Basic_FF_U.PhaseCurrent[0] * rtb_Add3);

  /* End of Outputs for SubSystem: '<S13>/Two phase CRL wrap' */
  /* End of Outputs for SubSystem: '<S12>/Two inputs CRL' */

  /* Sum: '<S17>/Add1' incorporates:
   *  Constant: '<S10>/One'
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   *  Product: '<S17>/Product'
   *  Product: '<S17>/Product1'
   *  Sum: '<S10>/Sum'
   *  Switch: '<S10>/Switch1'
   *  UnitDelay: '<S17>/Unit Delay'
   */
  FOC_Basic_FF_DW.UnitDelay_DSTATE = (1.0F -
    FOC_Basic_FF_U.IIR_Filter_Coefficient.Id_Filter_coefficient) *
    FOC_Basic_FF_DW.UnitDelay_DSTATE + rtb_algDD_o1_d *
    FOC_Basic_FF_U.IIR_Filter_Coefficient.Id_Filter_coefficient;

  /* Switch: '<S4>/Switch' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   *  UnitDelay: '<S17>/Unit Delay'
   */
  if (FOC_Basic_FF_U.IIR_Filter_Coefficient.Id_Filter_switch > 0.0F) {
    rtb_Gain_j = FOC_Basic_FF_DW.UnitDelay_DSTATE;
  } else {
    rtb_Gain_j = rtb_algDD_o1_d;
  }

  /* Sum: '<S27>/Sum3' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion'
   *  Inport: '<Root>/Id_ref_in'
   *  Switch: '<S4>/Switch'
   */
  FOC_Basic_FF_Y.Id_error = FOC_Basic_FF_U.Id_ref_in - rtb_Gain_j;

  /* Product: '<S125>/NProd Out' incorporates:
   *  DataTypeConversion: '<S27>/Data Type Conversion2'
   *  DataTypeConversion: '<S27>/Data Type Conversion3'
   *  DiscreteIntegrator: '<S117>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S115>/DProd Out'
   *  Sum: '<S117>/SumD'
   */
  rtb_Switch2_d = (FOC_Basic_FF_Y.Id_error *
                   FOC_Basic_FF_U.MTPA_PID.Flux_PID_MTPA.Kd_flux_PID_MTPA -
                   FOC_Basic_FF_DW.Filter_DSTATE) *
    FOC_Basic_FF_U.MTPA_PID.Flux_PID_MTPA.Filter_flux_PID_MTPA;

  /* Sum: '<S132>/Sum' incorporates:
   *  DataTypeConversion: '<S27>/Data Type Conversion'
   *  DiscreteIntegrator: '<S122>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S127>/PProd Out'
   */
  rtb_Sum = (FOC_Basic_FF_Y.Id_error *
             FOC_Basic_FF_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA +
             FOC_Basic_FF_DW.Integrator_DSTATE) + rtb_Switch2_d;

  /* Switch: '<S130>/Switch2' incorporates:
   *  DataTypeConversion: '<S27>/Data Type Conversion4'
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S130>/LowerRelop1'
   */
  if (!(rtb_Sum > FOC_Basic_FF_U.MTPA_PID.Up_Limit_flux_PID)) {
    /* Switch: '<S130>/Switch' incorporates:
     *  DataTypeConversion: '<S27>/Data Type Conversion5'
     *  RelationalOperator: '<S130>/UpperRelop'
     */
    if (rtb_Sum < FOC_Basic_FF_U.MTPA_PID.Low_Limit_flux_PID) {
      /* Switch: '<S130>/Switch2' */
      FOC_Basic_FF_Y.Vd_PID = FOC_Basic_FF_U.MTPA_PID.Low_Limit_flux_PID;
    } else {
      /* Switch: '<S130>/Switch2' */
      FOC_Basic_FF_Y.Vd_PID = rtb_Sum;
    }

    /* End of Switch: '<S130>/Switch' */
  }

  /* End of Switch: '<S130>/Switch2' */

  /* Gain: '<S5>/Gain' incorporates:
   *  Inport: '<Root>/Bus_Voltage'
   */
  rtb_Gain_j = 0.577350259F * FOC_Basic_FF_U.BusVoltage_V;

  /* RateTransition: '<S2>/Rate Transition' */
  if (FOC_Basic_FF_M->Timing.RateInteraction.TID0_1 == 1) {
    /* Outport: '<Root>/Iq_ref' */
    FOC_Basic_FF_Y.Iq_ref = FOC_Basic_FF_DW.RateTransition_Buffer0;
  }

  /* End of RateTransition: '<S2>/Rate Transition' */

  /* Switch: '<S76>/Switch2' incorporates:
   *  Gain: '<S29>/wm_pu2si_mech2elec'
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   */
  FOC_Basic_FF_Y.Vq_PID = 3.0 * FOC_Basic_FF_U.MtrSpd;

  /* Gain: '<S29>/NegSign' incorporates:
   *  Inport: '<Root>/Lq'
   *  Outport: '<Root>/Iq_ref'
   *  Product: '<S29>/prod1'
   */
  rtb_VdFF_unsat = -(FOC_Basic_FF_U.Lq * FOC_Basic_FF_Y.Iq_ref *
                     FOC_Basic_FF_Y.Vq_PID);

  /* Switch: '<S31>/Switch2' incorporates:
   *  RelationalOperator: '<S31>/LowerRelop1'
   *  RelationalOperator: '<S31>/UpperRelop'
   *  Switch: '<S29>/Switch'
   *  Switch: '<S31>/Switch'
   *  UnaryMinus: '<S29>/Unary Minus'
   */
  if (rtb_VdFF_unsat > rtb_Gain_j) {
    rtb_VdFF_unsat = rtb_Gain_j;
  } else if (rtb_VdFF_unsat < -rtb_Gain_j) {
    /* Switch: '<S31>/Switch' incorporates:
     *  UnaryMinus: '<S29>/Unary Minus'
     */
    rtb_VdFF_unsat = -rtb_Gain_j;
  }

  /* Sum: '<S5>/Add' incorporates:
   *  Switch: '<S31>/Switch2'
   */
  FOC_Basic_FF_Y.Vd = FOC_Basic_FF_Y.Vd_PID + rtb_VdFF_unsat;

  /* Switch: '<S24>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S24>/LowerRelop1'
   *  RelationalOperator: '<S24>/UpperRelop'
   *  Switch: '<S24>/Switch'
   */
  if (FOC_Basic_FF_Y.Vd > FOC_Basic_FF_U.MTPA_PID.Up_Limit_flux_PID) {
    /* Sum: '<S5>/Add' incorporates:
     *  DataTypeConversion: '<S27>/Data Type Conversion4'
     */
    FOC_Basic_FF_Y.Vd = FOC_Basic_FF_U.MTPA_PID.Up_Limit_flux_PID;
  } else if (FOC_Basic_FF_Y.Vd < FOC_Basic_FF_U.MTPA_PID.Low_Limit_flux_PID) {
    /* Sum: '<S5>/Add' incorporates:
     *  Switch: '<S24>/Switch'
     */
    FOC_Basic_FF_Y.Vd = FOC_Basic_FF_U.MTPA_PID.Low_Limit_flux_PID;
  }

  /* End of Switch: '<S24>/Switch2' */

  /* Product: '<S29>/prod2' incorporates:
   *  Inport: '<Root>/Id_ref_in'
   *  Inport: '<Root>/Lambda'
   *  Inport: '<Root>/Ld'
   *  Product: '<S29>/prod3'
   *  Sum: '<S29>/add1'
   */
  rtb_VqFF_unsat = (FOC_Basic_FF_U.Ld * FOC_Basic_FF_U.Id_ref_in +
                    FOC_Basic_FF_U.Lambda) * FOC_Basic_FF_Y.Vq_PID;

  /* Switch: '<S76>/Switch2' incorporates:
   *  DataTypeConversion: '<S26>/Data Type Conversion10'
   *  Inport: '<Root>/MTPA_PID'
   */
  FOC_Basic_FF_Y.Vq_PID = FOC_Basic_FF_U.MTPA_PID.Up_Limit_torque_PID;

  /* Sum: '<S20>/Add1' incorporates:
   *  Constant: '<S11>/One'
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   *  Product: '<S20>/Product'
   *  Product: '<S20>/Product1'
   *  Sum: '<S11>/Sum'
   *  Switch: '<S11>/Switch1'
   *  UnitDelay: '<S20>/Unit Delay'
   */
  FOC_Basic_FF_DW.UnitDelay_DSTATE_f = (1.0F -
    FOC_Basic_FF_U.IIR_Filter_Coefficient.Iq_Filter_coefficient) *
    FOC_Basic_FF_DW.UnitDelay_DSTATE_f + rtb_algDD_o2_o *
    FOC_Basic_FF_U.IIR_Filter_Coefficient.Iq_Filter_coefficient;

  /* Switch: '<S4>/Switch1' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   */
  if (FOC_Basic_FF_U.IIR_Filter_Coefficient.Iq_Filter_switch > 0.0F) {
    rtb_algDD_o2_o = FOC_Basic_FF_DW.UnitDelay_DSTATE_f;
  }

  /* End of Switch: '<S4>/Switch1' */

  /* Sum: '<S26>/Sum2' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion1'
   *  Outport: '<Root>/Iq_ref'
   */
  FOC_Basic_FF_Y.Iq_error = FOC_Basic_FF_Y.Iq_ref - rtb_algDD_o2_o;

  /* Product: '<S71>/NProd Out' incorporates:
   *  DataTypeConversion: '<S26>/Data Type Conversion8'
   *  DataTypeConversion: '<S26>/Data Type Conversion9'
   *  DiscreteIntegrator: '<S63>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S61>/DProd Out'
   *  Sum: '<S63>/SumD'
   */
  rtb_VdFF_unsat = (FOC_Basic_FF_Y.Iq_error *
                    FOC_Basic_FF_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA -
                    FOC_Basic_FF_DW.Filter_DSTATE_d) *
    FOC_Basic_FF_U.MTPA_PID.Torque_PID_MTPA.Filter_torque_PID_MTPA;

  /* Sum: '<S78>/Sum' incorporates:
   *  DataTypeConversion: '<S26>/Data Type Conversion6'
   *  DiscreteIntegrator: '<S68>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S73>/PProd Out'
   */
  rtb_Sum_f = (FOC_Basic_FF_Y.Iq_error *
               FOC_Basic_FF_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA +
               FOC_Basic_FF_DW.Integrator_DSTATE_h) + rtb_VdFF_unsat;

  /* Switch: '<S76>/Switch2' incorporates:
   *  DataTypeConversion: '<S26>/Data Type Conversion10'
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S76>/LowerRelop1'
   */
  if (!(rtb_Sum_f > FOC_Basic_FF_U.MTPA_PID.Up_Limit_torque_PID)) {
    /* Switch: '<S76>/Switch' incorporates:
     *  DataTypeConversion: '<S26>/Data Type Conversion11'
     *  RelationalOperator: '<S76>/UpperRelop'
     */
    if (rtb_Sum_f < FOC_Basic_FF_U.MTPA_PID.Low_Limit_torque_PID) {
      /* Switch: '<S76>/Switch2' */
      FOC_Basic_FF_Y.Vq_PID = FOC_Basic_FF_U.MTPA_PID.Low_Limit_torque_PID;
    } else {
      /* Switch: '<S76>/Switch2' */
      FOC_Basic_FF_Y.Vq_PID = rtb_Sum_f;
    }

    /* End of Switch: '<S76>/Switch' */
  }

  /* End of Switch: '<S76>/Switch2' */

  /* Switch: '<S32>/Switch2' incorporates:
   *  RelationalOperator: '<S32>/LowerRelop1'
   *  RelationalOperator: '<S32>/UpperRelop'
   *  Switch: '<S29>/Switch'
   *  Switch: '<S32>/Switch'
   *  UnaryMinus: '<S29>/Unary Minus'
   */
  if (rtb_VqFF_unsat > rtb_Gain_j) {
    rtb_VqFF_unsat = rtb_Gain_j;
  } else if (rtb_VqFF_unsat < -rtb_Gain_j) {
    /* Switch: '<S32>/Switch' incorporates:
     *  UnaryMinus: '<S29>/Unary Minus'
     */
    rtb_VqFF_unsat = -rtb_Gain_j;
  }

  /* Sum: '<S5>/Add1' incorporates:
   *  Switch: '<S32>/Switch2'
   */
  FOC_Basic_FF_Y.Vq = rtb_VqFF_unsat + FOC_Basic_FF_Y.Vq_PID;

  /* Switch: '<S25>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S25>/LowerRelop1'
   *  RelationalOperator: '<S25>/UpperRelop'
   *  Switch: '<S25>/Switch'
   */
  if (FOC_Basic_FF_Y.Vq > FOC_Basic_FF_U.MTPA_PID.Up_Limit_torque_PID) {
    /* Sum: '<S5>/Add1' incorporates:
     *  DataTypeConversion: '<S26>/Data Type Conversion10'
     */
    FOC_Basic_FF_Y.Vq = FOC_Basic_FF_U.MTPA_PID.Up_Limit_torque_PID;
  } else if (FOC_Basic_FF_Y.Vq < FOC_Basic_FF_U.MTPA_PID.Low_Limit_torque_PID) {
    /* Sum: '<S5>/Add1' incorporates:
     *  Switch: '<S25>/Switch'
     */
    FOC_Basic_FF_Y.Vq = FOC_Basic_FF_U.MTPA_PID.Low_Limit_torque_PID;
  }

  /* End of Switch: '<S25>/Switch2' */

  /* Outputs for Atomic SubSystem: '<S142>/Two inputs CRL' */
  /* Switch: '<S146>/Switch' incorporates:
   *  Product: '<S145>/dcos'
   *  Product: '<S145>/qsin'
   *  Sum: '<S145>/sum_alpha'
   */
  rtb_Switch_f_idx_0 = FOC_Basic_FF_Y.Vd * rtb_Add1_l - FOC_Basic_FF_Y.Vq *
    rtb_Add3;

  /* Gain: '<S144>/one_by_two' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S145>/a16'
   */
  rtb_VqFF_unsat = 0.5 * rtb_Switch_f_idx_0;

  /* Gain: '<S144>/sqrt3_by_two' incorporates:
   *  Product: '<S145>/dsin'
   *  Product: '<S145>/qcos'
   *  Sum: '<S145>/sum_beta'
   */
  rtb_Add3 = (FOC_Basic_FF_Y.Vq * rtb_Add1_l + FOC_Basic_FF_Y.Vd * rtb_Add3) *
    0.8660254037844386;

  /* End of Outputs for SubSystem: '<S142>/Two inputs CRL' */

  /* Sum: '<S144>/add_b' */
  rtb_Add1_l = rtb_Add3 - rtb_VqFF_unsat;

  /* Sum: '<S144>/add_c' */
  rtb_VqFF_unsat = (0.0 - rtb_VqFF_unsat) - rtb_Add3;

  /* Outputs for Atomic SubSystem: '<S142>/Two inputs CRL' */
  /* Gain: '<S150>/one_by_two' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S145>/a16'
   *  MinMax: '<S150>/Max'
   *  MinMax: '<S150>/Min'
   *  Sum: '<S150>/Add'
   */
  rtb_Add3 = (fmax(fmax(rtb_Switch_f_idx_0, rtb_Add1_l), rtb_VqFF_unsat) + fmin
              (fmin(rtb_Switch_f_idx_0, rtb_Add1_l), rtb_VqFF_unsat)) * -0.5;

  /* Outport: '<Root>/Va' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S145>/a16'
   *  Gain: '<S149>/Gain'
   *  Sum: '<S149>/Add3'
   */
  FOC_Basic_FF_Y.Va = (rtb_Switch_f_idx_0 + rtb_Add3) * 1.1547005383792517;

  /* End of Outputs for SubSystem: '<S142>/Two inputs CRL' */

  /* Outport: '<Root>/Vb' incorporates:
   *  Gain: '<S149>/Gain'
   *  Sum: '<S149>/Add1'
   */
  FOC_Basic_FF_Y.Vb = (rtb_Add1_l + rtb_Add3) * 1.1547005383792517;

  /* Outport: '<Root>/Vc' incorporates:
   *  Gain: '<S149>/Gain'
   *  Sum: '<S149>/Add2'
   */
  FOC_Basic_FF_Y.Vc = (rtb_Add3 + rtb_VqFF_unsat) * 1.1547005383792517;

  /* Outport: '<Root>/Iq' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion1'
   */
  FOC_Basic_FF_Y.Iq = rtb_algDD_o2_o;

  /* Switch: '<S4>/Switch' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   */
  if (FOC_Basic_FF_U.IIR_Filter_Coefficient.Id_Filter_switch > 0.0F) {
    /* Outport: '<Root>/Id' incorporates:
     *  UnitDelay: '<S17>/Unit Delay'
     */
    FOC_Basic_FF_Y.Id = FOC_Basic_FF_DW.UnitDelay_DSTATE;
  } else {
    /* Outport: '<Root>/Id' */
    FOC_Basic_FF_Y.Id = rtb_algDD_o1_d;
  }

  /* Product: '<S3>/delta rise limit' incorporates:
   *  Inport: '<Root>/Ref_Speed_rate_up'
   *  SampleTimeMath: '<S3>/sample time'
   *
   * About '<S3>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_Add3 = FOC_Basic_FF_U.Ref_Speed_rate_up * 0.0001;

  /* Delay: '<S3>/Delay' */
  if (FOC_Basic_FF_DW.icLoad) {
    /* Sum: '<S3>/Difference Inputs2' incorporates:
     *  Inport: '<Root>/Ref_Speed_mech_rpm'
     *
     * Block description for '<S3>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_Basic_FF_DW.Delay_DSTATE = FOC_Basic_FF_U.Ref_Speed_mech_rpm;
  }

  /* Sum: '<S3>/Difference Inputs1' incorporates:
   *  Delay: '<S3>/Delay'
   *  Inport: '<Root>/Ref_Speed_mech_rpm'
   *
   * Block description for '<S3>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_VqFF_unsat = FOC_Basic_FF_U.Ref_Speed_mech_rpm -
    FOC_Basic_FF_DW.Delay_DSTATE;

  /* Switch: '<S207>/Switch2' incorporates:
   *  RelationalOperator: '<S207>/LowerRelop1'
   */
  if (!(rtb_VqFF_unsat > rtb_Add3)) {
    /* Product: '<S3>/delta fall limit' incorporates:
     *  Inport: '<Root>/Ref_Speed_rate_down'
     *  SampleTimeMath: '<S3>/sample time'
     *
     * About '<S3>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_Add3 = 0.0001 * FOC_Basic_FF_U.Ref_Speed_rate_down;

    /* Switch: '<S207>/Switch' incorporates:
     *  RelationalOperator: '<S207>/UpperRelop'
     */
    if (!(rtb_VqFF_unsat < rtb_Add3)) {
      rtb_Add3 = rtb_VqFF_unsat;
    }

    /* End of Switch: '<S207>/Switch' */
  }

  /* End of Switch: '<S207>/Switch2' */

  /* Sum: '<S3>/Difference Inputs2' incorporates:
   *  Delay: '<S3>/Delay'
   *
   * Block description for '<S3>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_Basic_FF_DW.Delay_DSTATE += rtb_Add3;

  /* Outport: '<Root>/Speed_error' incorporates:
   *  Gain: '<S1>/rpm to Rad//sec'
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   *  Sum: '<S8>/Subtract'
   */
  FOC_Basic_FF_Y.Speed_error = 0.10471975511965977 *
    FOC_Basic_FF_DW.Delay_DSTATE - FOC_Basic_FF_U.MtrSpd;

  /* Outport: '<Root>/Id_ref' incorporates:
   *  Inport: '<Root>/Id_ref_in'
   */
  FOC_Basic_FF_Y.Id_ref = FOC_Basic_FF_U.Id_ref_in;

  /* Update for DiscreteIntegrator: '<S122>/Integrator' incorporates:
   *  DataTypeConversion: '<S27>/Data Type Conversion1'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S119>/IProd Out'
   *  Sum: '<S114>/SumI2'
   *  Sum: '<S114>/SumI4'
   *  Sum: '<S134>/SumI3'
   *  Sum: '<S135>/SumI1'
   */
  FOC_Basic_FF_DW.Integrator_DSTATE += ((FOC_Basic_FF_Y.Id_error *
    FOC_Basic_FF_U.MTPA_PID.Flux_PID_MTPA.Ki_flux_PID_MTPA +
    (FOC_Basic_FF_Y.Vd_PID - FOC_Basic_FF_Y.Vd_PID)) + (FOC_Basic_FF_Y.Vd_PID -
    rtb_Sum)) * 0.0001;
  if (FOC_Basic_FF_DW.Integrator_DSTATE > 58.0) {
    FOC_Basic_FF_DW.Integrator_DSTATE = 58.0;
  } else if (FOC_Basic_FF_DW.Integrator_DSTATE < -58.0) {
    FOC_Basic_FF_DW.Integrator_DSTATE = -58.0;
  }

  /* End of Update for DiscreteIntegrator: '<S122>/Integrator' */

  /* Update for DiscreteIntegrator: '<S117>/Filter' */
  FOC_Basic_FF_DW.Filter_DSTATE += 0.0001 * rtb_Switch2_d;

  /* Update for DiscreteIntegrator: '<S68>/Integrator' incorporates:
   *  DataTypeConversion: '<S26>/Data Type Conversion7'
   *  Gain: '<S80>/Kt'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S65>/IProd Out'
   *  Sum: '<S60>/SumI2'
   *  Sum: '<S60>/SumI4'
   *  Sum: '<S80>/SumI3'
   *  Sum: '<S81>/SumI1'
   */
  FOC_Basic_FF_DW.Integrator_DSTATE_h += (((FOC_Basic_FF_Y.Vq_PID -
    FOC_Basic_FF_Y.Vq_PID) * -10.0 + FOC_Basic_FF_Y.Iq_error *
    FOC_Basic_FF_U.MTPA_PID.Torque_PID_MTPA.Ki_torque_PID_MTPA) +
    (FOC_Basic_FF_Y.Vq_PID - rtb_Sum_f)) * 0.0001;
  if (FOC_Basic_FF_DW.Integrator_DSTATE_h > 58.0) {
    FOC_Basic_FF_DW.Integrator_DSTATE_h = 58.0;
  } else if (FOC_Basic_FF_DW.Integrator_DSTATE_h < -58.0) {
    FOC_Basic_FF_DW.Integrator_DSTATE_h = -58.0;
  }

  /* End of Update for DiscreteIntegrator: '<S68>/Integrator' */

  /* Update for DiscreteIntegrator: '<S63>/Filter' */
  FOC_Basic_FF_DW.Filter_DSTATE_d += 0.0001 * rtb_VdFF_unsat;

  /* Update for Delay: '<S3>/Delay' */
  FOC_Basic_FF_DW.icLoad = false;
}

/* Model step function for TID1 */
void FOC_Basic_FF_step1(void)          /* Sample time: [0.001s, 0.0s] */
{
  double rtb_NProdOut_j;
  double rtb_Sum;
  double rtb_UkYk1_l;
  double rtb_deltafalllimit_d;

  /* Product: '<S191>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S183>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S181>/DProd Out'
   *  Sum: '<S183>/SumD'
   */
  rtb_NProdOut_j = (FOC_Basic_FF_Y.Speed_error *
                    FOC_Basic_FF_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA -
                    FOC_Basic_FF_DW.Filter_DSTATE_i) *
    FOC_Basic_FF_U.MTPA_PID.Speed_PID_MTPA.Filter_speed_PID_MTPA;

  /* Sum: '<S198>/Sum' incorporates:
   *  DiscreteIntegrator: '<S188>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S193>/PProd Out'
   */
  rtb_Sum = (FOC_Basic_FF_Y.Speed_error *
             FOC_Basic_FF_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA +
             FOC_Basic_FF_DW.Integrator_DSTATE_b) + rtb_NProdOut_j;

  /* Switch: '<S196>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S196>/LowerRelop1'
   *  RelationalOperator: '<S196>/UpperRelop'
   *  Switch: '<S196>/Switch'
   */
  if (rtb_Sum > FOC_Basic_FF_U.MTPA_PID.Up_Limit_speed_PID_MTPA) {
    /* Switch: '<S196>/Switch2' */
    FOC_Basic_FF_Y.Iq_gen = FOC_Basic_FF_U.MTPA_PID.Up_Limit_speed_PID_MTPA;
  } else if (rtb_Sum < FOC_Basic_FF_U.MTPA_PID.Low_Limit_speed_PID_MTPA) {
    /* Switch: '<S196>/Switch2' incorporates:
     *  Switch: '<S196>/Switch'
     */
    FOC_Basic_FF_Y.Iq_gen = FOC_Basic_FF_U.MTPA_PID.Low_Limit_speed_PID_MTPA;
  } else {
    /* Switch: '<S196>/Switch2' incorporates:
     *  Switch: '<S196>/Switch'
     */
    FOC_Basic_FF_Y.Iq_gen = rtb_Sum;
  }

  /* End of Switch: '<S196>/Switch2' */

  /* Delay: '<S7>/Delay' */
  if (FOC_Basic_FF_DW.icLoad_p) {
    /* Sum: '<S7>/Difference Inputs2'
     *
     * Block description for '<S7>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_Basic_FF_DW.Delay_DSTATE_h = FOC_Basic_FF_Y.Iq_gen;
  }

  /* Sum: '<S7>/Difference Inputs1' incorporates:
   *  Delay: '<S7>/Delay'
   *
   * Block description for '<S7>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_UkYk1_l = FOC_Basic_FF_Y.Iq_gen - FOC_Basic_FF_DW.Delay_DSTATE_h;

  /* Product: '<S7>/delta rise limit' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  SampleTimeMath: '<S7>/sample time'
   *
   * About '<S7>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_deltafalllimit_d = FOC_Basic_FF_U.Rate_limiter.Torque_gen_ramp_up * 0.001;

  /* Switch: '<S152>/Switch2' incorporates:
   *  RelationalOperator: '<S152>/LowerRelop1'
   */
  if (!(rtb_UkYk1_l > rtb_deltafalllimit_d)) {
    /* Product: '<S7>/delta fall limit' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  SampleTimeMath: '<S7>/sample time'
     *
     * About '<S7>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_deltafalllimit_d = 0.001 *
      FOC_Basic_FF_U.Rate_limiter.Torque_gen_ramp_down;

    /* Switch: '<S152>/Switch' incorporates:
     *  RelationalOperator: '<S152>/UpperRelop'
     */
    if (!(rtb_UkYk1_l < rtb_deltafalllimit_d)) {
      rtb_deltafalllimit_d = rtb_UkYk1_l;
    }

    /* End of Switch: '<S152>/Switch' */
  }

  /* End of Switch: '<S152>/Switch2' */

  /* Sum: '<S7>/Difference Inputs2' incorporates:
   *  Delay: '<S7>/Delay'
   *
   * Block description for '<S7>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_Basic_FF_DW.Delay_DSTATE_h += rtb_deltafalllimit_d;

  /* RateTransition: '<S2>/Rate Transition' */
  FOC_Basic_FF_DW.RateTransition_Buffer0 = FOC_Basic_FF_DW.Delay_DSTATE_h;

  /* Update for DiscreteIntegrator: '<S188>/Integrator' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S185>/IProd Out'
   *  Sum: '<S180>/SumI2'
   *  Sum: '<S180>/SumI4'
   *  Sum: '<S200>/SumI3'
   *  Sum: '<S201>/SumI1'
   */
  FOC_Basic_FF_DW.Integrator_DSTATE_b += ((FOC_Basic_FF_Y.Speed_error *
    FOC_Basic_FF_U.MTPA_PID.Speed_PID_MTPA.Ki_speed_PID_MTPA +
    (FOC_Basic_FF_Y.Iq_gen - FOC_Basic_FF_Y.Iq_gen)) + (FOC_Basic_FF_Y.Iq_gen -
    rtb_Sum)) * 0.001;
  if (FOC_Basic_FF_DW.Integrator_DSTATE_b > 500.0) {
    FOC_Basic_FF_DW.Integrator_DSTATE_b = 500.0;
  } else if (FOC_Basic_FF_DW.Integrator_DSTATE_b < -500.0) {
    FOC_Basic_FF_DW.Integrator_DSTATE_b = -500.0;
  }

  /* End of Update for DiscreteIntegrator: '<S188>/Integrator' */

  /* Update for DiscreteIntegrator: '<S183>/Filter' */
  FOC_Basic_FF_DW.Filter_DSTATE_i += 0.001 * rtb_NProdOut_j;

  /* Update for Delay: '<S7>/Delay' */
  FOC_Basic_FF_DW.icLoad_p = false;
}

/* Model initialize function */
void FOC_Basic_FF_initialize(void)
{
  /* InitializeConditions for Delay: '<S3>/Delay' */
  FOC_Basic_FF_DW.icLoad = true;

  /* InitializeConditions for Delay: '<S7>/Delay' */
  FOC_Basic_FF_DW.icLoad_p = true;

  FOC_Basic_FF_U.BusVoltage_V = OP_VOLTAGE;
  FOC_Basic_FF_U.Lambda = LAMBDA;
  FOC_Basic_FF_U.Ld = LD;
  FOC_Basic_FF_U.Lq = LQ;

    /* Rate limiter settings */
  FOC_Basic_FF_U.Ref_Speed_rate_up = 0.1f * 10000.0f;
  FOC_Basic_FF_U.Ref_Speed_rate_down = -10.0f * 10000.0f;
  FOC_Basic_FF_U.Rate_limiter.Torque_gen_ramp_up = 100.0f * 10000.0f;
  FOC_Basic_FF_U.Rate_limiter.Torque_gen_ramp_down = -100.0f * 10000.0f;

  //not used
  FOC_Basic_FF_U.Rate_limiter.Iq_ramp_up = 50.0f * 10000.0f;
  FOC_Basic_FF_U.Rate_limiter.Iq_ramp_down = -50.0f * 10000.0f;
  FOC_Basic_FF_U.Rate_limiter.Id_ramp_up = 10.0f * 10000.0f;
  FOC_Basic_FF_U.Rate_limiter.Id_ramp_down = -120.0f * 10000.0f;
  //not used

  /* IIR Filter Settings */
  FOC_Basic_FF_U.IIR_Filter_Coefficient.Id_Filter_switch = 1.0f;
  FOC_Basic_FF_U.IIR_Filter_Coefficient.Iq_Filter_switch = 1.0f;
  FOC_Basic_FF_U.IIR_Filter_Coefficient.Id_Filter_coefficient = 0.9f;
  FOC_Basic_FF_U.IIR_Filter_Coefficient.Iq_Filter_coefficient = 0.9f;

  /* PID Values */
  FOC_Basic_FF_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA = 5.0f;
  FOC_Basic_FF_U.MTPA_PID.Speed_PID_MTPA.Ki_speed_PID_MTPA = 9.0f;
  FOC_Basic_FF_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA = 0.00001;
  FOC_Basic_FF_U.MTPA_PID.Speed_PID_MTPA.Filter_speed_PID_MTPA = 10.0f;

  FOC_Basic_FF_U.MTPA_PID.Up_Limit_speed_PID_MTPA = 500.0f;
  FOC_Basic_FF_U.MTPA_PID.Low_Limit_speed_PID_MTPA = 0.0f;

  FOC_Basic_FF_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA = 0.2f;
  FOC_Basic_FF_U.MTPA_PID.Torque_PID_MTPA.Ki_torque_PID_MTPA = 5.0f;
  FOC_Basic_FF_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA = 0.0001f;
  FOC_Basic_FF_U.MTPA_PID.Torque_PID_MTPA.Filter_torque_PID_MTPA = 10.0f;

  FOC_Basic_FF_U.MTPA_PID.Up_Limit_torque_PID = SVM_VOLTAGE_LIMIT;
  FOC_Basic_FF_U.MTPA_PID.Low_Limit_torque_PID = -SVM_VOLTAGE_LIMIT;

  FOC_Basic_FF_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA = 0.3f;
  FOC_Basic_FF_U.MTPA_PID.Flux_PID_MTPA.Ki_flux_PID_MTPA = 6.0f;
  FOC_Basic_FF_U.MTPA_PID.Flux_PID_MTPA.Kd_flux_PID_MTPA = 0.0001f;
  FOC_Basic_FF_U.MTPA_PID.Flux_PID_MTPA.Filter_flux_PID_MTPA = 10.0f;

  FOC_Basic_FF_U.MTPA_PID.Up_Limit_flux_PID = SVM_VOLTAGE_LIMIT;
  FOC_Basic_FF_U.MTPA_PID.Low_Limit_flux_PID = -SVM_VOLTAGE_LIMIT;

  FOC_Basic_FF_U.Id_ref_in = 0.0f;
}

/* Model terminate function */
void FOC_Basic_FF_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
