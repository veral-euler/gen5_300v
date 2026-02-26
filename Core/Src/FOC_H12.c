/*
 * File: FOC_H12.c
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

#include "FOC_H12.h"
#include <math.h>
#include <stdbool.h>
#include "FOC_H12_private.h"

/* Block signals (default storage) */
B_FOC_H12_T FOC_H12_B;

/* Block states (default storage) */
DW_FOC_H12_T FOC_H12_DW;

/* External inputs (root inport signals with default storage) */
ExtU_FOC_H12_T FOC_H12_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_FOC_H12_T FOC_H12_Y;

/* Real-time model */
static RT_MODEL_FOC_H12_T FOC_H12_M_;
RT_MODEL_FOC_H12_T *const FOC_H12_M = &FOC_H12_M_;
float look2_pbinlxpw(float u0, float u1, const float bp0[], const float
                      bp1[], const float table[], uint32_t prevIndex[], const
                      uint32_t maxIndex[], uint32_t stride)
{
  float fractions[2];
  float frac;
  float yL_0d0;
  float yL_0d1;
  uint32_t bpIndices[2];
  uint32_t bpIdx;
  uint32_t found;
  uint32_t iLeft;
  uint32_t iRght;

  /* Column-major Lookup 2-D
     Search method: 'binary'
     Use previous index: 'on'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'on'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    bpIdx = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex[0U]]) {
    /* Binary Search using Previous Index */
    bpIdx = prevIndex[0U];
    iLeft = 0U;
    iRght = maxIndex[0U];
    found = 0U;
    while (found == 0U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx - 1U;
        bpIdx = ((bpIdx + iLeft) - 1U) >> 1U;
      } else if (u0 < bp0[bpIdx + 1U]) {
        found = 1U;
      } else {
        iLeft = bpIdx + 1U;
        bpIdx = ((bpIdx + iRght) + 1U) >> 1U;
      }
    }

    frac = (u0 - bp0[bpIdx]) / (bp0[bpIdx + 1U] - bp0[bpIdx]);
  } else {
    bpIdx = maxIndex[0U] - 1U;
    frac = (u0 - bp0[maxIndex[0U] - 1U]) / (bp0[maxIndex[0U]] - bp0[maxIndex[0U]
      - 1U]);
  }

  prevIndex[0U] = bpIdx;
  fractions[0U] = frac;
  bpIndices[0U] = bpIdx;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'on'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u1 <= bp1[0U]) {
    bpIdx = 0U;
    frac = (u1 - bp1[0U]) / (bp1[1U] - bp1[0U]);
  } else if (u1 < bp1[maxIndex[1U]]) {
    /* Binary Search using Previous Index */
    bpIdx = prevIndex[1U];
    iLeft = 0U;
    iRght = maxIndex[1U];
    found = 0U;
    while (found == 0U) {
      if (u1 < bp1[bpIdx]) {
        iRght = bpIdx - 1U;
        bpIdx = ((bpIdx + iLeft) - 1U) >> 1U;
      } else if (u1 < bp1[bpIdx + 1U]) {
        found = 1U;
      } else {
        iLeft = bpIdx + 1U;
        bpIdx = ((bpIdx + iRght) + 1U) >> 1U;
      }
    }

    frac = (u1 - bp1[bpIdx]) / (bp1[bpIdx + 1U] - bp1[bpIdx]);
  } else {
    bpIdx = maxIndex[1U] - 1U;
    frac = (u1 - bp1[maxIndex[1U] - 1U]) / (bp1[maxIndex[1U]] - bp1[maxIndex[1U]
      - 1U]);
  }

  prevIndex[1U] = bpIdx;

  /* Column-major Interpolation 2-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  iLeft = bpIdx * stride + bpIndices[0U];
  yL_0d0 = table[iLeft];
  yL_0d0 += (table[iLeft + 1U] - yL_0d0) * fractions[0U];
  iLeft += stride;
  yL_0d1 = table[iLeft];
  return (((table[iLeft + 1U] - yL_0d1) * fractions[0U] + yL_0d1) - yL_0d0) *
    frac + yL_0d0;
}

/* Model step function for TID0 */
void FOC_H12_step0(void)               /* Sample time: [0.0001s, 0.0s] */
{
  float rtb_Add1;
  float rtb_Add3;
  float rtb_IqTable;
  float rtb_NProdOut_l;
  float rtb_Product;
  float rtb_Sum;
  float rtb_Switch2_e;
  float rtb_Switch_h_idx_0;
  float rtb_add_c;
  float rtb_algDD_o1_h;
  float rtb_algDD_o2_n;
  bool tmp;

  /* Update the flag to indicate when data transfers from
   *  Sample time: [0.0001s, 0.0s] to Sample time: [0.001s, 0.0s]  */
  (FOC_H12_M->Timing.RateInteraction.TID0_1)++;
  if ((FOC_H12_M->Timing.RateInteraction.TID0_1) > 9) {
    FOC_H12_M->Timing.RateInteraction.TID0_1 = 0;
  }

  /* RateTransition generated from: '<S2>/Product' incorporates:
   *  RateTransition generated from: '<S201>/DProd Out'
   */
  tmp = (FOC_H12_M->Timing.RateInteraction.TID0_1 == 1);
  if (tmp) {
    /* RateTransition generated from: '<S2>/Product' */
    FOC_H12_B.TmpRTBAtProductInport2 = FOC_H12_DW.TmpRTBAtProductInport2_Buffer0;
  }

  /* End of RateTransition generated from: '<S2>/Product' */

  /* Product: '<S2>/Product' incorporates:
   *  Inport: '<Root>/Iq_Torque_ratio'
   */
  rtb_Product = FOC_H12_U.Iq_Torque_ratio * FOC_H12_B.TmpRTBAtProductInport2;

  /* Delay: '<S9>/Delay' */
  if (FOC_H12_DW.icLoad) {
    FOC_H12_DW.Delay_DSTATE = rtb_Product;
  }

  /* Product: '<S169>/delta fall limit' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  Product: '<S9>/delta rise limit'
   *  SampleTimeMath: '<S9>/sample time'
   *
   * About '<S9>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  FOC_H12_Y.Iq_sat = FOC_H12_U.Rate_limiter.Torque_gen_ramp_up * 0.0001;

  /* Sum: '<S9>/Difference Inputs1' incorporates:
   *  Delay: '<S9>/Delay'
   *
   * Block description for '<S9>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Product -= FOC_H12_DW.Delay_DSTATE;

  /* Switch: '<S172>/Switch2' incorporates:
   *  RelationalOperator: '<S172>/LowerRelop1'
   */
  if (!(rtb_Product > FOC_H12_Y.Iq_sat)) {
    /* Product: '<S169>/delta fall limit' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  Product: '<S9>/delta fall limit'
     *  SampleTimeMath: '<S9>/sample time'
     *
     * About '<S9>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    FOC_H12_Y.Iq_sat = 0.0001 * FOC_H12_U.Rate_limiter.Torque_gen_ramp_down;

    /* Switch: '<S172>/Switch' incorporates:
     *  RelationalOperator: '<S172>/UpperRelop'
     */
    if (!(rtb_Product < FOC_H12_Y.Iq_sat)) {
      /* Product: '<S169>/delta fall limit' */
      FOC_H12_Y.Iq_sat = rtb_Product;
    }

    /* End of Switch: '<S172>/Switch' */
  }

  /* End of Switch: '<S172>/Switch2' */

  /* Sum: '<S9>/Difference Inputs2' incorporates:
   *  Delay: '<S9>/Delay'
   *
   * Block description for '<S9>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_H12_Y.Torque_gen = FOC_H12_Y.Iq_sat + FOC_H12_DW.Delay_DSTATE;

  /* Abs: '<S7>/Abs' incorporates:
   *  Abs: '<S8>/Abs'
   *  Gain: '<S7>/Gain'
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   */
  rtb_NProdOut_l = fabs(9.5492965855137211 * FOC_H12_U.MtrSpd);

  /* Lookup_n-D: '<S7>/Id Table' incorporates:
   *  Abs: '<S7>/Abs'
   *  Sum: '<S9>/Difference Inputs2'
   *
   * Block description for '<S9>/Difference Inputs2':
   *
   *  Add in CPU
   */
  rtb_Product = look2_pbinlxpw(FOC_H12_Y.Torque_gen, rtb_NProdOut_l,
    FOC_H12_ConstP.pooled4, FOC_H12_ConstP.pooled5,
    FOC_H12_ConstP.IdTable_tableData, FOC_H12_DW.m_bpIndex,
    FOC_H12_ConstP.pooled11, 80U);

  /* Delay: '<S168>/Delay' */
  if (FOC_H12_DW.icLoad_a) {
    FOC_H12_DW.Delay_DSTATE_a = rtb_Product;
  }

  /* Product: '<S168>/delta fall limit' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  Product: '<S168>/delta rise limit'
   *  SampleTimeMath: '<S168>/sample time'
   *
   * About '<S168>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  FOC_H12_Y.Id_sat = FOC_H12_U.Rate_limiter.Id_ramp_up * 0.0001;

  /* Sum: '<S168>/Difference Inputs1' incorporates:
   *  Delay: '<S168>/Delay'
   *
   * Block description for '<S168>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Product -= FOC_H12_DW.Delay_DSTATE_a;

  /* Switch: '<S170>/Switch2' incorporates:
   *  RelationalOperator: '<S170>/LowerRelop1'
   */
  if (!(rtb_Product > FOC_H12_Y.Id_sat)) {
    /* Product: '<S168>/delta fall limit' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  SampleTimeMath: '<S168>/sample time'
     *
     * About '<S168>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    FOC_H12_Y.Id_sat = 0.0001 * FOC_H12_U.Rate_limiter.Id_ramp_down;

    /* Switch: '<S170>/Switch' incorporates:
     *  RelationalOperator: '<S170>/UpperRelop'
     */
    if (!(rtb_Product < FOC_H12_Y.Id_sat)) {
      /* Product: '<S168>/delta fall limit' */
      FOC_H12_Y.Id_sat = rtb_Product;
    }

    /* End of Switch: '<S170>/Switch' */
  }

  /* End of Switch: '<S170>/Switch2' */

  /* Sum: '<S168>/Difference Inputs2' incorporates:
   *  Delay: '<S168>/Delay'
   *
   * Block description for '<S168>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_H12_Y.Id_ref = FOC_H12_Y.Id_sat + FOC_H12_DW.Delay_DSTATE_a;

  /* Switch: '<S10>/Switch2' incorporates:
   *  Inport: '<Root>/Id_Iq_MTPA_limit'
   *  RelationalOperator: '<S10>/LowerRelop1'
   *  RelationalOperator: '<S10>/UpperRelop'
   *  Switch: '<S10>/Switch'
   */
  if (FOC_H12_Y.Id_ref > FOC_H12_U.Id_Iq_MTPA_limit.Id_up_limit) {
    /* Product: '<S168>/delta fall limit' */
    FOC_H12_Y.Id_sat = FOC_H12_U.Id_Iq_MTPA_limit.Id_up_limit;
  } else if (FOC_H12_Y.Id_ref < FOC_H12_U.Id_Iq_MTPA_limit.Id_low_limit) {
    /* Product: '<S168>/delta fall limit' incorporates:
     *  Switch: '<S10>/Switch'
     */
    FOC_H12_Y.Id_sat = FOC_H12_U.Id_Iq_MTPA_limit.Id_low_limit;
  } else {
    /* Product: '<S168>/delta fall limit' incorporates:
     *  Switch: '<S10>/Switch'
     */
    FOC_H12_Y.Id_sat = FOC_H12_Y.Id_ref;
  }

  /* End of Switch: '<S10>/Switch2' */

  /* Outputs for Atomic SubSystem: '<S20>/Two phase CRL wrap' */
  /* Gain: '<S21>/one_by_sqrt3' incorporates:
   *  Inport: '<Root>/Phase Current'
   *  Sum: '<S21>/a_plus_2b'
   */
  rtb_Product = ((FOC_H12_U.PhaseCurrent[0] + FOC_H12_U.PhaseCurrent[1]) +
                 FOC_H12_U.PhaseCurrent[1]) * 0.57735026918962584;

  /* End of Outputs for SubSystem: '<S20>/Two phase CRL wrap' */

  /* Trigonometry: '<S4>/Trigonometric Function' incorporates:
   *  Inport: '<Root>/angle'
   *  Trigonometry: '<S6>/Trigonometric Function1'
   */
  rtb_Add1 = sinf(FOC_H12_U.MtrElcPos);

  /* Trigonometry: '<S4>/Trigonometric Function1' incorporates:
   *  Inport: '<Root>/angle'
   *  Trigonometry: '<S6>/Trigonometric Function'
   */
  rtb_Add3 = cosf(FOC_H12_U.MtrElcPos);

  /* Outputs for Atomic SubSystem: '<S30>/Two inputs CRL' */
  /* Outputs for Atomic SubSystem: '<S20>/Two phase CRL wrap' */
  /* AlgorithmDescriptorDelegate generated from: '<S31>/a16' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S21>/a16'
   *  Inport: '<Root>/Phase Current'
   *  Product: '<S31>/acos'
   *  Product: '<S31>/asin'
   *  Product: '<S31>/bcos'
   *  Product: '<S31>/bsin'
   *  Sum: '<S31>/sum_Ds'
   *  Sum: '<S31>/sum_Qs'
   *  Switch: '<S32>/Switch'
   *  Trigonometry: '<S4>/Trigonometric Function'
   *  Trigonometry: '<S4>/Trigonometric Function1'
   */
  rtb_algDD_o1_h = (float)(FOC_H12_U.PhaseCurrent[0] * rtb_Add3 + rtb_Product *
    rtb_Add1);
  rtb_algDD_o2_n = (float)(rtb_Product * rtb_Add3 - FOC_H12_U.PhaseCurrent[0] *
    rtb_Add1);

  /* End of Outputs for SubSystem: '<S20>/Two phase CRL wrap' */
  /* End of Outputs for SubSystem: '<S30>/Two inputs CRL' */

  /* Sum: '<S24>/Add1' incorporates:
   *  Constant: '<S14>/One'
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   *  Product: '<S24>/Product'
   *  Product: '<S24>/Product1'
   *  Sum: '<S14>/Sum'
   *  Switch: '<S14>/Switch1'
   *  UnitDelay: '<S24>/Unit Delay'
   */
  FOC_H12_DW.UnitDelay_DSTATE = (1.0F -
    FOC_H12_U.IIR_Filter_Coefficient.Id_Filter_coefficient) *
    FOC_H12_DW.UnitDelay_DSTATE + rtb_algDD_o1_h *
    FOC_H12_U.IIR_Filter_Coefficient.Id_Filter_coefficient;

  /* Switch: '<S4>/Switch' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   *  UnitDelay: '<S24>/Unit Delay'
   */
  if (FOC_H12_U.IIR_Filter_Coefficient.Id_Filter_switch > 0.0F) {
    rtb_algDD_o1_h = FOC_H12_DW.UnitDelay_DSTATE;
  }

  /* End of Switch: '<S4>/Switch' */

  /* Sum: '<S27>/Add1' incorporates:
   *  Constant: '<S15>/One'
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   *  Product: '<S27>/Product'
   *  Product: '<S27>/Product1'
   *  Sum: '<S15>/Sum'
   *  Switch: '<S15>/Switch1'
   *  UnitDelay: '<S27>/Unit Delay'
   */
  FOC_H12_DW.UnitDelay_DSTATE_f = (1.0F -
    FOC_H12_U.IIR_Filter_Coefficient.Iq_Filter_coefficient) *
    FOC_H12_DW.UnitDelay_DSTATE_f + rtb_algDD_o2_n *
    FOC_H12_U.IIR_Filter_Coefficient.Iq_Filter_coefficient;

  /* Switch: '<S4>/Switch1' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   */
  if (FOC_H12_U.IIR_Filter_Coefficient.Iq_Filter_switch > 0.0F) {
    /* DataTypeConversion: '<S4>/Data Type Conversion1' incorporates:
     *  UnitDelay: '<S27>/Unit Delay'
     */
    FOC_H12_Y.Iq = FOC_H12_DW.UnitDelay_DSTATE_f;
  } else {
    /* DataTypeConversion: '<S4>/Data Type Conversion1' */
    FOC_H12_Y.Iq = rtb_algDD_o2_n;
  }

  /* End of Switch: '<S4>/Switch1' */

  /* Sum: '<S37>/Sum3' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion'
   */
  FOC_H12_Y.Id_error = FOC_H12_Y.Id_sat - rtb_algDD_o1_h;

  /* Product: '<S135>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S127>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S125>/DProd Out'
   *  Sum: '<S127>/SumD'
   */
  rtb_Product = (FOC_H12_Y.Id_error *
                 FOC_H12_U.MTPA_PID.Flux_PID_MTPA.Kd_flux_PID_MTPA -
                 FOC_H12_DW.Filter_DSTATE) *
    FOC_H12_U.MTPA_PID.Flux_PID_MTPA.Filter_flux_PID_MTPA;

  /* Sum: '<S142>/Sum' incorporates:
   *  DiscreteIntegrator: '<S132>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S137>/PProd Out'
   */
  rtb_Sum = (FOC_H12_Y.Id_error *
             FOC_H12_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA +
             FOC_H12_DW.Integrator_DSTATE) + rtb_Product;

  /* Switch: '<S140>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S140>/LowerRelop1'
   *  RelationalOperator: '<S140>/UpperRelop'
   *  Switch: '<S140>/Switch'
   */
  if (rtb_Sum > FOC_H12_U.MTPA_PID.Up_Limit_flux_PID) {
    rtb_Switch2_e = FOC_H12_U.MTPA_PID.Up_Limit_flux_PID;
  } else if (rtb_Sum < FOC_H12_U.MTPA_PID.Low_Limit_flux_PID) {
    /* Switch: '<S140>/Switch' */
    rtb_Switch2_e = FOC_H12_U.MTPA_PID.Low_Limit_flux_PID;
  } else {
    rtb_Switch2_e = rtb_Sum;
  }

  /* End of Switch: '<S140>/Switch2' */

  /* Gain: '<S5>/Gain' incorporates:
   *  Inport: '<Root>/BusVoltage_V'
   */
  rtb_algDD_o2_n = 0.577350259F * FOC_H12_U.BusVoltage_V;

  /* Lookup_n-D: '<S8>/2-D Lookup Table Lq' incorporates:
   *  Sum: '<S9>/Difference Inputs2'
   *
   * Block description for '<S9>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_H12_Y.Lq = look2_pbinlxpw(FOC_H12_Y.Torque_gen, rtb_NProdOut_l,
    FOC_H12_ConstP.pooled4, FOC_H12_ConstP.pooled5,
    FOC_H12_ConstP.uDLookupTableLq_tableData, FOC_H12_DW.m_bpIndex_n,
    FOC_H12_ConstP.pooled11, 80U);

  /* Lookup_n-D: '<S7>/Iq Table' incorporates:
   *  Abs: '<S7>/Abs'
   *  Sum: '<S9>/Difference Inputs2'
   *
   * Block description for '<S9>/Difference Inputs2':
   *
   *  Add in CPU
   */
  rtb_IqTable = look2_pbinlxpw(FOC_H12_Y.Torque_gen, rtb_NProdOut_l,
    FOC_H12_ConstP.pooled4, FOC_H12_ConstP.pooled5,
    FOC_H12_ConstP.IqTable_tableData, FOC_H12_DW.m_bpIndex_f,
    FOC_H12_ConstP.pooled11, 80U);

  /* Delay: '<S169>/Delay' */
  if (FOC_H12_DW.icLoad_h) {
    FOC_H12_DW.Delay_DSTATE_g = rtb_IqTable;
  }

  /* Product: '<S169>/delta fall limit' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  Product: '<S169>/delta rise limit'
   *  SampleTimeMath: '<S169>/sample time'
   *
   * About '<S169>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  FOC_H12_Y.Iq_sat = FOC_H12_U.Rate_limiter.Iq_ramp_up * 0.0001;

  /* Sum: '<S169>/Difference Inputs1' incorporates:
   *  Delay: '<S169>/Delay'
   *
   * Block description for '<S169>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_IqTable -= FOC_H12_DW.Delay_DSTATE_g;

  /* Switch: '<S171>/Switch2' incorporates:
   *  RelationalOperator: '<S171>/LowerRelop1'
   */
  if (!(rtb_IqTable > FOC_H12_Y.Iq_sat)) {
    /* Product: '<S169>/delta fall limit' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  SampleTimeMath: '<S169>/sample time'
     *
     * About '<S169>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    FOC_H12_Y.Iq_sat = 0.0001 * FOC_H12_U.Rate_limiter.Iq_ramp_down;

    /* Switch: '<S171>/Switch' incorporates:
     *  RelationalOperator: '<S171>/UpperRelop'
     */
    if (!(rtb_IqTable < FOC_H12_Y.Iq_sat)) {
      /* Product: '<S169>/delta fall limit' */
      FOC_H12_Y.Iq_sat = rtb_IqTable;
    }

    /* End of Switch: '<S171>/Switch' */
  }

  /* End of Switch: '<S171>/Switch2' */

  /* Sum: '<S169>/Difference Inputs2' incorporates:
   *  Delay: '<S169>/Delay'
   *
   * Block description for '<S169>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_H12_Y.Iq_ref = FOC_H12_Y.Iq_sat + FOC_H12_DW.Delay_DSTATE_g;

  /* Switch: '<S11>/Switch2' incorporates:
   *  Inport: '<Root>/Id_Iq_MTPA_limit'
   *  RelationalOperator: '<S11>/LowerRelop1'
   *  RelationalOperator: '<S11>/UpperRelop'
   *  Switch: '<S11>/Switch'
   */
  if (FOC_H12_Y.Iq_ref > FOC_H12_U.Id_Iq_MTPA_limit.Iq_up_limit) {
    /* Product: '<S169>/delta fall limit' */
    FOC_H12_Y.Iq_sat = FOC_H12_U.Id_Iq_MTPA_limit.Iq_up_limit;
  } else if (FOC_H12_Y.Iq_ref < FOC_H12_U.Id_Iq_MTPA_limit.Iq_low_limit) {
    /* Product: '<S169>/delta fall limit' incorporates:
     *  Switch: '<S11>/Switch'
     */
    FOC_H12_Y.Iq_sat = FOC_H12_U.Id_Iq_MTPA_limit.Iq_low_limit;
  } else {
    /* Product: '<S169>/delta fall limit' incorporates:
     *  Switch: '<S11>/Switch'
     */
    FOC_H12_Y.Iq_sat = FOC_H12_Y.Iq_ref;
  }

  /* End of Switch: '<S11>/Switch2' */

  /* Gain: '<S39>/wm_pu2si_mech2elec' incorporates:
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   */
  rtb_add_c = POLEPAIRS * FOC_H12_U.MtrSpd;

  /* Gain: '<S39>/NegSign' incorporates:
   *  Product: '<S39>/prod1'
   *  Switch: '<S40>/Switch1'
   */
  FOC_H12_Y.Vd_FF = -(FOC_H12_Y.Lq * FOC_H12_Y.Iq_sat * rtb_add_c);

  /* Switch: '<S41>/Switch2' incorporates:
   *  RelationalOperator: '<S41>/LowerRelop1'
   *  RelationalOperator: '<S41>/UpperRelop'
   *  Switch: '<S39>/Switch'
   *  Switch: '<S41>/Switch'
   *  UnaryMinus: '<S39>/Unary Minus'
   */
  if (FOC_H12_Y.Vd_FF > rtb_algDD_o2_n) {
    /* Gain: '<S39>/NegSign' */
    FOC_H12_Y.Vd_FF = rtb_algDD_o2_n;
  } else if (FOC_H12_Y.Vd_FF < -rtb_algDD_o2_n) {
    /* Gain: '<S39>/NegSign' incorporates:
     *  Switch: '<S41>/Switch'
     *  UnaryMinus: '<S39>/Unary Minus'
     */
    FOC_H12_Y.Vd_FF = -rtb_algDD_o2_n;
  }

  /* End of Switch: '<S41>/Switch2' */

  /* Sum: '<S5>/Sum' */
  FOC_H12_Y.Outport1 = rtb_Switch2_e + FOC_H12_Y.Vd_FF;

  /* Switch: '<S34>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S34>/LowerRelop1'
   *  RelationalOperator: '<S34>/UpperRelop'
   *  Switch: '<S34>/Switch'
   */
  if (FOC_H12_Y.Outport1 > FOC_H12_U.MTPA_PID.Up_Limit_flux_PID) {
    /* Sum: '<S5>/Sum' */
    FOC_H12_Y.Outport1 = FOC_H12_U.MTPA_PID.Up_Limit_flux_PID;
  } else if (FOC_H12_Y.Outport1 < FOC_H12_U.MTPA_PID.Low_Limit_flux_PID) {
    /* Sum: '<S5>/Sum' incorporates:
     *  Switch: '<S34>/Switch'
     */
    FOC_H12_Y.Outport1 = FOC_H12_U.MTPA_PID.Low_Limit_flux_PID;
  }

  /* End of Switch: '<S34>/Switch2' */

  /* Lookup_n-D: '<S8>/2-D Lookup Table Psim' incorporates:
   *  Sum: '<S9>/Difference Inputs2'
   *
   * Block description for '<S9>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_H12_Y.Lambda = look2_pbinlxpw(FOC_H12_Y.Torque_gen, rtb_NProdOut_l,
    FOC_H12_ConstP.pooled4, FOC_H12_ConstP.pooled5,
    FOC_H12_ConstP.uDLookupTablePsim_tableData, FOC_H12_DW.m_bpIndex_o,
    FOC_H12_ConstP.pooled11, 80U);

  /* Lookup_n-D: '<S8>/2-D Lookup Table Ld' incorporates:
   *  Sum: '<S9>/Difference Inputs2'
   *
   * Block description for '<S9>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_H12_Y.Ld = look2_pbinlxpw(FOC_H12_Y.Torque_gen, rtb_NProdOut_l,
    FOC_H12_ConstP.pooled4, FOC_H12_ConstP.pooled5,
    FOC_H12_ConstP.uDLookupTableLd_tableData, FOC_H12_DW.m_bpIndex_h,
    FOC_H12_ConstP.pooled11, 80U);

  /* Product: '<S39>/prod2' incorporates:
   *  Product: '<S39>/prod3'
   *  Sum: '<S39>/add1'
   *  Switch: '<S40>/Switch'
   *  Switch: '<S40>/Switch2'
   */
  FOC_H12_Y.Vq_FF = (FOC_H12_Y.Ld * FOC_H12_Y.Id_sat + FOC_H12_Y.Lambda) *
    rtb_add_c;

  /* Switch: '<S42>/Switch2' incorporates:
   *  RelationalOperator: '<S42>/LowerRelop1'
   *  RelationalOperator: '<S42>/UpperRelop'
   *  Switch: '<S39>/Switch'
   *  Switch: '<S42>/Switch'
   *  UnaryMinus: '<S39>/Unary Minus'
   */
  if (FOC_H12_Y.Vq_FF > rtb_algDD_o2_n) {
    /* Product: '<S39>/prod2' */
    FOC_H12_Y.Vq_FF = rtb_algDD_o2_n;
  } else if (FOC_H12_Y.Vq_FF < -rtb_algDD_o2_n) {
    /* Product: '<S39>/prod2' incorporates:
     *  Switch: '<S42>/Switch'
     *  UnaryMinus: '<S39>/Unary Minus'
     */
    FOC_H12_Y.Vq_FF = -rtb_algDD_o2_n;
  }

  /* End of Switch: '<S42>/Switch2' */

  /* Sum: '<S36>/Sum2' */
  FOC_H12_Y.Iq_error = FOC_H12_Y.Iq_sat - FOC_H12_Y.Iq;

  /* Product: '<S81>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S73>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S71>/DProd Out'
   *  Sum: '<S73>/SumD'
   */
  rtb_NProdOut_l = (FOC_H12_Y.Iq_error *
                    FOC_H12_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA -
                    FOC_H12_DW.Filter_DSTATE_d) *
    FOC_H12_U.MTPA_PID.Torque_PID_MTPA.Filter_torque_PID_MTPA;

  /* Sum: '<S88>/Sum' incorporates:
   *  DiscreteIntegrator: '<S78>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S83>/PProd Out'
   */
  rtb_IqTable = (FOC_H12_Y.Iq_error *
                 FOC_H12_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA +
                 FOC_H12_DW.Integrator_DSTATE_h) + rtb_NProdOut_l;

  /* Switch: '<S86>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S86>/LowerRelop1'
   *  RelationalOperator: '<S86>/UpperRelop'
   *  Switch: '<S86>/Switch'
   */
  if (rtb_IqTable > FOC_H12_U.MTPA_PID.Up_Limit_torque_PID) {
    /* Switch: '<S86>/Switch2' */
    FOC_H12_Y.Vq_PID = FOC_H12_U.MTPA_PID.Up_Limit_torque_PID;
  } else if (rtb_IqTable < FOC_H12_U.MTPA_PID.Low_Limit_torque_PID) {
    /* Switch: '<S86>/Switch2' incorporates:
     *  Switch: '<S86>/Switch'
     */
    FOC_H12_Y.Vq_PID = FOC_H12_U.MTPA_PID.Low_Limit_torque_PID;
  } else {
    /* Switch: '<S86>/Switch2' incorporates:
     *  Switch: '<S86>/Switch'
     */
    FOC_H12_Y.Vq_PID = rtb_IqTable;
  }

  /* End of Switch: '<S86>/Switch2' */

  /* Sum: '<S5>/Sum4' */
  FOC_H12_Y.Outport2 = FOC_H12_Y.Vq_FF + FOC_H12_Y.Vq_PID;

  /* Switch: '<S35>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S35>/LowerRelop1'
   *  RelationalOperator: '<S35>/UpperRelop'
   *  Switch: '<S35>/Switch'
   */
  if (FOC_H12_Y.Outport2 > FOC_H12_U.MTPA_PID.Up_Limit_torque_PID) {
    /* Sum: '<S5>/Sum4' */
    FOC_H12_Y.Outport2 = FOC_H12_U.MTPA_PID.Up_Limit_torque_PID;
  } else if (FOC_H12_Y.Outport2 < FOC_H12_U.MTPA_PID.Low_Limit_torque_PID) {
    /* Sum: '<S5>/Sum4' incorporates:
     *  Switch: '<S35>/Switch'
     */
    FOC_H12_Y.Outport2 = FOC_H12_U.MTPA_PID.Low_Limit_torque_PID;
  }

  /* End of Switch: '<S35>/Switch2' */

  /* Outputs for Atomic SubSystem: '<S160>/Two inputs CRL' */
  /* Switch: '<S162>/Switch' incorporates:
   *  Product: '<S161>/dcos'
   *  Product: '<S161>/qsin'
   *  Sum: '<S161>/sum_alpha'
   */
  rtb_Switch_h_idx_0 = FOC_H12_Y.Outport1 * rtb_Add3 - FOC_H12_Y.Outport2 *
    rtb_Add1;

  /* Gain: '<S157>/one_by_two' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S161>/a16'
   */
  rtb_add_c = 0.5 * rtb_Switch_h_idx_0;

  /* Gain: '<S157>/sqrt3_by_two' incorporates:
   *  Product: '<S161>/dsin'
   *  Product: '<S161>/qcos'
   *  Sum: '<S161>/sum_beta'
   */
  rtb_Add3 = (FOC_H12_Y.Outport2 * rtb_Add3 + FOC_H12_Y.Outport1 * rtb_Add1) *
    0.8660254037844386;

  /* End of Outputs for SubSystem: '<S160>/Two inputs CRL' */

  /* Sum: '<S157>/add_b' */
  rtb_Add1 = rtb_Add3 - rtb_add_c;

  /* Sum: '<S157>/add_c' */
  rtb_add_c = (0.0 - rtb_add_c) - rtb_Add3;

  /* Outputs for Atomic SubSystem: '<S160>/Two inputs CRL' */
  /* Product: '<S3>/delta fall limit' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S161>/a16'
   *  Gain: '<S166>/one_by_two'
   *  MinMax: '<S166>/Max'
   *  MinMax: '<S166>/Min'
   *  Sum: '<S166>/Add'
   */
  FOC_H12_Y.Speed_error = (fmax(fmax(rtb_Switch_h_idx_0, rtb_Add1), rtb_add_c) +
    fmin(fmin(rtb_Switch_h_idx_0, rtb_Add1), rtb_add_c)) * -0.5;

  /* Outport: '<Root>/Va' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S161>/a16'
   *  Gain: '<S165>/Gain'
   *  Sum: '<S165>/Add3'
   */
  FOC_H12_Y.Va = (rtb_Switch_h_idx_0 + FOC_H12_Y.Speed_error) *
    1.1547005383792517;

  /* End of Outputs for SubSystem: '<S160>/Two inputs CRL' */

  /* Outport: '<Root>/Vb' incorporates:
   *  Gain: '<S165>/Gain'
   *  Sum: '<S165>/Add1'
   */
  FOC_H12_Y.Vb = (rtb_Add1 + FOC_H12_Y.Speed_error) * 1.1547005383792517;

  /* Outport: '<Root>/Vc' incorporates:
   *  Gain: '<S165>/Gain'
   *  Sum: '<S165>/Add2'
   */
  FOC_H12_Y.Vc = (FOC_H12_Y.Speed_error + rtb_add_c) * 1.1547005383792517;

  /* Outport: '<Root>/Id' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion'
   */
  FOC_H12_Y.Id = rtb_algDD_o1_h;

  /* Product: '<S3>/delta fall limit' incorporates:
   *  Inport: '<Root>/Ref_Speed_rate_up'
   *  Product: '<S3>/delta rise limit'
   *  SampleTimeMath: '<S3>/sample time'
   *
   * About '<S3>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  FOC_H12_Y.Speed_error = FOC_H12_U.Ref_Speed_rate_up * 0.0001;

  /* Delay: '<S3>/Delay' */
  if (FOC_H12_DW.icLoad_n) {
    /* Sum: '<S3>/Difference Inputs2' incorporates:
     *  Inport: '<Root>/Ref_Speed_mech_rpm'
     *
     * Block description for '<S3>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_H12_DW.Delay_DSTATE_p = FOC_H12_U.Ref_Speed_mech_rpm;
  }

  /* Sum: '<S3>/Difference Inputs1' incorporates:
   *  Delay: '<S3>/Delay'
   *  Inport: '<Root>/Ref_Speed_mech_rpm'
   *
   * Block description for '<S3>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_add_c = FOC_H12_U.Ref_Speed_mech_rpm - FOC_H12_DW.Delay_DSTATE_p;

  /* Switch: '<S227>/Switch2' incorporates:
   *  RelationalOperator: '<S227>/LowerRelop1'
   */
  if (!(rtb_add_c > FOC_H12_Y.Speed_error)) {
    /* Product: '<S3>/delta fall limit' incorporates:
     *  Inport: '<Root>/Ref_Speed_rate_down'
     *  SampleTimeMath: '<S3>/sample time'
     *
     * About '<S3>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    FOC_H12_Y.Speed_error = 0.0001 * FOC_H12_U.Ref_Speed_rate_down;

    /* Switch: '<S227>/Switch' incorporates:
     *  RelationalOperator: '<S227>/UpperRelop'
     */
    if (!(rtb_add_c < FOC_H12_Y.Speed_error)) {
      /* Product: '<S3>/delta fall limit' */
      FOC_H12_Y.Speed_error = rtb_add_c;
    }

    /* End of Switch: '<S227>/Switch' */
  }

  /* End of Switch: '<S227>/Switch2' */

  /* Sum: '<S3>/Difference Inputs2' incorporates:
   *  Delay: '<S3>/Delay'
   *
   * Block description for '<S3>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_H12_DW.Delay_DSTATE_p += FOC_H12_Y.Speed_error;

  /* Product: '<S3>/delta fall limit' incorporates:
   *  Gain: '<S1>/rpm to Rad//sec'
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   *  Sum: '<S12>/Subtract'
   */
  FOC_H12_Y.Speed_error = 0.10471975511965977 * FOC_H12_DW.Delay_DSTATE_p -
    FOC_H12_U.MtrSpd;

  /* RateTransition generated from: '<S201>/DProd Out' */
  if (tmp) {
    FOC_H12_DW.TmpRTBAtDProdOutInport1_Buffer = FOC_H12_Y.Speed_error;

    /* RateTransition generated from: '<S205>/IProd Out' */
    FOC_H12_DW.TmpRTBAtIProdOutInport1_Buffer = FOC_H12_Y.Speed_error;

    /* RateTransition generated from: '<S213>/PProd Out' */
    FOC_H12_DW.TmpRTBAtPProdOutInport1_Buffer = FOC_H12_Y.Speed_error;

    /* RateTransition generated from: '<S201>/DProd Out' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     */
    FOC_H12_DW.TmpRTBAtDProdOutInport2_Buffer =
      FOC_H12_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA;

    /* RateTransition generated from: '<S205>/IProd Out' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     */
    FOC_H12_DW.TmpRTBAtIProdOutInport2_Buffer =
      FOC_H12_U.MTPA_PID.Speed_PID_MTPA.Ki_speed_PID_MTPA;

    /* RateTransition generated from: '<S211>/NProd Out' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     */
    FOC_H12_DW.TmpRTBAtNProdOutInport2_Buffer =
      FOC_H12_U.MTPA_PID.Speed_PID_MTPA.Filter_speed_PID_MTPA;

    /* RateTransition generated from: '<S213>/PProd Out' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     */
    FOC_H12_DW.TmpRTBAtPProdOutInport2_Buffer =
      FOC_H12_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA;

    /* RateTransition generated from: '<S216>/LowerRelop1' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     */
    FOC_H12_DW.TmpRTBAtLowerRelop1Inport2_Buff =
      FOC_H12_U.MTPA_PID.Up_Limit_speed_PID_MTPA;

    /* RateTransition generated from: '<S216>/Switch2' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  RateTransition generated from: '<S216>/LowerRelop1'
     */
    FOC_H12_DW.TmpRTBAtSwitch2Inport1_Buffer =
      FOC_H12_U.MTPA_PID.Up_Limit_speed_PID_MTPA;

    /* RateTransition generated from: '<S216>/Switch' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     */
    FOC_H12_DW.TmpRTBAtSwitchInport1_Buffer =
      FOC_H12_U.MTPA_PID.Low_Limit_speed_PID_MTPA;

    /* RateTransition generated from: '<S216>/UpperRelop' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  RateTransition generated from: '<S216>/Switch'
     */
    FOC_H12_DW.TmpRTBAtUpperRelopInport2_Buffe =
      FOC_H12_U.MTPA_PID.Low_Limit_speed_PID_MTPA;
  }

  /* Update for Delay: '<S9>/Delay' */
  FOC_H12_DW.icLoad = false;
  FOC_H12_DW.Delay_DSTATE = FOC_H12_Y.Torque_gen;

  /* Update for Delay: '<S168>/Delay' */
  FOC_H12_DW.icLoad_a = false;
  FOC_H12_DW.Delay_DSTATE_a = FOC_H12_Y.Id_ref;

  /* Update for DiscreteIntegrator: '<S132>/Integrator' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S129>/IProd Out'
   *  Sum: '<S124>/SumI2'
   *  Sum: '<S124>/SumI4'
   *  Sum: '<S144>/SumI3'
   *  Sum: '<S145>/SumI1'
   */
  FOC_H12_DW.Integrator_DSTATE += ((FOC_H12_Y.Id_error *
    FOC_H12_U.MTPA_PID.Flux_PID_MTPA.Ki_flux_PID_MTPA + (rtb_Switch2_e -
    rtb_Switch2_e)) + (rtb_Switch2_e - rtb_Sum)) * 0.0001;
  if (FOC_H12_DW.Integrator_DSTATE > SVM_VOLTAGE_LIMIT) {
    FOC_H12_DW.Integrator_DSTATE = SVM_VOLTAGE_LIMIT;
  } else if (FOC_H12_DW.Integrator_DSTATE < -SVM_VOLTAGE_LIMIT) {
    FOC_H12_DW.Integrator_DSTATE = -SVM_VOLTAGE_LIMIT;
  }

  /* End of Update for DiscreteIntegrator: '<S132>/Integrator' */

  /* Update for DiscreteIntegrator: '<S127>/Filter' */
  FOC_H12_DW.Filter_DSTATE += 0.0001 * rtb_Product;

  /* Update for Delay: '<S169>/Delay' */
  FOC_H12_DW.icLoad_h = false;
  FOC_H12_DW.Delay_DSTATE_g = FOC_H12_Y.Iq_ref;

  /* Update for DiscreteIntegrator: '<S78>/Integrator' incorporates:
   *  Gain: '<S90>/Kt'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S75>/IProd Out'
   *  Sum: '<S70>/SumI2'
   *  Sum: '<S70>/SumI4'
   *  Sum: '<S90>/SumI3'
   *  Sum: '<S91>/SumI1'
   */
  FOC_H12_DW.Integrator_DSTATE_h += (((FOC_H12_Y.Vq_PID - FOC_H12_Y.Vq_PID) *
    -10.0 + FOC_H12_Y.Iq_error *
    FOC_H12_U.MTPA_PID.Torque_PID_MTPA.Ki_torque_PID_MTPA) + (FOC_H12_Y.Vq_PID -
    rtb_IqTable)) * 0.0001;
  if (FOC_H12_DW.Integrator_DSTATE_h > SVM_VOLTAGE_LIMIT) {
    FOC_H12_DW.Integrator_DSTATE_h = SVM_VOLTAGE_LIMIT;
  } else if (FOC_H12_DW.Integrator_DSTATE_h < -SVM_VOLTAGE_LIMIT) {
    FOC_H12_DW.Integrator_DSTATE_h = -SVM_VOLTAGE_LIMIT;
  }

  /* End of Update for DiscreteIntegrator: '<S78>/Integrator' */

  /* Update for DiscreteIntegrator: '<S73>/Filter' */
  FOC_H12_DW.Filter_DSTATE_d += 0.0001 * rtb_NProdOut_l;

  /* Update for Delay: '<S3>/Delay' */
  FOC_H12_DW.icLoad_n = false;
}

/* Model step function for TID1 */
void FOC_H12_step1(void)               /* Sample time: [0.001s, 0.0s] */
{
  float rtb_NProdOut_n;
  float rtb_Sum;

  /* Product: '<S211>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S203>/Filter'
   *  Product: '<S201>/DProd Out'
   *  RateTransition generated from: '<S201>/DProd Out'
   *  RateTransition generated from: '<S211>/NProd Out'
   *  Sum: '<S203>/SumD'
   * */
  rtb_NProdOut_n = (FOC_H12_DW.TmpRTBAtDProdOutInport1_Buffer *
                    FOC_H12_DW.TmpRTBAtDProdOutInport2_Buffer -
                    FOC_H12_DW.Filter_DSTATE_i) *
    FOC_H12_DW.TmpRTBAtNProdOutInport2_Buffer;

  /* Sum: '<S218>/Sum' incorporates:
   *  DiscreteIntegrator: '<S208>/Integrator'
   *  Product: '<S213>/PProd Out'
   *  RateTransition generated from: '<S213>/PProd Out'
   * */
  rtb_Sum = (FOC_H12_DW.TmpRTBAtPProdOutInport1_Buffer *
             FOC_H12_DW.TmpRTBAtPProdOutInport2_Buffer +
             FOC_H12_DW.Integrator_DSTATE_b) + rtb_NProdOut_n;

  /* Switch: '<S216>/Switch2' incorporates:
   *  RateTransition generated from: '<S216>/LowerRelop1'
   *  RateTransition generated from: '<S216>/UpperRelop'
   *  RelationalOperator: '<S216>/LowerRelop1'
   *  RelationalOperator: '<S216>/UpperRelop'
   *  Switch: '<S216>/Switch'
   */
  if (rtb_Sum > FOC_H12_DW.TmpRTBAtLowerRelop1Inport2_Buff) {
    /* Switch: '<S216>/Switch2' incorporates:
     *  RateTransition generated from: '<S216>/Switch2'
     */
    FOC_H12_Y.Iq_gen = FOC_H12_DW.TmpRTBAtSwitch2Inport1_Buffer;
  } else if (rtb_Sum < FOC_H12_DW.TmpRTBAtUpperRelopInport2_Buffe) {
    /* Switch: '<S216>/Switch2' incorporates:
     *  RateTransition generated from: '<S216>/Switch'
     *  Switch: '<S216>/Switch'
     */
    FOC_H12_Y.Iq_gen = FOC_H12_DW.TmpRTBAtSwitchInport1_Buffer;
  } else {
    /* Switch: '<S216>/Switch2' incorporates:
     *  Switch: '<S216>/Switch'
     */
    FOC_H12_Y.Iq_gen = rtb_Sum;
  }

  if (d.forward_pin == GPIO_PIN_RESET && d.reverse_pin == GPIO_PIN_SET)
    FOC_H12_Y.Iq_gen *= 1.0f;
  else if (d.forward_pin == GPIO_PIN_SET && d.reverse_pin == GPIO_PIN_RESET)
    FOC_H12_Y.Iq_gen *= -1.0f;
  else
    FOC_H12_Y.Iq_gen = 0.0f;

  /* End of Switch: '<S216>/Switch2' */

  /* RateTransition generated from: '<S2>/Product' */
  FOC_H12_DW.TmpRTBAtProductInport2_Buffer0 = FOC_H12_Y.Iq_gen;

  /* Update for DiscreteIntegrator: '<S208>/Integrator' incorporates:
   *  Product: '<S205>/IProd Out'
   *  RateTransition generated from: '<S205>/IProd Out'
   *  Sum: '<S200>/SumI2'
   *  Sum: '<S200>/SumI4'
   *  Sum: '<S220>/SumI3'
   *  Sum: '<S221>/SumI1'
   * */
  FOC_H12_DW.Integrator_DSTATE_b += ((FOC_H12_DW.TmpRTBAtIProdOutInport1_Buffer *
    FOC_H12_DW.TmpRTBAtIProdOutInport2_Buffer + (FOC_H12_Y.Iq_gen -
    FOC_H12_Y.Iq_gen)) + (FOC_H12_Y.Iq_gen - rtb_Sum)) * 0.001;
  if (FOC_H12_DW.Integrator_DSTATE_b > MOTOR_PEAK_AC) {
    FOC_H12_DW.Integrator_DSTATE_b = MOTOR_PEAK_AC;
  } else if (FOC_H12_DW.Integrator_DSTATE_b < -MOTOR_PEAK_AC) {
    FOC_H12_DW.Integrator_DSTATE_b = -MOTOR_PEAK_AC;
  }

  /* End of Update for DiscreteIntegrator: '<S208>/Integrator' */

  /* Update for DiscreteIntegrator: '<S203>/Filter' */
  FOC_H12_DW.Filter_DSTATE_i += 0.001 * rtb_NProdOut_n;
}

/* Model initialize function */
void FOC_H12_initialize(void)
{
  /* InitializeConditions for Delay: '<S9>/Delay' */
  FOC_H12_DW.icLoad = true;

  /* InitializeConditions for Delay: '<S168>/Delay' */
  FOC_H12_DW.icLoad_a = true;

  /* InitializeConditions for Delay: '<S169>/Delay' */
  FOC_H12_DW.icLoad_h = true;

  /* InitializeConditions for Delay: '<S3>/Delay' */
  FOC_H12_DW.icLoad_n = true;

  /* Motor Params */
  FOC_H12_U.BusVoltage_V = OP_VOLTAGE;
  FOC_H12_U.Iq_Torque_ratio = CURR_TORQUE_RATIO;

  /* Id Iq Limits */
  FOC_H12_U.Id_Iq_MTPA_limit.Iq_up_limit = 250.0f;
  FOC_H12_U.Id_Iq_MTPA_limit.Iq_low_limit = -250.0f;
  FOC_H12_U.Id_Iq_MTPA_limit.Id_up_limit = 300.0f;
  FOC_H12_U.Id_Iq_MTPA_limit.Id_low_limit = -300.0f;
  
  /* Speed Ref Rate Limiter Settings */
  FOC_H12_U.Ref_Speed_rate_up = 10.0f * 10000.0f;
  FOC_H12_U.Ref_Speed_rate_down = -1000.0f * 10000.0f;

  /* Rate Limiter Settings */
  FOC_H12_U.Rate_limiter.Torque_gen_ramp_up = 50.0f * 1000.0f;
  FOC_H12_U.Rate_limiter.Torque_gen_ramp_down = -50.0f * 1000.0f;
  FOC_H12_U.Rate_limiter.Iq_ramp_up = 50.0f * 10000.0f;
  FOC_H12_U.Rate_limiter.Iq_ramp_down = -50.0f * 10000.0f;
  FOC_H12_U.Rate_limiter.Id_ramp_up = 50.0f * 10000.0f;
  FOC_H12_U.Rate_limiter.Id_ramp_down = -50.0f * 10000.0f;

  /* Speed PID Values */
  FOC_H12_U.MTPA_PID.Up_Limit_speed_PID_MTPA = MOTOR_PEAK_AC;
  FOC_H12_U.MTPA_PID.Low_Limit_speed_PID_MTPA = 0.0f;
  FOC_H12_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA = 4.0f;
  FOC_H12_U.MTPA_PID.Speed_PID_MTPA.Ki_speed_PID_MTPA = 8.0f;
  FOC_H12_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA = 0.00001f;
  FOC_H12_U.MTPA_PID.Speed_PID_MTPA.Filter_speed_PID_MTPA = 5.0f;

  /* Iq PID Values */
  FOC_H12_U.MTPA_PID.Up_Limit_torque_PID = SVM_VOLTAGE_LIMIT;
  FOC_H12_U.MTPA_PID.Low_Limit_torque_PID = -SVM_VOLTAGE_LIMIT;
  FOC_H12_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA = 0.1f;
  FOC_H12_U.MTPA_PID.Torque_PID_MTPA.Ki_torque_PID_MTPA = 7.0f;
  FOC_H12_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA = 0.00001f;
  FOC_H12_U.MTPA_PID.Torque_PID_MTPA.Filter_torque_PID_MTPA = 5.0f;

  /* Id PID Values */
  FOC_H12_U.MTPA_PID.Up_Limit_flux_PID = SVM_VOLTAGE_LIMIT;
  FOC_H12_U.MTPA_PID.Low_Limit_flux_PID = -SVM_VOLTAGE_LIMIT;
  FOC_H12_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA = 0.2f;
  FOC_H12_U.MTPA_PID.Flux_PID_MTPA.Ki_flux_PID_MTPA = 6.0f;
  FOC_H12_U.MTPA_PID.Flux_PID_MTPA.Kd_flux_PID_MTPA = 0.00001f;
  FOC_H12_U.MTPA_PID.Flux_PID_MTPA.Filter_flux_PID_MTPA = 5.0f;

  /* IIR Filter Coefficients */
  FOC_H12_U.IIR_Filter_Coefficient.Id_Filter_switch = 1.0f;
  FOC_H12_U.IIR_Filter_Coefficient.Iq_Filter_switch = 1.0f;
  FOC_H12_U.IIR_Filter_Coefficient.Id_Filter_coefficient = 0.9f;
  FOC_H12_U.IIR_Filter_Coefficient.Iq_Filter_coefficient = 0.9f; 

}

/* Model terminate function */
void FOC_H12_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
