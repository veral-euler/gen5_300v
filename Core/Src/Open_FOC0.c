/*
 * File: Open_FOC0.c
 *
 * Code generated for Simulink model 'Open_FOC0'.
 *
 * Model version                  : 1.51
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Feb 23 20:36:54 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Open_FOC0.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <stdbool.h>

/* Block signals (default storage) */
B_Open_FOC0_T Open_FOC0_B;

/* Block states (default storage) */
DW_Open_FOC0_T Open_FOC0_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Open_FOC0_T Open_FOC0_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Open_FOC0_T Open_FOC0_Y;

/* Real-time model */
static RT_MODEL_Open_FOC0_T Open_FOC0_M_;
RT_MODEL_Open_FOC0_T *const Open_FOC0_M = &Open_FOC0_M_;

/* Model step function */
void Open_FOC0_step(void)
{
  double q;
  double yTemp;
  bool rEQ0;

  /* Outputs for Atomic SubSystem: '<S9>/Two phase CRL wrap' */
  /* Sum: '<S10>/a_plus_2b' incorporates:
   *  Inport: '<Root>/Phase_current'
   */
  Open_FOC0_B.a_plus_2b = (Open_FOC0_U.Phase_current[0] +
    Open_FOC0_U.Phase_current[1]) + Open_FOC0_U.Phase_current[1];

  /* Gain: '<S10>/one_by_sqrt3' */
  Open_FOC0_B.one_by_sqrt3 = 0.57735026918962584 * Open_FOC0_B.a_plus_2b;

  /* AlgorithmDescriptorDelegate generated from: '<S10>/a16' incorporates:
   *  Inport: '<Root>/Phase_current'
   */
  Open_FOC0_B.algDD_o1_g = Open_FOC0_U.Phase_current[0];

  /* AlgorithmDescriptorDelegate generated from: '<S10>/a16' */
  Open_FOC0_B.algDD_o2_o = Open_FOC0_B.one_by_sqrt3;

  /* End of Outputs for SubSystem: '<S9>/Two phase CRL wrap' */

  /* DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  Open_FOC0_B.DiscreteTimeIntegrator =
    Open_FOC0_DW.DiscreteTimeIntegrator_DSTATE;

  /* MATLABSystem: '<S1>/Modulo by Constant' */
  if (rtIsNaN(Open_FOC0_B.DiscreteTimeIntegrator) || rtIsInf
      (Open_FOC0_B.DiscreteTimeIntegrator)) {
    yTemp = (rtNaN);
  } else if (Open_FOC0_B.DiscreteTimeIntegrator == 0.0) {
    yTemp = 0.0;
  } else {
    yTemp = fmod(Open_FOC0_B.DiscreteTimeIntegrator, 6.2831853071795862);
    rEQ0 = (yTemp == 0.0);
    if (!rEQ0) {
      q = fabs(Open_FOC0_B.DiscreteTimeIntegrator / 6.2831853071795862);
      rEQ0 = !(fabs(q - floor(q + 0.5)) > 2.2204460492503131E-16 * q);
    }

    if (rEQ0) {
      yTemp = 0.0;
    } else if (yTemp < 0.0) {
      yTemp += 6.2831853071795862;
    }
  }

  /* MATLABSystem: '<S1>/Modulo by Constant' */
  Open_FOC0_B.ModulobyConstant = yTemp;

  /* Switch: '<S1>/Switch' incorporates:
   *  Inport: '<Root>/Theta_1_Speed_0'
   */
  if (Open_FOC0_U.Theta_1_Speed_0 > 0.0) {
    /* Switch: '<S1>/Switch' incorporates:
     *  Inport: '<Root>/Theta_e_ref'
     */
    Open_FOC0_B.Switch = Open_FOC0_U.Theta_e_ref;
  } else {
    /* Switch: '<S1>/Switch' */
    Open_FOC0_B.Switch = Open_FOC0_B.ModulobyConstant;
  }

  /* End of Switch: '<S1>/Switch' */

  /* Trigonometry: '<S1>/Trigonometric Function' incorporates:
   *  Trigonometry: '<S1>/Trigonometric Function2'
   */
  yTemp = sin(Open_FOC0_B.Switch);

  /* Trigonometry: '<S1>/Trigonometric Function' */
  Open_FOC0_B.TrigonometricFunction = yTemp;

  /* Trigonometry: '<S1>/Trigonometric Function1' incorporates:
   *  Trigonometry: '<S1>/Trigonometric Function3'
   */
  q = cos(Open_FOC0_B.Switch);

  /* Trigonometry: '<S1>/Trigonometric Function1' */
  Open_FOC0_B.TrigonometricFunction1 = q;

  /* Outputs for Atomic SubSystem: '<S7>/Two inputs CRL' */
  /* Product: '<S126>/acos' */
  Open_FOC0_B.acos_b = Open_FOC0_B.algDD_o1_g *
    Open_FOC0_B.TrigonometricFunction1;

  /* Product: '<S126>/bsin' */
  Open_FOC0_B.bsin = Open_FOC0_B.algDD_o2_o * Open_FOC0_B.TrigonometricFunction;

  /* Sum: '<S126>/sum_Ds' */
  Open_FOC0_B.sum_Ds = Open_FOC0_B.acos_b + Open_FOC0_B.bsin;

  /* Product: '<S126>/bcos' */
  Open_FOC0_B.bcos = Open_FOC0_B.algDD_o2_o * Open_FOC0_B.TrigonometricFunction1;

  /* Product: '<S126>/asin' */
  Open_FOC0_B.asin_e = Open_FOC0_B.algDD_o1_g *
    Open_FOC0_B.TrigonometricFunction;

  /* Sum: '<S126>/sum_Qs' */
  Open_FOC0_B.sum_Qs = Open_FOC0_B.bcos - Open_FOC0_B.asin_e;

  /* Switch: '<S127>/Switch' */
  Open_FOC0_B.Switch_p[0] = Open_FOC0_B.sum_Ds;
  Open_FOC0_B.Switch_p[1] = Open_FOC0_B.sum_Qs;

  /* AlgorithmDescriptorDelegate generated from: '<S126>/a16' */
  Open_FOC0_B.algDD_o1 = Open_FOC0_B.Switch_p[0];

  /* AlgorithmDescriptorDelegate generated from: '<S126>/a16' */
  Open_FOC0_B.algDD_o2 = Open_FOC0_B.Switch_p[1];

  /* End of Outputs for SubSystem: '<S7>/Two inputs CRL' */

  /* Sum: '<S1>/Sum' incorporates:
   *  Inport: '<Root>/Id_ref'
   */
  Open_FOC0_B.Sum = Open_FOC0_U.Id_ref - Open_FOC0_B.algDD_o1;

  /* Product: '<S52>/PProd Out' incorporates:
   *  Inport: '<Root>/Kp_d_axis'
   */
  Open_FOC0_B.PProdOut = Open_FOC0_B.Sum * Open_FOC0_U.Kp_d_axis;

  /* DiscreteIntegrator: '<S47>/Integrator' */
  Open_FOC0_B.Integrator = Open_FOC0_DW.Integrator_DSTATE;

  /* Product: '<S40>/DProd Out' incorporates:
   *  Inport: '<Root>/Kd__d_axis'
   */
  Open_FOC0_B.DProdOut = Open_FOC0_B.Sum * Open_FOC0_U.Kd__d_axis;

  /* DiscreteIntegrator: '<S42>/Filter' */
  Open_FOC0_B.Filter = Open_FOC0_DW.Filter_DSTATE;

  /* Sum: '<S42>/SumD' */
  Open_FOC0_B.SumD = Open_FOC0_B.DProdOut - Open_FOC0_B.Filter;

  /* Product: '<S50>/NProd Out' incorporates:
   *  Inport: '<Root>/Filter_d_axis'
   */
  Open_FOC0_B.NProdOut = Open_FOC0_B.SumD * Open_FOC0_U.Filter_d_axis;

  /* Sum: '<S57>/Sum' */
  Open_FOC0_B.Sum_p = (Open_FOC0_B.PProdOut + Open_FOC0_B.Integrator) +
    Open_FOC0_B.NProdOut;

  /* RelationalOperator: '<S55>/LowerRelop1' incorporates:
   *  Inport: '<Root>/Vd_up_limit'
   */
  Open_FOC0_B.LowerRelop1 = (Open_FOC0_B.Sum_p > Open_FOC0_U.Vd_up_limit);

  /* Switch: '<S55>/Switch2' */
  if (Open_FOC0_B.LowerRelop1) {
    /* Outport: '<Root>/Vd' incorporates:
     *  Inport: '<Root>/Vd_up_limit'
     */
    Open_FOC0_Y.Vd = Open_FOC0_U.Vd_up_limit;
  } else {
    /* RelationalOperator: '<S55>/UpperRelop' incorporates:
     *  Inport: '<Root>/Vd_low_limit'
     */
    Open_FOC0_B.UpperRelop_c = (Open_FOC0_B.Sum_p < Open_FOC0_U.Vd_low_limit);

    /* Switch: '<S55>/Switch' */
    if (Open_FOC0_B.UpperRelop_c) {
      /* Switch: '<S55>/Switch' incorporates:
       *  Inport: '<Root>/Vd_low_limit'
       */
      Open_FOC0_B.Switch_k = Open_FOC0_U.Vd_low_limit;
    } else {
      /* Switch: '<S55>/Switch' */
      Open_FOC0_B.Switch_k = Open_FOC0_B.Sum_p;
    }

    /* End of Switch: '<S55>/Switch' */

    /* Outport: '<Root>/Vd' */
    Open_FOC0_Y.Vd = Open_FOC0_B.Switch_k;
  }

  /* End of Switch: '<S55>/Switch2' */

  /* Sum: '<S1>/Sum1' incorporates:
   *  Inport: '<Root>/Iq_ref'
   */
  Open_FOC0_B.Sum1 = Open_FOC0_U.Iq_ref - Open_FOC0_B.algDD_o2;

  /* Product: '<S105>/PProd Out' incorporates:
   *  Inport: '<Root>/Kp_q_axis'
   */
  Open_FOC0_B.PProdOut_a = Open_FOC0_B.Sum1 * Open_FOC0_U.Kp_q_axis;

  /* DiscreteIntegrator: '<S100>/Integrator' */
  Open_FOC0_B.Integrator_k = Open_FOC0_DW.Integrator_DSTATE_n;

  /* Product: '<S93>/DProd Out' incorporates:
   *  Inport: '<Root>/Kd_q_axis'
   */
  Open_FOC0_B.DProdOut_a = Open_FOC0_B.Sum1 * Open_FOC0_U.Kd_q_axis;

  /* DiscreteIntegrator: '<S95>/Filter' */
  Open_FOC0_B.Filter_m = Open_FOC0_DW.Filter_DSTATE_i;

  /* Sum: '<S95>/SumD' */
  Open_FOC0_B.SumD_d = Open_FOC0_B.DProdOut_a - Open_FOC0_B.Filter_m;

  /* Product: '<S103>/NProd Out' incorporates:
   *  Inport: '<Root>/Filter_q_axis'
   */
  Open_FOC0_B.NProdOut_h = Open_FOC0_B.SumD_d * Open_FOC0_U.Filter_q_axis;

  /* Sum: '<S110>/Sum' */
  Open_FOC0_B.Sum_d = (Open_FOC0_B.PProdOut_a + Open_FOC0_B.Integrator_k) +
    Open_FOC0_B.NProdOut_h;

  /* RelationalOperator: '<S108>/LowerRelop1' incorporates:
   *  Inport: '<Root>/Vq_up_limit'
   */
  Open_FOC0_B.LowerRelop1_l = (Open_FOC0_B.Sum_d > Open_FOC0_U.Vq_up_limit);

  /* Switch: '<S108>/Switch2' */
  if (Open_FOC0_B.LowerRelop1_l) {
    /* Outport: '<Root>/Vq' incorporates:
     *  Inport: '<Root>/Vq_up_limit'
     */
    Open_FOC0_Y.Vq = Open_FOC0_U.Vq_up_limit;
  } else {
    /* RelationalOperator: '<S108>/UpperRelop' incorporates:
     *  Inport: '<Root>/Vq_low_limit'
     */
    Open_FOC0_B.UpperRelop_a = (Open_FOC0_B.Sum_d < Open_FOC0_U.Vq_low_limit);

    /* Switch: '<S108>/Switch' */
    if (Open_FOC0_B.UpperRelop_a) {
      /* Switch: '<S108>/Switch' incorporates:
       *  Inport: '<Root>/Vq_low_limit'
       */
      Open_FOC0_B.Switch_i = Open_FOC0_U.Vq_low_limit;
    } else {
      /* Switch: '<S108>/Switch' */
      Open_FOC0_B.Switch_i = Open_FOC0_B.Sum_d;
    }

    /* End of Switch: '<S108>/Switch' */

    /* Outport: '<Root>/Vq' */
    Open_FOC0_Y.Vq = Open_FOC0_B.Switch_i;
  }

  /* End of Switch: '<S108>/Switch2' */

  /* Trigonometry: '<S1>/Trigonometric Function2' */
  Open_FOC0_B.TrigonometricFunction2 = yTemp;

  /* Trigonometry: '<S1>/Trigonometric Function3' */
  Open_FOC0_B.TrigonometricFunction3 = q;

  /* Outputs for Atomic SubSystem: '<S3>/Two inputs CRL' */
  /* Product: '<S11>/qcos' incorporates:
   *  Outport: '<Root>/Vq'
   */
  Open_FOC0_B.qcos = Open_FOC0_Y.Vq * Open_FOC0_B.TrigonometricFunction3;

  /* Product: '<S11>/dsin' incorporates:
   *  Outport: '<Root>/Vd'
   */
  Open_FOC0_B.dsin = Open_FOC0_Y.Vd * Open_FOC0_B.TrigonometricFunction2;

  /* Sum: '<S11>/sum_beta' */
  Open_FOC0_B.sum_beta = Open_FOC0_B.qcos + Open_FOC0_B.dsin;

  /* Product: '<S11>/dcos' incorporates:
   *  Outport: '<Root>/Vd'
   */
  Open_FOC0_B.dcos = Open_FOC0_Y.Vd * Open_FOC0_B.TrigonometricFunction3;

  /* Product: '<S11>/qsin' incorporates:
   *  Outport: '<Root>/Vq'
   */
  Open_FOC0_B.qsin = Open_FOC0_Y.Vq * Open_FOC0_B.TrigonometricFunction2;

  /* Sum: '<S11>/sum_alpha' */
  Open_FOC0_B.sum_alpha = Open_FOC0_B.dcos - Open_FOC0_B.qsin;

  /* Switch: '<S12>/Switch' */
  Open_FOC0_B.Switch_l[0] = Open_FOC0_B.sum_alpha;
  Open_FOC0_B.Switch_l[1] = Open_FOC0_B.sum_beta;

  /* AlgorithmDescriptorDelegate generated from: '<S11>/a16' */
  Open_FOC0_B.algDD_o1_p = Open_FOC0_B.Switch_l[0];

  /* AlgorithmDescriptorDelegate generated from: '<S11>/a16' */
  Open_FOC0_B.algDD_o2_m = Open_FOC0_B.Switch_l[1];

  /* End of Outputs for SubSystem: '<S3>/Two inputs CRL' */

  /* Gain: '<S125>/one_by_two' */
  Open_FOC0_B.one_by_two = 0.5 * Open_FOC0_B.algDD_o1_p;

  /* Gain: '<S125>/sqrt3_by_two' */
  Open_FOC0_B.sqrt3_by_two = 0.8660254037844386 * Open_FOC0_B.algDD_o2_m;

  /* Sum: '<S125>/add_b' */
  Open_FOC0_B.add_b = Open_FOC0_B.sqrt3_by_two - Open_FOC0_B.one_by_two;

  /* Sum: '<S125>/add_c' */
  Open_FOC0_B.add_c = (0.0 - Open_FOC0_B.one_by_two) - Open_FOC0_B.sqrt3_by_two;

  /* MinMax: '<S122>/Max' */
  yTemp = fmax(Open_FOC0_B.algDD_o1_p, Open_FOC0_B.add_b);
  yTemp = fmax(yTemp, Open_FOC0_B.add_c);

  /* MinMax: '<S122>/Max' */
  Open_FOC0_B.Max = yTemp;

  /* MinMax: '<S122>/Min' */
  yTemp = fmin(Open_FOC0_B.algDD_o1_p, Open_FOC0_B.add_b);
  yTemp = fmin(yTemp, Open_FOC0_B.add_c);

  /* MinMax: '<S122>/Min' */
  Open_FOC0_B.Min = yTemp;

  /* Sum: '<S122>/Add' */
  Open_FOC0_B.Add = Open_FOC0_B.Max + Open_FOC0_B.Min;

  /* Gain: '<S122>/one_by_two' */
  Open_FOC0_B.one_by_two_m = -0.5 * Open_FOC0_B.Add;

  /* Sum: '<S121>/Add3' */
  Open_FOC0_B.Add3 = Open_FOC0_B.algDD_o1_p + Open_FOC0_B.one_by_two_m;

  /* Sum: '<S121>/Add1' */
  Open_FOC0_B.Add1 = Open_FOC0_B.add_b + Open_FOC0_B.one_by_two_m;

  /* Sum: '<S121>/Add2' */
  Open_FOC0_B.Add2 = Open_FOC0_B.one_by_two_m + Open_FOC0_B.add_c;

  /* Gain: '<S121>/Gain' */
  Open_FOC0_B.Gain[0] = 1.1547005383792517 * Open_FOC0_B.Add3;
  Open_FOC0_B.Gain[1] = 1.1547005383792517 * Open_FOC0_B.Add1;
  Open_FOC0_B.Gain[2] = 1.1547005383792517 * Open_FOC0_B.Add2;

  /* Outport: '<Root>/Va' */
  Open_FOC0_Y.Va = Open_FOC0_B.Gain[0];

  /* Outport: '<Root>/Vb' */
  Open_FOC0_Y.Vb = Open_FOC0_B.Gain[1];

  /* Outport: '<Root>/Vc' */
  Open_FOC0_Y.Vc = Open_FOC0_B.Gain[2];

  /* SampleTimeMath: '<S8>/sample time'
   *
   * About '<S8>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  Open_FOC0_B.sampletime = 0.0001;

  /* Product: '<S8>/delta rise limit' incorporates:
   *  Inport: '<Root>/Speed_up_rate'
   */
  Open_FOC0_B.deltariselimit = Open_FOC0_U.Speed_up_rate * 0.0001;

  /* Delay: '<S8>/Delay' incorporates:
   *  Constant: '<S8>/Constant'
   */
  if (Open_FOC0_DW.icLoad) {
    Open_FOC0_DW.Delay_DSTATE = 0.0;
  }

  /* Delay: '<S8>/Delay' */
  Open_FOC0_B.Yk1 = Open_FOC0_DW.Delay_DSTATE;

  /* Sum: '<S8>/Difference Inputs1' incorporates:
   *  Inport: '<Root>/Speed_ref'
   *
   * Block description for '<S8>/Difference Inputs1':
   *
   *  Add in CPU
   */
  Open_FOC0_B.UkYk1 = Open_FOC0_U.Speed_ref - Open_FOC0_B.Yk1;

  /* RelationalOperator: '<S128>/LowerRelop1' */
  Open_FOC0_B.LowerRelop1_m = (Open_FOC0_B.UkYk1 > Open_FOC0_B.deltariselimit);

  /* Switch: '<S128>/Switch2' */
  if (Open_FOC0_B.LowerRelop1_m) {
    /* Switch: '<S128>/Switch2' */
    Open_FOC0_B.Switch2_a = Open_FOC0_B.deltariselimit;
  } else {
    /* Product: '<S8>/delta fall limit' incorporates:
     *  Inport: '<Root>/Speed_down_rate'
     */
    Open_FOC0_B.deltafalllimit = 0.0001 * Open_FOC0_U.Speed_down_rate;

    /* RelationalOperator: '<S128>/UpperRelop' */
    Open_FOC0_B.UpperRelop = (Open_FOC0_B.UkYk1 < Open_FOC0_B.deltafalllimit);

    /* Switch: '<S128>/Switch' */
    if (Open_FOC0_B.UpperRelop) {
      /* Switch: '<S128>/Switch' */
      Open_FOC0_B.Switch_c = Open_FOC0_B.deltafalllimit;
    } else {
      /* Switch: '<S128>/Switch' */
      Open_FOC0_B.Switch_c = Open_FOC0_B.UkYk1;
    }

    /* End of Switch: '<S128>/Switch' */

    /* Switch: '<S128>/Switch2' */
    Open_FOC0_B.Switch2_a = Open_FOC0_B.Switch_c;
  }

  /* End of Switch: '<S128>/Switch2' */

  /* Sum: '<S8>/Difference Inputs2'
   *
   * Block description for '<S8>/Difference Inputs2':
   *
   *  Add in CPU
   */
  Open_FOC0_B.DifferenceInputs2 = Open_FOC0_B.Switch2_a + Open_FOC0_B.Yk1;

  /* Product: '<S1>/Product' incorporates:
   *  Inport: '<Root>/Pole_pairs'
   */
  Open_FOC0_B.Product = Open_FOC0_B.DifferenceInputs2 * Open_FOC0_U.Pole_pairs;

  /* Gain: '<S1>/Gain' */
  Open_FOC0_B.Gain_o = 0.016666666666666666 * Open_FOC0_B.Product;

  /* Product: '<S44>/IProd Out' incorporates:
   *  Inport: '<Root>/Ki_d_axis'
   */
  Open_FOC0_B.IProdOut = Open_FOC0_B.Sum * Open_FOC0_U.Ki_d_axis;

  /* Product: '<S97>/IProd Out' incorporates:
   *  Inport: '<Root>/Ki_q_axis'
   */
  Open_FOC0_B.IProdOut_m = Open_FOC0_B.Sum1 * Open_FOC0_U.Ki_q_axis;

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  Open_FOC0_DW.DiscreteTimeIntegrator_DSTATE += 0.00062831853071795862 *
    Open_FOC0_B.Gain_o;

  /* Update for DiscreteIntegrator: '<S47>/Integrator' */
  Open_FOC0_DW.Integrator_DSTATE += 0.0001 * Open_FOC0_B.IProdOut;

  /* Update for DiscreteIntegrator: '<S42>/Filter' */
  Open_FOC0_DW.Filter_DSTATE += 0.0001 * Open_FOC0_B.NProdOut;

  /* Update for DiscreteIntegrator: '<S100>/Integrator' */
  Open_FOC0_DW.Integrator_DSTATE_n += 0.0001 * Open_FOC0_B.IProdOut_m;

  /* Update for DiscreteIntegrator: '<S95>/Filter' */
  Open_FOC0_DW.Filter_DSTATE_i += 0.0001 * Open_FOC0_B.NProdOut_h;

  /* Update for Delay: '<S8>/Delay' */
  Open_FOC0_DW.icLoad = false;
  Open_FOC0_DW.Delay_DSTATE = Open_FOC0_B.DifferenceInputs2;
}

/* Model initialize function */
void Open_FOC0_initialize(void)
{
  /* InitializeConditions for Delay: '<S8>/Delay' */
  Open_FOC0_DW.icLoad = true;

  /* Start for MATLABSystem: '<S1>/Modulo by Constant' */
  Open_FOC0_DW.objisempty = true;
  Open_FOC0_DW.obj.isInitialized = 1;

  Open_FOC0_U.Theta_1_Speed_0 = 0;
  Open_FOC0_U.Theta_e_ref = 0;
  Open_FOC0_U.Pole_pairs = POLEPAIRS;
  Open_FOC0_U.Id_ref = -10.0f;
  Open_FOC0_U.Iq_ref = 10.0f;

  /* Rate Limiter Settings */
  Open_FOC0_U.Speed_ref = 500.0f;
  Open_FOC0_U.Speed_up_rate = 0.001 * 10000.0f;
  Open_FOC0_U.Speed_down_rate = -0.1 * 10000.0f;
  
  /* PID Settings */
  /* D Axis PID */
  Open_FOC0_U.Kp_d_axis = 0.08f;
  Open_FOC0_U.Ki_d_axis = 4.0f;
  Open_FOC0_U.Kd__d_axis = 0.00001f;
  Open_FOC0_U.Filter_d_axis = 5.0f;
  /* Q Axis PID */
  Open_FOC0_U.Kp_q_axis = 0.08f;
  Open_FOC0_U.Ki_q_axis = 6.0f;
  Open_FOC0_U.Kd_q_axis = 0.00001f;
  Open_FOC0_U.Filter_q_axis = 5.0f;

  /* Voltage limits */
  Open_FOC0_U.Vd_up_limit = 5.0f;
  Open_FOC0_U.Vd_low_limit = -5.0f;
  Open_FOC0_U.Vq_up_limit = 5.0f;
  Open_FOC0_U.Vq_low_limit = -5.0f;

}

/* Model terminate function */
void Open_FOC0_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
