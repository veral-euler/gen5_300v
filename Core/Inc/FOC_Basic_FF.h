/*
 * File: FOC_Basic_FF.h
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

#ifndef FOC_Basic_FF_h_
#define FOC_Basic_FF_h_
#ifndef FOC_Basic_FF_COMMON_INCLUDES_
#define FOC_Basic_FF_COMMON_INCLUDES_
#include <stdbool.h>
#include <stdint.h>
#include "complex_types.h"
#include "math.h"
#include "main.h"
#endif                                 /* FOC_Basic_FF_COMMON_INCLUDES_ */

#include "FOC_Basic_FF_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  double Integrator_DSTATE;            /* '<S122>/Integrator' */
  double Filter_DSTATE;                /* '<S117>/Filter' */
  double Integrator_DSTATE_h;          /* '<S68>/Integrator' */
  double Filter_DSTATE_d;              /* '<S63>/Filter' */
  double Delay_DSTATE;                 /* '<S3>/Delay' */
  double Integrator_DSTATE_b;          /* '<S188>/Integrator' */
  double Filter_DSTATE_i;              /* '<S183>/Filter' */
  double Delay_DSTATE_h;               /* '<S7>/Delay' */
  double RateTransition_Buffer0;       /* '<S2>/Rate Transition' */
  float UnitDelay_DSTATE;              /* '<S17>/Unit Delay' */
  float UnitDelay_DSTATE_f;            /* '<S20>/Unit Delay' */
  bool icLoad;                         /* '<S3>/Delay' */
  bool icLoad_p;                       /* '<S7>/Delay' */
} DW_FOC_Basic_FF_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  double Ref_Speed_mech_rpm;           /* '<Root>/Ref_Speed_mech_rpm' */
  double Ref_Speed_rate_up;            /* '<Root>/Ref_Speed_rate_up' */
  double Ref_Speed_rate_down;          /* '<Root>/Ref_Speed_rate_down' */
  double MtrSpd;                       /* '<Root>/Actual Speed_mech_rad//sec' */
  double MtrElcPos;                    /* '<Root>/angle' */
  double PhaseCurrent[3];              /* '<Root>/Phase Current' */
  PID_MTPABus MTPA_PID;                /* '<Root>/MTPA_PID' */
  Rate_limiterBus Rate_limiter;        /* '<Root>/Rate_limiter' */
  IIR_FilterBus IIR_Filter_Coefficient;/* '<Root>/IIR_Filter_Coefficient' */
  double Id_ref_in;                    /* '<Root>/Id_ref_in' */
  double Ld;                           /* '<Root>/Ld' */
  double Lq;                           /* '<Root>/Lq' */
  double Lambda;                       /* '<Root>/Lambda' */
  float BusVoltage_V;                  /* '<Root>/Bus_Voltage' */
} ExtU_FOC_Basic_FF_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  double Va;                           /* '<Root>/Va' */
  double Vb;                           /* '<Root>/Vb' */
  double Vc;                           /* '<Root>/Vc' */
  double Id;                           /* '<Root>/Id' */
  double Iq;                           /* '<Root>/Iq' */
  double Iq_ref;                       /* '<Root>/Iq_ref' */
  double Id_ref;                       /* '<Root>/Id_ref' */
  double Iq_gen;                       /* '<Root>/Iq_gen' */
  double Vd_PID;                       /* '<Root>/Vd_PID' */
  double Vq_PID;                       /* '<Root>/Vq_PID' */
  double Vd;                           /* '<Root>/Vd' */
  double Vq;                           /* '<Root>/Vq' */
  double Id_error;                     /* '<Root>/Id_error' */
  double Iq_error;                     /* '<Root>/Iq_error' */
  double Speed_error;                  /* '<Root>/Speed_error' */
} ExtY_FOC_Basic_FF_T;

/* Real-time Model Data Structure */
struct tag_RTM_FOC_Basic_FF_T {
  const char * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint8_t TID0_1;
    } RateInteraction;
  } Timing;
};

/* Block states (default storage) */
extern DW_FOC_Basic_FF_T FOC_Basic_FF_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_FOC_Basic_FF_T FOC_Basic_FF_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_FOC_Basic_FF_T FOC_Basic_FF_Y;

/* Model entry point functions */
extern void FOC_Basic_FF_initialize(void);
extern void FOC_Basic_FF_step0(void);  /* Sample time: [0.0001s, 0.0s] */
extern void FOC_Basic_FF_step1(void);  /* Sample time: [0.001s, 0.0s] */
extern void FOC_Basic_FF_terminate(void);

/* Real-time Model object */
extern RT_MODEL_FOC_Basic_FF_T *const FOC_Basic_FF_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S14>/Data Type Duplicate' : Unused code path elimination
 * Block '<S10>/Data Type Duplicate' : Unused code path elimination
 * Block '<S11>/Data Type Duplicate' : Unused code path elimination
 * Block '<S21>/Data Type Duplicate' : Unused code path elimination
 * Block '<S21>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S2>/Display' : Unused code path elimination
 * Block '<S2>/Display2' : Unused code path elimination
 * Block '<S29>/Data Type Duplicate' : Unused code path elimination
 * Block '<S31>/Data Type Duplicate' : Unused code path elimination
 * Block '<S32>/Data Type Duplicate' : Unused code path elimination
 * Block '<S24>/Data Type Duplicate' : Unused code path elimination
 * Block '<S24>/Data Type Propagation' : Unused code path elimination
 * Block '<S25>/Data Type Duplicate' : Unused code path elimination
 * Block '<S25>/Data Type Propagation' : Unused code path elimination
 * Block '<S76>/Data Type Duplicate' : Unused code path elimination
 * Block '<S76>/Data Type Propagation' : Unused code path elimination
 * Block '<S130>/Data Type Duplicate' : Unused code path elimination
 * Block '<S130>/Data Type Propagation' : Unused code path elimination
 * Block '<S27>/Scope' : Unused code path elimination
 * Block '<S144>/Data Type Duplicate' : Unused code path elimination
 * Block '<S145>/Data Type Duplicate' : Unused code path elimination
 * Block '<S145>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S143>/Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/Scope' : Unused code path elimination
 * Block '<S7>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S152>/Data Type Duplicate' : Unused code path elimination
 * Block '<S152>/Data Type Propagation' : Unused code path elimination
 * Block '<S196>/Data Type Duplicate' : Unused code path elimination
 * Block '<S196>/Data Type Propagation' : Unused code path elimination
 * Block '<S3>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S207>/Data Type Duplicate' : Unused code path elimination
 * Block '<S207>/Data Type Propagation' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S1>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S13>/Kalpha' : Eliminated nontunable gain of 1
 * Block '<S13>/Kbeta' : Eliminated nontunable gain of 1
 * Block '<S29>/Gain' : Eliminated nontunable gain of 1
 * Block '<S30>/Gain' : Eliminated nontunable gain of 1
 * Block '<S30>/Gain1' : Eliminated nontunable gain of 1
 * Block '<S30>/Gain2' : Eliminated nontunable gain of 1
 * Block '<S29>/VdFF_si2pu' : Eliminated nontunable gain of 1
 * Block '<S29>/VqFF_si2pu' : Eliminated nontunable gain of 1
 * Block '<S29>/id_pu2si' : Eliminated nontunable gain of 1
 * Block '<S29>/iq_pu2si' : Eliminated nontunable gain of 1
 * Block '<S60>/Kb' : Eliminated nontunable gain of 1
 * Block '<S114>/Kb' : Eliminated nontunable gain of 1
 * Block '<S134>/Kt' : Eliminated nontunable gain of 1
 * Block '<S144>/Ka' : Eliminated nontunable gain of 1
 * Block '<S144>/Kb' : Eliminated nontunable gain of 1
 * Block '<S144>/Kc' : Eliminated nontunable gain of 1
 * Block '<S7>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S180>/Kb' : Eliminated nontunable gain of 1
 * Block '<S200>/Kt' : Eliminated nontunable gain of 1
 * Block '<S3>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S10>/FilterConstant' : Unused code path elimination
 * Block '<S10>/OneMinusFilterConstant' : Unused code path elimination
 * Block '<S10>/UseInputPort' : Unused code path elimination
 * Block '<S11>/FilterConstant' : Unused code path elimination
 * Block '<S11>/OneMinusFilterConstant' : Unused code path elimination
 * Block '<S11>/UseInputPort' : Unused code path elimination
 * Block '<S29>/Constant' : Unused code path elimination
 * Block '<S30>/Constant' : Unused code path elimination
 * Block '<S30>/Constant1' : Unused code path elimination
 * Block '<S30>/Constant2' : Unused code path elimination
 * Block '<S30>/FluxPM_lumped' : Unused code path elimination
 * Block '<S30>/Ld_lumped' : Unused code path elimination
 * Block '<S30>/Lq_lumped' : Unused code path elimination
 * Block '<S29>/vsat_mask_input' : Unused code path elimination
 * Block '<S146>/Offset' : Unused code path elimination
 * Block '<S146>/Unary_Minus' : Unused code path elimination
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
 * hilite_system('IPMSM_motor_FOC_V1_FF/FOC_Basic_FF')    - opens subsystem IPMSM_motor_FOC_V1_FF/FOC_Basic_FF
 * hilite_system('IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'IPMSM_motor_FOC_V1_FF'
 * '<S1>'   : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF'
 * '<S2>'   : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA'
 * '<S3>'   : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/Rate Limiter Dynamic'
 * '<S4>'   : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Clarke_Park'
 * '<S5>'   : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop'
 * '<S6>'   : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inverse_Clarke_Park'
 * '<S7>'   : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Rate Limiter Dynamic'
 * '<S8>'   : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem'
 * '<S9>'   : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Clarke_Park/Clarke Transform'
 * '<S10>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Clarke_Park/IIR Filter'
 * '<S11>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Clarke_Park/IIR Filter1'
 * '<S12>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Clarke_Park/Park Transform'
 * '<S13>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Clarke_Park/Clarke Transform/Two phase input'
 * '<S14>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Clarke_Park/Clarke Transform/Two phase input/Two phase CRL wrap'
 * '<S15>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Clarke_Park/IIR Filter/IIR Filter'
 * '<S16>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Clarke_Park/IIR Filter/IIR Filter/Low-pass'
 * '<S17>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Clarke_Park/IIR Filter/IIR Filter/Low-pass/IIR Low Pass Filter'
 * '<S18>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Clarke_Park/IIR Filter1/IIR Filter'
 * '<S19>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Clarke_Park/IIR Filter1/IIR Filter/Low-pass'
 * '<S20>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Clarke_Park/IIR Filter1/IIR Filter/Low-pass/IIR Low Pass Filter'
 * '<S21>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Clarke_Park/Park Transform/Two inputs CRL'
 * '<S22>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Clarke_Park/Park Transform/Two inputs CRL/Switch_Axis'
 * '<S23>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/PMSM FeedForward Control'
 * '<S24>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Saturation Dynamic'
 * '<S25>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Saturation Dynamic1'
 * '<S26>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem'
 * '<S27>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1'
 * '<S28>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/PMSM FeedForward Control/FeedForward Control Selection'
 * '<S29>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/PMSM FeedForward Control/FeedForward Control Selection/Linear FeedForward_LumpedParameter_InputPort'
 * '<S30>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/PMSM FeedForward Control/FeedForward Control Selection/Linear FeedForward_LumpedParameter_InputPort/LumpedParams_InpurPorts'
 * '<S31>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/PMSM FeedForward Control/FeedForward Control Selection/Linear FeedForward_LumpedParameter_InputPort/Vd_sat'
 * '<S32>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/PMSM FeedForward Control/FeedForward Control Selection/Linear FeedForward_LumpedParameter_InputPort/Vq_sat'
 * '<S33>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq'
 * '<S34>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Anti-windup'
 * '<S35>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/D Gain'
 * '<S36>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/External Derivative'
 * '<S37>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Filter'
 * '<S38>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Filter ICs'
 * '<S39>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/I Gain'
 * '<S40>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Ideal P Gain'
 * '<S41>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Ideal P Gain Fdbk'
 * '<S42>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Integrator'
 * '<S43>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Integrator ICs'
 * '<S44>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/N Copy'
 * '<S45>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/N Gain'
 * '<S46>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/P Copy'
 * '<S47>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Parallel P Gain'
 * '<S48>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Reset Signal'
 * '<S49>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Saturation'
 * '<S50>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Saturation Fdbk'
 * '<S51>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Sum'
 * '<S52>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Sum Fdbk'
 * '<S53>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tracking Mode'
 * '<S54>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tracking Mode Sum'
 * '<S55>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tsamp - Integral'
 * '<S56>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tsamp - Ngain'
 * '<S57>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/postSat Signal'
 * '<S58>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/preInt Signal'
 * '<S59>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/preSat Signal'
 * '<S60>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Anti-windup/Back Calculation'
 * '<S61>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/D Gain/External Parameters'
 * '<S62>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/External Derivative/Error'
 * '<S63>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Filter/Disc. Forward Euler Filter'
 * '<S64>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Filter ICs/Internal IC - Filter'
 * '<S65>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/I Gain/External Parameters'
 * '<S66>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Ideal P Gain/Passthrough'
 * '<S67>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Ideal P Gain Fdbk/Disabled'
 * '<S68>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Integrator/Discrete'
 * '<S69>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Integrator ICs/Internal IC'
 * '<S70>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/N Copy/Disabled'
 * '<S71>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/N Gain/External Parameters'
 * '<S72>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/P Copy/Disabled'
 * '<S73>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Parallel P Gain/External Parameters'
 * '<S74>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Reset Signal/Disabled'
 * '<S75>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Saturation/External'
 * '<S76>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Saturation/External/Saturation Dynamic'
 * '<S77>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Saturation Fdbk/Disabled'
 * '<S78>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Sum/Sum_PID'
 * '<S79>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Sum Fdbk/Disabled'
 * '<S80>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tracking Mode/Enabled'
 * '<S81>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tracking Mode Sum/Tracking Mode'
 * '<S82>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tsamp - Integral/TsSignalSpecification'
 * '<S83>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tsamp - Ngain/Passthrough'
 * '<S84>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/postSat Signal/Forward_Path'
 * '<S85>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/preInt Signal/Internal PreInt'
 * '<S86>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/preSat Signal/Forward_Path'
 * '<S87>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd'
 * '<S88>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Anti-windup'
 * '<S89>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/D Gain'
 * '<S90>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/External Derivative'
 * '<S91>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Filter'
 * '<S92>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Filter ICs'
 * '<S93>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/I Gain'
 * '<S94>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain'
 * '<S95>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain Fdbk'
 * '<S96>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Integrator'
 * '<S97>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Integrator ICs'
 * '<S98>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/N Copy'
 * '<S99>'  : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/N Gain'
 * '<S100>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/P Copy'
 * '<S101>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Parallel P Gain'
 * '<S102>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Reset Signal'
 * '<S103>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Saturation'
 * '<S104>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Saturation Fdbk'
 * '<S105>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Sum'
 * '<S106>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Sum Fdbk'
 * '<S107>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tracking Mode'
 * '<S108>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tracking Mode Sum'
 * '<S109>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tsamp - Integral'
 * '<S110>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tsamp - Ngain'
 * '<S111>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/postSat Signal'
 * '<S112>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/preInt Signal'
 * '<S113>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/preSat Signal'
 * '<S114>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Anti-windup/Back Calculation'
 * '<S115>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/D Gain/External Parameters'
 * '<S116>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/External Derivative/Error'
 * '<S117>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Filter/Disc. Forward Euler Filter'
 * '<S118>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Filter ICs/Internal IC - Filter'
 * '<S119>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/I Gain/External Parameters'
 * '<S120>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain/Passthrough'
 * '<S121>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain Fdbk/Disabled'
 * '<S122>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Integrator/Discrete'
 * '<S123>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Integrator ICs/Internal IC'
 * '<S124>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/N Copy/Disabled'
 * '<S125>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/N Gain/External Parameters'
 * '<S126>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/P Copy/Disabled'
 * '<S127>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Parallel P Gain/External Parameters'
 * '<S128>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Reset Signal/Disabled'
 * '<S129>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Saturation/External'
 * '<S130>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Saturation/External/Saturation Dynamic'
 * '<S131>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Saturation Fdbk/Disabled'
 * '<S132>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Sum/Sum_PID'
 * '<S133>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Sum Fdbk/Disabled'
 * '<S134>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tracking Mode/Enabled'
 * '<S135>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tracking Mode Sum/Tracking Mode'
 * '<S136>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tsamp - Integral/TsSignalSpecification'
 * '<S137>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tsamp - Ngain/Passthrough'
 * '<S138>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/postSat Signal/Forward_Path'
 * '<S139>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/preInt Signal/Internal PreInt'
 * '<S140>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/preSat Signal/Forward_Path'
 * '<S141>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inverse_Clarke_Park/Inverse Clarke Transform'
 * '<S142>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inverse_Clarke_Park/Inverse Park Transform'
 * '<S143>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inverse_Clarke_Park/PWM Reference Generator'
 * '<S144>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inverse_Clarke_Park/Inverse Clarke Transform/Two phase input'
 * '<S145>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inverse_Clarke_Park/Inverse Park Transform/Two inputs CRL'
 * '<S146>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inverse_Clarke_Park/Inverse Park Transform/Two inputs CRL/Switch_Axis'
 * '<S147>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inverse_Clarke_Park/PWM Reference Generator/Modulation method'
 * '<S148>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inverse_Clarke_Park/PWM Reference Generator/Voltage Input'
 * '<S149>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inverse_Clarke_Park/PWM Reference Generator/Modulation method/SVPWM'
 * '<S150>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inverse_Clarke_Park/PWM Reference Generator/Modulation method/SVPWM/Half(Vmin+Vmax)'
 * '<S151>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Inverse_Clarke_Park/PWM Reference Generator/Voltage Input/Vabc'
 * '<S152>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S153>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd'
 * '<S154>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Anti-windup'
 * '<S155>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/D Gain'
 * '<S156>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/External Derivative'
 * '<S157>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Filter'
 * '<S158>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Filter ICs'
 * '<S159>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/I Gain'
 * '<S160>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Ideal P Gain'
 * '<S161>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Ideal P Gain Fdbk'
 * '<S162>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Integrator'
 * '<S163>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Integrator ICs'
 * '<S164>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/N Copy'
 * '<S165>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/N Gain'
 * '<S166>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/P Copy'
 * '<S167>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Parallel P Gain'
 * '<S168>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Reset Signal'
 * '<S169>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Saturation'
 * '<S170>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Saturation Fdbk'
 * '<S171>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Sum'
 * '<S172>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Sum Fdbk'
 * '<S173>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Tracking Mode'
 * '<S174>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Tracking Mode Sum'
 * '<S175>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Tsamp - Integral'
 * '<S176>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Tsamp - Ngain'
 * '<S177>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/postSat Signal'
 * '<S178>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/preInt Signal'
 * '<S179>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/preSat Signal'
 * '<S180>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Anti-windup/Back Calculation'
 * '<S181>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/D Gain/External Parameters'
 * '<S182>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/External Derivative/Error'
 * '<S183>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Filter/Disc. Forward Euler Filter'
 * '<S184>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Filter ICs/Internal IC - Filter'
 * '<S185>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/I Gain/External Parameters'
 * '<S186>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Ideal P Gain/Passthrough'
 * '<S187>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Ideal P Gain Fdbk/Disabled'
 * '<S188>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Integrator/Discrete'
 * '<S189>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Integrator ICs/Internal IC'
 * '<S190>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/N Copy/Disabled'
 * '<S191>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/N Gain/External Parameters'
 * '<S192>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/P Copy/Disabled'
 * '<S193>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Parallel P Gain/External Parameters'
 * '<S194>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Reset Signal/Disabled'
 * '<S195>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Saturation/External'
 * '<S196>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Saturation/External/Saturation Dynamic'
 * '<S197>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Saturation Fdbk/Disabled'
 * '<S198>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Sum/Sum_PID'
 * '<S199>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Sum Fdbk/Disabled'
 * '<S200>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Tracking Mode/Enabled'
 * '<S201>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Tracking Mode Sum/Tracking Mode'
 * '<S202>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Tsamp - Integral/TsSignalSpecification'
 * '<S203>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/Tsamp - Ngain/Passthrough'
 * '<S204>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/postSat Signal/Forward_Path'
 * '<S205>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/preInt Signal/Internal PreInt'
 * '<S206>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/FOC_MTPA/Subsystem/PI Vd/preSat Signal/Forward_Path'
 * '<S207>' : 'IPMSM_motor_FOC_V1_FF/FOC_Basic_FF/Rate Limiter Dynamic/Saturation Dynamic'
 */
#endif                                 /* FOC_Basic_FF_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
