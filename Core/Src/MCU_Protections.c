/*
 * File: MCU_Protections.c
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

#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include "MCU_Protections.h"
#include "MCU_Protections_private.h"
#include "MCU_Protections_types.h"
#include "zero_crossing_types.h"
#include "main.h"

/* Named constants for Chart: '<S1>/Chart' */
#define MCU_Pr_IN_Current_warning_fault ((uint8_t)2U)
#define MCU_Prot_IN_Current_error_fault ((uint8_t)1U)
#define MCU_Protecti_IN_HighTempWarning ((uint8_t)2U)
#define MCU_Protecti_IN_NO_ACTIVE_CHILD ((uint8_t)0U)
#define MCU_Protection_IN_HighTempError ((uint8_t)1U)
#define MCU_Protections_IN_Error       ((uint8_t)1U)
#define MCU_Protections_IN_Init        ((uint8_t)2U)
#define MCU_Protections_IN_Normal      ((uint8_t)3U)
#define MCU_Protections_IN_OV_Error    ((uint8_t)1U)
#define MCU_Protections_IN_OV_Warning  ((uint8_t)2U)
#define MCU_Protections_IN_TempSafe    ((uint8_t)3U)
#define MCU_Protections_IN_UV_Error    ((uint8_t)3U)
#define MCU_Protections_IN_UV_Warning  ((uint8_t)4U)
#define MCU_Protections_IN_VoltageSafe ((uint8_t)5U)
#define MCU_Protections_IN_Warning     ((uint8_t)3U)
#define MCU_Protections_IN_idle        ((uint8_t)2U)

/* Block signals (default storage) */
B_MCU_Protections_T MCU_Protections_B;

/* Block states (default storage) */
DW_MCU_Protections_T MCU_Protections_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_MCU_Protections_T MCU_Protections_PrevZCX;

/* External inputs (root inport signals with default storage) */
ExtU_MCU_Protections_T MCU_Protections_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_MCU_Protections_T MCU_Protections_Y;

/* Real-time model */
static RT_MODEL_MCU_Protections_T MCU_Protections_M_;
RT_MODEL_MCU_Protections_T *const MCU_Protections_M = &MCU_Protections_M_;

/* Forward declaration for local functions */
static void MCU_Protecti_Current_Protection(const bool *LogicalOperator1, const
  bool *LogicalOperator1_g);
static void MCU_Prot_Bus_Voltage_Protection(void);
static void MCU_Protections_Protections(const bool *LogicalOperator1, const bool
  *LogicalOperator1_g);

/*
 * Disable for enable system:
 *    '<S6>/NEGATIVE Edge'
 *    '<S11>/NEGATIVE Edge'
 */
void MCU_Protec_NEGATIVEEdge_Disable(DW_NEGATIVEEdge_MCU_Protectio_T *localDW)
{
  localDW->NEGATIVEEdge_MODE = false;
}

/*
 * Output and update for enable system:
 *    '<S6>/NEGATIVE Edge'
 *    '<S11>/NEGATIVE Edge'
 */
void MCU_Protections_NEGATIVEEdge(float rtu_Enable, bool rtu_IN, bool
  rtu_INprevious, bool *rty_OUT, DW_NEGATIVEEdge_MCU_Protectio_T *localDW)
{
  /* Outputs for Enabled SubSystem: '<S6>/NEGATIVE Edge' incorporates:
   *  EnablePort: '<S8>/Enable'
   */
  if (rtu_Enable > 0.0) {
    localDW->NEGATIVEEdge_MODE = true;
  } else if (localDW->NEGATIVEEdge_MODE) {
    MCU_Protec_NEGATIVEEdge_Disable(localDW);
  }

  if (localDW->NEGATIVEEdge_MODE) {
    /* RelationalOperator: '<S8>/Relational Operator1' */
    *rty_OUT = ((int32_t)rtu_INprevious > (int32_t)rtu_IN);
  }

  /* End of Outputs for SubSystem: '<S6>/NEGATIVE Edge' */
}

/*
 * Disable for enable system:
 *    '<S6>/POSITIVE Edge'
 *    '<S11>/POSITIVE Edge'
 */
void MCU_Protec_POSITIVEEdge_Disable(DW_POSITIVEEdge_MCU_Protectio_T *localDW)
{
  localDW->POSITIVEEdge_MODE = false;
}

/*
 * Output and update for enable system:
 *    '<S6>/POSITIVE Edge'
 *    '<S11>/POSITIVE Edge'
 */
void MCU_Protections_POSITIVEEdge(float rtu_Enable, bool rtu_IN, bool
  rtu_INprevious, bool *rty_OUT, DW_POSITIVEEdge_MCU_Protectio_T *localDW)
{
  /* Outputs for Enabled SubSystem: '<S6>/POSITIVE Edge' incorporates:
   *  EnablePort: '<S9>/Enable'
   */
  if (rtu_Enable > 0.0) {
    localDW->POSITIVEEdge_MODE = true;
  } else if (localDW->POSITIVEEdge_MODE) {
    MCU_Protec_POSITIVEEdge_Disable(localDW);
  }

  if (localDW->POSITIVEEdge_MODE) {
    /* RelationalOperator: '<S9>/Relational Operator1' */
    *rty_OUT = ((int32_t)rtu_INprevious < (int32_t)rtu_IN);
  }

  /* End of Outputs for SubSystem: '<S6>/POSITIVE Edge' */
}

/* Function for Chart: '<S1>/Chart' */
static void MCU_Protecti_Current_Protection(const bool *LogicalOperator1, const
  bool *LogicalOperator1_g)
{
  float tmp;
  bool c_out;
  bool guard1;
  bool guard2;
  guard1 = false;
  guard2 = false;
  switch (MCU_Protections_DW.is_Current_Protection) {
   case MCU_Protections_IN_Error:
    /* Outport: '<Root>/Current_Flag' */
    MCU_Protections_Y.Current_Flag = OC_Error;
    break;

   case MCU_Protections_IN_Init:
    if (MCU_Protections_DW.count_current_warning >
        MCU_Protections_U.Thresholds.Current_count_limit) {
      MCU_Protections_DW.is_Init = MCU_Protecti_IN_NO_ACTIVE_CHILD;
      MCU_Protections_DW.is_Current_Protection = MCU_Protections_IN_Warning;

      /* Outport: '<Root>/Current_Flag' */
      MCU_Protections_Y.Current_Flag = OC_Warning;
      MCU_Protections_DW.durationCounter_2_h = 0U;
      MCU_Protections_DW.durationCounter_1_e = 0U;
      MCU_Protections_DW.is_Warning = MCU_Protections_IN_idle;
    } else if (MCU_Protections_DW.count_current_error >
               MCU_Protections_U.Thresholds.Current_count_limit) {
      MCU_Protections_DW.is_Init = MCU_Protecti_IN_NO_ACTIVE_CHILD;
      MCU_Protections_DW.is_Current_Protection = MCU_Protections_IN_Error;

      /* Outport: '<Root>/Current_Flag' */
      MCU_Protections_Y.Current_Flag = OC_Error;
    } else {
      /* Outport: '<Root>/Current_Flag' */
      MCU_Protections_Y.Current_Flag = SafeCurrent;
      switch (MCU_Protections_DW.is_Init) {
       case MCU_Prot_IN_Current_error_fault:
        MCU_Protections_DW.durationCounter_2 = 0U;
        MCU_Protections_DW.durationCounter_1 = 0U;
        MCU_Protections_DW.is_Init = MCU_Protections_IN_Normal;
        break;

       case MCU_Pr_IN_Current_warning_fault:
        MCU_Protections_DW.durationCounter_2 = 0U;
        MCU_Protections_DW.durationCounter_1 = 0U;
        MCU_Protections_DW.is_Init = MCU_Protections_IN_Normal;
        break;

       default:
        /* case IN_Normal: */
        if (*LogicalOperator1) {
          MCU_Protections_DW.is_Init = MCU_Prot_IN_Current_error_fault;
          MCU_Protections_DW.count_current_error++;
        } else if (*LogicalOperator1_g) {
          MCU_Protections_DW.is_Init = MCU_Pr_IN_Current_warning_fault;
          MCU_Protections_DW.count_current_warning++;
        } else {
          if (MCU_Protections_DW.count_current_warning > 0.0) {
            if (*LogicalOperator1_g) {
              MCU_Protections_DW.durationCounter_1 = 0U;
            }

            /* Inport: '<Root>/Thresholds' */
            c_out = ((float)MCU_Protections_DW.durationCounter_1 >
                     MCU_Protections_U.Thresholds.Time_current_limit_normal_msec
                     * 10.0F);
          } else {
            c_out = false;
          }

          if (c_out) {
            MCU_Protections_DW.count_current_warning--;
            guard2 = true;
          } else {
            if (MCU_Protections_DW.count_current_error > 0.0) {
              if (*LogicalOperator1) {
                MCU_Protections_DW.durationCounter_2 = 0U;
              }

              /* Inport: '<Root>/Thresholds' */
              c_out = ((float)MCU_Protections_DW.durationCounter_2 >
                       MCU_Protections_U.Thresholds.Time_current_limit_normal_msec
                       * 10.0F);
            } else {
              c_out = false;
            }

            if (c_out) {
              MCU_Protections_DW.count_current_error--;
              guard2 = true;
            }
          }
        }
        break;
      }
    }
    break;

   default:
    /* case IN_Warning: */
    if (MCU_Protections_DW.count_current_warning == 0.0) {
      MCU_Protections_DW.is_Warning = MCU_Protecti_IN_NO_ACTIVE_CHILD;
      MCU_Protections_DW.is_Current_Protection = MCU_Protections_IN_Init;

      /* Outport: '<Root>/Current_Flag' */
      MCU_Protections_Y.Current_Flag = SafeCurrent;
      MCU_Protections_DW.durationCounter_2 = 0U;
      MCU_Protections_DW.durationCounter_1 = 0U;
      MCU_Protections_DW.is_Init = MCU_Protections_IN_Normal;
    } else if (MCU_Protections_DW.count_current_error >
               MCU_Protections_U.Thresholds.Current_count_limit) {
      MCU_Protections_DW.is_Warning = MCU_Protecti_IN_NO_ACTIVE_CHILD;
      MCU_Protections_DW.is_Current_Protection = MCU_Protections_IN_Error;

      /* Outport: '<Root>/Current_Flag' */
      MCU_Protections_Y.Current_Flag = OC_Error;
    } else {
      /* Outport: '<Root>/Current_Flag' */
      MCU_Protections_Y.Current_Flag = OC_Warning;
      switch (MCU_Protections_DW.is_Warning) {
       case MCU_Prot_IN_Current_error_fault:
        MCU_Protections_DW.durationCounter_2_h = 0U;
        MCU_Protections_DW.durationCounter_1_e = 0U;
        MCU_Protections_DW.is_Warning = MCU_Protections_IN_idle;
        break;

       default:
        /* case IN_idle: */
        if (*LogicalOperator1_g) {
          MCU_Protections_DW.durationCounter_1_e = 0U;
        }

        /* Inport: '<Root>/Thresholds' */
        tmp = MCU_Protections_U.Thresholds.Time_current_limit_normal_msec *
          10.0F;
        if (MCU_Protections_DW.durationCounter_1_e > tmp) {
          MCU_Protections_DW.count_current_warning--;
          guard1 = true;
        } else if (*LogicalOperator1) {
          MCU_Protections_DW.is_Warning = MCU_Prot_IN_Current_error_fault;
          MCU_Protections_DW.count_current_error++;
        } else {
          if (MCU_Protections_DW.count_current_error > 0.0) {
            if (*LogicalOperator1) {
              MCU_Protections_DW.durationCounter_2_h = 0U;
            }

            c_out = (MCU_Protections_DW.durationCounter_2_h > tmp);
          } else {
            c_out = false;
          }

          if (c_out) {
            MCU_Protections_DW.count_current_error--;
            guard1 = true;
          }
        }
        break;
      }
    }
    break;
  }

  if (guard2) {
    MCU_Protections_DW.durationCounter_2 = 0U;
    MCU_Protections_DW.durationCounter_1 = 0U;
    MCU_Protections_DW.is_Init = MCU_Protections_IN_Normal;
  }

  if (guard1) {
    MCU_Protections_DW.durationCounter_2_h = 0U;
    MCU_Protections_DW.durationCounter_1_e = 0U;
    MCU_Protections_DW.is_Warning = MCU_Protections_IN_idle;
  }
}

/* Function for Chart: '<S1>/Chart' */
static void MCU_Prot_Bus_Voltage_Protection(void)
{
  float tmp;
  switch (MCU_Protections_DW.is_Bus_Voltage_Protection) {
   case MCU_Protections_IN_OV_Error:
    /* Outport: '<Root>/Bus_Voltage_Flag' */
    MCU_Protections_Y.Bus_Voltage_Flag = OV_Error;
    break;

   case MCU_Protections_IN_OV_Warning:
    /* Outport: '<Root>/Bus_Voltage_Flag' */
    MCU_Protections_Y.Bus_Voltage_Flag = OV_Warning;

    /* Inport: '<Root>/Bus_Voltage_V' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    if (!(MCU_Protections_U.Bus_Voltage_V >
          MCU_Protections_U.Thresholds.OV_Error_Limit_V)) {
      MCU_Protections_DW.durationCounter_2_m0 = 0U;
    }

    /* Inport: '<Root>/Thresholds' */
    /* Inport: '<Root>/Bus_Voltage_V' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    tmp = MCU_Protections_U.Thresholds.Voltage_Protection_Timeout_msec * 10.0F;
    if (MCU_Protections_DW.durationCounter_2_m0 > tmp) {
      MCU_Protections_DW.is_Bus_Voltage_Protection = MCU_Protections_IN_OV_Error;

      /* Outport: '<Root>/Bus_Voltage_Flag' */
      MCU_Protections_Y.Bus_Voltage_Flag = OV_Error;
    } else {
      if (!(MCU_Protections_U.Bus_Voltage_V <
            MCU_Protections_U.Thresholds.OV_Warning_Limit_V)) {
        MCU_Protections_DW.durationCounter_1_bx = 0U;
      }

      if (MCU_Protections_DW.durationCounter_1_bx > tmp) {
        MCU_Protections_DW.durationCounter_4_a = 0U;
        MCU_Protections_DW.durationCounter_3_o = 0U;
        MCU_Protections_DW.durationCounter_2_j = 0U;
        MCU_Protections_DW.durationCounter_1_o = 0U;
        MCU_Protections_DW.is_Bus_Voltage_Protection =
          MCU_Protections_IN_VoltageSafe;

        /* Outport: '<Root>/Bus_Voltage_Flag' */
        MCU_Protections_Y.Bus_Voltage_Flag = SafeVoltage;
      }
    }
    break;

   case MCU_Protections_IN_UV_Error:
    /* Outport: '<Root>/Bus_Voltage_Flag' */
    MCU_Protections_Y.Bus_Voltage_Flag = UV_Error;
    break;

   case MCU_Protections_IN_UV_Warning:
    /* Outport: '<Root>/Bus_Voltage_Flag' */
    MCU_Protections_Y.Bus_Voltage_Flag = UV_Warning;

    /* Inport: '<Root>/Bus_Voltage_V' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    if (!(MCU_Protections_U.Bus_Voltage_V <
          MCU_Protections_U.Thresholds.UV_Error_Limit_V)) {
      MCU_Protections_DW.durationCounter_1_f = 0U;
    }

    /* Inport: '<Root>/Thresholds' */
    /* Inport: '<Root>/Bus_Voltage_V' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    tmp = MCU_Protections_U.Thresholds.Voltage_Protection_Timeout_msec * 10.0F;
    if (MCU_Protections_DW.durationCounter_1_f > tmp) {
      MCU_Protections_DW.is_Bus_Voltage_Protection = MCU_Protections_IN_UV_Error;

      /* Outport: '<Root>/Bus_Voltage_Flag' */
      MCU_Protections_Y.Bus_Voltage_Flag = UV_Error;
    } else {
      if (!(MCU_Protections_U.Bus_Voltage_V >
            MCU_Protections_U.Thresholds.UV_Warning_Limit_V)) {
        MCU_Protections_DW.durationCounter_2_cm = 0U;
      }

      if (MCU_Protections_DW.durationCounter_2_cm > tmp) {
        MCU_Protections_DW.durationCounter_4_a = 0U;
        MCU_Protections_DW.durationCounter_3_o = 0U;
        MCU_Protections_DW.durationCounter_2_j = 0U;
        MCU_Protections_DW.durationCounter_1_o = 0U;
        MCU_Protections_DW.is_Bus_Voltage_Protection =
          MCU_Protections_IN_VoltageSafe;

        /* Outport: '<Root>/Bus_Voltage_Flag' */
        MCU_Protections_Y.Bus_Voltage_Flag = SafeVoltage;
      }
    }
    break;

   default:
    /* Outport: '<Root>/Bus_Voltage_Flag' */
    /* case IN_VoltageSafe: */
    MCU_Protections_Y.Bus_Voltage_Flag = SafeVoltage;

    /* Inport: '<Root>/Bus_Voltage_V' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    if (!(MCU_Protections_U.Bus_Voltage_V >
          MCU_Protections_U.Thresholds.OV_Error_Limit_V)) {
      MCU_Protections_DW.durationCounter_4_a = 0U;
    }

    /* Inport: '<Root>/Thresholds' */
    /* Inport: '<Root>/Bus_Voltage_V' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    tmp = MCU_Protections_U.Thresholds.Voltage_Protection_Timeout_msec * 10.0F;
    if (MCU_Protections_DW.durationCounter_4_a > tmp) {
      MCU_Protections_DW.is_Bus_Voltage_Protection = MCU_Protections_IN_OV_Error;

      /* Outport: '<Root>/Bus_Voltage_Flag' */
      MCU_Protections_Y.Bus_Voltage_Flag = OV_Error;
    } else {
      if (!(MCU_Protections_U.Bus_Voltage_V <
            MCU_Protections_U.Thresholds.UV_Error_Limit_V)) {
        MCU_Protections_DW.durationCounter_2_j = 0U;
      }

      if (MCU_Protections_DW.durationCounter_2_j > tmp) {
        MCU_Protections_DW.is_Bus_Voltage_Protection =
          MCU_Protections_IN_UV_Error;

        /* Outport: '<Root>/Bus_Voltage_Flag' */
        MCU_Protections_Y.Bus_Voltage_Flag = UV_Error;
      } else {
        if (!(MCU_Protections_U.Bus_Voltage_V >
              MCU_Protections_U.Thresholds.OV_Warning_Limit_V)) {
          MCU_Protections_DW.durationCounter_3_o = 0U;
        }

        if (MCU_Protections_DW.durationCounter_3_o > tmp) {
          MCU_Protections_DW.durationCounter_2_m0 = 0U;
          MCU_Protections_DW.durationCounter_1_bx = 0U;
          MCU_Protections_DW.is_Bus_Voltage_Protection =
            MCU_Protections_IN_OV_Warning;

          /* Outport: '<Root>/Bus_Voltage_Flag' */
          MCU_Protections_Y.Bus_Voltage_Flag = OV_Warning;
        } else {
          if (!(MCU_Protections_U.Bus_Voltage_V <
                MCU_Protections_U.Thresholds.UV_Warning_Limit_V)) {
            MCU_Protections_DW.durationCounter_1_o = 0U;
          }

          if (MCU_Protections_DW.durationCounter_1_o > tmp) {
            MCU_Protections_DW.durationCounter_2_cm = 0U;
            MCU_Protections_DW.durationCounter_1_f = 0U;
            MCU_Protections_DW.is_Bus_Voltage_Protection =
              MCU_Protections_IN_UV_Warning;

            /* Outport: '<Root>/Bus_Voltage_Flag' */
            MCU_Protections_Y.Bus_Voltage_Flag = UV_Warning;
          }
        }
      }
    }
    break;
  }
}

/* Function for Chart: '<S1>/Chart' */
static void MCU_Protections_Protections(const bool *LogicalOperator1, const bool
  *LogicalOperator1_g)
{
  float tmp;
  MCU_Protecti_Current_Protection(LogicalOperator1, LogicalOperator1_g);
  switch (MCU_Protections_DW.is_MC_Temperature_Protection) {
   case MCU_Protection_IN_HighTempError:
    /* Outport: '<Root>/MC_TempFlag' */
    MCU_Protections_Y.MC_TempFlag = OT_Error;
    break;

   case MCU_Protecti_IN_HighTempWarning:
    /* Outport: '<Root>/MC_TempFlag' */
    MCU_Protections_Y.MC_TempFlag = OT_Warning;

    /* Inport: '<Root>/MC_Temperature_C' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    if (!(MCU_Protections_U.MC_Temperature_C >
          MCU_Protections_U.Thresholds.MC_OT_Error_Limit_C)) {
      MCU_Protections_DW.durationCounter_2_br = 0U;
    }

    /* Inport: '<Root>/Thresholds' */
    /* Inport: '<Root>/MC_Temperature_C' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    tmp = MCU_Protections_U.Thresholds.Temp_Protection_Timeout_msec * 10.0F;
    if (MCU_Protections_DW.durationCounter_2_br > tmp) {
      MCU_Protections_DW.is_MC_Temperature_Protection =
        MCU_Protection_IN_HighTempError;

      /* Outport: '<Root>/MC_TempFlag' */
      MCU_Protections_Y.MC_TempFlag = OT_Error;
    } else {
      if (!(MCU_Protections_U.MC_Temperature_C <
            MCU_Protections_U.Thresholds.MC_OT_Warning_Limit_C)) {
        MCU_Protections_DW.durationCounter_1_d = 0U;
      }

      if (MCU_Protections_DW.durationCounter_1_d > tmp) {
        MCU_Protections_DW.durationCounter_2_b = 0U;
        MCU_Protections_DW.durationCounter_1_b = 0U;
        MCU_Protections_DW.is_MC_Temperature_Protection =
          MCU_Protections_IN_TempSafe;

        /* Outport: '<Root>/MC_TempFlag' */
        MCU_Protections_Y.MC_TempFlag = SafeTemperature;
      }
    }
    break;

   default:
    /* Outport: '<Root>/MC_TempFlag' */
    /* case IN_TempSafe: */
    MCU_Protections_Y.MC_TempFlag = SafeTemperature;

    /* Inport: '<Root>/MC_Temperature_C' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    if (!(MCU_Protections_U.MC_Temperature_C >
          MCU_Protections_U.Thresholds.MC_OT_Error_Limit_C)) {
      MCU_Protections_DW.durationCounter_1_b = 0U;
    }

    /* Inport: '<Root>/Thresholds' */
    /* Inport: '<Root>/MC_Temperature_C' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    tmp = MCU_Protections_U.Thresholds.Temp_Protection_Timeout_msec * 10.0F;
    if (MCU_Protections_DW.durationCounter_1_b > tmp) {
      MCU_Protections_DW.is_MC_Temperature_Protection =
        MCU_Protection_IN_HighTempError;

      /* Outport: '<Root>/MC_TempFlag' */
      MCU_Protections_Y.MC_TempFlag = OT_Error;
    } else {
      if (!(MCU_Protections_U.MC_Temperature_C >
            MCU_Protections_U.Thresholds.MC_OT_Warning_Limit_C)) {
        MCU_Protections_DW.durationCounter_2_b = 0U;
      }

      if (MCU_Protections_DW.durationCounter_2_b > tmp) {
        MCU_Protections_DW.durationCounter_2_br = 0U;
        MCU_Protections_DW.durationCounter_1_d = 0U;
        MCU_Protections_DW.is_MC_Temperature_Protection =
          MCU_Protecti_IN_HighTempWarning;

        /* Outport: '<Root>/MC_TempFlag' */
        MCU_Protections_Y.MC_TempFlag = OT_Warning;
      }
    }
    break;
  }

  switch (MCU_Protections_DW.is_Motor_Temperature_Protection) {
   case MCU_Protection_IN_HighTempError:
    /* Outport: '<Root>/Motor_TempFlag' */
    MCU_Protections_Y.Motor_TempFlag = OT_Error;
    break;

   case MCU_Protecti_IN_HighTempWarning:
    /* Outport: '<Root>/Motor_TempFlag' */
    MCU_Protections_Y.Motor_TempFlag = OT_Warning;

    /* Inport: '<Root>/Motor_Temperature_C' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    if (!(MCU_Protections_U.Motor_Temperature_C >
          MCU_Protections_U.Thresholds.Motor_OT_Error_Limit_C)) {
      MCU_Protections_DW.durationCounter_2_k = 0U;
    }

    /* Inport: '<Root>/Thresholds' */
    /* Inport: '<Root>/Motor_Temperature_C' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    tmp = MCU_Protections_U.Thresholds.Temp_Protection_Timeout_msec * 10.0F;
    if (MCU_Protections_DW.durationCounter_2_k > tmp) {
      MCU_Protections_DW.is_Motor_Temperature_Protection =
        MCU_Protection_IN_HighTempError;

      /* Outport: '<Root>/Motor_TempFlag' */
      MCU_Protections_Y.Motor_TempFlag = OT_Error;
    } else {
      if (!(MCU_Protections_U.Motor_Temperature_C <
            MCU_Protections_U.Thresholds.Motor_OT_Warning_Limit_C)) {
        MCU_Protections_DW.durationCounter_1_i = 0U;
      }

      if (MCU_Protections_DW.durationCounter_1_i > tmp) {
        MCU_Protections_DW.durationCounter_2_p = 0U;
        MCU_Protections_DW.durationCounter_1_ez = 0U;
        MCU_Protections_DW.is_Motor_Temperature_Protection =
          MCU_Protections_IN_TempSafe;

        /* Outport: '<Root>/Motor_TempFlag' */
        MCU_Protections_Y.Motor_TempFlag = SafeTemperature;
      }
    }
    break;

   default:
    /* Outport: '<Root>/Motor_TempFlag' */
    /* case IN_TempSafe: */
    MCU_Protections_Y.Motor_TempFlag = SafeTemperature;

    /* Inport: '<Root>/Motor_Temperature_C' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    if (!(MCU_Protections_U.Motor_Temperature_C >
          MCU_Protections_U.Thresholds.Motor_OT_Error_Limit_C)) {
      MCU_Protections_DW.durationCounter_1_ez = 0U;
    }

    /* Inport: '<Root>/Thresholds' */
    /* Inport: '<Root>/Motor_Temperature_C' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    tmp = MCU_Protections_U.Thresholds.Temp_Protection_Timeout_msec * 10.0F;
    if (MCU_Protections_DW.durationCounter_1_ez > tmp) {
      MCU_Protections_DW.is_Motor_Temperature_Protection =
        MCU_Protection_IN_HighTempError;

      /* Outport: '<Root>/Motor_TempFlag' */
      MCU_Protections_Y.Motor_TempFlag = OT_Error;
    } else {
      if (!(MCU_Protections_U.Motor_Temperature_C >
            MCU_Protections_U.Thresholds.Motor_OT_Warning_Limit_C)) {
        MCU_Protections_DW.durationCounter_2_p = 0U;
      }

      if (MCU_Protections_DW.durationCounter_2_p > tmp) {
        MCU_Protections_DW.durationCounter_2_k = 0U;
        MCU_Protections_DW.durationCounter_1_i = 0U;
        MCU_Protections_DW.is_Motor_Temperature_Protection =
          MCU_Protecti_IN_HighTempWarning;

        /* Outport: '<Root>/Motor_TempFlag' */
        MCU_Protections_Y.Motor_TempFlag = OT_Warning;
      }
    }
    break;
  }

  switch (MCU_Protections_DW.is_Aux_Voltage_Protection) {
   case MCU_Protections_IN_OV_Error:
    /* Outport: '<Root>/Aux_Voltage_Flag' */
    MCU_Protections_Y.Aux_Voltage_Flag = OV_Error;
    break;

   case MCU_Protections_IN_OV_Warning:
    /* Outport: '<Root>/Aux_Voltage_Flag' */
    MCU_Protections_Y.Aux_Voltage_Flag = OV_Warning;

    /* Inport: '<Root>/Aux_Voltage_V' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    if (!(MCU_Protections_U.Aux_Voltage_V >
          MCU_Protections_U.Thresholds.Aux_OV_Error_Limit_V)) {
      MCU_Protections_DW.durationCounter_2_mw = 0U;
    }

    /* Inport: '<Root>/Thresholds' */
    /* Inport: '<Root>/Aux_Voltage_V' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    tmp = MCU_Protections_U.Thresholds.Voltage_Protection_Timeout_msec * 10.0F;
    if (MCU_Protections_DW.durationCounter_2_mw > tmp) {
      MCU_Protections_DW.is_Aux_Voltage_Protection = MCU_Protections_IN_OV_Error;

      /* Outport: '<Root>/Aux_Voltage_Flag' */
      MCU_Protections_Y.Aux_Voltage_Flag = OV_Error;
    } else {
      if (!(MCU_Protections_U.Aux_Voltage_V <
            MCU_Protections_U.Thresholds.Aux_OV_Warning_Limit_V)) {
        MCU_Protections_DW.durationCounter_1_k = 0U;
      }

      if (MCU_Protections_DW.durationCounter_1_k > tmp) {
        MCU_Protections_DW.durationCounter_4 = 0U;
        MCU_Protections_DW.durationCounter_3 = 0U;
        MCU_Protections_DW.durationCounter_2_c = 0U;
        MCU_Protections_DW.durationCounter_1_pp = 0U;
        MCU_Protections_DW.is_Aux_Voltage_Protection =
          MCU_Protections_IN_VoltageSafe;

        /* Outport: '<Root>/Aux_Voltage_Flag' */
        MCU_Protections_Y.Aux_Voltage_Flag = SafeVoltage;
      }
    }
    break;

   case MCU_Protections_IN_UV_Error:
    /* Outport: '<Root>/Aux_Voltage_Flag' */
    MCU_Protections_Y.Aux_Voltage_Flag = UV_Error;
    break;

   case MCU_Protections_IN_UV_Warning:
    /* Outport: '<Root>/Aux_Voltage_Flag' */
    MCU_Protections_Y.Aux_Voltage_Flag = UV_Warning;

    /* Inport: '<Root>/Aux_Voltage_V' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    if (!(MCU_Protections_U.Aux_Voltage_V <
          MCU_Protections_U.Thresholds.Aux_UV_Error_Limit_V)) {
      MCU_Protections_DW.durationCounter_1_p = 0U;
    }

    /* Inport: '<Root>/Thresholds' */
    /* Inport: '<Root>/Aux_Voltage_V' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    tmp = MCU_Protections_U.Thresholds.Voltage_Protection_Timeout_msec * 10.0F;
    if (MCU_Protections_DW.durationCounter_1_p > tmp) {
      MCU_Protections_DW.is_Aux_Voltage_Protection = MCU_Protections_IN_UV_Error;

      /* Outport: '<Root>/Aux_Voltage_Flag' */
      MCU_Protections_Y.Aux_Voltage_Flag = UV_Error;
    } else {
      if (!(MCU_Protections_U.Aux_Voltage_V >
            MCU_Protections_U.Thresholds.Aux_UV_Warning_Limit_V)) {
        MCU_Protections_DW.durationCounter_2_m = 0U;
      }

      if (MCU_Protections_DW.durationCounter_2_m > tmp) {
        MCU_Protections_DW.durationCounter_4 = 0U;
        MCU_Protections_DW.durationCounter_3 = 0U;
        MCU_Protections_DW.durationCounter_2_c = 0U;
        MCU_Protections_DW.durationCounter_1_pp = 0U;
        MCU_Protections_DW.is_Aux_Voltage_Protection =
          MCU_Protections_IN_VoltageSafe;

        /* Outport: '<Root>/Aux_Voltage_Flag' */
        MCU_Protections_Y.Aux_Voltage_Flag = SafeVoltage;
      }
    }
    break;

   default:
    /* Outport: '<Root>/Aux_Voltage_Flag' */
    /* case IN_VoltageSafe: */
    MCU_Protections_Y.Aux_Voltage_Flag = SafeVoltage;

    /* Inport: '<Root>/Aux_Voltage_V' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    if (!(MCU_Protections_U.Aux_Voltage_V >
          MCU_Protections_U.Thresholds.Aux_OV_Error_Limit_V)) {
      MCU_Protections_DW.durationCounter_4 = 0U;
    }

    /* Inport: '<Root>/Thresholds' */
    /* Inport: '<Root>/Aux_Voltage_V' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    tmp = MCU_Protections_U.Thresholds.Voltage_Protection_Timeout_msec * 10.0F;
    if (MCU_Protections_DW.durationCounter_4 > tmp) {
      MCU_Protections_DW.is_Aux_Voltage_Protection = MCU_Protections_IN_OV_Error;

      /* Outport: '<Root>/Aux_Voltage_Flag' */
      MCU_Protections_Y.Aux_Voltage_Flag = OV_Error;
    } else {
      if (!(MCU_Protections_U.Aux_Voltage_V <
            MCU_Protections_U.Thresholds.Aux_UV_Error_Limit_V)) {
        MCU_Protections_DW.durationCounter_2_c = 0U;
      }

      if (MCU_Protections_DW.durationCounter_2_c > tmp) {
        MCU_Protections_DW.is_Aux_Voltage_Protection =
          MCU_Protections_IN_UV_Error;

        /* Outport: '<Root>/Aux_Voltage_Flag' */
        MCU_Protections_Y.Aux_Voltage_Flag = UV_Error;
      } else {
        if (!(MCU_Protections_U.Aux_Voltage_V >
              MCU_Protections_U.Thresholds.Aux_OV_Warning_Limit_V)) {
          MCU_Protections_DW.durationCounter_3 = 0U;
        }

        if (MCU_Protections_DW.durationCounter_3 > tmp) {
          MCU_Protections_DW.durationCounter_2_mw = 0U;
          MCU_Protections_DW.durationCounter_1_k = 0U;
          MCU_Protections_DW.is_Aux_Voltage_Protection =
            MCU_Protections_IN_OV_Warning;

          /* Outport: '<Root>/Aux_Voltage_Flag' */
          MCU_Protections_Y.Aux_Voltage_Flag = OV_Warning;
        } else {
          if (!(MCU_Protections_U.Aux_Voltage_V <
                MCU_Protections_U.Thresholds.Aux_UV_Warning_Limit_V)) {
            MCU_Protections_DW.durationCounter_1_pp = 0U;
          }

          if (MCU_Protections_DW.durationCounter_1_pp > tmp) {
            MCU_Protections_DW.durationCounter_2_m = 0U;
            MCU_Protections_DW.durationCounter_1_p = 0U;
            MCU_Protections_DW.is_Aux_Voltage_Protection =
              MCU_Protections_IN_UV_Warning;

            /* Outport: '<Root>/Aux_Voltage_Flag' */
            MCU_Protections_Y.Aux_Voltage_Flag = UV_Warning;
          }
        }
      }
    }
    break;
  }

  MCU_Prot_Bus_Voltage_Protection();
}

/* Model step function */
void MCU_Protections_step(void)
{
  float rtb_Min;
  bool rtb_RelationalOperator_idx_0;
  bool rtb_RelationalOperator_idx_1;
  bool tmp;

  /* MinMax: '<S1>/Max' incorporates:
   *  Inport: '<Root>/I_a'
   *  Inport: '<Root>/I_b'
   *  Inport: '<Root>/I_c'
   */
  rtb_Min = fmax(fmax(MCU_Protections_U.I_a, MCU_Protections_U.I_b),
                 MCU_Protections_U.I_c);

  /* RelationalOperator: '<S5>/Relational Operator' incorporates:
   *  Inport: '<Root>/Thresholds'
   */
  rtb_RelationalOperator_idx_0 = (rtb_Min >
    MCU_Protections_U.Thresholds.OC_Warning_Limit_A);
  rtb_RelationalOperator_idx_1 = (rtb_Min >
    MCU_Protections_U.Thresholds.OC_Error_Limit_A);

  /* MinMax: '<S1>/Min' incorporates:
   *  Inport: '<Root>/I_a'
   *  Inport: '<Root>/I_b'
   *  Inport: '<Root>/I_c'
   */
  rtb_Min = fmin(fmin(MCU_Protections_U.I_a, MCU_Protections_U.I_b),
                 MCU_Protections_U.I_c);

  /* Logic: '<S5>/OR' incorporates:
   *  Gain: '<S5>/Gain'
   *  Inport: '<Root>/Thresholds'
   *  RelationalOperator: '<S5>/Relational Operator1'
   */
  MCU_Protections_B.OR[0] = (rtb_RelationalOperator_idx_0 || (rtb_Min <
    -MCU_Protections_U.Thresholds.OC_Warning_Limit_A));
  MCU_Protections_B.OR[1] = (rtb_RelationalOperator_idx_1 || (rtb_Min <
    -MCU_Protections_U.Thresholds.OC_Error_Limit_A));

  /* Outputs for Enabled SubSystem: '<S6>/POSITIVE Edge' */
  MCU_Protections_POSITIVEEdge(MCU_Protections_ConstB.MultiportSwitch[0],
    MCU_Protections_B.OR[0], MCU_Protections_DW.Memory_PreviousInput,
    &MCU_Protections_B.RelationalOperator1_j, &MCU_Protections_DW.POSITIVEEdge);

  /* End of Outputs for SubSystem: '<S6>/POSITIVE Edge' */

  /* Outputs for Enabled SubSystem: '<S6>/NEGATIVE Edge' */
  MCU_Protections_NEGATIVEEdge(MCU_Protections_ConstB.MultiportSwitch[1],
    MCU_Protections_B.OR[0], MCU_Protections_DW.Memory_PreviousInput,
    &MCU_Protections_B.RelationalOperator1_i, &MCU_Protections_DW.NEGATIVEEdge);

  /* End of Outputs for SubSystem: '<S6>/NEGATIVE Edge' */

  /* Outputs for Enabled SubSystem: '<S11>/POSITIVE Edge' */
  MCU_Protections_POSITIVEEdge(MCU_Protections_ConstB.MultiportSwitch_n[0],
    MCU_Protections_B.OR[1], MCU_Protections_DW.Memory_PreviousInput_k,
    &MCU_Protections_B.RelationalOperator1, &MCU_Protections_DW.POSITIVEEdge_j);

  /* End of Outputs for SubSystem: '<S11>/POSITIVE Edge' */

  /* Outputs for Enabled SubSystem: '<S11>/NEGATIVE Edge' */
  MCU_Protections_NEGATIVEEdge(MCU_Protections_ConstB.MultiportSwitch_n[1],
    MCU_Protections_B.OR[1], MCU_Protections_DW.Memory_PreviousInput_k,
    &MCU_Protections_B.RelationalOperator1_h, &MCU_Protections_DW.NEGATIVEEdge_f);

  /* End of Outputs for SubSystem: '<S11>/NEGATIVE Edge' */

  /* Logic: '<S11>/Logical Operator1' */
  rtb_RelationalOperator_idx_0 = (MCU_Protections_B.RelationalOperator1 ||
    MCU_Protections_B.RelationalOperator1_h);

  /* Logic: '<S6>/Logical Operator1' */
  rtb_RelationalOperator_idx_1 = (MCU_Protections_B.RelationalOperator1_j ||
    MCU_Protections_B.RelationalOperator1_i);

  /* Chart: '<S1>/Chart' incorporates:
   *  Inport: '<Root>/Aux_Voltage_V'
   *  Inport: '<Root>/Bus_Voltage_V'
   *  Inport: '<Root>/MC_Temperature_C'
   *  Inport: '<Root>/Motor_Temperature_C'
   *  Inport: '<Root>/Thresholds'
   */
  if (MCU_Protections_DW.is_active_c3_MCU_Protections == 0) {
    MCU_Protections_DW.is_active_c3_MCU_Protections = 1U;
    MCU_Protections_DW.is_Current_Protection = MCU_Protections_IN_Init;

    /* Outport: '<Root>/Current_Flag' */
    MCU_Protections_Y.Current_Flag = SafeCurrent;
    MCU_Protections_DW.durationCounter_2 = 0U;
    MCU_Protections_DW.durationCounter_1 = 0U;
    MCU_Protections_DW.is_Init = MCU_Protections_IN_Normal;
    MCU_Protections_DW.durationCounter_2_b = 0U;
    MCU_Protections_DW.durationCounter_1_b = 0U;
    MCU_Protections_DW.is_MC_Temperature_Protection =
      MCU_Protections_IN_TempSafe;

    /* Outport: '<Root>/MC_TempFlag' */
    MCU_Protections_Y.MC_TempFlag = SafeTemperature;
    MCU_Protections_DW.durationCounter_2_p = 0U;
    MCU_Protections_DW.durationCounter_1_ez = 0U;
    MCU_Protections_DW.is_Motor_Temperature_Protection =
      MCU_Protections_IN_TempSafe;

    /* Outport: '<Root>/Motor_TempFlag' */
    MCU_Protections_Y.Motor_TempFlag = SafeTemperature;
    MCU_Protections_DW.durationCounter_4 = 0U;
    MCU_Protections_DW.durationCounter_3 = 0U;
    MCU_Protections_DW.durationCounter_2_c = 0U;
    MCU_Protections_DW.durationCounter_1_pp = 0U;
    MCU_Protections_DW.is_Aux_Voltage_Protection =
      MCU_Protections_IN_VoltageSafe;

    /* Outport: '<Root>/Aux_Voltage_Flag' */
    MCU_Protections_Y.Aux_Voltage_Flag = SafeVoltage;
    MCU_Protections_DW.durationCounter_4_a = 0U;
    MCU_Protections_DW.durationCounter_3_o = 0U;
    MCU_Protections_DW.durationCounter_2_j = 0U;
    MCU_Protections_DW.durationCounter_1_o = 0U;
    MCU_Protections_DW.is_Bus_Voltage_Protection =
      MCU_Protections_IN_VoltageSafe;

    /* Outport: '<Root>/Bus_Voltage_Flag' */
    MCU_Protections_Y.Bus_Voltage_Flag = SafeVoltage;
  } else {
    MCU_Protections_Protections(&rtb_RelationalOperator_idx_0,
      &rtb_RelationalOperator_idx_1);
  }

  tmp = !rtb_RelationalOperator_idx_1;
  if (tmp) {
    MCU_Protections_DW.durationCounter_1++;
  } else {
    MCU_Protections_DW.durationCounter_1 = 0U;
  }

  if (!rtb_RelationalOperator_idx_0) {
    MCU_Protections_DW.durationCounter_2++;
    MCU_Protections_DW.durationCounter_2_h++;
  } else {
    MCU_Protections_DW.durationCounter_2 = 0U;
    MCU_Protections_DW.durationCounter_2_h = 0U;
  }

  if (tmp) {
    MCU_Protections_DW.durationCounter_1_e++;
  } else {
    MCU_Protections_DW.durationCounter_1_e = 0U;
  }

  if (MCU_Protections_U.MC_Temperature_C >
      MCU_Protections_U.Thresholds.MC_OT_Error_Limit_C) {
    MCU_Protections_DW.durationCounter_1_b++;
  } else {
    MCU_Protections_DW.durationCounter_1_b = 0U;
  }

  if (MCU_Protections_U.MC_Temperature_C >
      MCU_Protections_U.Thresholds.MC_OT_Warning_Limit_C) {
    MCU_Protections_DW.durationCounter_2_b++;
  } else {
    MCU_Protections_DW.durationCounter_2_b = 0U;
  }

  if (MCU_Protections_U.MC_Temperature_C <
      MCU_Protections_U.Thresholds.MC_OT_Warning_Limit_C) {
    MCU_Protections_DW.durationCounter_1_d++;
  } else {
    MCU_Protections_DW.durationCounter_1_d = 0U;
  }

  if (MCU_Protections_U.MC_Temperature_C >
      MCU_Protections_U.Thresholds.MC_OT_Error_Limit_C) {
    MCU_Protections_DW.durationCounter_2_br++;
  } else {
    MCU_Protections_DW.durationCounter_2_br = 0U;
  }

  if (MCU_Protections_U.Motor_Temperature_C >
      MCU_Protections_U.Thresholds.Motor_OT_Error_Limit_C) {
    MCU_Protections_DW.durationCounter_1_ez++;
  } else {
    MCU_Protections_DW.durationCounter_1_ez = 0U;
  }

  if (MCU_Protections_U.Motor_Temperature_C >
      MCU_Protections_U.Thresholds.Motor_OT_Warning_Limit_C) {
    MCU_Protections_DW.durationCounter_2_p++;
  } else {
    MCU_Protections_DW.durationCounter_2_p = 0U;
  }

  if (MCU_Protections_U.Motor_Temperature_C <
      MCU_Protections_U.Thresholds.Motor_OT_Warning_Limit_C) {
    MCU_Protections_DW.durationCounter_1_i++;
  } else {
    MCU_Protections_DW.durationCounter_1_i = 0U;
  }

  if (MCU_Protections_U.Motor_Temperature_C >
      MCU_Protections_U.Thresholds.Motor_OT_Error_Limit_C) {
    MCU_Protections_DW.durationCounter_2_k++;
  } else {
    MCU_Protections_DW.durationCounter_2_k = 0U;
  }

  if (MCU_Protections_U.Aux_Voltage_V <
      MCU_Protections_U.Thresholds.Aux_UV_Error_Limit_V) {
    MCU_Protections_DW.durationCounter_1_p++;
  } else {
    MCU_Protections_DW.durationCounter_1_p = 0U;
  }

  if (MCU_Protections_U.Aux_Voltage_V <
      MCU_Protections_U.Thresholds.Aux_UV_Warning_Limit_V) {
    MCU_Protections_DW.durationCounter_1_pp++;
  } else {
    MCU_Protections_DW.durationCounter_1_pp = 0U;
  }

  if (MCU_Protections_U.Aux_Voltage_V >
      MCU_Protections_U.Thresholds.Aux_UV_Warning_Limit_V) {
    MCU_Protections_DW.durationCounter_2_m++;
  } else {
    MCU_Protections_DW.durationCounter_2_m = 0U;
  }

  if (MCU_Protections_U.Aux_Voltage_V <
      MCU_Protections_U.Thresholds.Aux_UV_Error_Limit_V) {
    MCU_Protections_DW.durationCounter_2_c++;
  } else {
    MCU_Protections_DW.durationCounter_2_c = 0U;
  }

  if (MCU_Protections_U.Aux_Voltage_V >
      MCU_Protections_U.Thresholds.Aux_OV_Warning_Limit_V) {
    MCU_Protections_DW.durationCounter_3++;
  } else {
    MCU_Protections_DW.durationCounter_3 = 0U;
  }

  if (MCU_Protections_U.Aux_Voltage_V >
      MCU_Protections_U.Thresholds.Aux_OV_Error_Limit_V) {
    MCU_Protections_DW.durationCounter_4++;
  } else {
    MCU_Protections_DW.durationCounter_4 = 0U;
  }

  if (MCU_Protections_U.Aux_Voltage_V <
      MCU_Protections_U.Thresholds.Aux_OV_Warning_Limit_V) {
    MCU_Protections_DW.durationCounter_1_k++;
  } else {
    MCU_Protections_DW.durationCounter_1_k = 0U;
  }

  if (MCU_Protections_U.Aux_Voltage_V >
      MCU_Protections_U.Thresholds.Aux_OV_Error_Limit_V) {
    MCU_Protections_DW.durationCounter_2_mw++;
  } else {
    MCU_Protections_DW.durationCounter_2_mw = 0U;
  }

  if (MCU_Protections_U.Bus_Voltage_V <
      MCU_Protections_U.Thresholds.UV_Error_Limit_V) {
    MCU_Protections_DW.durationCounter_1_f++;
  } else {
    MCU_Protections_DW.durationCounter_1_f = 0U;
  }

  if (MCU_Protections_U.Bus_Voltage_V <
      MCU_Protections_U.Thresholds.UV_Warning_Limit_V) {
    MCU_Protections_DW.durationCounter_1_o++;
  } else {
    MCU_Protections_DW.durationCounter_1_o = 0U;
  }

  if (MCU_Protections_U.Bus_Voltage_V >
      MCU_Protections_U.Thresholds.UV_Warning_Limit_V) {
    MCU_Protections_DW.durationCounter_2_cm++;
  } else {
    MCU_Protections_DW.durationCounter_2_cm = 0U;
  }

  if (MCU_Protections_U.Bus_Voltage_V <
      MCU_Protections_U.Thresholds.UV_Error_Limit_V) {
    MCU_Protections_DW.durationCounter_2_j++;
  } else {
    MCU_Protections_DW.durationCounter_2_j = 0U;
  }

  if (MCU_Protections_U.Bus_Voltage_V >
      MCU_Protections_U.Thresholds.OV_Warning_Limit_V) {
    MCU_Protections_DW.durationCounter_3_o++;
  } else {
    MCU_Protections_DW.durationCounter_3_o = 0U;
  }

  if (MCU_Protections_U.Bus_Voltage_V >
      MCU_Protections_U.Thresholds.OV_Error_Limit_V) {
    MCU_Protections_DW.durationCounter_4_a++;
  } else {
    MCU_Protections_DW.durationCounter_4_a = 0U;
  }

  if (MCU_Protections_U.Bus_Voltage_V <
      MCU_Protections_U.Thresholds.OV_Warning_Limit_V) {
    MCU_Protections_DW.durationCounter_1_bx++;
  } else {
    MCU_Protections_DW.durationCounter_1_bx = 0U;
  }

  if (MCU_Protections_U.Bus_Voltage_V >
      MCU_Protections_U.Thresholds.OV_Error_Limit_V) {
    MCU_Protections_DW.durationCounter_2_m0++;
  } else {
    MCU_Protections_DW.durationCounter_2_m0 = 0U;
  }

  /* End of Chart: '<S1>/Chart' */

  /* Outputs for Triggered SubSystem: '<S7>/Triggered Subsystem' incorporates:
   *  TriggerPort: '<S10>/Trigger'
   */
  MCU_Protections_PrevZCX.TriggeredSubsystem_Trig_ZCE_n =
    rtb_RelationalOperator_idx_1;

  /* End of Outputs for SubSystem: '<S7>/Triggered Subsystem' */

  /* Outputs for Triggered SubSystem: '<S12>/Triggered Subsystem' incorporates:
   *  TriggerPort: '<S15>/Trigger'
   */
  MCU_Protections_PrevZCX.TriggeredSubsystem_Trig_ZCE =
    rtb_RelationalOperator_idx_0;

  /* End of Outputs for SubSystem: '<S12>/Triggered Subsystem' */

  /* Update for Memory: '<S6>/Memory' */
  MCU_Protections_DW.Memory_PreviousInput = MCU_Protections_B.OR[0];

  /* Update for Memory: '<S11>/Memory' */
  MCU_Protections_DW.Memory_PreviousInput_k = MCU_Protections_B.OR[1];

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  MCU_Protections_M->Timing.t[0] =
    ((float)(++MCU_Protections_M->Timing.clockTick0)) *
    MCU_Protections_M->Timing.stepSize0;

  {
    /* Update absolute timer for sample time: [0.0001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.0001, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    MCU_Protections_M->Timing.clockTick1++;
  }
}

/* Model initialize function */
void MCU_Protections_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&MCU_Protections_M->solverInfo,
                          &MCU_Protections_M->Timing.simTimeStep);
    rtsiSetTPtr(&MCU_Protections_M->solverInfo, &rtmGetTPtr(MCU_Protections_M));
    rtsiSetStepSizePtr(&MCU_Protections_M->solverInfo,
                       &MCU_Protections_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&MCU_Protections_M->solverInfo, (&rtmGetErrorStatus
      (MCU_Protections_M)));
    rtsiSetRTModelPtr(&MCU_Protections_M->solverInfo, MCU_Protections_M);
  }

  rtsiSetSimTimeStep(&MCU_Protections_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&MCU_Protections_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&MCU_Protections_M->solverInfo, false);
  rtsiSetSolverName(&MCU_Protections_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(MCU_Protections_M, &MCU_Protections_M->Timing.tArray[0]);
  MCU_Protections_M->Timing.stepSize0 = 0.0001;
  MCU_Protections_PrevZCX.TriggeredSubsystem_Trig_ZCE_n = POS_ZCSIG;
  MCU_Protections_PrevZCX.TriggeredSubsystem_Trig_ZCE = POS_ZCSIG;

  /* Threshold values */
  MCU_Protections_U.Thresholds.Aux_OV_Error_Limit_V = 18.0f;
  MCU_Protections_U.Thresholds.Aux_OV_Warning_Limit_V = 15.0f;
  MCU_Protections_U.Thresholds.Aux_UV_Warning_Limit_V = 10.0f;
  MCU_Protections_U.Thresholds.Aux_UV_Error_Limit_V = 8.5f;

  MCU_Protections_U.Thresholds.MC_OT_Warning_Limit_C = 75.0f;
  MCU_Protections_U.Thresholds.MC_OT_Error_Limit_C = 85.0f;
  MCU_Protections_U.Thresholds.Motor_OT_Warning_Limit_C = 100.0f;
  MCU_Protections_U.Thresholds.Motor_OT_Error_Limit_C = 120.0f;

  MCU_Protections_U.Thresholds.OC_Warning_Limit_A = 400.0f;
  MCU_Protections_U.Thresholds.OC_Error_Limit_A = 450.0f;
  MCU_Protections_U.Thresholds.Current_count_limit = 100.0f;

  MCU_Protections_U.Thresholds.OV_Warning_Limit_V = 110.0f;
  MCU_Protections_U.Thresholds.OV_Error_Limit_V = 115.0f;
  MCU_Protections_U.Thresholds.UV_Warning_Limit_V = 80.0f;
  MCU_Protections_U.Thresholds.UV_Error_Limit_V = 75.0f;

  MCU_Protections_U.Thresholds.Voltage_Protection_Timeout_msec = 150.0f;
  MCU_Protections_U.Thresholds.Temp_Protection_Timeout_msec = 150.0f;
  MCU_Protections_U.Thresholds.Time_current_limit_normal_msec = 150.0f;
}

/* Model terminate function */
void MCU_Protections_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
