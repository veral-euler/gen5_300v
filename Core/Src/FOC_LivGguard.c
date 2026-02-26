/*
 * File: FOC_LivGguard.c
 *
 * Code generated for Simulink model 'FOC_LivGguard'.
 *
 * Model version                  : 18.321
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Wed Feb 11 17:44:19 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_LivGguard.h"
#include <math.h>
#include "FOC_LivGguard_private.h"

/* Block signals (default storage) */
B_FOC_LivGguard_T FOC_LivGguard_B;

/* Block states (default storage) */
DW_FOC_LivGguard_T FOC_LivGguard_DW;

/* External inputs (root inport signals with default storage) */
ExtU_FOC_LivGguard_T FOC_LivGguard_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_FOC_LivGguard_T FOC_LivGguard_Y;

/* Real-time model */
static RT_MODEL_FOC_LivGguard_T FOC_LivGguard_M_;
RT_MODEL_FOC_LivGguard_T *const FOC_LivGguard_M = &FOC_LivGguard_M_;
double look2_binlx(double u0, double u1, const double bp0[], const double bp1[],
                   const double table[], const uint32_t maxIndex[], uint32_t
                   stride)
{
  double fractions[2];
  double frac;
  double yL_0d0;
  double yL_0d1;
  uint32_t bpIndices[2];
  uint32_t bpIdx;
  uint32_t iLeft;
  uint32_t iRght;

  /* Column-major Lookup 2-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex[0U]]) {
    /* Binary Search */
    bpIdx = maxIndex[0U] >> 1U;
    iLeft = 0U;
    iRght = maxIndex[0U];
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex[0U] - 1U;
    frac = (u0 - bp0[maxIndex[0U] - 1U]) / (bp0[maxIndex[0U]] - bp0[maxIndex[0U]
      - 1U]);
  }

  fractions[0U] = frac;
  bpIndices[0U] = iLeft;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u1 <= bp1[0U]) {
    iLeft = 0U;
    frac = (u1 - bp1[0U]) / (bp1[1U] - bp1[0U]);
  } else if (u1 < bp1[maxIndex[1U]]) {
    /* Binary Search */
    bpIdx = maxIndex[1U] >> 1U;
    iLeft = 0U;
    iRght = maxIndex[1U];
    while (iRght - iLeft > 1U) {
      if (u1 < bp1[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u1 - bp1[iLeft]) / (bp1[iLeft + 1U] - bp1[iLeft]);
  } else {
    iLeft = maxIndex[1U] - 1U;
    frac = (u1 - bp1[maxIndex[1U] - 1U]) / (bp1[maxIndex[1U]] - bp1[maxIndex[1U]
      - 1U]);
  }

  /* Column-major Interpolation 2-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'wrapping'
   */
  bpIdx = iLeft * stride + bpIndices[0U];
  yL_0d0 = table[bpIdx];
  yL_0d0 += (table[bpIdx + 1U] - yL_0d0) * fractions[0U];
  bpIdx += stride;
  yL_0d1 = table[bpIdx];
  return (((table[bpIdx + 1U] - yL_0d1) * fractions[0U] + yL_0d1) - yL_0d0) *
    frac + yL_0d0;
}

/* Model step function for TID0 */
void FOC_LivGguard_step0(void)         /* Sample time: [0.0001s, 0.0s] */
{
  double rtb_Add1_l;
  double rtb_Add3;
  double rtb_Sum_f;
  double rtb_Switch;
  double rtb_Switch_f_idx_0;
  double rtb_UkYk1_f;
  double rtb_add_c;
  double rtb_deltafalllimit_a;
  float rtb_Gain_j;
  float rtb_algDD_o1_d;
  float rtb_algDD_o2_o;

  /* Update the flag to indicate when data transfers from
   *  Sample time: [0.0001s, 0.0s] to Sample time: [0.001s, 0.0s]  */
  (FOC_LivGguard_M->Timing.RateInteraction.TID0_1)++;
  if ((FOC_LivGguard_M->Timing.RateInteraction.TID0_1) > 9) {
    FOC_LivGguard_M->Timing.RateInteraction.TID0_1 = 0;
  }

  /* Gain: '<S7>/Rad//sec to RPM' incorporates:
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   */
  rtb_deltafalllimit_a = 9.5492965855137211 *
    FOC_LivGguard_U.ActualSpeed_mech_radsec;

  /* RateTransition: '<S2>/Rate Transition' */
  if (FOC_LivGguard_M->Timing.RateInteraction.TID0_1 == 1) {
    /* RateTransition: '<S2>/Rate Transition' */
    FOC_LivGguard_B.RateTransition = FOC_LivGguard_DW.RateTransition_Buffer0;
  }

  /* End of RateTransition: '<S2>/Rate Transition' */

  /* Switch: '<S2>/Switch' incorporates:
   *  Inport: '<Root>/Iq_Torque_ratio'
   *  Inport: '<Root>/Speed_1_Torque_0'
   *  Inport: '<Root>/T_ref'
   *  Product: '<S2>/Product1'
   */
  if (FOC_LivGguard_U.Speed_1_Torque_0 > 0.0) {
    rtb_Switch = FOC_LivGguard_U.Iq_Torque_ratio *
      FOC_LivGguard_B.RateTransition;
  } else {
    rtb_Switch = FOC_LivGguard_U.RefTrq;
  }

  /* End of Switch: '<S2>/Switch' */

  /* Delay: '<S8>/Delay' */
  if (FOC_LivGguard_DW.icLoad) {
    FOC_LivGguard_DW.Delay_DSTATE = rtb_Switch;
  }

  /* Product: '<S8>/delta fall limit' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  Product: '<S8>/delta rise limit'
   *  SampleTimeMath: '<S8>/sample time'
   *
   * About '<S8>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  FOC_LivGguard_Y.Id_ref_sat = FOC_LivGguard_U.Rate_limiter.Torque_gen_ramp_up *
    0.0001;

  /* Sum: '<S8>/Difference Inputs1' incorporates:
   *  Delay: '<S8>/Delay'
   *
   * Block description for '<S8>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Switch -= FOC_LivGguard_DW.Delay_DSTATE;

  /* Switch: '<S164>/Switch2' incorporates:
   *  RelationalOperator: '<S164>/LowerRelop1'
   */
  if (!(rtb_Switch > FOC_LivGguard_Y.Id_ref_sat)) {
    /* Product: '<S8>/delta fall limit' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  SampleTimeMath: '<S8>/sample time'
     *
     * About '<S8>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    FOC_LivGguard_Y.Id_ref_sat = 0.0001 *
      FOC_LivGguard_U.Rate_limiter.Torque_gen_ramp_down;

    /* Switch: '<S164>/Switch' incorporates:
     *  RelationalOperator: '<S164>/UpperRelop'
     */
    if (!(rtb_Switch < FOC_LivGguard_Y.Id_ref_sat)) {
      /* Product: '<S8>/delta fall limit' */
      FOC_LivGguard_Y.Id_ref_sat = rtb_Switch;
    }

    /* End of Switch: '<S164>/Switch' */
  }

  /* End of Switch: '<S164>/Switch2' */

  /* Sum: '<S8>/Difference Inputs2' incorporates:
   *  Delay: '<S8>/Delay'
   *
   * Block description for '<S8>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_LivGguard_Y.T_gen = FOC_LivGguard_Y.Id_ref_sat +
    FOC_LivGguard_DW.Delay_DSTATE;

  /* Lookup_n-D: '<S7>/Id_Table' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion'
   *  Sum: '<S8>/Difference Inputs2'
   *
   * Block description for '<S8>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_LivGguard_Y.Id_LUT = look2_binlx(rtb_deltafalllimit_a,
    FOC_LivGguard_Y.T_gen, FOC_LivGguard_ConstP.pooled4,
    FOC_LivGguard_ConstP.pooled5, FOC_LivGguard_ConstP.Id_Table_tableData,
    FOC_LivGguard_ConstP.pooled11, 27U);

  /* Lookup_n-D: '<S7>/Iq_Table' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion'
   *  Sum: '<S8>/Difference Inputs2'
   *
   * Block description for '<S8>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_LivGguard_Y.Iq_LUT = look2_binlx(rtb_deltafalllimit_a,
    FOC_LivGguard_Y.T_gen, FOC_LivGguard_ConstP.pooled4,
    FOC_LivGguard_ConstP.pooled5, FOC_LivGguard_ConstP.Iq_Table_tableData,
    FOC_LivGguard_ConstP.pooled11, 27U);

  /* If: '<S158>/If' incorporates:
   *  Inport: '<Root>/Drive_State'
   */
  if (FOC_LivGguard_U.Drive_State == 1.0) {
    /* Outputs for IfAction SubSystem: '<S158>/If Action Subsystem' incorporates:
     *  ActionPort: '<S161>/Action Port'
     */
    /* SignalConversion generated from: '<S161>/Id_LUT' incorporates:
     *  Merge: '<S158>/Merge'
     */
    FOC_LivGguard_B.Merge[0] = FOC_LivGguard_Y.Id_LUT;

    /* SignalConversion generated from: '<S161>/Iq_LUT' incorporates:
     *  Merge: '<S158>/Merge'
     */
    FOC_LivGguard_B.Merge[1] = FOC_LivGguard_Y.Iq_LUT;

    /* End of Outputs for SubSystem: '<S158>/If Action Subsystem' */
  } else if (FOC_LivGguard_U.Drive_State == 2.0) {
    /* Outputs for IfAction SubSystem: '<S158>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S162>/Action Port'
     */
    /* Gain: '<S162>/Gain' incorporates:
     *  Merge: '<S158>/Merge'
     */
    FOC_LivGguard_B.Merge[1] = -FOC_LivGguard_Y.Iq_LUT;

    /* SignalConversion generated from: '<S162>/Id_LUT' incorporates:
     *  Merge: '<S158>/Merge'
     */
    FOC_LivGguard_B.Merge[0] = FOC_LivGguard_Y.Id_LUT;

    /* End of Outputs for SubSystem: '<S158>/If Action Subsystem1' */
  } else {
    /* Outputs for IfAction SubSystem: '<S158>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S163>/Action Port'
     */
    /* Merge: '<S158>/Merge' incorporates:
     *  Constant: '<S163>/Constant'
     *  SignalConversion generated from: '<S163>/Out1'
     */
    FOC_LivGguard_B.Merge[0] = 0.0;
    FOC_LivGguard_B.Merge[1] = 0.0;

    /* End of Outputs for SubSystem: '<S158>/If Action Subsystem2' */
  }

  /* End of If: '<S158>/If' */

  /* Delay: '<S154>/Delay' */
  if (FOC_LivGguard_DW.icLoad_b) {
    FOC_LivGguard_DW.Delay_DSTATE_b = FOC_LivGguard_B.Merge[0];
  }

  /* Product: '<S154>/delta rise limit' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  SampleTimeMath: '<S154>/sample time'
   *
   * About '<S154>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_deltafalllimit_a = FOC_LivGguard_U.Rate_limiter.Id_ramp_up * 0.0001;

  /* Sum: '<S154>/Difference Inputs1' incorporates:
   *  Delay: '<S154>/Delay'
   *
   * Block description for '<S154>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Switch = FOC_LivGguard_B.Merge[0] - FOC_LivGguard_DW.Delay_DSTATE_b;

  /* Switch: '<S159>/Switch2' incorporates:
   *  RelationalOperator: '<S159>/LowerRelop1'
   */
  if (!(rtb_Switch > rtb_deltafalllimit_a)) {
    /* Product: '<S154>/delta fall limit' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  SampleTimeMath: '<S154>/sample time'
     *
     * About '<S154>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_deltafalllimit_a = 0.0001 * FOC_LivGguard_U.Rate_limiter.Id_ramp_down;

    /* Switch: '<S159>/Switch' incorporates:
     *  RelationalOperator: '<S159>/UpperRelop'
     */
    if (!(rtb_Switch < rtb_deltafalllimit_a)) {
      rtb_deltafalllimit_a = rtb_Switch;
    }

    /* End of Switch: '<S159>/Switch' */
  }

  /* End of Switch: '<S159>/Switch2' */

  /* Sum: '<S154>/Difference Inputs2' incorporates:
   *  Delay: '<S154>/Delay'
   *
   * Block description for '<S154>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_LivGguard_Y.Id_ref = rtb_deltafalllimit_a +
    FOC_LivGguard_DW.Delay_DSTATE_b;

  /* Switch: '<S156>/Switch2' incorporates:
   *  Inport: '<Root>/Id_Iq_MTPA_limit'
   *  RelationalOperator: '<S156>/LowerRelop1'
   *  RelationalOperator: '<S156>/UpperRelop'
   *  Switch: '<S156>/Switch'
   */
  if (FOC_LivGguard_Y.Id_ref > FOC_LivGguard_U.Id_Iq_MTPA_limit.Id_up_limit) {
    /* Product: '<S8>/delta fall limit' */
    FOC_LivGguard_Y.Id_ref_sat = FOC_LivGguard_U.Id_Iq_MTPA_limit.Id_up_limit;
  } else if (FOC_LivGguard_Y.Id_ref <
             FOC_LivGguard_U.Id_Iq_MTPA_limit.Id_low_limit) {
    /* Product: '<S8>/delta fall limit' incorporates:
     *  Switch: '<S156>/Switch'
     */
    FOC_LivGguard_Y.Id_ref_sat = FOC_LivGguard_U.Id_Iq_MTPA_limit.Id_low_limit;
  } else {
    /* Product: '<S8>/delta fall limit' incorporates:
     *  Switch: '<S156>/Switch'
     */
    FOC_LivGguard_Y.Id_ref_sat = FOC_LivGguard_Y.Id_ref;
  }

  /* End of Switch: '<S156>/Switch2' */

  /* Outputs for Atomic SubSystem: '<S15>/Two phase CRL wrap' */
  /* Gain: '<S16>/one_by_sqrt3' incorporates:
   *  Inport: '<Root>/Phase Current'
   *  Sum: '<S16>/a_plus_2b'
   */
  rtb_deltafalllimit_a = ((FOC_LivGguard_U.PhaseCurrent[0] +
    FOC_LivGguard_U.PhaseCurrent[1]) + FOC_LivGguard_U.PhaseCurrent[1]) *
    0.57735026918962584;

  /* End of Outputs for SubSystem: '<S15>/Two phase CRL wrap' */

  /* Trigonometry: '<S4>/Trigonometric Function' incorporates:
   *  Inport: '<Root>/angle'
   *  Trigonometry: '<S6>/Trigonometric Function1'
   */
  rtb_Add3 = sin(FOC_LivGguard_U.MtrElcPos);

  /* Trigonometry: '<S4>/Trigonometric Function1' incorporates:
   *  Inport: '<Root>/angle'
   *  Trigonometry: '<S6>/Trigonometric Function'
   */
  rtb_Add1_l = cos(FOC_LivGguard_U.MtrElcPos);

  /* Outputs for Atomic SubSystem: '<S14>/Two inputs CRL' */
  /* Outputs for Atomic SubSystem: '<S15>/Two phase CRL wrap' */
  /* AlgorithmDescriptorDelegate generated from: '<S23>/a16' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S16>/a16'
   *  Inport: '<Root>/Phase Current'
   *  Product: '<S23>/acos'
   *  Product: '<S23>/asin'
   *  Product: '<S23>/bcos'
   *  Product: '<S23>/bsin'
   *  Sum: '<S23>/sum_Ds'
   *  Sum: '<S23>/sum_Qs'
   *  Switch: '<S24>/Switch'
   *  Trigonometry: '<S4>/Trigonometric Function'
   *  Trigonometry: '<S4>/Trigonometric Function1'
   */
  rtb_algDD_o1_d = (float)(FOC_LivGguard_U.PhaseCurrent[0] * rtb_Add1_l +
    rtb_deltafalllimit_a * rtb_Add3);
  rtb_algDD_o2_o = (float)(rtb_deltafalllimit_a * rtb_Add1_l -
    FOC_LivGguard_U.PhaseCurrent[0] * rtb_Add3);

  /* End of Outputs for SubSystem: '<S15>/Two phase CRL wrap' */
  /* End of Outputs for SubSystem: '<S14>/Two inputs CRL' */

  /* Sum: '<S19>/Add1' incorporates:
   *  Constant: '<S12>/One'
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   *  Product: '<S19>/Product'
   *  Product: '<S19>/Product1'
   *  Sum: '<S12>/Sum'
   *  Switch: '<S12>/Switch1'
   *  UnitDelay: '<S19>/Unit Delay'
   */
  FOC_LivGguard_DW.UnitDelay_DSTATE = (1.0F -
    FOC_LivGguard_U.IIR_Filter_Coefficient.Id_Filter_coefficient) *
    FOC_LivGguard_DW.UnitDelay_DSTATE + rtb_algDD_o1_d *
    FOC_LivGguard_U.IIR_Filter_Coefficient.Id_Filter_coefficient;

  /* Switch: '<S4>/Switch' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   *  UnitDelay: '<S19>/Unit Delay'
   */
  if (FOC_LivGguard_U.IIR_Filter_Coefficient.Id_Filter_switch > 0.0F) {
    rtb_Gain_j = FOC_LivGguard_DW.UnitDelay_DSTATE;
  } else {
    rtb_Gain_j = rtb_algDD_o1_d;
  }

  /* Sum: '<S29>/Sum3' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion'
   *  Switch: '<S4>/Switch'
   */
  FOC_LivGguard_Y.Id_error = FOC_LivGguard_Y.Id_ref_sat - rtb_Gain_j;

  /* Product: '<S127>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S119>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S117>/DProd Out'
   *  Sum: '<S119>/SumD'
   */
  rtb_deltafalllimit_a = (FOC_LivGguard_Y.Id_error *
    FOC_LivGguard_U.MTPA_PID.Flux_PID_MTPA.Kd_flux_PID_MTPA -
    FOC_LivGguard_DW.Filter_DSTATE) *
    FOC_LivGguard_U.MTPA_PID.Flux_PID_MTPA.Filter_flux_PID_MTPA;

  /* Sum: '<S134>/Sum' incorporates:
   *  DiscreteIntegrator: '<S124>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S129>/PProd Out'
   */
  rtb_Switch = (FOC_LivGguard_Y.Id_error *
                FOC_LivGguard_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA +
                FOC_LivGguard_DW.Integrator_DSTATE) + rtb_deltafalllimit_a;

  /* Switch: '<S132>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S132>/LowerRelop1'
   *  RelationalOperator: '<S132>/UpperRelop'
   *  Switch: '<S132>/Switch'
   */
  if (rtb_Switch > FOC_LivGguard_U.MTPA_PID.Up_Limit_flux_PID) {
    /* Switch: '<S132>/Switch2' */
    FOC_LivGguard_Y.Vd_PID = FOC_LivGguard_U.MTPA_PID.Up_Limit_flux_PID;
  } else if (rtb_Switch < FOC_LivGguard_U.MTPA_PID.Low_Limit_flux_PID) {
    /* Switch: '<S132>/Switch2' incorporates:
     *  Switch: '<S132>/Switch'
     */
    FOC_LivGguard_Y.Vd_PID = FOC_LivGguard_U.MTPA_PID.Low_Limit_flux_PID;
  } else {
    /* Switch: '<S132>/Switch2' incorporates:
     *  Switch: '<S132>/Switch'
     */
    FOC_LivGguard_Y.Vd_PID = rtb_Switch;
  }

  /* End of Switch: '<S132>/Switch2' */

  /* Gain: '<S5>/Gain' incorporates:
   *  Inport: '<Root>/Bus_Voltage'
   */
  rtb_Gain_j = 0.577350259F * FOC_LivGguard_U.BusVoltage_V;

  /* Gain: '<S10>/Gain' incorporates:
   *  Abs: '<S10>/Abs'
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   */
  FOC_LivGguard_Y.Ld = fabs(FOC_LivGguard_U.ActualSpeed_mech_radsec) * RAD_S_TO_RPM;

  /* Gain: '<S10>/Gain1' incorporates:
   *  Gain: '<S10>/Gain'
   *  Lookup_n-D: '<S10>/Lq_Table'
   *  Sum: '<S8>/Difference Inputs2'
   *
   * Block description for '<S8>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_LivGguard_Y.Lq = 0.001 * look2_binlx(FOC_LivGguard_Y.Ld,
    FOC_LivGguard_Y.T_gen, FOC_LivGguard_ConstP.pooled4,
    FOC_LivGguard_ConstP.pooled5, FOC_LivGguard_ConstP.Lq_Table_tableData,
    FOC_LivGguard_ConstP.pooled11, 27U);

  /* Delay: '<S155>/Delay' */
  if (FOC_LivGguard_DW.icLoad_n) {
    FOC_LivGguard_DW.Delay_DSTATE_bc = FOC_LivGguard_B.Merge[1];
  }

  /* Product: '<S155>/delta fall limit' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  Product: '<S155>/delta rise limit'
   *  SampleTimeMath: '<S155>/sample time'
   *
   * About '<S155>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  FOC_LivGguard_Y.Iq_ref_sat = FOC_LivGguard_U.Rate_limiter.Iq_ramp_up * 0.0001;

  /* Sum: '<S155>/Difference Inputs1' incorporates:
   *  Delay: '<S155>/Delay'
   *
   * Block description for '<S155>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_UkYk1_f = FOC_LivGguard_B.Merge[1] - FOC_LivGguard_DW.Delay_DSTATE_bc;

  /* Switch: '<S160>/Switch2' incorporates:
   *  RelationalOperator: '<S160>/LowerRelop1'
   */
  if (!(rtb_UkYk1_f > FOC_LivGguard_Y.Iq_ref_sat)) {
    /* Product: '<S155>/delta fall limit' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  SampleTimeMath: '<S155>/sample time'
     *
     * About '<S155>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    FOC_LivGguard_Y.Iq_ref_sat = 0.0001 *
      FOC_LivGguard_U.Rate_limiter.Iq_ramp_down;

    /* Switch: '<S160>/Switch' incorporates:
     *  RelationalOperator: '<S160>/UpperRelop'
     */
    if (!(rtb_UkYk1_f < FOC_LivGguard_Y.Iq_ref_sat)) {
      /* Product: '<S155>/delta fall limit' */
      FOC_LivGguard_Y.Iq_ref_sat = rtb_UkYk1_f;
    }

    /* End of Switch: '<S160>/Switch' */
  }

  /* End of Switch: '<S160>/Switch2' */

  /* Sum: '<S155>/Difference Inputs2' incorporates:
   *  Delay: '<S155>/Delay'
   *
   * Block description for '<S155>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_LivGguard_Y.Iq_ref = FOC_LivGguard_Y.Iq_ref_sat +
    FOC_LivGguard_DW.Delay_DSTATE_bc;

  /* Switch: '<S157>/Switch2' incorporates:
   *  Inport: '<Root>/Id_Iq_MTPA_limit'
   *  RelationalOperator: '<S157>/LowerRelop1'
   *  RelationalOperator: '<S157>/UpperRelop'
   *  Switch: '<S157>/Switch'
   */
  if (FOC_LivGguard_Y.Iq_ref > FOC_LivGguard_U.Id_Iq_MTPA_limit.Iq_up_limit) {
    /* Product: '<S155>/delta fall limit' */
    FOC_LivGguard_Y.Iq_ref_sat = FOC_LivGguard_U.Id_Iq_MTPA_limit.Iq_up_limit;
  } else if (FOC_LivGguard_Y.Iq_ref <
             FOC_LivGguard_U.Id_Iq_MTPA_limit.Iq_low_limit) {
    /* Product: '<S155>/delta fall limit' incorporates:
     *  Switch: '<S157>/Switch'
     */
    FOC_LivGguard_Y.Iq_ref_sat = FOC_LivGguard_U.Id_Iq_MTPA_limit.Iq_low_limit;
  } else {
    /* Product: '<S155>/delta fall limit' incorporates:
     *  Switch: '<S157>/Switch'
     */
    FOC_LivGguard_Y.Iq_ref_sat = FOC_LivGguard_Y.Iq_ref;
  }

  /* End of Switch: '<S157>/Switch2' */

  /* Sum: '<S28>/Sum2' incorporates:
   *  Gain: '<S31>/wm_pu2si_mech2elec'
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   */
  FOC_LivGguard_Y.Iq_error = 3.0 * FOC_LivGguard_U.ActualSpeed_mech_radsec;

  /* Gain: '<S31>/NegSign' incorporates:
   *  Product: '<S31>/prod1'
   *  Switch: '<S32>/Switch1'
   */
  FOC_LivGguard_Y.Vd_FF = -(FOC_LivGguard_Y.Lq * FOC_LivGguard_Y.Iq_ref_sat *
    FOC_LivGguard_Y.Iq_error);

  /* Switch: '<S33>/Switch2' incorporates:
   *  RelationalOperator: '<S33>/LowerRelop1'
   *  RelationalOperator: '<S33>/UpperRelop'
   *  Switch: '<S31>/Switch'
   *  Switch: '<S33>/Switch'
   *  UnaryMinus: '<S31>/Unary Minus'
   */
  if (FOC_LivGguard_Y.Vd_FF > rtb_Gain_j) {
    /* Gain: '<S31>/NegSign' */
    FOC_LivGguard_Y.Vd_FF = rtb_Gain_j;
  } else if (FOC_LivGguard_Y.Vd_FF < -rtb_Gain_j) {
    /* Gain: '<S31>/NegSign' incorporates:
     *  Switch: '<S33>/Switch'
     *  UnaryMinus: '<S31>/Unary Minus'
     */
    FOC_LivGguard_Y.Vd_FF = -rtb_Gain_j;
  }

  /* End of Switch: '<S33>/Switch2' */

  /* Sum: '<S5>/Add' */
  FOC_LivGguard_Y.Vd = FOC_LivGguard_Y.Vd_PID + FOC_LivGguard_Y.Vd_FF;

  /* Switch: '<S26>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S26>/LowerRelop1'
   *  RelationalOperator: '<S26>/UpperRelop'
   *  Switch: '<S26>/Switch'
   */
  if (FOC_LivGguard_Y.Vd > FOC_LivGguard_U.MTPA_PID.Up_Limit_flux_PID) {
    /* Sum: '<S5>/Add' */
    FOC_LivGguard_Y.Vd = FOC_LivGguard_U.MTPA_PID.Up_Limit_flux_PID;
  } else if (FOC_LivGguard_Y.Vd < FOC_LivGguard_U.MTPA_PID.Low_Limit_flux_PID) {
    /* Sum: '<S5>/Add' incorporates:
     *  Switch: '<S26>/Switch'
     */
    FOC_LivGguard_Y.Vd = FOC_LivGguard_U.MTPA_PID.Low_Limit_flux_PID;
  }

  /* End of Switch: '<S26>/Switch2' */

  /* Gain: '<S10>/Gain2' incorporates:
   *  Gain: '<S10>/Gain'
   *  Lookup_n-D: '<S10>/Flux_Table'
   *  Sum: '<S8>/Difference Inputs2'
   *
   * Block description for '<S8>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_LivGguard_Y.Lambda = 0.001 * look2_binlx(FOC_LivGguard_Y.Ld,
    FOC_LivGguard_Y.T_gen, FOC_LivGguard_ConstP.pooled4,
    FOC_LivGguard_ConstP.pooled5, FOC_LivGguard_ConstP.Flux_Table_tableData,
    FOC_LivGguard_ConstP.pooled11, 27U);

  /* Gain: '<S10>/Gain' incorporates:
   *  Lookup_n-D: '<S10>/Ld_Table'
   *  Sum: '<S8>/Difference Inputs2'
   *
   * Block description for '<S8>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_LivGguard_Y.Ld = 0.001 * look2_binlx(FOC_LivGguard_Y.Ld,
    FOC_LivGguard_Y.T_gen, FOC_LivGguard_ConstP.pooled4,
    FOC_LivGguard_ConstP.pooled5, FOC_LivGguard_ConstP.Ld_Table_tableData,
    FOC_LivGguard_ConstP.pooled11, 27U);

  /* Product: '<S31>/prod2' incorporates:
   *  Product: '<S31>/prod3'
   *  Sum: '<S31>/add1'
   *  Switch: '<S32>/Switch'
   *  Switch: '<S32>/Switch2'
   */
  FOC_LivGguard_Y.Vq_FF = (FOC_LivGguard_Y.Ld * FOC_LivGguard_Y.Id_ref_sat +
    FOC_LivGguard_Y.Lambda) * FOC_LivGguard_Y.Iq_error;

  /* Switch: '<S34>/Switch2' incorporates:
   *  RelationalOperator: '<S34>/LowerRelop1'
   *  RelationalOperator: '<S34>/UpperRelop'
   *  Switch: '<S31>/Switch'
   *  Switch: '<S34>/Switch'
   *  UnaryMinus: '<S31>/Unary Minus'
   */
  if (FOC_LivGguard_Y.Vq_FF > rtb_Gain_j) {
    /* Product: '<S31>/prod2' */
    FOC_LivGguard_Y.Vq_FF = rtb_Gain_j;
  } else if (FOC_LivGguard_Y.Vq_FF < -rtb_Gain_j) {
    /* Product: '<S31>/prod2' incorporates:
     *  Switch: '<S34>/Switch'
     *  UnaryMinus: '<S31>/Unary Minus'
     */
    FOC_LivGguard_Y.Vq_FF = -rtb_Gain_j;
  }

  /* End of Switch: '<S34>/Switch2' */

  /* Sum: '<S22>/Add1' incorporates:
   *  Constant: '<S13>/One'
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   *  Product: '<S22>/Product'
   *  Product: '<S22>/Product1'
   *  Sum: '<S13>/Sum'
   *  Switch: '<S13>/Switch1'
   *  UnitDelay: '<S22>/Unit Delay'
   */
  FOC_LivGguard_DW.UnitDelay_DSTATE_f = (1.0F -
    FOC_LivGguard_U.IIR_Filter_Coefficient.Iq_Filter_coefficient) *
    FOC_LivGguard_DW.UnitDelay_DSTATE_f + rtb_algDD_o2_o *
    FOC_LivGguard_U.IIR_Filter_Coefficient.Iq_Filter_coefficient;

  /* Switch: '<S4>/Switch1' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   */
  if (FOC_LivGguard_U.IIR_Filter_Coefficient.Iq_Filter_switch > 0.0F) {
    rtb_algDD_o2_o = FOC_LivGguard_DW.UnitDelay_DSTATE_f;
  }

  /* End of Switch: '<S4>/Switch1' */

  /* Sum: '<S28>/Sum2' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion1'
   */
  FOC_LivGguard_Y.Iq_error = FOC_LivGguard_Y.Iq_ref_sat - rtb_algDD_o2_o;

  /* Product: '<S73>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S65>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S63>/DProd Out'
   *  Sum: '<S65>/SumD'
   */
  rtb_UkYk1_f = (FOC_LivGguard_Y.Iq_error *
                 FOC_LivGguard_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA -
                 FOC_LivGguard_DW.Filter_DSTATE_d) *
    FOC_LivGguard_U.MTPA_PID.Torque_PID_MTPA.Filter_torque_PID_MTPA;

  /* Sum: '<S80>/Sum' incorporates:
   *  DiscreteIntegrator: '<S70>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S75>/PProd Out'
   */
  rtb_Sum_f = (FOC_LivGguard_Y.Iq_error *
               FOC_LivGguard_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA +
               FOC_LivGguard_DW.Integrator_DSTATE_h) + rtb_UkYk1_f;

  /* Switch: '<S78>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S78>/LowerRelop1'
   *  RelationalOperator: '<S78>/UpperRelop'
   *  Switch: '<S78>/Switch'
   */
  if (rtb_Sum_f > FOC_LivGguard_U.MTPA_PID.Up_Limit_torque_PID) {
    /* Switch: '<S78>/Switch2' */
    FOC_LivGguard_Y.Vq_PID = FOC_LivGguard_U.MTPA_PID.Up_Limit_torque_PID;
  } else if (rtb_Sum_f < FOC_LivGguard_U.MTPA_PID.Low_Limit_torque_PID) {
    /* Switch: '<S78>/Switch2' incorporates:
     *  Switch: '<S78>/Switch'
     */
    FOC_LivGguard_Y.Vq_PID = FOC_LivGguard_U.MTPA_PID.Low_Limit_torque_PID;
  } else {
    /* Switch: '<S78>/Switch2' incorporates:
     *  Switch: '<S78>/Switch'
     */
    FOC_LivGguard_Y.Vq_PID = rtb_Sum_f;
  }

  /* End of Switch: '<S78>/Switch2' */

  /* Sum: '<S5>/Add1' */
  FOC_LivGguard_Y.Vq = FOC_LivGguard_Y.Vq_FF + FOC_LivGguard_Y.Vq_PID;

  /* Switch: '<S27>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S27>/LowerRelop1'
   *  RelationalOperator: '<S27>/UpperRelop'
   *  Switch: '<S27>/Switch'
   */
  if (FOC_LivGguard_Y.Vq > FOC_LivGguard_U.MTPA_PID.Up_Limit_torque_PID) {
    /* Sum: '<S5>/Add1' */
    FOC_LivGguard_Y.Vq = FOC_LivGguard_U.MTPA_PID.Up_Limit_torque_PID;
  } else if (FOC_LivGguard_Y.Vq < FOC_LivGguard_U.MTPA_PID.Low_Limit_torque_PID)
  {
    /* Sum: '<S5>/Add1' incorporates:
     *  Switch: '<S27>/Switch'
     */
    FOC_LivGguard_Y.Vq = FOC_LivGguard_U.MTPA_PID.Low_Limit_torque_PID;
  }

  /* End of Switch: '<S27>/Switch2' */

  /* Outputs for Atomic SubSystem: '<S144>/Two inputs CRL' */
  /* Switch: '<S148>/Switch' incorporates:
   *  Product: '<S147>/dcos'
   *  Product: '<S147>/qsin'
   *  Sum: '<S147>/sum_alpha'
   */
  rtb_Switch_f_idx_0 = FOC_LivGguard_Y.Vd * rtb_Add1_l - FOC_LivGguard_Y.Vq *
    rtb_Add3;

  /* Gain: '<S146>/one_by_two' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S147>/a16'
   */
  rtb_add_c = 0.5 * rtb_Switch_f_idx_0;

  /* Gain: '<S146>/sqrt3_by_two' incorporates:
   *  Product: '<S147>/dsin'
   *  Product: '<S147>/qcos'
   *  Sum: '<S147>/sum_beta'
   */
  rtb_Add3 = (FOC_LivGguard_Y.Vq * rtb_Add1_l + FOC_LivGguard_Y.Vd * rtb_Add3) *
    0.8660254037844386;

  /* End of Outputs for SubSystem: '<S144>/Two inputs CRL' */

  /* Sum: '<S146>/add_b' */
  rtb_Add1_l = rtb_Add3 - rtb_add_c;

  /* Sum: '<S146>/add_c' */
  rtb_add_c = (0.0 - rtb_add_c) - rtb_Add3;

  /* Outputs for Atomic SubSystem: '<S144>/Two inputs CRL' */
  /* Gain: '<S152>/one_by_two' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S147>/a16'
   *  MinMax: '<S152>/Max'
   *  MinMax: '<S152>/Min'
   *  Sum: '<S152>/Add'
   */
  rtb_Add3 = (fmax(fmax(rtb_Switch_f_idx_0, rtb_Add1_l), rtb_add_c) + fmin(fmin
    (rtb_Switch_f_idx_0, rtb_Add1_l), rtb_add_c)) * -0.5;

  /* Outport: '<Root>/Va' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S147>/a16'
   *  Gain: '<S151>/Gain'
   *  Sum: '<S151>/Add3'
   */
  FOC_LivGguard_Y.Va = (rtb_Switch_f_idx_0 + rtb_Add3) * 1.1547005383792517;

  /* End of Outputs for SubSystem: '<S144>/Two inputs CRL' */

  /* Outport: '<Root>/Vb' incorporates:
   *  Gain: '<S151>/Gain'
   *  Sum: '<S151>/Add1'
   */
  FOC_LivGguard_Y.Vb = (rtb_Add1_l + rtb_Add3) * 1.1547005383792517;

  /* Outport: '<Root>/Vc' incorporates:
   *  Gain: '<S151>/Gain'
   *  Sum: '<S151>/Add2'
   */
  FOC_LivGguard_Y.Vc = (rtb_Add3 + rtb_add_c) * 1.1547005383792517;

  /* Outport: '<Root>/Iq' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion1'
   */
  FOC_LivGguard_Y.Iq = rtb_algDD_o2_o;

  /* Switch: '<S4>/Switch' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   */
  if (FOC_LivGguard_U.IIR_Filter_Coefficient.Id_Filter_switch > 0.0F) {
    /* Outport: '<Root>/Id' incorporates:
     *  UnitDelay: '<S19>/Unit Delay'
     */
    FOC_LivGguard_Y.Id = FOC_LivGguard_DW.UnitDelay_DSTATE;
  } else {
    /* Outport: '<Root>/Id' */
    FOC_LivGguard_Y.Id = rtb_algDD_o1_d;
  }

  /* Outport: '<Root>/Id_LUT_FNR' */
  FOC_LivGguard_Y.Id_LUT_FNR = FOC_LivGguard_B.Merge[0];

  /* Outport: '<Root>/Iq_LUT_FNR' */
  FOC_LivGguard_Y.Iq_LUT_FNR = FOC_LivGguard_B.Merge[1];

  /* Delay: '<S3>/Delay' incorporates:
   *  Constant: '<S3>/Constant'
   */
  if (FOC_LivGguard_DW.icLoad_j) {
    FOC_LivGguard_DW.Delay_DSTATE_k = 0.0;
  }

  /* Switch: '<S1>/Switch' incorporates:
   *  Constant: '<S1>/Constant'
   *  Inport: '<Root>/Drive_State'
   *  Inport: '<Root>/Ref_Speed_mech_rpm'
   */
  if (FOC_LivGguard_U.Drive_State > 2.0) {
    rtb_Add3 = 0.0;
  } else {
    rtb_Add3 = FOC_LivGguard_U.Ref_Speed_mech_rpm;
  }

  /* Sum: '<S3>/Difference Inputs1' incorporates:
   *  Delay: '<S3>/Delay'
   *  Switch: '<S1>/Switch'
   *
   * Block description for '<S3>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_add_c = rtb_Add3 - FOC_LivGguard_DW.Delay_DSTATE_k;

  /* Product: '<S3>/delta rise limit' incorporates:
   *  Inport: '<Root>/Ref_Speed_rate_up'
   *  SampleTimeMath: '<S3>/sample time'
   *
   * About '<S3>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_Add3 = FOC_LivGguard_U.Ref_Speed_rate_up * 0.0001;

  /* Switch: '<S219>/Switch2' incorporates:
   *  RelationalOperator: '<S219>/LowerRelop1'
   */
  if (!(rtb_add_c > rtb_Add3)) {
    /* Product: '<S3>/delta fall limit' incorporates:
     *  Inport: '<Root>/Ref_Speed_rate_down'
     *  SampleTimeMath: '<S3>/sample time'
     *
     * About '<S3>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_Add3 = 0.0001 * FOC_LivGguard_U.Ref_Speed_rate_down;

    /* Switch: '<S219>/Switch' incorporates:
     *  RelationalOperator: '<S219>/UpperRelop'
     */
    if (!(rtb_add_c < rtb_Add3)) {
      rtb_Add3 = rtb_add_c;
    }

    /* End of Switch: '<S219>/Switch' */
  }

  /* End of Switch: '<S219>/Switch2' */

  /* Sum: '<S3>/Difference Inputs2' incorporates:
   *  Delay: '<S3>/Delay'
   *
   * Block description for '<S3>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_LivGguard_Y.Ref_Speed_mech_rpm_out = rtb_Add3 +
    FOC_LivGguard_DW.Delay_DSTATE_k;

  /* Outport: '<Root>/Speed_error' incorporates:
   *  Gain: '<S1>/rpm to Rad//sec'
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   *  Sum: '<S9>/Subtract'
   */
  FOC_LivGguard_Y.Speed_error = 0.10471975511965977 *
    FOC_LivGguard_Y.Ref_Speed_mech_rpm_out -
    FOC_LivGguard_U.ActualSpeed_mech_radsec;

  /* Outport: '<Root>/Pole_pairsb' incorporates:
   *  Inport: '<Root>/Pole_pairs'
   */
  FOC_LivGguard_Y.Pole_pairsb = FOC_LivGguard_U.p;

  /* Update for Delay: '<S8>/Delay' */
  FOC_LivGguard_DW.icLoad = false;
  FOC_LivGguard_DW.Delay_DSTATE = FOC_LivGguard_Y.T_gen;

  /* Update for Delay: '<S154>/Delay' */
  FOC_LivGguard_DW.icLoad_b = false;
  FOC_LivGguard_DW.Delay_DSTATE_b = FOC_LivGguard_Y.Id_ref;

  /* Update for DiscreteIntegrator: '<S124>/Integrator' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S121>/IProd Out'
   *  Sum: '<S116>/SumI2'
   *  Sum: '<S116>/SumI4'
   *  Sum: '<S136>/SumI3'
   *  Sum: '<S137>/SumI1'
   */
  FOC_LivGguard_DW.Integrator_DSTATE += ((FOC_LivGguard_Y.Id_error *
    FOC_LivGguard_U.MTPA_PID.Flux_PID_MTPA.Ki_flux_PID_MTPA +
    (FOC_LivGguard_Y.Vd_PID - FOC_LivGguard_Y.Vd_PID)) + (FOC_LivGguard_Y.Vd_PID
    - rtb_Switch)) * 0.0001;
  if (FOC_LivGguard_DW.Integrator_DSTATE > SVM_VOLTAGE_LIMIT) {
    FOC_LivGguard_DW.Integrator_DSTATE = SVM_VOLTAGE_LIMIT;
  } else if (FOC_LivGguard_DW.Integrator_DSTATE < -SVM_VOLTAGE_LIMIT) {
    FOC_LivGguard_DW.Integrator_DSTATE = -SVM_VOLTAGE_LIMIT;
  }

  /* End of Update for DiscreteIntegrator: '<S124>/Integrator' */

  /* Update for DiscreteIntegrator: '<S119>/Filter' */
  FOC_LivGguard_DW.Filter_DSTATE += 0.0001 * rtb_deltafalllimit_a;

  /* Update for Delay: '<S155>/Delay' */
  FOC_LivGguard_DW.icLoad_n = false;
  FOC_LivGguard_DW.Delay_DSTATE_bc = FOC_LivGguard_Y.Iq_ref;

  /* Update for DiscreteIntegrator: '<S70>/Integrator' incorporates:
   *  Gain: '<S82>/Kt'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S67>/IProd Out'
   *  Sum: '<S62>/SumI2'
   *  Sum: '<S62>/SumI4'
   *  Sum: '<S82>/SumI3'
   *  Sum: '<S83>/SumI1'
   */
  FOC_LivGguard_DW.Integrator_DSTATE_h += (((FOC_LivGguard_Y.Vq_PID -
    FOC_LivGguard_Y.Vq_PID) * -10.0 + FOC_LivGguard_Y.Iq_error *
    FOC_LivGguard_U.MTPA_PID.Torque_PID_MTPA.Ki_torque_PID_MTPA) +
    (FOC_LivGguard_Y.Vq_PID - rtb_Sum_f)) * 0.0001;
  if (FOC_LivGguard_DW.Integrator_DSTATE_h > SVM_VOLTAGE_LIMIT) {
    FOC_LivGguard_DW.Integrator_DSTATE_h = SVM_VOLTAGE_LIMIT;
  } else if (FOC_LivGguard_DW.Integrator_DSTATE_h < -SVM_VOLTAGE_LIMIT) {
    FOC_LivGguard_DW.Integrator_DSTATE_h = -SVM_VOLTAGE_LIMIT;
  }

  /* End of Update for DiscreteIntegrator: '<S70>/Integrator' */

  /* Update for DiscreteIntegrator: '<S65>/Filter' */
  FOC_LivGguard_DW.Filter_DSTATE_d += 0.0001 * rtb_UkYk1_f;

  /* Update for Delay: '<S3>/Delay' */
  FOC_LivGguard_DW.icLoad_j = false;
  FOC_LivGguard_DW.Delay_DSTATE_k = FOC_LivGguard_Y.Ref_Speed_mech_rpm_out;
}

/* Model step function for TID1 */
void FOC_LivGguard_step1(void)         /* Sample time: [0.001s, 0.0s] */
{
  double rtb_NProdOut_j;
  double rtb_Sum_o;

  /* Product: '<S203>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S195>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S193>/DProd Out'
   *  Sum: '<S195>/SumD'
   */
  rtb_NProdOut_j = (FOC_LivGguard_Y.Speed_error *
                    FOC_LivGguard_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA -
                    FOC_LivGguard_DW.Filter_DSTATE_i) *
    FOC_LivGguard_U.MTPA_PID.Speed_PID_MTPA.Filter_speed_PID_MTPA;

  /* Sum: '<S210>/Sum' incorporates:
   *  DiscreteIntegrator: '<S200>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S205>/PProd Out'
   */
  rtb_Sum_o = (FOC_LivGguard_Y.Speed_error *
               FOC_LivGguard_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA +
               FOC_LivGguard_DW.Integrator_DSTATE_b) + rtb_NProdOut_j;

  /* Switch: '<S208>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S208>/LowerRelop1'
   *  RelationalOperator: '<S208>/UpperRelop'
   *  Switch: '<S208>/Switch'
   */
  if (rtb_Sum_o > FOC_LivGguard_U.MTPA_PID.Up_Limit_speed_PID_MTPA) {
    /* Switch: '<S208>/Switch2' */
    FOC_LivGguard_Y.Iq_gen = FOC_LivGguard_U.MTPA_PID.Up_Limit_speed_PID_MTPA;
  } else if (rtb_Sum_o < FOC_LivGguard_U.MTPA_PID.Low_Limit_speed_PID_MTPA) {
    /* Switch: '<S208>/Switch2' incorporates:
     *  Switch: '<S208>/Switch'
     */
    FOC_LivGguard_Y.Iq_gen = FOC_LivGguard_U.MTPA_PID.Low_Limit_speed_PID_MTPA;
  } else {
    /* Switch: '<S208>/Switch2' incorporates:
     *  Switch: '<S208>/Switch'
     */
    FOC_LivGguard_Y.Iq_gen = rtb_Sum_o;
  }

  /* End of Switch: '<S208>/Switch2' */

  /* RateTransition: '<S2>/Rate Transition' */
  FOC_LivGguard_DW.RateTransition_Buffer0 = FOC_LivGguard_Y.Iq_gen;

  /* Update for DiscreteIntegrator: '<S200>/Integrator' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S197>/IProd Out'
   *  Sum: '<S192>/SumI2'
   *  Sum: '<S192>/SumI4'
   *  Sum: '<S212>/SumI3'
   *  Sum: '<S213>/SumI1'
   */
  FOC_LivGguard_DW.Integrator_DSTATE_b += ((FOC_LivGguard_Y.Speed_error *
    FOC_LivGguard_U.MTPA_PID.Speed_PID_MTPA.Ki_speed_PID_MTPA +
    (FOC_LivGguard_Y.Iq_gen - FOC_LivGguard_Y.Iq_gen)) + (FOC_LivGguard_Y.Iq_gen
    - rtb_Sum_o)) * 0.001;
  if (FOC_LivGguard_DW.Integrator_DSTATE_b > MOTOR_PEAK_AC) {
    FOC_LivGguard_DW.Integrator_DSTATE_b = MOTOR_PEAK_AC;
  } else if (FOC_LivGguard_DW.Integrator_DSTATE_b < -MOTOR_PEAK_AC) {
    FOC_LivGguard_DW.Integrator_DSTATE_b = -MOTOR_PEAK_AC;
  }

  /* End of Update for DiscreteIntegrator: '<S200>/Integrator' */

  /* Update for DiscreteIntegrator: '<S195>/Filter' */
  FOC_LivGguard_DW.Filter_DSTATE_i += 0.001 * rtb_NProdOut_j;
}

/* Model initialize function */
void FOC_LivGguard_initialize(void)
{
  /* InitializeConditions for Delay: '<S8>/Delay' */
  FOC_LivGguard_DW.icLoad = true;

  /* InitializeConditions for Delay: '<S154>/Delay' */
  FOC_LivGguard_DW.icLoad_b = true;

  /* InitializeConditions for Delay: '<S155>/Delay' */
  FOC_LivGguard_DW.icLoad_n = true;

  /* InitializeConditions for Delay: '<S3>/Delay' */
  FOC_LivGguard_DW.icLoad_j = true;

  FOC_LivGguard_U.BusVoltage_V = OP_VOLTAGE;
  FOC_LivGguard_U.Iq_Torque_ratio = CURR_TORQUE_RATIO;
  FOC_LivGguard_U.p = POLEPAIRS;

  /* Id Iq Limits */
  FOC_LivGguard_U.Id_Iq_MTPA_limit.Iq_up_limit = 300.0f;
  FOC_LivGguard_U.Id_Iq_MTPA_limit.Iq_low_limit = -300.0f;
  FOC_LivGguard_U.Id_Iq_MTPA_limit.Id_up_limit = 300.0f;
  FOC_LivGguard_U.Id_Iq_MTPA_limit.Id_low_limit = -300.0f;
  
  /* Speed Ref Rate Limiter Settings */
  FOC_LivGguard_U.Ref_Speed_rate_up = 100.0f * 10000.0f;
  FOC_LivGguard_U.Ref_Speed_rate_down = -100.0f * 10000.0f;

  /* Rate Limiter Settings */
  FOC_LivGguard_U.Rate_limiter.Torque_gen_ramp_up = 50.0f * 10000.0f;
  FOC_LivGguard_U.Rate_limiter.Torque_gen_ramp_down = -50.0f * 10000.0f;
  FOC_LivGguard_U.Rate_limiter.Iq_ramp_up = 50.0f * 10000.0f;
  FOC_LivGguard_U.Rate_limiter.Iq_ramp_down = -50.0f * 10000.0f;
  FOC_LivGguard_U.Rate_limiter.Id_ramp_up = 50.0f * 10000.0f;
  FOC_LivGguard_U.Rate_limiter.Id_ramp_down = -50.0f * 10000.0f;

  /* Speed PID Values */
  FOC_LivGguard_U.MTPA_PID.Up_Limit_speed_PID_MTPA = MOTOR_PEAK_AC;
  FOC_LivGguard_U.MTPA_PID.Low_Limit_speed_PID_MTPA = 0.0f;
  FOC_LivGguard_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA = 4.0f;
  FOC_LivGguard_U.MTPA_PID.Speed_PID_MTPA.Ki_speed_PID_MTPA = 8.0f;
  FOC_LivGguard_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA = 0.00001f;
  FOC_LivGguard_U.MTPA_PID.Speed_PID_MTPA.Filter_speed_PID_MTPA = 5.0f;

  /* Iq PID Values */
  FOC_LivGguard_U.MTPA_PID.Up_Limit_torque_PID = SVM_VOLTAGE_LIMIT;
  FOC_LivGguard_U.MTPA_PID.Low_Limit_torque_PID = -SVM_VOLTAGE_LIMIT;
  FOC_LivGguard_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA = 0.1f;
  FOC_LivGguard_U.MTPA_PID.Torque_PID_MTPA.Ki_torque_PID_MTPA = 7.0f;
  FOC_LivGguard_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA = 0.00001f;
  FOC_LivGguard_U.MTPA_PID.Torque_PID_MTPA.Filter_torque_PID_MTPA = 5.0f;

  /* Id PID Values */
  FOC_LivGguard_U.MTPA_PID.Up_Limit_flux_PID = SVM_VOLTAGE_LIMIT;
  FOC_LivGguard_U.MTPA_PID.Low_Limit_flux_PID = -SVM_VOLTAGE_LIMIT;
  FOC_LivGguard_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA = 0.2f;
  FOC_LivGguard_U.MTPA_PID.Flux_PID_MTPA.Ki_flux_PID_MTPA = 6.0f;
  FOC_LivGguard_U.MTPA_PID.Flux_PID_MTPA.Kd_flux_PID_MTPA = 0.00001f;
  FOC_LivGguard_U.MTPA_PID.Flux_PID_MTPA.Filter_flux_PID_MTPA = 5.0f;

  /* IIR Filter Coefficients */
  FOC_LivGguard_U.IIR_Filter_Coefficient.Id_Filter_switch = 1.0f;
  FOC_LivGguard_U.IIR_Filter_Coefficient.Iq_Filter_switch = 1.0f;
  FOC_LivGguard_U.IIR_Filter_Coefficient.Id_Filter_coefficient = 0.9f;
  FOC_LivGguard_U.IIR_Filter_Coefficient.Iq_Filter_coefficient = 0.9f; 

  FOC_LivGguard_U.Speed_1_Torque_0 = 1.0f;
  FOC_LivGguard_U.RefTrq = 0.0f;
}

/* Model terminate function */
void FOC_LivGguard_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
