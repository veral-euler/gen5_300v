/*
 * File: FOC_MTPA_FWC_FF.h
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
  float Merge[6];                      /* '<S4>/Merge' */
  float Merge_k[2];                    /* '<S9>/Merge' */
  float Merge2[6];                     /* '<S4>/Merge2' */
  float Merge1[6];                     /* '<S4>/Merge1' */
  float T_ref;                         /* '<S5>/FNR_switching' */
} B_FOC_MTPA_FWC_FF_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  Rate_limiterBus TmpRTBAtOuter_LoopInport3_Buffe;/* synthesized block */
  float drive_sign;                   /* '<S5>/FNR_switching' */
  float UnitDelay_DSTATE;              /* '<S19>/Unit Delay' */
  float UnitDelay_DSTATE_f;            /* '<S22>/Unit Delay' */
  float Ld_calc_DSTATE;                /* '<S10>/Ld_calc' */
  float Lq_calc_DSTATE;                /* '<S10>/Lq_calc' */
  float Delay_DSTATE;                  /* '<S235>/Delay' */
  float Delay_DSTATE_l;                /* '<S154>/Delay' */
  float Integrator_DSTATE;             /* '<S121>/Integrator' */
  float Filter_DSTATE;                 /* '<S116>/Filter' */
  float Delay_DSTATE_p;                /* '<S155>/Delay' */
  float Integrator_DSTATE_h;           /* '<S67>/Integrator' */
  float Filter_DSTATE_d;               /* '<S62>/Filter' */
  float Delay_DSTATE_c;                /* '<S171>/Delay' */
  float Integrator_DSTATE_g;           /* '<S209>/Integrator' */
  float Filter_DSTATE_c;               /* '<S204>/Filter' */
  float UnitDelay_DSTATE_c;            /* '<S159>/Unit Delay' */
  float DiscreteTimeIntegrator_DSTATE; /* '<S159>/Discrete-Time Integrator' */
  float RateTransition_Buffer0;        /* '<S1>/Rate Transition' */
  float TmpRTBAtDataTypeConversion1Outp;/* synthesized block */
  float TmpRTBAtMerge1Outport1_Buffer[6];/* synthesized block */
  float TmpRTBAtOuter_LoopInport1_Buffe;/* synthesized block */
  float TmpRTBAtOuter_LoopInport6_Buffe;/* synthesized block */
  float wm_input_Buffer;               /* synthesized block */
  float counter;                       /* '<S5>/FNR_switching' */
  float init_speed;                    /* '<S5>/FNR_switching' */
  float mid_speed;                     /* '<S5>/FNR_switching' */
  float rpm_prev;                      /* '<S5>/FNR_switching' */
  float max_negTorque;                 /* '<S5>/FNR_switching' */
  uint32_t durationCounter_1;          /* '<S5>/FNR_switching' */
  uint32_t durationCounter_2;          /* '<S5>/FNR_switching' */
  uint32_t durationCounter_1_m;        /* '<S5>/FNR_switching' */
  uint32_t durationCounter_1_l;        /* '<S5>/FNR_switching' */
  uint32_t durationCounter_2_e;        /* '<S5>/FNR_switching' */
  int8_t DiscreteTimeIntegrator_PrevRese;/* '<S159>/Discrete-Time Integrator' */
  uint8_t is_active_c2_FOC_MTPA_FWC_FF;/* '<S5>/FNR_switching' */
  uint8_t is_c2_FOC_MTPA_FWC_FF;       /* '<S5>/FNR_switching' */
  uint8_t is_Neutral;                  /* '<S5>/FNR_switching' */
  uint8_t is_active_c3_FOC_MTPA_FWC_FF;/* '<S158>/Chart' */
  uint8_t is_c3_FOC_MTPA_FWC_FF;       /* '<S158>/Chart' */
  bool icLoad;                         /* '<S10>/Ld_calc' */
  bool icLoad_o;                       /* '<S10>/Lq_calc' */
  bool icLoad_e;                       /* '<S235>/Delay' */
  bool icLoad_l;                       /* '<S154>/Delay' */
  bool icLoad_p;                       /* '<S155>/Delay' */
  bool icLoad_k;                       /* '<S171>/Delay' */
} DW_FOC_MTPA_FWC_FF_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  float Ref_Speed_mech_rpm;            /* '<Root>/Ref_Speed_mech_rpm' */
  float ActualSpeed_mech_radsec;       /* '<Root>/Actual Speed_mech_rad//sec' */
  float angle;                         /* '<Root>/angle' */
  float PhaseCurrent[3];              /* '<Root>/Phase Current' */
  PID_MTPABus MTPA_PID;                /* '<Root>/MTPA_PID' */
  Rate_limiterBus Rate_limiter;        /* '<Root>/Rate_limiter' */
  IIR_FilterBus IIR_Filter_Coefficient;/* '<Root>/IIR_Filter_Coefficient' */
  Motor_ParametersBus Motor_Parameters;/* '<Root>/Motor_Parameters' */
  float BusVoltage_V;                  /* '<Root>/Bus_Voltage' */
  ThrottleBus Throttle_input;          /* '<Root>/Throttle_input' */
  Id_Iq_MTPA_limitBus Id_Iq_MTPA_limit;/* '<Root>/Id_Iq_MTPA_limit' */
  float Iq_Torque_ratio;              /* '<Root>/Iq_Torque_ratio' */
  bool Speed_1_Torque_0;              /* '<Root>/Speed_1_Torque_0' */
  float RefTrq;                        /* '<Root>/T_ref' */
  float Is_max;                       /* '<Root>/Is_max' */
  float Drive_State;                   /* '<Root>/Drive_State' */
  FWCBus FWC_values;                   /* '<Root>/FWC_values' */
  float RPM_min_limit;                 /* '<Root>/RPM_min_limit' */
  RegenBus Regen;                      /* '<Root>/Regen' */
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
  bool MTPA_FWC_condition;             /* '<Root>/MTPA_FWC_condition' */
  bool Throttle_en;                    /* '<Root>/Throttle_en' */
  ThrottleState Throttle_State;        /* '<Root>/Throttle_State' */
  bool Throttle_error;                 /* '<Root>/Throttle_error' */
  float Ref_speed_out_RPM;             /* '<Root>/Ref_speed_out_RPM' */
  float T_gen;                         /* '<Root>/T_gen' */
  float T_ref_FNR;                     /* '<Root>/T_ref_FNR' */
  float Actual_torque_from_meas;       /* '<Root>/Actual_torque_from_meas' */
  float Actual_torque_from_ref;        /* '<Root>/Actual_torque_from_ref' */
  float I_mag;                         /* '<Root>/I_mag' */
  float I_qo;                          /* '<Root>/I_qo' */
  bool Regen_Mode;                     /* '<Root>/Regen_Mode' */
  bool PID_Switch;                     /* '<Root>/PID_Switch' */
  float Ld;                            /* '<Root>/Ld' */
  float Lq;                            /* '<Root>/Lq' */
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
 * Block '<S16>/Data Type Duplicate' : Unused code path elimination
 * Block '<S12>/Data Type Duplicate' : Unused code path elimination
 * Block '<S13>/Data Type Duplicate' : Unused code path elimination
 * Block '<S23>/Data Type Duplicate' : Unused code path elimination
 * Block '<S23>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S30>/Data Type Duplicate' : Unused code path elimination
 * Block '<S31>/Data Type Duplicate' : Unused code path elimination
 * Block '<S26>/Data Type Duplicate' : Unused code path elimination
 * Block '<S26>/Data Type Propagation' : Unused code path elimination
 * Block '<S27>/Data Type Duplicate' : Unused code path elimination
 * Block '<S27>/Data Type Propagation' : Unused code path elimination
 * Block '<S75>/Data Type Duplicate' : Unused code path elimination
 * Block '<S75>/Data Type Propagation' : Unused code path elimination
 * Block '<S129>/Data Type Duplicate' : Unused code path elimination
 * Block '<S129>/Data Type Propagation' : Unused code path elimination
 * Block '<S29>/Scope' : Unused code path elimination
 * Block '<S143>/Data Type Duplicate' : Unused code path elimination
 * Block '<S144>/Data Type Duplicate' : Unused code path elimination
 * Block '<S144>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S142>/Data Type Duplicate' : Unused code path elimination
 * Block '<S8>/Scope' : Unused code path elimination
 * Block '<S152>/Display' : Unused code path elimination
 * Block '<S153>/Display' : Unused code path elimination
 * Block '<S164>/Data Type Duplicate' : Unused code path elimination
 * Block '<S164>/Data Type Propagation' : Unused code path elimination
 * Block '<S165>/Data Type Duplicate' : Unused code path elimination
 * Block '<S165>/Data Type Propagation' : Unused code path elimination
 * Block '<S154>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S166>/Data Type Duplicate' : Unused code path elimination
 * Block '<S166>/Data Type Propagation' : Unused code path elimination
 * Block '<S155>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S167>/Data Type Duplicate' : Unused code path elimination
 * Block '<S167>/Data Type Propagation' : Unused code path elimination
 * Block '<S156>/Data Type Duplicate' : Unused code path elimination
 * Block '<S156>/Data Type Propagation' : Unused code path elimination
 * Block '<S157>/Data Type Duplicate' : Unused code path elimination
 * Block '<S157>/Data Type Propagation' : Unused code path elimination
 * Block '<S3>/Display' : Unused code path elimination
 * Block '<S3>/Display2' : Unused code path elimination
 * Block '<S173>/Data Type Duplicate' : Unused code path elimination
 * Block '<S173>/Data Type Propagation' : Unused code path elimination
 * Block '<S3>/Scope1' : Unused code path elimination
 * Block '<S217>/Data Type Duplicate' : Unused code path elimination
 * Block '<S217>/Data Type Propagation' : Unused code path elimination
 * Block '<S235>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S236>/Data Type Duplicate' : Unused code path elimination
 * Block '<S236>/Data Type Propagation' : Unused code path elimination
 * Block '<S1>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S15>/Kalpha' : Eliminated nontunable gain of 1
 * Block '<S15>/Kbeta' : Eliminated nontunable gain of 1
 * Block '<S59>/Kb' : Eliminated nontunable gain of 1
 * Block '<S113>/Kb' : Eliminated nontunable gain of 1
 * Block '<S143>/Ka' : Eliminated nontunable gain of 1
 * Block '<S143>/Kb' : Eliminated nontunable gain of 1
 * Block '<S143>/Kc' : Eliminated nontunable gain of 1
 * Block '<S154>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S155>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S171>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S201>/Kb' : Eliminated nontunable gain of 1
 * Block '<S235>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S12>/FilterConstant' : Unused code path elimination
 * Block '<S12>/OneMinusFilterConstant' : Unused code path elimination
 * Block '<S12>/UseInputPort' : Unused code path elimination
 * Block '<S13>/FilterConstant' : Unused code path elimination
 * Block '<S13>/OneMinusFilterConstant' : Unused code path elimination
 * Block '<S13>/UseInputPort' : Unused code path elimination
 * Block '<S24>/Offset' : Unused code path elimination
 * Block '<S24>/Unary_Minus' : Unused code path elimination
 * Block '<S145>/Offset' : Unused code path elimination
 * Block '<S145>/Unary_Minus' : Unused code path elimination
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
 * '<S2>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop'
 * '<S3>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop'
 * '<S4>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/PID_Selection'
 * '<S5>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Subsystem3'
 * '<S6>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park'
 * '<S7>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop'
 * '<S8>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park'
 * '<S9>'   : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC'
 * '<S10>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Motor_Parameter'
 * '<S11>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/Clarke Transform'
 * '<S12>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/IIR Filter'
 * '<S13>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/IIR Filter1'
 * '<S14>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/Park Transform'
 * '<S15>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/Clarke Transform/Two phase input'
 * '<S16>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/Clarke Transform/Two phase input/Two phase CRL wrap'
 * '<S17>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/IIR Filter/IIR Filter'
 * '<S18>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/IIR Filter/IIR Filter/Low-pass'
 * '<S19>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/IIR Filter/IIR Filter/Low-pass/IIR Low Pass Filter'
 * '<S20>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/IIR Filter1/IIR Filter'
 * '<S21>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/IIR Filter1/IIR Filter/Low-pass'
 * '<S22>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/IIR Filter1/IIR Filter/Low-pass/IIR Low Pass Filter'
 * '<S23>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/Park Transform/Two inputs CRL'
 * '<S24>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Clarke_Park/Park Transform/Two inputs CRL/Switch_Axis'
 * '<S25>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Feed_Forward'
 * '<S26>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Saturation Dynamic'
 * '<S27>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Saturation Dynamic1'
 * '<S28>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem'
 * '<S29>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1'
 * '<S30>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Feed_Forward/Vd_sat'
 * '<S31>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Feed_Forward/Vq_sat'
 * '<S32>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq'
 * '<S33>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Anti-windup'
 * '<S34>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/D Gain'
 * '<S35>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/External Derivative'
 * '<S36>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Filter'
 * '<S37>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Filter ICs'
 * '<S38>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/I Gain'
 * '<S39>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Ideal P Gain'
 * '<S40>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Ideal P Gain Fdbk'
 * '<S41>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Integrator'
 * '<S42>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Integrator ICs'
 * '<S43>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/N Copy'
 * '<S44>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/N Gain'
 * '<S45>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/P Copy'
 * '<S46>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Parallel P Gain'
 * '<S47>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Reset Signal'
 * '<S48>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Saturation'
 * '<S49>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Saturation Fdbk'
 * '<S50>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Sum'
 * '<S51>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Sum Fdbk'
 * '<S52>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Tracking Mode'
 * '<S53>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Tracking Mode Sum'
 * '<S54>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Tsamp - Integral'
 * '<S55>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Tsamp - Ngain'
 * '<S56>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/postSat Signal'
 * '<S57>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/preInt Signal'
 * '<S58>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/preSat Signal'
 * '<S59>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Anti-windup/Back Calculation'
 * '<S60>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/D Gain/External Parameters'
 * '<S61>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/External Derivative/Error'
 * '<S62>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Filter/Disc. Forward Euler Filter'
 * '<S63>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Filter ICs/Internal IC - Filter'
 * '<S64>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/I Gain/External Parameters'
 * '<S65>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Ideal P Gain/Passthrough'
 * '<S66>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Ideal P Gain Fdbk/Disabled'
 * '<S67>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Integrator/Discrete'
 * '<S68>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Integrator ICs/Internal IC'
 * '<S69>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/N Copy/Disabled'
 * '<S70>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/N Gain/External Parameters'
 * '<S71>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/P Copy/Disabled'
 * '<S72>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Parallel P Gain/External Parameters'
 * '<S73>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Reset Signal/Disabled'
 * '<S74>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Saturation/External'
 * '<S75>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Saturation/External/Saturation Dynamic'
 * '<S76>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Saturation Fdbk/Disabled'
 * '<S77>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Sum/Sum_PID'
 * '<S78>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Sum Fdbk/Disabled'
 * '<S79>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Tracking Mode/Disabled'
 * '<S80>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Tracking Mode Sum/Passthrough'
 * '<S81>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Tsamp - Integral/TsSignalSpecification'
 * '<S82>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/Tsamp - Ngain/Passthrough'
 * '<S83>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/postSat Signal/Forward_Path'
 * '<S84>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/preInt Signal/Internal PreInt'
 * '<S85>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem/PI Vq/preSat Signal/Forward_Path'
 * '<S86>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd'
 * '<S87>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Anti-windup'
 * '<S88>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/D Gain'
 * '<S89>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/External Derivative'
 * '<S90>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Filter'
 * '<S91>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Filter ICs'
 * '<S92>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/I Gain'
 * '<S93>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain'
 * '<S94>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain Fdbk'
 * '<S95>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Integrator'
 * '<S96>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Integrator ICs'
 * '<S97>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/N Copy'
 * '<S98>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/N Gain'
 * '<S99>'  : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/P Copy'
 * '<S100>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Parallel P Gain'
 * '<S101>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Reset Signal'
 * '<S102>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Saturation'
 * '<S103>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Saturation Fdbk'
 * '<S104>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Sum'
 * '<S105>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Sum Fdbk'
 * '<S106>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Tracking Mode'
 * '<S107>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Tracking Mode Sum'
 * '<S108>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Tsamp - Integral'
 * '<S109>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Tsamp - Ngain'
 * '<S110>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/postSat Signal'
 * '<S111>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/preInt Signal'
 * '<S112>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/preSat Signal'
 * '<S113>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Anti-windup/Back Calculation'
 * '<S114>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/D Gain/External Parameters'
 * '<S115>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/External Derivative/Error'
 * '<S116>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Filter/Disc. Forward Euler Filter'
 * '<S117>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Filter ICs/Internal IC - Filter'
 * '<S118>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/I Gain/External Parameters'
 * '<S119>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain/Passthrough'
 * '<S120>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Ideal P Gain Fdbk/Disabled'
 * '<S121>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Integrator/Discrete'
 * '<S122>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Integrator ICs/Internal IC'
 * '<S123>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/N Copy/Disabled'
 * '<S124>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/N Gain/External Parameters'
 * '<S125>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/P Copy/Disabled'
 * '<S126>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Parallel P Gain/External Parameters'
 * '<S127>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Reset Signal/Disabled'
 * '<S128>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Saturation/External'
 * '<S129>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Saturation/External/Saturation Dynamic'
 * '<S130>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Saturation Fdbk/Disabled'
 * '<S131>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Sum/Sum_PID'
 * '<S132>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Sum Fdbk/Disabled'
 * '<S133>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Tracking Mode/Disabled'
 * '<S134>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Tracking Mode Sum/Passthrough'
 * '<S135>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Tsamp - Integral/TsSignalSpecification'
 * '<S136>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/Tsamp - Ngain/Passthrough'
 * '<S137>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/postSat Signal/Forward_Path'
 * '<S138>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/preInt Signal/Internal PreInt'
 * '<S139>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inner PID loop/Subsystem1/PI Vd/preSat Signal/Forward_Path'
 * '<S140>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/Inverse Clarke Transform'
 * '<S141>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/Inverse Park Transform'
 * '<S142>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/PWM Reference Generator'
 * '<S143>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/Inverse Clarke Transform/Two phase input'
 * '<S144>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/Inverse Park Transform/Two inputs CRL'
 * '<S145>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/Inverse Park Transform/Two inputs CRL/Switch_Axis'
 * '<S146>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/PWM Reference Generator/Modulation method'
 * '<S147>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/PWM Reference Generator/Voltage Input'
 * '<S148>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/PWM Reference Generator/Modulation method/SVPWM'
 * '<S149>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/PWM Reference Generator/Modulation method/SVPWM/Half(Vmin+Vmax)'
 * '<S150>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Inverse_Clarke_Park/PWM Reference Generator/Voltage Input/Vabc'
 * '<S151>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/If Action Subsystem'
 * '<S152>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/If Action Subsystem1'
 * '<S153>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/MTPA'
 * '<S154>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/Rate Limiter Dynamic'
 * '<S155>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/Rate Limiter Dynamic1'
 * '<S156>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/Saturation Dynamic'
 * '<S157>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/Saturation Dynamic1'
 * '<S158>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/Subsystem'
 * '<S159>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/If Action Subsystem1/PMSM FWC'
 * '<S160>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/If Action Subsystem1/PMSM FWC/Cartesian to Polar'
 * '<S161>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/If Action Subsystem1/PMSM FWC/Modulation index'
 * '<S162>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/If Action Subsystem1/PMSM FWC/Polar to Cartesian'
 * '<S163>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/If Action Subsystem1/PMSM FWC/Modulation index/Prevent division by 0'
 * '<S164>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/MTPA/Saturation Dynamic'
 * '<S165>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/MTPA/Saturation Dynamic1'
 * '<S166>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S167>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/Rate Limiter Dynamic1/Saturation Dynamic'
 * '<S168>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/MTPA_FWC/Subsystem/Chart'
 * '<S169>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Motor_Parameter/Subsystem'
 * '<S170>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Inner_Loop/Motor_Parameter/Subsystem1'
 * '<S171>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Rate_limiter'
 * '<S172>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1'
 * '<S173>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Rate_limiter/Saturation Dynamic'
 * '<S174>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd'
 * '<S175>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Anti-windup'
 * '<S176>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/D Gain'
 * '<S177>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/External Derivative'
 * '<S178>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Filter'
 * '<S179>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Filter ICs'
 * '<S180>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/I Gain'
 * '<S181>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Ideal P Gain'
 * '<S182>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Ideal P Gain Fdbk'
 * '<S183>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Integrator'
 * '<S184>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Integrator ICs'
 * '<S185>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/N Copy'
 * '<S186>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/N Gain'
 * '<S187>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/P Copy'
 * '<S188>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Parallel P Gain'
 * '<S189>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Reset Signal'
 * '<S190>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Saturation'
 * '<S191>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Saturation Fdbk'
 * '<S192>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Sum'
 * '<S193>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Sum Fdbk'
 * '<S194>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Tracking Mode'
 * '<S195>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Tracking Mode Sum'
 * '<S196>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Tsamp - Integral'
 * '<S197>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Tsamp - Ngain'
 * '<S198>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/postSat Signal'
 * '<S199>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/preInt Signal'
 * '<S200>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/preSat Signal'
 * '<S201>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Anti-windup/Back Calculation'
 * '<S202>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/D Gain/External Parameters'
 * '<S203>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/External Derivative/Error'
 * '<S204>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Filter/Disc. Forward Euler Filter'
 * '<S205>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Filter ICs/Internal IC - Filter'
 * '<S206>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/I Gain/External Parameters'
 * '<S207>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Ideal P Gain/Passthrough'
 * '<S208>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Ideal P Gain Fdbk/Disabled'
 * '<S209>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Integrator/Discrete'
 * '<S210>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Integrator ICs/Internal IC'
 * '<S211>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/N Copy/Disabled'
 * '<S212>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/N Gain/External Parameters'
 * '<S213>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/P Copy/Disabled'
 * '<S214>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Parallel P Gain/External Parameters'
 * '<S215>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Reset Signal/Disabled'
 * '<S216>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Saturation/External'
 * '<S217>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Saturation/External/Saturation Dynamic'
 * '<S218>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Saturation Fdbk/Disabled'
 * '<S219>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Sum/Sum_PID'
 * '<S220>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Sum Fdbk/Disabled'
 * '<S221>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Tracking Mode/Disabled'
 * '<S222>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Tracking Mode Sum/Passthrough'
 * '<S223>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Tsamp - Integral/TsSignalSpecification'
 * '<S224>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/Tsamp - Ngain/Passthrough'
 * '<S225>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/postSat Signal/Forward_Path'
 * '<S226>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/preInt Signal/Internal PreInt'
 * '<S227>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Outer_Loop/Subsystem1/PI Vd/preSat Signal/Forward_Path'
 * '<S228>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/PID_Selection/If Action Subsystem'
 * '<S229>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/PID_Selection/If Action Subsystem1'
 * '<S230>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/PID_Selection/If Action Subsystem2'
 * '<S231>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/PID_Selection/If Action Subsystem3'
 * '<S232>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/PID_Selection/If Action Subsystem4'
 * '<S233>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/PID_Selection/If Action Subsystem5'
 * '<S234>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Subsystem3/FNR_switching'
 * '<S235>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Subsystem3/Rate Limiter Dynamic'
 * '<S236>' : 'IPMSM_motor_FOC_MTPA_FWC_FF_try_default_FW/FOC_MTPA_FWC_FF/Subsystem3/Rate Limiter Dynamic/Saturation Dynamic'
 */
#endif                                 /* FOC_MTPA_FWC_FF_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
