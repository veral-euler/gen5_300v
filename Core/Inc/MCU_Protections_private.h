/*
 * File: MCU_Protections_private.h
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

#ifndef MCU_Protections_private_h_
#define MCU_Protections_private_h_
#include <stdbool.h>
#include <stdint.h>
#include "complex_types.h"
#include "zero_crossing_types.h"
#include "MCU_Protections.h"
#include "MCU_Protections_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

extern void MCU_Protec_NEGATIVEEdge_Disable(DW_NEGATIVEEdge_MCU_Protectio_T
  *localDW);
extern void MCU_Protections_NEGATIVEEdge(double rtu_Enable, bool rtu_IN, bool
  rtu_INprevious, bool *rty_OUT, DW_NEGATIVEEdge_MCU_Protectio_T *localDW);
extern void MCU_Protec_POSITIVEEdge_Disable(DW_POSITIVEEdge_MCU_Protectio_T
  *localDW);
extern void MCU_Protections_POSITIVEEdge(double rtu_Enable, bool rtu_IN, bool
  rtu_INprevious, bool *rty_OUT, DW_POSITIVEEdge_MCU_Protectio_T *localDW);

#endif                                 /* MCU_Protections_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
