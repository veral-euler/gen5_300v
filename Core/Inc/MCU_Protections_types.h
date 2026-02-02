/*
 * File: MCU_Protections_types.h
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

#ifndef MCU_Protections_types_h_
#define MCU_Protections_types_h_
#include <stdint.h>
#ifndef DEFINED_TYPEDEF_FOR_ThresholdsBus_
#define DEFINED_TYPEDEF_FOR_ThresholdsBus_

typedef struct {
  float MC_OT_Warning_Limit_C;
  float MC_OT_Error_Limit_C;
  float Motor_OT_Warning_Limit_C;
  float Motor_OT_Error_Limit_C;
  float UV_Warning_Limit_V;
  float UV_Error_Limit_V;
  float OV_Warning_Limit_V;
  float OV_Error_Limit_V;
  float Aux_UV_Warning_Limit_V;
  float Aux_UV_Error_Limit_V;
  float Aux_OV_Warning_Limit_V;
  float Aux_OV_Error_Limit_V;
  float OC_Warning_Limit_A;
  float OC_Error_Limit_A;
  float Voltage_Protection_Timeout_msec;
  float Temp_Protection_Timeout_msec;
  float Time_current_limit_normal_msec;
  float Current_count_limit;
} ThresholdsBus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_TempState_
#define DEFINED_TYPEDEF_FOR_TempState_

typedef enum {
  SafeTemperature = 0,                 /* Default value */
  OT_Warning,
  OT_Error
} TempState;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VoltageState_
#define DEFINED_TYPEDEF_FOR_VoltageState_

typedef enum {
  SafeVoltage = 0,                     /* Default value */
  OV_Warning,
  OV_Error,
  UV_Warning,
  UV_Error
} VoltageState;

#endif

#ifndef DEFINED_TYPEDEF_FOR_CurrentState_
#define DEFINED_TYPEDEF_FOR_CurrentState_

typedef enum {
  SafeCurrent = 0,                     /* Default value */
  OC_Warning,
  OC_Error
} CurrentState;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_MCU_Protections_T RT_MODEL_MCU_Protections_T;

#endif                                 /* MCU_Protections_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
