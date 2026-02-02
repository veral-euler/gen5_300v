/*
 * File: MCU_Protections.h
 *
 * Code generated for Simulink model 'MCU_Protections'.
 *
 * Model version                  : 1.15
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Fri Jan 30 19:41:21 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef MCU_Protections_h_
#define MCU_Protections_h_
#ifndef MCU_Protections_COMMON_INCLUDES_
#define MCU_Protections_COMMON_INCLUDES_
#include <stdbool.h>
#include <stdint.h>
#include "complex_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "math.h"
#endif                                 /* MCU_Protections_COMMON_INCLUDES_ */

#include "MCU_Protections_types.h"
#include "zero_crossing_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block states (default storage) for system '<S6>/NEGATIVE Edge' */
typedef struct {
  bool NEGATIVEEdge_MODE;              /* '<S6>/NEGATIVE Edge' */
} DW_NEGATIVEEdge_MCU_Protectio_T;

/* Block states (default storage) for system '<S6>/POSITIVE Edge' */
typedef struct {
  bool POSITIVEEdge_MODE;              /* '<S6>/POSITIVE Edge' */
} DW_POSITIVEEdge_MCU_Protectio_T;

/* Block signals (default storage) */
typedef struct {
  bool OR[2];                          /* '<S5>/OR' */
  bool RelationalOperator1;            /* '<S14>/Relational Operator1' */
  bool RelationalOperator1_h;          /* '<S13>/Relational Operator1' */
  bool RelationalOperator1_j;          /* '<S9>/Relational Operator1' */
  bool RelationalOperator1_i;          /* '<S8>/Relational Operator1' */
} B_MCU_Protections_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  double count_current_error;          /* '<S1>/Chart' */
  double count_current_warning;        /* '<S1>/Chart' */
  uint32_t durationCounter_1;          /* '<S1>/Chart' */
  uint32_t durationCounter_2;          /* '<S1>/Chart' */
  uint32_t durationCounter_1_e;        /* '<S1>/Chart' */
  uint32_t durationCounter_2_h;        /* '<S1>/Chart' */
  uint32_t durationCounter_1_b;        /* '<S1>/Chart' */
  uint32_t durationCounter_2_b;        /* '<S1>/Chart' */
  uint32_t durationCounter_1_d;        /* '<S1>/Chart' */
  uint32_t durationCounter_2_br;       /* '<S1>/Chart' */
  uint32_t durationCounter_1_ez;       /* '<S1>/Chart' */
  uint32_t durationCounter_2_p;        /* '<S1>/Chart' */
  uint32_t durationCounter_1_i;        /* '<S1>/Chart' */
  uint32_t durationCounter_2_k;        /* '<S1>/Chart' */
  uint32_t durationCounter_1_p;        /* '<S1>/Chart' */
  uint32_t durationCounter_1_pp;       /* '<S1>/Chart' */
  uint32_t durationCounter_2_m;        /* '<S1>/Chart' */
  uint32_t durationCounter_2_c;        /* '<S1>/Chart' */
  uint32_t durationCounter_3;          /* '<S1>/Chart' */
  uint32_t durationCounter_4;          /* '<S1>/Chart' */
  uint32_t durationCounter_1_k;        /* '<S1>/Chart' */
  uint32_t durationCounter_2_mw;       /* '<S1>/Chart' */
  uint32_t durationCounter_1_f;        /* '<S1>/Chart' */
  uint32_t durationCounter_1_o;        /* '<S1>/Chart' */
  uint32_t durationCounter_2_cm;       /* '<S1>/Chart' */
  uint32_t durationCounter_2_j;        /* '<S1>/Chart' */
  uint32_t durationCounter_3_o;        /* '<S1>/Chart' */
  uint32_t durationCounter_4_a;        /* '<S1>/Chart' */
  uint32_t durationCounter_1_bx;       /* '<S1>/Chart' */
  uint32_t durationCounter_2_m0;       /* '<S1>/Chart' */
  uint8_t is_active_c3_MCU_Protections;/* '<S1>/Chart' */
  uint8_t is_Current_Protection;       /* '<S1>/Chart' */
  uint8_t is_Init;                     /* '<S1>/Chart' */
  uint8_t is_Warning;                  /* '<S1>/Chart' */
  uint8_t is_MC_Temperature_Protection;/* '<S1>/Chart' */
  uint8_t is_Motor_Temperature_Protection;/* '<S1>/Chart' */
  uint8_t is_Aux_Voltage_Protection;   /* '<S1>/Chart' */
  uint8_t is_Bus_Voltage_Protection;   /* '<S1>/Chart' */
  bool Memory_PreviousInput;           /* '<S6>/Memory' */
  bool Memory_PreviousInput_k;         /* '<S11>/Memory' */
  DW_POSITIVEEdge_MCU_Protectio_T POSITIVEEdge_j;/* '<S11>/POSITIVE Edge' */
  DW_NEGATIVEEdge_MCU_Protectio_T NEGATIVEEdge_f;/* '<S11>/NEGATIVE Edge' */
  DW_POSITIVEEdge_MCU_Protectio_T POSITIVEEdge;/* '<S6>/POSITIVE Edge' */
  DW_NEGATIVEEdge_MCU_Protectio_T NEGATIVEEdge;/* '<S6>/NEGATIVE Edge' */
} DW_MCU_Protections_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState TriggeredSubsystem_Trig_ZCE;/* '<S12>/Triggered Subsystem' */
  ZCSigState TriggeredSubsystem_Trig_ZCE_n;/* '<S7>/Triggered Subsystem' */
} PrevZCX_MCU_Protections_T;

/* Invariant block signals (default storage) */
typedef struct {
  const double MultiportSwitch[2];     /* '<S6>/Multiport Switch' */
  const double MultiportSwitch_n[2];   /* '<S11>/Multiport Switch' */
} ConstB_MCU_Protections_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  ThresholdsBus Thresholds;            /* '<Root>/Thresholds' */
  double MC_Temperature_C;             /* '<Root>/MC_Temperature_C' */
  double Motor_Temperature_C;          /* '<Root>/Motor_Temperature_C' */
  double I_a;                          /* '<Root>/I_a' */
  double I_b;                          /* '<Root>/I_b' */
  double I_c;                          /* '<Root>/I_c' */
  double Bus_Voltage_V;                /* '<Root>/Bus_Voltage_V' */
  double Aux_Voltage_V;                /* '<Root>/Aux_Voltage_V' */
} ExtU_MCU_Protections_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  TempState Motor_TempFlag;            /* '<Root>/Motor_TempFlag' */
  TempState MC_TempFlag;               /* '<Root>/MC_TempFlag' */
  VoltageState Aux_Voltage_Flag;       /* '<Root>/Aux_Voltage_Flag' */
  VoltageState Bus_Voltage_Flag;       /* '<Root>/Bus_Voltage_Flag' */
  CurrentState Current_Flag;           /* '<Root>/Current_Flag' */
} ExtY_MCU_Protections_T;

/* Real-time Model Data Structure */
struct tag_RTM_MCU_Protections_T {
  const char *errorStatus;
  RTWSolverInfo solverInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_t clockTick0;
    double stepSize0;
    uint32_t clockTick1;
    SimTimeStep simTimeStep;
    double *t;
    double tArray[2];
  } Timing;
};

/* Block signals (default storage) */
extern B_MCU_Protections_T MCU_Protections_B;

/* Block states (default storage) */
extern DW_MCU_Protections_T MCU_Protections_DW;

/* Zero-crossing (trigger) state */
extern PrevZCX_MCU_Protections_T MCU_Protections_PrevZCX;

/* External inputs (root inport signals with default storage) */
extern ExtU_MCU_Protections_T MCU_Protections_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_MCU_Protections_T MCU_Protections_Y;
extern const ConstB_MCU_Protections_T MCU_Protections_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void MCU_Protections_initialize(void);
extern void MCU_Protections_step(void);
extern void MCU_Protections_terminate(void);

/* Real-time Model object */
extern RT_MODEL_MCU_Protections_T *const MCU_Protections_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S7>/Constant' : Unused code path elimination
 * Block '<S7>/Relational Operator' : Unused code path elimination
 * Block '<S7>/Sum' : Unused code path elimination
 * Block '<S12>/Constant' : Unused code path elimination
 * Block '<S12>/Relational Operator' : Unused code path elimination
 * Block '<S12>/Sum' : Unused code path elimination
 * Block '<S6>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S11>/Data Type Conversion2' : Eliminate redundant data type conversion
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
 * hilite_system('Protection_Logic/MCU_Protections')    - opens subsystem Protection_Logic/MCU_Protections
 * hilite_system('Protection_Logic/MCU_Protections/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Protection_Logic'
 * '<S1>'   : 'Protection_Logic/MCU_Protections'
 * '<S2>'   : 'Protection_Logic/MCU_Protections/Chart'
 * '<S3>'   : 'Protection_Logic/MCU_Protections/Edge Detector'
 * '<S4>'   : 'Protection_Logic/MCU_Protections/Edge Detector1'
 * '<S5>'   : 'Protection_Logic/MCU_Protections/Subsystem'
 * '<S6>'   : 'Protection_Logic/MCU_Protections/Edge Detector/Model'
 * '<S7>'   : 'Protection_Logic/MCU_Protections/Edge Detector/Model/Internal dirac generator'
 * '<S8>'   : 'Protection_Logic/MCU_Protections/Edge Detector/Model/NEGATIVE Edge'
 * '<S9>'   : 'Protection_Logic/MCU_Protections/Edge Detector/Model/POSITIVE Edge'
 * '<S10>'  : 'Protection_Logic/MCU_Protections/Edge Detector/Model/Internal dirac generator/Triggered Subsystem'
 * '<S11>'  : 'Protection_Logic/MCU_Protections/Edge Detector1/Model'
 * '<S12>'  : 'Protection_Logic/MCU_Protections/Edge Detector1/Model/Internal dirac generator'
 * '<S13>'  : 'Protection_Logic/MCU_Protections/Edge Detector1/Model/NEGATIVE Edge'
 * '<S14>'  : 'Protection_Logic/MCU_Protections/Edge Detector1/Model/POSITIVE Edge'
 * '<S15>'  : 'Protection_Logic/MCU_Protections/Edge Detector1/Model/Internal dirac generator/Triggered Subsystem'
 */
#endif                                 /* MCU_Protections_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
