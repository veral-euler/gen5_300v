/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
DMA_HandleTypeDef hdma_adc1;

FDCAN_HandleTypeDef hfdcan2;

I2C_HandleTypeDef hi2c2;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim17;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t heart_beat_init[8] = {0x01, 0x04};
uint8_t rxMsg[8] = {0};
uint16_t injectedVal[2] = {0};
uint16_t currSensOff[2] = {0, 0};
uint16_t adc1_buffer[5] = {0};
uint16_t counter = 0;
uint32_t ia_offset = 0;
uint32_t ib_offset = 0;

/* Autotune stuct instances */
tag_AngleAutoTuneDebugParam TagAutotuneDebug;
tag_AngleAutoTuneOutputParam TagAutotuneOutput;
tag_AngleAutoTuneInputParam TagAutotuneInput;
tag_AutotuneConfig AutotuneConfig;

fnr_state_t fnr_state = NEUTRAL;
power_mode_t pw_state = ECO;
currSession cS = INIT;
errors_nums err = NO_ERROR;
errors er = {0};
can_data_t can_d = {.can_Lambda = LAMBDA, .can_Ld = LD, .can_Lq = LQ, .canFW_params.M_to_F = FW_M2F, .canFW_params.F_to_M = FW_F2M, .canFW_params.Kaw = FW_KAW, .canFW_params.Kfw = FW_KFW, .canFW_params.Rst_Factor = FW_RST_FACTOR, .canSpeed_PID.Kp = SPEED_KP, .canSpeed_PID.Ki = SPEED_KI, .canSpeed_PID.Kd = SPEED_KD, .canSpeed_PID.Back_Kaw = SPEED_PID_BACK_KAW, .canSpeed_PID.Kd_Filter = SPEED_KD_FILTER, .canSpeed_PID.Output_Up_Limit = SPEED_PID_OUT_UPL, .canSpeed_PID.Output_Low_Limit = SPEED_PID_OUT_LOWL, .canId_PID.Kp = ID_KP, .canId_PID.Ki = ID_KI, .canId_PID.Kd = ID_KD, .canId_PID.Back_Kaw = ID_PID_BACK_KAW, .canId_PID.Kd_Filter = ID_KD_FILTER, .canId_PID.Output_Up_Limit = ID_PID_OUT_UPL, .canId_PID.Output_Low_Limit = ID_PID_OUT_LOWL, .canIq_PID.Kp = IQ_KP, .canIq_PID.Ki = IQ_KI, .canIq_PID.Kd = IQ_KD, .canIq_PID.Back_Kaw = IQ_PID_BACK_KAW, .canIq_PID.Kd_Filter = IQ_KD_FILTER, .canIq_PID.Output_Up_Limit = IQ_PID_OUT_UPL, .canIq_PID.Output_Low_Limit = IQ_PID_OUT_LOWL};
data d = {.tuning_enabled = 0, .canBus_ok = 1, .Kvf = V_F_RATIO, .speed_ref = 0.0f, .start_alignment = 1, .end_alignment = 0, .Vmax_SVM = SVM_VOLTAGE_LIMIT, .pole_pair = POLEPAIRS, .Vdc = OP_VOLTAGE};

/* P4 pending flags — EEPROM write deferred out of TIM17 ISR */
static volatile uint8_t  eeprom_write_pending = 0;
static volatile uint16_t eeprom_cw_pending    = 0;
static volatile uint16_t eeprom_ccw_pending   = 0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  SCB_EnableICache();
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

/* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */
  #if EST_CYC_CNT
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CYCCNT = 0;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  #endif
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_ADC2_Init();
  MX_TIM5_Init();
  MX_TIM17_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();
  MX_FDCAN2_Init();
  MX_I2C2_Init();
  MX_TIM4_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  HAL_Delay(10);

  /* Stopping all TIM1 for safety precauiton at program start */
  HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
  HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);

  HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_3);
  HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
  HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  /* First read EEPROM for calib done flag */
  Read_EEPROM_at_init();
  HAL_Delay(10);

  #if TUNING_ENABLED
  d.tuning_enabled = 1;
  #endif

  #if !TUNING_ENABLED
  d.tuning_enabled = 0;
  cS = ANGLE_CALIB_DONE;
  #endif

  if (cS == INIT && d.tuning_enabled) {
    AD2S1210_Init();
    set_Initial_angle();
    /* Setting Auto tune algo input params */
    AutotuneConfig.f_idSetRef = AUTO_TUNING_IDREF;
    AutotuneConfig.f_IdRefIncrementValue = AUTOTUNE_IDREF_INCREMENT;
    AutotuneConfig.f_CalibElectricalAngleInc = AUTOTUNE_ANGLE_INCREMENT;
    AutotuneConfig.F_MaxVd = MAX_VD;
    AutotuneConfig.F_MinVd = MIN_VD;
    AutotuneConfig.f_Electrical360Rad = ANGLE_RAD_360;
    AutotuneConfig.u8_MOTOR_POLE_PAIRS = MOTOR_POLE_PAIRS;
    AutotuneConfig.u16_AO_Set_Time = AO_SET_TIME;
    AutotuneConfig.u16FreeRunTmo = AUTOTUNE_FREERUNCOUNT;
    AutotuneConfig.f_Autotune_RPM_Set_Ref = TUNING_CALC_RPM;
    AutotuneConfig.u16StateChangeTMO = AUTOTUNESTATE_CHANGE_TMO;
    AutotuneConfig.u16_AUTOTUN_SPEED_RAMP_TIME = AUTOTUN_SPEED_RAMP_TIME;
    AutotuneConfig.u16_AUTOTUNE_SPEED_RAMP = AUTOTUNE_SPEED_RAMP;
    AutotuneConfig.u16_MAX_ITERATION = MAX_ITERATION;
    AutotuneConfig.u16_ALIGNEMENT_TMO = ALIGNEMENT_TMO;
    AutotuneConfig.u16_AVERAGE_SAMPLE = AVERAGE_SAMPLE;
    AutotuneConfig.u16_VD_VQ_AVERAGE_COUNT = VD_VQ_AVERAGE_COUNT;
    AutotuneInit(&AutotuneConfig);
  } else if (cS == ANGLE_CALIB_DONE) {
    #if RESOLVER_ENABLED
    AD2S1210_Init();
    set_Initial_angle();
    #endif
    #if !RESOLVER_ENABLED
    set_Initial_angle();
    #endif
    Disable_tim5();
    //cS = ENC_READ;
  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  // Start encoder capture on both channels with interrupts
  if (HAL_TIM_Encoder_Start_IT(&htim2, TIM_CHANNEL_ALL) != HAL_OK)
    Error_Handler();

  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);

  HAL_ADCEx_Calibration_Start(&hadc2, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
  HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
  HAL_Delay(10);

  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc1_buffer, 5);

  /* Initializing FOC and Protections model */
  FOC_MTPA_FWC_FF_initialize();
  Open_FOC0_initialize();
  Offset0_initialize();
  Angle_to_Speed_initialize();
  #if PROTECTION_MODEL
  MCU_Protections_initialize();
  #endif
  RateLimiter_Init(&limiter, 100.0f, 600.0f, 0.0f);
  RateLimiter_Init(&torqueRate, 10.0f, 10.0f, 0.0f);
  #if OFFSET_SCHEDULER
  OffsetScheduler_Init(&g_offset_sched, d.offset_angle_mech_cw, OFFSET_HIGH_RAD, d.offset_angle_mech_ccw);
  #endif
  HAL_Delay(10);

  /*Starting FDCAN2, Queue Init and Throttle Init*/
  FDCAN_SETUP();
  CAN_Queue_Init();
  #if THROTTLE_BASED_REF
  App_Init();
  #endif

  /*Sending Heartbeat message once at init and sending PID values*/
  _fdcan_transmit_on_can(0x400, 0, heart_beat_init, 0x08);
  /* Enable LED */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_SET);

  /*Starting ADC2 Injected conversions first*/
  HAL_ADCEx_InjectedStart_IT(&hadc2);
  HAL_TIM_Base_Start_IT(&htim17);

  /*Then starting TIM1 complementary channels and trigger channel*/
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);

  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    uint32_t time_stamp_now = HAL_GetTick();

    /* P4: deferred EEPROM write (ISR set flag to avoid blocking 1kHz TIM17) */
    if (eeprom_write_pending && cS == ANGLE_CALIB_DONE)
    {
      eeprom_write_pending = 0;
      if (EEPROM_Write_Page0(eeprom_cw_pending, eeprom_ccw_pending) == HAL_OK)
        HAL_NVIC_SystemReset();
      else
      {
        er.eeprom_write_error = 1;
        err = EEPROM_WRITE_ERROR;
      }
    }

    if (cS == FOC_START)
      power_mode_fnr_switch();

    /* Gathering ADC1 values */
    ADC1_Analog_Val_Update();
    #if PROTECTION_MODEL
    /* MCU Proctections Model input update */
    Model_Params_Input();
    /* Running MCU protections model */
    MCU_Protections_step();
    /* Checking the MCU Protections Model output flags and setting error flags */
    Model_Output_Flag_Checks();
    #endif

    #if CAN_BASED_REF
    if (cS == FOC_START && FOC_MTPA_FWC_FF_U.Speed_1_Torque_0 == 1)
      FOC_MTPA_FWC_FF_U.Ref_Speed_mech_rpm = RateLimiter_Update(&limiter, d.speed_ref, ((float)time_stamp_now * 0.001f));
    else if (cS == OPEN_FOC_START)
      Open_FOC0_U.Speed_ref = RateLimiter_Update(&limiter, d.speed_ref, ((float)time_stamp_now * 0.001f));
    #endif

    #if THROTTLE_BASED_REF
    if (FOC_MTPA_FWC_FF_U.Speed_1_Torque_0 == 1 && cS == FOC_START) {
      d.speed_ref = (float)ThrottleMap_GetRPM(&g_throttle_cfg, d.thr_v_mv);
      /* Pass target_rpm into your FOC speed reference */
      FOC_MTPA_FWC_FF_U.Ref_Speed_mech_rpm = RateLimiter_Update(&limiter, d.speed_ref, ((float)time_stamp_now * 0.001f));
    } else if (FOC_MTPA_FWC_FF_U.Speed_1_Torque_0 == 0 && cS == FOC_START) {
      float max_torque = get_torque_speed_limit(d.rad_s);
      float torque_ref = ThrottleMap_GetTorque(&g_throttle_cfg, d.thr_v_mv, max_torque);
      d.torque_final = apply_torque_scaling(torque_ref, d.rad_s, pw_state, fnr_state, (float)d.Mtr_temp, (float)d.Mtc_temp, &taper_state, &derate_result);
      /* Pass target_reftrq into your FOC Torque reference */
      FOC_MTPA_FWC_FF_U.RefTrq = d.torque_final;
    }
    #endif
  }
  /* USER CODE END 3 */
}

/* USER CODE BEGIN 4 */
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  if (hadc->Instance == ADC2)
  {
    /* Reading injected values for the 2 phases */
    injectedVal[PHASE_U] = HAL_ADCEx_InjectedGetValue(hadc, ADC_INJECTED_RANK_1);
    injectedVal[PHASE_V] = HAL_ADCEx_InjectedGetValue(hadc, ADC_INJECTED_RANK_2);

    if (cS == CURR_SENS_CALIB)
    {
      /* Calibrating current sensor offsets */
      ia_offset += injectedVal[PHASE_U];
      ib_offset += injectedVal[PHASE_V];
      counter++;

      if (counter >= NO_OF_SAMPLES)
      {
        ia_offset = ia_offset / NO_OF_SAMPLES;
        ib_offset = ib_offset / NO_OF_SAMPLES;

        currSensOff[PHASE_U] = ia_offset;
        currSensOff[PHASE_V] = ib_offset;

        ia_offset = 0;
        ib_offset = 0;
        counter = 0;

        /* Setting TIM1 PWM freq to 10kHz and setting TIM2 counter reg to inital angle count */
        __HAL_TIM_SET_PRESCALER(&htim1, 2);
        __HAL_TIM_SET_AUTORELOAD(&htim1, 2499);
        __HAL_TIM_SET_COUNTER(&htim2, d.Count_From_Duty);

        /* Setting elec angle to 0 */
        d.elec_angle = 0.0f;

        #if ENABLE_FAULTS
        /* Running initial fault check */
        d.init_check = Initial_Fault_Check();

        /* Checking if inital fault check is OK and turning on the Gate drivers*/
        if (d.init_check == HAL_OK)
        {
          HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
          if ((d.start_alignment == 1 && d.end_alignment == 0) && d.tuning_enabled) {
            FOC_MTPA_FWC_FF_U.Speed_1_Torque_0 = 1.0f;
            cS = ANGLE_CALIB;
          } else if (CLOSED_FOC) {
            FOC_MTPA_FWC_FF_U.Speed_1_Torque_0 = 1.0f;
            cS = FOC_START;
          } else if (OPEN_FOC) {
            Open_FOC0_U.Theta_1_Speed_0 = 0.0f;
            cS = OPEN_FOC_START;
          }
        }
        else if (d.init_check == !HAL_OK)
        {
          HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
          cS = CONT_ERROR;
          disable_drive();
        }
        #endif

        #if DISABLE_FAULTS
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
        if (OPEN_FOC) {
          Open_FOC0_U.Theta_1_Speed_0 = 0.0f;
          cS = OPEN_FOC_START;
        } else if (CLOSED_FOC) {
          FOC_MTPA_FWC_FF_U.Speed_1_Torque_0 = 1.0f;
          cS = FOC_START;
        }
        #endif
      }
    }

    else if (cS == ANGLE_CALIB)
    {
      static uint8_t milli_counter = 0; 
      milli_counter++;

      // if(!TagAutotuneOutput.AutotuneCompleteflag){
      //   TagAutotuneInput.AutotuneFlag = ANGLE_AUTOTUNE; 
      // }
      // else{
      //   TagAutotuneInput.AutotuneFlag = NORMAL_RUN;
      // }

      if(milli_counter >= 10)
      {
        milli_counter = 0;
        Offset0_U.Pwmangle = TWO_PI - AD2S1210_ReadAngle();
        //TagAutotuneInput.f_MotorRpm = d.RPM;
        Offset0_U.Vq = FOC_MTPA_FWC_FF_Y.Vq;
        Offset0_U.Vd = FOC_MTPA_FWC_FF_Y.Vd;

        // AngleAutotuningRoutine(&TagAutotuneInput, &TagAutotuneOutput, &TagAutotuneDebug);

        Offset0_step();
      }


      if(Offset0_Y.FOC_closed_loop == 0){
          /* Updating phase current data */
          Open_FOC0_U.Phase_current[2] = (float)(injectedVal[PHASE_U] - currSensOff[PHASE_U]) * ADC_TO_CURR;
          Open_FOC0_U.Phase_current[1] = (float)(injectedVal[PHASE_V] - currSensOff[PHASE_V]) * ADC_TO_CURR;
          Open_FOC0_U.Phase_current[0] = 0.0f - Open_FOC0_U.Phase_current[1] - Open_FOC0_U.Phase_current[2];

          Open_FOC0_U.Id_ref = Offset0_Y.Idref;
          Open_FOC0_U.Iq_ref = Offset0_Y.Iqref;
          Open_FOC0_U.Theta_e_ref = Offset0_Y.Electricalangle;

          /* Running Open FOC model */
          Open_FOC0_step();

          d.Va_SVM = Open_FOC0_Y.Va;
          d.Vb_SVM = Open_FOC0_Y.Vb;
          d.Vc_SVM = Open_FOC0_Y.Vc;
      }

      else if(Offset0_Y.FOC_closed_loop == 1){
        /* Updating pahse current data */
        FOC_MTPA_FWC_FF_U.PhaseCurrent[2] = (float)(injectedVal[PHASE_U] - currSensOff[PHASE_U]) * ADC_TO_CURR;
        FOC_MTPA_FWC_FF_U.PhaseCurrent[1] = (float)(injectedVal[PHASE_V] - currSensOff[PHASE_V]) * ADC_TO_CURR;
        FOC_MTPA_FWC_FF_U.PhaseCurrent[0] = 0.0f - FOC_MTPA_FWC_FF_U.PhaseCurrent[1] - FOC_MTPA_FWC_FF_U.PhaseCurrent[2];
      
        FOC_MTPA_FWC_FF_U.Throttle_input.Throttle_Inst_Voltage = THR_MIN_VAL;
        FOC_MTPA_FWC_FF_U.Ref_Speed_mech_rpm = Offset0_Y.MotorRpmRef;

        if(Offset0_Y.FNR == Forward){
          FOC_MTPA_FWC_FF_U.Drive_State = Forward;
          d.ATA_Offset = Offset0_Y.Offset_CW;
        }
        else if(Offset0_Y.FNR == Reverse){
          FOC_MTPA_FWC_FF_U.Drive_State = Reverse;
          d.ATA_Offset = Offset0_Y.Offset_CCW;
        }
        else if(Offset0_Y.FNR == Neutral){
          FOC_MTPA_FWC_FF_U.Drive_State = Neutral;
        }
        else{
          FOC_MTPA_FWC_FF_U.Drive_State = Throttle_Error;
        }

        d.encoder_count = __HAL_TIM_GET_COUNTER(&htim2);
        d.mech_angle = ((float)d.encoder_count * COUNTS_TO_RADS);
        d.mech_angle = fmodf(d.mech_angle, TWO_PI);

        /* Updating elec angle data */
        d.elec_angle = (d.mech_angle * POLEPAIRS);
        d.elec_angle = fmodf(d.elec_angle - d.ATA_Offset, TWO_PI);
        if (d.elec_angle < 0.0f) d.elec_angle += TWO_PI;
        FOC_MTPA_FWC_FF_U.angle = d.elec_angle;

        /* Running the FOC model */
        rt_OneStep();

        /* SVM and PWM update */
        d.Va_SVM = FOC_MTPA_FWC_FF_Y.Va;
        d.Vb_SVM = FOC_MTPA_FWC_FF_Y.Vb;
        d.Vc_SVM = FOC_MTPA_FWC_FF_Y.Vc;
      }

      if (Offset0_Y.AutotuneCompleteflag == true)
      {
        d.start_alignment = 0;
        d.end_alignment = 1;
        d.offset_angle_mech_cw = TagAutotuneOutput.f_Offset_CW;
        d.offset_angle_mech_ccw = TagAutotuneOutput.f_Offset_CCW;
        cS = ANGLE_OFFSET_STORE;
      }

      if (d.Va_SVM > d.Vmax_SVM)
      {
        d.Va_SVM = d.Vmax_SVM;
      }
      else if (d.Va_SVM < -d.Vmax_SVM)
      {
        d.Va_SVM = -d.Vmax_SVM;
      }

      if (d.Vb_SVM > d.Vmax_SVM)
      {
        d.Vb_SVM = d.Vmax_SVM;
      }
      else if (d.Vb_SVM < -d.Vmax_SVM)
      {
        d.Vb_SVM = -d.Vmax_SVM;
      }

      if (d.Vc_SVM > d.Vmax_SVM)
      {
        d.Vc_SVM = d.Vmax_SVM;
      }
      else if (d.Vc_SVM < -d.Vmax_SVM)
      {
        d.Vc_SVM = -d.Vmax_SVM;
      }

      d.pwm_a = (uint16_t)((d.Va_SVM / d.Vmax_SVM) * TIM1_ARR_HALF + TIM1_ARR_HALF);
      d.pwm_b = (uint16_t)((d.Vb_SVM / d.Vmax_SVM) * TIM1_ARR_HALF + TIM1_ARR_HALF);
      d.pwm_c = (uint16_t)((d.Vc_SVM / d.Vmax_SVM) * TIM1_ARR_HALF + TIM1_ARR_HALF);

      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, d.pwm_a);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, d.pwm_b);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, d.pwm_c);
    }

    else if (cS == FOC_START)
    {
      #if EST_CYC_CNT
      /* Current count for time estimation */
      uint32_t start = DWT->CYCCNT;
      #endif
      /* Updating phase current data */
	  FOC_MTPA_FWC_FF_U.PhaseCurrent[2] = (float)(injectedVal[PHASE_U] - currSensOff[PHASE_U]) * ADC_TO_CURR;
      FOC_MTPA_FWC_FF_U.PhaseCurrent[1] = (float)(injectedVal[PHASE_V] - currSensOff[PHASE_V]) * ADC_TO_CURR;
      FOC_MTPA_FWC_FF_U.PhaseCurrent[0] = 0.0f - FOC_MTPA_FWC_FF_U.PhaseCurrent[1] - FOC_MTPA_FWC_FF_U.PhaseCurrent[2];

      #if !RESOLVER_ENABLED
      /* Updating angle data */
      d.encoder_count = __HAL_TIM_GET_COUNTER(&htim2);
      if (FOC_MTPA_FWC_FF_Y.Throttle_State == (ThrottleState)FORWARD)
        d.mech_angle = ((float)d.encoder_count * COUNTS_TO_RADS) - d.offset_angle_mech_cw;
      else if (FOC_MTPA_FWC_FF_Y.Throttle_State == (ThrottleState)REVERSE)
        d.mech_angle = ((float)d.encoder_count * COUNTS_TO_RADS) - d.offset_angle_mech_ccw;
      else if (FOC_MTPA_FWC_FF_Y.Throttle_State == (ThrottleState)NEUTRAL)
        d.mech_angle = ((float)d.encoder_count * COUNTS_TO_RADS) - d.offset_angle_mech_avg;
      d.mech_angle = fmodf(d.mech_angle, TWO_PI);
      d.elec_angle = (d.mech_angle * POLEPAIRS);
      d.elec_angle = fmodf(d.elec_angle, TWO_PI);
      #endif

      #if RESOLVER_ENABLED
      /* Updating mech angle data */
      d.encoder_count = __HAL_TIM_GET_COUNTER(&htim2);
      d.mech_angle = ((float)d.encoder_count * COUNTS_TO_RADS);
      d.mech_angle = fmodf(d.mech_angle, TWO_PI);
      d.elec_angle = (d.mech_angle * POLEPAIRS);
      d.elec_angle = fmodf(d.elec_angle - 4.24f, TWO_PI);
      if (d.elec_angle < 0.0f) d.elec_angle += TWO_PI;
      d.elec_angle_resolver = TWO_PI - AD2S1210_ReadAngle();
      d.elec_angle_resolver = fmodf(d.elec_angle_resolver, TWO_PI);
      #endif

      #if OFFSET_SCHEDULER
      /* Updating mech angle data */
      d.encoder_count = __HAL_TIM_GET_COUNTER(&htim2);
      d.mech_angle = ((float)d.encoder_count * COUNTS_TO_RADS);
      d.mech_angle = fmodf(d.mech_angle, TWO_PI);

      /* Updating elec angle data */
      OffsetScheduler_Update(&g_offset_sched, d.irms, fnr_state, 0.0001f);
      d.elec_angle = OffsetScheduler_GetTheta(&g_offset_sched, d.mech_angle, d.omega_e, POLEPAIRS);
      d.elec_angle = fmodf(d.elec_angle, TWO_PI);
      #endif

      #if RESOLVER_ENABLED
      FOC_MTPA_FWC_FF_U.angle = d.elec_angle; // Using resolver angle for FOC
      #endif

      #if !RESOLVER_ENABLED
      FOC_MTPA_FWC_FF_U.MtrElcPos = d.elec_angle; // Using encoder angle for FOC
      #endif 

      /* Running the FOC model */
      rt_OneStep();

      /* SVM and PWM update */
      d.Va_SVM = FOC_MTPA_FWC_FF_Y.Va;
      d.Vb_SVM = FOC_MTPA_FWC_FF_Y.Vb;
      d.Vc_SVM = FOC_MTPA_FWC_FF_Y.Vc;

      if (d.Va_SVM > d.Vmax_SVM)
      {
        d.Va_SVM = d.Vmax_SVM;
      }
      else if (d.Va_SVM < -d.Vmax_SVM)
      {
        d.Va_SVM = -d.Vmax_SVM;
      }

      if (d.Vb_SVM > d.Vmax_SVM)
      {
        d.Vb_SVM = d.Vmax_SVM;
      }
      else if (d.Vb_SVM < -d.Vmax_SVM)
      {
        d.Vb_SVM = -d.Vmax_SVM;
      }

      if (d.Vc_SVM > d.Vmax_SVM)
      {
        d.Vc_SVM = d.Vmax_SVM;
      }
      else if (d.Vc_SVM < -d.Vmax_SVM)
      {
        d.Vc_SVM = -d.Vmax_SVM;
      }

      d.pwm_a = (uint16_t)((d.Va_SVM / d.Vmax_SVM) * TIM1_ARR_HALF + TIM1_ARR_HALF);
      d.pwm_b = (uint16_t)((d.Vb_SVM / d.Vmax_SVM) * TIM1_ARR_HALF + TIM1_ARR_HALF);
      d.pwm_c = (uint16_t)((d.Vc_SVM / d.Vmax_SVM) * TIM1_ARR_HALF + TIM1_ARR_HALF);

      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, d.pwm_a);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, d.pwm_b);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, d.pwm_c);

      #if EST_CYC_CNT
      /* Finally calculating the total time taken */
      uint32_t end = DWT->CYCCNT;
      d.cycles = end - start;
      #endif
    }

    else if (OPEN_FOC_START) 
    {
      Open_FOC0_U.Phase_current[2] = (float)(injectedVal[PHASE_U] - currSensOff[PHASE_U]) * ADC_TO_CURR;
      Open_FOC0_U.Phase_current[1] = (float)(injectedVal[PHASE_V] - currSensOff[PHASE_V]) * ADC_TO_CURR;
      Open_FOC0_U.Phase_current[0] = 0.0f - Open_FOC0_U.Phase_current[1] - Open_FOC0_U.Phase_current[2];

      /* Getting angle from resolver */
      d.elec_angle_resolver = TWO_PI - AD2S1210_ReadAngle();
      d.elec_angle_resolver = fmodf(d.elec_angle_resolver, TWO_PI);

      /* Updating mech angle data */
      d.encoder_count = __HAL_TIM_GET_COUNTER(&htim2);
      d.mech_angle = ((float)d.encoder_count * COUNTS_TO_RADS);
      d.mech_angle = fmodf(d.mech_angle, TWO_PI);

      Open_FOC0_step();

      d.Va_SVM = Open_FOC0_Y.Va;
      d.Vb_SVM = Open_FOC0_Y.Vb;
      d.Vc_SVM = Open_FOC0_Y.Vc;

      if (d.Va_SVM > d.Vmax_SVM)
      {
        d.Va_SVM = d.Vmax_SVM;
      }
      else if (d.Va_SVM < -d.Vmax_SVM)
      {
        d.Va_SVM = -d.Vmax_SVM;
      }

      if (d.Vb_SVM > d.Vmax_SVM)
      {
        d.Vb_SVM = d.Vmax_SVM;
      }
      else if (d.Vb_SVM < -d.Vmax_SVM)
      {
        d.Vb_SVM = -d.Vmax_SVM;
      }

      if (d.Vc_SVM > d.Vmax_SVM)
      {
        d.Vc_SVM = d.Vmax_SVM;
      }
      else if (d.Vc_SVM < -d.Vmax_SVM)
      {
        d.Vc_SVM = -d.Vmax_SVM;
      }

      d.pwm_a = (uint16_t)((d.Va_SVM / d.Vmax_SVM) * TIM1_ARR_HALF + TIM1_ARR_HALF);
      d.pwm_b = (uint16_t)((d.Vb_SVM / d.Vmax_SVM) * TIM1_ARR_HALF + TIM1_ARR_HALF);
      d.pwm_c = (uint16_t)((d.Vc_SVM / d.Vmax_SVM) * TIM1_ARR_HALF + TIM1_ARR_HALF);

      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, d.pwm_a);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, d.pwm_b);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, d.pwm_c);
    }
    
    else if (cS == ENC_READ)
    {
      d.encoder_count = __HAL_TIM_GET_COUNTER(&htim2);
    }
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM4)
  {
    HAL_TIM_Base_Stop_IT(&htim4);
    #if VH_CAN_ID
    Send_on_CAN_7A1();
    Send_on_CAN_7A2();
    Send_on_CAN_7A3();
    #endif
  }

  if (htim->Instance == TIM17)
  {
    /* Time counter for CAN transmission */
    static uint16_t can_counter = 500;
    can_counter++;

    #if ENABLE_FAULTS
    if (cS == FOC_START || cS == ANGLE_CALIB || cS == OPEN_FOC_START) 
    {
      /* Temperature and Encoder disconnection errors */
      Sensor_Disconnection_Check();
      /* Limit Error Checks */
      Error_Check();
    }
    #endif

    if (cS == ANGLE_OFFSET_STORE)
    {
      /* P4: set flag only — blocking I2C write deferred to main loop */
      eeprom_cw_pending  = (uint16_t)(d.offset_angle_mech_cw  * 100.0f);
      eeprom_ccw_pending = (uint16_t)(d.offset_angle_mech_ccw * 100.0f);
      d.offset_angle_mech_avg = (eeprom_ccw_pending + eeprom_cw_pending) / 2.0f;
      eeprom_write_pending = 1;
      cS = ANGLE_CALIB_DONE;  /* Prevent re-entry; main loop performs the write */
    }

    if (cS == RESET_STATE) 
    {
      /* Turn off drive completely */
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, TIM1_ARR_HALF);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, TIM1_ARR_HALF);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, TIM1_ARR_HALF);
      __HAL_TIM_MOE_DISABLE(&htim1);

      /* Stopping ADC injected interrupt completely */
      HAL_ADCEx_InjectedStop_IT(&hadc2);

      /* Reset FOC Model data structs */
      (void)memset(&FOC_MTPA_FWC_FF_U, 0, sizeof(ExtU_FOC_MTPA_FWC_FF_T));
      (void)memset(&FOC_MTPA_FWC_FF_Y, 0, sizeof(ExtY_FOC_MTPA_FWC_FF_T));
      
      /* Calling NVIC Reset to reset the system */
      HAL_NVIC_SystemReset();
    }

    /* Queue messages every 500ms */
    if (can_counter >= CAN_BUS_CYCLE)
    {
      can_counter = 0;

      d.canBus_ok = 1;

      /* Check and recover from BUS OFF before queuing */
      FDCAN_ProtocolStatusTypeDef psr;
      HAL_FDCAN_GetProtocolStatus(&hfdcan2, &psr);

      if (psr.BusOff)
      {
        HAL_FDCAN_Stop(&hfdcan2);
        CAN_Queue_Init();           // flush stale queue
        HAL_FDCAN_Start(&hfdcan2);  // re-enters error active after 128×11 recessive bits
        d.canBus_ok = 0;
      }

      if (d.canBus_ok)
      {
        // Only queue - don't process here
        #if DEBUG_CAN_ID
        Send_Data_On_CAN_401();
        Send_Data_On_CAN_402();
        Send_Data_On_CAN_403();
        Send_Data_On_CAN_404();
        Send_Data_On_CAN_405();
        Send_Data_On_CAN_406();
        Send_Data_On_CAN_407();
        Send_Data_On_CAN_408();
        Send_Data_On_CAN_409();
        /* Sending Firmware Ver and Config Ver */
        Send_Data_On_CAN_410();
        #endif

        #if VH_CAN_ID
        Send_on_CAN_705(d.Mtr_temp, d.Mtc_temp);
        #if HLP
        Send_on_CAN_706(d.Vdc, fabsf(d.RPM * RPM_TO_KMPH_HLP), er.error_c1);
        #endif
        #if HI_CITY
        Send_on_CAN_706(d.Vdc, fabsf(d.RPM * RPM_TO_KMPH_HI_CITY), er.error_c1);
        #endif
        #if HI_RANGE
        Send_on_CAN_706(d.Vdc, fabsf(d.RPM * RPM_TO_KMPH_HI_RANGE), er.error_c1);
        #endif
        Send_on_CAN_708(er.error_c2, er.error_c3);
        Send_on_CAN_709(0);
        Send_on_CAN_710(d.throttle_percent, d.throttle_v);
        Send_on_CAN_715(fabsf(d.RPM), d.Vdc, d.Aux_dc);
        Send_on_CAN_716(d.vrms, d.irms);
        Send_on_CAN_717(fabsf(d.RPM));
        Send_on_CAN_724(FOC_MTPA_FWC_FF_Y.T_gen);
        Send_on_CAN_726();
        Schedule_7Ax_Transmission();
        #endif
      }
    }
  }
}

/* FDCAN Rx Callback */
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
  HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxMessageBuf, rxMsg);

  #if DEBUG_CAN_ID
  if (RxMessageBuf.Identifier == 0x102) {
    d.speed_ref = (float)((rxMsg[1] << 8) | rxMsg[0]);
  }

  else if (RxMessageBuf.Identifier == 0x103) {
    can_d.can_Lambda = (float)((rxMsg[1] << 8) | rxMsg[0]) * 1.0E-5f;
    can_d.can_Ld = (float)((rxMsg[3] << 8) | rxMsg[2]) * 1.0E-8f;
    can_d.can_Lq = (float)((rxMsg[5] << 8) | rxMsg[4]) * 1.0E-7f;

    /* Setting motor params from CAN */
    FOC_MTPA_FWC_FF_U.Motor_Parameters.Lambda = can_d.can_Lambda;
    FOC_MTPA_FWC_FF_U.Motor_Parameters.Ld = can_d.can_Ld;
    FOC_MTPA_FWC_FF_U.Motor_Parameters.Lq = can_d.can_Lq;
  }

  else if (RxMessageBuf.Identifier == 0x104) {
    can_d.canFW_params.Kfw = (float)((rxMsg[1] << 8) | rxMsg[0]) * 1.0E-3f;
    can_d.canFW_params.Kaw = (float)((rxMsg[3] << 8) | rxMsg[2]) * 1.0E-3f;
  }

  else if (RxMessageBuf.Identifier == 0x105) {
    can_d.canSpeed_PID.Kp = (float)((rxMsg[1] << 8) | rxMsg[0]) * 1.0E-2f;
    can_d.canSpeed_PID.Ki = (float)((rxMsg[3] << 8) | rxMsg[2]) * 1.0E-2f;
    can_d.canSpeed_PID.Kd = (float)((rxMsg[5] << 8) | rxMsg[4]) * 1.0E-5f;

    /* Setting Speed PID params on CAN */
    FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA = can_d.canSpeed_PID.Kp;
    FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Ki_speed_PID_MTPA = can_d.canSpeed_PID.Ki;
    FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA = can_d.canSpeed_PID.Kd;
  }

  else if (RxMessageBuf.Identifier == 0x106) {
    can_d.canId_PID.Kp = (float)((rxMsg[1] << 8) | rxMsg[0]) * 1.0E-2f;
    can_d.canId_PID.Ki = (float)((rxMsg[3] << 8) | rxMsg[2]) * 1.0E-2f;
    can_d.canId_PID.Kd = (float)((rxMsg[5] << 8) | rxMsg[4]) * 1.0E-5f;

    /* Setting ID PID params on CAN */
    FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA = can_d.canId_PID.Kp;
    FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Ki_flux_PID_MTPA = can_d.canId_PID.Ki;
    FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Kd_flux_PID_MTPA = can_d.canId_PID.Kd;
  }

  else if (RxMessageBuf.Identifier == 0x107) {
    can_d.canIq_PID.Kp = (float)((rxMsg[1] << 8) | rxMsg[0]) * 1.0E-2f;
    can_d.canIq_PID.Ki = (float)((rxMsg[3] << 8) | rxMsg[2]) * 1.0E-2f;
    can_d.canIq_PID.Kd = (float)((rxMsg[5] << 8) | rxMsg[4]) * 1.0E-5f;

    /* Setting IQ PID params on CAN */
    FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA = can_d.canIq_PID.Kp;
    FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Ki_torque_PID_MTPA = can_d.canIq_PID.Ki;
    FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA = can_d.canIq_PID.Kd;
  }

  else if (RxMessageBuf.Identifier == 0x108) {
    can_d.direction = rxMsg[0];
  }
  else if (RxMessageBuf.Identifier == 0x109) {
    can_d.power_mode = rxMsg[0];
  }

  #if CAN_BASED_THRV
  else if (RxMessageBuf.Identifier == 0x110) {
    can_d.can_instV = (float)((rxMsg[1] << 8) | rxMsg[0]);
    can_d.can_instV *= 0.001f;

    /* Setting FOC Model thr voltage on CAN Rx */
    FOC_MTPA_FWC_FF_U.Throttle_input.Throttle_Inst_Voltage = can_d.can_instV;
  }
  #endif

  else if (RxMessageBuf.Identifier == 0x111) {
    can_d.reset_flag = rxMsg[0];
    
    if (can_d.reset_flag == (uint8_t)1 && fabsf(d.RPM) <= 10.0f) {
      /* Setting fnr state to neutral and making speed ref to 0 */
      d.speed_ref = FOC_MTPA_FWC_FF_U.Ref_Speed_mech_rpm = 0.0f;
      fnr_state = NEUTRAL;
      pw_state = ECO;
      cS = RESET_STATE;
    }
  }
  #endif
}

/* FDCAN TX Complete Callback - automatically sends next message */
void HAL_FDCAN_TxBufferCompleteCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes)
{
  if (hfdcan->Instance == FDCAN2)
  {
    // Transmission complete, send next message from queue
    CAN_Queue_Process();
  }
}

// Callback
void HAL_FDCAN_ErrorStatusCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t ErrorStatusITs)
{
  if (hfdcan->Instance == FDCAN2)
  {
    if (ErrorStatusITs & FDCAN_IT_BUS_OFF)
    {
      HAL_FDCAN_Stop(&hfdcan2);
      CAN_Queue_Init();
      HAL_FDCAN_Start(&hfdcan2);
    }
  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == GPIO_PIN_7)
  {
    d.z_pulse ^= 1;
    d.z_count++;

    //d.elec_angle = 0.0f; // Resetting angle on Z pulse, can be changed to an offset if needed

    if (d.z_count > 4)
      d.z_count = 0;

    /* Stopping uint32_t overflow */
    if (d.z_count >= UINT32_MAX)
    {
      d.z_count = 0;
    }

    /* Not Resetting mech angle and TIM2 reg on every z index pulse, only getting the TIM2 count */
    if (cS == FOC_START)
    {
      /* Getting TIM2 count at Z trig */
      d.count_at_z = __HAL_TIM_GET_COUNTER(&htim2);
      //			d.mech_angle = 0.0f;
      //			__HAL_TIM_SET_COUNTER(&htim2, 0);
    }

    /* Storing the prev Z count */
    d.prev_z_count = d.curr_z_count;
  }
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM5)
  {
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) // If the interrupt is triggered by channel 1
    {
      /* Using TIM5 to get the initial angle on startup from the encoder PWM duty */
      // Read the IC value
      d.ICvalue = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

      if (d.ICvalue != 0)
      {
        // calculate the Duty Cycle
        d.Duty = (HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2) * 100.0f) / d.ICvalue;

        d.Frequency = (float)HAL_RCC_GetSysClockFreq() / (d.ICvalue * (TIM5_PSC + 1));

        d.abs_Angle_pwm = (100.0f - d.Duty) * 0.01f * TWO_PI - HIGH_PULSE16_ERROR;
        d.abs_Angle_pwm = fmodf(d.abs_Angle_pwm, TWO_PI);
      }
    }
  }
}

void delay_us(uint32_t us)
{
  SysTick->VAL = 0;
  while(us--) {
    while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
