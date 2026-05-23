/*
 * File: Angle_to_Speed.h
 *
 * Code generated for Simulink model 'Angle_to_Speed'.
 *
 * Model version                  : 1.15
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Fri May 22 16:16:07 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef Angle_to_Speed_h_
#define Angle_to_Speed_h_
#ifndef Angle_to_Speed_COMMON_INCLUDES_
#define Angle_to_Speed_COMMON_INCLUDES_
#include <stdbool.h>
#include <stdint.h>
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "math.h"
#endif                                 /* Angle_to_Speed_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct Angle_to_Speed_tag_RTM Angle_to_Speed_RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  float Probe[2];                      /* '<S4>/Probe' */
  float Integrator_DSTATE;             /* '<S10>/Integrator' */
  uint32_t CircBufIdx;                 /* '<S3>/Delay' */
  uint16_t Delay_DSTATE[29];           /* '<S3>/Delay' */
  int8_t Integrator_PrevResetState;    /* '<S10>/Integrator' */
  uint8_t Integrator_IC_LOADING;       /* '<S10>/Integrator' */
} Angle_to_Speed_DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  double Theta;                        /* '<Root>/Theta' */
} Angle_to_Speed_ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  float Speed;                         /* '<Root>/Speed' */
  float Speed_filtered;                /* '<Root>/Speed_filtered' */
} Angle_to_Speed_ExtY;

/* Real-time Model Data Structure */
struct Angle_to_Speed_tag_RTM {
  const char * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern Angle_to_Speed_DW rtAngle_to_Speed_DW;

/* External inputs (root inport signals with default storage) */
extern Angle_to_Speed_ExtU rtAngle_to_Speed_U;

/* External outputs (root outports fed by signals with default storage) */
extern Angle_to_Speed_ExtY rtAngle_to_Speed_Y;

/* Model entry point functions */
extern void Angle_to_Speed_initialize(void);
extern void Angle_to_Speed_step(void);

/* Real-time Model object */
extern Angle_to_Speed_RT_MODEL *const rtAngle_to_Speed_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S3>/DataTypeSet' : Unused code path elimination
 * Block '<S3>/fixdtDatatype' : Unused code path elimination
 * Block '<S10>/Saturation' : Eliminated Saturate block
 * Block '<S2>/K' : Eliminated nontunable gain of 1
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
 * hilite_system('elec_angle_to_elec_speed_V1/Angle_to_Speed')    - opens subsystem elec_angle_to_elec_speed_V1/Angle_to_Speed
 * hilite_system('elec_angle_to_elec_speed_V1/Angle_to_Speed/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'elec_angle_to_elec_speed_V1'
 * '<S1>'   : 'elec_angle_to_elec_speed_V1/Angle_to_Speed'
 * '<S2>'   : 'elec_angle_to_elec_speed_V1/Angle_to_Speed/Low-Pass Filter (Discrete or Continuous)'
 * '<S3>'   : 'elec_angle_to_elec_speed_V1/Angle_to_Speed/Speed Measurement'
 * '<S4>'   : 'elec_angle_to_elec_speed_V1/Angle_to_Speed/Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant'
 * '<S5>'   : 'elec_angle_to_elec_speed_V1/Angle_to_Speed/Low-Pass Filter (Discrete or Continuous)/Initialization'
 * '<S6>'   : 'elec_angle_to_elec_speed_V1/Angle_to_Speed/Low-Pass Filter (Discrete or Continuous)/Integrator (Discrete or Continuous)'
 * '<S7>'   : 'elec_angle_to_elec_speed_V1/Angle_to_Speed/Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant/Compare To Constant'
 * '<S8>'   : 'elec_angle_to_elec_speed_V1/Angle_to_Speed/Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant/Compare To Zero'
 * '<S9>'   : 'elec_angle_to_elec_speed_V1/Angle_to_Speed/Low-Pass Filter (Discrete or Continuous)/Initialization/Init_u'
 * '<S10>'  : 'elec_angle_to_elec_speed_V1/Angle_to_Speed/Low-Pass Filter (Discrete or Continuous)/Integrator (Discrete or Continuous)/Discrete'
 * '<S11>'  : 'elec_angle_to_elec_speed_V1/Angle_to_Speed/Speed Measurement/DT_Handle'
 * '<S12>'  : 'elec_angle_to_elec_speed_V1/Angle_to_Speed/Speed Measurement/DT_Handle/floating-point'
 */
#endif                                 /* Angle_to_Speed_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
