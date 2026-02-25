/*
 * File: Open_FOC0.h
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

#ifndef Open_FOC0_h_
#define Open_FOC0_h_
#ifndef Open_FOC0_COMMON_INCLUDES_
#define Open_FOC0_COMMON_INCLUDES_
#include <stdbool.h>
#include <stdint.h>
#include "complex_types.h"
#include "rt_nonfinite.h"
#include "math.h"
#include "main.h"
#endif                                 /* Open_FOC0_COMMON_INCLUDES_ */

#include "Open_FOC0_types.h"
#include "rtGetNaN.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  double DiscreteTimeIntegrator;       /* '<S1>/Discrete-Time Integrator' */
  double Switch;                       /* '<S1>/Switch' */
  double TrigonometricFunction;        /* '<S1>/Trigonometric Function' */
  double TrigonometricFunction1;       /* '<S1>/Trigonometric Function1' */
  double Sum;                          /* '<S1>/Sum' */
  double PProdOut;                     /* '<S52>/PProd Out' */
  double Integrator;                   /* '<S47>/Integrator' */
  double DProdOut;                     /* '<S40>/DProd Out' */
  double Filter;                       /* '<S42>/Filter' */
  double SumD;                         /* '<S42>/SumD' */
  double NProdOut;                     /* '<S50>/NProd Out' */
  double Sum_p;                        /* '<S57>/Sum' */
  double Sum1;                         /* '<S1>/Sum1' */
  double PProdOut_a;                   /* '<S105>/PProd Out' */
  double Integrator_k;                 /* '<S100>/Integrator' */
  double DProdOut_a;                   /* '<S93>/DProd Out' */
  double Filter_m;                     /* '<S95>/Filter' */
  double SumD_d;                       /* '<S95>/SumD' */
  double NProdOut_h;                   /* '<S103>/NProd Out' */
  double Sum_d;                        /* '<S110>/Sum' */
  double TrigonometricFunction2;       /* '<S1>/Trigonometric Function2' */
  double TrigonometricFunction3;       /* '<S1>/Trigonometric Function3' */
  double one_by_two;                   /* '<S125>/one_by_two' */
  double sqrt3_by_two;                 /* '<S125>/sqrt3_by_two' */
  double add_b;                        /* '<S125>/add_b' */
  double add_c;                        /* '<S125>/add_c' */
  double Max;                          /* '<S122>/Max' */
  double Min;                          /* '<S122>/Min' */
  double Add;                          /* '<S122>/Add' */
  double one_by_two_m;                 /* '<S122>/one_by_two' */
  double Add3;                         /* '<S121>/Add3' */
  double Add1;                         /* '<S121>/Add1' */
  double Add2;                         /* '<S121>/Add2' */
  double Gain[3];                      /* '<S121>/Gain' */
  double sampletime;                   /* '<S8>/sample time' */
  double deltariselimit;               /* '<S8>/delta rise limit' */
  double Yk1;                          /* '<S8>/Delay' */
  double UkYk1;                        /* '<S8>/Difference Inputs1' */
  double Switch2_a;                    /* '<S128>/Switch2' */
  double DifferenceInputs2;            /* '<S8>/Difference Inputs2' */
  double Product;                      /* '<S1>/Product' */
  double Gain_o;                       /* '<S1>/Gain' */
  double IProdOut;                     /* '<S44>/IProd Out' */
  double IProdOut_m;                   /* '<S97>/IProd Out' */
  double deltafalllimit;               /* '<S8>/delta fall limit' */
  double Switch_c;                     /* '<S128>/Switch' */
  double acos_b;                       /* '<S126>/acos' */
  double bsin;                         /* '<S126>/bsin' */
  double sum_Ds;                       /* '<S126>/sum_Ds' */
  double bcos;                         /* '<S126>/bcos' */
  double asin_e;                       /* '<S126>/asin' */
  double sum_Qs;                       /* '<S126>/sum_Qs' */
  double Switch_p[2];                  /* '<S127>/Switch' */
  double algDD_o1;
  double algDD_o2;
  double Switch_i;                     /* '<S108>/Switch' */
  double Switch_k;                     /* '<S55>/Switch' */
  double ModulobyConstant;             /* '<S1>/Modulo by Constant' */
  double qcos;                         /* '<S11>/qcos' */
  double dsin;                         /* '<S11>/dsin' */
  double sum_beta;                     /* '<S11>/sum_beta' */
  double dcos;                         /* '<S11>/dcos' */
  double qsin;                         /* '<S11>/qsin' */
  double sum_alpha;                    /* '<S11>/sum_alpha' */
  double Switch_l[2];                  /* '<S12>/Switch' */
  double algDD_o1_p;
  double algDD_o2_m;
  double a_plus_2b;                    /* '<S10>/a_plus_2b' */
  double one_by_sqrt3;                 /* '<S10>/one_by_sqrt3' */
  double algDD_o1_g;
  double algDD_o2_o;
  bool LowerRelop1;                    /* '<S55>/LowerRelop1' */
  bool LowerRelop1_l;                  /* '<S108>/LowerRelop1' */
  bool LowerRelop1_m;                  /* '<S128>/LowerRelop1' */
  bool UpperRelop;                     /* '<S128>/UpperRelop' */
  bool UpperRelop_a;                   /* '<S108>/UpperRelop' */
  bool UpperRelop_c;                   /* '<S55>/UpperRelop' */
} B_Open_FOC0_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  double DiscreteTimeIntegrator_DSTATE;/* '<S1>/Discrete-Time Integrator' */
  double Integrator_DSTATE;            /* '<S47>/Integrator' */
  double Filter_DSTATE;                /* '<S42>/Filter' */
  double Integrator_DSTATE_n;          /* '<S100>/Integrator' */
  double Filter_DSTATE_i;              /* '<S95>/Filter' */
  double Delay_DSTATE;                 /* '<S8>/Delay' */
  fixed_system_ModByConstant_Op_T obj; /* '<S1>/Modulo by Constant' */
  bool icLoad;                         /* '<S8>/Delay' */
  bool objisempty;                     /* '<S1>/Modulo by Constant' */
} DW_Open_FOC0_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  double Iq_ref;                       /* '<Root>/Iq_ref' */
  double Id_ref;                       /* '<Root>/Id_ref' */
  double Theta_e_ref;                  /* '<Root>/Theta_e_ref' */
  double Theta_1_Speed_0;              /* '<Root>/Theta_1_Speed_0' */
  double Speed_ref;                    /* '<Root>/Speed_ref' */
  double Speed_up_rate;                /* '<Root>/Speed_up_rate' */
  double Speed_down_rate;              /* '<Root>/Speed_down_rate' */
  double Pole_pairs;                   /* '<Root>/Pole_pairs' */
  double Phase_current[3];             /* '<Root>/Phase_current' */
  double Kp_d_axis;                    /* '<Root>/Kp_d_axis' */
  double Ki_d_axis;                    /* '<Root>/Ki_d_axis' */
  double Kd__d_axis;                   /* '<Root>/Kd__d_axis' */
  double Filter_d_axis;                /* '<Root>/Filter_d_axis' */
  double Vd_up_limit;                  /* '<Root>/Vd_up_limit' */
  double Vd_low_limit;                 /* '<Root>/Vd_low_limit' */
  double Kp_q_axis;                    /* '<Root>/Kp_q_axis' */
  double Ki_q_axis;                    /* '<Root>/Ki_q_axis' */
  double Kd_q_axis;                    /* '<Root>/Kd_q_axis' */
  double Filter_q_axis;                /* '<Root>/Filter_q_axis' */
  double Vq_up_limit;                  /* '<Root>/Vq_up_limit' */
  double Vq_low_limit;                 /* '<Root>/Vq_low_limit' */
} ExtU_Open_FOC0_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  double Va;                           /* '<Root>/Va' */
  double Vb;                           /* '<Root>/Vb' */
  double Vc;                           /* '<Root>/Vc' */
  double Vd;                           /* '<Root>/Vd' */
  double Vq;                           /* '<Root>/Vq' */
} ExtY_Open_FOC0_T;

/* Real-time Model Data Structure */
struct tag_RTM_Open_FOC0_T {
  const char * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_Open_FOC0_T Open_FOC0_B;

/* Block states (default storage) */
extern DW_Open_FOC0_T Open_FOC0_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_Open_FOC0_T Open_FOC0_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Open_FOC0_T Open_FOC0_Y;

/* Model entry point functions */
extern void Open_FOC0_initialize(void);
extern void Open_FOC0_step(void);
extern void Open_FOC0_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Open_FOC0_T *const Open_FOC0_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S10>/Data Type Duplicate' : Unused code path elimination
 * Block '<S11>/Data Type Duplicate' : Unused code path elimination
 * Block '<S11>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S55>/Data Type Duplicate' : Unused code path elimination
 * Block '<S55>/Data Type Propagation' : Unused code path elimination
 * Block '<S108>/Data Type Duplicate' : Unused code path elimination
 * Block '<S108>/Data Type Propagation' : Unused code path elimination
 * Block '<S6>/Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/Vc' : Unused code path elimination
 * Block '<S125>/Data Type Duplicate' : Unused code path elimination
 * Block '<S126>/Data Type Duplicate' : Unused code path elimination
 * Block '<S126>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S128>/Data Type Duplicate' : Unused code path elimination
 * Block '<S128>/Data Type Propagation' : Unused code path elimination
 * Block '<S9>/Kalpha' : Eliminated nontunable gain of 1
 * Block '<S9>/Kbeta' : Eliminated nontunable gain of 1
 * Block '<S125>/Ka' : Eliminated nontunable gain of 1
 * Block '<S125>/Kb' : Eliminated nontunable gain of 1
 * Block '<S125>/Kc' : Eliminated nontunable gain of 1
 * Block '<S8>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S12>/Offset' : Unused code path elimination
 * Block '<S12>/Unary_Minus' : Unused code path elimination
 * Block '<S127>/Offset' : Unused code path elimination
 * Block '<S127>/Unary_Minus' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('Open_FOC_C_Elec/Subsystem1/Open_FOC')    - opens subsystem Open_FOC_C_Elec/Subsystem1/Open_FOC
 * hilite_system('Open_FOC_C_Elec/Subsystem1/Open_FOC/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Open_FOC_C_Elec/Subsystem1'
 * '<S1>'   : 'Open_FOC_C_Elec/Subsystem1/Open_FOC'
 * '<S2>'   : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/Clarke Transform'
 * '<S3>'   : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/Inverse Park Transform'
 * '<S4>'   : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller'
 * '<S5>'   : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1'
 * '<S6>'   : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PWM Reference Generator'
 * '<S7>'   : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/Park Transform'
 * '<S8>'   : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/Subsystem'
 * '<S9>'   : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/Clarke Transform/Two phase input'
 * '<S10>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/Clarke Transform/Two phase input/Two phase CRL wrap'
 * '<S11>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/Inverse Park Transform/Two inputs CRL'
 * '<S12>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/Inverse Park Transform/Two inputs CRL/Switch_Axis'
 * '<S13>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Anti-windup'
 * '<S14>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/D Gain'
 * '<S15>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/External Derivative'
 * '<S16>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Filter'
 * '<S17>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Filter ICs'
 * '<S18>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/I Gain'
 * '<S19>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Ideal P Gain'
 * '<S20>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Ideal P Gain Fdbk'
 * '<S21>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Integrator'
 * '<S22>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Integrator ICs'
 * '<S23>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/N Copy'
 * '<S24>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/N Gain'
 * '<S25>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/P Copy'
 * '<S26>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Parallel P Gain'
 * '<S27>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Reset Signal'
 * '<S28>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Saturation'
 * '<S29>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Saturation Fdbk'
 * '<S30>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Sum'
 * '<S31>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Sum Fdbk'
 * '<S32>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Tracking Mode'
 * '<S33>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Tracking Mode Sum'
 * '<S34>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Tsamp - Integral'
 * '<S35>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Tsamp - Ngain'
 * '<S36>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/postSat Signal'
 * '<S37>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/preInt Signal'
 * '<S38>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/preSat Signal'
 * '<S39>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Anti-windup/Passthrough'
 * '<S40>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/D Gain/External Parameters'
 * '<S41>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/External Derivative/Error'
 * '<S42>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S43>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S44>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/I Gain/External Parameters'
 * '<S45>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Ideal P Gain/Passthrough'
 * '<S46>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S47>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Integrator/Discrete'
 * '<S48>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Integrator ICs/Internal IC'
 * '<S49>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/N Copy/Disabled'
 * '<S50>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/N Gain/External Parameters'
 * '<S51>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/P Copy/Disabled'
 * '<S52>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Parallel P Gain/External Parameters'
 * '<S53>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Reset Signal/Disabled'
 * '<S54>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Saturation/External'
 * '<S55>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Saturation/External/Saturation Dynamic'
 * '<S56>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Saturation Fdbk/Disabled'
 * '<S57>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Sum/Sum_PID'
 * '<S58>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Sum Fdbk/Disabled'
 * '<S59>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Tracking Mode/Disabled'
 * '<S60>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S61>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S62>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S63>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/postSat Signal/Forward_Path'
 * '<S64>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/preInt Signal/Internal PreInt'
 * '<S65>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller/preSat Signal/Forward_Path'
 * '<S66>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Anti-windup'
 * '<S67>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/D Gain'
 * '<S68>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/External Derivative'
 * '<S69>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Filter'
 * '<S70>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Filter ICs'
 * '<S71>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/I Gain'
 * '<S72>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Ideal P Gain'
 * '<S73>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Ideal P Gain Fdbk'
 * '<S74>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Integrator'
 * '<S75>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Integrator ICs'
 * '<S76>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/N Copy'
 * '<S77>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/N Gain'
 * '<S78>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/P Copy'
 * '<S79>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Parallel P Gain'
 * '<S80>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Reset Signal'
 * '<S81>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Saturation'
 * '<S82>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Saturation Fdbk'
 * '<S83>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Sum'
 * '<S84>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Sum Fdbk'
 * '<S85>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Tracking Mode'
 * '<S86>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Tracking Mode Sum'
 * '<S87>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Tsamp - Integral'
 * '<S88>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Tsamp - Ngain'
 * '<S89>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/postSat Signal'
 * '<S90>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/preInt Signal'
 * '<S91>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/preSat Signal'
 * '<S92>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Anti-windup/Passthrough'
 * '<S93>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/D Gain/External Parameters'
 * '<S94>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/External Derivative/Error'
 * '<S95>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Filter/Disc. Forward Euler Filter'
 * '<S96>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Filter ICs/Internal IC - Filter'
 * '<S97>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/I Gain/External Parameters'
 * '<S98>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Ideal P Gain/Passthrough'
 * '<S99>'  : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S100>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Integrator/Discrete'
 * '<S101>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Integrator ICs/Internal IC'
 * '<S102>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/N Copy/Disabled'
 * '<S103>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/N Gain/External Parameters'
 * '<S104>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/P Copy/Disabled'
 * '<S105>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Parallel P Gain/External Parameters'
 * '<S106>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Reset Signal/Disabled'
 * '<S107>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Saturation/External'
 * '<S108>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Saturation/External/Saturation Dynamic'
 * '<S109>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Saturation Fdbk/Disabled'
 * '<S110>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Sum/Sum_PID'
 * '<S111>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Sum Fdbk/Disabled'
 * '<S112>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Tracking Mode/Disabled'
 * '<S113>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S114>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Tsamp - Integral/TsSignalSpecification'
 * '<S115>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S116>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/postSat Signal/Forward_Path'
 * '<S117>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/preInt Signal/Internal PreInt'
 * '<S118>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PID Controller1/preSat Signal/Forward_Path'
 * '<S119>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PWM Reference Generator/Modulation method'
 * '<S120>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PWM Reference Generator/Voltage Input'
 * '<S121>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PWM Reference Generator/Modulation method/SVPWM'
 * '<S122>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PWM Reference Generator/Modulation method/SVPWM/Half(Vmin+Vmax)'
 * '<S123>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PWM Reference Generator/Voltage Input/Valphabeta'
 * '<S124>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PWM Reference Generator/Voltage Input/Valphabeta/Inverse Clarke Transform'
 * '<S125>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/PWM Reference Generator/Voltage Input/Valphabeta/Inverse Clarke Transform/Two phase input'
 * '<S126>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/Park Transform/Two inputs CRL'
 * '<S127>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/Park Transform/Two inputs CRL/Switch_Axis'
 * '<S128>' : 'Open_FOC_C_Elec/Subsystem1/Open_FOC/Subsystem/Saturation Dynamic'
 */
#endif                                 /* Open_FOC0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
