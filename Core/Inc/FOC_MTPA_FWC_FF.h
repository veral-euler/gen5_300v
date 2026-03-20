/*
 * File: FOC_MTPA_FWC_FF.h
 *
 * Code generated for Simulink model 'FOC_MTPA_FWC_FF'.
 *
 * Model version                  : 18.348
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Fri Mar 20 14:59:13 2026
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
  float T_ref_final;                   /* '<S1>/Rate Transition' */
  float Merge[2];                      /* '<S8>/Merge' */
  float DataTypeConversion1;           /* '<S1>/Data Type Conversion1' */
  float Iq_ref;                        /* '<S161>/FNR_switching' */
  float Id_ref;                        /* '<S161>/FNR_switching' */
} B_FOC_MTPA_FWC_FF_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  float Delay_DSTATE;                  /* '<S9>/Delay' */
  float DelayOneStep_DSTATE;           /* '<S1>/Delay One Step' */
  float Delay_DSTATE_h;                /* '<S156>/Delay' */
  float UnitDelay_DSTATE;              /* '<S18>/Unit Delay' */
  float Integrator_DSTATE;             /* '<S123>/Integrator' */
  float Filter_DSTATE;                 /* '<S118>/Filter' */
  float Delay_DSTATE_b;                /* '<S157>/Delay' */
  float UnitDelay_DSTATE_f;            /* '<S21>/Unit Delay' */
  float Integrator_DSTATE_h;           /* '<S69>/Integrator' */
  float Filter_DSTATE_d;               /* '<S64>/Filter' */
  float DelayOneStep_DSTATE_m;         /* '<S4>/Delay One Step' */
  float Delay_DSTATE_c;                /* '<S174>/Delay' */
  float Integrator_DSTATE_g;           /* '<S212>/Integrator' */
  float Filter_DSTATE_c;               /* '<S207>/Filter' */
  float UnitDelay_DSTATE_p;            /* '<S162>/Unit Delay' */
  float DiscreteTimeIntegrator_DSTATE; /* '<S162>/Discrete-Time Integrator' */
  float RateTransition_Buffer0;        /* '<S1>/Rate Transition' */
  uint32_t durationCounter_1;          /* '<S161>/FNR_switching' */
  uint32_t durationCounter_1_n;        /* '<S161>/FNR_switching' */
  uint8_t is_active_c1_FOC_MTPA_FWC_FF;/* '<S161>/FNR_switching' */
  uint8_t is_c1_FOC_MTPA_FWC_FF;       /* '<S161>/FNR_switching' */
  uint8_t is_active_c3_FOC_MTPA_FWC_FF;/* '<S160>/Chart' */
  uint8_t is_c3_FOC_MTPA_FWC_FF;       /* '<S160>/Chart' */
  bool icLoad;                         /* '<S9>/Delay' */
  bool icLoad_p;                       /* '<S156>/Delay' */
  bool icLoad_l;                       /* '<S157>/Delay' */
  bool icLoad_k;                       /* '<S174>/Delay' */
} DW_FOC_MTPA_FWC_FF_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  float Ref_Speed_mech_rpm;            /* '<Root>/Ref_Speed_mech_rpm' */
  float ActualSpeed_mech_radsec;       /* '<Root>/Actual Speed_mech_rad//sec' */
  float MtrElcPos;                    /* '<Root>/angle' */
  float PhaseCurrent[3];              /* '<Root>/Phase Current' */
  PID_MTPABus MTPA_PID;                /* '<Root>/MTPA_PID' */
  Rate_limiterBus Rate_limiter;        /* '<Root>/Rate_limiter' */
  IIR_FilterBus IIR_Filter_Coefficient;/* '<Root>/IIR_Filter_Coefficient' */
  Motor_ParametersBus Motor_Parameters;/* '<Root>/Motor_Parameters' */
  float BusVoltage_V;                  /* '<Root>/Bus_Voltage' */
  ThrottleBus Throttle_input;          /* '<Root>/Throttle_input' */
  Id_Iq_MTPA_limitBus Id_Iq_MTPA_limit;/* '<Root>/Id_Iq_MTPA_limit' */
  float Iq_Torque_ratio;              /* '<Root>/Iq_Torque_ratio' */
  float Speed_1_Torque_0;              /* '<Root>/Speed_1_Torque_0' */
  float RefTrq;                        /* '<Root>/T_ref' */
  float Is_max;                       /* '<Root>/Is_max' */
  float Drive_State;                   /* '<Root>/Drive_State' */
  float RPM_min_limit;                 /* '<Root>/RPM_min_limit' */
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
  float Id_ref_MTPA;                   /* '<Root>/Id_ref_MTPA' */
  float Iq_ref_MTPA;                   /* '<Root>/Iq_ref_MTPA' */
  float V_s;                           /* '<Root>/V_s' */
  float V_max;                         /* '<Root>/V_max' */
  float MTPA_FWC_condition;           /* '<Root>/MTPA_FWC_condition' */
  float Throttle_en;                  /* '<Root>/Throttle_en' */
  ThrottleState Throttle_State;        /* '<Root>/Throttle_State' */
  bool Throttle_error;                 /* '<Root>/Throttle_error' */
  float Ref_speed_out_RPM;             /* '<Root>/Ref_speed_out_RPM' */
  float T_gen;                         /* '<Root>/T_gen' */
  float Iq_gen1;                       /* '<Root>/Iq_gen1' */
} ExtY_FOC_MTPA_FWC_FF_T;

/* Real-time Model Data Structure */
struct tag_RTM_FOC_MTPA_FWC_FF_T {
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
 * Block '<S5>/Data Type Conversion2' : Unused code path elimination
 * Block '<S5>/Data Type Conversion3' : Unused code path elimination
 * Block '<S11>/Data Type Duplicate' : Unused code path elimination
 * Block '<S12>/Data Type Duplicate' : Unused code path elimination
 * Block '<S22>/Data Type Duplicate' : Unused code path elimination
 * Block '<S22>/Data Type Duplicate1' : Unused code path elimination
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
 * Block '<S7>/Scope' : Unused code path elimination
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
 * Block '<S173>/Data Type Duplicate' : Unused code path elimination
 * Block '<S173>/Data Type Propagation' : Unused code path elimination
 * Block '<S4>/Display' : Unused code path elimination
 * Block '<S4>/Display2' : Unused code path elimination
 * Block '<S4>/Scope1' : Unused code path elimination
 * Block '<S176>/Data Type Duplicate' : Unused code path elimination
 * Block '<S176>/Data Type Propagation' : Unused code path elimination
 * Block '<S220>/Data Type Duplicate' : Unused code path elimination
 * Block '<S220>/Data Type Propagation' : Unused code path elimination
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
 * Block '<S9>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S174>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S204>/Kb' : Eliminated nontunable gain of 1
 * Block '<S224>/Kt' : Eliminated nontunable gain of 1
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
 * '<S2>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Compare To Constant'
 * '<S3>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop'
 * '<S4>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop'
 * '<S5>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park'
 * '<S6>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop'
 * '<S7>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park'
 * '<S8>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC'
 * '<S9>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Subsystem1'
 * '<S10>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/Clarke Transform'
 * '<S11>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/IIR Filter'
 * '<S12>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/IIR Filter1'
 * '<S13>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/Park Transform'
 * '<S14>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/Clarke Transform/Two phase input'
 * '<S15>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/Clarke Transform/Two phase input/Two phase CRL wrap'
 * '<S16>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/IIR Filter/IIR Filter'
 * '<S17>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/IIR Filter/IIR Filter/Low-pass'
 * '<S18>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/IIR Filter/IIR Filter/Low-pass/IIR Low Pass Filter'
 * '<S19>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/IIR Filter1/IIR Filter'
 * '<S20>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/IIR Filter1/IIR Filter/Low-pass'
 * '<S21>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/IIR Filter1/IIR Filter/Low-pass/IIR Low Pass Filter'
 * '<S22>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/Park Transform/Two inputs CRL'
 * '<S23>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/Park Transform/Two inputs CRL/Switch_Axis'
 * '<S24>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/PMSM FeedForward Control'
 * '<S25>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Saturation Dynamic'
 * '<S26>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Saturation Dynamic1'
 * '<S27>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem'
 * '<S28>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1'
 * '<S29>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/PMSM FeedForward Control/FeedForward Control Selection'
 * '<S30>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/PMSM FeedForward Control/FeedForward Control Selection/Linear FeedForward_LumpedParameter_InputPort'
 * '<S31>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/PMSM FeedForward Control/FeedForward Control Selection/Linear FeedForward_LumpedParameter_InputPort/LumpedParams_InpurPorts'
 * '<S32>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/PMSM FeedForward Control/FeedForward Control Selection/Linear FeedForward_LumpedParameter_InputPort/Vd_sat'
 * '<S33>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/PMSM FeedForward Control/FeedForward Control Selection/Linear FeedForward_LumpedParameter_InputPort/Vq_sat'
 * '<S34>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq'
 * '<S35>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Anti-windup'
 * '<S36>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/D Gain'
 * '<S37>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/External Derivative'
 * '<S38>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Filter'
 * '<S39>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Filter ICs'
 * '<S40>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/I Gain'
 * '<S41>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Ideal P Gain'
 * '<S42>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Ideal P Gain Fdbk'
 * '<S43>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Integrator'
 * '<S44>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Integrator ICs'
 * '<S45>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/N Copy'
 * '<S46>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/N Gain'
 * '<S47>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/P Copy'
 * '<S48>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Parallel P Gain'
 * '<S49>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Reset Signal'
 * '<S50>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Saturation'
 * '<S51>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Saturation Fdbk'
 * '<S52>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Sum'
 * '<S53>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Sum Fdbk'
 * '<S54>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Tracking Mode'
 * '<S55>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Tracking Mode Sum'
 * '<S56>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Tsamp - Integral'
 * '<S57>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Tsamp - Ngain'
 * '<S58>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/postSat Signal'
 * '<S59>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/preInt Signal'
 * '<S60>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/preSat Signal'
 * '<S61>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Anti-windup/Back Calculation'
 * '<S62>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/D Gain/External Parameters'
 * '<S63>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/External Derivative/Error'
 * '<S64>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Filter/Disc. Forward Euler Filter'
 * '<S65>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Filter ICs/Internal IC - Filter'
 * '<S66>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/I Gain/External Parameters'
 * '<S67>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Ideal P Gain/Passthrough'
 * '<S68>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Ideal P Gain Fdbk/Disabled'
 * '<S69>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Integrator/Discrete'
 * '<S70>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Integrator ICs/Internal IC'
 * '<S71>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/N Copy/Disabled'
 * '<S72>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/N Gain/External Parameters'
 * '<S73>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/P Copy/Disabled'
 * '<S74>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Parallel P Gain/External Parameters'
 * '<S75>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Reset Signal/Disabled'
 * '<S76>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Saturation/External'
 * '<S77>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Saturation/External/Saturation Dynamic'
 * '<S78>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Saturation Fdbk/Disabled'
 * '<S79>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Sum/Sum_PID'
 * '<S80>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Sum Fdbk/Disabled'
 * '<S81>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Tracking Mode/Enabled'
 * '<S82>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Tracking Mode Sum/Tracking Mode'
 * '<S83>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Tsamp - Integral/TsSignalSpecification'
 * '<S84>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Tsamp - Ngain/Passthrough'
 * '<S85>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/postSat Signal/Forward_Path'
 * '<S86>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/preInt Signal/Internal PreInt'
 * '<S87>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/preSat Signal/Forward_Path'
 * '<S88>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd'
 * '<S89>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Anti-windup'
 * '<S90>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/D Gain'
 * '<S91>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/External Derivative'
 * '<S92>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Filter'
 * '<S93>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Filter ICs'
 * '<S94>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/I Gain'
 * '<S95>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain'
 * '<S96>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain Fdbk'
 * '<S97>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Integrator'
 * '<S98>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Integrator ICs'
 * '<S99>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/N Copy'
 * '<S100>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/N Gain'
 * '<S101>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/P Copy'
 * '<S102>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Parallel P Gain'
 * '<S103>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Reset Signal'
 * '<S104>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Saturation'
 * '<S105>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Saturation Fdbk'
 * '<S106>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Sum'
 * '<S107>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Sum Fdbk'
 * '<S108>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Tracking Mode'
 * '<S109>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Tracking Mode Sum'
 * '<S110>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Tsamp - Integral'
 * '<S111>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Tsamp - Ngain'
 * '<S112>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/postSat Signal'
 * '<S113>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/preInt Signal'
 * '<S114>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/preSat Signal'
 * '<S115>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Anti-windup/Back Calculation'
 * '<S116>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/D Gain/External Parameters'
 * '<S117>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/External Derivative/Error'
 * '<S118>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Filter/Disc. Forward Euler Filter'
 * '<S119>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Filter ICs/Internal IC - Filter'
 * '<S120>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/I Gain/External Parameters'
 * '<S121>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain/Passthrough'
 * '<S122>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain Fdbk/Disabled'
 * '<S123>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Integrator/Discrete'
 * '<S124>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Integrator ICs/Internal IC'
 * '<S125>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/N Copy/Disabled'
 * '<S126>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/N Gain/External Parameters'
 * '<S127>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/P Copy/Disabled'
 * '<S128>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Parallel P Gain/External Parameters'
 * '<S129>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Reset Signal/Disabled'
 * '<S130>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Saturation/External'
 * '<S131>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Saturation/External/Saturation Dynamic'
 * '<S132>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Saturation Fdbk/Disabled'
 * '<S133>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Sum/Sum_PID'
 * '<S134>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Sum Fdbk/Disabled'
 * '<S135>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Tracking Mode/Enabled'
 * '<S136>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Tracking Mode Sum/Tracking Mode'
 * '<S137>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Tsamp - Integral/TsSignalSpecification'
 * '<S138>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Tsamp - Ngain/Passthrough'
 * '<S139>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/postSat Signal/Forward_Path'
 * '<S140>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/preInt Signal/Internal PreInt'
 * '<S141>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/preSat Signal/Forward_Path'
 * '<S142>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/Inverse Clarke Transform'
 * '<S143>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/Inverse Park Transform'
 * '<S144>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/PWM Reference Generator'
 * '<S145>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/Inverse Clarke Transform/Two phase input'
 * '<S146>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/Inverse Park Transform/Two inputs CRL'
 * '<S147>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/Inverse Park Transform/Two inputs CRL/Switch_Axis'
 * '<S148>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/PWM Reference Generator/Modulation method'
 * '<S149>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/PWM Reference Generator/Voltage Input'
 * '<S150>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/PWM Reference Generator/Modulation method/SVPWM'
 * '<S151>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/PWM Reference Generator/Modulation method/SVPWM/Half(Vmin+Vmax)'
 * '<S152>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/PWM Reference Generator/Voltage Input/Vabc'
 * '<S153>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/If Action Subsystem'
 * '<S154>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/If Action Subsystem1'
 * '<S155>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/MTPA'
 * '<S156>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/Rate Limiter Dynamic'
 * '<S157>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/Rate Limiter Dynamic1'
 * '<S158>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/Saturation Dynamic'
 * '<S159>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/Saturation Dynamic1'
 * '<S160>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/Subsystem'
 * '<S161>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/Subsystem1'
 * '<S162>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/If Action Subsystem1/PMSM Field-Weakening Controller'
 * '<S163>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/If Action Subsystem1/PMSM Field-Weakening Controller/Cartesian to Polar'
 * '<S164>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/If Action Subsystem1/PMSM Field-Weakening Controller/Modulation index'
 * '<S165>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/If Action Subsystem1/PMSM Field-Weakening Controller/Polar to Cartesian'
 * '<S166>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/If Action Subsystem1/PMSM Field-Weakening Controller/Modulation index/Prevent division by 0'
 * '<S167>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/MTPA/Saturation Dynamic'
 * '<S168>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/MTPA/Saturation Dynamic1'
 * '<S169>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S170>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/Rate Limiter Dynamic1/Saturation Dynamic'
 * '<S171>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/Subsystem/Chart'
 * '<S172>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/Subsystem1/FNR_switching'
 * '<S173>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Subsystem1/Saturation Dynamic'
 * '<S174>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem'
 * '<S175>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1'
 * '<S176>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem/Saturation Dynamic'
 * '<S177>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd'
 * '<S178>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Anti-windup'
 * '<S179>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/D Gain'
 * '<S180>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/External Derivative'
 * '<S181>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Filter'
 * '<S182>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Filter ICs'
 * '<S183>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/I Gain'
 * '<S184>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Ideal P Gain'
 * '<S185>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Ideal P Gain Fdbk'
 * '<S186>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Integrator'
 * '<S187>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Integrator ICs'
 * '<S188>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/N Copy'
 * '<S189>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/N Gain'
 * '<S190>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/P Copy'
 * '<S191>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Parallel P Gain'
 * '<S192>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Reset Signal'
 * '<S193>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Saturation'
 * '<S194>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Saturation Fdbk'
 * '<S195>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Sum'
 * '<S196>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Sum Fdbk'
 * '<S197>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Tracking Mode'
 * '<S198>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Tracking Mode Sum'
 * '<S199>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Tsamp - Integral'
 * '<S200>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Tsamp - Ngain'
 * '<S201>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/postSat Signal'
 * '<S202>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/preInt Signal'
 * '<S203>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/preSat Signal'
 * '<S204>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Anti-windup/Back Calculation'
 * '<S205>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/D Gain/External Parameters'
 * '<S206>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/External Derivative/Error'
 * '<S207>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Filter/Disc. Forward Euler Filter'
 * '<S208>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Filter ICs/Internal IC - Filter'
 * '<S209>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/I Gain/External Parameters'
 * '<S210>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Ideal P Gain/Passthrough'
 * '<S211>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Ideal P Gain Fdbk/Disabled'
 * '<S212>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Integrator/Discrete'
 * '<S213>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Integrator ICs/Internal IC'
 * '<S214>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/N Copy/Disabled'
 * '<S215>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/N Gain/External Parameters'
 * '<S216>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/P Copy/Disabled'
 * '<S217>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Parallel P Gain/External Parameters'
 * '<S218>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Reset Signal/Disabled'
 * '<S219>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Saturation/External'
 * '<S220>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Saturation/External/Saturation Dynamic'
 * '<S221>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Saturation Fdbk/Disabled'
 * '<S222>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Sum/Sum_PID'
 * '<S223>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Sum Fdbk/Disabled'
 * '<S224>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Tracking Mode/Enabled'
 * '<S225>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Tracking Mode Sum/Tracking Mode'
 * '<S226>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Tsamp - Integral/TsSignalSpecification'
 * '<S227>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Tsamp - Ngain/Passthrough'
 * '<S228>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/postSat Signal/Forward_Path'
 * '<S229>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/preInt Signal/Internal PreInt'
 * '<S230>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/preSat Signal/Forward_Path'
 */
#endif                                 /* FOC_MTPA_FWC_FF_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
