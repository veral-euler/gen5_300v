/*
 * File: FOC_Basic_FF.c
 *
 * Code generated for Simulink model 'FOC_Basic_FF'.
 *
 * Model version                  : 18.284
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Jan 29 14:01:39 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_Basic_FF.h"
#include <stdint.h>
#include <math.h>
#include "FOC_Basic_FF_types.h"

/* Named constants for Chart: '<S3>/Protection_States' */
#define FOC_Basic_FF_IN_CurrentSafe    ((uint8_t)1U)
#define FOC_Basic_FF_IN_HighTempError  ((uint8_t)1U)
#define FOC_Basic_FF_IN_HighTempWarning ((uint8_t)2U)
#define FOC_Basic_FF_IN_OC_Error       ((uint8_t)2U)
#define FOC_Basic_FF_IN_OC_Warning     ((uint8_t)3U)
#define FOC_Basic_FF_IN_OV_Error       ((uint8_t)1U)
#define FOC_Basic_FF_IN_OV_Warning     ((uint8_t)2U)
#define FOC_Basic_FF_IN_TempSafe       ((uint8_t)3U)
#define FOC_Basic_FF_IN_UV_Error       ((uint8_t)3U)
#define FOC_Basic_FF_IN_UV_Warning     ((uint8_t)4U)
#define FOC_Basic_FF_IN_VoltageSafe    ((uint8_t)5U)

/* Block states (default storage) */
DW_FOC_Basic_FF_T FOC_Basic_FF_DW;

/* External inputs (root inport signals with default storage) */
ExtU_FOC_Basic_FF_T FOC_Basic_FF_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_FOC_Basic_FF_T FOC_Basic_FF_Y;

/* Real-time model */
static RT_MODEL_FOC_Basic_FF_T FOC_Basic_FF_M_;
RT_MODEL_FOC_Basic_FF_T *const FOC_Basic_FF_M = &FOC_Basic_FF_M_;

/* Forward declaration for local functions */
static void FOC_Basic_FF_VoltageProtection(void);

/* Function for Chart: '<S3>/Protection_States' */
static void FOC_Basic_FF_VoltageProtection(void)
{
  switch (FOC_Basic_FF_DW.is_VoltageProtection) {
   case FOC_Basic_FF_IN_OV_Error:
    /* Outport: '<Root>/VoltageFlag' */
    FOC_Basic_FF_Y.VoltageFlag = OV_Error;
    if (FOC_Basic_FF_DW.durationCounter_1_m > 1000U) {
      FOC_Basic_FF_DW.durationCounter_2_c0 = 0U;
      FOC_Basic_FF_DW.durationCounter_1_h = 0U;
      FOC_Basic_FF_DW.is_VoltageProtection = FOC_Basic_FF_IN_VoltageSafe;

      /* Outport: '<Root>/VoltageFlag' */
      FOC_Basic_FF_Y.VoltageFlag = SafeVoltage;
    } else if (FOC_Basic_FF_DW.durationCounter_2_d > 1000U) {
      FOC_Basic_FF_DW.durationCounter_2_bq = 0U;
      FOC_Basic_FF_DW.durationCounter_1_f = 0U;
      FOC_Basic_FF_DW.is_VoltageProtection = FOC_Basic_FF_IN_OV_Warning;

      /* Outport: '<Root>/VoltageFlag' */
      FOC_Basic_FF_Y.VoltageFlag = OV_Warning;
    }
    break;

   case FOC_Basic_FF_IN_OV_Warning:
    /* Outport: '<Root>/VoltageFlag' */
    FOC_Basic_FF_Y.VoltageFlag = OV_Warning;
    FOC_Basic_FF_DW.durationCounter_2_bq = 0U;
    if (FOC_Basic_FF_DW.durationCounter_1_f > 1000U) {
      FOC_Basic_FF_DW.durationCounter_2_c0 = 0U;
      FOC_Basic_FF_DW.durationCounter_1_h = 0U;
      FOC_Basic_FF_DW.is_VoltageProtection = FOC_Basic_FF_IN_VoltageSafe;

      /* Outport: '<Root>/VoltageFlag' */
      FOC_Basic_FF_Y.VoltageFlag = SafeVoltage;
    }
    break;

   case FOC_Basic_FF_IN_UV_Error:
    /* Outport: '<Root>/VoltageFlag' */
    FOC_Basic_FF_Y.VoltageFlag = UV_Error;

    /* Inport: '<Root>/Bus_Voltage' */
    /* Inport: '<Root>/Bus_Voltage' */
    if (!(FOC_Basic_FF_U.BusVoltage_V > -80.0F)) {
      FOC_Basic_FF_DW.durationCounter_1_e3 = 0U;
    }

    if (FOC_Basic_FF_DW.durationCounter_1_e3 > 1000U) {
      FOC_Basic_FF_DW.durationCounter_2_k = 0U;
      FOC_Basic_FF_DW.durationCounter_1_o = 0U;
      FOC_Basic_FF_DW.is_VoltageProtection = FOC_Basic_FF_IN_UV_Warning;

      /* Outport: '<Root>/VoltageFlag' */
      FOC_Basic_FF_Y.VoltageFlag = UV_Warning;
    } else {
      if (!(FOC_Basic_FF_U.BusVoltage_V > -60.0F)) {
        FOC_Basic_FF_DW.durationCounter_2_n = 0U;
      }

      if (FOC_Basic_FF_DW.durationCounter_2_n > 1000U) {
        FOC_Basic_FF_DW.durationCounter_2_c0 = 0U;
        FOC_Basic_FF_DW.durationCounter_1_h = 0U;
        FOC_Basic_FF_DW.is_VoltageProtection = FOC_Basic_FF_IN_VoltageSafe;

        /* Outport: '<Root>/VoltageFlag' */
        FOC_Basic_FF_Y.VoltageFlag = SafeVoltage;
      }
    }
    break;

   case FOC_Basic_FF_IN_UV_Warning:
    /* Outport: '<Root>/VoltageFlag' */
    FOC_Basic_FF_Y.VoltageFlag = UV_Warning;

    /* Inport: '<Root>/Bus_Voltage' */
    /* Inport: '<Root>/Bus_Voltage' */
    if (!(FOC_Basic_FF_U.BusVoltage_V < -80.0F)) {
      FOC_Basic_FF_DW.durationCounter_1_o = 0U;
    }

    if (FOC_Basic_FF_DW.durationCounter_1_o > 1000U) {
      FOC_Basic_FF_DW.durationCounter_2_n = 0U;
      FOC_Basic_FF_DW.durationCounter_1_e3 = 0U;
      FOC_Basic_FF_DW.is_VoltageProtection = FOC_Basic_FF_IN_UV_Error;

      /* Outport: '<Root>/VoltageFlag' */
      FOC_Basic_FF_Y.VoltageFlag = UV_Error;
    } else {
      if (!(FOC_Basic_FF_U.BusVoltage_V > -60.0F)) {
        FOC_Basic_FF_DW.durationCounter_2_k = 0U;
      }

      if (FOC_Basic_FF_DW.durationCounter_2_k > 1000U) {
        FOC_Basic_FF_DW.durationCounter_2_c0 = 0U;
        FOC_Basic_FF_DW.durationCounter_1_h = 0U;
        FOC_Basic_FF_DW.is_VoltageProtection = FOC_Basic_FF_IN_VoltageSafe;

        /* Outport: '<Root>/VoltageFlag' */
        FOC_Basic_FF_Y.VoltageFlag = SafeVoltage;
      }
    }
    break;

   default:
    /* Outport: '<Root>/VoltageFlag' */
    /* case IN_VoltageSafe: */
    FOC_Basic_FF_Y.VoltageFlag = SafeVoltage;
    FOC_Basic_FF_DW.durationCounter_2_c0 = 0U;

    /* Inport: '<Root>/Bus_Voltage' */
    if (!(FOC_Basic_FF_U.BusVoltage_V < -60.0F)) {
      FOC_Basic_FF_DW.durationCounter_1_h = 0U;
    }

    if (FOC_Basic_FF_DW.durationCounter_1_h > 1000U) {
      FOC_Basic_FF_DW.durationCounter_2_k = 0U;
      FOC_Basic_FF_DW.durationCounter_1_o = 0U;
      FOC_Basic_FF_DW.is_VoltageProtection = FOC_Basic_FF_IN_UV_Warning;

      /* Outport: '<Root>/VoltageFlag' */
      FOC_Basic_FF_Y.VoltageFlag = UV_Warning;
    }
    break;
  }
}

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

  /* Switch: '<S131>/Switch2' incorporates:
   *  DataTypeConversion: '<S28>/Data Type Conversion4'
   *  Inport: '<Root>/MTPA_PID'
   */
  FOC_Basic_FF_Y.Vd_PID = FOC_Basic_FF_U.MTPA_PID.Up_Limit_flux_PID;

  /* Outputs for Atomic SubSystem: '<S14>/Two phase CRL wrap' */
  /* Gain: '<S15>/one_by_sqrt3' incorporates:
   *  Inport: '<Root>/Phase Current'
   *  Sum: '<S15>/a_plus_2b'
   */
  rtb_Switch2_d = ((FOC_Basic_FF_U.PhaseCurrent[0] +
                    FOC_Basic_FF_U.PhaseCurrent[1]) +
                   FOC_Basic_FF_U.PhaseCurrent[1]) * 0.57735026918962584;

  /* End of Outputs for SubSystem: '<S14>/Two phase CRL wrap' */

  /* Trigonometry: '<S5>/Trigonometric Function' incorporates:
   *  Inport: '<Root>/angle'
   *  Trigonometry: '<S7>/Trigonometric Function1'
   */
  rtb_Add3 = sin(FOC_Basic_FF_U.MtrElcPos);

  /* Trigonometry: '<S5>/Trigonometric Function1' incorporates:
   *  Inport: '<Root>/angle'
   *  Trigonometry: '<S7>/Trigonometric Function'
   */
  rtb_Add1_l = cos(FOC_Basic_FF_U.MtrElcPos);

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
   *  Trigonometry: '<S5>/Trigonometric Function'
   *  Trigonometry: '<S5>/Trigonometric Function1'
   */
  rtb_algDD_o1_d = (float)(FOC_Basic_FF_U.PhaseCurrent[0] * rtb_Add1_l +
    rtb_Switch2_d * rtb_Add3);
  rtb_algDD_o2_o = (float)(rtb_Switch2_d * rtb_Add1_l -
    FOC_Basic_FF_U.PhaseCurrent[0] * rtb_Add3);

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
  FOC_Basic_FF_DW.UnitDelay_DSTATE = (1.0F -
    FOC_Basic_FF_U.IIR_Filter_Coefficient.Id_Filter_coefficient) *
    FOC_Basic_FF_DW.UnitDelay_DSTATE + rtb_algDD_o1_d *
    FOC_Basic_FF_U.IIR_Filter_Coefficient.Id_Filter_coefficient;

  /* Switch: '<S5>/Switch' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   *  UnitDelay: '<S18>/Unit Delay'
   */
  if (FOC_Basic_FF_U.IIR_Filter_Coefficient.Id_Filter_switch > 0.0F) {
    rtb_Gain_j = FOC_Basic_FF_DW.UnitDelay_DSTATE;
  } else {
    rtb_Gain_j = rtb_algDD_o1_d;
  }

  /* Sum: '<S28>/Sum3' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion'
   *  Inport: '<Root>/Id_ref_in'
   *  Switch: '<S5>/Switch'
   */
  FOC_Basic_FF_Y.Id_error = FOC_Basic_FF_U.Id_ref_in - rtb_Gain_j;

  /* Product: '<S126>/NProd Out' incorporates:
   *  DataTypeConversion: '<S28>/Data Type Conversion2'
   *  DataTypeConversion: '<S28>/Data Type Conversion3'
   *  DiscreteIntegrator: '<S118>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S116>/DProd Out'
   *  Sum: '<S118>/SumD'
   */
  rtb_Switch2_d = (FOC_Basic_FF_Y.Id_error *
                   FOC_Basic_FF_U.MTPA_PID.Flux_PID_MTPA.Kd_flux_PID_MTPA -
                   FOC_Basic_FF_DW.Filter_DSTATE) *
    FOC_Basic_FF_U.MTPA_PID.Flux_PID_MTPA.Filter_flux_PID_MTPA;

  /* Sum: '<S133>/Sum' incorporates:
   *  DataTypeConversion: '<S28>/Data Type Conversion'
   *  DiscreteIntegrator: '<S123>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S128>/PProd Out'
   */
  rtb_Sum = (FOC_Basic_FF_Y.Id_error *
             FOC_Basic_FF_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA +
             FOC_Basic_FF_DW.Integrator_DSTATE) + rtb_Switch2_d;

  /* Switch: '<S131>/Switch2' incorporates:
   *  DataTypeConversion: '<S28>/Data Type Conversion4'
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S131>/LowerRelop1'
   */
  if (!(rtb_Sum > FOC_Basic_FF_U.MTPA_PID.Up_Limit_flux_PID)) {
    /* Switch: '<S131>/Switch' incorporates:
     *  DataTypeConversion: '<S28>/Data Type Conversion5'
     *  RelationalOperator: '<S131>/UpperRelop'
     */
    if (rtb_Sum < FOC_Basic_FF_U.MTPA_PID.Low_Limit_flux_PID) {
      /* Switch: '<S131>/Switch2' */
      FOC_Basic_FF_Y.Vd_PID = FOC_Basic_FF_U.MTPA_PID.Low_Limit_flux_PID;
    } else {
      /* Switch: '<S131>/Switch2' */
      FOC_Basic_FF_Y.Vd_PID = rtb_Sum;
    }

    /* End of Switch: '<S131>/Switch' */
  }

  /* End of Switch: '<S131>/Switch2' */

  /* Gain: '<S6>/Gain' incorporates:
   *  Inport: '<Root>/Bus_Voltage'
   */
  rtb_Gain_j = 0.577350259F * FOC_Basic_FF_U.BusVoltage_V;

  /* RateTransition: '<S2>/Rate Transition' */
  if (FOC_Basic_FF_M->Timing.RateInteraction.TID0_1 == 1) {
    /* Outport: '<Root>/Iq_ref' */
    FOC_Basic_FF_Y.Iq_ref = FOC_Basic_FF_DW.RateTransition_Buffer0;
  }

  /* End of RateTransition: '<S2>/Rate Transition' */

  /* Switch: '<S77>/Switch2' incorporates:
   *  Gain: '<S30>/wm_pu2si_mech2elec'
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   */
  FOC_Basic_FF_Y.Vq_PID = 3.0 * FOC_Basic_FF_U.MtrSpd;

  /* Gain: '<S30>/NegSign' incorporates:
   *  Inport: '<Root>/Lq'
   *  Outport: '<Root>/Iq_ref'
   *  Product: '<S30>/prod1'
   */
  rtb_VdFF_unsat = -(FOC_Basic_FF_U.Lq * FOC_Basic_FF_Y.Iq_ref *
                     FOC_Basic_FF_Y.Vq_PID);

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

  /* Sum: '<S6>/Add' incorporates:
   *  Switch: '<S32>/Switch2'
   */
  FOC_Basic_FF_Y.Vd = FOC_Basic_FF_Y.Vd_PID + rtb_VdFF_unsat;

  /* Switch: '<S25>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S25>/LowerRelop1'
   *  RelationalOperator: '<S25>/UpperRelop'
   *  Switch: '<S25>/Switch'
   */
  if (FOC_Basic_FF_Y.Vd > FOC_Basic_FF_U.MTPA_PID.Up_Limit_flux_PID) {
    /* Sum: '<S6>/Add' incorporates:
     *  DataTypeConversion: '<S28>/Data Type Conversion4'
     */
    FOC_Basic_FF_Y.Vd = FOC_Basic_FF_U.MTPA_PID.Up_Limit_flux_PID;
  } else if (FOC_Basic_FF_Y.Vd < FOC_Basic_FF_U.MTPA_PID.Low_Limit_flux_PID) {
    /* Sum: '<S6>/Add' incorporates:
     *  Switch: '<S25>/Switch'
     */
    FOC_Basic_FF_Y.Vd = FOC_Basic_FF_U.MTPA_PID.Low_Limit_flux_PID;
  }

  /* End of Switch: '<S25>/Switch2' */

  /* Product: '<S30>/prod2' incorporates:
   *  Inport: '<Root>/Id_ref_in'
   *  Inport: '<Root>/Lambda'
   *  Inport: '<Root>/Ld'
   *  Product: '<S30>/prod3'
   *  Sum: '<S30>/add1'
   */
  rtb_VqFF_unsat = (FOC_Basic_FF_U.Ld * FOC_Basic_FF_U.Id_ref_in +
                    FOC_Basic_FF_U.Lambda) * FOC_Basic_FF_Y.Vq_PID;

  /* Switch: '<S77>/Switch2' incorporates:
   *  DataTypeConversion: '<S27>/Data Type Conversion10'
   *  Inport: '<Root>/MTPA_PID'
   */
  FOC_Basic_FF_Y.Vq_PID = FOC_Basic_FF_U.MTPA_PID.Up_Limit_torque_PID;

  /* Sum: '<S21>/Add1' incorporates:
   *  Constant: '<S12>/One'
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   *  Product: '<S21>/Product'
   *  Product: '<S21>/Product1'
   *  Sum: '<S12>/Sum'
   *  Switch: '<S12>/Switch1'
   *  UnitDelay: '<S21>/Unit Delay'
   */
  FOC_Basic_FF_DW.UnitDelay_DSTATE_f = (1.0F -
    FOC_Basic_FF_U.IIR_Filter_Coefficient.Iq_Filter_coefficient) *
    FOC_Basic_FF_DW.UnitDelay_DSTATE_f + rtb_algDD_o2_o *
    FOC_Basic_FF_U.IIR_Filter_Coefficient.Iq_Filter_coefficient;

  /* Switch: '<S5>/Switch1' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   */
  if (FOC_Basic_FF_U.IIR_Filter_Coefficient.Iq_Filter_switch > 0.0F) {
    rtb_algDD_o2_o = FOC_Basic_FF_DW.UnitDelay_DSTATE_f;
  }

  /* End of Switch: '<S5>/Switch1' */

  /* Sum: '<S27>/Sum2' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion1'
   *  Outport: '<Root>/Iq_ref'
   */
  FOC_Basic_FF_Y.Iq_error = FOC_Basic_FF_Y.Iq_ref - rtb_algDD_o2_o;

  /* Product: '<S72>/NProd Out' incorporates:
   *  DataTypeConversion: '<S27>/Data Type Conversion8'
   *  DataTypeConversion: '<S27>/Data Type Conversion9'
   *  DiscreteIntegrator: '<S64>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S62>/DProd Out'
   *  Sum: '<S64>/SumD'
   */
  rtb_VdFF_unsat = (FOC_Basic_FF_Y.Iq_error *
                    FOC_Basic_FF_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA -
                    FOC_Basic_FF_DW.Filter_DSTATE_d) *
    FOC_Basic_FF_U.MTPA_PID.Torque_PID_MTPA.Filter_torque_PID_MTPA;

  /* Sum: '<S79>/Sum' incorporates:
   *  DataTypeConversion: '<S27>/Data Type Conversion6'
   *  DiscreteIntegrator: '<S69>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S74>/PProd Out'
   */
  rtb_Sum_f = (FOC_Basic_FF_Y.Iq_error *
               FOC_Basic_FF_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA +
               FOC_Basic_FF_DW.Integrator_DSTATE_h) + rtb_VdFF_unsat;

  /* Switch: '<S77>/Switch2' incorporates:
   *  DataTypeConversion: '<S27>/Data Type Conversion10'
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S77>/LowerRelop1'
   */
  if (!(rtb_Sum_f > FOC_Basic_FF_U.MTPA_PID.Up_Limit_torque_PID)) {
    /* Switch: '<S77>/Switch' incorporates:
     *  DataTypeConversion: '<S27>/Data Type Conversion11'
     *  RelationalOperator: '<S77>/UpperRelop'
     */
    if (rtb_Sum_f < FOC_Basic_FF_U.MTPA_PID.Low_Limit_torque_PID) {
      /* Switch: '<S77>/Switch2' */
      FOC_Basic_FF_Y.Vq_PID = FOC_Basic_FF_U.MTPA_PID.Low_Limit_torque_PID;
    } else {
      /* Switch: '<S77>/Switch2' */
      FOC_Basic_FF_Y.Vq_PID = rtb_Sum_f;
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

  /* Sum: '<S6>/Add1' incorporates:
   *  Switch: '<S33>/Switch2'
   */
  FOC_Basic_FF_Y.Vq = rtb_VqFF_unsat + FOC_Basic_FF_Y.Vq_PID;

  /* Switch: '<S26>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S26>/LowerRelop1'
   *  RelationalOperator: '<S26>/UpperRelop'
   *  Switch: '<S26>/Switch'
   */
  if (FOC_Basic_FF_Y.Vq > FOC_Basic_FF_U.MTPA_PID.Up_Limit_torque_PID) {
    /* Sum: '<S6>/Add1' incorporates:
     *  DataTypeConversion: '<S27>/Data Type Conversion10'
     */
    FOC_Basic_FF_Y.Vq = FOC_Basic_FF_U.MTPA_PID.Up_Limit_torque_PID;
  } else if (FOC_Basic_FF_Y.Vq < FOC_Basic_FF_U.MTPA_PID.Low_Limit_torque_PID) {
    /* Sum: '<S6>/Add1' incorporates:
     *  Switch: '<S26>/Switch'
     */
    FOC_Basic_FF_Y.Vq = FOC_Basic_FF_U.MTPA_PID.Low_Limit_torque_PID;
  }

  /* End of Switch: '<S26>/Switch2' */

  /* Outputs for Atomic SubSystem: '<S143>/Two inputs CRL' */
  /* Switch: '<S147>/Switch' incorporates:
   *  Product: '<S146>/dcos'
   *  Product: '<S146>/qsin'
   *  Sum: '<S146>/sum_alpha'
   */
  rtb_Switch_f_idx_0 = FOC_Basic_FF_Y.Vd * rtb_Add1_l - FOC_Basic_FF_Y.Vq *
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
  rtb_Add3 = (FOC_Basic_FF_Y.Vq * rtb_Add1_l + FOC_Basic_FF_Y.Vd * rtb_Add3) *
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

  /* MinMax: '<S3>/Max1' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S146>/a16'
   *  Gain: '<S150>/Gain'
   *  Sum: '<S150>/Add1'
   *  Sum: '<S150>/Add2'
   *  Sum: '<S150>/Add3'
   */
  FOC_Basic_FF_Y.Va = (rtb_Switch_f_idx_0 + rtb_Add3) * 1.1547005383792517;

  /* End of Outputs for SubSystem: '<S143>/Two inputs CRL' */
  FOC_Basic_FF_Y.Vb = (rtb_Add1_l + rtb_Add3) * 1.1547005383792517;
  FOC_Basic_FF_Y.Vc = (rtb_Add3 + rtb_VqFF_unsat) * 1.1547005383792517;

  /* MinMax: '<S3>/Max2' incorporates:
   *  Inport: '<Root>/MCTemperature_C'
   *  Inport: '<Root>/MotorTemperature_C'
   */
  rtb_Gain_j = fmaxf(FOC_Basic_FF_U.MCTemperature_C,
                     FOC_Basic_FF_U.MotorTemperature_C);

  /* MinMax: '<S3>/Max' incorporates:
   *  Inport: '<Root>/Phase Current'
   */
  rtb_Add3 = fmax(fmax(FOC_Basic_FF_U.PhaseCurrent[0],
                       FOC_Basic_FF_U.PhaseCurrent[1]),
                  FOC_Basic_FF_U.PhaseCurrent[2]);

  /* Chart: '<S3>/Protection_States' incorporates:
   *  Inport: '<Root>/Bus_Voltage'
   */
  if (FOC_Basic_FF_DW.is_active_c7_FOC_Basic_FF == 0) {
    FOC_Basic_FF_DW.is_active_c7_FOC_Basic_FF = 1U;
    FOC_Basic_FF_DW.durationCounter_1 = 0U;
    FOC_Basic_FF_DW.is_TemperatureProtection = FOC_Basic_FF_IN_TempSafe;

    /* Outport: '<Root>/TempFlag' */
    FOC_Basic_FF_Y.TempFlag = SafeTemperature;
    FOC_Basic_FF_DW.durationCounter_1_h = 0U;
    FOC_Basic_FF_DW.is_VoltageProtection = FOC_Basic_FF_IN_VoltageSafe;

    /* Outport: '<Root>/VoltageFlag' */
    FOC_Basic_FF_Y.VoltageFlag = SafeVoltage;
    FOC_Basic_FF_DW.durationCounter_1_i = 0U;
    FOC_Basic_FF_DW.is_CurrentProtection = FOC_Basic_FF_IN_CurrentSafe;

    /* Outport: '<Root>/CurrentFlag' */
    FOC_Basic_FF_Y.CurrentFlag = SafeCurrent;
  } else {
    switch (FOC_Basic_FF_DW.is_TemperatureProtection) {
     case FOC_Basic_FF_IN_HighTempError:
      /* Outport: '<Root>/TempFlag' */
      FOC_Basic_FF_Y.TempFlag = OT_Error;
      if (!(rtb_Gain_j < 80.0F)) {
        FOC_Basic_FF_DW.durationCounter_1_c = 0U;
      }

      if (FOC_Basic_FF_DW.durationCounter_1_c > 1000U) {
        FOC_Basic_FF_DW.durationCounter_1 = 0U;
        FOC_Basic_FF_DW.is_TemperatureProtection = FOC_Basic_FF_IN_TempSafe;

        /* Outport: '<Root>/TempFlag' */
        FOC_Basic_FF_Y.TempFlag = SafeTemperature;
      } else {
        if (!(rtb_Gain_j < 100.0F)) {
          FOC_Basic_FF_DW.durationCounter_2 = 0U;
        }

        if (FOC_Basic_FF_DW.durationCounter_2 > 1000U) {
          FOC_Basic_FF_DW.durationCounter_2_e = 0U;
          FOC_Basic_FF_DW.durationCounter_1_e = 0U;
          FOC_Basic_FF_DW.is_TemperatureProtection =
            FOC_Basic_FF_IN_HighTempWarning;

          /* Outport: '<Root>/TempFlag' */
          FOC_Basic_FF_Y.TempFlag = OT_Warning;
        }
      }
      break;

     case FOC_Basic_FF_IN_HighTempWarning:
      /* Outport: '<Root>/TempFlag' */
      FOC_Basic_FF_Y.TempFlag = OT_Warning;
      if (!(rtb_Gain_j > 100.0F)) {
        FOC_Basic_FF_DW.durationCounter_2_e = 0U;
      }

      if (FOC_Basic_FF_DW.durationCounter_2_e > 1000U) {
        FOC_Basic_FF_DW.durationCounter_2 = 0U;
        FOC_Basic_FF_DW.durationCounter_1_c = 0U;
        FOC_Basic_FF_DW.is_TemperatureProtection = FOC_Basic_FF_IN_HighTempError;

        /* Outport: '<Root>/TempFlag' */
        FOC_Basic_FF_Y.TempFlag = OT_Error;
      } else {
        if (!(rtb_Gain_j < 80.0F)) {
          FOC_Basic_FF_DW.durationCounter_1_e = 0U;
        }

        if (FOC_Basic_FF_DW.durationCounter_1_e > 1000U) {
          FOC_Basic_FF_DW.durationCounter_1 = 0U;
          FOC_Basic_FF_DW.is_TemperatureProtection = FOC_Basic_FF_IN_TempSafe;

          /* Outport: '<Root>/TempFlag' */
          FOC_Basic_FF_Y.TempFlag = SafeTemperature;
        }
      }
      break;

     default:
      /* Outport: '<Root>/TempFlag' */
      /* case IN_TempSafe: */
      FOC_Basic_FF_Y.TempFlag = SafeTemperature;
      if (!(rtb_Gain_j > 80.0F)) {
        FOC_Basic_FF_DW.durationCounter_1 = 0U;
      }

      if (FOC_Basic_FF_DW.durationCounter_1 > 1000U) {
        FOC_Basic_FF_DW.durationCounter_2_e = 0U;
        FOC_Basic_FF_DW.durationCounter_1_e = 0U;
        FOC_Basic_FF_DW.is_TemperatureProtection =
          FOC_Basic_FF_IN_HighTempWarning;

        /* Outport: '<Root>/TempFlag' */
        FOC_Basic_FF_Y.TempFlag = OT_Warning;
      }
      break;
    }

    FOC_Basic_FF_VoltageProtection();
    switch (FOC_Basic_FF_DW.is_CurrentProtection) {
     case FOC_Basic_FF_IN_CurrentSafe:
      /* Outport: '<Root>/CurrentFlag' */
      FOC_Basic_FF_Y.CurrentFlag = SafeCurrent;
      if (!(rtb_Add3 > 300.0)) {
        FOC_Basic_FF_DW.durationCounter_1_i = 0U;
      }

      if (FOC_Basic_FF_DW.durationCounter_1_i > 1000U) {
        FOC_Basic_FF_DW.durationCounter_2_c = 0U;
        FOC_Basic_FF_DW.durationCounter_1_d = 0U;
        FOC_Basic_FF_DW.is_CurrentProtection = FOC_Basic_FF_IN_OC_Warning;

        /* Outport: '<Root>/CurrentFlag' */
        FOC_Basic_FF_Y.CurrentFlag = OC_Warning;
      }
      break;

     case FOC_Basic_FF_IN_OC_Error:
      /* Outport: '<Root>/CurrentFlag' */
      FOC_Basic_FF_Y.CurrentFlag = OC_Error;
      if (!(rtb_Add3 < 300.0)) {
        FOC_Basic_FF_DW.durationCounter_1_a = 0U;
      }

      if (FOC_Basic_FF_DW.durationCounter_1_a > 1000U) {
        FOC_Basic_FF_DW.durationCounter_1_i = 0U;
        FOC_Basic_FF_DW.is_CurrentProtection = FOC_Basic_FF_IN_CurrentSafe;

        /* Outport: '<Root>/CurrentFlag' */
        FOC_Basic_FF_Y.CurrentFlag = SafeCurrent;
      } else {
        if (!(rtb_Add3 < 350.0)) {
          FOC_Basic_FF_DW.durationCounter_2_b = 0U;
        }

        if (FOC_Basic_FF_DW.durationCounter_2_b > 1000U) {
          FOC_Basic_FF_DW.durationCounter_2_c = 0U;
          FOC_Basic_FF_DW.durationCounter_1_d = 0U;
          FOC_Basic_FF_DW.is_CurrentProtection = FOC_Basic_FF_IN_OC_Warning;

          /* Outport: '<Root>/CurrentFlag' */
          FOC_Basic_FF_Y.CurrentFlag = OC_Warning;
        }
      }
      break;

     default:
      /* Outport: '<Root>/CurrentFlag' */
      /* case IN_OC_Warning: */
      FOC_Basic_FF_Y.CurrentFlag = OC_Warning;
      if (!(rtb_Add3 > 350.0)) {
        FOC_Basic_FF_DW.durationCounter_2_c = 0U;
      }

      if (FOC_Basic_FF_DW.durationCounter_2_c > 1000U) {
        FOC_Basic_FF_DW.durationCounter_2_b = 0U;
        FOC_Basic_FF_DW.durationCounter_1_a = 0U;
        FOC_Basic_FF_DW.is_CurrentProtection = FOC_Basic_FF_IN_OC_Error;

        /* Outport: '<Root>/CurrentFlag' */
        FOC_Basic_FF_Y.CurrentFlag = OC_Error;
      } else {
        if (!(rtb_Add3 < 300.0)) {
          FOC_Basic_FF_DW.durationCounter_1_d = 0U;
        }

        if (FOC_Basic_FF_DW.durationCounter_1_d > 1000U) {
          FOC_Basic_FF_DW.durationCounter_1_i = 0U;
          FOC_Basic_FF_DW.is_CurrentProtection = FOC_Basic_FF_IN_CurrentSafe;

          /* Outport: '<Root>/CurrentFlag' */
          FOC_Basic_FF_Y.CurrentFlag = SafeCurrent;
        }
      }
      break;
    }
  }

  if (rtb_Gain_j > 80.0F) {
    FOC_Basic_FF_DW.durationCounter_1++;
  } else {
    FOC_Basic_FF_DW.durationCounter_1 = 0U;
  }

  if (rtb_Gain_j < 80.0F) {
    FOC_Basic_FF_DW.durationCounter_1_c++;
    FOC_Basic_FF_DW.durationCounter_1_e++;
  } else {
    FOC_Basic_FF_DW.durationCounter_1_c = 0U;
    FOC_Basic_FF_DW.durationCounter_1_e = 0U;
  }

  if (rtb_Gain_j < 100.0F) {
    FOC_Basic_FF_DW.durationCounter_2++;
  } else {
    FOC_Basic_FF_DW.durationCounter_2 = 0U;
  }

  if (rtb_Gain_j > 100.0F) {
    FOC_Basic_FF_DW.durationCounter_2_e++;
  } else {
    FOC_Basic_FF_DW.durationCounter_2_e = 0U;
  }

  if (rtb_Add3 > 300.0) {
    FOC_Basic_FF_DW.durationCounter_1_i++;
  } else {
    FOC_Basic_FF_DW.durationCounter_1_i = 0U;
  }

  if (rtb_Add3 < 300.0) {
    FOC_Basic_FF_DW.durationCounter_1_a++;
    FOC_Basic_FF_DW.durationCounter_1_d++;
  } else {
    FOC_Basic_FF_DW.durationCounter_1_a = 0U;
    FOC_Basic_FF_DW.durationCounter_1_d = 0U;
  }

  if (rtb_Add3 < 350.0) {
    FOC_Basic_FF_DW.durationCounter_2_b++;
  } else {
    FOC_Basic_FF_DW.durationCounter_2_b = 0U;
  }

  if (rtb_Add3 > 350.0) {
    FOC_Basic_FF_DW.durationCounter_2_c++;
  } else {
    FOC_Basic_FF_DW.durationCounter_2_c = 0U;
  }

  if (FOC_Basic_FF_U.BusVoltage_V > -80.0F) {
    FOC_Basic_FF_DW.durationCounter_1_e3++;
  } else {
    FOC_Basic_FF_DW.durationCounter_1_e3 = 0U;
  }

  if (FOC_Basic_FF_U.BusVoltage_V < -80.0F) {
    FOC_Basic_FF_DW.durationCounter_1_o++;
  } else {
    FOC_Basic_FF_DW.durationCounter_1_o = 0U;
  }

  if (FOC_Basic_FF_U.BusVoltage_V < -60.0F) {
    FOC_Basic_FF_DW.durationCounter_1_h++;
  } else {
    FOC_Basic_FF_DW.durationCounter_1_h = 0U;
  }

  if (FOC_Basic_FF_U.BusVoltage_V > -60.0F) {
    FOC_Basic_FF_DW.durationCounter_2_k++;
    FOC_Basic_FF_DW.durationCounter_2_n++;
  } else {
    FOC_Basic_FF_DW.durationCounter_2_k = 0U;
    FOC_Basic_FF_DW.durationCounter_2_n = 0U;
  }

  FOC_Basic_FF_DW.durationCounter_2_c0 = 0U;
  FOC_Basic_FF_DW.durationCounter_1_m++;
  FOC_Basic_FF_DW.durationCounter_1_f++;
  FOC_Basic_FF_DW.durationCounter_2_d++;
  FOC_Basic_FF_DW.durationCounter_2_bq = 0U;

  /* End of Chart: '<S3>/Protection_States' */

  /* Outport: '<Root>/Iq' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion1'
   */
  FOC_Basic_FF_Y.Iq = rtb_algDD_o2_o;

  /* Switch: '<S5>/Switch' incorporates:
   *  Inport: '<Root>/IIR_Filter_Coefficient'
   */
  if (FOC_Basic_FF_U.IIR_Filter_Coefficient.Id_Filter_switch > 0.0F) {
    /* Outport: '<Root>/Id' incorporates:
     *  UnitDelay: '<S18>/Unit Delay'
     */
    FOC_Basic_FF_Y.Id = FOC_Basic_FF_DW.UnitDelay_DSTATE;
  } else {
    /* Outport: '<Root>/Id' */
    FOC_Basic_FF_Y.Id = rtb_algDD_o1_d;
  }

  /* Product: '<S4>/delta rise limit' incorporates:
   *  Inport: '<Root>/Ref_Speed_rate_up'
   *  SampleTimeMath: '<S4>/sample time'
   *
   * About '<S4>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_Add3 = FOC_Basic_FF_U.Ref_Speed_rate_up * 0.0001;

  /* Delay: '<S4>/Delay' */
  if (FOC_Basic_FF_DW.icLoad) {
    /* Sum: '<S4>/Difference Inputs2' incorporates:
     *  Inport: '<Root>/Ref_Speed_mech_rpm'
     *
     * Block description for '<S4>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_Basic_FF_DW.Delay_DSTATE = FOC_Basic_FF_U.Ref_Speed_mech_rpm;
  }

  /* Sum: '<S4>/Difference Inputs1' incorporates:
   *  Delay: '<S4>/Delay'
   *  Inport: '<Root>/Ref_Speed_mech_rpm'
   *
   * Block description for '<S4>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_VqFF_unsat = FOC_Basic_FF_U.Ref_Speed_mech_rpm -
    FOC_Basic_FF_DW.Delay_DSTATE;

  /* Switch: '<S209>/Switch2' incorporates:
   *  RelationalOperator: '<S209>/LowerRelop1'
   */
  if (!(rtb_VqFF_unsat > rtb_Add3)) {
    /* Product: '<S4>/delta fall limit' incorporates:
     *  Inport: '<Root>/Ref_Speed_rate_down'
     *  SampleTimeMath: '<S4>/sample time'
     *
     * About '<S4>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_Add3 = 0.0001 * FOC_Basic_FF_U.Ref_Speed_rate_down;

    /* Switch: '<S209>/Switch' incorporates:
     *  RelationalOperator: '<S209>/UpperRelop'
     */
    if (!(rtb_VqFF_unsat < rtb_Add3)) {
      rtb_Add3 = rtb_VqFF_unsat;
    }

    /* End of Switch: '<S209>/Switch' */
  }

  /* End of Switch: '<S209>/Switch2' */

  /* Sum: '<S4>/Difference Inputs2' incorporates:
   *  Delay: '<S4>/Delay'
   *
   * Block description for '<S4>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_Basic_FF_DW.Delay_DSTATE += rtb_Add3;

  /* Outport: '<Root>/Speed_error' incorporates:
   *  Gain: '<S1>/rpm to Rad//sec'
   *  Inport: '<Root>/Actual Speed_mech_rad//sec'
   *  Sum: '<S9>/Subtract'
   */
  FOC_Basic_FF_Y.Speed_error = 0.10471975511965977 *
    FOC_Basic_FF_DW.Delay_DSTATE - FOC_Basic_FF_U.MtrSpd;

  /* Outport: '<Root>/Id_ref' incorporates:
   *  Inport: '<Root>/Id_ref_in'
   */
  FOC_Basic_FF_Y.Id_ref = FOC_Basic_FF_U.Id_ref_in;

  /* Update for DiscreteIntegrator: '<S123>/Integrator' incorporates:
   *  DataTypeConversion: '<S28>/Data Type Conversion1'
   *  Inport: '<Root>/MTPA_PID'
   *  Product: '<S120>/IProd Out'
   *  Sum: '<S115>/SumI2'
   *  Sum: '<S115>/SumI4'
   *  Sum: '<S135>/SumI3'
   *  Sum: '<S136>/SumI1'
   */
  FOC_Basic_FF_DW.Integrator_DSTATE += ((FOC_Basic_FF_Y.Id_error *
    FOC_Basic_FF_U.MTPA_PID.Flux_PID_MTPA.Ki_flux_PID_MTPA +
    (FOC_Basic_FF_Y.Vd_PID - FOC_Basic_FF_Y.Vd_PID)) + (FOC_Basic_FF_Y.Vd_PID -
    rtb_Sum)) * 0.0001;
  if (FOC_Basic_FF_DW.Integrator_DSTATE > SVM_VOLTAGE_LIMIT) {
    FOC_Basic_FF_DW.Integrator_DSTATE = SVM_VOLTAGE_LIMIT;
  } else if (FOC_Basic_FF_DW.Integrator_DSTATE < -SVM_VOLTAGE_LIMIT) {
    FOC_Basic_FF_DW.Integrator_DSTATE = -SVM_VOLTAGE_LIMIT;
  }

  /* End of Update for DiscreteIntegrator: '<S123>/Integrator' */

  /* Update for DiscreteIntegrator: '<S118>/Filter' */
  FOC_Basic_FF_DW.Filter_DSTATE += 0.0001 * rtb_Switch2_d;

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
  FOC_Basic_FF_DW.Integrator_DSTATE_h += (((FOC_Basic_FF_Y.Vq_PID -
    FOC_Basic_FF_Y.Vq_PID) * -10.0 + FOC_Basic_FF_Y.Iq_error *
    FOC_Basic_FF_U.MTPA_PID.Torque_PID_MTPA.Ki_torque_PID_MTPA) +
    (FOC_Basic_FF_Y.Vq_PID - rtb_Sum_f)) * 0.0001;
  if (FOC_Basic_FF_DW.Integrator_DSTATE_h > SVM_VOLTAGE_LIMIT) {
    FOC_Basic_FF_DW.Integrator_DSTATE_h = SVM_VOLTAGE_LIMIT;
  } else if (FOC_Basic_FF_DW.Integrator_DSTATE_h < -SVM_VOLTAGE_LIMIT) {
    FOC_Basic_FF_DW.Integrator_DSTATE_h = -SVM_VOLTAGE_LIMIT;
  }

  /* End of Update for DiscreteIntegrator: '<S69>/Integrator' */

  /* Update for DiscreteIntegrator: '<S64>/Filter' */
  FOC_Basic_FF_DW.Filter_DSTATE_d += 0.0001 * rtb_VdFF_unsat;

  /* Update for Delay: '<S4>/Delay' */
  FOC_Basic_FF_DW.icLoad = false;
}

/* Model step function for TID1 */
void FOC_Basic_FF_step1(void)          /* Sample time: [0.001s, 0.0s] */
{
  double rtb_NProdOut_j;
  double rtb_Sum;
  double rtb_UkYk1_l;
  double rtb_deltafalllimit_d;

  /* Product: '<S192>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S184>/Filter'
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S182>/DProd Out'
   *  Sum: '<S184>/SumD'
   */
  rtb_NProdOut_j = (FOC_Basic_FF_Y.Speed_error *
                    FOC_Basic_FF_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA -
                    FOC_Basic_FF_DW.Filter_DSTATE_i) *
    FOC_Basic_FF_U.MTPA_PID.Speed_PID_MTPA.Filter_speed_PID_MTPA;

  /* Sum: '<S199>/Sum' incorporates:
   *  DiscreteIntegrator: '<S189>/Integrator'
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S194>/PProd Out'
   */
  rtb_Sum = (FOC_Basic_FF_Y.Speed_error *
             FOC_Basic_FF_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA +
             FOC_Basic_FF_DW.Integrator_DSTATE_b) + rtb_NProdOut_j;

  /* Switch: '<S197>/Switch2' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  RelationalOperator: '<S197>/LowerRelop1'
   *  RelationalOperator: '<S197>/UpperRelop'
   *  Switch: '<S197>/Switch'
   */
  if (rtb_Sum > FOC_Basic_FF_U.MTPA_PID.Up_Limit_speed_PID_MTPA) {
    /* Switch: '<S197>/Switch2' */
    FOC_Basic_FF_Y.Iq_gen = FOC_Basic_FF_U.MTPA_PID.Up_Limit_speed_PID_MTPA;
  } else if (rtb_Sum < FOC_Basic_FF_U.MTPA_PID.Low_Limit_speed_PID_MTPA) {
    /* Switch: '<S197>/Switch2' incorporates:
     *  Switch: '<S197>/Switch'
     */
    FOC_Basic_FF_Y.Iq_gen = FOC_Basic_FF_U.MTPA_PID.Low_Limit_speed_PID_MTPA;
  } else {
    /* Switch: '<S197>/Switch2' incorporates:
     *  Switch: '<S197>/Switch'
     */
    FOC_Basic_FF_Y.Iq_gen = rtb_Sum;
  }

  if (d.forward_pin == GPIO_PIN_RESET && d.reverse_pin == GPIO_PIN_SET)
    FOC_Basic_FF_Y.Iq_gen *= 1.0f;
  else if (d.forward_pin == GPIO_PIN_SET && d.reverse_pin == GPIO_PIN_RESET)
    FOC_Basic_FF_Y.Iq_gen *= -1.0f;
  else
    FOC_Basic_FF_Y.Iq_gen = 0.0f;

  /* End of Switch: '<S197>/Switch2' */

  /* Delay: '<S8>/Delay' */
  if (FOC_Basic_FF_DW.icLoad_p) {
    /* Sum: '<S8>/Difference Inputs2'
     *
     * Block description for '<S8>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_Basic_FF_DW.Delay_DSTATE_h = FOC_Basic_FF_Y.Iq_gen;
  }

  /* Sum: '<S8>/Difference Inputs1' incorporates:
   *  Delay: '<S8>/Delay'
   *
   * Block description for '<S8>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_UkYk1_l = FOC_Basic_FF_Y.Iq_gen - FOC_Basic_FF_DW.Delay_DSTATE_h;

  /* Product: '<S8>/delta rise limit' incorporates:
   *  Inport: '<Root>/Rate_limiter'
   *  SampleTimeMath: '<S8>/sample time'
   *
   * About '<S8>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_deltafalllimit_d = FOC_Basic_FF_U.Rate_limiter.Torque_gen_ramp_up * 0.001;

  /* Switch: '<S153>/Switch2' incorporates:
   *  RelationalOperator: '<S153>/LowerRelop1'
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
      FOC_Basic_FF_U.Rate_limiter.Torque_gen_ramp_down;

    /* Switch: '<S153>/Switch' incorporates:
     *  RelationalOperator: '<S153>/UpperRelop'
     */
    if (!(rtb_UkYk1_l < rtb_deltafalllimit_d)) {
      rtb_deltafalllimit_d = rtb_UkYk1_l;
    }

    /* End of Switch: '<S153>/Switch' */
  }

  /* End of Switch: '<S153>/Switch2' */

  /* Sum: '<S8>/Difference Inputs2' incorporates:
   *  Delay: '<S8>/Delay'
   *
   * Block description for '<S8>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_Basic_FF_DW.Delay_DSTATE_h += rtb_deltafalllimit_d;

  /* RateTransition: '<S2>/Rate Transition' */
  FOC_Basic_FF_DW.RateTransition_Buffer0 = FOC_Basic_FF_DW.Delay_DSTATE_h;

  /* Update for DiscreteIntegrator: '<S189>/Integrator' incorporates:
   *  Inport: '<Root>/MTPA_PID'
   *  Outport: '<Root>/Speed_error'
   *  Product: '<S186>/IProd Out'
   *  Sum: '<S181>/SumI2'
   *  Sum: '<S181>/SumI4'
   *  Sum: '<S201>/SumI3'
   *  Sum: '<S202>/SumI1'
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

  /* End of Update for DiscreteIntegrator: '<S189>/Integrator' */

  /* Update for DiscreteIntegrator: '<S184>/Filter' */
  FOC_Basic_FF_DW.Filter_DSTATE_i += 0.001 * rtb_NProdOut_j;

  /* Update for Delay: '<S8>/Delay' */
  FOC_Basic_FF_DW.icLoad_p = false;
}

/* Model initialize function */
void FOC_Basic_FF_initialize(void)
{
  /* InitializeConditions for Delay: '<S4>/Delay' */
  FOC_Basic_FF_DW.icLoad = true;

  /* InitializeConditions for Delay: '<S8>/Delay' */
  FOC_Basic_FF_DW.icLoad_p = true;

  FOC_Basic_FF_U.BusVoltage_V = OP_VOLTAGE;
  FOC_Basic_FF_U.MotorTemperature_C = 40.0f;
  FOC_Basic_FF_U.MCTemperature_C = 40.0f;
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
