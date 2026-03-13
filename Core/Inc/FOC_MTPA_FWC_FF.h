/*
 * File: FOC_MTPA_FWC_FF.h
 *
 * Code generated for Simulink model 'FOC_MTPA_FWC_FF'.
 *
 * Model version                  : 18.322
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Fri Mar 13 14:25:46 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef FOC_MTPA_FWC_FF_h_
#define FOC_MTPA_FWC_FF_h_
#ifndef FOC_MTPA_FWC_FF_COMMON_INCLUDES_
#define FOC_MTPA_FWC_FF_COMMON_INCLUDES_
#include <stdbool.h>
#include <stdint.h>
#include "complex_types.h"
#include "rt_nonfinite.h"
#include "math.h"
#include "main.h"
#endif                                 /* FOC_MTPA_FWC_FF_COMMON_INCLUDES_ */

#include "FOC_MTPA_FWC_FF_types.h"
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
  float Merge[2];                      /* '<S7>/Merge' */
  float Merge_n[2];                    /* '<S161>/Merge' */
  float Switch2;                       /* '<S219>/Switch2' */
  float sampletime;                    /* '<S8>/sample time' */
} B_FOC_MTPA_FWC_FF_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  float Delay_DSTATE;                  /* '<S8>/Delay' */
  float Delay_DSTATE_h;                /* '<S156>/Delay' */
  float UnitDelay_DSTATE;              /* '<S18>/Unit Delay' */
  float Integrator_DSTATE;             /* '<S123>/Integrator' */
  float Filter_DSTATE;                 /* '<S118>/Filter' */
  float Delay_DSTATE_b;                /* '<S157>/Delay' */
  float UnitDelay_DSTATE_f;            /* '<S21>/Unit Delay' */
  float Integrator_DSTATE_h;           /* '<S69>/Integrator' */
  float Filter_DSTATE_d;               /* '<S64>/Filter' */
  float Delay_DSTATE_c;                /* '<S3>/Delay' */
  float Integrator_DSTATE_b;           /* '<S211>/Integrator' */
  float Filter_DSTATE_i;               /* '<S206>/Filter' */
  float UnitDelay_DSTATE_p;            /* '<S162>/Unit Delay' */
  float DiscreteTimeIntegrator_DSTATE; /* '<S162>/Discrete-Time Integrator' */
  uint8_t is_active_c3_FOC_MTPA_FWC_FF;/* '<S160>/Chart' */
  uint8_t is_c3_FOC_MTPA_FWC_FF;       /* '<S160>/Chart' */
  bool icLoad;                         /* '<S8>/Delay' */
  bool icLoad_p;                       /* '<S156>/Delay' */
  bool icLoad_l;                       /* '<S157>/Delay' */
  bool icLoad_k;                       /* '<S3>/Delay' */
} DW_FOC_MTPA_FWC_FF_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  double Ref_Speed_mech_rpm;           /* '<Root>/Ref_Speed_mech_rpm' */
  float Ref_Speed_rate_up;             /* '<Root>/Ref_Speed_rate_up' */
  float Ref_Speed_rate_down;           /* '<Root>/Ref_Speed_rate_down' */
  double MtrSpd;                       /* '<Root>/Actual Speed_mech_rpm' */
  double MtrElcPos;                    /* '<Root>/angle' */
  double PhaseCurrent[3];              /* '<Root>/Phase Current' */
  PID_MTPABus MTPA_PID;                /* '<Root>/MTPA_PID' */
  Rate_limiterBus Rate_limiter;        /* '<Root>/Rate_limiter' */
  IIR_FilterBus IIR_Filter_Coefficient;/* '<Root>/IIR_Filter_Coefficient' */
  double Rs;                           /* '<Root>/Rs' */
  double Ld;                           /* '<Root>/Ld' */
  double Lq;                           /* '<Root>/Lq' */
  double Lambda;                       /* '<Root>/Lambda' */
  float p;                             /* '<Root>/Pole_pairs' */
  float BusVoltage_V;                  /* '<Root>/Bus_Voltage' */
  Id_Iq_MTPA_limitBus Id_Iq_MTPA_limit;/* '<Root>/Id_Iq_MTPA_limit' */
  double Iq_Torque_ratio;              /* '<Root>/Iq_Torque_ratio' */
  float Speed_1_Torque_0;              /* '<Root>/Speed_1_Torque_0' */
  float RefTrq;                        /* '<Root>/T_ref' */
  double Is_max;                       /* '<Root>/Is_max' */
  float Drive_State;                   /* '<Root>/Drive_State' */
} ExtU_FOC_MTPA_FWC_FF_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  float Va;                            /* '<Root>/Va' */
  float Vb;                            /* '<Root>/Vb' */
  float Vc;                            /* '<Root>/Vc' */
  float Id;                            /* '<Root>/Id' */
  float Iq;                            /* '<Root>/Iq' */
  float Iq_ref_final;                  /* '<Root>/Iq_ref_final' */
  float Id_ref_final;                  /* '<Root>/Id_ref_final' */
  float Iq_gen;                        /* '<Root>/Iq_gen' */
  float Vd_PID;                        /* '<Root>/Vd_PID' */
  float Vq_PID;                        /* '<Root>/Vq_PID' */
  float Vd;                            /* '<Root>/Vd' */
  float Vq;                            /* '<Root>/Vq' */
  float Id_error;                      /* '<Root>/Id_error' */
  float Iq_error;                      /* '<Root>/Iq_error' */
  float Speed_error;                   /* '<Root>/Speed_error' */
  float Iq_PID;                        /* '<Root>/Iq_PID' */
  float Id_ref_MTPA;                   /* '<Root>/Id_ref_MTPA' */
  float Iq_ref_MTPA;                   /* '<Root>/Iq_ref_MTPA' */
  float V_s;                           /* '<Root>/V_s' */
  float V_max;                         /* '<Root>/V_max' */
  double MTPA_FWC_condition;           /* '<Root>/MTPA_FWC_condition' */
} ExtY_FOC_MTPA_FWC_FF_T;

/* Real-time Model Data Structure */
struct tag_RTM_FOC_MTPA_FWC_FF_T {
  const char * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_FOC_MTPA_FWC_FF_T FOC_MTPA_FWC_FF_B;

/* Block states (default storage) */
extern DW_FOC_MTPA_FWC_FF_T FOC_MTPA_FWC_FF_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_FOC_MTPA_FWC_FF_T FOC_MTPA_FWC_FF_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_FOC_MTPA_FWC_FF_T FOC_MTPA_FWC_FF_Y;

/* Model entry point functions */
extern void FOC_MTPA_FWC_FF_initialize(void);
extern void FOC_MTPA_FWC_FF_step0(void);/* Sample time: [0.0001s, 0.0s] */
extern void FOC_MTPA_FWC_FF_step1(void);/* Sample time: [0.001s, 0.0s] */
extern void FOC_MTPA_FWC_FF_terminate(void);

/* Real-time Model object */
extern RT_MODEL_FOC_MTPA_FWC_FF_T *const FOC_MTPA_FWC_FF_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S15>/Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/Data Type Conversion2' : Unused code path elimination
 * Block '<S4>/Data Type Conversion3' : Unused code path elimination
 * Block '<S11>/Data Type Duplicate' : Unused code path elimination
 * Block '<S12>/Data Type Duplicate' : Unused code path elimination
 * Block '<S22>/Data Type Duplicate' : Unused code path elimination
 * Block '<S22>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S2>/Display2' : Unused code path elimination
 * Block '<S30>/Data Type Duplicate' : Unused code path elimination
 * Block '<S32>/Data Type Duplicate' : Unused code path elimination
 * Block '<S33>/Data Type Duplicate' : Unused code path elimination
 * Block '<S25>/Data Type Duplicate' : Unused code path elimination
 * Block '<S25>/Data Type Propagation' : Unused code path elimination
 * Block '<S26>/Data Type Duplicate' : Unused code path elimination
 * Block '<S26>/Data Type Propagation' : Unused code path elimination
 * Block '<S77>/Data Type Duplicate' : Unused code path elimination
 * Block '<S77>/Data Type Propagation' : Unused code path elimination
 * Block '<S131>/Data Type Duplicate' : Unused code path elimination
 * Block '<S131>/Data Type Propagation' : Unused code path elimination
 * Block '<S28>/Scope' : Unused code path elimination
 * Block '<S145>/Data Type Duplicate' : Unused code path elimination
 * Block '<S146>/Data Type Duplicate' : Unused code path elimination
 * Block '<S146>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S144>/Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/Scope' : Unused code path elimination
 * Block '<S154>/Display' : Unused code path elimination
 * Block '<S167>/Data Type Duplicate' : Unused code path elimination
 * Block '<S167>/Data Type Propagation' : Unused code path elimination
 * Block '<S168>/Data Type Duplicate' : Unused code path elimination
 * Block '<S168>/Data Type Propagation' : Unused code path elimination
 * Block '<S156>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S169>/Data Type Duplicate' : Unused code path elimination
 * Block '<S169>/Data Type Propagation' : Unused code path elimination
 * Block '<S157>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S170>/Data Type Duplicate' : Unused code path elimination
 * Block '<S170>/Data Type Propagation' : Unused code path elimination
 * Block '<S158>/Data Type Duplicate' : Unused code path elimination
 * Block '<S158>/Data Type Propagation' : Unused code path elimination
 * Block '<S159>/Data Type Duplicate' : Unused code path elimination
 * Block '<S159>/Data Type Propagation' : Unused code path elimination
 * Block '<S8>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S175>/Data Type Duplicate' : Unused code path elimination
 * Block '<S175>/Data Type Propagation' : Unused code path elimination
 * Block '<S219>/Data Type Duplicate' : Unused code path elimination
 * Block '<S219>/Data Type Propagation' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S230>/Data Type Duplicate' : Unused code path elimination
 * Block '<S230>/Data Type Propagation' : Unused code path elimination
 * Block '<S14>/Kalpha' : Eliminated nontunable gain of 1
 * Block '<S14>/Kbeta' : Eliminated nontunable gain of 1
 * Block '<S30>/Gain' : Eliminated nontunable gain of 1
 * Block '<S31>/Gain' : Eliminated nontunable gain of 1
 * Block '<S31>/Gain1' : Eliminated nontunable gain of 1
 * Block '<S31>/Gain2' : Eliminated nontunable gain of 1
 * Block '<S30>/VdFF_si2pu' : Eliminated nontunable gain of 1
 * Block '<S30>/VqFF_si2pu' : Eliminated nontunable gain of 1
 * Block '<S30>/id_pu2si' : Eliminated nontunable gain of 1
 * Block '<S30>/iq_pu2si' : Eliminated nontunable gain of 1
 * Block '<S27>/Data Type Conversion10' : Eliminate redundant data type conversion
 * Block '<S27>/Data Type Conversion11' : Eliminate redundant data type conversion
 * Block '<S27>/Data Type Conversion6' : Eliminate redundant data type conversion
 * Block '<S27>/Data Type Conversion7' : Eliminate redundant data type conversion
 * Block '<S27>/Data Type Conversion8' : Eliminate redundant data type conversion
 * Block '<S27>/Data Type Conversion9' : Eliminate redundant data type conversion
 * Block '<S61>/Kb' : Eliminated nontunable gain of 1
 * Block '<S28>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S28>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S28>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S28>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S28>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S28>/Data Type Conversion5' : Eliminate redundant data type conversion
 * Block '<S115>/Kb' : Eliminated nontunable gain of 1
 * Block '<S135>/Kt' : Eliminated nontunable gain of 1
 * Block '<S145>/Ka' : Eliminated nontunable gain of 1
 * Block '<S145>/Kb' : Eliminated nontunable gain of 1
 * Block '<S145>/Kc' : Eliminated nontunable gain of 1
 * Block '<S156>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S157>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S8>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S2>/Rate Transition' : Eliminated since input and output rates are identical
 * Block '<S203>/Kb' : Eliminated nontunable gain of 1
 * Block '<S223>/Kt' : Eliminated nontunable gain of 1
 * Block '<S3>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S11>/FilterConstant' : Unused code path elimination
 * Block '<S11>/OneMinusFilterConstant' : Unused code path elimination
 * Block '<S11>/UseInputPort' : Unused code path elimination
 * Block '<S12>/FilterConstant' : Unused code path elimination
 * Block '<S12>/OneMinusFilterConstant' : Unused code path elimination
 * Block '<S12>/UseInputPort' : Unused code path elimination
 * Block '<S30>/Constant' : Unused code path elimination
 * Block '<S31>/Constant' : Unused code path elimination
 * Block '<S31>/Constant1' : Unused code path elimination
 * Block '<S31>/Constant2' : Unused code path elimination
 * Block '<S31>/FluxPM_lumped' : Unused code path elimination
 * Block '<S31>/Ld_lumped' : Unused code path elimination
 * Block '<S31>/Lq_lumped' : Unused code path elimination
 * Block '<S30>/vsat_mask_input' : Unused code path elimination
 * Block '<S147>/Offset' : Unused code path elimination
 * Block '<S147>/Unary_Minus' : Unused code path elimination
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
 * hilite_system('IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF')    - opens subsystem IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF
 * hilite_system('IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW'
 * '<S1>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF'
 * '<S2>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC'
 * '<S3>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Subsystem'
 * '<S4>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Clarke_Park'
 * '<S5>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop'
 * '<S6>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inverse_Clarke_Park'
 * '<S7>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC'
 * '<S8>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Rate Limiter Dynamic'
 * '<S9>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem'
 * '<S10>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Clarke_Park/Clarke Transform'
 * '<S11>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Clarke_Park/IIR Filter'
 * '<S12>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Clarke_Park/IIR Filter1'
 * '<S13>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Clarke_Park/Park Transform'
 * '<S14>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Clarke_Park/Clarke Transform/Two phase input'
 * '<S15>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Clarke_Park/Clarke Transform/Two phase input/Two phase CRL wrap'
 * '<S16>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Clarke_Park/IIR Filter/IIR Filter'
 * '<S17>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Clarke_Park/IIR Filter/IIR Filter/Low-pass'
 * '<S18>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Clarke_Park/IIR Filter/IIR Filter/Low-pass/IIR Low Pass Filter'
 * '<S19>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Clarke_Park/IIR Filter1/IIR Filter'
 * '<S20>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Clarke_Park/IIR Filter1/IIR Filter/Low-pass'
 * '<S21>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Clarke_Park/IIR Filter1/IIR Filter/Low-pass/IIR Low Pass Filter'
 * '<S22>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Clarke_Park/Park Transform/Two inputs CRL'
 * '<S23>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Clarke_Park/Park Transform/Two inputs CRL/Switch_Axis'
 * '<S24>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/PMSM FeedForward Control'
 * '<S25>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Saturation Dynamic'
 * '<S26>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Saturation Dynamic1'
 * '<S27>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem'
 * '<S28>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1'
 * '<S29>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/PMSM FeedForward Control/FeedForward Control Selection'
 * '<S30>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/PMSM FeedForward Control/FeedForward Control Selection/Linear FeedForward_LumpedParameter_InputPort'
 * '<S31>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/PMSM FeedForward Control/FeedForward Control Selection/Linear FeedForward_LumpedParameter_InputPort/LumpedParams_InpurPorts'
 * '<S32>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/PMSM FeedForward Control/FeedForward Control Selection/Linear FeedForward_LumpedParameter_InputPort/Vd_sat'
 * '<S33>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/PMSM FeedForward Control/FeedForward Control Selection/Linear FeedForward_LumpedParameter_InputPort/Vq_sat'
 * '<S34>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq'
 * '<S35>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Anti-windup'
 * '<S36>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/D Gain'
 * '<S37>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/External Derivative'
 * '<S38>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Filter'
 * '<S39>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Filter ICs'
 * '<S40>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/I Gain'
 * '<S41>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Ideal P Gain'
 * '<S42>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Ideal P Gain Fdbk'
 * '<S43>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Integrator'
 * '<S44>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Integrator ICs'
 * '<S45>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/N Copy'
 * '<S46>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/N Gain'
 * '<S47>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/P Copy'
 * '<S48>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Parallel P Gain'
 * '<S49>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Reset Signal'
 * '<S50>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Saturation'
 * '<S51>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Saturation Fdbk'
 * '<S52>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Sum'
 * '<S53>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Sum Fdbk'
 * '<S54>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Tracking Mode'
 * '<S55>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Tracking Mode Sum'
 * '<S56>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Tsamp - Integral'
 * '<S57>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Tsamp - Ngain'
 * '<S58>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/postSat Signal'
 * '<S59>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/preInt Signal'
 * '<S60>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/preSat Signal'
 * '<S61>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Anti-windup/Back Calculation'
 * '<S62>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/D Gain/External Parameters'
 * '<S63>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/External Derivative/Error'
 * '<S64>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Filter/Disc. Forward Euler Filter'
 * '<S65>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Filter ICs/Internal IC - Filter'
 * '<S66>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/I Gain/External Parameters'
 * '<S67>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Ideal P Gain/Passthrough'
 * '<S68>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Ideal P Gain Fdbk/Disabled'
 * '<S69>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Integrator/Discrete'
 * '<S70>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Integrator ICs/Internal IC'
 * '<S71>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/N Copy/Disabled'
 * '<S72>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/N Gain/External Parameters'
 * '<S73>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/P Copy/Disabled'
 * '<S74>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Parallel P Gain/External Parameters'
 * '<S75>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Reset Signal/Disabled'
 * '<S76>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Saturation/External'
 * '<S77>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Saturation/External/Saturation Dynamic'
 * '<S78>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Saturation Fdbk/Disabled'
 * '<S79>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Sum/Sum_PID'
 * '<S80>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Sum Fdbk/Disabled'
 * '<S81>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Tracking Mode/Enabled'
 * '<S82>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Tracking Mode Sum/Tracking Mode'
 * '<S83>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Tsamp - Integral/TsSignalSpecification'
 * '<S84>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/Tsamp - Ngain/Passthrough'
 * '<S85>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/postSat Signal/Forward_Path'
 * '<S86>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/preInt Signal/Internal PreInt'
 * '<S87>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem/PI Vq/preSat Signal/Forward_Path'
 * '<S88>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd'
 * '<S89>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Anti-windup'
 * '<S90>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/D Gain'
 * '<S91>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/External Derivative'
 * '<S92>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Filter'
 * '<S93>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Filter ICs'
 * '<S94>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/I Gain'
 * '<S95>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain'
 * '<S96>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain Fdbk'
 * '<S97>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Integrator'
 * '<S98>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Integrator ICs'
 * '<S99>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/N Copy'
 * '<S100>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/N Gain'
 * '<S101>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/P Copy'
 * '<S102>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Parallel P Gain'
 * '<S103>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Reset Signal'
 * '<S104>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Saturation'
 * '<S105>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Saturation Fdbk'
 * '<S106>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Sum'
 * '<S107>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Sum Fdbk'
 * '<S108>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Tracking Mode'
 * '<S109>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Tracking Mode Sum'
 * '<S110>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Tsamp - Integral'
 * '<S111>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Tsamp - Ngain'
 * '<S112>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/postSat Signal'
 * '<S113>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/preInt Signal'
 * '<S114>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/preSat Signal'
 * '<S115>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Anti-windup/Back Calculation'
 * '<S116>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/D Gain/External Parameters'
 * '<S117>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/External Derivative/Error'
 * '<S118>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Filter/Disc. Forward Euler Filter'
 * '<S119>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Filter ICs/Internal IC - Filter'
 * '<S120>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/I Gain/External Parameters'
 * '<S121>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain/Passthrough'
 * '<S122>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain Fdbk/Disabled'
 * '<S123>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Integrator/Discrete'
 * '<S124>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Integrator ICs/Internal IC'
 * '<S125>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/N Copy/Disabled'
 * '<S126>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/N Gain/External Parameters'
 * '<S127>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/P Copy/Disabled'
 * '<S128>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Parallel P Gain/External Parameters'
 * '<S129>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Reset Signal/Disabled'
 * '<S130>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Saturation/External'
 * '<S131>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Saturation/External/Saturation Dynamic'
 * '<S132>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Saturation Fdbk/Disabled'
 * '<S133>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Sum/Sum_PID'
 * '<S134>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Sum Fdbk/Disabled'
 * '<S135>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Tracking Mode/Enabled'
 * '<S136>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Tracking Mode Sum/Tracking Mode'
 * '<S137>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Tsamp - Integral/TsSignalSpecification'
 * '<S138>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/Tsamp - Ngain/Passthrough'
 * '<S139>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/postSat Signal/Forward_Path'
 * '<S140>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/preInt Signal/Internal PreInt'
 * '<S141>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inner PID loop/Subsystem1/PI Vd/preSat Signal/Forward_Path'
 * '<S142>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inverse_Clarke_Park/Inverse Clarke Transform'
 * '<S143>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inverse_Clarke_Park/Inverse Park Transform'
 * '<S144>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inverse_Clarke_Park/PWM Reference Generator'
 * '<S145>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inverse_Clarke_Park/Inverse Clarke Transform/Two phase input'
 * '<S146>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inverse_Clarke_Park/Inverse Park Transform/Two inputs CRL'
 * '<S147>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inverse_Clarke_Park/Inverse Park Transform/Two inputs CRL/Switch_Axis'
 * '<S148>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inverse_Clarke_Park/PWM Reference Generator/Modulation method'
 * '<S149>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inverse_Clarke_Park/PWM Reference Generator/Voltage Input'
 * '<S150>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inverse_Clarke_Park/PWM Reference Generator/Modulation method/SVPWM'
 * '<S151>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inverse_Clarke_Park/PWM Reference Generator/Modulation method/SVPWM/Half(Vmin+Vmax)'
 * '<S152>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Inverse_Clarke_Park/PWM Reference Generator/Voltage Input/Vabc'
 * '<S153>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/If Action Subsystem'
 * '<S154>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/If Action Subsystem1'
 * '<S155>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/MTPA'
 * '<S156>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/Rate Limiter Dynamic'
 * '<S157>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/Rate Limiter Dynamic1'
 * '<S158>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/Saturation Dynamic'
 * '<S159>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/Saturation Dynamic1'
 * '<S160>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/Subsystem'
 * '<S161>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/Subsystem1'
 * '<S162>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/If Action Subsystem1/PMSM Field-Weakening Controller'
 * '<S163>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/If Action Subsystem1/PMSM Field-Weakening Controller/Cartesian to Polar'
 * '<S164>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/If Action Subsystem1/PMSM Field-Weakening Controller/Modulation index'
 * '<S165>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/If Action Subsystem1/PMSM Field-Weakening Controller/Polar to Cartesian'
 * '<S166>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/If Action Subsystem1/PMSM Field-Weakening Controller/Modulation index/Prevent division by 0'
 * '<S167>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/MTPA/Saturation Dynamic'
 * '<S168>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/MTPA/Saturation Dynamic1'
 * '<S169>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S170>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/Rate Limiter Dynamic1/Saturation Dynamic'
 * '<S171>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/Subsystem/Chart'
 * '<S172>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/Subsystem1/If Action Subsystem'
 * '<S173>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/Subsystem1/If Action Subsystem1'
 * '<S174>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/MTPA_FWC/Subsystem1/If Action Subsystem2'
 * '<S175>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S176>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd'
 * '<S177>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Anti-windup'
 * '<S178>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/D Gain'
 * '<S179>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/External Derivative'
 * '<S180>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Filter'
 * '<S181>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Filter ICs'
 * '<S182>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/I Gain'
 * '<S183>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Ideal P Gain'
 * '<S184>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Ideal P Gain Fdbk'
 * '<S185>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Integrator'
 * '<S186>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Integrator ICs'
 * '<S187>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/N Copy'
 * '<S188>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/N Gain'
 * '<S189>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/P Copy'
 * '<S190>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Parallel P Gain'
 * '<S191>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Reset Signal'
 * '<S192>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Saturation'
 * '<S193>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Saturation Fdbk'
 * '<S194>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Sum'
 * '<S195>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Sum Fdbk'
 * '<S196>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Tracking Mode'
 * '<S197>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Tracking Mode Sum'
 * '<S198>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Tsamp - Integral'
 * '<S199>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Tsamp - Ngain'
 * '<S200>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/postSat Signal'
 * '<S201>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/preInt Signal'
 * '<S202>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/preSat Signal'
 * '<S203>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Anti-windup/Back Calculation'
 * '<S204>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/D Gain/External Parameters'
 * '<S205>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/External Derivative/Error'
 * '<S206>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Filter/Disc. Forward Euler Filter'
 * '<S207>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Filter ICs/Internal IC - Filter'
 * '<S208>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/I Gain/External Parameters'
 * '<S209>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Ideal P Gain/Passthrough'
 * '<S210>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Ideal P Gain Fdbk/Disabled'
 * '<S211>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Integrator/Discrete'
 * '<S212>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Integrator ICs/Internal IC'
 * '<S213>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/N Copy/Disabled'
 * '<S214>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/N Gain/External Parameters'
 * '<S215>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/P Copy/Disabled'
 * '<S216>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Parallel P Gain/External Parameters'
 * '<S217>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Reset Signal/Disabled'
 * '<S218>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Saturation/External'
 * '<S219>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Saturation/External/Saturation Dynamic'
 * '<S220>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Saturation Fdbk/Disabled'
 * '<S221>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Sum/Sum_PID'
 * '<S222>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Sum Fdbk/Disabled'
 * '<S223>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Tracking Mode/Enabled'
 * '<S224>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Tracking Mode Sum/Tracking Mode'
 * '<S225>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Tsamp - Integral/TsSignalSpecification'
 * '<S226>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/Tsamp - Ngain/Passthrough'
 * '<S227>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/postSat Signal/Forward_Path'
 * '<S228>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/preInt Signal/Internal PreInt'
 * '<S229>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/FOC_MTPA_FWC/Subsystem/PI Vd/preSat Signal/Forward_Path'
 * '<S230>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Subsystem/Saturation Dynamic'
 */
#endif                                 /* FOC_MTPA_FWC_FF_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
