/*
 * File: FOC_MTPA_FF.h
 *
 * Code generated for Simulink model 'FOC_MTPA_FF'.
 *
 * Model version                  : 18.293
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Tue Feb  3 14:27:04 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef FOC_MTPA_FF_h_
#define FOC_MTPA_FF_h_
#ifndef FOC_MTPA_FF_COMMON_INCLUDES_
#define FOC_MTPA_FF_COMMON_INCLUDES_
#include <stdbool.h>
#include <stdint.h>
#include "complex_types.h"
#include "math.h"
#include "main.h"
#endif                                 /* FOC_MTPA_FF_COMMON_INCLUDES_ */

#include "FOC_MTPA_FF_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  double Integrator_DSTATE;            /* '<S123>/Integrator' */
  double Filter_DSTATE;                /* '<S118>/Filter' */
  double Integrator_DSTATE_h;          /* '<S69>/Integrator' */
  double Filter_DSTATE_d;              /* '<S64>/Filter' */
  double Delay_DSTATE;                 /* '<S3>/Delay' */
  double Integrator_DSTATE_b;          /* '<S191>/Integrator' */
  double Filter_DSTATE_i;              /* '<S186>/Filter' */
  double Delay_DSTATE_h;               /* '<S8>/Delay' */
  double RateTransition_Buffer0;       /* '<S2>/Rate Transition' */
  float UnitDelay_DSTATE;              /* '<S18>/Unit Delay' */
  float UnitDelay_DSTATE_f;            /* '<S21>/Unit Delay' */
  bool icLoad;                         /* '<S3>/Delay' */
  bool icLoad_p;                       /* '<S8>/Delay' */
} DW_FOC_MTPA_FF_T;

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
  double Rs;                           /* '<Root>/Rs' */
  double Ld;                           /* '<Root>/Ld' */
  double Lq;                           /* '<Root>/Lq' */
  double Lambda;                       /* '<Root>/Lambda' */
  float p;                             /* '<Root>/Pole_pairs' */
  float BusVoltage_V;                  /* '<Root>/Bus_Voltage' */
  Id_Iq_MTPA_limitBus Id_Iq_MTPA_limit;/* '<Root>/Id_Iq_MTPA_limit' */
  double Iq_Torque_ratio;              /* '<Root>/Iq_Torque_ratio' */
  double Speed_1_Torque_0;             /* '<Root>/Speed_1_Torque_0' */
  double RefTrq;                       /* '<Root>/T_ref' */
} ExtU_FOC_MTPA_FF_T;

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
} ExtY_FOC_MTPA_FF_T;

/* Real-time Model Data Structure */
struct tag_RTM_FOC_MTPA_FF_T {
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
extern DW_FOC_MTPA_FF_T FOC_MTPA_FF_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_FOC_MTPA_FF_T FOC_MTPA_FF_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_FOC_MTPA_FF_T FOC_MTPA_FF_Y;

/* Model entry point functions */
extern void FOC_MTPA_FF_initialize(void);
extern void FOC_MTPA_FF_step0(void);   /* Sample time: [0.0001s, 0.0s] */
extern void FOC_MTPA_FF_step1(void);   /* Sample time: [0.001s, 0.0s] */
extern void FOC_MTPA_FF_terminate(void);

/* Real-time Model object */
extern RT_MODEL_FOC_MTPA_FF_T *const FOC_MTPA_FF_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S15>/Data Type Duplicate' : Unused code path elimination
 * Block '<S11>/Data Type Duplicate' : Unused code path elimination
 * Block '<S12>/Data Type Duplicate' : Unused code path elimination
 * Block '<S22>/Data Type Duplicate' : Unused code path elimination
 * Block '<S22>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S2>/Display' : Unused code path elimination
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
 * Block '<S153>/Data Type Duplicate' : Unused code path elimination
 * Block '<S153>/Data Type Propagation' : Unused code path elimination
 * Block '<S154>/Data Type Duplicate' : Unused code path elimination
 * Block '<S154>/Data Type Propagation' : Unused code path elimination
 * Block '<S8>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S155>/Data Type Duplicate' : Unused code path elimination
 * Block '<S155>/Data Type Propagation' : Unused code path elimination
 * Block '<S199>/Data Type Duplicate' : Unused code path elimination
 * Block '<S199>/Data Type Propagation' : Unused code path elimination
 * Block '<S3>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S210>/Data Type Duplicate' : Unused code path elimination
 * Block '<S210>/Data Type Propagation' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S1>/Data Type Conversion' : Eliminate redundant data type conversion
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
 * Block '<S61>/Kb' : Eliminated nontunable gain of 1
 * Block '<S115>/Kb' : Eliminated nontunable gain of 1
 * Block '<S135>/Kt' : Eliminated nontunable gain of 1
 * Block '<S145>/Ka' : Eliminated nontunable gain of 1
 * Block '<S145>/Kb' : Eliminated nontunable gain of 1
 * Block '<S145>/Kc' : Eliminated nontunable gain of 1
 * Block '<S7>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S8>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S183>/Kb' : Eliminated nontunable gain of 1
 * Block '<S203>/Kt' : Eliminated nontunable gain of 1
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
 * hilite_system('IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF')    - opens subsystem IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF
 * hilite_system('IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'IPMSM_motor_FOC_MTPA_FF'
 * '<S1>'   : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF'
 * '<S2>'   : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA'
 * '<S3>'   : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/Rate Limiter Dynamic'
 * '<S4>'   : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Clarke_Park'
 * '<S5>'   : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop'
 * '<S6>'   : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inverse_Clarke_Park'
 * '<S7>'   : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/MTPA'
 * '<S8>'   : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Rate Limiter Dynamic'
 * '<S9>'   : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem'
 * '<S10>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Clarke_Park/Clarke Transform'
 * '<S11>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Clarke_Park/IIR Filter'
 * '<S12>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Clarke_Park/IIR Filter1'
 * '<S13>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Clarke_Park/Park Transform'
 * '<S14>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Clarke_Park/Clarke Transform/Two phase input'
 * '<S15>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Clarke_Park/Clarke Transform/Two phase input/Two phase CRL wrap'
 * '<S16>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Clarke_Park/IIR Filter/IIR Filter'
 * '<S17>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Clarke_Park/IIR Filter/IIR Filter/Low-pass'
 * '<S18>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Clarke_Park/IIR Filter/IIR Filter/Low-pass/IIR Low Pass Filter'
 * '<S19>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Clarke_Park/IIR Filter1/IIR Filter'
 * '<S20>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Clarke_Park/IIR Filter1/IIR Filter/Low-pass'
 * '<S21>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Clarke_Park/IIR Filter1/IIR Filter/Low-pass/IIR Low Pass Filter'
 * '<S22>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Clarke_Park/Park Transform/Two inputs CRL'
 * '<S23>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Clarke_Park/Park Transform/Two inputs CRL/Switch_Axis'
 * '<S24>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/PMSM FeedForward Control'
 * '<S25>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Saturation Dynamic'
 * '<S26>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Saturation Dynamic1'
 * '<S27>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem'
 * '<S28>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1'
 * '<S29>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/PMSM FeedForward Control/FeedForward Control Selection'
 * '<S30>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/PMSM FeedForward Control/FeedForward Control Selection/Linear FeedForward_LumpedParameter_InputPort'
 * '<S31>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/PMSM FeedForward Control/FeedForward Control Selection/Linear FeedForward_LumpedParameter_InputPort/LumpedParams_InpurPorts'
 * '<S32>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/PMSM FeedForward Control/FeedForward Control Selection/Linear FeedForward_LumpedParameter_InputPort/Vd_sat'
 * '<S33>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/PMSM FeedForward Control/FeedForward Control Selection/Linear FeedForward_LumpedParameter_InputPort/Vq_sat'
 * '<S34>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq'
 * '<S35>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Anti-windup'
 * '<S36>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/D Gain'
 * '<S37>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/External Derivative'
 * '<S38>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Filter'
 * '<S39>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Filter ICs'
 * '<S40>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/I Gain'
 * '<S41>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Ideal P Gain'
 * '<S42>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Ideal P Gain Fdbk'
 * '<S43>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Integrator'
 * '<S44>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Integrator ICs'
 * '<S45>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/N Copy'
 * '<S46>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/N Gain'
 * '<S47>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/P Copy'
 * '<S48>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Parallel P Gain'
 * '<S49>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Reset Signal'
 * '<S50>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Saturation'
 * '<S51>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Saturation Fdbk'
 * '<S52>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Sum'
 * '<S53>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Sum Fdbk'
 * '<S54>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tracking Mode'
 * '<S55>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tracking Mode Sum'
 * '<S56>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tsamp - Integral'
 * '<S57>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tsamp - Ngain'
 * '<S58>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/postSat Signal'
 * '<S59>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/preInt Signal'
 * '<S60>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/preSat Signal'
 * '<S61>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Anti-windup/Back Calculation'
 * '<S62>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/D Gain/External Parameters'
 * '<S63>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/External Derivative/Error'
 * '<S64>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Filter/Disc. Forward Euler Filter'
 * '<S65>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Filter ICs/Internal IC - Filter'
 * '<S66>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/I Gain/External Parameters'
 * '<S67>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Ideal P Gain/Passthrough'
 * '<S68>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Ideal P Gain Fdbk/Disabled'
 * '<S69>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Integrator/Discrete'
 * '<S70>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Integrator ICs/Internal IC'
 * '<S71>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/N Copy/Disabled'
 * '<S72>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/N Gain/External Parameters'
 * '<S73>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/P Copy/Disabled'
 * '<S74>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Parallel P Gain/External Parameters'
 * '<S75>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Reset Signal/Disabled'
 * '<S76>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Saturation/External'
 * '<S77>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Saturation/External/Saturation Dynamic'
 * '<S78>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Saturation Fdbk/Disabled'
 * '<S79>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Sum/Sum_PID'
 * '<S80>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Sum Fdbk/Disabled'
 * '<S81>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tracking Mode/Enabled'
 * '<S82>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tracking Mode Sum/Tracking Mode'
 * '<S83>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tsamp - Integral/TsSignalSpecification'
 * '<S84>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/Tsamp - Ngain/Passthrough'
 * '<S85>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/postSat Signal/Forward_Path'
 * '<S86>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/preInt Signal/Internal PreInt'
 * '<S87>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem/PI Vq/preSat Signal/Forward_Path'
 * '<S88>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd'
 * '<S89>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Anti-windup'
 * '<S90>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/D Gain'
 * '<S91>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/External Derivative'
 * '<S92>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Filter'
 * '<S93>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Filter ICs'
 * '<S94>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/I Gain'
 * '<S95>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain'
 * '<S96>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain Fdbk'
 * '<S97>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Integrator'
 * '<S98>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Integrator ICs'
 * '<S99>'  : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/N Copy'
 * '<S100>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/N Gain'
 * '<S101>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/P Copy'
 * '<S102>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Parallel P Gain'
 * '<S103>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Reset Signal'
 * '<S104>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Saturation'
 * '<S105>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Saturation Fdbk'
 * '<S106>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Sum'
 * '<S107>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Sum Fdbk'
 * '<S108>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tracking Mode'
 * '<S109>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tracking Mode Sum'
 * '<S110>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tsamp - Integral'
 * '<S111>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tsamp - Ngain'
 * '<S112>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/postSat Signal'
 * '<S113>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/preInt Signal'
 * '<S114>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/preSat Signal'
 * '<S115>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Anti-windup/Back Calculation'
 * '<S116>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/D Gain/External Parameters'
 * '<S117>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/External Derivative/Error'
 * '<S118>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Filter/Disc. Forward Euler Filter'
 * '<S119>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Filter ICs/Internal IC - Filter'
 * '<S120>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/I Gain/External Parameters'
 * '<S121>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain/Passthrough'
 * '<S122>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain Fdbk/Disabled'
 * '<S123>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Integrator/Discrete'
 * '<S124>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Integrator ICs/Internal IC'
 * '<S125>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/N Copy/Disabled'
 * '<S126>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/N Gain/External Parameters'
 * '<S127>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/P Copy/Disabled'
 * '<S128>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Parallel P Gain/External Parameters'
 * '<S129>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Reset Signal/Disabled'
 * '<S130>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Saturation/External'
 * '<S131>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Saturation/External/Saturation Dynamic'
 * '<S132>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Saturation Fdbk/Disabled'
 * '<S133>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Sum/Sum_PID'
 * '<S134>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Sum Fdbk/Disabled'
 * '<S135>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tracking Mode/Enabled'
 * '<S136>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tracking Mode Sum/Tracking Mode'
 * '<S137>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tsamp - Integral/TsSignalSpecification'
 * '<S138>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/Tsamp - Ngain/Passthrough'
 * '<S139>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/postSat Signal/Forward_Path'
 * '<S140>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/preInt Signal/Internal PreInt'
 * '<S141>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inner PID loop/Subsystem1/PI Vd/preSat Signal/Forward_Path'
 * '<S142>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inverse_Clarke_Park/Inverse Clarke Transform'
 * '<S143>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inverse_Clarke_Park/Inverse Park Transform'
 * '<S144>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inverse_Clarke_Park/PWM Reference Generator'
 * '<S145>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inverse_Clarke_Park/Inverse Clarke Transform/Two phase input'
 * '<S146>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inverse_Clarke_Park/Inverse Park Transform/Two inputs CRL'
 * '<S147>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inverse_Clarke_Park/Inverse Park Transform/Two inputs CRL/Switch_Axis'
 * '<S148>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inverse_Clarke_Park/PWM Reference Generator/Modulation method'
 * '<S149>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inverse_Clarke_Park/PWM Reference Generator/Voltage Input'
 * '<S150>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inverse_Clarke_Park/PWM Reference Generator/Modulation method/SVPWM'
 * '<S151>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inverse_Clarke_Park/PWM Reference Generator/Modulation method/SVPWM/Half(Vmin+Vmax)'
 * '<S152>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Inverse_Clarke_Park/PWM Reference Generator/Voltage Input/Vabc'
 * '<S153>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/MTPA/Saturation Dynamic'
 * '<S154>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/MTPA/Saturation Dynamic1'
 * '<S155>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S156>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd'
 * '<S157>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Anti-windup'
 * '<S158>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/D Gain'
 * '<S159>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/External Derivative'
 * '<S160>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Filter'
 * '<S161>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Filter ICs'
 * '<S162>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/I Gain'
 * '<S163>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Ideal P Gain'
 * '<S164>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Ideal P Gain Fdbk'
 * '<S165>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Integrator'
 * '<S166>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Integrator ICs'
 * '<S167>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/N Copy'
 * '<S168>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/N Gain'
 * '<S169>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/P Copy'
 * '<S170>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Parallel P Gain'
 * '<S171>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Reset Signal'
 * '<S172>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Saturation'
 * '<S173>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Saturation Fdbk'
 * '<S174>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Sum'
 * '<S175>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Sum Fdbk'
 * '<S176>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Tracking Mode'
 * '<S177>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Tracking Mode Sum'
 * '<S178>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Tsamp - Integral'
 * '<S179>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Tsamp - Ngain'
 * '<S180>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/postSat Signal'
 * '<S181>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/preInt Signal'
 * '<S182>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/preSat Signal'
 * '<S183>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Anti-windup/Back Calculation'
 * '<S184>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/D Gain/External Parameters'
 * '<S185>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/External Derivative/Error'
 * '<S186>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Filter/Disc. Forward Euler Filter'
 * '<S187>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Filter ICs/Internal IC - Filter'
 * '<S188>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/I Gain/External Parameters'
 * '<S189>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Ideal P Gain/Passthrough'
 * '<S190>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Ideal P Gain Fdbk/Disabled'
 * '<S191>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Integrator/Discrete'
 * '<S192>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Integrator ICs/Internal IC'
 * '<S193>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/N Copy/Disabled'
 * '<S194>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/N Gain/External Parameters'
 * '<S195>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/P Copy/Disabled'
 * '<S196>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Parallel P Gain/External Parameters'
 * '<S197>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Reset Signal/Disabled'
 * '<S198>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Saturation/External'
 * '<S199>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Saturation/External/Saturation Dynamic'
 * '<S200>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Saturation Fdbk/Disabled'
 * '<S201>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Sum/Sum_PID'
 * '<S202>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Sum Fdbk/Disabled'
 * '<S203>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Tracking Mode/Enabled'
 * '<S204>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Tracking Mode Sum/Tracking Mode'
 * '<S205>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Tsamp - Integral/TsSignalSpecification'
 * '<S206>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/Tsamp - Ngain/Passthrough'
 * '<S207>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/postSat Signal/Forward_Path'
 * '<S208>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/preInt Signal/Internal PreInt'
 * '<S209>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/FOC_MTPA/Subsystem/PI Vd/preSat Signal/Forward_Path'
 * '<S210>' : 'IPMSM_motor_FOC_MTPA_FF/FOC_MTPA_FF/Rate Limiter Dynamic/Saturation Dynamic'
 */
#endif                                 /* FOC_MTPA_FF_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
