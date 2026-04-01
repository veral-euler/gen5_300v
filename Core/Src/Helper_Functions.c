#include "Helper_Functions.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim5;
extern ADC_HandleTypeDef hadc2;

void rt_OneStep(void)
{
  static bool OverrunFlags[2] = { 0, 0 };

  static bool eventFlags[2] = { 0, 0 };/* Model has 2 rates */

  static int taskCounter[2] = { 0, 0 };

  /* Disable interrupts here */

  /* Check base rate for overrun */
  if (OverrunFlags[0]) {
    rtmSetErrorStatus(FOC_MTPA_FWC_FF_M, "Overrun");
    return;
  }

  OverrunFlags[0] = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */

  /*
   * For a bare-board target (i.e., no operating system), the
   * following code checks whether any subrate overruns,
   * and also sets the rates that need to run this time step.
   */
  if (taskCounter[1] == 0) {
    if (eventFlags[1]) {
      OverrunFlags[0] = false;
      OverrunFlags[1] = true;

      /* Sampling too fast */
      rtmSetErrorStatus(FOC_MTPA_FWC_FF_M, "Overrun");
      return;
    }

    eventFlags[1] = true;
  }

  taskCounter[1]++;
  if (taskCounter[1] == 10) {
    taskCounter[1]= 0;
  }

  /* Set model inputs associated with base rate here */

  /* Step the model for base rate */
  FOC_MTPA_FWC_FF_step0();

  /* Get model outputs here */

  /* Indicate task for base rate complete */
  OverrunFlags[0] = false;

  /* If task 1 is running, do not run any lower priority task */
  if (OverrunFlags[1]) {
    return;
  }

  /* Step the model for subrate */
  if (eventFlags[1]) {
    OverrunFlags[1] = true;

    /* Set model inputs associated with subrates here */
    /* Gathering speed feedback data and setting motor start flag */
    Speed_Sense(d.mech_angle);
    d.omega_e = d.rad_s * POLEPAIRS;
    FOC_MTPA_FWC_FF_U.ActualSpeed_mech_radsec = fabsf(d.rad_s);
    if (fabsf(d.RPM) >= MIN_RPM_FOR_MOTOR_START)
    {
      d.motor_start = 1;
    }

    /* Step the model for subrate 1 */
    FOC_MTPA_FWC_FF_step1();

    /* Get model outputs here */

    /* Indicate task complete for subrate */
    OverrunFlags[1] = false;
    eventFlags[1] = false;
  }

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

void set_Initial_angle(void)
{
  /* Calculating the startup angle and converting to TIM2 counts */
  d.Angle_From_Duty = (100.0f - d.Duty) * 0.01f * TWO_PI - HIGH_PULSE16_ERROR;
  d.Angle_From_Duty = fmodf(d.Angle_From_Duty, TWO_PI);
  d.Count_From_Duty = (uint32_t)((d.Angle_From_Duty / TWO_PI) * (TIM2_ARR + 1));

  /* Checking for PWM disconnection error */
  if (encoder_pwm_error_check() == !HAL_OK)
  {
    er.error_triggered = 1;
    er.pwm_error = 1;
    err = ENCODER_PWM_ERROR;
    cS = CONT_ERROR;

    disable_drive();

    return;
  }

  HAL_Delay(10);

  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
  cS = CURR_SENS_CALIB;
}

void Disable_tim5(void)
{
  HAL_TIM_IC_Stop_IT(&htim5, TIM_CHANNEL_1);
  HAL_TIM_IC_Stop_IT(&htim5, TIM_CHANNEL_2);
  HAL_TIM_IC_DeInit(&htim5);
  HAL_TIM_Base_MspDeInit(&htim5);
}

void power_mode_fnr_switch(void)
{
  #if THROTTLE_BASED_DIR
  d.forward_pin = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3);
  d.reverse_pin = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4);
  d.power_pin = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2);
  #endif

  #if THROTTLE_BASED_DIR
  if (d.forward_pin == GPIO_PIN_SET && d.reverse_pin == GPIO_PIN_SET)
  {
    fnr_state = NEUTRAL;
    d.speed_ref = 0.0f;
    d.torque_final = 0.0f;
    FOC_MTPA_FWC_FF_U.Drive_State = NEUTRAL;
  }
  else if (d.forward_pin == GPIO_PIN_RESET && d.reverse_pin == GPIO_PIN_SET)
  {
    fnr_state = FORWARD;
    FOC_MTPA_FWC_FF_U.Drive_State = FORWARD;
  }
  else if (d.forward_pin == GPIO_PIN_SET && d.reverse_pin == GPIO_PIN_RESET)
  {
    fnr_state = REVERSE;
    FOC_MTPA_FWC_FF_U.Drive_State = REVERSE;
  }
  #endif

  #if CAN_BASED_DIR
  if (can_d.direction == FORWARD) {
    fnr_state = FORWARD;
    FOC_MTPA_FWC_FF_U.Drive_State = FORWARD;
  } else if (can_d.direction == REVERSE) {
    fnr_state = REVERSE;
    FOC_MTPA_FWC_FF_U.Drive_State = REVERSE;
  } else if (can_d.direction == NEUTRAL) {
    d.speed_ref = 0.0f;
    FOC_MTPA_FWC_FF_U.Ref_Speed_mech_rpm = 0.0f;
    fnr_state = NEUTRAL;
    FOC_MTPA_FWC_FF_U.Drive_State = NEUTRAL;
  }

  if (can_d.power_mode == SPORTS) {
    pw_state = SPORTS;
  } else if (can_d.power_mode == ECO) {
    pw_state = ECO;
  }
  #endif

  #if THROTTLE_BASED_REF
  ThrottleMap_SetDirection(&g_throttle_cfg, fnr_state);
  #endif

  #if THROTTLE_BASED_DIR
  if (d.power_pin == GPIO_PIN_RESET) {
    pw_state = SPORTS;
  } else {
    pw_state = ECO;
  }
  #endif

  #if THROTTLE_BASED_REF
  ThrottleMap_SetDriveMode(&g_throttle_cfg, pw_state);
  #endif

  #if CAN_BASED_REF
  if (pw_state == ECO && fnr_state == FORWARD) {
    if (d.speed_ref >= ECO_MAX_SPEED) {
      d.speed_ref = ECO_MAX_SPEED;
    }
  } else if (pw_state == SPORTS && fnr_state == FORWARD) {
    if (d.speed_ref >= SPORTS_MAX_SPEED) {
      d.speed_ref = SPORTS_MAX_SPEED;
    }
  }

  if (fnr_state == REVERSE) {
    if (d.speed_ref >= REV_MAX_SPEED) {
      d.speed_ref = REV_MAX_SPEED;
    }
  }
  #endif
}

void disable_drive(void) 
{
  #if ENABLE_FAULTS
  if (cS == CONT_ERROR)
  {
    /* Checking is error is triggered and shutting off gate drivers and TIM1 */
    if (er.error_triggered)
    {
      er.drive_off = 1;

      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, TIM1_ARR_HALF);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, TIM1_ARR_HALF);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, TIM1_ARR_HALF);
      __HAL_TIM_MOE_DISABLE(&htim1);
      HAL_ADCEx_InjectedStop_IT(&hadc2);
    }

    /* Resetting FOC data structures after error trigger */
    (void)memset(&FOC_MTPA_FWC_FF_U, 0, sizeof(ExtU_FOC_MTPA_FWC_FF_T));
    (void)memset(&FOC_MTPA_FWC_FF_Y, 0, sizeof(ExtY_FOC_MTPA_FWC_FF_T));
    (void)memset(&d, 0, sizeof(data));
  }
  #endif
}