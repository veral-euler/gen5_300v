/*
 * File: FOC_MTPA_FWC_FF.c
 *
 * Code generated for Simulink model 'FOC_MTPA_FWC_FF'.
 *
 * Model version                  : 18.429
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Fri Apr 17 14:57:16 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_MTPA_FWC_FF.h"
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include "FOC_MTPA_FWC_FF_private.h"
#include "rt_nonfinite.h"
#include "FOC_MTPA_FWC_FF_types.h"
#include "rt_defines.h"

/* Named constants for Chart: '<S158>/Chart' */
#define FOC_MTPA_FWC_FF_IN_FW          ((uint8_t)1U)
#define FOC_MTPA_FWC_FF_IN_MTPA        ((uint8_t)2U)
#define FOC_MTPA_FWC_IN_NO_ACTIVE_CHILD ((uint8_t)0U)

/* Named constants for Chart: '<S5>/FNR_switching' */
#define FOC_MTPA_FWC_FF_IN_Forward     ((uint8_t)1U)
#define FOC_MTPA_FWC_FF_IN_Initial     ((uint8_t)2U)
#define FOC_MTPA_FWC_FF_IN_Neutral     ((uint8_t)3U)
#define FOC_MTPA_FWC_FF_IN_Normal      ((uint8_t)2U)
#define FOC_MTPA_FWC_FF_IN_Regen_mode1 ((uint8_t)4U)
#define FOC_MTPA_FWC_FF_IN_Reverse     ((uint8_t)5U)
#define FOC_MTPA_FWC__IN_Throttle_error ((uint8_t)6U)
#define FOC_MTPA__IN_Invalid_Transition ((uint8_t)1U)

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

/* Forward declaration for local functions */
static void FOC_MTPA_FWC_FF_Regen_mode1(const float *Abs, const bool *FNR_Active);

/* Function for Chart: '<S5>/FNR_switching' */
static void FOC_MTPA_FWC_FF_Regen_mode1(const float *Abs, const bool *FNR_Active)
{
  float ref_speed;
  float shape;
  float x2;
  bool tmp;
  tmp = !*FNR_Active;

  /* Inport: '<Root>/Regen' */
  if (tmp || ((*Abs <= FOC_MTPA_FWC_FF_U.Regen.RPM_Regen_min_Speed) &&
              FOC_MTPA_FWC_FF_U.Regen.Polarity_switch)) {
    FOC_MTPA_FWC_FF_B.T_ref = 0.0F;
    FOC_MTPA_FWC_FF_DW.counter = 0.0F;

    /* Outport: '<Root>/Regen_Mode' */
    FOC_MTPA_FWC_FF_Y.Regen_Mode = false;
    FOC_MTPA_FWC_FF_DW.durationCounter_2_e = 0U;
    FOC_MTPA_FWC_FF_DW.durationCounter_1_l = 0U;
    FOC_MTPA_FWC_FF_DW.is_c2_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Reverse;

    /* Outport: '<Root>/Throttle_en' */
    FOC_MTPA_FWC_FF_Y.Throttle_en = true;

    /* Outport: '<Root>/Throttle_State' */
    FOC_MTPA_FWC_FF_Y.Throttle_State = Reverse;
  } else if (tmp || ((*Abs <= FOC_MTPA_FWC_FF_U.Regen.RPM_Regen_min_Speed) &&
                     (!FOC_MTPA_FWC_FF_U.Regen.Polarity_switch))) {
    FOC_MTPA_FWC_FF_B.T_ref = 0.0F;
    FOC_MTPA_FWC_FF_DW.counter = 0.0F;

    /* Outport: '<Root>/Regen_Mode' */
    FOC_MTPA_FWC_FF_Y.Regen_Mode = false;
    FOC_MTPA_FWC_FF_DW.durationCounter_2 = 0U;
    FOC_MTPA_FWC_FF_DW.durationCounter_1 = 0U;
    FOC_MTPA_FWC_FF_DW.is_c2_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Forward;

    /* Outport: '<Root>/Throttle_en' */
    FOC_MTPA_FWC_FF_Y.Throttle_en = true;

    /* Outport: '<Root>/Throttle_State' */
    FOC_MTPA_FWC_FF_Y.Throttle_State = Forward;
  } else {
    FOC_MTPA_FWC_FF_DW.counter += fabsf(FOC_MTPA_FWC_FF_DW.rpm_prev - *Abs);
    if (FOC_MTPA_FWC_FF_DW.mid_speed <= FOC_MTPA_FWC_FF_U.Regen.regen_cap_rpm) {
      ref_speed = FOC_MTPA_FWC_FF_DW.mid_speed;
    } else {
      ref_speed = FOC_MTPA_FWC_FF_DW.init_speed;
    }

    ref_speed = fminf(fmaxf((ref_speed -
      FOC_MTPA_FWC_FF_U.Regen.RPM_Regen_min_Speed) / (fmaxf(ref_speed,
      FOC_MTPA_FWC_FF_U.Regen.regen_cap_rpm) -
      FOC_MTPA_FWC_FF_U.Regen.RPM_Regen_min_Speed), 0.0F), 1.0F) *
      FOC_MTPA_FWC_FF_DW.max_negTorque;
    if (*Abs >= FOC_MTPA_FWC_FF_DW.mid_speed) {
      x2 = fminf(fmaxf(FOC_MTPA_FWC_FF_DW.counter / fabsf
                       (FOC_MTPA_FWC_FF_DW.init_speed -
                        FOC_MTPA_FWC_FF_DW.mid_speed), 0.0F), 1.0F);
      shape = 1.0F - (1.0F - x2) * (1.0F - x2);
    } else {
      x2 = fminf(fmaxf((*Abs - FOC_MTPA_FWC_FF_U.Regen.RPM_Regen_min_Speed) /
                       (FOC_MTPA_FWC_FF_DW.mid_speed -
                        FOC_MTPA_FWC_FF_U.Regen.RPM_Regen_min_Speed), 0.0F),
                 1.0F);
      shape = 1.0F - (1.0F - x2) * (1.0F - x2);
    }

    x2 = fabsf(ref_speed);
    FOC_MTPA_FWC_FF_B.T_ref = (float)-FOC_MTPA_FWC_FF_DW.drive_sign * x2 * shape;
    if (-FOC_MTPA_FWC_FF_DW.drive_sign < 0.0) {
      FOC_MTPA_FWC_FF_B.T_ref = fminf(fmaxf(FOC_MTPA_FWC_FF_B.T_ref, ref_speed),
        0.0F);
    } else if (-FOC_MTPA_FWC_FF_DW.drive_sign > 0.0) {
      FOC_MTPA_FWC_FF_B.T_ref = fmaxf(fminf(FOC_MTPA_FWC_FF_B.T_ref, x2), 0.0F);
    } else {
      FOC_MTPA_FWC_FF_B.T_ref = 0.0F;
    }

    FOC_MTPA_FWC_FF_DW.rpm_prev = *Abs;
  }

  /* End of Inport: '<Root>/Regen' */
}

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
  float Abs;
  float rtb_DataTypeConversion1;
  float rtb_Product2_tmp;
  float rtb_Switch_f_idx_0;
  float rtb_TrigonometricFunction1_tmp;
  float rtb_UkYk1_j;
  float rtb_V_qo;
  float rtb_VqFF_unsat;
  float rtb_add_c;
  float rtb_k;
  int32_t i;
  bool FNR_Active;
  bool guard1;
  bool guard2;
  bool tmp;
  bool tmp_0;

  /* Update the flag to indicate when data transfers from
   *  Sample time: [0.0001s, 0.0s] to Sample time: [0.001s, 0.0s]  */
  (FOC_MTPA_FWC_FF_M->Timing.RateInteraction.TID0_1)++;
  if ((FOC_MTPA_FWC_FF_M->Timing.RateInteraction.TID0_1) > 9) {
    FOC_MTPA_FWC_FF_M->Timing.RateInteraction.TID0_1 = 0;
  }

  /* Outputs for Atomic SubSystem: '<S15>/Two phase CRL wrap' */
  /* Gain: '<S16>/one_by_sqrt3' incorporates:
   *  Inport: '<Root>/Phase Current'
   *  Sum: '<S16>/a_plus_2b'
   */
  rtb_DataTypeConversion1 = ((FOC_MTPA_FWC_FF_U.PhaseCurrent[0] +
    FOC_MTPA_FWC_FF_U.PhaseCurrent[1]) + FOC_MTPA_FWC_FF_U.PhaseCurrent[1]) *
    0.577350259F;

  /* End of Outputs for SubSystem: '<S15>/Two phase CRL wrap' */

  /* Trigonometry: '<S6>/Trigonometric Function' incorporates:
   *  Inport: '<Root>/angle'
   *  Trigonometry: '<S8>/Trigonometric Function1'
   */
  rtb_k = sinf(FOC_MTPA_FWC_FF_U.angle);

  /* Trigonometry: '<S6>/Trigonometric Function1' incorporates:
   *  Inport: '<Root>/angle'
   *  Trigonometry: '<S8>/Trigonometric Function'
   */
  rtb_TrigonometricFunction1_tmp = cosf(FOC_MTPA_FWC_FF_U.angle);

  /* Outputs for Atomic SubSystem: '<S14>/Two inputs CRL' */
  /* Outputs for Atomic SubSystem: '<S15>/Two phase CRL wrap' */
  /* AlgorithmDescriptorDelegate generated from: '<S23>/a16' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S16>/a16'
   *  Inport: '<Root>/Phase Current'
   *  Product: '<S23>/acos'
   *  Product: '<S23>/bsin'
   *  Sum: '<S23>/sum_Ds'
   *  Trigonometry: '<S6>/Trigonometric Function'
   *  Trigonometry: '<S6>/Trigonometric Function1'
   */
  FOC_MTPA_FWC_FF_Y.Id = FOC_MTPA_FWC_FF_U.PhaseCurrent[0] *
    rtb_TrigonometricFunction1_tmp + rtb_DataTypeConversion1 * rtb_k;

  /* AlgorithmDescriptorDelegate generated from: '<S23>/a16' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S16>/a16'
   *  Inport: '<Root>/Phase Current'
   *  Product: '<S23>/asin'
   *  Product: '<S23>/bcos'
   *  Sum: '<S23>/sum_Qs'
   *  Trigonometry: '<S6>/Trigonometric Function'
   *  Trigonometry: '<S6>/Trigonometric Function1'
   */
  FOC_MTPA_FWC_FF_Y.Iq = rtb_DataTypeConversion1 *
    rtb_TrigonometricFunction1_tmp - FOC_MTPA_FWC_FF_U.PhaseCurrent[0] * rtb_k;

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
  FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE = (1.0F -
    FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Id_Filter_coefficient) *
    FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE + FOC_MTPA_FWC_FF_Y.Id *
    FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Id_Filter_coefficient;

  /* Switch: '<S6>/Switch' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   */
  if (FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Id_Filter_switch) {
    /* AlgorithmDescriptorDelegate generated from: '<S23>/a16' incorporates:
     *  UnitDelay: '<S19>/Unit Delay'
     */
    FOC_MTPA_FWC_FF_Y.Id = FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE;
  }

  /* End of Switch: '<S6>/Switch' */

  /* Sum: '<S22>/Add1' incorporates:
   *  Constant: '<S13>/One'
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   *  Product: '<S22>/Product'
   *  Product: '<S22>/Product1'
   *  Sum: '<S13>/Sum'
   *  Switch: '<S13>/Switch1'
   *  UnitDelay: '<S22>/Unit Delay'
   */
  FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE_f = (1.0F -
    FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Iq_Filter_coefficient) *
    FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE_f + FOC_MTPA_FWC_FF_Y.Iq *
    FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Iq_Filter_coefficient;

  /* Switch: '<S6>/Switch1' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   */
  if (FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Iq_Filter_switch) {
    /* AlgorithmDescriptorDelegate generated from: '<S23>/a16' incorporates:
     *  UnitDelay: '<S22>/Unit Delay'
     */
    FOC_MTPA_FWC_FF_Y.Iq = FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE_f;
  }

  /* End of Switch: '<S6>/Switch1' */

  /* Delay: '<S10>/Ld_calc' incorporates:
   *  Inport: '<Root>/Motor_Parameters'
   */
  if (FOC_MTPA_FWC_FF_DW.icLoad) {
    FOC_MTPA_FWC_FF_DW.Ld_calc_DSTATE = FOC_MTPA_FWC_FF_U.Motor_Parameters.Ld;
  }

  /* Delay: '<S10>/Lq_calc' incorporates:
   *  Inport: '<Root>/Motor_Parameters'
   */
  if (FOC_MTPA_FWC_FF_DW.icLoad_o) {
    FOC_MTPA_FWC_FF_DW.Lq_calc_DSTATE = FOC_MTPA_FWC_FF_U.Motor_Parameters.Lq;
  }

  /* Sum: '<S2>/Subtract' incorporates:
   *  Delay: '<S10>/Ld_calc'
   *  Delay: '<S10>/Lq_calc'
   *  Sum: '<S9>/Subtract'
   */
  rtb_Product2_tmp = FOC_MTPA_FWC_FF_DW.Ld_calc_DSTATE -
    FOC_MTPA_FWC_FF_DW.Lq_calc_DSTATE;

  /* Product: '<S2>/Product2' incorporates:
   *  Constant: '<S2>/Constant'
   *  Inport: '<Root>/Motor_Parameters'
   *  Product: '<S2>/Product'
   *  Product: '<S2>/Product1'
   *  Sum: '<S2>/Add'
   *  Sum: '<S2>/Subtract'
   */
  FOC_MTPA_FWC_FF_Y.Actual_torque_from_meas = (float)((FOC_MTPA_FWC_FF_Y.Id *
    FOC_MTPA_FWC_FF_Y.Iq * rtb_Product2_tmp + FOC_MTPA_FWC_FF_Y.Iq *
    FOC_MTPA_FWC_FF_U.Motor_Parameters.Lambda) *
    FOC_MTPA_FWC_FF_U.Motor_Parameters.Pole_Pairs * 1.5);

  /* Switch: '<S4>/Switch' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  Math: '<S2>/Hypot'
   *  RelationalOperator: '<S4>/Relational Operator1'
   *  RelationalOperator: '<S4>/Relational Operator2'
   */
  if (FOC_MTPA_FWC_FF_U.MTPA_PID.Selection.I_0_T_1_switch) {
    tmp = (FOC_MTPA_FWC_FF_Y.Actual_torque_from_meas >=
           FOC_MTPA_FWC_FF_U.MTPA_PID.Selection.T_limit);
  } else {
    tmp = (rt_hypotf_snf(FOC_MTPA_FWC_FF_Y.Id, FOC_MTPA_FWC_FF_Y.Iq) >=
           FOC_MTPA_FWC_FF_U.MTPA_PID.Selection.I_limit);
  }

  /* Logic: '<S4>/Logical Operator' incorporates:
   *  Gain: '<S4>/Gain'
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S4>/Relational Operator'
   *  Switch: '<S4>/Switch'
   */
  FOC_MTPA_FWC_FF_Y.PID_Switch = ((9.54929638F *
    FOC_MTPA_FWC_FF_U.ActualSpeed_mech_radsec >=
    FOC_MTPA_FWC_FF_U.MTPA_PID.Selection.Speed_RPM_limit) && tmp);

  /* If: '<S4>/If' */
  if (FOC_MTPA_FWC_FF_Y.PID_Switch) {
    /* Outputs for IfAction SubSystem: '<S4>/If Action Subsystem' incorporates:
     *  ActionPort: '<S228>/Action Port'
     */
    /* SignalConversion generated from: '<S228>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge'
     */
    FOC_MTPA_FWC_FF_B.Merge[0] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA;

    /* SignalConversion generated from: '<S228>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge'
     */
    FOC_MTPA_FWC_FF_B.Merge[1] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Ki_flux_PID_MTPA;

    /* SignalConversion generated from: '<S228>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge'
     */
    FOC_MTPA_FWC_FF_B.Merge[2] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Kd_flux_PID_MTPA;

    /* SignalConversion generated from: '<S228>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge'
     */
    FOC_MTPA_FWC_FF_B.Merge[3] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Filter_flux_PID_MTPA;

    /* SignalConversion generated from: '<S228>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge'
     */
    FOC_MTPA_FWC_FF_B.Merge[4] = FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_flux_PID;

    /* SignalConversion generated from: '<S228>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge'
     */
    FOC_MTPA_FWC_FF_B.Merge[5] = FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_flux_PID;

    /* End of Outputs for SubSystem: '<S4>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S4>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S229>/Action Port'
     */
    /* SignalConversion generated from: '<S229>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge'
     */
    FOC_MTPA_FWC_FF_B.Merge[0] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA_low;

    /* SignalConversion generated from: '<S229>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge'
     */
    FOC_MTPA_FWC_FF_B.Merge[1] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Ki_flux_PID_MTPA_low;

    /* SignalConversion generated from: '<S229>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge'
     */
    FOC_MTPA_FWC_FF_B.Merge[2] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Kd_flux_PID_MTPA_low;

    /* SignalConversion generated from: '<S229>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge'
     */
    FOC_MTPA_FWC_FF_B.Merge[3] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Filter_flux_PID_MTPA_low;

    /* SignalConversion generated from: '<S229>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge'
     */
    FOC_MTPA_FWC_FF_B.Merge[4] = FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_flux_PID;

    /* SignalConversion generated from: '<S229>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge'
     */
    FOC_MTPA_FWC_FF_B.Merge[5] = FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_flux_PID;

    /* End of Outputs for SubSystem: '<S4>/If Action Subsystem1' */
  }

  /* End of If: '<S4>/If' */

  /* Sum: '<S158>/Subtract' incorporates:
   *  Gain: '<S158>/Gain1'
   *  Inport: '<Root>/Bus_Voltage'
   *  Inport: '<Root>/Is_max'
   *  Inport: '<Root>/Motor_Parameters'
   *  Product: '<S158>/Product4'
   */
  FOC_MTPA_FWC_FF_Y.V_max = 0.577350259F * FOC_MTPA_FWC_FF_U.BusVoltage_V -
    FOC_MTPA_FWC_FF_U.Is_max * FOC_MTPA_FWC_FF_U.Motor_Parameters.Rs;

  /* Product: '<S153>/Divide1' incorporates:
   *  Delay: '<S10>/Ld_calc'
   *  Delay: '<S10>/Lq_calc'
   *  Gain: '<S153>/Gain2'
   *  Inport: '<Root>/Motor_Parameters'
   *  Sum: '<S153>/Subtract2'
   */
  rtb_DataTypeConversion1 = FOC_MTPA_FWC_FF_U.Motor_Parameters.Lambda /
    ((FOC_MTPA_FWC_FF_DW.Lq_calc_DSTATE - FOC_MTPA_FWC_FF_DW.Ld_calc_DSTATE) *
     4.0F);

  /* RateTransition: '<S1>/Rate Transition' incorporates:
   *  RateTransition generated from: '<S1>/Data Type Conversion1'
   *  RateTransition generated from: '<S4>/Merge1'
   */
  tmp = (FOC_MTPA_FWC_FF_M->Timing.RateInteraction.TID0_1 == 1);
  if (tmp) {
    /* Outport: '<Root>/T_gen' */
    FOC_MTPA_FWC_FF_Y.T_gen = FOC_MTPA_FWC_FF_DW.RateTransition_Buffer0;
  }

  /* End of RateTransition: '<S1>/Rate Transition' */

  /* Abs: '<S5>/Abs' incorporates:
   *  Gain: '<S5>/Rad//sec to rpm'
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   */
  Abs = fabsf(9.54929638F * FOC_MTPA_FWC_FF_U.ActualSpeed_mech_radsec);

  /* RelationalOperator: '<S5>/FNR_Active' incorporates:
   *  Inport: '<Root>/Throttle_input'
   *  Sum: '<S5>/Add'
   */
  FNR_Active = (FOC_MTPA_FWC_FF_U.Throttle_input.Throttle_Inst_Voltage <=
                FOC_MTPA_FWC_FF_U.Throttle_input.Min_Throttle_Voltage +
                FOC_MTPA_FWC_FF_U.Throttle_input.Throttle_V_Hyst_band_FNR_shift);

  /* Outport: '<Root>/Throttle_error' incorporates:
   *  Inport: '<Root>/Throttle_input'
   *  Logic: '<S5>/Logical Operator'
   *  RelationalOperator: '<S5>/Relational Operator'
   *  RelationalOperator: '<S5>/Relational Operator1'
   */
  if (cS == ANGLE_CALIB)
    FOC_MTPA_FWC_FF_Y.Throttle_error = false;

  if (cS == FOC_START) {
    FOC_MTPA_FWC_FF_Y.Throttle_error =
    ((FOC_MTPA_FWC_FF_U.Throttle_input.Throttle_Inst_Voltage >=
      FOC_MTPA_FWC_FF_U.Throttle_input.Max_Throttle_Voltage) ||
     (FOC_MTPA_FWC_FF_U.Throttle_input.Throttle_Inst_Voltage <=
      FOC_MTPA_FWC_FF_U.Throttle_input.Min_Throttle_Voltage));
  }

  /* Chart: '<S5>/FNR_switching' incorporates:
   *  Inport: '<Root>/Drive_State'
   *  Inport: '<Root>/RPM_min_limit'
   *  Inport: '<Root>/Regen'
   *  Outport: '<Root>/T_gen'
   *  Outport: '<Root>/Throttle_error'
   */
  if (FOC_MTPA_FWC_FF_DW.is_active_c2_FOC_MTPA_FWC_FF == 0) {
    FOC_MTPA_FWC_FF_DW.is_active_c2_FOC_MTPA_FWC_FF = 1U;
    FOC_MTPA_FWC_FF_DW.is_c2_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Initial;

    /* Outport: '<Root>/Throttle_en' */
    FOC_MTPA_FWC_FF_Y.Throttle_en = false;

    /* Outport: '<Root>/Throttle_State' */
    FOC_MTPA_FWC_FF_Y.Throttle_State = Neutral;
    FOC_MTPA_FWC_FF_B.T_ref = 0.0F;
  } else {
    switch (FOC_MTPA_FWC_FF_DW.is_c2_FOC_MTPA_FWC_FF) {
     case FOC_MTPA_FWC_FF_IN_Forward:
      /* Outport: '<Root>/Throttle_State' */
      FOC_MTPA_FWC_FF_Y.Throttle_State = Forward;
      if (!FOC_MTPA_FWC_FF_Y.Throttle_error) {
        FOC_MTPA_FWC_FF_DW.durationCounter_2 = 0U;
      }

      if (FOC_MTPA_FWC_FF_DW.durationCounter_2 > 1000U) {
        FOC_MTPA_FWC_FF_DW.is_c2_FOC_MTPA_FWC_FF =
          FOC_MTPA_FWC__IN_Throttle_error;

        /* Outport: '<Root>/Throttle_en' */
        FOC_MTPA_FWC_FF_Y.Throttle_en = false;

        /* Outport: '<Root>/Throttle_State' */
        FOC_MTPA_FWC_FF_Y.Throttle_State = Throttle_Error;
      } else if (FOC_MTPA_FWC_FF_U.Drive_State == 2.0F) {
        FOC_MTPA_FWC_FF_DW.durationCounter_1_m = 0U;
        FOC_MTPA_FWC_FF_DW.is_c2_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Neutral;

        /* Outport: '<Root>/Throttle_en' */
        FOC_MTPA_FWC_FF_Y.Throttle_en = false;

        /* Outport: '<Root>/Throttle_State' */
        FOC_MTPA_FWC_FF_Y.Throttle_State = Neutral;
        FOC_MTPA_FWC_FF_DW.is_Neutral = FOC_MTPA__IN_Invalid_Transition;
      } else if (FOC_MTPA_FWC_FF_U.Drive_State == 3.0F) {
        FOC_MTPA_FWC_FF_DW.durationCounter_1_m = 0U;
        FOC_MTPA_FWC_FF_DW.is_c2_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Neutral;

        /* Outport: '<Root>/Throttle_en' */
        FOC_MTPA_FWC_FF_Y.Throttle_en = false;

        /* Outport: '<Root>/Throttle_State' */
        FOC_MTPA_FWC_FF_Y.Throttle_State = Neutral;
        FOC_MTPA_FWC_FF_DW.is_Neutral = FOC_MTPA_FWC_FF_IN_Normal;
      } else {
        if ((!FNR_Active) || (!(Abs >
                                FOC_MTPA_FWC_FF_U.Regen.RPM_Regen_min_Speed)) ||
            FOC_MTPA_FWC_FF_U.Regen.Polarity_switch ||
            (!FOC_MTPA_FWC_FF_U.Regen.Regen_Active)) {
          FOC_MTPA_FWC_FF_DW.durationCounter_1 = 0U;
        }

        if (FOC_MTPA_FWC_FF_DW.durationCounter_1 > 1000U) {
          FOC_MTPA_FWC_FF_DW.drive_sign = 1.0;
          FOC_MTPA_FWC_FF_DW.max_negTorque =
            -FOC_MTPA_FWC_FF_U.Regen.max_Regen_Torque;
          FOC_MTPA_FWC_FF_DW.is_c2_FOC_MTPA_FWC_FF =
            FOC_MTPA_FWC_FF_IN_Regen_mode1;

          /* Outport: '<Root>/Regen_Mode' */
          FOC_MTPA_FWC_FF_Y.Regen_Mode = true;
          FOC_MTPA_FWC_FF_DW.init_speed = Abs;
          FOC_MTPA_FWC_FF_DW.mid_speed = (FOC_MTPA_FWC_FF_DW.init_speed +
            FOC_MTPA_FWC_FF_U.Regen.RPM_Regen_min_Speed) / 2.0F;
          FOC_MTPA_FWC_FF_DW.rpm_prev = Abs;
          FOC_MTPA_FWC_FF_DW.counter = 0.0F;
          FOC_MTPA_FWC_FF_B.T_ref = 0.0F;
        } else {
          FOC_MTPA_FWC_FF_B.T_ref = FOC_MTPA_FWC_FF_Y.T_gen;
        }
      }
      break;

     case FOC_MTPA_FWC_FF_IN_Initial:
      /* Outport: '<Root>/Throttle_State' */
      FOC_MTPA_FWC_FF_Y.Throttle_State = Neutral;
      if ((FOC_MTPA_FWC_FF_Y.T_gen < 1.0F) && FNR_Active) {
        FOC_MTPA_FWC_FF_DW.durationCounter_1_m = 0U;
        FOC_MTPA_FWC_FF_DW.is_c2_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Neutral;

        /* Outport: '<Root>/Throttle_en' */
        FOC_MTPA_FWC_FF_Y.Throttle_en = false;

        /* Outport: '<Root>/Throttle_State' */
        FOC_MTPA_FWC_FF_Y.Throttle_State = Neutral;
        FOC_MTPA_FWC_FF_DW.is_Neutral = FOC_MTPA_FWC_FF_IN_Normal;
      }
      break;

     case FOC_MTPA_FWC_FF_IN_Neutral:
      /* Outport: '<Root>/Throttle_State' */
      FOC_MTPA_FWC_FF_Y.Throttle_State = Neutral;
      tmp_0 = !FOC_MTPA_FWC_FF_Y.Throttle_error;
      if (((!(FOC_MTPA_FWC_FF_U.Drive_State == 1.0F)) || tmp_0) &&
          ((!(FOC_MTPA_FWC_FF_U.Drive_State == 2.0F)) || tmp_0)) {
        FOC_MTPA_FWC_FF_DW.durationCounter_1_m = 0U;
      }

      if (FOC_MTPA_FWC_FF_DW.durationCounter_1_m > 1000U) {
        FOC_MTPA_FWC_FF_DW.is_Neutral = FOC_MTPA_FWC_IN_NO_ACTIVE_CHILD;
        FOC_MTPA_FWC_FF_DW.is_c2_FOC_MTPA_FWC_FF =
          FOC_MTPA_FWC__IN_Throttle_error;

        /* Outport: '<Root>/Throttle_en' */
        FOC_MTPA_FWC_FF_Y.Throttle_en = false;

        /* Outport: '<Root>/Throttle_State' */
        FOC_MTPA_FWC_FF_Y.Throttle_State = Throttle_Error;
      } else {
        FOC_MTPA_FWC_FF_B.T_ref = FOC_MTPA_FWC_FF_Y.T_gen;
        if (FOC_MTPA_FWC_FF_DW.is_Neutral == FOC_MTPA__IN_Invalid_Transition) {
          if (FOC_MTPA_FWC_FF_U.Drive_State == 3.0F) {
            FOC_MTPA_FWC_FF_DW.is_Neutral = FOC_MTPA_FWC_FF_IN_Normal;
          }

          /* case IN_Normal: */
        } else if ((FOC_MTPA_FWC_FF_U.Drive_State == 2.0F) && (Abs <=
                    FOC_MTPA_FWC_FF_U.RPM_min_limit) && tmp_0 &&
                   (FOC_MTPA_FWC_FF_Y.T_gen < 1.0F) && FNR_Active) {
          FOC_MTPA_FWC_FF_DW.is_Neutral = FOC_MTPA_FWC_IN_NO_ACTIVE_CHILD;
          FOC_MTPA_FWC_FF_DW.durationCounter_2_e = 0U;
          FOC_MTPA_FWC_FF_DW.durationCounter_1_l = 0U;
          FOC_MTPA_FWC_FF_DW.is_c2_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Reverse;

          /* Outport: '<Root>/Throttle_en' */
          FOC_MTPA_FWC_FF_Y.Throttle_en = true;

          /* Outport: '<Root>/Throttle_State' */
          FOC_MTPA_FWC_FF_Y.Throttle_State = Reverse;
        } else if ((FOC_MTPA_FWC_FF_U.Drive_State == 1.0F) && (Abs <=
                    FOC_MTPA_FWC_FF_U.RPM_min_limit) && tmp_0 &&
                   (FOC_MTPA_FWC_FF_Y.T_gen < 1.0F) && FNR_Active) {
          FOC_MTPA_FWC_FF_DW.is_Neutral = FOC_MTPA_FWC_IN_NO_ACTIVE_CHILD;
          FOC_MTPA_FWC_FF_DW.durationCounter_2 = 0U;
          FOC_MTPA_FWC_FF_DW.durationCounter_1 = 0U;
          FOC_MTPA_FWC_FF_DW.is_c2_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Forward;

          /* Outport: '<Root>/Throttle_en' */
          FOC_MTPA_FWC_FF_Y.Throttle_en = true;

          /* Outport: '<Root>/Throttle_State' */
          FOC_MTPA_FWC_FF_Y.Throttle_State = Forward;
        }
      }
      break;

     case FOC_MTPA_FWC_FF_IN_Regen_mode1:
      FOC_MTPA_FWC_FF_Regen_mode1(&Abs, &FNR_Active);
      break;

     case FOC_MTPA_FWC_FF_IN_Reverse:
      /* Outport: '<Root>/Throttle_State' */
      FOC_MTPA_FWC_FF_Y.Throttle_State = Reverse;
      if (!FOC_MTPA_FWC_FF_Y.Throttle_error) {
        FOC_MTPA_FWC_FF_DW.durationCounter_1_l = 0U;
      }

      if (FOC_MTPA_FWC_FF_DW.durationCounter_1_l > 1000U) {
        FOC_MTPA_FWC_FF_DW.is_c2_FOC_MTPA_FWC_FF =
          FOC_MTPA_FWC__IN_Throttle_error;

        /* Outport: '<Root>/Throttle_en' */
        FOC_MTPA_FWC_FF_Y.Throttle_en = false;

        /* Outport: '<Root>/Throttle_State' */
        FOC_MTPA_FWC_FF_Y.Throttle_State = Throttle_Error;
      } else if (FOC_MTPA_FWC_FF_U.Drive_State == 3.0F) {
        FOC_MTPA_FWC_FF_DW.durationCounter_1_m = 0U;
        FOC_MTPA_FWC_FF_DW.is_c2_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Neutral;

        /* Outport: '<Root>/Throttle_en' */
        FOC_MTPA_FWC_FF_Y.Throttle_en = false;

        /* Outport: '<Root>/Throttle_State' */
        FOC_MTPA_FWC_FF_Y.Throttle_State = Neutral;
        FOC_MTPA_FWC_FF_DW.is_Neutral = FOC_MTPA_FWC_FF_IN_Normal;
      } else if (FOC_MTPA_FWC_FF_U.Drive_State == 1.0F) {
        FOC_MTPA_FWC_FF_DW.durationCounter_1_m = 0U;
        FOC_MTPA_FWC_FF_DW.is_c2_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Neutral;

        /* Outport: '<Root>/Throttle_en' */
        FOC_MTPA_FWC_FF_Y.Throttle_en = false;

        /* Outport: '<Root>/Throttle_State' */
        FOC_MTPA_FWC_FF_Y.Throttle_State = Neutral;
        FOC_MTPA_FWC_FF_DW.is_Neutral = FOC_MTPA__IN_Invalid_Transition;
      } else {
        if ((!FNR_Active) || (!(Abs >
                                FOC_MTPA_FWC_FF_U.Regen.RPM_Regen_min_Speed)) ||
            (!FOC_MTPA_FWC_FF_U.Regen.Polarity_switch) ||
            (!FOC_MTPA_FWC_FF_U.Regen.Regen_Active)) {
          FOC_MTPA_FWC_FF_DW.durationCounter_2_e = 0U;
        }

        if (FOC_MTPA_FWC_FF_DW.durationCounter_2_e > 1000U) {
          FOC_MTPA_FWC_FF_DW.drive_sign = -1.0;
          FOC_MTPA_FWC_FF_DW.max_negTorque =
            FOC_MTPA_FWC_FF_U.Regen.max_Regen_Torque;
          FOC_MTPA_FWC_FF_DW.is_c2_FOC_MTPA_FWC_FF =
            FOC_MTPA_FWC_FF_IN_Regen_mode1;

          /* Outport: '<Root>/Regen_Mode' */
          FOC_MTPA_FWC_FF_Y.Regen_Mode = true;
          FOC_MTPA_FWC_FF_DW.init_speed = Abs;
          FOC_MTPA_FWC_FF_DW.mid_speed = (FOC_MTPA_FWC_FF_DW.init_speed +
            FOC_MTPA_FWC_FF_U.Regen.RPM_Regen_min_Speed) / 2.0F;
          FOC_MTPA_FWC_FF_DW.rpm_prev = Abs;
          FOC_MTPA_FWC_FF_DW.counter = 0.0F;
          FOC_MTPA_FWC_FF_B.T_ref = 0.0F;
        } else {
          FOC_MTPA_FWC_FF_B.T_ref = -FOC_MTPA_FWC_FF_Y.T_gen;
        }
      }
      break;

     default:
      /* Outport: '<Root>/Throttle_State' */
      /* case IN_Throttle_error: */
      FOC_MTPA_FWC_FF_Y.Throttle_State = Throttle_Error;
      if ((FOC_MTPA_FWC_FF_U.Drive_State == 3.0F) && (Abs <=
           FOC_MTPA_FWC_FF_U.RPM_min_limit) &&
          (!FOC_MTPA_FWC_FF_Y.Throttle_error) && FNR_Active) {
        FOC_MTPA_FWC_FF_DW.durationCounter_1_m = 0U;
        FOC_MTPA_FWC_FF_DW.is_c2_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_Neutral;

        /* Outport: '<Root>/Throttle_en' */
        FOC_MTPA_FWC_FF_Y.Throttle_en = false;

        /* Outport: '<Root>/Throttle_State' */
        FOC_MTPA_FWC_FF_Y.Throttle_State = Neutral;
        FOC_MTPA_FWC_FF_DW.is_Neutral = FOC_MTPA_FWC_FF_IN_Normal;
      } else {
        FOC_MTPA_FWC_FF_B.T_ref = FOC_MTPA_FWC_FF_Y.T_gen;
      }
      break;
    }
  }

  tmp_0 = (FNR_Active && (Abs > FOC_MTPA_FWC_FF_U.Regen.RPM_Regen_min_Speed));
  if (tmp_0 && (!FOC_MTPA_FWC_FF_U.Regen.Polarity_switch) &&
      FOC_MTPA_FWC_FF_U.Regen.Regen_Active) {
    FOC_MTPA_FWC_FF_DW.durationCounter_1++;
  } else {
    FOC_MTPA_FWC_FF_DW.durationCounter_1 = 0U;
  }

  if (FOC_MTPA_FWC_FF_Y.Throttle_error) {
    FOC_MTPA_FWC_FF_DW.durationCounter_2++;
  } else {
    FOC_MTPA_FWC_FF_DW.durationCounter_2 = 0U;
  }

  if (((FOC_MTPA_FWC_FF_U.Drive_State == 1.0F) &&
       FOC_MTPA_FWC_FF_Y.Throttle_error) || ((FOC_MTPA_FWC_FF_U.Drive_State ==
        2.0F) && FOC_MTPA_FWC_FF_Y.Throttle_error)) {
    FOC_MTPA_FWC_FF_DW.durationCounter_1_m++;
  } else {
    FOC_MTPA_FWC_FF_DW.durationCounter_1_m = 0U;
  }

  if (FOC_MTPA_FWC_FF_Y.Throttle_error) {
    FOC_MTPA_FWC_FF_DW.durationCounter_1_l++;
  } else {
    FOC_MTPA_FWC_FF_DW.durationCounter_1_l = 0U;
  }

  if (tmp_0 && FOC_MTPA_FWC_FF_U.Regen.Polarity_switch &&
      FOC_MTPA_FWC_FF_U.Regen.Regen_Active) {
    FOC_MTPA_FWC_FF_DW.durationCounter_2_e++;
  } else {
    FOC_MTPA_FWC_FF_DW.durationCounter_2_e = 0U;
  }

  /* End of Chart: '<S5>/FNR_switching' */

  /* Delay: '<S235>/Delay' */
  if (FOC_MTPA_FWC_FF_DW.icLoad_e) {
    FOC_MTPA_FWC_FF_DW.Delay_DSTATE = FOC_MTPA_FWC_FF_B.T_ref;
  }

  /* Product: '<S154>/delta fall limit' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  Product: '<S235>/delta rise limit'
   *  SampleTimeMath: '<S235>/sample time'
   *
   * About '<S235>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  FOC_MTPA_FWC_FF_Y.Id_error = FOC_MTPA_FWC_FF_U.Rate_limiter.Torque_gen_ramp_up
    * 0.0001F;

  /* Sum: '<S235>/Difference Inputs1' incorporates:
   *  Delay: '<S235>/Delay'
   *
   * Block description for '<S235>/Difference Inputs1':
   *
   *  Add in CPU
   */
  Abs = FOC_MTPA_FWC_FF_B.T_ref - FOC_MTPA_FWC_FF_DW.Delay_DSTATE;

  /* Switch: '<S236>/Switch2' incorporates:
   *  RelationalOperator: '<S236>/LowerRelop1'
   */
  if (!(Abs > FOC_MTPA_FWC_FF_Y.Id_error)) {
    /* Product: '<S154>/delta fall limit' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  Product: '<S235>/delta fall limit'
     *  SampleTimeMath: '<S235>/sample time'
     *
     * About '<S235>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    FOC_MTPA_FWC_FF_Y.Id_error = 0.0001F *
      FOC_MTPA_FWC_FF_U.Rate_limiter.Torque_gen_ramp_down;

    /* Switch: '<S236>/Switch' incorporates:
     *  RelationalOperator: '<S236>/UpperRelop'
     */
    if (!(Abs < FOC_MTPA_FWC_FF_Y.Id_error)) {
      /* Product: '<S154>/delta fall limit' */
      FOC_MTPA_FWC_FF_Y.Id_error = Abs;
    }

    /* End of Switch: '<S236>/Switch' */
  }

  /* End of Switch: '<S236>/Switch2' */

  /* Sum: '<S235>/Difference Inputs2' incorporates:
   *  Delay: '<S235>/Delay'
   *
   * Block description for '<S235>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_MTPA_FWC_FF_Y.T_ref_FNR = FOC_MTPA_FWC_FF_Y.Id_error +
    FOC_MTPA_FWC_FF_DW.Delay_DSTATE;

  /* Product: '<S153>/Divide' incorporates:
   *  Abs: '<S153>/Abs1'
   *  Constant: '<S153>/Constant1'
   *  Gain: '<S153>/Gain'
   *  Inport: '<Root>/Motor_Parameters'
   *  Product: '<S153>/Product'
   */
  FOC_MTPA_FWC_FF_Y.I_qo = fabsf(2.0F * FOC_MTPA_FWC_FF_Y.T_ref_FNR) / (float)
    (FOC_MTPA_FWC_FF_U.Motor_Parameters.Lambda *
     FOC_MTPA_FWC_FF_U.Motor_Parameters.Pole_Pairs * 3.0);

  /* Switch: '<S165>/Switch2' incorporates:
   *  Inport: '<Root>/Id_Iq_MTPA_limit'
   *  RelationalOperator: '<S165>/LowerRelop1'
   *  RelationalOperator: '<S165>/UpperRelop'
   *  Switch: '<S165>/Switch'
   */
  if (FOC_MTPA_FWC_FF_Y.I_qo > FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_up_limit) {
    /* Switch: '<S165>/Switch2' */
    FOC_MTPA_FWC_FF_Y.I_mag = FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_up_limit;
  } else if (FOC_MTPA_FWC_FF_Y.I_qo <
             FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_low_limit) {
    /* Switch: '<S165>/Switch2' incorporates:
     *  Switch: '<S165>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.I_mag = FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_low_limit;
  } else {
    /* Switch: '<S165>/Switch2' incorporates:
     *  Switch: '<S165>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.I_mag = FOC_MTPA_FWC_FF_Y.I_qo;
  }

  /* End of Switch: '<S165>/Switch2' */

  /* Product: '<S154>/delta fall limit' incorporates:
   *  Math: '<S153>/Math Function2'
   */
  FOC_MTPA_FWC_FF_Y.Id_error = FOC_MTPA_FWC_FF_Y.I_mag * FOC_MTPA_FWC_FF_Y.I_mag;

  /* Sum: '<S153>/Subtract' incorporates:
   *  Abs: '<S153>/Abs2'
   *  Gain: '<S153>/Gain4'
   *  Math: '<S153>/Math Function'
   *  Sqrt: '<S153>/Sqrt'
   *  Sum: '<S153>/Add'
   */
  FOC_MTPA_FWC_FF_Y.Id_ref_MTPA = rtb_DataTypeConversion1 - sqrtf(fabsf
    (rtb_DataTypeConversion1 * rtb_DataTypeConversion1 + 0.5F *
     FOC_MTPA_FWC_FF_Y.Id_error));

  /* Switch: '<S164>/Switch2' incorporates:
   *  Inport: '<Root>/Id_Iq_MTPA_limit'
   *  RelationalOperator: '<S164>/LowerRelop1'
   *  RelationalOperator: '<S164>/UpperRelop'
   *  Switch: '<S164>/Switch'
   */
  if (FOC_MTPA_FWC_FF_Y.Id_ref_MTPA >
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_up_limit) {
    /* Sum: '<S153>/Subtract' */
    FOC_MTPA_FWC_FF_Y.Id_ref_MTPA =
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_up_limit;
  } else if (FOC_MTPA_FWC_FF_Y.Id_ref_MTPA <
             FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_low_limit) {
    /* Sum: '<S153>/Subtract' incorporates:
     *  Switch: '<S164>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Id_ref_MTPA =
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_low_limit;
  }

  /* End of Switch: '<S164>/Switch2' */

  /* Signum: '<S153>/Sign' */
  if (rtIsNaNF(FOC_MTPA_FWC_FF_Y.T_ref_FNR)) {
    Abs = (rtNaNF);
  } else if (FOC_MTPA_FWC_FF_Y.T_ref_FNR < 0.0F) {
    Abs = -1.0F;
  } else {
    Abs = (float)(FOC_MTPA_FWC_FF_Y.T_ref_FNR > 0.0F);
  }

  /* Product: '<S153>/Product1' incorporates:
   *  Abs: '<S153>/Abs'
   *  Math: '<S153>/Math Function3'
   *  Signum: '<S153>/Sign'
   *  Sqrt: '<S153>/Sqrt1'
   *  Sum: '<S153>/Subtract1'
   */
  FOC_MTPA_FWC_FF_Y.Iq_ref_MTPA = sqrtf(fabsf(FOC_MTPA_FWC_FF_Y.Id_error -
    FOC_MTPA_FWC_FF_Y.Id_ref_MTPA * FOC_MTPA_FWC_FF_Y.Id_ref_MTPA)) * Abs;

  /* Product: '<S158>/Product' incorporates:
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   *  Inport: '<Root>/Motor_Parameters'
   *  Product: '<S25>/we'
   */
  rtb_VqFF_unsat = FOC_MTPA_FWC_FF_U.Motor_Parameters.Pole_Pairs *
    FOC_MTPA_FWC_FF_U.ActualSpeed_mech_radsec;

  /* Gain: '<S158>/Gain' incorporates:
   *  Delay: '<S10>/Lq_calc'
   *  Product: '<S158>/Product'
   *  Product: '<S158>/Product1'
   */
  Abs = -(rtb_VqFF_unsat * FOC_MTPA_FWC_FF_DW.Lq_calc_DSTATE *
          FOC_MTPA_FWC_FF_Y.Iq_ref_MTPA);

  /* Product: '<S158>/Product3' incorporates:
   *  Delay: '<S10>/Ld_calc'
   *  Inport: '<Root>/Motor_Parameters'
   *  Product: '<S158>/Product'
   *  Product: '<S158>/Product2'
   *  Sum: '<S158>/Add'
   */
  rtb_V_qo = (FOC_MTPA_FWC_FF_DW.Ld_calc_DSTATE * FOC_MTPA_FWC_FF_Y.Id_ref_MTPA
              + FOC_MTPA_FWC_FF_U.Motor_Parameters.Lambda) * rtb_VqFF_unsat;

  /* Outputs for IfAction SubSystem: '<S9>/If Action Subsystem1' incorporates:
   *  ActionPort: '<S152>/Action Port'
   */
  /* If: '<S9>/If' incorporates:
   *  Math: '<S158>/Square'
   *  Math: '<S158>/Square1'
   *  Sqrt: '<S158>/Sqrt'
   *  Sqrt: '<S161>/Sqrt'
   *  Sum: '<S158>/Add1'
   */
  FOC_MTPA_FWC_FF_Y.V_s = sqrtf(Abs * Abs + rtb_V_qo * rtb_V_qo);

  /* End of Outputs for SubSystem: '<S9>/If Action Subsystem1' */

  /* Chart: '<S158>/Chart' */
  guard1 = false;
  guard2 = false;
  if (FOC_MTPA_FWC_FF_DW.is_active_c3_FOC_MTPA_FWC_FF == 0) {
    FOC_MTPA_FWC_FF_DW.is_active_c3_FOC_MTPA_FWC_FF = 1U;
    FOC_MTPA_FWC_FF_DW.is_c3_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_MTPA;

    /* Outport: '<Root>/MTPA_FWC_condition' */
    FOC_MTPA_FWC_FF_Y.MTPA_FWC_condition = false;
    guard2 = true;
  } else if (FOC_MTPA_FWC_FF_DW.is_c3_FOC_MTPA_FWC_FF == FOC_MTPA_FWC_FF_IN_FW)
  {
    if (FOC_MTPA_FWC_FF_Y.V_s < FOC_MTPA_FWC_FF_U.FWC_values.F2M_factor *
        FOC_MTPA_FWC_FF_Y.V_max) {
      FOC_MTPA_FWC_FF_DW.is_c3_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_MTPA;

      /* Outport: '<Root>/MTPA_FWC_condition' */
      FOC_MTPA_FWC_FF_Y.MTPA_FWC_condition = false;
      guard2 = true;
    } else {
      /* Outport: '<Root>/MTPA_FWC_condition' */
      FOC_MTPA_FWC_FF_Y.MTPA_FWC_condition = true;
      guard1 = true;
    }

    /* case IN_MTPA: */
  } else if (FOC_MTPA_FWC_FF_Y.V_s > FOC_MTPA_FWC_FF_U.FWC_values.M2F_factor *
             FOC_MTPA_FWC_FF_Y.V_max) {
    FOC_MTPA_FWC_FF_DW.is_c3_FOC_MTPA_FWC_FF = FOC_MTPA_FWC_FF_IN_FW;

    /* Outport: '<Root>/MTPA_FWC_condition' */
    FOC_MTPA_FWC_FF_Y.MTPA_FWC_condition = true;
    guard1 = true;
  } else {
    /* Outport: '<Root>/MTPA_FWC_condition' */
    FOC_MTPA_FWC_FF_Y.MTPA_FWC_condition = false;
    guard2 = true;
  }

  if (guard2) {
    /* Outputs for IfAction SubSystem: '<S9>/If Action Subsystem' incorporates:
     *  ActionPort: '<S151>/Action Port'
     */
    /* If: '<S9>/If' incorporates:
     *  Merge: '<S9>/Merge'
     *  SignalConversion generated from: '<S151>/Id_ref'
     *  SignalConversion generated from: '<S151>/Iq_ref'
     */
    FOC_MTPA_FWC_FF_B.Merge_k[0] = FOC_MTPA_FWC_FF_Y.Id_ref_MTPA;
    FOC_MTPA_FWC_FF_B.Merge_k[1] = FOC_MTPA_FWC_FF_Y.Iq_ref_MTPA;

    /* End of Outputs for SubSystem: '<S9>/If Action Subsystem' */
  }

  if (guard1) {
    /* Outputs for IfAction SubSystem: '<S9>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S152>/Action Port'
     */
    /* If: '<S9>/If' incorporates:
     *  Constant: '<S159>/Constant'
     *  Constant: '<S159>/Constant1'
     *  Constant: '<S159>/Modulation index threshold'
     *  Constant: '<S163>/Constant1'
     *  DiscreteIntegrator: '<S159>/Discrete-Time Integrator'
     *  Fcn: '<S160>/x->r'
     *  Fcn: '<S160>/x->theta'
     *  Fcn: '<S162>/r->x'
     *  Fcn: '<S162>/theta->y'
     *  Inport: '<Root>/FWC_values'
     *  Merge: '<S9>/Merge'
     *  Product: '<S152>/Product'
     *  Product: '<S159>/Product'
     *  Product: '<S159>/Product1'
     *  Product: '<S159>/Product2'
     *  Product: '<S161>/Product'
     *  RelationalOperator: '<S152>/Relational Operator'
     *  Saturate: '<S159>/Saturation'
     *  SignalConversion generated from: '<S152>/Out1'
     *  Sqrt: '<S158>/Sqrt'
     *  Sum: '<S159>/Sum'
     *  Sum: '<S159>/Sum1'
     *  Sum: '<S159>/Sum2'
     *  Sum: '<S159>/Sum3'
     *  Sum: '<S159>/Sum4'
     *  Switch: '<S163>/Switch'
     *  UnitDelay: '<S159>/Unit Delay'
     * */
    FNR_Active = (FOC_MTPA_FWC_FF_Y.V_s <= FOC_MTPA_FWC_FF_Y.V_max *
                  FOC_MTPA_FWC_FF_U.FWC_values.FW_Int_reset_factor);
    if (FNR_Active && (FOC_MTPA_FWC_FF_DW.DiscreteTimeIntegrator_PrevRese <= 0))
    {
      FOC_MTPA_FWC_FF_DW.DiscreteTimeIntegrator_DSTATE = 1.0F;
    }

    if (FOC_MTPA_FWC_FF_Y.V_max > 0.1F) {
      Abs = FOC_MTPA_FWC_FF_Y.V_max;
    } else {
      Abs = 0.1F;
    }

    FOC_MTPA_FWC_FF_DW.DiscreteTimeIntegrator_DSTATE += ((1.0F -
      FOC_MTPA_FWC_FF_Y.V_s / Abs) * FOC_MTPA_FWC_FF_U.FWC_values.Kfw +
      FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE_c * FOC_MTPA_FWC_FF_U.FWC_values.Kaw) *
      0.0001F;
    if (FOC_MTPA_FWC_FF_DW.DiscreteTimeIntegrator_DSTATE > 1.0F) {
      Abs = 1.0F;
    } else if (FOC_MTPA_FWC_FF_DW.DiscreteTimeIntegrator_DSTATE < 0.0F) {
      Abs = 0.0F;
    } else {
      Abs = FOC_MTPA_FWC_FF_DW.DiscreteTimeIntegrator_DSTATE;
    }

    FOC_MTPA_FWC_FF_DW.UnitDelay_DSTATE_c = Abs -
      FOC_MTPA_FWC_FF_DW.DiscreteTimeIntegrator_DSTATE;
    {
      float angle_MTPA = rt_atan2f_snf(FOC_MTPA_FWC_FF_Y.Iq_ref_MTPA,
                                        FOC_MTPA_FWC_FF_Y.Id_ref_MTPA);
      /* Rotate toward -pi for reverse (Iq<0), +pi for forward (Iq>0).
       * Original formula assumed +pi target, which gave positive Id in reverse
       * when LivGuard's high Lambda forces FW_scale below ~0.7. */
      float fw_target = (angle_MTPA >= 0.0F) ? (float)3.1415926535897931
                                              : -(float)3.1415926535897931;
      Abs = fw_target - (fw_target - angle_MTPA) * Abs;
    }
    rtb_V_qo = rt_hypotf_snf(FOC_MTPA_FWC_FF_Y.Id_ref_MTPA,
      FOC_MTPA_FWC_FF_Y.Iq_ref_MTPA);
    FOC_MTPA_FWC_FF_B.Merge_k[0] = rtb_V_qo * cosf(Abs);
    FOC_MTPA_FWC_FF_B.Merge_k[1] = rtb_V_qo * sinf(Abs);
    FOC_MTPA_FWC_FF_DW.DiscreteTimeIntegrator_PrevRese = (int8_t)FNR_Active;

    /* End of Outputs for SubSystem: '<S9>/If Action Subsystem1' */
  }

  /* End of Chart: '<S158>/Chart' */

  /* Delay: '<S154>/Delay' */
  if (FOC_MTPA_FWC_FF_DW.icLoad_l) {
    /* Sum: '<S154>/Difference Inputs2'
     *
     * Block description for '<S154>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_MTPA_FWC_FF_DW.Delay_DSTATE_l = FOC_MTPA_FWC_FF_B.Merge_k[0];
  }

  /* Product: '<S154>/delta fall limit' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  Product: '<S154>/delta rise limit'
   *  SampleTimeMath: '<S154>/sample time'
   *
   * About '<S154>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  FOC_MTPA_FWC_FF_Y.Id_error = FOC_MTPA_FWC_FF_U.Rate_limiter.Id_ramp_up *
    0.0001F;

  /* Sum: '<S154>/Difference Inputs1' incorporates:
   *  Delay: '<S154>/Delay'
   *
   * Block description for '<S154>/Difference Inputs1':
   *
   *  Add in CPU
   */
  Abs = FOC_MTPA_FWC_FF_B.Merge_k[0] - FOC_MTPA_FWC_FF_DW.Delay_DSTATE_l;

  /* Switch: '<S166>/Switch2' incorporates:
   *  RelationalOperator: '<S166>/LowerRelop1'
   */
  if (!(Abs > FOC_MTPA_FWC_FF_Y.Id_error)) {
    /* Product: '<S154>/delta fall limit' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  SampleTimeMath: '<S154>/sample time'
     *
     * About '<S154>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    FOC_MTPA_FWC_FF_Y.Id_error = 0.0001F *
      FOC_MTPA_FWC_FF_U.Rate_limiter.Id_ramp_down;

    /* Switch: '<S166>/Switch' incorporates:
     *  RelationalOperator: '<S166>/UpperRelop'
     */
    if (!(Abs < FOC_MTPA_FWC_FF_Y.Id_error)) {
      /* Product: '<S154>/delta fall limit' */
      FOC_MTPA_FWC_FF_Y.Id_error = Abs;
    }

    /* End of Switch: '<S166>/Switch' */
  }

  /* End of Switch: '<S166>/Switch2' */

  /* Sum: '<S154>/Difference Inputs2' incorporates:
   *  Delay: '<S154>/Delay'
   *
   * Block description for '<S154>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_MTPA_FWC_FF_DW.Delay_DSTATE_l += FOC_MTPA_FWC_FF_Y.Id_error;

  /* Switch: '<S156>/Switch2' incorporates:
   *  Inport: '<Root>/Id_Iq_MTPA_limit'
   *  RelationalOperator: '<S156>/LowerRelop1'
   *  RelationalOperator: '<S156>/UpperRelop'
   *  Switch: '<S156>/Switch'
   */
  if (FOC_MTPA_FWC_FF_DW.Delay_DSTATE_l >
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_up_limit) {
    /* Switch: '<S156>/Switch2' */
    FOC_MTPA_FWC_FF_Y.Id_ref_final =
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_up_limit;
  } else if (FOC_MTPA_FWC_FF_DW.Delay_DSTATE_l <
             FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_low_limit) {
    /* Switch: '<S156>/Switch2' incorporates:
     *  Switch: '<S156>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Id_ref_final =
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_low_limit;
  } else {
    /* Switch: '<S156>/Switch2' incorporates:
     *  Switch: '<S156>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Id_ref_final = FOC_MTPA_FWC_FF_DW.Delay_DSTATE_l;
  }

  /* End of Switch: '<S156>/Switch2' */

  /* Product: '<S154>/delta fall limit' incorporates:
   *  Sum: '<S29>/Sum3'
   */
  FOC_MTPA_FWC_FF_Y.Id_error = FOC_MTPA_FWC_FF_Y.Id_ref_final -
    FOC_MTPA_FWC_FF_Y.Id;

  /* Product: '<S124>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S116>/Filter'
   *  Product: '<S114>/DProd Out'
   *  Sum: '<S116>/SumD'
   */
  Abs = (FOC_MTPA_FWC_FF_Y.Id_error * FOC_MTPA_FWC_FF_B.Merge[2] -
         FOC_MTPA_FWC_FF_DW.Filter_DSTATE) * FOC_MTPA_FWC_FF_B.Merge[3];

  /* Sum: '<S131>/Sum' incorporates:
   *  DiscreteIntegrator: '<S121>/Integrator'
   *  Product: '<S126>/PProd Out'
   */
  rtb_V_qo = (FOC_MTPA_FWC_FF_Y.Id_error * FOC_MTPA_FWC_FF_B.Merge[0] +
              FOC_MTPA_FWC_FF_DW.Integrator_DSTATE) + Abs;

  /* Switch: '<S129>/Switch2' incorporates:
   *  RelationalOperator: '<S129>/LowerRelop1'
   *  RelationalOperator: '<S129>/UpperRelop'
   *  Switch: '<S129>/Switch'
   */
  if (rtb_V_qo > FOC_MTPA_FWC_FF_B.Merge[4]) {
    /* Switch: '<S129>/Switch2' */
    FOC_MTPA_FWC_FF_Y.Vd_PID = FOC_MTPA_FWC_FF_B.Merge[4];
  } else if (rtb_V_qo < FOC_MTPA_FWC_FF_B.Merge[5]) {
    /* Switch: '<S129>/Switch2' incorporates:
     *  Switch: '<S129>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Vd_PID = FOC_MTPA_FWC_FF_B.Merge[5];
  } else {
    /* Switch: '<S129>/Switch2' incorporates:
     *  Switch: '<S129>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Vd_PID = rtb_V_qo;
  }

  /* End of Switch: '<S129>/Switch2' */

  /* Gain: '<S7>/Gain' incorporates:
   *  Inport: '<Root>/Bus_Voltage'
   */
  rtb_DataTypeConversion1 = 0.577350259F * FOC_MTPA_FWC_FF_U.BusVoltage_V;

  /* Delay: '<S155>/Delay' */
  if (FOC_MTPA_FWC_FF_DW.icLoad_p) {
    /* Sum: '<S155>/Difference Inputs2'
     *
     * Block description for '<S155>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_MTPA_FWC_FF_DW.Delay_DSTATE_p = FOC_MTPA_FWC_FF_B.Merge_k[1];
  }

  /* Product: '<S155>/delta fall limit' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  Product: '<S155>/delta rise limit'
   *  SampleTimeMath: '<S155>/sample time'
   *
   * About '<S155>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  FOC_MTPA_FWC_FF_Y.Iq_ref_final = FOC_MTPA_FWC_FF_U.Rate_limiter.Iq_ramp_up *
    0.0001F;

  /* Sum: '<S155>/Difference Inputs1' incorporates:
   *  Delay: '<S155>/Delay'
   *
   * Block description for '<S155>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_UkYk1_j = FOC_MTPA_FWC_FF_B.Merge_k[1] - FOC_MTPA_FWC_FF_DW.Delay_DSTATE_p;

  /* Switch: '<S167>/Switch2' incorporates:
   *  RelationalOperator: '<S167>/LowerRelop1'
   */
  if (!(rtb_UkYk1_j > FOC_MTPA_FWC_FF_Y.Iq_ref_final)) {
    /* Product: '<S155>/delta fall limit' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  SampleTimeMath: '<S155>/sample time'
     *
     * About '<S155>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    FOC_MTPA_FWC_FF_Y.Iq_ref_final = 0.0001F *
      FOC_MTPA_FWC_FF_U.Rate_limiter.Iq_ramp_down;

    /* Switch: '<S167>/Switch' incorporates:
     *  RelationalOperator: '<S167>/UpperRelop'
     */
    if (!(rtb_UkYk1_j < FOC_MTPA_FWC_FF_Y.Iq_ref_final)) {
      /* Product: '<S155>/delta fall limit' */
      FOC_MTPA_FWC_FF_Y.Iq_ref_final = rtb_UkYk1_j;
    }

    /* End of Switch: '<S167>/Switch' */
  }

  /* End of Switch: '<S167>/Switch2' */

  /* Sum: '<S155>/Difference Inputs2' incorporates:
   *  Delay: '<S155>/Delay'
   *
   * Block description for '<S155>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_MTPA_FWC_FF_DW.Delay_DSTATE_p += FOC_MTPA_FWC_FF_Y.Iq_ref_final;

  /* Switch: '<S157>/Switch2' incorporates:
   *  Inport: '<Root>/Id_Iq_MTPA_limit'
   *  RelationalOperator: '<S157>/LowerRelop1'
   *  RelationalOperator: '<S157>/UpperRelop'
   *  Switch: '<S157>/Switch'
   */
  if (FOC_MTPA_FWC_FF_DW.Delay_DSTATE_p >
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_up_limit) {
    /* Product: '<S155>/delta fall limit' */
    FOC_MTPA_FWC_FF_Y.Iq_ref_final =
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_up_limit;
  } else if (FOC_MTPA_FWC_FF_DW.Delay_DSTATE_p <
             FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_low_limit) {
    /* Product: '<S155>/delta fall limit' incorporates:
     *  Switch: '<S157>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Iq_ref_final =
      FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_low_limit;
  } else {
    /* Product: '<S155>/delta fall limit' incorporates:
     *  Switch: '<S157>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Iq_ref_final = FOC_MTPA_FWC_FF_DW.Delay_DSTATE_p;
  }

  /* End of Switch: '<S157>/Switch2' */

  /* Gain: '<S25>/NegSign' incorporates:
   *  Delay: '<S10>/Lq_calc'
   *  Product: '<S25>/prod1'
   */
  rtb_UkYk1_j = -(FOC_MTPA_FWC_FF_DW.Lq_calc_DSTATE *
                  FOC_MTPA_FWC_FF_Y.Iq_ref_final * rtb_VqFF_unsat);

  /* Switch: '<S30>/Switch2' incorporates:
   *  RelationalOperator: '<S30>/LowerRelop1'
   *  RelationalOperator: '<S30>/UpperRelop'
   *  Switch: '<S30>/Switch'
   *  UnaryMinus: '<S25>/Unary Minus'
   */
  if (rtb_UkYk1_j > rtb_DataTypeConversion1) {
    rtb_UkYk1_j = rtb_DataTypeConversion1;
  } else if (rtb_UkYk1_j < -rtb_DataTypeConversion1) {
    /* Switch: '<S30>/Switch' incorporates:
     *  UnaryMinus: '<S25>/Unary Minus'
     */
    rtb_UkYk1_j = -rtb_DataTypeConversion1;
  }

  /* Sum: '<S7>/Add' incorporates:
   *  Switch: '<S30>/Switch2'
   */
  FOC_MTPA_FWC_FF_Y.Vd = FOC_MTPA_FWC_FF_Y.Vd_PID + rtb_UkYk1_j;

  /* Switch: '<S26>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S26>/LowerRelop1'
   *  RelationalOperator: '<S26>/UpperRelop'
   *  Switch: '<S26>/Switch'
   */
  if (FOC_MTPA_FWC_FF_Y.Vd > FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_flux_PID) {
    /* Sum: '<S7>/Add' */
    FOC_MTPA_FWC_FF_Y.Vd = FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_flux_PID;
  } else if (FOC_MTPA_FWC_FF_Y.Vd <
             FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_flux_PID) {
    /* Sum: '<S7>/Add' incorporates:
     *  Switch: '<S26>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Vd = FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_flux_PID;
  }

  /* End of Switch: '<S26>/Switch2' */

  /* Product: '<S25>/prod2' incorporates:
   *  Delay: '<S10>/Ld_calc'
   *  Inport: '<Root>/Motor_Parameters'
   *  Product: '<S25>/prod3'
   *  Sum: '<S25>/add1'
   */
  rtb_VqFF_unsat *= FOC_MTPA_FWC_FF_DW.Ld_calc_DSTATE *
    FOC_MTPA_FWC_FF_Y.Id_ref_final + FOC_MTPA_FWC_FF_U.Motor_Parameters.Lambda;

  /* Switch: '<S31>/Switch2' incorporates:
   *  RelationalOperator: '<S31>/LowerRelop1'
   */
  if (!(rtb_VqFF_unsat > rtb_DataTypeConversion1)) {
    /* Switch: '<S31>/Switch' incorporates:
     *  RelationalOperator: '<S31>/UpperRelop'
     *  UnaryMinus: '<S25>/Unary Minus'
     */
    if (rtb_VqFF_unsat < -rtb_DataTypeConversion1) {
      rtb_DataTypeConversion1 = -rtb_DataTypeConversion1;
    } else {
      rtb_DataTypeConversion1 = rtb_VqFF_unsat;
    }

    /* End of Switch: '<S31>/Switch' */
  }

  /* End of Switch: '<S31>/Switch2' */

  /* If: '<S4>/If2' */
  if (FOC_MTPA_FWC_FF_Y.PID_Switch) {
    /* Outputs for IfAction SubSystem: '<S4>/If Action Subsystem4' incorporates:
     *  ActionPort: '<S232>/Action Port'
     */
    /* SignalConversion generated from: '<S232>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge2'
     */
    FOC_MTPA_FWC_FF_B.Merge2[0] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA;

    /* SignalConversion generated from: '<S232>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge2'
     */
    FOC_MTPA_FWC_FF_B.Merge2[1] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Ki_torque_PID_MTPA;

    /* SignalConversion generated from: '<S232>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge2'
     */
    FOC_MTPA_FWC_FF_B.Merge2[2] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA;

    /* SignalConversion generated from: '<S232>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge2'
     */
    FOC_MTPA_FWC_FF_B.Merge2[3] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Filter_torque_PID_MTPA;

    /* SignalConversion generated from: '<S232>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge2'
     */
    FOC_MTPA_FWC_FF_B.Merge2[4] = FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_torque_PID;

    /* SignalConversion generated from: '<S232>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge2'
     */
    FOC_MTPA_FWC_FF_B.Merge2[5] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_torque_PID;

    /* End of Outputs for SubSystem: '<S4>/If Action Subsystem4' */
  } else {
    /* Outputs for IfAction SubSystem: '<S4>/If Action Subsystem5' incorporates:
     *  ActionPort: '<S233>/Action Port'
     */
    /* SignalConversion generated from: '<S233>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge2'
     */
    FOC_MTPA_FWC_FF_B.Merge2[0] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA_low;

    /* SignalConversion generated from: '<S233>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge2'
     */
    FOC_MTPA_FWC_FF_B.Merge2[1] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Ki_torque_PID_MTPA_low;

    /* SignalConversion generated from: '<S233>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge2'
     */
    FOC_MTPA_FWC_FF_B.Merge2[2] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA_low;

    /* SignalConversion generated from: '<S233>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge2'
     */
    FOC_MTPA_FWC_FF_B.Merge2[3] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Filter_torque_PID_MTPA_low;

    /* SignalConversion generated from: '<S233>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge2'
     */
    FOC_MTPA_FWC_FF_B.Merge2[4] = FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_torque_PID;

    /* SignalConversion generated from: '<S233>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge2'
     */
    FOC_MTPA_FWC_FF_B.Merge2[5] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_torque_PID;

    /* End of Outputs for SubSystem: '<S4>/If Action Subsystem5' */
  }

  /* End of If: '<S4>/If2' */

  /* Gain: '<S169>/Gain' incorporates:
   *  Sum: '<S28>/Sum2'
   */
  FOC_MTPA_FWC_FF_Y.Iq_error = FOC_MTPA_FWC_FF_Y.Iq_ref_final -
    FOC_MTPA_FWC_FF_Y.Iq;

  /* Product: '<S70>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S62>/Filter'
   *  Product: '<S60>/DProd Out'
   *  Sum: '<S62>/SumD'
   */
  rtb_VqFF_unsat = (FOC_MTPA_FWC_FF_Y.Iq_error * FOC_MTPA_FWC_FF_B.Merge2[2] -
                    FOC_MTPA_FWC_FF_DW.Filter_DSTATE_d) *
    FOC_MTPA_FWC_FF_B.Merge2[3];

  /* Sum: '<S77>/Sum' incorporates:
   *  DiscreteIntegrator: '<S67>/Integrator'
   *  Product: '<S72>/PProd Out'
   */
  rtb_UkYk1_j = (FOC_MTPA_FWC_FF_Y.Iq_error * FOC_MTPA_FWC_FF_B.Merge2[0] +
                 FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_h) + rtb_VqFF_unsat;

  /* Switch: '<S75>/Switch2' incorporates:
   *  RelationalOperator: '<S75>/LowerRelop1'
   *  RelationalOperator: '<S75>/UpperRelop'
   *  Switch: '<S75>/Switch'
   */
  if (rtb_UkYk1_j > FOC_MTPA_FWC_FF_B.Merge2[4]) {
    /* Gain: '<S170>/Gain' */
    FOC_MTPA_FWC_FF_Y.Vq_PID = FOC_MTPA_FWC_FF_B.Merge2[4];
  } else if (rtb_UkYk1_j < FOC_MTPA_FWC_FF_B.Merge2[5]) {
    /* Gain: '<S170>/Gain' incorporates:
     *  Switch: '<S75>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Vq_PID = FOC_MTPA_FWC_FF_B.Merge2[5];
  } else {
    /* Gain: '<S170>/Gain' incorporates:
     *  Switch: '<S75>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Vq_PID = rtb_UkYk1_j;
  }

  /* End of Switch: '<S75>/Switch2' */

  /* Sum: '<S7>/Add1' */
  FOC_MTPA_FWC_FF_Y.Vq = rtb_DataTypeConversion1 + FOC_MTPA_FWC_FF_Y.Vq_PID;

  /* Switch: '<S27>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S27>/LowerRelop1'
   *  RelationalOperator: '<S27>/UpperRelop'
   *  Switch: '<S27>/Switch'
   */
  if (FOC_MTPA_FWC_FF_Y.Vq > FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_torque_PID) {
    /* Sum: '<S7>/Add1' */
    FOC_MTPA_FWC_FF_Y.Vq = FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_torque_PID;
  } else if (FOC_MTPA_FWC_FF_Y.Vq <
             FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_torque_PID) {
    /* Sum: '<S7>/Add1' incorporates:
     *  Switch: '<S27>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Vq = FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_torque_PID;
  }

  /* End of Switch: '<S27>/Switch2' */

  /* Outputs for Atomic SubSystem: '<S141>/Two inputs CRL' */
  /* Switch: '<S145>/Switch' incorporates:
   *  Product: '<S144>/dcos'
   *  Product: '<S144>/qsin'
   *  Sum: '<S144>/sum_alpha'
   */
  rtb_Switch_f_idx_0 = FOC_MTPA_FWC_FF_Y.Vd * rtb_TrigonometricFunction1_tmp -
    FOC_MTPA_FWC_FF_Y.Vq * rtb_k;

  /* Gain: '<S143>/one_by_two' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S144>/a16'
   */
  rtb_add_c = 0.5F * rtb_Switch_f_idx_0;

  /* Gain: '<S143>/sqrt3_by_two' incorporates:
   *  Product: '<S144>/dsin'
   *  Product: '<S144>/qcos'
   *  Sum: '<S144>/sum_beta'
   */
  rtb_DataTypeConversion1 = (FOC_MTPA_FWC_FF_Y.Vq *
    rtb_TrigonometricFunction1_tmp + FOC_MTPA_FWC_FF_Y.Vd * rtb_k) *
    0.866025388F;

  /* End of Outputs for SubSystem: '<S141>/Two inputs CRL' */

  /* Sum: '<S143>/add_b' */
  rtb_k = rtb_DataTypeConversion1 - rtb_add_c;

  /* Sum: '<S143>/add_c' */
  rtb_add_c = (0.0F - rtb_add_c) - rtb_DataTypeConversion1;

  /* Outputs for Atomic SubSystem: '<S141>/Two inputs CRL' */
  /* Gain: '<S149>/one_by_two' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S144>/a16'
   *  MinMax: '<S149>/Max'
   *  MinMax: '<S149>/Min'
   *  Sum: '<S149>/Add'
   */
  rtb_DataTypeConversion1 = (fmaxf(fmaxf(rtb_Switch_f_idx_0, rtb_k), rtb_add_c)
    + fminf(fminf(rtb_Switch_f_idx_0, rtb_k), rtb_add_c)) * -0.5F;

  /* Outport: '<Root>/Va' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S144>/a16'
   *  Gain: '<S148>/Gain'
   *  Sum: '<S148>/Add3'
   */
  FOC_MTPA_FWC_FF_Y.Va = (rtb_Switch_f_idx_0 + rtb_DataTypeConversion1) *
    1.15470052F;

  /* End of Outputs for SubSystem: '<S141>/Two inputs CRL' */

  /* Outport: '<Root>/Vb' incorporates:
   *  Gain: '<S148>/Gain'
   *  Sum: '<S148>/Add1'
   */
  FOC_MTPA_FWC_FF_Y.Vb = (rtb_k + rtb_DataTypeConversion1) * 1.15470052F;

  /* Outport: '<Root>/Vc' incorporates:
   *  Gain: '<S148>/Gain'
   *  Sum: '<S148>/Add2'
   */
  FOC_MTPA_FWC_FF_Y.Vc = (rtb_DataTypeConversion1 + rtb_add_c) * 1.15470052F;

  /* Outport: '<Root>/Actual_torque_from_ref' incorporates:
   *  Constant: '<S9>/Constant'
   *  Inport: '<Root>/Motor_Parameters'
   *  Product: '<S9>/Product'
   *  Product: '<S9>/Product1'
   *  Product: '<S9>/Product2'
   *  Sum: '<S9>/Add'
   */
  FOC_MTPA_FWC_FF_Y.Actual_torque_from_ref = (float)
    ((FOC_MTPA_FWC_FF_Y.Id_ref_final * FOC_MTPA_FWC_FF_Y.Iq_ref_final *
      rtb_Product2_tmp + FOC_MTPA_FWC_FF_Y.Iq_ref_final *
      FOC_MTPA_FWC_FF_U.Motor_Parameters.Lambda) *
     FOC_MTPA_FWC_FF_U.Motor_Parameters.Pole_Pairs * 1.5);

  /* RateTransition generated from: '<S1>/Data Type Conversion1' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion1'
   *  Outport: '<Root>/Throttle_State'
   */
  if (tmp) {
    FOC_MTPA_FWC_FF_DW.TmpRTBAtDataTypeConversion1Outp = (float)
      FOC_MTPA_FWC_FF_Y.Throttle_State;
  }

  /* If: '<S4>/If1' */
  if (FOC_MTPA_FWC_FF_Y.PID_Switch) {
    /* Outputs for IfAction SubSystem: '<S4>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S230>/Action Port'
     */
    /* SignalConversion generated from: '<S230>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge1'
     */
    FOC_MTPA_FWC_FF_B.Merge1[0] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA;

    /* SignalConversion generated from: '<S230>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge1'
     */
    FOC_MTPA_FWC_FF_B.Merge1[1] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Ki_speed_PID_MTPA;

    /* SignalConversion generated from: '<S230>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge1'
     */
    FOC_MTPA_FWC_FF_B.Merge1[2] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA;

    /* SignalConversion generated from: '<S230>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge1'
     */
    FOC_MTPA_FWC_FF_B.Merge1[3] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Filter_speed_PID_MTPA;

    /* SignalConversion generated from: '<S230>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge1'
     */
    FOC_MTPA_FWC_FF_B.Merge1[4] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_speed_PID_MTPA;

    /* SignalConversion generated from: '<S230>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge1'
     */
    FOC_MTPA_FWC_FF_B.Merge1[5] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_speed_PID_MTPA;

    /* End of Outputs for SubSystem: '<S4>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S4>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S231>/Action Port'
     */
    /* SignalConversion generated from: '<S231>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge1'
     */
    FOC_MTPA_FWC_FF_B.Merge1[0] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA_low;

    /* SignalConversion generated from: '<S231>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge1'
     */
    FOC_MTPA_FWC_FF_B.Merge1[1] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Ki_speed_PID_MTPA_low;

    /* SignalConversion generated from: '<S231>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge1'
     */
    FOC_MTPA_FWC_FF_B.Merge1[2] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA_low;

    /* SignalConversion generated from: '<S231>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge1'
     */
    FOC_MTPA_FWC_FF_B.Merge1[3] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Filter_speed_PID_MTPA_low;

    /* SignalConversion generated from: '<S231>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge1'
     */
    FOC_MTPA_FWC_FF_B.Merge1[4] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_speed_PID_MTPA;

    /* SignalConversion generated from: '<S231>/Bus Selector' incorporates:
     *  Inport: '<Root>/MTPA_PID'
     *  Merge: '<S4>/Merge1'
     */
    FOC_MTPA_FWC_FF_B.Merge1[5] =
      FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_speed_PID_MTPA;

    /* End of Outputs for SubSystem: '<S4>/If Action Subsystem3' */
  }

  /* End of If: '<S4>/If1' */

  /* Outport: '<Root>/Lq' incorporates:
   *  Delay: '<S10>/Lq_calc'
   */
  FOC_MTPA_FWC_FF_Y.Lq = FOC_MTPA_FWC_FF_DW.Lq_calc_DSTATE;

  /* Outport: '<Root>/Ld' incorporates:
   *  Delay: '<S10>/Ld_calc'
   */
  FOC_MTPA_FWC_FF_Y.Ld = FOC_MTPA_FWC_FF_DW.Ld_calc_DSTATE;

  /* RateTransition generated from: '<S4>/Merge1' incorporates:
   *  Inport: '<Root>/Ref_Speed_mech_rpm'
   *  RateTransition generated from: '<S1>/Outer_Loop'
   */
  if (tmp) {
    for (i = 0; i < 6; i++) {
      FOC_MTPA_FWC_FF_DW.TmpRTBAtMerge1Outport1_Buffer[i] =
        FOC_MTPA_FWC_FF_B.Merge1[i];
    }

    FOC_MTPA_FWC_FF_DW.TmpRTBAtOuter_LoopInport1_Buffe =
      FOC_MTPA_FWC_FF_U.Ref_Speed_mech_rpm;

    /* RateTransition generated from: '<S1>/Outer_Loop' incorporates:
     *  Inport: '<Root>/Rate_limiter'
     *  Inport: '<Root>/Ref_Speed_mech_rpm'
     */
    FOC_MTPA_FWC_FF_DW.TmpRTBAtOuter_LoopInport3_Buffe =
      FOC_MTPA_FWC_FF_U.Rate_limiter;

    /* RateTransition generated from: '<S1>/Outer_Loop' incorporates:
     *  Inport: '<Root>/T_ref'
     */
    FOC_MTPA_FWC_FF_DW.TmpRTBAtOuter_LoopInport6_Buffe =
      FOC_MTPA_FWC_FF_U.RefTrq;

    /* RateTransition generated from: '<S1>/Outer_Loop' incorporates:
     *  Inport: '<Root>/Actual Speed_mech_rad//sec'
     */
    FOC_MTPA_FWC_FF_DW.wm_input_Buffer =
      FOC_MTPA_FWC_FF_U.ActualSpeed_mech_radsec;
  }

  /* Update for Delay: '<S10>/Ld_calc' */
  FOC_MTPA_FWC_FF_DW.icLoad = false;

  /* Product: '<S169>/alpha' incorporates:
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   *  Inport: '<Root>/Motor_Parameters'
   *  Product: '<S2>/Product3'
   *  Sum: '<S169>/Subtract1'
   *  Sum: '<S169>/Subtract2'
   */
  rtb_Product2_tmp = (FOC_MTPA_FWC_FF_U.ActualSpeed_mech_radsec *
                      FOC_MTPA_FWC_FF_Y.Actual_torque_from_meas -
                      FOC_MTPA_FWC_FF_U.Motor_Parameters.Motor_P_lim_Watts) /
    (FOC_MTPA_FWC_FF_U.Motor_Parameters.Motor_P_Max_Watts -
     FOC_MTPA_FWC_FF_U.Motor_Parameters.Motor_P_lim_Watts);

  /* Saturate: '<S169>/Saturation' */
  if (rtb_Product2_tmp > 1.0F) {
    /* Saturate: '<S170>/Saturation' */
    rtb_Product2_tmp = 1.0F;
  } else if (rtb_Product2_tmp < 0.0F) {
    /* Saturate: '<S170>/Saturation' */
    rtb_Product2_tmp = 0.0F;
  }

  /* Update for Delay: '<S10>/Ld_calc' incorporates:
   *  Constant: '<S169>/Constant'
   *  Gain: '<S169>/Gain'
   *  Inport: '<Root>/Motor_Parameters'
   *  Product: '<S10>/Product1'
   *  Product: '<S169>/Product'
   *  Saturate: '<S169>/Saturation'
   *  Sum: '<S169>/k'
   */
  FOC_MTPA_FWC_FF_DW.Ld_calc_DSTATE = (1.0F - 0.01F *
    FOC_MTPA_FWC_FF_U.Motor_Parameters.Ld_Percentage * rtb_Product2_tmp) *
    FOC_MTPA_FWC_FF_U.Motor_Parameters.Ld;

  /* Update for Delay: '<S10>/Lq_calc' incorporates:
   *  Constant: '<S170>/Constant'
   *  Gain: '<S170>/Gain'
   *  Inport: '<Root>/Motor_Parameters'
   *  Product: '<S10>/Product2'
   *  Product: '<S170>/Product'
   *  Sum: '<S170>/k'
   */
  FOC_MTPA_FWC_FF_DW.icLoad_o = false;
  FOC_MTPA_FWC_FF_DW.Lq_calc_DSTATE = (1.0F - 0.01F *
    FOC_MTPA_FWC_FF_U.Motor_Parameters.Lq_Percentage * rtb_Product2_tmp) *
    FOC_MTPA_FWC_FF_U.Motor_Parameters.Lq;

  /* Update for Delay: '<S235>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad_e = false;
  FOC_MTPA_FWC_FF_DW.Delay_DSTATE = FOC_MTPA_FWC_FF_Y.T_ref_FNR;

  /* Update for Delay: '<S154>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad_l = false;

  /* Update for DiscreteIntegrator: '<S121>/Integrator' incorporates:
   *  Product: '<S118>/IProd Out'
   *  Sum: '<S113>/SumI2'
   *  Sum: '<S113>/SumI4'
   */
  FOC_MTPA_FWC_FF_DW.Integrator_DSTATE += ((FOC_MTPA_FWC_FF_Y.Vd_PID - rtb_V_qo) * can_d.canId_PID.Back_Kaw
    + FOC_MTPA_FWC_FF_Y.Id_error * FOC_MTPA_FWC_FF_B.Merge[1]) * 0.0001F;
  if (FOC_MTPA_FWC_FF_DW.Integrator_DSTATE > d.Vmax_SVM) {
    FOC_MTPA_FWC_FF_DW.Integrator_DSTATE = d.Vmax_SVM;
  } else if (FOC_MTPA_FWC_FF_DW.Integrator_DSTATE < -d.Vmax_SVM) {
    FOC_MTPA_FWC_FF_DW.Integrator_DSTATE = -d.Vmax_SVM;
  }

  /* End of Update for DiscreteIntegrator: '<S121>/Integrator' */

  /* Update for DiscreteIntegrator: '<S116>/Filter' */
  FOC_MTPA_FWC_FF_DW.Filter_DSTATE += 0.0001F * Abs;

  /* Update for Delay: '<S155>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad_p = false;

  /* Update for DiscreteIntegrator: '<S67>/Integrator' incorporates:
   *  Product: '<S64>/IProd Out'
   *  Sum: '<S59>/SumI2'
   *  Sum: '<S59>/SumI4'
   */
  FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_h += ((FOC_MTPA_FWC_FF_Y.Vq_PID -
    rtb_UkYk1_j) * can_d.canIq_PID.Back_Kaw + FOC_MTPA_FWC_FF_Y.Iq_error * FOC_MTPA_FWC_FF_B.Merge2[1]) *
    0.0001F;
  if (FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_h > d.Vmax_SVM) {
    FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_h = d.Vmax_SVM;
  } else if (FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_h < -d.Vmax_SVM) {
    FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_h = -d.Vmax_SVM;
  }

  /* End of Update for DiscreteIntegrator: '<S67>/Integrator' */

  /* Update for DiscreteIntegrator: '<S62>/Filter' */
  FOC_MTPA_FWC_FF_DW.Filter_DSTATE_d += 0.0001F * rtb_VqFF_unsat;
}

/* Model step function for TID1 */
void FOC_MTPA_FWC_FF_step1(void)       /* Sample time: [0.001s, 0.0s] */
{
  float tmp;
  float rtb_Sum_j;
  float rtb_UkYk1_b;
  float rtb_deltafalllimit_j;

  /* Outputs for Atomic SubSystem: '<S1>/Outer_Loop' */
  /* Delay: '<S171>/Delay' */
  if (FOC_MTPA_FWC_FF_DW.icLoad_k) {
    /* Sum: '<S171>/Difference Inputs2' incorporates:
     *  Constant: '<S171>/Constant'
     *
     * Block description for '<S171>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_MTPA_FWC_FF_DW.Delay_DSTATE_c = 0.0F;
  }

  /* Product: '<S171>/delta rise limit' incorporates:
   *  RateTransition generated from: '<S1>/Outer_Loop'
   *  SampleTimeMath: '<S171>/sample time'
   *
   * About '<S171>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_deltafalllimit_j =
    FOC_MTPA_FWC_FF_DW.TmpRTBAtOuter_LoopInport3_Buffe.Ref_Speed_rate_up *
    0.001F;

  /* Switch: '<S3>/FNR_speed_Switch' incorporates:
   *  Constant: '<S3>/Constant'
   *  RateTransition generated from: '<S1>/Data Type Conversion1'
   *  RateTransition generated from: '<S1>/Outer_Loop'
   */
  if (FOC_MTPA_FWC_FF_DW.TmpRTBAtDataTypeConversion1Outp > 2.0F) {
    tmp = 0.0;
  } else {
    tmp = FOC_MTPA_FWC_FF_DW.TmpRTBAtOuter_LoopInport1_Buffe;
  }

  /* Sum: '<S171>/Difference Inputs1' incorporates:
   *  Delay: '<S171>/Delay'
   *  Switch: '<S3>/FNR_speed_Switch'
   *
   * Block description for '<S171>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_UkYk1_b = (float)(tmp - FOC_MTPA_FWC_FF_DW.Delay_DSTATE_c);

  /* Switch: '<S173>/Switch2' incorporates:
   *  RelationalOperator: '<S173>/LowerRelop1'
   */
  if (!(rtb_UkYk1_b > rtb_deltafalllimit_j)) {
    /* Switch: '<S3>/Speed_rate_limiter_switch' incorporates:
     *  RateTransition generated from: '<S1>/Data Type Conversion1'
     *  RateTransition generated from: '<S1>/Outer_Loop'
     */
    if (FOC_MTPA_FWC_FF_DW.TmpRTBAtDataTypeConversion1Outp > 2.0F) {
      rtb_deltafalllimit_j =
        FOC_MTPA_FWC_FF_DW.TmpRTBAtOuter_LoopInport3_Buffe.Ref_Speed_rate_down_neutral;
    } else {
      rtb_deltafalllimit_j =
        FOC_MTPA_FWC_FF_DW.TmpRTBAtOuter_LoopInport3_Buffe.Ref_Speed_rate_down;
    }

    /* Product: '<S171>/delta fall limit' incorporates:
     *  SampleTimeMath: '<S171>/sample time'
     *  Switch: '<S3>/Speed_rate_limiter_switch'
     *
     * About '<S171>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_deltafalllimit_j *= 0.001F;

    /* Switch: '<S173>/Switch' incorporates:
     *  RelationalOperator: '<S173>/UpperRelop'
     */
    if (!(rtb_UkYk1_b < rtb_deltafalllimit_j)) {
      rtb_deltafalllimit_j = rtb_UkYk1_b;
    }

    /* End of Switch: '<S173>/Switch' */
  }

  /* End of Switch: '<S173>/Switch2' */

  /* Sum: '<S171>/Difference Inputs2' incorporates:
   *  Delay: '<S171>/Delay'
   *
   * Block description for '<S171>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_MTPA_FWC_FF_DW.Delay_DSTATE_c += rtb_deltafalllimit_j;

  /* Sum: '<S172>/Subtract' incorporates:
   *  Abs: '<S3>/Abs'
   *  Gain: '<S3>/rpm to Rad//sec'
   *  RateTransition generated from: '<S1>/Outer_Loop'
   */
  FOC_MTPA_FWC_FF_Y.Speed_error = 0.104719758F *
    FOC_MTPA_FWC_FF_DW.Delay_DSTATE_c - fabsf(FOC_MTPA_FWC_FF_DW.wm_input_Buffer);

  /* Product: '<S212>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S204>/Filter'
   *  Product: '<S202>/DProd Out'
   *  RateTransition generated from: '<S4>/Merge1'
   *  Sum: '<S204>/SumD'
   */
  rtb_deltafalllimit_j = (FOC_MTPA_FWC_FF_Y.Speed_error *
    FOC_MTPA_FWC_FF_DW.TmpRTBAtMerge1Outport1_Buffer[2] -
    FOC_MTPA_FWC_FF_DW.Filter_DSTATE_c) *
    FOC_MTPA_FWC_FF_DW.TmpRTBAtMerge1Outport1_Buffer[3];

  /* Sum: '<S219>/Sum' incorporates:
   *  DiscreteIntegrator: '<S209>/Integrator'
   *  Product: '<S214>/PProd Out'
   *  RateTransition generated from: '<S4>/Merge1'
   */
  rtb_Sum_j = (FOC_MTPA_FWC_FF_Y.Speed_error *
               FOC_MTPA_FWC_FF_DW.TmpRTBAtMerge1Outport1_Buffer[0] +
               FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_g) + rtb_deltafalllimit_j;

  /* Switch: '<S217>/Switch2' incorporates:
   *  RateTransition generated from: '<S4>/Merge1'
   *  RelationalOperator: '<S217>/LowerRelop1'
   *  RelationalOperator: '<S217>/UpperRelop'
   *  Switch: '<S217>/Switch'
   */
  if (rtb_Sum_j > FOC_MTPA_FWC_FF_DW.TmpRTBAtMerge1Outport1_Buffer[4]) {
    /* Switch: '<S217>/Switch2' */
    FOC_MTPA_FWC_FF_Y.Iq_gen = FOC_MTPA_FWC_FF_DW.TmpRTBAtMerge1Outport1_Buffer
      [4];
  } else if (rtb_Sum_j < FOC_MTPA_FWC_FF_DW.TmpRTBAtMerge1Outport1_Buffer[5]) {
    /* Switch: '<S217>/Switch2' incorporates:
     *  Switch: '<S217>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Iq_gen = FOC_MTPA_FWC_FF_DW.TmpRTBAtMerge1Outport1_Buffer
      [5];
  } else {
    /* Switch: '<S217>/Switch2' incorporates:
     *  Switch: '<S217>/Switch'
     */
    FOC_MTPA_FWC_FF_Y.Iq_gen = rtb_Sum_j;
  }

  /* End of Switch: '<S217>/Switch2' */

  /* Switch: '<S3>/Speed_Torque_switch' incorporates:
   *  Inport: '<Root>/Iq_Torque_ratio'
   *  Inport: '<Root>/Speed_1_Torque_0'
   *  Product: '<S3>/Product1'
   *  RateTransition generated from: '<S1>/Data Type Conversion1'
   *  RateTransition generated from: '<S1>/Outer_Loop'
   *  Switch: '<S3>/Switch2'
   */
  if (FOC_MTPA_FWC_FF_U.Speed_1_Torque_0) {
    rtb_UkYk1_b = FOC_MTPA_FWC_FF_Y.Iq_gen * FOC_MTPA_FWC_FF_U.Iq_Torque_ratio;
  } else if (FOC_MTPA_FWC_FF_DW.TmpRTBAtDataTypeConversion1Outp > 2.0F) {
    /* Switch: '<S3>/Switch2' incorporates:
     *  Constant: '<S3>/Constant1'
     */
    rtb_UkYk1_b = 0.0F;
  } else {
    rtb_UkYk1_b = FOC_MTPA_FWC_FF_DW.TmpRTBAtOuter_LoopInport6_Buffe;
  }

  /* End of Switch: '<S3>/Speed_Torque_switch' */

  /* Update for Delay: '<S171>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad_k = false;

  /* Update for DiscreteIntegrator: '<S209>/Integrator' incorporates:
   *  Product: '<S206>/IProd Out'
   *  RateTransition generated from: '<S4>/Merge1'
   *  Sum: '<S201>/SumI2'
   *  Sum: '<S201>/SumI4'
   */
  FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_g += ((FOC_MTPA_FWC_FF_Y.Iq_gen -
    rtb_Sum_j) * can_d.canSpeed_PID.Back_Kaw + FOC_MTPA_FWC_FF_Y.Speed_error *
    FOC_MTPA_FWC_FF_DW.TmpRTBAtMerge1Outport1_Buffer[1]) * 0.001F;
  if (FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_g > MOTOR_PEAK_AC) {
    FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_g = MOTOR_PEAK_AC;
  } else if (FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_g < -MOTOR_PEAK_AC) {
    FOC_MTPA_FWC_FF_DW.Integrator_DSTATE_g = -MOTOR_PEAK_AC;
  }

  /* End of Update for DiscreteIntegrator: '<S209>/Integrator' */

  /* Update for DiscreteIntegrator: '<S204>/Filter' */
  FOC_MTPA_FWC_FF_DW.Filter_DSTATE_c += 0.001F * rtb_deltafalllimit_j;

  /* End of Outputs for SubSystem: '<S1>/Outer_Loop' */

  /* Outport: '<Root>/Ref_speed_out_RPM' */
  FOC_MTPA_FWC_FF_Y.Ref_speed_out_RPM = FOC_MTPA_FWC_FF_DW.Delay_DSTATE_c;

  /* RateTransition: '<S1>/Rate Transition' */
  FOC_MTPA_FWC_FF_DW.RateTransition_Buffer0 = rtb_UkYk1_b;
}

/* Model initialize function */
void FOC_MTPA_FWC_FF_initialize(void)
{
  /* Registration code */

  /* external outputs */
  FOC_MTPA_FWC_FF_Y.Throttle_State = Forward;

  /* InitializeConditions for Delay: '<S10>/Ld_calc' */
  FOC_MTPA_FWC_FF_DW.icLoad = true;

  /* InitializeConditions for Delay: '<S10>/Lq_calc' */
  FOC_MTPA_FWC_FF_DW.icLoad_o = true;

  /* InitializeConditions for Delay: '<S235>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad_e = true;

  /* InitializeConditions for Delay: '<S154>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad_l = true;

  /* InitializeConditions for Delay: '<S155>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad_p = true;

  /* SystemInitialize for IfAction SubSystem: '<S9>/If Action Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S159>/Discrete-Time Integrator' */
  FOC_MTPA_FWC_FF_DW.DiscreteTimeIntegrator_DSTATE = 1.0F;
  FOC_MTPA_FWC_FF_DW.DiscreteTimeIntegrator_PrevRese = 2;

  /* End of SystemInitialize for SubSystem: '<S9>/If Action Subsystem1' */

  /* SystemInitialize for Atomic SubSystem: '<S1>/Outer_Loop' */
  /* InitializeConditions for Delay: '<S171>/Delay' */
  FOC_MTPA_FWC_FF_DW.icLoad_k = true;

  FOC_MTPA_FWC_FF_U.BusVoltage_V = OP_VOLTAGE;
  FOC_MTPA_FWC_FF_U.Iq_Torque_ratio = CURR_TORQUE_RATIO;
  FOC_MTPA_FWC_FF_U.Motor_Parameters.Pole_Pairs = POLEPAIRS;
  FOC_MTPA_FWC_FF_U.Motor_Parameters.Rs = RS;
  FOC_MTPA_FWC_FF_U.Motor_Parameters.Lambda = can_d.can_Lambda;
  FOC_MTPA_FWC_FF_U.Motor_Parameters.Ld = can_d.can_Ld;
  FOC_MTPA_FWC_FF_U.Motor_Parameters.Lq = can_d.can_Lq;
  FOC_MTPA_FWC_FF_U.Motor_Parameters.Motor_P_lim_Watts = MIN_POWER;
  FOC_MTPA_FWC_FF_U.Motor_Parameters.Motor_P_Max_Watts = MAX_POWER;
  FOC_MTPA_FWC_FF_U.Motor_Parameters.Ld_Percentage = LD_PERCENTAGE_CHANGE;
  FOC_MTPA_FWC_FF_U.Motor_Parameters.Lq_Percentage = LQ_PERCENTAGE_CHANGE;

  FOC_MTPA_FWC_FF_U.Is_max = MOTOR_PEAK_AC;
  FOC_MTPA_FWC_FF_U.RPM_min_limit = MIN_RPM_CHANGE_LIM;

  FOC_MTPA_FWC_FF_U.FWC_values.M2F_factor = can_d.canFW_params.M_to_F;
  FOC_MTPA_FWC_FF_U.FWC_values.F2M_factor = can_d.canFW_params.F_to_M;
  FOC_MTPA_FWC_FF_U.FWC_values.FW_Int_reset_factor = can_d.canFW_params.Rst_Factor;
  FOC_MTPA_FWC_FF_U.FWC_values.Kaw = can_d.canFW_params.Kaw;
  FOC_MTPA_FWC_FF_U.FWC_values.Kfw = can_d.canFW_params.Kfw;

  /* Regen Settings */
  FOC_MTPA_FWC_FF_U.Regen.max_Regen_Torque = REGEN_MAX_TORQUE;
  FOC_MTPA_FWC_FF_U.Regen.regen_cap_rpm = REGEN_CAP_RPM;
  FOC_MTPA_FWC_FF_U.Regen.RPM_Regen_min_Speed = REGEN_MIN_RPM_EN;
  FOC_MTPA_FWC_FF_U.Regen.Polarity_switch = REGEN_POLARITY;
  FOC_MTPA_FWC_FF_U.Regen.Regen_Active = REGEN_ACTIVE_STATE;

  /* Low Speed PID Switch settings */
  FOC_MTPA_FWC_FF_U.MTPA_PID.Selection.Speed_RPM_limit = LOW_SPEED_TO_HIGH_SPEED_SWITCH_RPM;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Selection.I_limit = LOW_SPEED_I_LIMIT;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Selection.T_limit = LOW_SPEED_T_LIMIT;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Selection.I_0_T_1_switch = LOW_SPEED_I_T_SWITCH;

  /* Throttle Settings */
  FOC_MTPA_FWC_FF_U.Throttle_input.Max_Output_Value = SPORTS_MAX_SPEED;
  FOC_MTPA_FWC_FF_U.Throttle_input.Max_Throttle_Voltage = THR_MAX_VAL;
  FOC_MTPA_FWC_FF_U.Throttle_input.Min_Throttle_Voltage = THR_MIN_VAL;
  FOC_MTPA_FWC_FF_U.Throttle_input.Throttle_V_Hyst_band_FNR_shift = THR_HYS_BAND;

   /* Id Iq Limits */
  FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_up_limit = 560.0f;
  FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Iq_low_limit = -560.0f;
  FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_up_limit = 560.0f;
  FOC_MTPA_FWC_FF_U.Id_Iq_MTPA_limit.Id_low_limit = -560.0f;
  
  /* Speed Ref Rate Limiter Settings */
  FOC_MTPA_FWC_FF_U.Rate_limiter.Ref_Speed_rate_up = 10.0f * 10000.0f;
  FOC_MTPA_FWC_FF_U.Rate_limiter.Ref_Speed_rate_down = -50.0f * 10000.0f;
  FOC_MTPA_FWC_FF_U.Rate_limiter.Ref_Speed_rate_down_neutral = -60.0f * 10000.0f;

  /* Rate Limiter Settings */
  FOC_MTPA_FWC_FF_U.Rate_limiter.Torque_gen_ramp_up = 1.0f * 10000.0f;
  FOC_MTPA_FWC_FF_U.Rate_limiter.Torque_gen_ramp_down = -1.0f * 10000.0f;
  FOC_MTPA_FWC_FF_U.Rate_limiter.Iq_ramp_up = 50.0f * 10000.0f;
  FOC_MTPA_FWC_FF_U.Rate_limiter.Iq_ramp_down = -50.0f * 10000.0f;
  FOC_MTPA_FWC_FF_U.Rate_limiter.Id_ramp_up = 50.0f * 10000.0f;
  FOC_MTPA_FWC_FF_U.Rate_limiter.Id_ramp_down = -50.0f * 10000.0f;

  /* Speed PID Values */
  FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_speed_PID_MTPA = can_d.canSpeed_PID.Output_Up_Limit;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_speed_PID_MTPA = can_d.canSpeed_PID.Output_Low_Limit;
  /* High Speed PID Values */
  FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA = can_d.canSpeed_PID.Kp;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Ki_speed_PID_MTPA = can_d.canSpeed_PID.Ki;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA = can_d.canSpeed_PID.Kd;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Filter_speed_PID_MTPA = can_d.canSpeed_PID.Kd_Filter;
  /* Low Speed PID Values */
  FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA_low = can_d.canSpeed_PID.Kp * LOW_SPEED_SCALING;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Ki_speed_PID_MTPA_low = can_d.canSpeed_PID.Ki * LOW_SPEED_SCALING;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA_low = can_d.canSpeed_PID.Kd;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Filter_speed_PID_MTPA_low = can_d.canSpeed_PID.Kd_Filter;

  /* Iq PID Values */
  FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_torque_PID = can_d.canIq_PID.Output_Up_Limit;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_torque_PID = can_d.canIq_PID.Output_Low_Limit;
  /* High Speed PID Values */
  FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA = can_d.canIq_PID.Kp;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Ki_torque_PID_MTPA = can_d.canIq_PID.Ki;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA = can_d.canId_PID.Kd;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Filter_torque_PID_MTPA = can_d.canIq_PID.Kd_Filter;
  /* Low Speed PID Values */
  FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA_low = can_d.canIq_PID.Kp * LOW_SPEED_SCALING;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Ki_torque_PID_MTPA_low = can_d.canIq_PID.Ki * LOW_SPEED_SCALING;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA_low = can_d.canId_PID.Kd;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Filter_torque_PID_MTPA_low = can_d.canIq_PID.Kd_Filter;

  /* Id PID Values */
  FOC_MTPA_FWC_FF_U.MTPA_PID.Up_Limit_flux_PID = can_d.canId_PID.Output_Up_Limit;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Low_Limit_flux_PID = can_d.canId_PID.Output_Low_Limit;
  /* High Speed PID Values */
  FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA = can_d.canId_PID.Kp;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Ki_flux_PID_MTPA = can_d.canId_PID.Ki;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Kd_flux_PID_MTPA = can_d.canId_PID.Kd;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Filter_flux_PID_MTPA = can_d.canId_PID.Kd_Filter;
  /* Low Speed PID Values */
  FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA_low = can_d.canId_PID.Kp * LOW_SPEED_SCALING;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Ki_flux_PID_MTPA_low = can_d.canId_PID.Ki * LOW_SPEED_SCALING;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Kd_flux_PID_MTPA_low = can_d.canId_PID.Kd;
  FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Filter_flux_PID_MTPA_low = can_d.canId_PID.Kd_Filter;

  /* IIR Filter Coefficients */
  FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Id_Filter_switch = 1;
  FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Iq_Filter_switch = 1;
  FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Id_Filter_coefficient = 0.9f;
  FOC_MTPA_FWC_FF_U.IIR_Filter_Coefficient.Iq_Filter_coefficient = 0.9f; 

  FOC_MTPA_FWC_FF_U.RefTrq = 0.0f;
  FOC_MTPA_FWC_FF_U.Ref_Speed_mech_rpm = 0.0f;
  /* End of SystemInitialize for SubSystem: '<S1>/Outer_Loop' */

  /* SystemInitialize for Outport: '<Root>/Throttle_State' incorporates:
   *  Chart: '<S5>/FNR_switching'
   */
  FOC_MTPA_FWC_FF_Y.Throttle_State = Forward;
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
