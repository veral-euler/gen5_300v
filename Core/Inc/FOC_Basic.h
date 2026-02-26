/*
 * File: FOC_Basic.h
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

#ifndef FOC_Basic_h_
#define FOC_Basic_h_
#ifndef FOC_Basic_COMMON_INCLUDES_
#define FOC_Basic_COMMON_INCLUDES_
#include <stdbool.h>
#include <stdint.h>
#include "complex_types.h"
#include "math.h"
#include "main.h"
#endif                                 /* FOC_Basic_COMMON_INCLUDES_ */

#include "FOC_Basic_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  float Integrator_DSTATE;            /* '<S116>/Integrator' */
  float Filter_DSTATE;                /* '<S111>/Filter' */
  float Integrator_DSTATE_h;          /* '<S62>/Integrator' */
  float Filter_DSTATE_d;              /* '<S57>/Filter' */
  float Delay_DSTATE;                 /* '<S3>/Delay' */
  float Integrator_DSTATE_b;          /* '<S182>/Integrator' */
  float Filter_DSTATE_i;              /* '<S177>/Filter' */
  float Delay_DSTATE_h;               /* '<S7>/Delay' */
  float RateTransition_Buffer0;       /* '<S2>/Rate Transition' */
  float UnitDelay_DSTATE;              /* '<S17>/Unit Delay' */
  float UnitDelay_DSTATE_f;            /* '<S20>/Unit Delay' */
  bool icLoad;                         /* '<S3>/Delay' */
  bool icLoad_p;                       /* '<S7>/Delay' */
} DW_FOC_Basic_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  float Ref_Speed_mech_rpm;           /* '<Root>/Ref_Speed_mech_rpm' */
  float Ref_Speed_rate_up;            /* '<Root>/Ref_Speed_rate_up' */
  float Ref_Speed_rate_down;          /* '<Root>/Ref_Speed_rate_down' */
  float MtrSpd;                       /* '<Root>/Actual Speed_mech_rad//sec' */
  float MtrElcPos;                    /* '<Root>/angle' */
  float PhaseCurrent[3];              /* '<Root>/Phase Current' */
  PID_MTPABus MTPA_PID;                /* '<Root>/MTPA_PID' */
  Rate_limiterBus Rate_limiter;        /* '<Root>/Rate_limiter' */
  IIR_FilterBus IIR_Filter_Coefficient;/* '<Root>/IIR_Filter_Coefficient' */
  float Id_ref_in;                    /* '<Root>/Id_ref_in' */
} ExtU_FOC_Basic_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  float Va;                           /* '<Root>/Va' */
  float Vb;                           /* '<Root>/Vb' */
  float Vc;                           /* '<Root>/Vc' */
  float Id;                           /* '<Root>/Id' */
  float Iq;                           /* '<Root>/Iq' */
  float Iq_ref;                       /* '<Root>/Iq_ref' */
  float Id_ref;                       /* '<Root>/Id_ref' */
  float Iq_gen;                       /* '<Root>/Iq_gen' */
  float Vd_PID;                       /* '<Root>/Vd_PID' */
  float Vq_PID;                       /* '<Root>/Vq_PID' */
  float Vd;                           /* '<Root>/Vd' */
  float Vq;                           /* '<Root>/Vq' */
  float Id_error;                     /* '<Root>/Id_error' */
  float Iq_error;                     /* '<Root>/Iq_error' */
  float Speed_error;                  /* '<Root>/Speed_error' */
} ExtY_FOC_Basic_T;

/* Real-time Model Data Structure */
struct tag_RTM_FOC_Basic_T {
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
extern DW_FOC_Basic_T FOC_Basic_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_FOC_Basic_T FOC_Basic_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_FOC_Basic_T FOC_Basic_Y;

/* Model entry point functions */
extern void FOC_Basic_initialize(void);
extern void FOC_Basic_step0(void);     /* Sample time: [0.0001s, 0.0s] */
extern void FOC_Basic_step1(void);     /* Sample time: [0.001s, 0.0s] */
extern void FOC_Basic_terminate(void);

/* Real-time Model object */
extern RT_MODEL_FOC_Basic_T *const FOC_Basic_M;

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
 * Block '<S23>/Data Type Duplicate' : Unused code path elimination
 * Block '<S23>/Data Type Propagation' : Unused code path elimination
 * Block '<S24>/Data Type Duplicate' : Unused code path elimination
 * Block '<S24>/Data Type Propagation' : Unused code path elimination
 * Block '<S70>/Data Type Duplicate' : Unused code path elimination
 * Block '<S70>/Data Type Propagation' : Unused code path elimination
 * Block '<S124>/Data Type Duplicate' : Unused code path elimination
 * Block '<S124>/Data Type Propagation' : Unused code path elimination
 * Block '<S26>/Scope' : Unused code path elimination
 * Block '<S138>/Data Type Duplicate' : Unused code path elimination
 * Block '<S139>/Data Type Duplicate' : Unused code path elimination
 * Block '<S139>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S137>/Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/Scope' : Unused code path elimination
 * Block '<S7>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S146>/Data Type Duplicate' : Unused code path elimination
 * Block '<S146>/Data Type Propagation' : Unused code path elimination
 * Block '<S190>/Data Type Duplicate' : Unused code path elimination
 * Block '<S190>/Data Type Propagation' : Unused code path elimination
 * Block '<S3>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S201>/Data Type Duplicate' : Unused code path elimination
 * Block '<S201>/Data Type Propagation' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S1>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S13>/Kalpha' : Eliminated nontunable gain of 1
 * Block '<S13>/Kbeta' : Eliminated nontunable gain of 1
 * Block '<S25>/Data Type Conversion10' : Eliminate redundant data type conversion
 * Block '<S25>/Data Type Conversion11' : Eliminate redundant data type conversion
 * Block '<S25>/Data Type Conversion6' : Eliminate redundant data type conversion
 * Block '<S25>/Data Type Conversion7' : Eliminate redundant data type conversion
 * Block '<S25>/Data Type Conversion8' : Eliminate redundant data type conversion
 * Block '<S25>/Data Type Conversion9' : Eliminate redundant data type conversion
 * Block '<S54>/Kb' : Eliminated nontunable gain of 1
 * Block '<S26>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S26>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S26>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S26>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S26>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S26>/Data Type Conversion5' : Eliminate redundant data type conversion
 * Block '<S108>/Kb' : Eliminated nontunable gain of 1
 * Block '<S128>/Kt' : Eliminated nontunable gain of 1
 * Block '<S138>/Ka' : Eliminated nontunable gain of 1
 * Block '<S138>/Kb' : Eliminated nontunable gain of 1
 * Block '<S138>/Kc' : Eliminated nontunable gain of 1
 * Block '<S7>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S174>/Kb' : Eliminated nontunable gain of 1
 * Block '<S194>/Kt' : Eliminated nontunable gain of 1
 * Block '<S3>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S10>/FilterConstant' : Unused code path elimination
 * Block '<S10>/OneMinusFilterConstant' : Unused code path elimination
 * Block '<S10>/UseInputPort' : Unused code path elimination
 * Block '<S11>/FilterConstant' : Unused code path elimination
 * Block '<S11>/OneMinusFilterConstant' : Unused code path elimination
 * Block '<S11>/UseInputPort' : Unused code path elimination
 * Block '<S140>/Offset' : Unused code path elimination
 * Block '<S140>/Unary_Minus' : Unused code path elimination
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
 * hilite_system('IPMSM_motor_FOC_V1/FOC_Basic')    - opens subsystem IPMSM_motor_FOC_V1/FOC_Basic
 * hilite_system('IPMSM_motor_FOC_V1/FOC_Basic/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'IPMSM_motor_FOC_V1'
 * '<S1>'   : 'IPMSM_motor_FOC_V1/FOC_Basic'
 * '<S2>'   : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA'
 * '<S3>'   : 'IPMSM_motor_FOC_V1/FOC_Basic/Rate Limiter Dynamic'
 * '<S4>'   : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Clarke_Park'
 * '<S5>'   : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop'
 * '<S6>'   : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inverse_Clarke_Park'
 * '<S7>'   : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Rate Limiter Dynamic'
 * '<S8>'   : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem'
 * '<S9>'   : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Clarke_Park/Clarke Transform'
 * '<S10>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Clarke_Park/IIR Filter'
 * '<S11>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Clarke_Park/IIR Filter1'
 * '<S12>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Clarke_Park/Park Transform'
 * '<S13>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Clarke_Park/Clarke Transform/Two phase input'
 * '<S14>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Clarke_Park/Clarke Transform/Two phase input/Two phase CRL wrap'
 * '<S15>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Clarke_Park/IIR Filter/IIR Filter'
 * '<S16>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Clarke_Park/IIR Filter/IIR Filter/Low-pass'
 * '<S17>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Clarke_Park/IIR Filter/IIR Filter/Low-pass/IIR Low Pass Filter'
 * '<S18>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Clarke_Park/IIR Filter1/IIR Filter'
 * '<S19>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Clarke_Park/IIR Filter1/IIR Filter/Low-pass'
 * '<S20>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Clarke_Park/IIR Filter1/IIR Filter/Low-pass/IIR Low Pass Filter'
 * '<S21>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Clarke_Park/Park Transform/Two inputs CRL'
 * '<S22>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Clarke_Park/Park Transform/Two inputs CRL/Switch_Axis'
 * '<S23>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Saturation Dynamic'
 * '<S24>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Saturation Dynamic1'
 * '<S25>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem'
 * '<S26>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1'
 * '<S27>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq'
 * '<S28>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Anti-windup'
 * '<S29>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/D Gain'
 * '<S30>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/External Derivative'
 * '<S31>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Filter'
 * '<S32>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Filter ICs'
 * '<S33>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/I Gain'
 * '<S34>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Ideal P Gain'
 * '<S35>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Ideal P Gain Fdbk'
 * '<S36>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Integrator'
 * '<S37>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Integrator ICs'
 * '<S38>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/N Copy'
 * '<S39>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/N Gain'
 * '<S40>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/P Copy'
 * '<S41>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Parallel P Gain'
 * '<S42>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Reset Signal'
 * '<S43>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Saturation'
 * '<S44>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Saturation Fdbk'
 * '<S45>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Sum'
 * '<S46>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Sum Fdbk'
 * '<S47>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tracking Mode'
 * '<S48>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tracking Mode Sum'
 * '<S49>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tsamp - Integral'
 * '<S50>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tsamp - Ngain'
 * '<S51>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/postSat Signal'
 * '<S52>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/preInt Signal'
 * '<S53>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/preSat Signal'
 * '<S54>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Anti-windup/Back Calculation'
 * '<S55>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/D Gain/External Parameters'
 * '<S56>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/External Derivative/Error'
 * '<S57>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Filter/Disc. Forward Euler Filter'
 * '<S58>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Filter ICs/Internal IC - Filter'
 * '<S59>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/I Gain/External Parameters'
 * '<S60>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Ideal P Gain/Passthrough'
 * '<S61>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Ideal P Gain Fdbk/Disabled'
 * '<S62>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Integrator/Discrete'
 * '<S63>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Integrator ICs/Internal IC'
 * '<S64>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/N Copy/Disabled'
 * '<S65>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/N Gain/External Parameters'
 * '<S66>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/P Copy/Disabled'
 * '<S67>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Parallel P Gain/External Parameters'
 * '<S68>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Reset Signal/Disabled'
 * '<S69>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Saturation/External'
 * '<S70>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Saturation/External/Saturation Dynamic'
 * '<S71>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Saturation Fdbk/Disabled'
 * '<S72>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Sum/Sum_PID'
 * '<S73>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Sum Fdbk/Disabled'
 * '<S74>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tracking Mode/Enabled'
 * '<S75>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tracking Mode Sum/Tracking Mode'
 * '<S76>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tsamp - Integral/TsSignalSpecification'
 * '<S77>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tsamp - Ngain/Passthrough'
 * '<S78>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/postSat Signal/Forward_Path'
 * '<S79>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/preInt Signal/Internal PreInt'
 * '<S80>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/preSat Signal/Forward_Path'
 * '<S81>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd'
 * '<S82>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Anti-windup'
 * '<S83>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/D Gain'
 * '<S84>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/External Derivative'
 * '<S85>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Filter'
 * '<S86>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Filter ICs'
 * '<S87>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/I Gain'
 * '<S88>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain'
 * '<S89>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain Fdbk'
 * '<S90>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Integrator'
 * '<S91>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Integrator ICs'
 * '<S92>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/N Copy'
 * '<S93>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/N Gain'
 * '<S94>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/P Copy'
 * '<S95>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Parallel P Gain'
 * '<S96>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Reset Signal'
 * '<S97>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Saturation'
 * '<S98>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Saturation Fdbk'
 * '<S99>'  : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Sum'
 * '<S100>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Sum Fdbk'
 * '<S101>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tracking Mode'
 * '<S102>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tracking Mode Sum'
 * '<S103>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tsamp - Integral'
 * '<S104>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tsamp - Ngain'
 * '<S105>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/postSat Signal'
 * '<S106>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/preInt Signal'
 * '<S107>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/preSat Signal'
 * '<S108>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Anti-windup/Back Calculation'
 * '<S109>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/D Gain/External Parameters'
 * '<S110>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/External Derivative/Error'
 * '<S111>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Filter/Disc. Forward Euler Filter'
 * '<S112>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Filter ICs/Internal IC - Filter'
 * '<S113>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/I Gain/External Parameters'
 * '<S114>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain/Passthrough'
 * '<S115>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain Fdbk/Disabled'
 * '<S116>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Integrator/Discrete'
 * '<S117>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Integrator ICs/Internal IC'
 * '<S118>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/N Copy/Disabled'
 * '<S119>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/N Gain/External Parameters'
 * '<S120>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/P Copy/Disabled'
 * '<S121>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Parallel P Gain/External Parameters'
 * '<S122>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Reset Signal/Disabled'
 * '<S123>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Saturation/External'
 * '<S124>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Saturation/External/Saturation Dynamic'
 * '<S125>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Saturation Fdbk/Disabled'
 * '<S126>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Sum/Sum_PID'
 * '<S127>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Sum Fdbk/Disabled'
 * '<S128>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tracking Mode/Enabled'
 * '<S129>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tracking Mode Sum/Tracking Mode'
 * '<S130>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tsamp - Integral/TsSignalSpecification'
 * '<S131>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tsamp - Ngain/Passthrough'
 * '<S132>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/postSat Signal/Forward_Path'
 * '<S133>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/preInt Signal/Internal PreInt'
 * '<S134>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/preSat Signal/Forward_Path'
 * '<S135>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inverse_Clarke_Park/Inverse Clarke Transform'
 * '<S136>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inverse_Clarke_Park/Inverse Park Transform'
 * '<S137>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inverse_Clarke_Park/PWM Reference Generator'
 * '<S138>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inverse_Clarke_Park/Inverse Clarke Transform/Two phase input'
 * '<S139>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inverse_Clarke_Park/Inverse Park Transform/Two inputs CRL'
 * '<S140>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inverse_Clarke_Park/Inverse Park Transform/Two inputs CRL/Switch_Axis'
 * '<S141>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inverse_Clarke_Park/PWM Reference Generator/Modulation method'
 * '<S142>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inverse_Clarke_Park/PWM Reference Generator/Voltage Input'
 * '<S143>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inverse_Clarke_Park/PWM Reference Generator/Modulation method/SVPWM'
 * '<S144>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inverse_Clarke_Park/PWM Reference Generator/Modulation method/SVPWM/Half(Vmin+Vmax)'
 * '<S145>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Inverse_Clarke_Park/PWM Reference Generator/Voltage Input/Vabc'
 * '<S146>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S147>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd'
 * '<S148>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Anti-windup'
 * '<S149>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/D Gain'
 * '<S150>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/External Derivative'
 * '<S151>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Filter'
 * '<S152>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Filter ICs'
 * '<S153>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/I Gain'
 * '<S154>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Ideal P Gain'
 * '<S155>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Ideal P Gain Fdbk'
 * '<S156>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Integrator'
 * '<S157>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Integrator ICs'
 * '<S158>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/N Copy'
 * '<S159>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/N Gain'
 * '<S160>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/P Copy'
 * '<S161>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Parallel P Gain'
 * '<S162>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Reset Signal'
 * '<S163>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Saturation'
 * '<S164>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Saturation Fdbk'
 * '<S165>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Sum'
 * '<S166>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Sum Fdbk'
 * '<S167>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Tracking Mode'
 * '<S168>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Tracking Mode Sum'
 * '<S169>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Tsamp - Integral'
 * '<S170>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Tsamp - Ngain'
 * '<S171>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/postSat Signal'
 * '<S172>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/preInt Signal'
 * '<S173>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/preSat Signal'
 * '<S174>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Anti-windup/Back Calculation'
 * '<S175>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/D Gain/External Parameters'
 * '<S176>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/External Derivative/Error'
 * '<S177>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Filter/Disc. Forward Euler Filter'
 * '<S178>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Filter ICs/Internal IC - Filter'
 * '<S179>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/I Gain/External Parameters'
 * '<S180>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Ideal P Gain/Passthrough'
 * '<S181>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Ideal P Gain Fdbk/Disabled'
 * '<S182>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Integrator/Discrete'
 * '<S183>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Integrator ICs/Internal IC'
 * '<S184>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/N Copy/Disabled'
 * '<S185>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/N Gain/External Parameters'
 * '<S186>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/P Copy/Disabled'
 * '<S187>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Parallel P Gain/External Parameters'
 * '<S188>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Reset Signal/Disabled'
 * '<S189>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Saturation/External'
 * '<S190>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Saturation/External/Saturation Dynamic'
 * '<S191>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Saturation Fdbk/Disabled'
 * '<S192>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Sum/Sum_PID'
 * '<S193>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Sum Fdbk/Disabled'
 * '<S194>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Tracking Mode/Enabled'
 * '<S195>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Tracking Mode Sum/Tracking Mode'
 * '<S196>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Tsamp - Integral/TsSignalSpecification'
 * '<S197>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/Tsamp - Ngain/Passthrough'
 * '<S198>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/postSat Signal/Forward_Path'
 * '<S199>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/preInt Signal/Internal PreInt'
 * '<S200>' : 'IPMSM_motor_FOC_V1/FOC_Basic/FOC_MTPA/Subsystem/PI Vd/preSat Signal/Forward_Path'
 * '<S201>' : 'IPMSM_motor_FOC_V1/FOC_Basic/Rate Limiter Dynamic/Saturation Dynamic'
 */
#endif                                 /* FOC_Basic_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
