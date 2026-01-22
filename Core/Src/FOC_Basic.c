/*
 * File: FOC_Basic.c
 *
 * Code generated for Simulink model 'FOC_Basic'.
 *
 * Model version                  : 18.281
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Jan 19 14:26:00 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_Basic.h"
#include <math.h>

/* Block states (default storage) */
DW_FOC_Basic_T FOC_Basic_DW;

/* External inputs (root inport signals with default storage) */
ExtU_FOC_Basic_T FOC_Basic_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_FOC_Basic_T FOC_Basic_Y;

/* Real-time model */
static RT_MODEL_FOC_Basic_T FOC_Basic_M_;
RT_MODEL_FOC_Basic_T *const FOC_Basic_M = &FOC_Basic_M_;

/* Model step function for TID0 */
void FOC_Basic_step0(void)             /* Sample time: [0.0001s, 0.0s] */
{
  double rtb_Add1;
  double rtb_Add3;
  double rtb_NProdOut_l;
  double rtb_Sum;
  double rtb_Sum_f;
  double rtb_Switch2_d;
  double rtb_Switch_f_idx_0;
  double rtb_add_c;
  float rtb_algDD_o1_d;
  float rtb_algDD_o2_o;
  float tmp;

  /* Update the flag to indicate when data transfers from
   *  Sample time: [0.0001s, 0.0s] to Sample time: [0.001s, 0.0s]  */
  (FOC_Basic_M->Timing.RateInteraction.TID0_1)++;
  if ((FOC_Basic_M->Timing.RateInteraction.TID0_1) > 9) {
    FOC_Basic_M->Timing.RateInteraction.TID0_1 = 0;
  }

  /* Outputs for Atomic SubSystem: '<S13>/Two phase CRL wrap' */
  /* Gain: '<S14>/one_by_sqrt3' incorporates:
   *  Inport: '<Root>/Phase Current'
   *  Sum: '<S14>/a_plus_2b'
   */
  rtb_Switch2_d = ((FOC_Basic_U.PhaseCurrent[0] + FOC_Basic_U.PhaseCurrent[1]) +
                   FOC_Basic_U.PhaseCurrent[1]) * 0.57735026918962584;

  /* End of Outputs for SubSystem: '<S13>/Two phase CRL wrap' */

  /* Trigonometry: '<S4>/Trigonometric Function' incorporates:
   *  Inport: '<Root>/angle'
   *  Trigonometry: '<S6>/Trigonometric Function1'
   */
  rtb_Add3 = sin(FOC_Basic_U.MtrElcPos);

  /* Trigonometry: '<S4>/Trigonometric Function1' incorporates:
   *  Inport: '<Root>/angle'
   *  Trigonometry: '<S6>/Trigonometric Function'
   */
  rtb_Add1 = cos(FOC_Basic_U.MtrElcPos);

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
  rtb_algDD_o1_d = (float)(FOC_Basic_U.PhaseCurrent[0] * rtb_Add1 +
    rtb_Switch2_d * rtb_Add3);
  rtb_algDD_o2_o = (float)(rtb_Switch2_d * rtb_Add1 - FOC_Basic_U.PhaseCurrent[0]
    * rtb_Add3);

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
  FOC_Basic_DW.UnitDelay_DSTATE = (1.0F -
    FOC_Basic_U.IIR_Filter_Coefficient.Id_Filter_coefficient) *
    FOC_Basic_DW.UnitDelay_DSTATE + rtb_algDD_o1_d *
    FOC_Basic_U.IIR_Filter_Coefficient.Id_Filter_coefficient;

  /* Switch: '<S4>/Switch' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   *  UnitDelay: '<S17>/Unit Delay'
   */
  if (FOC_Basic_U.IIR_Filter_Coefficient.Id_Filter_switch > 0.0F) {
    tmp = FOC_Basic_DW.UnitDelay_DSTATE;
  } else {
    tmp = rtb_algDD_o1_d;
  }

  /* Sum: '<S26>/Sum3' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion'
   *  Inport: '<Root>/Id_ref_in'
   *  Switch: '<S4>/Switch'
   */
  FOC_Basic_Y.Id_error = FOC_Basic_U.Id_ref_in - tmp;

  /* Product: '<S119>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S111>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S109>/DProd Out'
   *  Sum: '<S111>/SumD'
   */
  rtb_Switch2_d = (FOC_Basic_Y.Id_error *
                   FOC_Basic_U.MTPA_PID.Flux_PID_MTPA.Kd_flux_PID_MTPA -
                   FOC_Basic_DW.Filter_DSTATE) *
    FOC_Basic_U.MTPA_PID.Flux_PID_MTPA.Filter_flux_PID_MTPA;

  /* Sum: '<S126>/Sum' incorporates:
   *  DiscreteIntegrator: '<S116>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S121>/PProd Out'
   */
  rtb_Sum = (FOC_Basic_Y.Id_error *
             FOC_Basic_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA +
             FOC_Basic_DW.Integrator_DSTATE) + rtb_Switch2_d;

  /* Switch: '<S124>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S124>/LowerRelop1'
   *  RelationalOperator: '<S124>/UpperRelop'
   *  Switch: '<S124>/Switch'
   */
  if (rtb_Sum > FOC_Basic_U.MTPA_PID.Up_Limit_flux_PID) {
    /* Switch: '<S124>/Switch2' */
    FOC_Basic_Y.Vd_PID = FOC_Basic_U.MTPA_PID.Up_Limit_flux_PID;
  } else if (rtb_Sum < FOC_Basic_U.MTPA_PID.Low_Limit_flux_PID) {
    /* Switch: '<S124>/Switch2' incorporates:
     *  Switch: '<S124>/Switch'
     */
    FOC_Basic_Y.Vd_PID = FOC_Basic_U.MTPA_PID.Low_Limit_flux_PID;
  } else {
    /* Switch: '<S124>/Switch2' incorporates:
     *  Switch: '<S124>/Switch'
     */
    FOC_Basic_Y.Vd_PID = rtb_Sum;
  }

  /* End of Switch: '<S124>/Switch2' */

  /* Switch: '<S23>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S23>/LowerRelop1'
   *  RelationalOperator: '<S23>/UpperRelop'
   *  Switch: '<S23>/Switch'
   */
  if (FOC_Basic_Y.Vd_PID > FOC_Basic_U.MTPA_PID.Up_Limit_flux_PID) {
    /* Switch: '<S23>/Switch2' */
    FOC_Basic_Y.Vd = FOC_Basic_U.MTPA_PID.Up_Limit_flux_PID;
  } else if (FOC_Basic_Y.Vd_PID < FOC_Basic_U.MTPA_PID.Low_Limit_flux_PID) {
    /* Switch: '<S23>/Switch2' incorporates:
     *  Switch: '<S23>/Switch'
     */
    FOC_Basic_Y.Vd = FOC_Basic_U.MTPA_PID.Low_Limit_flux_PID;
  } else {
    /* Switch: '<S23>/Switch2' incorporates:
     *  Switch: '<S23>/Switch'
     */
    FOC_Basic_Y.Vd = FOC_Basic_Y.Vd_PID;
  }

  /* End of Switch: '<S23>/Switch2' */

  /* RateTransition: '<S2>/Rate Transition' */
  if (FOC_Basic_M->Timing.RateInteraction.TID0_1 == 1) {
    /* Outport: '<Root>/Iq_ref' */
    FOC_Basic_Y.Iq_ref = FOC_Basic_DW.RateTransition_Buffer0;
  }

  /* End of RateTransition: '<S2>/Rate Transition' */

  /* Sum: '<S20>/Add1' incorporates:
   *  Constant: '<S11>/One'
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   *  Product: '<S20>/Product'
   *  Product: '<S20>/Product1'
   *  Sum: '<S11>/Sum'
   *  Switch: '<S11>/Switch1'
   *  UnitDelay: '<S20>/Unit Delay'
   */
  FOC_Basic_DW.UnitDelay_DSTATE_f = (1.0F -
    FOC_Basic_U.IIR_Filter_Coefficient.Iq_Filter_coefficient) *
    FOC_Basic_DW.UnitDelay_DSTATE_f + rtb_algDD_o2_o *
    FOC_Basic_U.IIR_Filter_Coefficient.Iq_Filter_coefficient;

  /* Switch: '<S4>/Switch1' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   */
  if (FOC_Basic_U.IIR_Filter_Coefficient.Iq_Filter_switch > 0.0F) {
    rtb_algDD_o2_o = FOC_Basic_DW.UnitDelay_DSTATE_f;
  }

  /* End of Switch: '<S4>/Switch1' */

  /* Sum: '<S25>/Sum2' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion1'
   *  Outport: '<Root>/Iq_ref'
   */
  FOC_Basic_Y.Iq_error = FOC_Basic_Y.Iq_ref - rtb_algDD_o2_o;

  /* Product: '<S65>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S57>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S55>/DProd Out'
   *  Sum: '<S57>/SumD'
   */
  rtb_NProdOut_l = (FOC_Basic_Y.Iq_error *
                    FOC_Basic_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA -
                    FOC_Basic_DW.Filter_DSTATE_d) *
    FOC_Basic_U.MTPA_PID.Torque_PID_MTPA.Filter_torque_PID_MTPA;

  /* Sum: '<S72>/Sum' incorporates:
   *  DiscreteIntegrator: '<S62>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S67>/PProd Out'
   */
  rtb_Sum_f = (FOC_Basic_Y.Iq_error *
               FOC_Basic_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA +
               FOC_Basic_DW.Integrator_DSTATE_h) + rtb_NProdOut_l;

  /* Switch: '<S70>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S70>/LowerRelop1'
   *  RelationalOperator: '<S70>/UpperRelop'
   *  Switch: '<S70>/Switch'
   */
  if (rtb_Sum_f > FOC_Basic_U.MTPA_PID.Up_Limit_torque_PID) {
    /* Switch: '<S70>/Switch2' */
    FOC_Basic_Y.Vq_PID = FOC_Basic_U.MTPA_PID.Up_Limit_torque_PID;
  } else if (rtb_Sum_f < FOC_Basic_U.MTPA_PID.Low_Limit_torque_PID) {
    /* Switch: '<S70>/Switch2' incorporates:
     *  Switch: '<S70>/Switch'
     */
    FOC_Basic_Y.Vq_PID = FOC_Basic_U.MTPA_PID.Low_Limit_torque_PID;
  } else {
    /* Switch: '<S70>/Switch2' incorporates:
     *  Switch: '<S70>/Switch'
     */
    FOC_Basic_Y.Vq_PID = rtb_Sum_f;
  }

  /* End of Switch: '<S70>/Switch2' */

  /* Switch: '<S24>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S24>/LowerRelop1'
   *  RelationalOperator: '<S24>/UpperRelop'
   *  Switch: '<S24>/Switch'
   */
  if (FOC_Basic_Y.Vq_PID > FOC_Basic_U.MTPA_PID.Up_Limit_torque_PID) {
    /* Switch: '<S24>/Switch2' */
    FOC_Basic_Y.Vq = FOC_Basic_U.MTPA_PID.Up_Limit_torque_PID;
  } else if (FOC_Basic_Y.Vq_PID < FOC_Basic_U.MTPA_PID.Low_Limit_torque_PID) {
    /* Switch: '<S24>/Switch2' incorporates:
     *  Switch: '<S24>/Switch'
     */
    FOC_Basic_Y.Vq = FOC_Basic_U.MTPA_PID.Low_Limit_torque_PID;
  } else {
    /* Switch: '<S24>/Switch2' incorporates:
     *  Switch: '<S24>/Switch'
     */
    FOC_Basic_Y.Vq = FOC_Basic_Y.Vq_PID;
  }

  /* End of Switch: '<S24>/Switch2' */

  /* Outputs for Atomic SubSystem: '<S136>/Two inputs CRL' */
  /* Switch: '<S140>/Switch' incorporates:
   *  Product: '<S139>/dcos'
   *  Product: '<S139>/qsin'
   *  Sum: '<S139>/sum_alpha'
   */
  rtb_Switch_f_idx_0 = FOC_Basic_Y.Vd * rtb_Add1 - FOC_Basic_Y.Vq * rtb_Add3;

  /* Gain: '<S138>/one_by_two' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S139>/a16'
   */
  rtb_add_c = 0.5 * rtb_Switch_f_idx_0;

  /* Gain: '<S138>/sqrt3_by_two' incorporates:
   *  Product: '<S139>/dsin'
   *  Product: '<S139>/qcos'
   *  Sum: '<S139>/sum_beta'
   */
  rtb_Add3 = (FOC_Basic_Y.Vq * rtb_Add1 + FOC_Basic_Y.Vd * rtb_Add3) *
    0.8660254037844386;

  /* End of Outputs for SubSystem: '<S136>/Two inputs CRL' */

  /* Sum: '<S138>/add_b' */
  rtb_Add1 = rtb_Add3 - rtb_add_c;

  /* Sum: '<S138>/add_c' */
  rtb_add_c = (0.0 - rtb_add_c) - rtb_Add3;

  /* Outputs for Atomic SubSystem: '<S136>/Two inputs CRL' */
  /* Gain: '<S144>/one_by_two' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S139>/a16'
   *  MinMax: '<S144>/Max'
   *  MinMax: '<S144>/Min'
   *  Sum: '<S144>/Add'
   */
  rtb_Add3 = (fmax(fmax(rtb_Switch_f_idx_0, rtb_Add1), rtb_add_c) + fmin(fmin
    (rtb_Switch_f_idx_0, rtb_Add1), rtb_add_c)) * -0.5;

  /* Outport: '<Root>/Va' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S139>/a16'
   *  Gain: '<S143>/Gain'
   *  Sum: '<S143>/Add3'
   */
  FOC_Basic_Y.Va = (rtb_Switch_f_idx_0 + rtb_Add3) * 1.1547005383792517;

  /* End of Outputs for SubSystem: '<S136>/Two inputs CRL' */

  /* Outport: '<Root>/Vb' incorporates:
   *  Gain: '<S143>/Gain'
   *  Sum: '<S143>/Add1'
   */
  FOC_Basic_Y.Vb = (rtb_Add1 + rtb_Add3) * 1.1547005383792517;

  /* Outport: '<Root>/Vc' incorporates:
   *  Gain: '<S143>/Gain'
   *  Sum: '<S143>/Add2'
   */
  FOC_Basic_Y.Vc = (rtb_Add3 + rtb_add_c) * 1.1547005383792517;

  /* Outport: '<Root>/Iq' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion1'
   */
  FOC_Basic_Y.Iq = rtb_algDD_o2_o;

  /* Switch: '<S4>/Switch' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   */
  if (FOC_Basic_U.IIR_Filter_Coefficient.Id_Filter_switch > 0.0F) {
    /* Outport: '<Root>/Id' incorporates:
     *  UnitDelay: '<S17>/Unit Delay'
     */
    FOC_Basic_Y.Id = FOC_Basic_DW.UnitDelay_DSTATE;
  } else {
    /* Outport: '<Root>/Id' */
    FOC_Basic_Y.Id = rtb_algDD_o1_d;
  }

  /* Product: '<S3>/delta rise limit' incorporates:
   *  Inport: '<Root>/Ref_Speed_rate_up'
   *  SampleTimeMath: '<S3>/sample time'
   *
   * About '<S3>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_Add3 = FOC_Basic_U.Ref_Speed_rate_up * 0.0001;

  /* Delay: '<S3>/Delay' */
  if (FOC_Basic_DW.icLoad) {
    /* Sum: '<S3>/Difference Inputs2' incorporates:
     *  Inport: '<Root>/Ref_Speed_mech_rpm'
     *
     * Block description for '<S3>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_Basic_DW.Delay_DSTATE = FOC_Basic_U.Ref_Speed_mech_rpm;
  }

  /* Sum: '<S3>/Difference Inputs1' incorporates:
   *  Delay: '<S3>/Delay'
   *  Inport: '<Root>/Ref_Speed_mech_rpm'
   *
   * Block description for '<S3>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_add_c = FOC_Basic_U.Ref_Speed_mech_rpm - FOC_Basic_DW.Delay_DSTATE;

  /* Switch: '<S201>/Switch2' incorporates:
   *  RelationalOperator: '<S201>/LowerRelop1'
   */
  if (!(rtb_add_c > rtb_Add3)) {
    /* Product: '<S3>/delta fall limit' incorporates:
     *  Inport: '<Root>/Ref_Speed_rate_down'
     *  SampleTimeMath: '<S3>/sample time'
     *
     * About '<S3>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_Add3 = 0.0001 * FOC_Basic_U.Ref_Speed_rate_down;

    /* Switch: '<S201>/Switch' incorporates:
     *  RelationalOperator: '<S201>/UpperRelop'
     */
    if (!(rtb_add_c < rtb_Add3)) {
      rtb_Add3 = rtb_add_c;
    }

    /* End of Switch: '<S201>/Switch' */
  }

  /* End of Switch: '<S201>/Switch2' */

  /* Sum: '<S3>/Difference Inputs2' incorporates:
   *  Delay: '<S3>/Delay'
   *
   * Block description for '<S3>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_Basic_DW.Delay_DSTATE += rtb_Add3;

  /* Outport: '<Root>/Speed_error' incorporates:
   *  Gain: '<S1>/rpm to Rad//sec'
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   *  Sum: '<S8>/Subtract'
   */
  FOC_Basic_Y.Speed_error = 0.10471975511965977 * FOC_Basic_DW.Delay_DSTATE -
    FOC_Basic_U.MtrSpd;

  /* Outport: '<Root>/Id_ref' incorporates:
   *  Inport: '<Root>/Id_ref_in'
   */
  FOC_Basic_Y.Id_ref = FOC_Basic_U.Id_ref_in;

  /* Update for DiscreteIntegrator: '<S116>/Integrator' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S113>/IProd Out'
   *  Sum: '<S108>/SumI2'
   *  Sum: '<S108>/SumI4'
   *  Sum: '<S128>/SumI3'
   *  Sum: '<S129>/SumI1'
   */
  FOC_Basic_DW.Integrator_DSTATE += ((FOC_Basic_Y.Id_error *
    FOC_Basic_U.MTPA_PID.Flux_PID_MTPA.Ki_flux_PID_MTPA + (FOC_Basic_Y.Vd_PID -
    FOC_Basic_Y.Vd_PID)) + (FOC_Basic_Y.Vd_PID - rtb_Sum)) * 0.0001;
  if (FOC_Basic_DW.Integrator_DSTATE > 33.48f) {
    FOC_Basic_DW.Integrator_DSTATE = 33.48f;
  } else if (FOC_Basic_DW.Integrator_DSTATE < -33.48f) {
    FOC_Basic_DW.Integrator_DSTATE = -33.48f;
  }

  /* End of Update for DiscreteIntegrator: '<S116>/Integrator' */

  /* Update for DiscreteIntegrator: '<S111>/Filter' */
  FOC_Basic_DW.Filter_DSTATE += 0.0001 * rtb_Switch2_d;

  /* Update for DiscreteIntegrator: '<S62>/Integrator' incorporates:
   *  Gain: '<S74>/Kt'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S59>/IProd Out'
   *  Sum: '<S54>/SumI2'
   *  Sum: '<S54>/SumI4'
   *  Sum: '<S74>/SumI3'
   *  Sum: '<S75>/SumI1'
   */
  FOC_Basic_DW.Integrator_DSTATE_h += (((FOC_Basic_Y.Vq_PID - FOC_Basic_Y.Vq_PID)
    * -10.0 + FOC_Basic_Y.Iq_error *
    FOC_Basic_U.MTPA_PID.Torque_PID_MTPA.Ki_torque_PID_MTPA) +
    (FOC_Basic_Y.Vq_PID - rtb_Sum_f)) * 0.0001;
  if (FOC_Basic_DW.Integrator_DSTATE_h > 33.48f) {
    FOC_Basic_DW.Integrator_DSTATE_h = 33.48f;
  } else if (FOC_Basic_DW.Integrator_DSTATE_h < -33.48f) {
    FOC_Basic_DW.Integrator_DSTATE_h = -33.48f;
  }

  /* End of Update for DiscreteIntegrator: '<S62>/Integrator' */

  /* Update for DiscreteIntegrator: '<S57>/Filter' */
  FOC_Basic_DW.Filter_DSTATE_d += 0.0001 * rtb_NProdOut_l;

  /* Update for Delay: '<S3>/Delay' */
  FOC_Basic_DW.icLoad = false;
}

/* Model step function for TID1 */
void FOC_Basic_step1(void)             /* Sample time: [0.001s, 0.0s] */
{
  double rtb_NProdOut_n;
  double rtb_Sum;
  double rtb_UkYk1_l;
  double rtb_deltafalllimit_d;

  /* Product: '<S185>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S177>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S175>/DProd Out'
   *  Sum: '<S177>/SumD'
   */
  rtb_NProdOut_n = (FOC_Basic_Y.Speed_error *
                    FOC_Basic_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA -
                    FOC_Basic_DW.Filter_DSTATE_i) *
    FOC_Basic_U.MTPA_PID.Speed_PID_MTPA.Filter_speed_PID_MTPA;

  /* Sum: '<S192>/Sum' incorporates:
   *  DiscreteIntegrator: '<S182>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S187>/PProd Out'
   */
  rtb_Sum = (FOC_Basic_Y.Speed_error *
             FOC_Basic_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA +
             FOC_Basic_DW.Integrator_DSTATE_b) + rtb_NProdOut_n;

  /* Switch: '<S190>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S190>/LowerRelop1'
   *  RelationalOperator: '<S190>/UpperRelop'
   *  Switch: '<S190>/Switch'
   */
  if (rtb_Sum > FOC_Basic_U.MTPA_PID.Up_Limit_speed_PID_MTPA) {
    /* Switch: '<S190>/Switch2' */
    FOC_Basic_Y.Iq_gen = FOC_Basic_U.MTPA_PID.Up_Limit_speed_PID_MTPA;
  } else if (rtb_Sum < FOC_Basic_U.MTPA_PID.Low_Limit_speed_PID_MTPA) {
    /* Switch: '<S190>/Switch2' incorporates:
     *  Switch: '<S190>/Switch'
     */
    FOC_Basic_Y.Iq_gen = FOC_Basic_U.MTPA_PID.Low_Limit_speed_PID_MTPA;
  } else {
    /* Switch: '<S190>/Switch2' incorporates:
     *  Switch: '<S190>/Switch'
     */
    FOC_Basic_Y.Iq_gen = rtb_Sum;
  }

  /* End of Switch: '<S190>/Switch2' */

  /* Delay: '<S7>/Delay' */
  if (FOC_Basic_DW.icLoad_p) {
    /* Sum: '<S7>/Difference Inputs2'
     *
     * Block description for '<S7>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_Basic_DW.Delay_DSTATE_h = FOC_Basic_Y.Iq_gen;
  }

  /* Sum: '<S7>/Difference Inputs1' incorporates:
   *  Delay: '<S7>/Delay'
   *
   * Block description for '<S7>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_UkYk1_l = FOC_Basic_Y.Iq_gen - FOC_Basic_DW.Delay_DSTATE_h;

  /* Product: '<S7>/delta rise limit' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  SampleTimeMath: '<S7>/sample time'
   *
   * About '<S7>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_deltafalllimit_d = FOC_Basic_U.Rate_limiter.Torque_gen_ramp_up * 0.001;

  /* Switch: '<S146>/Switch2' incorporates:
   *  RelationalOperator: '<S146>/LowerRelop1'
   */
  if (!(rtb_UkYk1_l > rtb_deltafalllimit_d)) {
    /* Product: '<S7>/delta fall limit' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  SampleTimeMath: '<S7>/sample time'
     *
     * About '<S7>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_deltafalllimit_d = 0.001 * FOC_Basic_U.Rate_limiter.Torque_gen_ramp_down;

    /* Switch: '<S146>/Switch' incorporates:
     *  RelationalOperator: '<S146>/UpperRelop'
     */
    if (!(rtb_UkYk1_l < rtb_deltafalllimit_d)) {
      rtb_deltafalllimit_d = rtb_UkYk1_l;
    }

    /* End of Switch: '<S146>/Switch' */
  }

  /* End of Switch: '<S146>/Switch2' */

  /* Sum: '<S7>/Difference Inputs2' incorporates:
   *  Delay: '<S7>/Delay'
   *
   * Block description for '<S7>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_Basic_DW.Delay_DSTATE_h += rtb_deltafalllimit_d;

  /* RateTransition: '<S2>/Rate Transition' */
  FOC_Basic_DW.RateTransition_Buffer0 = FOC_Basic_DW.Delay_DSTATE_h;

  /* Update for DiscreteIntegrator: '<S182>/Integrator' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S179>/IProd Out'
   *  Sum: '<S174>/SumI2'
   *  Sum: '<S174>/SumI4'
   *  Sum: '<S194>/SumI3'
   *  Sum: '<S195>/SumI1'
   */
  FOC_Basic_DW.Integrator_DSTATE_b += ((FOC_Basic_Y.Speed_error *
    FOC_Basic_U.MTPA_PID.Speed_PID_MTPA.Ki_speed_PID_MTPA + (FOC_Basic_Y.Iq_gen
    - FOC_Basic_Y.Iq_gen)) + (FOC_Basic_Y.Iq_gen - rtb_Sum)) * 0.001;
  if (FOC_Basic_DW.Integrator_DSTATE_b > 500.0) {
    FOC_Basic_DW.Integrator_DSTATE_b = 500.0;
  } else if (FOC_Basic_DW.Integrator_DSTATE_b < -500.0) {
    FOC_Basic_DW.Integrator_DSTATE_b = -500.0;
  }

  /* End of Update for DiscreteIntegrator: '<S182>/Integrator' */

  /* Update for DiscreteIntegrator: '<S177>/Filter' */
  FOC_Basic_DW.Filter_DSTATE_i += 0.001 * rtb_NProdOut_n;

  /* Update for Delay: '<S7>/Delay' */
  FOC_Basic_DW.icLoad_p = false;
}

/* Model initialize function */
void FOC_Basic_initialize(void)
{
  /* InitializeConditions for Delay: '<S3>/Delay' */
  FOC_Basic_DW.icLoad = true;

  /* InitializeConditions for Delay: '<S7>/Delay' */
  FOC_Basic_DW.icLoad_p = true;

  /* Rate limiter settings */
  FOC_Basic_U.Ref_Speed_rate_up = 0.1f * 10000.0f;
  FOC_Basic_U.Ref_Speed_rate_down = -10.0f * 10000.0f;
  FOC_Basic_U.Rate_limiter.Torque_gen_ramp_up = 100.0f * 10000.0f;
  FOC_Basic_U.Rate_limiter.Torque_gen_ramp_down = -100.0f * 10000.0f;

  //not used
  FOC_Basic_U.Rate_limiter.Iq_ramp_up = 50.0f * 10000.0f;
  FOC_Basic_U.Rate_limiter.Iq_ramp_down = -50.0f * 10000.0f;
  FOC_Basic_U.Rate_limiter.Id_ramp_up = 50.0f * 10000.0f;
  FOC_Basic_U.Rate_limiter.Id_ramp_down = -50.0f * 10000.0f;
  //not used

  /* IIR Filter Settings */
  FOC_Basic_U.IIR_Filter_Coefficient.Id_Filter_switch = 1.0f;
  FOC_Basic_U.IIR_Filter_Coefficient.Iq_Filter_switch = 1.0f;
  FOC_Basic_U.IIR_Filter_Coefficient.Id_Filter_coefficient = 0.9f;
  FOC_Basic_U.IIR_Filter_Coefficient.Iq_Filter_coefficient = 0.9f;

  /* PID Values */
  FOC_Basic_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA = 5.0f;
  FOC_Basic_U.MTPA_PID.Speed_PID_MTPA.Ki_speed_PID_MTPA = 9.0f;
  FOC_Basic_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA = 0.00001;
  FOC_Basic_U.MTPA_PID.Speed_PID_MTPA.Filter_speed_PID_MTPA = 10.0f;

  FOC_Basic_U.MTPA_PID.Up_Limit_speed_PID_MTPA = 500.0f;
  FOC_Basic_U.MTPA_PID.Low_Limit_speed_PID_MTPA = 0.0f;

  FOC_Basic_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA = 0.2f;
  FOC_Basic_U.MTPA_PID.Torque_PID_MTPA.Ki_torque_PID_MTPA = 5.0f;
  FOC_Basic_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA = 0.0001f;
  FOC_Basic_U.MTPA_PID.Torque_PID_MTPA.Filter_torque_PID_MTPA = 10.0f;

  FOC_Basic_U.MTPA_PID.Up_Limit_torque_PID = 33.48f;
  FOC_Basic_U.MTPA_PID.Low_Limit_torque_PID = -33.48f;

  FOC_Basic_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA = 0.3f;
  FOC_Basic_U.MTPA_PID.Flux_PID_MTPA.Ki_flux_PID_MTPA = 6.0f;
  FOC_Basic_U.MTPA_PID.Flux_PID_MTPA.Kd_flux_PID_MTPA = 0.0001f;
  FOC_Basic_U.MTPA_PID.Flux_PID_MTPA.Filter_flux_PID_MTPA = 10.0f;

  FOC_Basic_U.MTPA_PID.Up_Limit_flux_PID = 33.48f;
  FOC_Basic_U.MTPA_PID.Low_Limit_flux_PID = -33.48f;

  FOC_Basic_U.Id_ref_in = 0.0f;
  FOC_Basic_U.Ref_Speed_mech_rpm = 100.0f;
}

/* Model terminate function */
void FOC_Basic_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
