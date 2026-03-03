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
#include "NTC_Temp_Reading.h"
#include "MCU_Protections.h"
#include "FOC_LivGguard.h"
#include "fdcan.h"
#include "Rate_Limiter.h"
#include "alignment_routine.h"
#include "Eeprom.h"
#include "Sensor_Disconnection_Checks.h"
#include "Limit_Errors.h"
#include "Open_FOC0.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct data {
	uint8_t z_pulse;
	uint8_t A_Pulse;
	uint8_t B_Pulse;
	uint8_t A_B_XOR;
	uint8_t motor_start;
	uint8_t start_alignment;
	uint8_t end_alignment;
	uint8_t forward_pin;
	uint8_t reverse_pin;
	uint8_t init_check;
	uint8_t Vdc;
	uint8_t Aux_dc;
	int16_t Mtr_temp;
	int16_t Mtc_temp;
	uint16_t pwm_a;
	uint16_t pwm_b;
	uint16_t pwm_c;
	uint16_t offset_angle_elec_16bit;
	uint16_t mtc_analog_val;
	uint16_t mtr_analog_val;
	uint32_t count_at_alignment;
	uint32_t encoder_count;
	uint32_t Count_From_Duty;
	uint32_t count_at_z;
	uint32_t count_diff_at_z;
	uint32_t z_count;
	uint32_t prev_z_count;
	uint32_t curr_z_count;
	uint32_t z_count_diff;
	uint32_t cycles;
	float offset_angle_elec;
	float speed_ref;
	float count_delta;
	float Kvf;
	float freq;
	float t_req;
	float ICvalue;
	float Duty;
	float Angle_From_Duty;
	float Frequency;
	float pole_pair;
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

typedef struct errors {
	char curr_sens_error;
	char bus_voltage_ov_error;
	char bus_voltage_uv_error;
	char aux_voltage_ov_error;
	char aux_voltage_uv_error;
	char id_iq_oc_error;
	char phase_curr_error;
	char mtr_temp_ot_error;
	char mtc_temp_ot_error;
	char mtr_temp_disconnection_error;
	char mtc_temp_disconnection_error;
	char eeprom_write_error;
	char eeprom_read_error;
	char a_b_error;
	char z_error;
	char pwm_error;
	char enc_5v_error;
	char error_triggered;
	char drive_off;
} errors;

typedef enum errors_nums {
	NO_ERROR,
	CURR_SENS_ERROR,
	BUS_VOLTAGE_OV_ERROR,
	BUS_VOLTAGE_UV_ERROR,
	AUX_VOLTAGE_OV_ERROR,
	AUX_VOLTAGE_UV_ERROR,
	ID_IQ_OC_ERROR,
	PHASE_CURR_ERROR,
	MTR_TEMP_OT_ERROR,
	MTC_TEMP_OT_ERROR,
	MTR_TEMP_DISCONNECTION_ERROR,
	MTC_TEMP_DISCONNECTION_ERROR,
	EEPROM_WRITE_ERROR,
	EEPROM_READ_ERROR,
	ENCODER_A_B_ERROR,
	ENCODER_Z_ERROR,
	ENCODER_PWM_ERROR,
	ENCODER_5V_ERROR
} errors_nums;

typedef enum currSession {
	INIT,
	ANGLE_CALIB,
	ANGLE_CALIB_DONE,
	ANGLE_OFFSET_STORE,
	OPEN_FOC_START,
	CURR_SENS_CALIB,
	FOC_START,
	CONT_ERROR
} currSession;

typedef enum fnr_state_t {
	FORWARD = 1,
	REVERSE,
	NEUTRAL
} fnr_state_t;

extern fnr_state_t fnr_state;
extern currSession cS;
extern data d;
extern errors er;
extern errors_nums err;
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
void set_Initial_angle(void);
void disable_drive(void);
void rt_OneStep(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */
#define POLEPAIRS 				3.0f
#define COUNTS_TO_RADS			0.003067962f //(2.0f * (PI / (TIM2_ARR+1)))
#define TWO_PI					6.283185f
#define TWO_ROOT2				2.828427f
#define ROOT2					1.414213f
#define	ROOT3					1.732051f
#define ONE_BY_ROOT2			0.70710678f
#define ADC_TO_CURR				0.0407496f
#define ALIGN_DUTY				1000
#define RS		  				0.0102f
#define LQ						0.000148f
#define LD						0.000064f
#define LAMBDA					0.032f
#define CURR_TORQUE_RATIO		0.1673f //(Max_Torque/Max_Arms)
#define NO_OF_SAMPLES 			4096
#define ADC_TO_V				0.00005030822f
#define DEG_TWO_PI_3			2.094395f
#define DEG_4_PI_3				4.188790f
#define OP_VOLTAGE				58.0f
#define AUX_OP_VOLTAGE			12.0f
#define SVM_VOLTAGE_LIMIT		(OP_VOLTAGE / ROOT3)
#define MOTOR_PEAK_ARMS			338.0f
#define MOTOR_PEAK_AC			(MOTOR_PEAK_ARMS * ROOT2)
#define V_F_RATIO				0.2875f
#define SPEED_REF_RPM_MAX		500.0f
#define MIN_RPM_FOR_MOTOR_START 80.0f
#define RAD_S_TO_RPM   			9.549296f

#define TIM1_PSC			19
#define TIM1_ARR			2499
#define TIM1_DEAD_TIME		100
#define TIM1_ARR_HALF		1250.0f
#define TIM2_ARR			2047//(MAX_COUNT of your position sensor - 1)
#define TIM5_PSC			99
#define TIM5_ARR			0xFFFFFFFF
#define TIM17_PSC			39
#define TIM17_ARR			2499
#define HIGH_PULSE16_ERROR	0.024574f
#define OFFSET_CALC_ELEC 	1.1913f

#define EST_CYC_CNT			1
#define OPEN_FOC			0
#define CLOSED_FOC			1
#define PROTECTION_MODEL	0
#define ENABLE_FAULTS		1
#define DISABLE_FAULTS		0

#define MTR_NTC_R25			49000.0f
#define MTC_NTC_R25			10000.0f
#define CAN_BUS_CYCLE		500
#define BUS_VDC_SCALE		0.00206f
#define AUX_VDC_SCALE		0.000188658f

#define MAX_PHASE_CURRENT		512.0f
#define BUS_DC_OV_LIMIT			72
#define BUS_DC_UV_LIMIT			50
#define AUX_UV_LIMIT			9
#define MOTOR_TEMP_OT_LIMIT		120
#define CONTRL_TEMP_OT_LIMIT	80
#define PHASE_OC_COUNT			5
#define ID_IQ_OC_COUNT			5
#define BUS_DC_OV_COUNT			1
#define BUS_DC_UV_COUNT			1
#define CURR_SEN_ANLG_HIGH		40000
#define CURR_SEN_ANLG_LOW		14000
#define TEMP_SENS_FAULT_COUNT 	65000
#define ENCODER_CHECK_MS		20
#define ENCODER_FAULT_MAX_COUNT 5

typedef enum ADC2_CHANNELS {
	PHASE_U,
	PHASE_V,
} ADC2_CHANNELS;

typedef enum ADC1_CHANNELS {
	THROTTLE,
	CONTRL_TEMP,
	MOTOR_TEMP,
	AUX_DC,
	BUS_DC
} ADC1_CHANNELS;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
