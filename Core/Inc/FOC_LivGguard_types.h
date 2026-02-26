/*
 * File: FOC_LivGguard_types.h
 *
 * Code generated for Simulink model 'FOC_LivGguard'.
 *
 * Model version                  : 18.321
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Wed Feb 11 17:44:19 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef FOC_LivGguard_types_h_
#define FOC_LivGguard_types_h_
#ifndef DEFINED_TYPEDEF_FOR_Flux_PID_MTPA_
#define DEFINED_TYPEDEF_FOR_Flux_PID_MTPA_

typedef struct {
  float Kp_flux_PID_MTPA;
  float Ki_flux_PID_MTPA;
  float Kd_flux_PID_MTPA;
  float Filter_flux_PID_MTPA;
} Flux_PID_MTPA;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Speed_PID_MTPA_
#define DEFINED_TYPEDEF_FOR_Speed_PID_MTPA_

typedef struct {
  float Kp_speed_PID_MTPA;
  float Ki_speed_PID_MTPA;
  float Kd_speed_PID_MTPA;
  float Filter_speed_PID_MTPA;
} Speed_PID_MTPA;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Torque_PID_MTPA_
#define DEFINED_TYPEDEF_FOR_Torque_PID_MTPA_

typedef struct {
  float Kp_torque_PID_MTPA;
  float Ki_torque_PID_MTPA;
  float Kd_torque_PID_MTPA;
  float Filter_torque_PID_MTPA;
} Torque_PID_MTPA;

#endif

#ifndef DEFINED_TYPEDEF_FOR_PID_MTPABus_
#define DEFINED_TYPEDEF_FOR_PID_MTPABus_

typedef struct {
  Flux_PID_MTPA Flux_PID_MTPA;
  Speed_PID_MTPA Speed_PID_MTPA;
  Torque_PID_MTPA Torque_PID_MTPA;
  float Up_Limit_speed_PID_MTPA;
  float Low_Limit_speed_PID_MTPA;
  float Up_Limit_flux_PID;
  float Low_Limit_flux_PID;
  float Up_Limit_torque_PID;
  float Low_Limit_torque_PID;
} PID_MTPABus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Rate_limiterBus_
#define DEFINED_TYPEDEF_FOR_Rate_limiterBus_

typedef struct {
  float Id_ramp_up;
  float Id_ramp_down;
  float Iq_ramp_up;
  float Iq_ramp_down;
  float Torque_gen_ramp_up;
  float Torque_gen_ramp_down;
} Rate_limiterBus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_IIR_FilterBus_
#define DEFINED_TYPEDEF_FOR_IIR_FilterBus_

typedef struct {
  float Id_Filter_coefficient;
  float Id_Filter_switch;
  float Iq_Filter_coefficient;
  float Iq_Filter_switch;
} IIR_FilterBus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Id_Iq_MTPA_limitBus_
#define DEFINED_TYPEDEF_FOR_Id_Iq_MTPA_limitBus_

typedef struct {
  float Id_up_limit;
  float Id_low_limit;
  float Iq_up_limit;
  float Iq_low_limit;
} Id_Iq_MTPA_limitBus;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_FOC_LivGguard_T RT_MODEL_FOC_LivGguard_T;

#endif                                 /* FOC_LivGguard_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
