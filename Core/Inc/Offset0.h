/*
 * File: Offset0.h
 *
 * Code generated for Simulink model 'Offset0'.
 *
 * Model version                  : 1.0
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Sat May 16 13:56:28 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef Offset0_h_
#define Offset0_h_
#ifndef Offset0_COMMON_INCLUDES_
#define Offset0_COMMON_INCLUDES_
#include <stdbool.h>
#include <stdint.h>
#include "complex_types.h"
#include "rt_nonfinite.h"
#include "math.h"
#endif                                 /* Offset0_COMMON_INCLUDES_ */

#include "Offset0_types.h"
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
  float MotorRpmRef;                   /* '<S1>/Chart' */
  float error;                         /* '<S5>/error' */
  uint16_t flag_C;                     /* '<S1>/Chart' */
} B_Offset0_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  float Delay_DSTATE;                  /* '<S4>/Delay' */
  float UnitDelay_DSTATE;              /* '<S2>/Unit Delay' */
  float Angle_f;                       /* '<S1>/Chart' */
  float Vd_samp;                       /* '<S1>/Chart' */
  float Vq_samp;                       /* '<S1>/Chart' */
  float sample;                        /* '<S1>/Chart' */
  float sample2;                       /* '<S1>/Chart' */
  float error_sample;                  /* '<S1>/Chart' */
  float errorM;                        /* '<S1>/Chart' */
  uint16_t UnitDelay1_DSTATE;          /* '<S2>/Unit Delay1' */
  uint16_t timer2;                     /* '<S1>/Chart' */
  uint16_t timer4;                     /* '<S1>/Chart' */
  uint16_t Repeat_CCW;                 /* '<S1>/Chart' */
  uint16_t Repeat_CW;                  /* '<S1>/Chart' */
  uint16_t Rotate_CCW;                 /* '<S1>/Chart' */
  uint16_t flag;                       /* '<S1>/Chart' */
  uint16_t flag4;                      /* '<S1>/Chart' */
  uint16_t timer1;                     /* '<S1>/Chart' */
  uint16_t timer3;                     /* '<S1>/Chart' */
  uint16_t temporalCounter_i1;         /* '<S1>/Chart' */
  uint8_t is_active_c3_Offset0;        /* '<S1>/Chart' */
  uint8_t is_c3_Offset0;               /* '<S1>/Chart' */
  uint8_t is_Coarse_offset_angle;      /* '<S1>/Chart' */
  uint8_t is_Fine_Offset_angle;        /* '<S1>/Chart' */
  uint8_t is_Average_Offset_calculation_C;/* '<S1>/Chart' */
  uint8_t is_Average_Offset_calculation_e;/* '<S1>/Chart' */
  uint8_t temporalCounter_i2;          /* '<S1>/Chart' */
  bool icLoad;                         /* '<S4>/Delay' */
  bool Subsystem_MODE;                 /* '<S2>/Subsystem' */
} DW_Offset0_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  float Vq;                            /* '<Root>/Vq' */
  float Vd;                            /* '<Root>/Vd' */
  float RATED_RPM;                     /* '<Root>/RATED_RPM' */
  uint16_t POLE_PAIRS;                 /* '<Root>/POLE_PAIRS' */
  float NO_OF_V_SAMPLES;               /* '<Root>/NO_OF_V_SAMPLES' */
  uint16_t NO_OF_CW_SAMPLE;            /* '<Root>/NO_OF_CW_SAMPLE' */
  uint16_t NO_OF_CCW_SAMPLE;           /* '<Root>/NO_OF_CCW_SAMPLE' */
  float Vd_MAX;                        /* '<Root>/Vd_MAX' */
  float Vd_MIN;                        /* '<Root>/Vd_MIN' */
  float Speed_Ramp_up;                 /* '<Root>/Speed_Ramp_up' */
  float Speed_Ramp_down;               /* '<Root>/Speed_Ramp_down' */
  float Pwmangle;                      /* '<Root>/Pwmangle' */
  float AUTO_TUNING_IDREFF;            /* '<Root>/AUTO_TUNING_IDREFF' */
  float AUTOTUNE_ANGLE_INCREMENTT;     /* '<Root>/AUTOTUNE_ANGLE_INCREMENTT' */
  float AUTOTUNE_IDREF_INCREMENTT;     /* '<Root>/AUTOTUNE_IDREF_INCREMENTT' */
  float Pole_pairs;                    /* '<Root>/Pole_pairs' */
  float IDREF_MAX_LIMITT;              /* '<Root>/IDREF_MAX_LIMITT' */
  uint16_t ALIGNEMENT_TMOO;            /* '<Root>/ALIGNEMENT_TMOO' */
  float MAX_SAMPLE_ROTATION;           /* '<Root>/MAX_SAMPLE_ROTATION' */
  uint16_t WAIT_TIME;                  /* '<Root>/WAIT_TIME' */
} ExtU_Offset0_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  float Vq_avg;                        /* '<Root>/Vq_avg' */
  float Offset_CW;                     /* '<Root>/Offset_CW' */
  float Offset_CCW;                    /* '<Root>/Offset_CCW' */
  float MotorRpmRef;                   /* '<Root>/MotorRpmRef' */
  uint16_t AutotuneCompleteflag;       /* '<Root>/ AutotuneCompleteflag' */
  float Vd_avg;                        /* '<Root>/Vd_avg' */
  uint16_t FNR;                        /* '<Root>/FNR' */
  float Vd_net;                        /* '<Root>/Vd_net' */
  uint16_t RR;                         /* '<Root>/RR' */
  float Angle;                         /* '<Root>/Angle' */
  float Idref;                         /* '<Root>/Idref' */
  float Iqref;                         /* '<Root>/Iqref' */
  float Electricalangle;               /* '<Root>/Electricalangle' */
  float initial_offset;                /* '<Root>/initial_offset' */
  float error_C;                       /* '<Root>/error_C' */
  float initial_offset2;               /* '<Root>/initial_offset2' */
  float error_M;                       /* '<Root>/error_M' */
  uint16_t FOC_closed_loop;            /* '<Root>/FOC_closed_loop' */
  float Offset_CW_Mech;                /* '<Root>/Offset_CW_Mech' */
  float Offset_CCW_Mech;               /* '<Root>/Offset_CCW_Mech' */
  float initial_offset_Mech;           /* '<Root>/initial_offset_Mech' */
} ExtY_Offset0_T;

/* Real-time Model Data Structure */
struct tag_RTM_Offset0_T {
  const char * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_Offset0_T Offset0_B;

/* Block states (default storage) */
extern DW_Offset0_T Offset0_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_Offset0_T Offset0_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Offset0_T Offset0_Y;

/* Model entry point functions */
extern void Offset0_initialize(void);
extern void Offset0_step(void);
extern void Offset0_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Offset0_T *const Offset0_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Scope' : Unused code path elimination
 * Block '<S2>/Scope1' : Unused code path elimination
 * Block '<S2>/Scope2' : Unused code path elimination
 * Block '<S2>/Scope3' : Unused code path elimination
 * Block '<S2>/Scope4' : Unused code path elimination
 * Block '<S4>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/Data Type Propagation' : Unused code path elimination
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope2' : Unused code path elimination
 * Block '<S4>/Zero-Order Hold' : Eliminated since input and output rates are identical
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
 * hilite_system('Integrated_Model_offset_24B/Offset')    - opens subsystem Integrated_Model_offset_24B/Offset
 * hilite_system('Integrated_Model_offset_24B/Offset/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Integrated_Model_offset_24B'
 * '<S1>'   : 'Integrated_Model_offset_24B/Offset'
 * '<S2>'   : 'Integrated_Model_offset_24B/Offset/Average_calculation'
 * '<S3>'   : 'Integrated_Model_offset_24B/Offset/Chart'
 * '<S4>'   : 'Integrated_Model_offset_24B/Offset/Rate Limiter Dynamic'
 * '<S5>'   : 'Integrated_Model_offset_24B/Offset/Average_calculation/Subsystem'
 * '<S6>'   : 'Integrated_Model_offset_24B/Offset/Rate Limiter Dynamic/Saturation Dynamic'
 */
#endif                                 /* Offset0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
