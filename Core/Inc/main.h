/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "Speed_Sensing.h"
#include "FOC_Basic.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct data {
	uint8_t z_pulse;
	uint8_t z_count;
	uint8_t start_alignment;
	uint8_t end_alignment;
	uint8_t forward_pin;
	uint8_t reverse_pin;
	uint16_t pwm_a;
	uint16_t pwm_b;
	uint16_t pwm_c;
	uint32_t count_at_alignment;
	uint32_t encoder_count;
	uint32_t Count_From_Duty;
	float count_delta;
	float Kvf;
	float freq;
	float t_req;
	float ICvalue;
	float Duty;
	float Angle_From_Duty;
	float Frequency;
	float pole_pair;
	float Vdc;
	float Va;
	float Vb;
	float Vc;
	float Vpp;
	float Vmax_SVM;
	float mech_angle;
	float elec_angle;
	float elec_angle_120;
	float elec_angle_240;
	float Va_SVM;
	float Vb_SVM;
	float Vc_SVM;
	float raw_rad_s;
	float rad_s;
	float elecfreq;
	float RPM;
	float rms_a;
	float rms_b;
	float rms_c;
	float rms_total;
	float throttle_v;
} data;

typedef enum currSens {
	INIT,
	CALIB,
	END
} currSens;

extern currSens cS;
extern data d;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
uint32_t GetMicroseconds(void);
float throttle_to_torque(float v_throttle);
void rt_OneStep(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */
#define POLEPAIRS 			3.0f
#define COUNTS_TO_RADS		0.001533981f
#define TWO_PI				6.283185f
#define TWO_ROOT2			2.828427f
#define ADC_TO_CURR			0.040246f
#define ALIGN_DUTY			750
#define RS		  			0.0107f
#define CURR_TORQUE_RATIO	4.375f
#define NO_OF_SAMPLES 		4096
#define ADC_TO_V			0.00005030822f
#define T_DOWN				0.0000001f
#define T_UP				0.00001f
#define DEG_TWO_PI_3		2.094395f
#define DEG_4_PI_3			4.188790f
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
