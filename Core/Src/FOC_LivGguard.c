/*
 * File: FOC_LivGguard.c
 *
 * Code generated for Simulink model 'FOC_LivGguard'.
 *
 * Model version                  : 18.309
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Feb  5 16:05:38 2026
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
  double rtb_Iq_Table;
  double rtb_Product1;
  double rtb_Sum;
  double rtb_Switch_f_idx_0;
  double rtb_TrigonometricFunction1_tmp;
  double rtb_add_c;
  double rtb_deltafalllimit_a;
  double rtb_deltafalllimit_d;
  float rtb_Gain_j;
  float rtb_algDD_o1_d;
  float rtb_algDD_o2_o;

  /* Product: '<S155>/delta fall limit' incorporates:
   *  Abs: '<S7>/Abs'
   *  Gain: '<S7>/Rad//sec to RPM'
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   */
  FOC_LivGguard_Y.Iq_error = fabs(9.5492965855137211 * FOC_LivGguard_U.MtrSpd);

  /* Product: '<S2>/Product1' incorporates:
   *  Inport: '<Root>/Iq_Torque_ratio'
   */
  rtb_Product1 = FOC_LivGguard_U.Iq_Torque_ratio * FOC_LivGguard_B.Switch2;

  /* Delay: '<S8>/Delay' */
  if (FOC_LivGguard_DW.icLoad) {
    /* Sum: '<S8>/Difference Inputs2'
     *
     * Block description for '<S8>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_LivGguard_DW.Delay_DSTATE = rtb_Product1;
  }

  /* Product: '<S8>/delta rise limit' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  SampleTimeMath: '<S8>/sample time'
   *
   * About '<S8>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_deltafalllimit_d = FOC_LivGguard_U.Rate_limiter.Torque_gen_ramp_up *
    0.0001;

  /* Sum: '<S8>/Difference Inputs1' incorporates:
   *  Delay: '<S8>/Delay'
   *
   * Block description for '<S8>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Product1 -= FOC_LivGguard_DW.Delay_DSTATE;

  /* Switch: '<S160>/Switch2' incorporates:
   *  RelationalOperator: '<S160>/LowerRelop1'
   */
  if (!(rtb_Product1 > rtb_deltafalllimit_d)) {
    /* Product: '<S8>/delta fall limit' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  SampleTimeMath: '<S8>/sample time'
     *
     * About '<S8>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_deltafalllimit_d = 0.0001 *
      FOC_LivGguard_U.Rate_limiter.Torque_gen_ramp_down;

    /* Switch: '<S160>/Switch' incorporates:
     *  RelationalOperator: '<S160>/UpperRelop'
     */
    if (!(rtb_Product1 < rtb_deltafalllimit_d)) {
      rtb_deltafalllimit_d = rtb_Product1;
    }

    /* End of Switch: '<S160>/Switch' */
  }

  /* End of Switch: '<S160>/Switch2' */

  /* Sum: '<S8>/Difference Inputs2' incorporates:
   *  Delay: '<S8>/Delay'
   *
   * Block description for '<S8>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_LivGguard_DW.Delay_DSTATE += rtb_deltafalllimit_d;

  /* Switch: '<S2>/Switch' incorporates:
   *  Inport: '<Root>/Speed_1_Torque_0'
   *  Inport: '<Root>/T_ref'
   */
  if (FOC_LivGguard_U.Speed_1_Torque_0 > 0.0) {
    rtb_deltafalllimit_d = FOC_LivGguard_DW.Delay_DSTATE;
  } else {
    rtb_deltafalllimit_d = FOC_LivGguard_U.RefTrq;
  }

  /* End of Switch: '<S2>/Switch' */

  /* Lookup_n-D: '<S7>/Id_Table' incorporates:
   *  Sum: '<S151>/Add3'
   *  Sum: '<S28>/Sum2'
   */
  rtb_Product1 = look2_binlx(FOC_LivGguard_Y.Iq_error, rtb_deltafalllimit_d,
    FOC_LivGguard_ConstP.pooled3, FOC_LivGguard_ConstP.pooled4,
    FOC_LivGguard_ConstP.Id_Table_tableData, FOC_LivGguard_ConstP.pooled10, 27U);

  /* Delay: '<S154>/Delay' */
  if (FOC_LivGguard_DW.icLoad_b) {
    FOC_LivGguard_DW.Delay_DSTATE_b = rtb_Product1;
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
  rtb_Product1 -= FOC_LivGguard_DW.Delay_DSTATE_b;

  /* Switch: '<S158>/Switch2' incorporates:
   *  RelationalOperator: '<S158>/LowerRelop1'
   */
  if (!(rtb_Product1 > rtb_deltafalllimit_a)) {
    /* Product: '<S154>/delta fall limit' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  SampleTimeMath: '<S154>/sample time'
     *
     * About '<S154>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_deltafalllimit_a = 0.0001 * FOC_LivGguard_U.Rate_limiter.Id_ramp_down;

    /* Switch: '<S158>/Switch' incorporates:
     *  RelationalOperator: '<S158>/UpperRelop'
     */
    if (!(rtb_Product1 < rtb_deltafalllimit_a)) {
      rtb_deltafalllimit_a = rtb_Product1;
    }

    /* End of Switch: '<S158>/Switch' */
  }

  /* End of Switch: '<S158>/Switch2' */

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
    rtb_deltafalllimit_a = FOC_LivGguard_U.Id_Iq_MTPA_limit.Id_up_limit;
  } else if (FOC_LivGguard_Y.Id_ref <
             FOC_LivGguard_U.Id_Iq_MTPA_limit.Id_low_limit) {
    /* Switch: '<S156>/Switch' */
    rtb_deltafalllimit_a = FOC_LivGguard_U.Id_Iq_MTPA_limit.Id_low_limit;
  } else {
    rtb_deltafalllimit_a = FOC_LivGguard_Y.Id_ref;
  }

  /* End of Switch: '<S156>/Switch2' */

  /* Outputs for Atomic SubSystem: '<S15>/Two phase CRL wrap' */
  /* Gain: '<S16>/one_by_sqrt3' incorporates:
   *  Inport: '<Root>/Phase Current'
   *  Sum: '<S16>/a_plus_2b'
   */
  rtb_Product1 = ((FOC_LivGguard_U.PhaseCurrent[0] +
                   FOC_LivGguard_U.PhaseCurrent[1]) +
                  FOC_LivGguard_U.PhaseCurrent[1]) * 0.57735026918962584;

  /* End of Outputs for SubSystem: '<S15>/Two phase CRL wrap' */

  /* Trigonometry: '<S4>/Trigonometric Function' incorporates:
   *  Inport: '<Root>/angle'
   *  Trigonometry: '<S6>/Trigonometric Function1'
   */
  rtb_Add1_l = sin(FOC_LivGguard_U.MtrElcPos);

  /* Trigonometry: '<S4>/Trigonometric Function1' incorporates:
   *  Inport: '<Root>/angle'
   *  Trigonometry: '<S6>/Trigonometric Function'
   */
  rtb_TrigonometricFunction1_tmp = cos(FOC_LivGguard_U.MtrElcPos);

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
  rtb_algDD_o1_d = (float)(FOC_LivGguard_U.PhaseCurrent[0] *
    rtb_TrigonometricFunction1_tmp + rtb_Product1 * rtb_Add1_l);
  rtb_algDD_o2_o = (float)(rtb_Product1 * rtb_TrigonometricFunction1_tmp -
    FOC_LivGguard_U.PhaseCurrent[0] * rtb_Add1_l);

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
  FOC_LivGguard_Y.Id_error = rtb_deltafalllimit_a - rtb_Gain_j;

  /* Product: '<S127>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S119>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S117>/DProd Out'
   *  Sum: '<S119>/SumD'
   */
  rtb_Product1 = (FOC_LivGguard_Y.Id_error *
                  FOC_LivGguard_U.MTPA_PID.Flux_PID_MTPA.Kd_flux_PID_MTPA -
                  FOC_LivGguard_DW.Filter_DSTATE) *
    FOC_LivGguard_U.MTPA_PID.Flux_PID_MTPA.Filter_flux_PID_MTPA;

  /* Sum: '<S134>/Sum' incorporates:
   *  DiscreteIntegrator: '<S124>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S129>/PProd Out'
   */
  rtb_Sum = (FOC_LivGguard_Y.Id_error *
             FOC_LivGguard_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA +
             FOC_LivGguard_DW.Integrator_DSTATE) + rtb_Product1;

  /* Switch: '<S132>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S132>/LowerRelop1'
   *  RelationalOperator: '<S132>/UpperRelop'
   *  Switch: '<S132>/Switch'
   */
  if (rtb_Sum > FOC_LivGguard_U.MTPA_PID.Up_Limit_flux_PID) {
    /* Switch: '<S132>/Switch2' */
    FOC_LivGguard_Y.Vd_PID = FOC_LivGguard_U.MTPA_PID.Up_Limit_flux_PID;
  } else if (rtb_Sum < FOC_LivGguard_U.MTPA_PID.Low_Limit_flux_PID) {
    /* Switch: '<S132>/Switch2' incorporates:
     *  Switch: '<S132>/Switch'
     */
    FOC_LivGguard_Y.Vd_PID = FOC_LivGguard_U.MTPA_PID.Low_Limit_flux_PID;
  } else {
    /* Switch: '<S132>/Switch2' incorporates:
     *  Switch: '<S132>/Switch'
     */
    FOC_LivGguard_Y.Vd_PID = rtb_Sum;
  }

  /* End of Switch: '<S132>/Switch2' */

  /* Gain: '<S5>/Gain' incorporates:
   *  Inport: '<Root>/Bus_Voltage'
   */
  rtb_Gain_j = 0.577350259F * FOC_LivGguard_U.BusVoltage_V;

  /* Switch: '<S78>/Switch2' incorporates:
   *  Abs: '<S10>/Abs'
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   */
  FOC_LivGguard_Y.Vq_PID = fabs(FOC_LivGguard_U.MtrSpd);

  /* Lookup_n-D: '<S7>/Iq_Table' incorporates:
   *  Sum: '<S151>/Add3'
   *  Sum: '<S28>/Sum2'
   */
  rtb_Iq_Table = look2_binlx(FOC_LivGguard_Y.Iq_error, rtb_deltafalllimit_d,
    FOC_LivGguard_ConstP.pooled3, FOC_LivGguard_ConstP.pooled4,
    FOC_LivGguard_ConstP.Iq_Table_tableData, FOC_LivGguard_ConstP.pooled10, 27U);

  /* Delay: '<S155>/Delay' */
  if (FOC_LivGguard_DW.icLoad_n) {
    FOC_LivGguard_DW.Delay_DSTATE_bc = rtb_Iq_Table;
  }

  /* Product: '<S155>/delta fall limit' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  Product: '<S155>/delta rise limit'
   *  SampleTimeMath: '<S155>/sample time'
   *
   * About '<S155>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  FOC_LivGguard_Y.Iq_error = FOC_LivGguard_U.Rate_limiter.Iq_ramp_up * 0.0001;

  /* Sum: '<S155>/Difference Inputs1' incorporates:
   *  Delay: '<S155>/Delay'
   *
   * Block description for '<S155>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Iq_Table -= FOC_LivGguard_DW.Delay_DSTATE_bc;

  /* Switch: '<S159>/Switch2' incorporates:
   *  RelationalOperator: '<S159>/LowerRelop1'
   */
  if (!(rtb_Iq_Table > FOC_LivGguard_Y.Iq_error)) {
    /* Product: '<S155>/delta fall limit' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  SampleTimeMath: '<S155>/sample time'
     *
     * About '<S155>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    FOC_LivGguard_Y.Iq_error = 0.0001 *
      FOC_LivGguard_U.Rate_limiter.Iq_ramp_down;

    /* Switch: '<S159>/Switch' incorporates:
     *  RelationalOperator: '<S159>/UpperRelop'
     */
    if (!(rtb_Iq_Table < FOC_LivGguard_Y.Iq_error)) {
      /* Product: '<S155>/delta fall limit' */
      FOC_LivGguard_Y.Iq_error = rtb_Iq_Table;
    }

    /* End of Switch: '<S159>/Switch' */
  }

  /* End of Switch: '<S159>/Switch2' */

  /* Sum: '<S155>/Difference Inputs2' incorporates:
   *  Delay: '<S155>/Delay'
   *
   * Block description for '<S155>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_LivGguard_Y.Iq_ref = FOC_LivGguard_Y.Iq_error +
    FOC_LivGguard_DW.Delay_DSTATE_bc;

  if (d.forward_pin == GPIO_PIN_RESET && d.reverse_pin == GPIO_PIN_SET)
    FOC_LivGguard_Y.Iq_ref *= 1.0f;
  else if (d.forward_pin == GPIO_PIN_SET && d.reverse_pin == GPIO_PIN_RESET)
    FOC_LivGguard_Y.Iq_ref *= -1.0f;
  else {
    FOC_LivGguard_Y.Iq_ref = 0.0f;
    FOC_LivGguard_Y.Id_ref = 0.0f;
  }

  /* Switch: '<S157>/Switch2' incorporates:
   *  Inport: '<Root>/Id_Iq_MTPA_limit'
   *  RelationalOperator: '<S157>/LowerRelop1'
   *  RelationalOperator: '<S157>/UpperRelop'
   *  Switch: '<S157>/Switch'
   */
  if (FOC_LivGguard_Y.Iq_ref > FOC_LivGguard_U.Id_Iq_MTPA_limit.Iq_up_limit) {
    /* Product: '<S155>/delta fall limit' */
    FOC_LivGguard_Y.Iq_error = FOC_LivGguard_U.Id_Iq_MTPA_limit.Iq_up_limit;
  } else if (FOC_LivGguard_Y.Iq_ref <
             FOC_LivGguard_U.Id_Iq_MTPA_limit.Iq_low_limit) {
    /* Product: '<S155>/delta fall limit' incorporates:
     *  Switch: '<S157>/Switch'
     */
    FOC_LivGguard_Y.Iq_error = FOC_LivGguard_U.Id_Iq_MTPA_limit.Iq_low_limit;
  } else {
    /* Product: '<S155>/delta fall limit' incorporates:
     *  Switch: '<S157>/Switch'
     */
    FOC_LivGguard_Y.Iq_error = FOC_LivGguard_Y.Iq_ref;
  }

  /* End of Switch: '<S157>/Switch2' */

  /* Gain: '<S31>/wm_pu2si_mech2elec' incorporates:
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   */
  rtb_add_c = POLEPAIRS * FOC_LivGguard_U.MtrSpd;

  /* Gain: '<S31>/NegSign' incorporates:
   *  Gain: '<S10>/Gain1'
   *  Lookup_n-D: '<S10>/Lq_Table'
   *  Product: '<S31>/prod1'
   *  Sum: '<S151>/Add3'
   *  Switch: '<S78>/Switch2'
   */
  rtb_Iq_Table = -(0.001 * look2_binlx(FOC_LivGguard_Y.Vq_PID,
    rtb_deltafalllimit_d, FOC_LivGguard_ConstP.pooled3,
    FOC_LivGguard_ConstP.pooled4, FOC_LivGguard_ConstP.Lq_Table_tableData,
    FOC_LivGguard_ConstP.pooled10, 27U) * FOC_LivGguard_Y.Iq_error * rtb_add_c);

  /* Switch: '<S33>/Switch2' incorporates:
   *  RelationalOperator: '<S33>/LowerRelop1'
   *  RelationalOperator: '<S33>/UpperRelop'
   *  Switch: '<S31>/Switch'
   *  Switch: '<S33>/Switch'
   *  UnaryMinus: '<S31>/Unary Minus'
   */
  if (rtb_Iq_Table > rtb_Gain_j) {
    rtb_Iq_Table = rtb_Gain_j;
  } else if (rtb_Iq_Table < -rtb_Gain_j) {
    /* Switch: '<S33>/Switch' incorporates:
     *  UnaryMinus: '<S31>/Unary Minus'
     */
    rtb_Iq_Table = -rtb_Gain_j;
  }

  /* Sum: '<S5>/Add' incorporates:
   *  Switch: '<S33>/Switch2'
   */
  FOC_LivGguard_Y.Vd = FOC_LivGguard_Y.Vd_PID + rtb_Iq_Table;

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

  /* Product: '<S31>/prod2' incorporates:
   *  Gain: '<S10>/Gain'
   *  Gain: '<S10>/Gain2'
   *  Lookup_n-D: '<S10>/Flux_Table'
   *  Lookup_n-D: '<S10>/Ld_Table'
   *  Product: '<S31>/prod3'
   *  Sum: '<S151>/Add3'
   *  Sum: '<S31>/add1'
   *  Switch: '<S78>/Switch2'
   */
  rtb_deltafalllimit_d = (0.001 * look2_binlx(FOC_LivGguard_Y.Vq_PID,
    rtb_deltafalllimit_d, FOC_LivGguard_ConstP.pooled3,
    FOC_LivGguard_ConstP.pooled4, FOC_LivGguard_ConstP.Ld_Table_tableData,
    FOC_LivGguard_ConstP.pooled10, 27U) * rtb_deltafalllimit_a + 0.001 *
    look2_binlx(FOC_LivGguard_Y.Vq_PID, rtb_deltafalllimit_d,
                FOC_LivGguard_ConstP.pooled3, FOC_LivGguard_ConstP.pooled4,
                FOC_LivGguard_ConstP.Flux_Table_tableData,
                FOC_LivGguard_ConstP.pooled10, 27U)) * rtb_add_c;

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

  /* Product: '<S155>/delta fall limit' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion1'
   *  Sum: '<S28>/Sum2'
   */
  FOC_LivGguard_Y.Iq_error -= rtb_algDD_o2_o;

  /* Product: '<S73>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S65>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S63>/DProd Out'
   *  Sum: '<S65>/SumD'
   */
  rtb_deltafalllimit_a = (FOC_LivGguard_Y.Iq_error *
    FOC_LivGguard_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA -
    FOC_LivGguard_DW.Filter_DSTATE_d) *
    FOC_LivGguard_U.MTPA_PID.Torque_PID_MTPA.Filter_torque_PID_MTPA;

  /* Sum: '<S80>/Sum' incorporates:
   *  DiscreteIntegrator: '<S70>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S75>/PProd Out'
   */
  rtb_Iq_Table = (FOC_LivGguard_Y.Iq_error *
                  FOC_LivGguard_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA +
                  FOC_LivGguard_DW.Integrator_DSTATE_h) + rtb_deltafalllimit_a;

  /* Switch: '<S78>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S78>/LowerRelop1'
   *  RelationalOperator: '<S78>/UpperRelop'
   *  Switch: '<S78>/Switch'
   */
  if (rtb_Iq_Table > FOC_LivGguard_U.MTPA_PID.Up_Limit_torque_PID) {
    /* Switch: '<S78>/Switch2' */
    FOC_LivGguard_Y.Vq_PID = FOC_LivGguard_U.MTPA_PID.Up_Limit_torque_PID;
  } else if (rtb_Iq_Table < FOC_LivGguard_U.MTPA_PID.Low_Limit_torque_PID) {
    /* Switch: '<S78>/Switch2' incorporates:
     *  Switch: '<S78>/Switch'
     */
    FOC_LivGguard_Y.Vq_PID = FOC_LivGguard_U.MTPA_PID.Low_Limit_torque_PID;
  } else {
    /* Switch: '<S78>/Switch2' incorporates:
     *  Switch: '<S78>/Switch'
     */
    FOC_LivGguard_Y.Vq_PID = rtb_Iq_Table;
  }

  /* End of Switch: '<S78>/Switch2' */

  /* Switch: '<S34>/Switch2' incorporates:
   *  RelationalOperator: '<S34>/LowerRelop1'
   *  RelationalOperator: '<S34>/UpperRelop'
   *  Switch: '<S31>/Switch'
   *  Switch: '<S34>/Switch'
   *  UnaryMinus: '<S31>/Unary Minus'
   */
  if (rtb_deltafalllimit_d > rtb_Gain_j) {
    rtb_deltafalllimit_d = rtb_Gain_j;
  } else if (rtb_deltafalllimit_d < -rtb_Gain_j) {
    /* Switch: '<S34>/Switch' incorporates:
     *  UnaryMinus: '<S31>/Unary Minus'
     */
    rtb_deltafalllimit_d = -rtb_Gain_j;
  }

  /* Sum: '<S5>/Add1' incorporates:
   *  Switch: '<S34>/Switch2'
   */
  FOC_LivGguard_Y.Vq = rtb_deltafalllimit_d + FOC_LivGguard_Y.Vq_PID;

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
  rtb_Switch_f_idx_0 = FOC_LivGguard_Y.Vd * rtb_TrigonometricFunction1_tmp -
    FOC_LivGguard_Y.Vq * rtb_Add1_l;

  /* Gain: '<S146>/one_by_two' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S147>/a16'
   */
  rtb_add_c = 0.5 * rtb_Switch_f_idx_0;

  /* Gain: '<S146>/sqrt3_by_two' incorporates:
   *  Product: '<S147>/dsin'
   *  Product: '<S147>/qcos'
   *  Sum: '<S147>/sum_beta'
   */
  rtb_deltafalllimit_d = (FOC_LivGguard_Y.Vq * rtb_TrigonometricFunction1_tmp +
    FOC_LivGguard_Y.Vd * rtb_Add1_l) * 0.8660254037844386;

  /* End of Outputs for SubSystem: '<S144>/Two inputs CRL' */

  /* Sum: '<S146>/add_b' */
  rtb_Add1_l = rtb_deltafalllimit_d - rtb_add_c;

  /* Sum: '<S146>/add_c' */
  rtb_add_c = (0.0 - rtb_add_c) - rtb_deltafalllimit_d;

  /* Outputs for Atomic SubSystem: '<S144>/Two inputs CRL' */
  /* Gain: '<S152>/one_by_two' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S147>/a16'
   *  MinMax: '<S152>/Max'
   *  MinMax: '<S152>/Min'
   *  Sum: '<S152>/Add'
   */
  rtb_deltafalllimit_d = (fmax(fmax(rtb_Switch_f_idx_0, rtb_Add1_l), rtb_add_c)
    + fmin(fmin(rtb_Switch_f_idx_0, rtb_Add1_l), rtb_add_c)) * -0.5;

  /* Outport: '<Root>/Va' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S147>/a16'
   *  Gain: '<S151>/Gain'
   *  Sum: '<S151>/Add3'
   */
  FOC_LivGguard_Y.Va = (rtb_Switch_f_idx_0 + rtb_deltafalllimit_d) *
    1.1547005383792517;

  /* End of Outputs for SubSystem: '<S144>/Two inputs CRL' */

  /* Outport: '<Root>/Vb' incorporates:
   *  Gain: '<S151>/Gain'
   *  Sum: '<S151>/Add1'
   */
  FOC_LivGguard_Y.Vb = (rtb_Add1_l + rtb_deltafalllimit_d) * 1.1547005383792517;

  /* Outport: '<Root>/Vc' incorporates:
   *  Gain: '<S151>/Gain'
   *  Sum: '<S151>/Add2'
   */
  FOC_LivGguard_Y.Vc = (rtb_deltafalllimit_d + rtb_add_c) * 1.1547005383792517;

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

  /* Product: '<S3>/delta rise limit' incorporates:
   *  Inport: '<Root>/Ref_Speed_rate_up'
   *  SampleTimeMath: '<S3>/sample time'
   *
   * About '<S3>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_deltafalllimit_d = FOC_LivGguard_U.Ref_Speed_rate_up * 0.0001;

  /* Delay: '<S3>/Delay' */
  if (FOC_LivGguard_DW.icLoad_g) {
    /* Sum: '<S3>/Difference Inputs2' incorporates:
     *  Inport: '<Root>/Ref_Speed_mech_rpm'
     *
     * Block description for '<S3>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_LivGguard_DW.Delay_DSTATE_o = FOC_LivGguard_U.Ref_Speed_mech_rpm;
  }

  /* Sum: '<S3>/Difference Inputs1' incorporates:
   *  Delay: '<S3>/Delay'
   *  Inport: '<Root>/Ref_Speed_mech_rpm'
   *
   * Block description for '<S3>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Add1_l = FOC_LivGguard_U.Ref_Speed_mech_rpm -
    FOC_LivGguard_DW.Delay_DSTATE_o;

  /* Switch: '<S215>/Switch2' incorporates:
   *  RelationalOperator: '<S215>/LowerRelop1'
   */
  if (!(rtb_Add1_l > rtb_deltafalllimit_d)) {
    /* Product: '<S3>/delta fall limit' incorporates:
     *  Inport: '<Root>/Ref_Speed_rate_down'
     *  SampleTimeMath: '<S3>/sample time'
     *
     * About '<S3>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_deltafalllimit_d = 0.0001 * FOC_LivGguard_U.Ref_Speed_rate_down;

    /* Switch: '<S215>/Switch' incorporates:
     *  RelationalOperator: '<S215>/UpperRelop'
     */
    if (!(rtb_Add1_l < rtb_deltafalllimit_d)) {
      rtb_deltafalllimit_d = rtb_Add1_l;
    }

    /* End of Switch: '<S215>/Switch' */
  }

  /* End of Switch: '<S215>/Switch2' */

  /* Sum: '<S3>/Difference Inputs2' incorporates:
   *  Delay: '<S3>/Delay'
   *
   * Block description for '<S3>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_LivGguard_DW.Delay_DSTATE_o += rtb_deltafalllimit_d;

  /* Outport: '<Root>/Speed_error' incorporates:
   *  Gain: '<S1>/rpm to Rad//sec'
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   *  Sum: '<S9>/Subtract'
   */
  FOC_LivGguard_Y.Speed_error = 0.10471975511965977 *
    FOC_LivGguard_DW.Delay_DSTATE_o - FOC_LivGguard_U.MtrSpd;

  /* Update for Delay: '<S8>/Delay' */
  FOC_LivGguard_DW.icLoad = false;

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
    - rtb_Sum)) * 0.0001;
  if (FOC_LivGguard_DW.Integrator_DSTATE > SVM_VOLTAGE_LIMIT) {
    FOC_LivGguard_DW.Integrator_DSTATE = SVM_VOLTAGE_LIMIT;
  } else if (FOC_LivGguard_DW.Integrator_DSTATE < -SVM_VOLTAGE_LIMIT) {
    FOC_LivGguard_DW.Integrator_DSTATE = -SVM_VOLTAGE_LIMIT;
  }

  /* End of Update for DiscreteIntegrator: '<S124>/Integrator' */

  /* Update for DiscreteIntegrator: '<S119>/Filter' */
  FOC_LivGguard_DW.Filter_DSTATE += 0.0001 * rtb_Product1;

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
    (FOC_LivGguard_Y.Vq_PID - rtb_Iq_Table)) * 0.0001;
  if (FOC_LivGguard_DW.Integrator_DSTATE_h > SVM_VOLTAGE_LIMIT) {
    FOC_LivGguard_DW.Integrator_DSTATE_h = SVM_VOLTAGE_LIMIT;
  } else if (FOC_LivGguard_DW.Integrator_DSTATE_h < -SVM_VOLTAGE_LIMIT) {
    FOC_LivGguard_DW.Integrator_DSTATE_h = -SVM_VOLTAGE_LIMIT;
  }

  /* End of Update for DiscreteIntegrator: '<S70>/Integrator' */

  /* Update for DiscreteIntegrator: '<S65>/Filter' */
  FOC_LivGguard_DW.Filter_DSTATE_d += 0.0001 * rtb_deltafalllimit_a;

  /* Update for Delay: '<S3>/Delay' */
  FOC_LivGguard_DW.icLoad_g = false;
}

/* Model step function for TID1 */
void FOC_LivGguard_step1(void)         /* Sample time: [0.001s, 0.0s] */
{
  double rtb_NProdOut_j;
  double rtb_Sum;

  /* Product: '<S199>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S191>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S189>/DProd Out'
   *  Sum: '<S191>/SumD'
   */
  rtb_NProdOut_j = (FOC_LivGguard_Y.Speed_error *
                    FOC_LivGguard_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA -
                    FOC_LivGguard_DW.Filter_DSTATE_i) *
    FOC_LivGguard_U.MTPA_PID.Speed_PID_MTPA.Filter_speed_PID_MTPA;

  /* Sum: '<S206>/Sum' incorporates:
   *  DiscreteIntegrator: '<S196>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S201>/PProd Out'
   */
  rtb_Sum = (FOC_LivGguard_Y.Speed_error *
             FOC_LivGguard_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA +
             FOC_LivGguard_DW.Integrator_DSTATE_b) + rtb_NProdOut_j;

  /* Switch: '<S204>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S204>/LowerRelop1'
   *  RelationalOperator: '<S204>/UpperRelop'
   *  Switch: '<S204>/Switch'
   */
  if (rtb_Sum > FOC_LivGguard_U.MTPA_PID.Up_Limit_speed_PID_MTPA) {
    /* Switch: '<S204>/Switch2' */
    FOC_LivGguard_B.Switch2 = FOC_LivGguard_U.MTPA_PID.Up_Limit_speed_PID_MTPA;
  } else if (rtb_Sum < FOC_LivGguard_U.MTPA_PID.Low_Limit_speed_PID_MTPA) {
    /* Switch: '<S204>/Switch' incorporates:
     *  Switch: '<S204>/Switch2'
     */
    FOC_LivGguard_B.Switch2 = FOC_LivGguard_U.MTPA_PID.Low_Limit_speed_PID_MTPA;
  } else {
    /* Switch: '<S204>/Switch2' incorporates:
     *  Switch: '<S204>/Switch'
     */
    FOC_LivGguard_B.Switch2 = rtb_Sum;
  }

  /* End of Switch: '<S204>/Switch2' */

  /* Outport: '<Root>/Iq_gen' */
  FOC_LivGguard_Y.Iq_gen = FOC_LivGguard_B.Switch2;

  /* Update for DiscreteIntegrator: '<S196>/Integrator' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S193>/IProd Out'
   *  Sum: '<S188>/SumI2'
   *  Sum: '<S188>/SumI4'
   *  Sum: '<S208>/SumI3'
   *  Sum: '<S209>/SumI1'
   */
  FOC_LivGguard_DW.Integrator_DSTATE_b += ((FOC_LivGguard_Y.Speed_error *
    FOC_LivGguard_U.MTPA_PID.Speed_PID_MTPA.Ki_speed_PID_MTPA +
    (FOC_LivGguard_B.Switch2 - FOC_LivGguard_B.Switch2)) +
    (FOC_LivGguard_B.Switch2 - rtb_Sum)) * 0.001;
  if (FOC_LivGguard_DW.Integrator_DSTATE_b > MOTOR_PEAK_AC) {
    FOC_LivGguard_DW.Integrator_DSTATE_b = MOTOR_PEAK_AC;
  } else if (FOC_LivGguard_DW.Integrator_DSTATE_b < -MOTOR_PEAK_AC) {
    FOC_LivGguard_DW.Integrator_DSTATE_b = -MOTOR_PEAK_AC;
  }

  /* End of Update for DiscreteIntegrator: '<S196>/Integrator' */

  /* Update for DiscreteIntegrator: '<S191>/Filter' */
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
  FOC_LivGguard_DW.icLoad_g = true;

  FOC_LivGguard_U.BusVoltage_V = OP_VOLTAGE;
  FOC_LivGguard_U.Iq_Torque_ratio = CURR_TORQUE_RATIO;
  FOC_LivGguard_U.p = POLEPAIRS;

  /* Id Iq Limits */
  FOC_LivGguard_U.Id_Iq_MTPA_limit.Iq_up_limit = 250.0f;
  FOC_LivGguard_U.Id_Iq_MTPA_limit.Iq_low_limit = -250.0f;
  FOC_LivGguard_U.Id_Iq_MTPA_limit.Id_up_limit = 300.0f;
  FOC_LivGguard_U.Id_Iq_MTPA_limit.Id_low_limit = -300.0f;
  
  /* Speed Ref Rate Limiter Settings */
  FOC_LivGguard_U.Ref_Speed_rate_up = 1.0f * 10000.0f;
  FOC_LivGguard_U.Ref_Speed_rate_down = -1000.0f * 10000.0f;

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
