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

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim17;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM1_Init(void);
static void MX_ADC2_Init(void);
static void MX_TIM5_Init(void);
static void MX_TIM17_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM2_Init(void);
static void MX_FDCAN2_Init(void);
static void MX_I2C2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t heart_beat_init[8] = {0x01,0x00};
uint16_t injectedVal[2] = {0};
uint16_t currSensOff[2] = {0.0f};
uint16_t adc1_buffer[5] = {0};
uint16_t counter = 0;
uint32_t ia_offset = 0;
uint32_t ib_offset = 0;

fnr_state_t fnr_state = NEUTRAL;
currSens cS = ANGLE_CALIB_DONE;
errors_nums err = NO_ERROR;
errors er = {0};
data d = {.Kvf = V_F_RATIO, .speed_ref = 0.0f, .freq = 0.0f, .t_req = 0.0f, .start_alignment = 1, .end_alignment = 0, .Vpp = 0.0f, .Vmax_SVM = SVM_VOLTAGE_LIMIT, .pole_pair = POLEPAIRS, .Vdc = OP_VOLTAGE};
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  /* USER CODE BEGIN 2 */
  HAL_Delay(100);

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
  Read_EEPROM_at_init();

  if (cS == INIT) {
    cS = ANGLE_CALIB;
    Motor_Alignment_Routine();
  } else if (cS == ANGLE_CALIB_DONE) {
    set_Initial_angle();
  }
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
  // Start encoder capture on both channels with interrupts
  if (HAL_TIM_Encoder_Start_IT(&htim2, TIM_CHANNEL_ALL) != HAL_OK) Error_Handler();

  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);

  HAL_ADCEx_Calibration_Start(&hadc2, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
  HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
  HAL_Delay(1000);

  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc1_buffer, 5);

  /* Initializing FOC and Protections model */
  FOC_LivGguard_initialize();
  MCU_Protections_initialize();
  RateLimiter_Init(&limiter, 50.0f, 100.0f, 0.0f);
  HAL_Delay(100);

  /*Starting FDCAN2 and Queue Init*/
  FDCAN_SETUP();
  CAN_Queue_Init();

  /*Sending Heartbeat message once at init*/
  _fdcan_transmit_on_can(0x400, 0, heart_beat_init, 0x08);

  /*Starting ADC2 Injected conversions first*/
  HAL_ADCEx_InjectedStart_IT(&hadc2);

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
    
    d.forward_pin = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3);
    d.reverse_pin = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4);

    if (d.forward_pin == GPIO_PIN_SET && d.reverse_pin == GPIO_PIN_SET) {
      fnr_state = NEUTRAL;
      d.speed_ref = 0.0f;
      FOC_LivGguard_U.Ref_Speed_mech_rpm = 0.0f;
    } else if (d.forward_pin == GPIO_PIN_RESET && d.reverse_pin == GPIO_PIN_SET) {
      fnr_state = FORWARD;
    } else if (d.forward_pin == GPIO_PIN_SET && d.reverse_pin == GPIO_PIN_RESET) {
      fnr_state = REVERSE;
    }

    /* Gathering MTR Temp, CNT Temp, VDC and AUX DC in while loop */
    d.Mtc_temp = NTC_Read(adc1_buffer[CONTRL_TEMP], MTC_NTC_R25);
    d.mtc_analog_val = adc1_buffer[CONTRL_TEMP];
    d.Mtr_temp = NTC_Read(adc1_buffer[MOTOR_TEMP], MTR_NTC_R25);
    d.mtr_analog_val = adc1_buffer[MOTOR_TEMP];
    d.Vdc = (float)adc1_buffer[BUS_DC] * BUS_VDC_SCALE;
    d.Aux_dc = (float)adc1_buffer[AUX_DC] * AUX_VDC_SCALE;

    FOC_LivGguard_U.Ref_Speed_mech_rpm = RateLimiter_Update(&limiter, d.speed_ref, ((float)time_stamp_now * 0.001f));
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSI);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 12;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 4096;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInitStruct.PLL2.PLL2M = 4;
  PeriphClkInitStruct.PLL2.PLL2N = 9;
  PeriphClkInitStruct.PLL2.PLL2P = 4;
  PeriphClkInitStruct.PLL2.PLL2Q = 2;
  PeriphClkInitStruct.PLL2.PLL2R = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_3;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOMEDIUM;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 3072;
  PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_16B;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.NbrOfConversion = 5;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DMA_CIRCULAR;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_64CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSignedSaturation = DISABLE;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.SamplingTime = ADC_SAMPLETIME_32CYCLES_5;
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_17;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  sConfig.SamplingTime = ADC_SAMPLETIME_16CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = ADC_REGULAR_RANK_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC2_Init(void)
{

  /* USER CODE BEGIN ADC2_Init 0 */

  /* USER CODE END ADC2_Init 0 */

  ADC_InjectionConfTypeDef sConfigInjected = {0};

  /* USER CODE BEGIN ADC2_Init 1 */

  /* USER CODE END ADC2_Init 1 */

  /** Common config
  */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV4;
  hadc2.Init.Resolution = ADC_RESOLUTION_16B;
  hadc2.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc2.Init.LowPowerAutoWait = DISABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
  hadc2.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc2.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  hadc2.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Disable Injected Queue
  */
  HAL_ADCEx_DisableInjectedQueue(&hadc2);

  /** Configure Injected Channel
  */
  sConfigInjected.InjectedChannel = ADC_CHANNEL_3;
  sConfigInjected.InjectedRank = ADC_INJECTED_RANK_1;
  sConfigInjected.InjectedSamplingTime = ADC_SAMPLETIME_64CYCLES_5;
  sConfigInjected.InjectedSingleDiff = ADC_SINGLE_ENDED;
  sConfigInjected.InjectedOffsetNumber = ADC_OFFSET_NONE;
  sConfigInjected.InjectedOffset = 0;
  sConfigInjected.InjectedOffsetSignedSaturation = DISABLE;
  sConfigInjected.InjectedNbrOfConversion = 2;
  sConfigInjected.InjectedDiscontinuousConvMode = DISABLE;
  sConfigInjected.AutoInjectedConv = DISABLE;
  sConfigInjected.QueueInjectedContext = DISABLE;
  sConfigInjected.ExternalTrigInjecConv = ADC_EXTERNALTRIGINJEC_T1_TRGO2;
  sConfigInjected.ExternalTrigInjecConvEdge = ADC_EXTERNALTRIGINJECCONV_EDGE_RISING;
  sConfigInjected.InjecOversamplingMode = DISABLE;
  if (HAL_ADCEx_InjectedConfigChannel(&hadc2, &sConfigInjected) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Injected Channel
  */
  sConfigInjected.InjectedChannel = ADC_CHANNEL_19;
  sConfigInjected.InjectedRank = ADC_INJECTED_RANK_2;
  if (HAL_ADCEx_InjectedConfigChannel(&hadc2, &sConfigInjected) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC2_Init 2 */

  /* USER CODE END ADC2_Init 2 */

}

/**
  * @brief FDCAN2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_FDCAN2_Init(void)
{

  /* USER CODE BEGIN FDCAN2_Init 0 */

  /* USER CODE END FDCAN2_Init 0 */

  /* USER CODE BEGIN FDCAN2_Init 1 */

  /* USER CODE END FDCAN2_Init 1 */
  hfdcan2.Instance = FDCAN2;
  hfdcan2.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
  hfdcan2.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan2.Init.AutoRetransmission = ENABLE;
  hfdcan2.Init.TransmitPause = DISABLE;
  hfdcan2.Init.ProtocolException = DISABLE;
  hfdcan2.Init.NominalPrescaler = 10;
  hfdcan2.Init.NominalSyncJumpWidth = 1;
  hfdcan2.Init.NominalTimeSeg1 = 16;
  hfdcan2.Init.NominalTimeSeg2 = 3;
  hfdcan2.Init.DataPrescaler = 10;
  hfdcan2.Init.DataSyncJumpWidth = 1;
  hfdcan2.Init.DataTimeSeg1 = 16;
  hfdcan2.Init.DataTimeSeg2 = 3;
  hfdcan2.Init.MessageRAMOffset = 0;
  hfdcan2.Init.StdFiltersNbr = 8;
  hfdcan2.Init.ExtFiltersNbr = 0;
  hfdcan2.Init.RxFifo0ElmtsNbr = 6;
  hfdcan2.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan2.Init.RxFifo1ElmtsNbr = 6;
  hfdcan2.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan2.Init.RxBuffersNbr = 6;
  hfdcan2.Init.RxBufferSize = FDCAN_DATA_BYTES_8;
  hfdcan2.Init.TxEventsNbr = 0;
  hfdcan2.Init.TxBuffersNbr = 8;
  hfdcan2.Init.TxFifoQueueElmtsNbr = 8;
  hfdcan2.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  hfdcan2.Init.TxElmtSize = FDCAN_DATA_BYTES_8;
  if (HAL_FDCAN_Init(&hfdcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN2_Init 2 */

  /* USER CODE END FDCAN2_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x10C0ECFF;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = TIM1_PSC;
  htim1.Init.CounterMode = TIM_COUNTERMODE_CENTERALIGNED1;
  htim1.Init.Period = TIM1_ARR;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_OC4REF;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_SET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.Pulse = 1250;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = TIM1_DEAD_TIME;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = TIM2_ARR;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 10;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 10;
  if (HAL_TIM_Encoder_Init(&htim2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = TIM5_PSC;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = TIM5_ARR;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
  sSlaveConfig.InputTrigger = TIM_TS_TI1FP1;
  sSlaveConfig.TriggerPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sSlaveConfig.TriggerPrescaler = TIM_ICPSC_DIV1;
  sSlaveConfig.TriggerFilter = 10;
  if (HAL_TIM_SlaveConfigSynchro(&htim5, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 10;
  if (HAL_TIM_IC_ConfigChannel(&htim5, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim5, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */
  // Start input capture on both channels with interrupts
  if (HAL_TIM_IC_Start_IT(&htim5, TIM_CHANNEL_1) != HAL_OK) Error_Handler();
  if (HAL_TIM_IC_Start_IT(&htim5, TIM_CHANNEL_2) != HAL_OK) Error_Handler();
  /* USER CODE END TIM5_Init 2 */

}

/**
  * @brief TIM17 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM17_Init(void)
{

  /* USER CODE BEGIN TIM17_Init 0 */

  /* USER CODE END TIM17_Init 0 */

  /* USER CODE BEGIN TIM17_Init 1 */

  /* USER CODE END TIM17_Init 1 */
  htim17.Instance = TIM17;
  htim17.Init.Prescaler = TIM17_PSC;
  htim17.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim17.Init.Period = TIM17_ARR;
  htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim17.Init.RepetitionCounter = 0;
  htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim17) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM17_Init 2 */

  /* USER CODE END TIM17_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);

  /*Configure GPIO pin : PE7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PD10 PD11 PD12 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PD3 PD4 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	if(hadc->Instance==ADC2)
	{
    /* Reading injected values for the 2 phases */
		injectedVal[PHASE_U] = HAL_ADCEx_InjectedGetValue(hadc, ADC_INJECTED_RANK_1);
		injectedVal[PHASE_V] = HAL_ADCEx_InjectedGetValue(hadc, ADC_INJECTED_RANK_2);

		if (cS == CURR_SENS_CALIB) {
      /* Calibrating current sensor offsets */
			ia_offset += injectedVal[PHASE_U];
			ib_offset += injectedVal[PHASE_V];
			counter++;

			if (counter >= NO_OF_SAMPLES) {
				ia_offset = ia_offset / NO_OF_SAMPLES;
				ib_offset = ib_offset / NO_OF_SAMPLES;

				currSensOff[PHASE_U] = ia_offset;
				currSensOff[PHASE_V] = ib_offset;

				ia_offset = 0;
				ib_offset = 0;
				counter = 0;

        /* Setting TIM1 PWM freq to 10kHz and setting TIM2 counter reg to inital angle count */
				__HAL_TIM_SET_PRESCALER(&htim1, 1);
				__HAL_TIM_SET_AUTORELOAD(&htim1, 2499);
				__HAL_TIM_SET_COUNTER(&htim2, d.Count_From_Duty);

        /* Setting elec angle to 0 */
				d.elec_angle = d.elec_angle_120 = d.elec_angle_240 = 0.0f;

        /* Running initial fault check */
				d.init_check = Initial_Fault_Check();

        /* Checking if inital fault check is OK and turning on the Gate drivers*/
				if (d.init_check == HAL_OK) {
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
					HAL_TIM_Base_Start_IT(&htim17);
          d.speed_ref = SPEED_REF_RPM_MAX;
					cS = FOC_START;
				} else if (d.init_check == !HAL_OK) {
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
					HAL_TIM_Base_Start_IT(&htim17);
					cS = CONT_ERROR;
				}
			}
		}

		if (cS == FOC_START) {
      /* Updating pahse current data */
			FOC_LivGguard_U.PhaseCurrent[2] = (float)(injectedVal[PHASE_U] - currSensOff[PHASE_U]) * ADC_TO_CURR;
			FOC_LivGguard_U.PhaseCurrent[1] = (float)(injectedVal[PHASE_V] - currSensOff[PHASE_V]) * ADC_TO_CURR;
			FOC_LivGguard_U.PhaseCurrent[0] = 0.0f - FOC_LivGguard_U.PhaseCurrent[1] - FOC_LivGguard_U.PhaseCurrent[2];

      /* Updating angle data */
			d.encoder_count = __HAL_TIM_GET_COUNTER(&htim2);
			d.mech_angle = d.encoder_count * COUNTS_TO_RADS;
			d.mech_angle = fmodf(d.mech_angle, TWO_PI);
			d.elec_angle = (d.mech_angle * POLEPAIRS) - d.offset_angle_elec;
			d.elec_angle = fmodf(d.elec_angle, TWO_PI);
			FOC_LivGguard_U.MtrElcPos = d.elec_angle;

      /* Running the FOC model */
			rt_OneStep();

      /* SVM and PWM update */
			d.Va_SVM = FOC_LivGguard_Y.Va;
			d.Vb_SVM = FOC_LivGguard_Y.Vb;
			d.Vc_SVM = FOC_LivGguard_Y.Vc;

			if (d.Va_SVM > d.Vmax_SVM) {
				d.Va_SVM = d.Vmax_SVM;
			} else if (d.Va_SVM < -d.Vmax_SVM) {
				d.Va_SVM = -d.Vmax_SVM;
			}

			if (d.Vb_SVM > d.Vmax_SVM) {
				d.Vb_SVM = d.Vmax_SVM;
			} else if (d.Vb_SVM < -d.Vmax_SVM) {
				d.Vb_SVM = -d.Vmax_SVM;
			}

			if (d.Vc_SVM > d.Vmax_SVM) {
				d.Vc_SVM = d.Vmax_SVM;
			} else if (d.Vc_SVM < -d.Vmax_SVM) {
				d.Vc_SVM = -d.Vmax_SVM;
			}

			d.pwm_a = (uint16_t)((d.Va_SVM / d.Vmax_SVM) * TIM1_ARR_HALF + TIM1_ARR_HALF);
			d.pwm_b = (uint16_t)((d.Vb_SVM / d.Vmax_SVM) * TIM1_ARR_HALF + TIM1_ARR_HALF);
			d.pwm_c = (uint16_t)((d.Vc_SVM / d.Vmax_SVM) * TIM1_ARR_HALF + TIM1_ARR_HALF);

			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, d.pwm_a);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, d.pwm_b);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, d.pwm_c);
		}

		if (cS == CONT_ERROR) {
      /* Checking is error is triggered and shutting off gate drivers and TIM1 */
			if (er.error_triggered) {
				er.drive_off = 1;

				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
				__HAL_TIM_MOE_DISABLE(&htim1);
			}

      /* Resetting FOC data structures after error trigger */
			(void)memset(&FOC_LivGguard_U, 0, sizeof(ExtU_FOC_LivGguard_T));
			(void)memset(&FOC_LivGguard_Y, 0, sizeof(ExtY_FOC_LivGguard_T));
		}

    if (cS == ANGLE_OFFSET_STORE) {
      //TODO: Store the angle offset in flash memory and read it on startup to avoid doing the offset calibration on every power cycle
      uint16_t offset_eeprom = (uint16_t)(d.offset_angle_elec * 100.0f);
      if (EEPROM_Write_Page0(offset_eeprom) == HAL_OK)
        cS = ANGLE_CALIB_DONE;
      else {
        er.eeprom_write_error = 1;
        err = EEPROM_WRITE_ERROR;
      }
      HAL_TIM_Base_Start_IT(&htim17);
      HAL_NVIC_SystemReset();
    }
	}

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM17) {
    /* Time counter for CAN transmission */
    static uint16_t can_counter = 0;
    can_counter++;

    /* Gathering the ADC1 data */
    ADC1_Analog_Val_Update();

    /* MCU Proctections Model input update */
    Model_Params_Input();
    /* Running MCU protections model */
		MCU_Protections_step();
    Sensor_Disconnection_Check();

    /* Checking the MCU Protections Model output flags and setting error flags */
    Model_Output_Flag_Checks();
    
    /* Queue messages every 500ms */
    if (can_counter >= CAN_BUS_CYCLE) {
      can_counter = 0;
      
      // Only queue - don't process here
      Send_Data_On_CAN_401();
      Send_Data_On_CAN_402();
      Send_Data_On_CAN_403();
    }
	}
}

/* FDCAN TX Complete Callback - automatically sends next message */
void HAL_FDCAN_TxBufferCompleteCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes)
{
  if (hfdcan->Instance == FDCAN2) {
      // Transmission complete, send next message from queue
      CAN_Queue_Process();
  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == GPIO_PIN_7) {
		d.z_pulse ^= 1;
		d.z_count++;

    /* Storing Curr Z count */
    d.curr_z_count = d.z_count;

    /* Stopping uint32_t overflow */
		if (d.z_count >= UINT32_MAX) {
			d.z_count = 0;
		}

    /* Not Resetting mech angle and TIM2 reg on every z index pulse, only getting the TIM2 count */
		if (cS == FOC_START) {
      /* Getting TIM2 count at Z trig */
      d.count_at_z = __HAL_TIM_GET_COUNTER(&htim2);
//			d.mech_angle = 0.0f;
//			__HAL_TIM_SET_COUNTER(&htim2, 0);
		}
	}
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM5) {
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)  // If the interrupt is triggered by channel 1
    {
      /* Using TIM5 to get the initial angle on startup from the encoder PWM duty */
      // Read the IC value
      d.ICvalue = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

      if (d.ICvalue != 0)
      {
        // calculate the Duty Cycle
        d.Duty = (HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2) * 100.0f)/d.ICvalue;

        d.Frequency = (float)HAL_RCC_GetSysClockFreq()/(d.ICvalue * (TIM5_PSC + 1));
      }
    }
  }
}

float throttle_to_rpm(float v_throttle) {
    const float V_MIN = 1.2f;
    const float V_MAX = 3.4f;
    const float RPM_MAX = 3000.0f;

    // Clamp voltage
    if (v_throttle <= V_MIN)
        return 0.0f;

    if (v_throttle >= V_MAX)
        return RPM_MAX;

    // Linear map
    return RPM_MAX * (v_throttle - V_MIN) / (V_MAX - V_MIN);
}

float map_speed_to_id_ref(float speed_rpm)
{
    const float BASE_SPEED_RPM = 750.0f;   // start of flux weakening
    const float MAX_SPEED_RPM  = 3000.0f;   // full weakening
    const float ID_FW_MAX      = 3.0f;     // max |Id| in amps

    float speed = fabsf(speed_rpm);

    if (d.forward_pin == GPIO_PIN_RESET && d.reverse_pin == GPIO_PIN_SET) {
    	if (speed <= BASE_SPEED_RPM)
    	{
        	return 0.0f;
    	}
    	else if (speed >= MAX_SPEED_RPM)
    	{
        	return -ID_FW_MAX;
    	}
    	else
    	{
        	float k = (speed - BASE_SPEED_RPM) /
                  (MAX_SPEED_RPM - BASE_SPEED_RPM);

        	return -ID_FW_MAX * k;
    	}
    } else if (d.forward_pin == GPIO_PIN_SET && d.reverse_pin == GPIO_PIN_RESET) {
    	if (speed <= BASE_SPEED_RPM)
    	{
        	return 0.0f;
    	}
    	else if (speed >= MAX_SPEED_RPM)
    	{
        	return ID_FW_MAX;
    	}
    	else
    	{
        	float k = (speed - BASE_SPEED_RPM) /
                  (MAX_SPEED_RPM - BASE_SPEED_RPM);

        	return ID_FW_MAX * k;
    	}
    } else {
    	return 0;
    }
}

void rt_OneStep(void)
{
  static bool OverrunFlags[2] = { 0, 0 };

  static bool eventFlags[2] = { 0, 0 };/* Model has 2 rates */

  static int taskCounter[2] = { 0, 0 };

  /* Disable interrupts here */

  /* Check base rate for overrun */
  if (OverrunFlags[0]) {
    rtmSetErrorStatus(FOC_LivGguard_M, "Overrun");
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
      rtmSetErrorStatus(FOC_LivGguard_M, "Overrun");
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
  FOC_LivGguard_step0();

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
		FOC_LivGguard_U.MtrSpd = fabsf(d.rad_s);
    if (fabsf(d.RPM) >= MIN_RPM_FOR_MOTOR_START) {
      d.motor_start = 1;
    }

    /* Step the model for subrate 1 */
    FOC_LivGguard_step1();

    /* Get model outputs here */

    /* Indicate task complete for subrate */
    OverrunFlags[1] = false;
    eventFlags[1] = false;
  }

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

uint8_t Initial_Fault_Check(void) {
	if (injectedVal[0] <= 14000 || injectedVal[1] <= 14000 || injectedVal[0] >= 40000 || injectedVal[1] >= 40000) {
		er.curr_sens_error = 1;
    err = CURR_SENS_ERROR;
		er.error_triggered = 1;
	}

	if (d.Vdc >= MCU_Protections_U.Thresholds.OV_Error_Limit_V) {
		er.bus_voltage_ov_error = 1;
    err = BUS_VOLTAGE_OV_ERROR;
		er.error_triggered = 1;
	}

	if (d.Vdc <= MCU_Protections_U.Thresholds.UV_Error_Limit_V) {
		er.bus_voltage_uv_error = 1;
    err = BUS_VOLTAGE_UV_ERROR;
		er.error_triggered = 1;
	}

	if (er.error_triggered) {
		return !HAL_OK;
	} else {
		return HAL_OK;
	}
}

void set_Initial_angle(void) {
  /* Calculating the startup angle and converting to TIM2 counts */
  d.Angle_From_Duty = (100.0f - d.Duty) * 0.01f * 2.0f * M_PI - HIGH_PULSE16_ERROR;
  d.Angle_From_Duty = fmodf(d.Angle_From_Duty, TWO_PI);
  d.Count_From_Duty = (uint16_t)((d.Angle_From_Duty / TWO_PI) * (TIM2_ARR + 1));

  /* Checking for PWM disconnection error */
  if (encoder_pwm_error_check() == !HAL_OK) {
    er.error_triggered = 1;
    er.pwm_error = 1;
    err = ENCODER_PWM_ERROR;
    cS = CONT_ERROR;

    return;
  }

  HAL_Delay(100);

  /* Disabling the encoder PWM input capture */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
  HAL_TIM_IC_Stop_IT(&htim5, TIM_CHANNEL_1);
  HAL_TIM_IC_Stop_IT(&htim5, TIM_CHANNEL_2);
  HAL_TIM_IC_DeInit(&htim5);
  HAL_TIM_Base_MspDeInit(&htim5);
  cS = CURR_SENS_CALIB;
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
