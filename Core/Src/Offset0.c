/*
 * File: Offset0.c
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

#include "Offset0.h"
#include <stdint.h>
#include <math.h>
#include "rt_nonfinite.h"
#include <stdbool.h>
#include "Offset0_private.h"
#include "rt_defines.h"

/* Named constants for Chart: '<S1>/Chart' */
#define IN_Average_Offset_calculation_C ((uint8_t)1U)
#define IN_Average_Offset_calculation_g ((uint8_t)2U)
#define O_IN_Reverse_Motor_speedRpm_set ((uint8_t)4U)
#define Off_IN_Offset_angle_calculation ((uint8_t)2U)
#define Offset0_IN_Angle_shifting      ((uint8_t)1U)
#define Offset0_IN_Check_FineOffset    ((uint8_t)1U)
#define Offset0_IN_Coarse_offset_angle ((uint8_t)1U)
#define Offset0_IN_Fine_Offset_angle   ((uint8_t)2U)
#define Offset0_IN_Motor_speedRpm_set  ((uint8_t)3U)
#define Offset0_IN_NO_ACTIVE_CHILD     ((uint8_t)0U)
#define Offset0_IN_Rotor_Allingment    ((uint8_t)2U)
#define Offset0_IN_Speed_Zero          ((uint8_t)3U)
#define Offset0_IN_Tuning_complete     ((uint8_t)4U)
#define Offset0_IN_go_for_CCW          ((uint8_t)5U)
#define Offset0_IN_go_for_CCW_c        ((uint8_t)4U)
#define Offset0_IN_go_for_CW           ((uint8_t)6U)
#define Offset0_IN_samples_Average     ((uint8_t)5U)
#define Offset_IN_Go_for_closedloop_FOC ((uint8_t)3U)

/* Block signals (default storage) */
B_Offset0_T Offset0_B;

/* Block states (default storage) */
DW_Offset0_T Offset0_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Offset0_T Offset0_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Offset0_T Offset0_Y;

/* Real-time model */
static RT_MODEL_Offset0_T Offset0_M_;
RT_MODEL_Offset0_T *const Offset0_M = &Offset0_M_;

/* Forward declaration for local functions */
static float Offset0_mod(float x);
static void exit_internal_Average_Offset_ca(void);
static void Offset0_Fine_Offset_angle(void);

/* Function for Chart: '<S1>/Chart' */
static float Offset0_mod(float x)
{
  float r;
  if (rtIsNaNF(x)) {
    r = (rtNaNF);
  } else if (rtIsInfF(x)) {
    r = (rtNaNF);
  } else if (x == 0.0F) {
    r = 0.0F;
  } else {
    bool rEQ0;
    r = fmodf(x, 6.28318548F);
    rEQ0 = (r == 0.0F);
    if (!rEQ0) {
      float q;
      q = fabsf(x / 6.28318548F);
      rEQ0 = !(fabsf(q - floorf(q + 0.5F)) > 1.1920929E-7F * q);
    }

    if (rEQ0) {
      r = 0.0F;
    } else if (r < 0.0F) {
      r += 6.28318548F;
    }
  }

  return r;
}

//float rt_atan2f_snf(float u0, float u1)
//{
//  float y;
//  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
//    y = (rtNaNF);
//  } else if (rtIsInfF(u0) && rtIsInfF(u1)) {
//    int32_t tmp;
//    int32_t tmp_0;
//    if (u0 > 0.0F) {
//      tmp = 1;
//    } else {
//      tmp = -1;
//    }
//
//    if (u1 > 0.0F) {
//      tmp_0 = 1;
//    } else {
//      tmp_0 = -1;
//    }
//
//    y = atan2f((float)tmp, (float)tmp_0);
//  } else if (u1 == 0.0F) {
//    if (u0 > 0.0F) {
//      y = RT_PIF / 2.0F;
//    } else if (u0 < 0.0F) {
//      y = -(RT_PIF / 2.0F);
//    } else {
//      y = 0.0F;
//    }
//  } else {
//    y = atan2f(u0, u1);
//  }
//
//  return y;
//}

/* Function for Chart: '<S1>/Chart' */
static void exit_internal_Average_Offset_ca(void)
{
  if (Offset0_DW.is_Average_Offset_calculation_e ==
      Off_IN_Offset_angle_calculation) {
    /* Outport: '<Root>/Vd_net' incorporates:
     *  Inport: '<Root>/Vd_MAX'
     *  Outport: '<Root>/Vd_avg'
     */
    Offset0_Y.Vd_net = fabsf(Offset0_Y.Vd_avg - Offset0_U.Vd_MAX);

    /* Outport: '<Root>/Angle' incorporates:
     *  Inport: '<Root>/POLE_PAIRS'
     *  Outport: '<Root>/Vd_net'
     *  Outport: '<Root>/Vq_avg'
     */
    Offset0_Y.Angle = rt_atan2f_snf(Offset0_Y.Vd_net, fabsf(Offset0_Y.Vq_avg)) /
      (float)Offset0_U.POLE_PAIRS;

    /* Outport: '<Root>/Vd_avg' incorporates:
     *  Inport: '<Root>/Vd_MAX'
     *  Inport: '<Root>/Vd_MIN'
     *  Outport: '<Root>/Angle'
     */
    if (Offset0_Y.Vd_avg <= Offset0_U.Vd_MIN) {
      Offset0_DW.Angle_f = -Offset0_Y.Angle;
    } else if (Offset0_Y.Vd_avg >= Offset0_U.Vd_MAX) {
      Offset0_DW.Angle_f = Offset0_Y.Angle;
    }

    /* Outport: '<Root>/Offset_CW' */
    Offset0_Y.Offset_CW += Offset0_DW.Angle_f;
    Offset0_DW.is_Average_Offset_calculation_e = Offset0_IN_NO_ACTIVE_CHILD;
  } else {
    Offset0_DW.is_Average_Offset_calculation_e = Offset0_IN_NO_ACTIVE_CHILD;
  }
}

/* Function for Chart: '<S1>/Chart' */
static void Offset0_Fine_Offset_angle(void)
{
  float error;
  uint32_t tmp;
  switch (Offset0_DW.is_Fine_Offset_angle) {
   case IN_Average_Offset_calculation_C:
    if (Offset0_DW.Repeat_CCW == 1) {
      if (Offset0_DW.is_Average_Offset_calculation_C ==
          Off_IN_Offset_angle_calculation) {
        /* Outport: '<Root>/Vd_net' incorporates:
         *  Inport: '<Root>/Vd_MIN'
         *  Outport: '<Root>/Vd_avg'
         */
        Offset0_Y.Vd_net = fabsf(Offset0_Y.Vd_avg - Offset0_U.Vd_MIN);

        /* Outport: '<Root>/Angle' incorporates:
         *  Inport: '<Root>/POLE_PAIRS'
         *  Outport: '<Root>/Vd_net'
         *  Outport: '<Root>/Vq_avg'
         */
        Offset0_Y.Angle = rt_atan2f_snf(Offset0_Y.Vd_net, fabsf(Offset0_Y.Vq_avg))
          / (float)Offset0_U.POLE_PAIRS;

        /* Outport: '<Root>/Offset_CCW' incorporates:
         *  Outport: '<Root>/Angle'
         */
        Offset0_Y.Offset_CCW += Offset0_Y.Angle;

        /* Outport: '<Root>/RR' */
        Offset0_Y.RR = 0U;
        Offset0_DW.is_Average_Offset_calculation_C = Offset0_IN_NO_ACTIVE_CHILD;
      } else {
        Offset0_DW.is_Average_Offset_calculation_C = Offset0_IN_NO_ACTIVE_CHILD;
      }

      Offset0_DW.temporalCounter_i1 = 0U;
      Offset0_DW.is_Fine_Offset_angle = Offset0_IN_go_for_CCW;
    } else {
      switch (Offset0_DW.is_Average_Offset_calculation_C) {
       case Offset0_IN_Check_FineOffset:
        /* Outport: '<Root>/ AutotuneCompleteflag' incorporates:
         *  Inport: '<Root>/NO_OF_CCW_SAMPLE'
         *  Inport: '<Root>/Vd_MAX'
         *  Outport: '<Root>/Vd_avg'
         */
        if (Offset0_Y.AutotuneCompleteflag == 1) {
          Offset0_DW.is_Average_Offset_calculation_C =
            Offset0_IN_Tuning_complete;
        } else {
          error = fabsf(Offset0_Y.Vd_avg) - fabsf(Offset0_U.Vd_MAX);
          if (error >= 0.04) {
            Offset0_DW.sample2++;
            Offset0_DW.Repeat_CCW = 1U;
            if (Offset0_DW.sample2 >= Offset0_U.NO_OF_CCW_SAMPLE) {
              Offset0_DW.Repeat_CCW = 0U;
              Offset0_Y.AutotuneCompleteflag = 1U;
              Offset0_DW.sample2 = 0.0F;
            }
          } else if (error <= 0.04) {
            Offset0_Y.AutotuneCompleteflag = 1U;
          }
        }
        break;

       case Off_IN_Offset_angle_calculation:
        if (Offset0_DW.temporalCounter_i1 >= 1) {
          /* Outport: '<Root>/Vd_net' incorporates:
           *  Inport: '<Root>/Vd_MIN'
           *  Outport: '<Root>/Vd_avg'
           */
          Offset0_Y.Vd_net = fabsf(Offset0_Y.Vd_avg - Offset0_U.Vd_MIN);

          /* Outport: '<Root>/Angle' incorporates:
           *  Inport: '<Root>/POLE_PAIRS'
           *  Outport: '<Root>/Vd_net'
           *  Outport: '<Root>/Vq_avg'
           */
          Offset0_Y.Angle = rt_atan2f_snf(Offset0_Y.Vd_net, fabsf
            (Offset0_Y.Vq_avg)) / (float)Offset0_U.POLE_PAIRS;

          /* Outport: '<Root>/Offset_CCW' incorporates:
           *  Outport: '<Root>/Angle'
           */
          Offset0_Y.Offset_CCW += Offset0_Y.Angle;

          /* Outport: '<Root>/RR' */
          Offset0_Y.RR = 0U;
          Offset0_DW.is_Average_Offset_calculation_C =
            Offset0_IN_Check_FineOffset;

          /* Outport: '<Root>/ AutotuneCompleteflag' */
          Offset0_Y.AutotuneCompleteflag = 0U;
          Offset0_DW.Rotate_CCW = 0U;
        }
        break;

       case Offset0_IN_Speed_Zero:
        if (Offset0_DW.temporalCounter_i1 >= 1) {
          Offset0_DW.temporalCounter_i1 = 0U;
          Offset0_DW.is_Average_Offset_calculation_C =
            Off_IN_Offset_angle_calculation;

          /* Outport: '<Root>/Vd_net' */
          Offset0_Y.Vd_net = 0.0F;

          /* Outport: '<Root>/Angle' */
          Offset0_Y.Angle = 0.0F;
        }
        break;

       case Offset0_IN_Tuning_complete:
        Offset0_DW.Repeat_CCW = 0U;

        /* Outport: '<Root>/ AutotuneCompleteflag' */
        Offset0_Y.AutotuneCompleteflag = 1U;
        break;

       default:
        /* case IN_samples_Average: */
        if (Offset0_DW.flag4 == 1) {
          Offset0_DW.temporalCounter_i1 = 0U;
          Offset0_DW.is_Average_Offset_calculation_C = Offset0_IN_Speed_Zero;
          Offset0_DW.flag = 0U;
          Offset0_B.MotorRpmRef = 0.0F;
        } else {
          tmp = Offset0_DW.timer3 + 1U;
          if (Offset0_DW.timer3 + 1U > 65535U) {
            tmp = 65535U;
          }

          Offset0_DW.timer3 = (uint16_t)tmp;

          /* Inport: '<Root>/Vd' */
          Offset0_DW.Vd_samp += Offset0_U.Vd;

          /* Inport: '<Root>/Vq' */
          Offset0_DW.Vq_samp += Offset0_U.Vq;

          /* Inport: '<Root>/NO_OF_V_SAMPLES' */
          if (Offset0_DW.timer3 >= Offset0_U.NO_OF_V_SAMPLES) {
            /* Outport: '<Root>/Vd_avg' */
            Offset0_Y.Vd_avg = Offset0_DW.Vd_samp / Offset0_U.NO_OF_V_SAMPLES;

            /* Outport: '<Root>/Vq_avg' */
            Offset0_Y.Vq_avg = Offset0_DW.Vq_samp / Offset0_U.NO_OF_V_SAMPLES;
            Offset0_DW.timer3 = 0U;
            Offset0_DW.Vd_samp = 0.0F;
            Offset0_DW.Vq_samp = 0.0F;
            Offset0_DW.flag4 = 1U;
          }
        }
        break;
      }
    }
    break;

   case IN_Average_Offset_calculation_g:
    if (Offset0_DW.Repeat_CW == 1) {
      exit_internal_Average_Offset_ca();
      Offset0_DW.temporalCounter_i1 = 0U;
      Offset0_DW.is_Fine_Offset_angle = Offset0_IN_go_for_CW;
    } else if ((Offset0_DW.Rotate_CCW == 1) && (Offset0_DW.temporalCounter_i1 >=
                Offset0_U.WAIT_TIME)) {
      exit_internal_Average_Offset_ca();
      Offset0_DW.temporalCounter_i1 = 0U;
      Offset0_DW.is_Fine_Offset_angle = O_IN_Reverse_Motor_speedRpm_set;
      Offset0_DW.Repeat_CCW = 0U;

      /* Outport: '<Root>/FNR' */
      Offset0_Y.FNR = 2U;
    } else {
      switch (Offset0_DW.is_Average_Offset_calculation_e) {
       case Offset0_IN_Check_FineOffset:
        if (Offset0_DW.Rotate_CCW == 1) {
          Offset0_DW.is_Average_Offset_calculation_e = Offset0_IN_go_for_CCW_c;
        } else {
          /* Outport: '<Root>/Vd_avg' incorporates:
           *  Inport: '<Root>/Vd_MAX'
           */
          error = fabsf(Offset0_Y.Vd_avg) - fabsf(Offset0_U.Vd_MAX);
          if (error >= 0.04) {
            Offset0_DW.sample++;
            Offset0_DW.Repeat_CW = 1U;

            /* Inport: '<Root>/NO_OF_CW_SAMPLE' */
            if (Offset0_DW.sample >= Offset0_U.NO_OF_CW_SAMPLE) {
              Offset0_DW.Repeat_CW = 0U;
              Offset0_DW.Rotate_CCW = 1U;
              Offset0_DW.sample = 0.0F;
            }

            /* End of Inport: '<Root>/NO_OF_CW_SAMPLE' */
          } else if (error <= 0.04) {
            Offset0_DW.Rotate_CCW = 1U;
          }
        }
        break;

       case Off_IN_Offset_angle_calculation:
        if (Offset0_DW.temporalCounter_i2 >= 1) {
          /* Outport: '<Root>/Vd_net' incorporates:
           *  Inport: '<Root>/Vd_MAX'
           *  Outport: '<Root>/Vd_avg'
           */
          Offset0_Y.Vd_net = fabsf(Offset0_Y.Vd_avg - Offset0_U.Vd_MAX);

          /* Outport: '<Root>/Angle' incorporates:
           *  Inport: '<Root>/POLE_PAIRS'
           *  Outport: '<Root>/Vd_net'
           *  Outport: '<Root>/Vq_avg'
           */
          Offset0_Y.Angle = rt_atan2f_snf(Offset0_Y.Vd_net, fabsf
            (Offset0_Y.Vq_avg)) / (float)Offset0_U.POLE_PAIRS;

          /* Outport: '<Root>/Vd_avg' incorporates:
           *  Inport: '<Root>/Vd_MAX'
           *  Inport: '<Root>/Vd_MIN'
           *  Outport: '<Root>/Angle'
           */
          if (Offset0_Y.Vd_avg <= Offset0_U.Vd_MIN) {
            Offset0_DW.Angle_f = -Offset0_Y.Angle;
          } else if (Offset0_Y.Vd_avg >= Offset0_U.Vd_MAX) {
            Offset0_DW.Angle_f = Offset0_Y.Angle;
          }

          /* Outport: '<Root>/Offset_CW' */
          Offset0_Y.Offset_CW += Offset0_DW.Angle_f;
          Offset0_DW.is_Average_Offset_calculation_e =
            Offset0_IN_Check_FineOffset;
          Offset0_DW.Repeat_CW = 0U;
          Offset0_DW.Rotate_CCW = 0U;
        }
        break;

       case Offset0_IN_Speed_Zero:
        if (Offset0_DW.temporalCounter_i2 >= 1) {
          Offset0_DW.temporalCounter_i2 = 0U;
          Offset0_DW.is_Average_Offset_calculation_e =
            Off_IN_Offset_angle_calculation;

          /* Outport: '<Root>/Vd_net' */
          Offset0_Y.Vd_net = 0.0F;

          /* Outport: '<Root>/Angle' */
          Offset0_Y.Angle = 0.0F;
          Offset0_DW.Angle_f = 0.0F;
        }
        break;

       case Offset0_IN_go_for_CCW_c:
        Offset0_DW.Repeat_CW = 0U;
        Offset0_DW.Rotate_CCW = 1U;

        /* Outport: '<Root>/FNR' */
        Offset0_Y.FNR = 3U;

        /* Outport: '<Root>/RR' */
        Offset0_Y.RR = 1U;
        break;

       default:
        /* case IN_samples_Average: */
        if (Offset0_DW.flag == 1) {
          Offset0_DW.temporalCounter_i2 = 0U;
          Offset0_DW.is_Average_Offset_calculation_e = Offset0_IN_Speed_Zero;
          Offset0_DW.flag = 0U;
          Offset0_B.MotorRpmRef = 0.0F;
        } else {
          tmp = Offset0_DW.timer1 + 1U;
          if (Offset0_DW.timer1 + 1U > 65535U) {
            tmp = 65535U;
          }

          Offset0_DW.timer1 = (uint16_t)tmp;

          /* Inport: '<Root>/Vd' */
          Offset0_DW.Vd_samp += Offset0_U.Vd;

          /* Inport: '<Root>/Vq' */
          Offset0_DW.Vq_samp += Offset0_U.Vq;

          /* Inport: '<Root>/NO_OF_V_SAMPLES' */
          if (Offset0_DW.timer1 >= Offset0_U.NO_OF_V_SAMPLES) {
            /* Outport: '<Root>/Vd_avg' */
            Offset0_Y.Vd_avg = Offset0_DW.Vd_samp / Offset0_U.NO_OF_V_SAMPLES;

            /* Outport: '<Root>/Vq_avg' */
            Offset0_Y.Vq_avg = Offset0_DW.Vq_samp / Offset0_U.NO_OF_V_SAMPLES;
            Offset0_DW.timer1 = 0U;
            Offset0_DW.Vd_samp = 0.0F;
            Offset0_DW.Vq_samp = 0.0F;
            Offset0_DW.flag = 1U;
          }
        }
        break;
      }
    }
    break;

   case Offset0_IN_Motor_speedRpm_set:
    /* Inport: '<Root>/WAIT_TIME' */
    if (Offset0_DW.temporalCounter_i1 >= Offset0_U.WAIT_TIME) {
      Offset0_DW.temporalCounter_i1 = 0U;
      Offset0_DW.is_Fine_Offset_angle = IN_Average_Offset_calculation_g;
      Offset0_DW.timer1 = 0U;
      Offset0_DW.timer2 = 0U;
      Offset0_DW.is_Average_Offset_calculation_e = Offset0_IN_samples_Average;
      Offset0_DW.Vd_samp = 0.0F;
      Offset0_DW.Vq_samp = 0.0F;
      Offset0_DW.flag = 0U;
    } else {
      /* Inport: '<Root>/RATED_RPM' */
      Offset0_B.MotorRpmRef = Offset0_U.RATED_RPM;
    }
    break;

   case O_IN_Reverse_Motor_speedRpm_set:
    /* Inport: '<Root>/WAIT_TIME' */
    if ((Offset0_DW.temporalCounter_i1 >= Offset0_U.WAIT_TIME) &&
        (Offset0_DW.Repeat_CCW == 0)) {
      Offset0_DW.is_Fine_Offset_angle = IN_Average_Offset_calculation_C;
      Offset0_DW.timer3 = 0U;
      Offset0_DW.timer4 = 0U;
      Offset0_DW.is_Average_Offset_calculation_C = Offset0_IN_samples_Average;
      Offset0_DW.Vd_samp = 0.0F;
      Offset0_DW.Vq_samp = 0.0F;
      Offset0_DW.flag4 = 0U;
    } else {
      /* Inport: '<Root>/RATED_RPM' */
      Offset0_B.MotorRpmRef = Offset0_U.RATED_RPM;
    }
    break;

   case Offset0_IN_go_for_CCW:
    /* Inport: '<Root>/WAIT_TIME' */
    if ((Offset0_DW.temporalCounter_i1 >= Offset0_U.WAIT_TIME) &&
        (Offset0_DW.Repeat_CCW == 1)) {
      Offset0_DW.temporalCounter_i1 = 0U;
      Offset0_DW.is_Fine_Offset_angle = O_IN_Reverse_Motor_speedRpm_set;
      Offset0_DW.Repeat_CCW = 0U;

      /* Outport: '<Root>/FNR' */
      Offset0_Y.FNR = 2U;
    }
    break;

   default:
    /* Inport: '<Root>/WAIT_TIME' */
    /* case IN_go_for_CW: */
    if ((Offset0_DW.temporalCounter_i1 >= Offset0_U.WAIT_TIME) &&
        (Offset0_DW.Repeat_CW == 1)) {
      Offset0_DW.temporalCounter_i1 = 0U;
      Offset0_DW.is_Fine_Offset_angle = Offset0_IN_Motor_speedRpm_set;
      Offset0_DW.Repeat_CW = 0U;

      /* Outport: '<Root>/FNR' */
      Offset0_Y.FNR = 1U;
    }
    break;
  }
}

/* Model step function */
void Offset0_step(void)
{
  float q;
  float rtb_deltafalllimit;
  uint32_t tmp;
  bool rEQ0;

  /* Chart: '<S1>/Chart' incorporates:
   *  Inport: '<Root>/ALIGNEMENT_TMOO'
   *  Inport: '<Root>/AUTOTUNE_IDREF_INCREMENTT'
   *  Inport: '<Root>/IDREF_MAX_LIMITT'
   *  Inport: '<Root>/MAX_SAMPLE_ROTATION'
   *  Inport: '<Root>/Pwmangle'
   *  Outport: '<Root>/Electricalangle'
   *  Outport: '<Root>/FOC_closed_loop'
   *  Outport: '<Root>/Idref'
   *  Outport: '<Root>/error_C'
   */
  if (Offset0_DW.temporalCounter_i1 < 65535U) {
    Offset0_DW.temporalCounter_i1++;
  }

  if (Offset0_DW.temporalCounter_i2 < 1) {
    Offset0_DW.temporalCounter_i2 = 1U;
  }

  if (Offset0_DW.is_active_c3_Offset0 == 0) {
    Offset0_DW.is_active_c3_Offset0 = 1U;
    Offset0_DW.is_c3_Offset0 = Offset0_IN_Coarse_offset_angle;
    Offset0_DW.timer1 = 0U;
    Offset0_DW.timer2 = 0U;
    Offset0_DW.timer3 = 0U;
    Offset0_DW.timer4 = 0U;

    /* Outport: '<Root>/FOC_closed_loop' */
    Offset0_Y.FOC_closed_loop = 0U;
    Offset0_DW.is_Coarse_offset_angle = Offset0_IN_Rotor_Allingment;

    /* Outport: '<Root>/Idref' incorporates:
     *  Inport: '<Root>/AUTO_TUNING_IDREFF'
     */
    Offset0_Y.Idref = Offset0_U.AUTO_TUNING_IDREFF;

    /* Outport: '<Root>/Iqref' */
    Offset0_Y.Iqref = 0.0F;

    /* Outport: '<Root>/Electricalangle' */
    Offset0_Y.Electricalangle = 0.0F;
  } else {
    switch (Offset0_DW.is_c3_Offset0) {
     case Offset0_IN_Coarse_offset_angle:
      if (Offset0_Y.FOC_closed_loop == 1) {
        if (Offset0_DW.is_Coarse_offset_angle == Offset0_IN_Angle_shifting) {
          /* Outport: '<Root>/Idref' */
          Offset0_Y.Idref = 0.0F;
          Offset0_DW.is_Coarse_offset_angle = Offset0_IN_NO_ACTIVE_CHILD;
        } else {
          Offset0_DW.is_Coarse_offset_angle = Offset0_IN_NO_ACTIVE_CHILD;
        }

        Offset0_DW.temporalCounter_i1 = 0U;
        Offset0_DW.is_c3_Offset0 = Offset_IN_Go_for_closedloop_FOC;
      } else if (Offset0_DW.is_Coarse_offset_angle == Offset0_IN_Angle_shifting)
      {
        /* Outport: '<Root>/Iqref' */
        Offset0_Y.Iqref = 0.0F;
        Offset0_B.flag_C = 0U;
        if (Offset0_DW.sample < Offset0_U.MAX_SAMPLE_ROTATION) {
          tmp = Offset0_DW.timer2 + 1U;
          if (Offset0_DW.timer2 + 1U > 65535U) {
            tmp = 65535U;
          }

          Offset0_DW.timer2 = (uint16_t)tmp;
          if (Offset0_DW.timer2 > Offset0_U.ALIGNEMENT_TMOO) {
            Offset0_B.flag_C = 1U;

            /* Outport: '<Root>/error_C' incorporates:
             *  Inport: '<Root>/Pole_pairs'
             *  Inport: '<Root>/Pwmangle'
             *  Outport: '<Root>/Electricalangle'
             *  Product: '<S1>/Product'
             */
            Offset0_Y.error_C = fabsf(Offset0_mod(Offset0_U.Pwmangle *
              Offset0_U.Pole_pairs) - Offset0_Y.Electricalangle);
            tmp = Offset0_DW.timer4 + 1U;
            if (Offset0_DW.timer4 + 1U > 65535U) {
              tmp = 65535U;
            }

            Offset0_DW.timer4 = (uint16_t)tmp;
            Offset0_DW.error_sample += Offset0_Y.error_C;
            if (Offset0_DW.timer4 >= 2000) {
              /* Outport: '<Root>/initial_offset2' */
              Offset0_Y.initial_offset2 = Offset0_DW.error_sample / 2000.0F;
              Offset0_DW.error_sample = 0.0F;
              Offset0_DW.timer4 = 0U;
            }

            /* Outport: '<Root>/Electricalangle' incorporates:
             *  Inport: '<Root>/AUTOTUNE_ANGLE_INCREMENTT'
             *  Outport: '<Root>/error_C'
             */
            Offset0_Y.Electricalangle += Offset0_U.AUTOTUNE_ANGLE_INCREMENTT;
            if (Offset0_Y.Electricalangle >= 6.2831853071795862) {
              Offset0_DW.sample++;
              q = 6.28318548F - (Offset0_Y.Electricalangle - Offset0_U.Pwmangle);
              if (rtIsNaNF(q)) {
                rtb_deltafalllimit = (rtNaNF);
              } else if (rtIsInfF(q)) {
                rtb_deltafalllimit = (rtNaNF);
              } else if (q == 0.0F) {
                rtb_deltafalllimit = 0.0F;
              } else {
                rtb_deltafalllimit = fmodf(q, 6.28318548F);
                rEQ0 = (rtb_deltafalllimit == 0.0F);
                if (!rEQ0) {
                  q = fabsf(q / 6.28318548F);
                  rEQ0 = !(fabsf(q - floorf(q + 0.5F)) > 1.1920929E-7F * q);
                }

                if (rEQ0) {
                  rtb_deltafalllimit = 0.0F;
                } else if (rtb_deltafalllimit < 0.0F) {
                  rtb_deltafalllimit += 6.28318548F;
                }
              }

              Offset0_DW.errorM += rtb_deltafalllimit;
              if (Offset0_DW.sample == 3.0F) {
                /* Outport: '<Root>/error_M' */
                Offset0_Y.error_M = Offset0_DW.errorM / 3.0F;
              }
            }

            /* Outport: '<Root>/Electricalangle' incorporates:
             *  Inport: '<Root>/Pwmangle'
             */
            Offset0_Y.Electricalangle = Offset0_mod(Offset0_Y.Electricalangle);
            Offset0_DW.timer2 = 0U;
          }
        }

        if (Offset0_DW.sample >= Offset0_U.MAX_SAMPLE_ROTATION) {
          Offset0_Y.FOC_closed_loop = 1U;
        }
      } else {
        /* Outport: '<Root>/Iqref' */
        /* case IN_Rotor_Allingment: */
        Offset0_Y.Iqref = 0.0F;
        if (Offset0_Y.Idref >= Offset0_U.IDREF_MAX_LIMITT) {
          Offset0_DW.is_Coarse_offset_angle = Offset0_IN_Angle_shifting;

          /* Outport: '<Root>/Electricalangle' */
          Offset0_Y.Electricalangle = 0.0F;
          Offset0_DW.sample = 0.0F;
          Offset0_DW.error_sample = 0.0F;
          Offset0_DW.errorM = 0.0F;
        } else {
          tmp = Offset0_DW.timer1 + 1U;
          if (Offset0_DW.timer1 + 1U > 65535U) {
            tmp = 65535U;
          }

          Offset0_DW.timer1 = (uint16_t)tmp;
          if (Offset0_DW.timer1 >= Offset0_U.ALIGNEMENT_TMOO) {
            Offset0_Y.Idref += Offset0_U.AUTOTUNE_IDREF_INCREMENTT;
            Offset0_DW.timer1 = 0U;
          }
        }
      }
      break;

     case Offset0_IN_Fine_Offset_angle:
      Offset0_Fine_Offset_angle();
      break;

     default:
      /* case IN_Go_for_closedloop_FOC: */
      if (Offset0_DW.temporalCounter_i1 >= 5000) {
        Offset0_DW.is_c3_Offset0 = Offset0_IN_Fine_Offset_angle;
        Offset0_DW.sample = 0.0F;
        Offset0_DW.sample2 = 0.0F;

        /* Outport: '<Root>/RR' */
        Offset0_Y.RR = 0U;
        Offset0_DW.temporalCounter_i1 = 0U;
        Offset0_DW.is_Fine_Offset_angle = Offset0_IN_Motor_speedRpm_set;
        Offset0_DW.Repeat_CW = 0U;

        /* Outport: '<Root>/FNR' */
        Offset0_Y.FNR = 1U;
      } else {
        /* Outport: '<Root>/Offset_CW' incorporates:
         *  Outport: '<Root>/error_M'
         */
        Offset0_Y.Offset_CW = Offset0_Y.error_M;

        /* Outport: '<Root>/Offset_CCW' incorporates:
         *  Outport: '<Root>/error_M'
         */
        Offset0_Y.Offset_CCW = Offset0_Y.error_M;
      }
      break;
    }
  }

  /* End of Chart: '<S1>/Chart' */

  /* Delay: '<S4>/Delay' */
  if (Offset0_DW.icLoad) {
    Offset0_DW.Delay_DSTATE = Offset0_B.MotorRpmRef;
  }

  /* Sum: '<S4>/Difference Inputs1' incorporates:
   *  Delay: '<S4>/Delay'
   *
   * Block description for '<S4>/Difference Inputs1':
   *
   *  Add in CPU
   */
  q = Offset0_B.MotorRpmRef - Offset0_DW.Delay_DSTATE;

  /* Product: '<S4>/delta rise limit' incorporates:
   *  Inport: '<Root>/Speed_Ramp_up'
   *  SampleTimeMath: '<S4>/sample time'
   *
   * About '<S4>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_deltafalllimit = Offset0_U.Speed_Ramp_up * 0.001F;

  /* Switch: '<S6>/Switch2' incorporates:
   *  RelationalOperator: '<S6>/LowerRelop1'
   */
  if (!(q > rtb_deltafalllimit)) {
    /* Product: '<S4>/delta fall limit' incorporates:
     *  Inport: '<Root>/Speed_Ramp_down'
     *  SampleTimeMath: '<S4>/sample time'
     *
     * About '<S4>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_deltafalllimit = 0.001F * Offset0_U.Speed_Ramp_down;

    /* Switch: '<S6>/Switch' incorporates:
     *  RelationalOperator: '<S6>/UpperRelop'
     */
    if (!(q < rtb_deltafalllimit)) {
      rtb_deltafalllimit = q;
    }

    /* End of Switch: '<S6>/Switch' */
  }

  /* End of Switch: '<S6>/Switch2' */

  /* Sum: '<S4>/Difference Inputs2' incorporates:
   *  Delay: '<S4>/Delay'
   *
   * Block description for '<S4>/Difference Inputs2':
   *
   *  Add in CPU
   */
  Offset0_Y.MotorRpmRef = rtb_deltafalllimit + Offset0_DW.Delay_DSTATE;

  /* Outport: '<Root>/Offset_CW_Mech' incorporates:
   *  Inport: '<Root>/Pole_pairs'
   *  Outport: '<Root>/Offset_CW'
   *  Product: '<S1>/Divide'
   */
  Offset0_Y.Offset_CW_Mech = Offset0_Y.Offset_CW / Offset0_U.Pole_pairs;

  /* Outport: '<Root>/Offset_CCW_Mech' incorporates:
   *  Inport: '<Root>/Pole_pairs'
   *  Outport: '<Root>/Offset_CCW'
   *  Product: '<S1>/Divide1'
   */
  Offset0_Y.Offset_CCW_Mech = Offset0_Y.Offset_CCW / Offset0_U.Pole_pairs;

  /* Outport: '<Root>/initial_offset_Mech' incorporates:
   *  Inport: '<Root>/Pole_pairs'
   *  Outport: '<Root>/error_M'
   *  Product: '<S1>/Divide2'
   */
  Offset0_Y.initial_offset_Mech = Offset0_Y.error_M / Offset0_U.Pole_pairs;

  /* Outputs for Enabled SubSystem: '<S2>/Subsystem' incorporates:
   *  EnablePort: '<S5>/Enable'
   */
  if (Offset0_B.flag_C > 0) {
    Offset0_DW.Subsystem_MODE = true;

    /* SignalConversion generated from: '<S5>/error' incorporates:
     *  Outport: '<Root>/error_C'
     */
    Offset0_B.error = Offset0_Y.error_C;
  } else if (Offset0_DW.Subsystem_MODE) {
    /* Disable for SignalConversion generated from: '<S5>/error' incorporates:
     *  Outport: '<S5>/Error'
     */
    Offset0_B.error = 0.0F;
    Offset0_DW.Subsystem_MODE = false;
  }

  /* End of Outputs for SubSystem: '<S2>/Subsystem' */

  /* UnitDelay: '<S2>/Unit Delay' */
  rtb_deltafalllimit = Offset0_DW.UnitDelay_DSTATE;

  /* Sum: '<S2>/Sum' incorporates:
   *  UnitDelay: '<S2>/Unit Delay'
   */
  Offset0_DW.UnitDelay_DSTATE += Offset0_B.error;

  /* Outport: '<Root>/initial_offset' incorporates:
   *  Product: '<S2>/Divide'
   *  UnitDelay: '<S2>/Unit Delay1'
   */
  Offset0_Y.initial_offset = rtb_deltafalllimit / (float)
    Offset0_DW.UnitDelay1_DSTATE;

  /* Sum: '<S2>/Sum1' incorporates:
   *  UnitDelay: '<S2>/Unit Delay1'
   */
  Offset0_DW.UnitDelay1_DSTATE += Offset0_B.flag_C;

  /* Update for Delay: '<S4>/Delay' */
  Offset0_DW.icLoad = false;
  Offset0_DW.Delay_DSTATE = Offset0_Y.MotorRpmRef;
}

/* Model initialize function */
void Offset0_initialize(void)
{
  /* InitializeConditions for Delay: '<S4>/Delay' */
  Offset0_DW.icLoad = true;

  Offset0_U.Pole_pairs = 3.0f;
  Offset0_U.AUTO_TUNING_IDREFF = 20.0f;
  Offset0_U.ALIGNEMENT_TMOO = 20.0f;
  Offset0_U.AUTOTUNE_ANGLE_INCREMENTT = 0.006f;
  Offset0_U.AUTOTUNE_IDREF_INCREMENTT = 0.02f;
  Offset0_U.IDREF_MAX_LIMITT = 60.0f;
  Offset0_U.MAX_SAMPLE_ROTATION = 4.0f; 
  Offset0_U.NO_OF_CCW_SAMPLE = 2.0f;
  Offset0_U.NO_OF_CW_SAMPLE = 3.0f;
  Offset0_U.NO_OF_V_SAMPLES = 600.0f;
  Offset0_U.POLE_PAIRS = 1.0f;
  Offset0_U.RATED_RPM = 1000.0f;
  Offset0_U.Speed_Ramp_down = -100.0f;
  Offset0_U.Speed_Ramp_up = 500.0f;
  Offset0_U.Vd_MAX = -0.2f;
  Offset0_U.Vd_MIN = -1.0f;
  Offset0_U.WAIT_TIME = 30000.0f;


}

/* Model terminate function */
void Offset0_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
