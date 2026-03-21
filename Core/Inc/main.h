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
#define EST_CYC_CNT			1
#define CLOSED_FOC			1
#define PROTECTION_MODEL	0
#define ENABLE_FAULTS		1
#define DISABLE_FAULTS		0
#define VH_CAN_ID			0
#define DEBUG_CAN_ID		1
#define CAN_BASED_REF		1
#define CAN_BASED_DIR		1
#define THROTTLE_BASED_DIR	0
#define THROTTLE_BASED_REF  0
#define CAN_BASED_THRV		1
#define THR_BASED_THRV		0
#define ENABLE_TUNING		0

#define CONFIG_VERSION_MAJOR 		0x05
#define CONFIG_VERSION_MINOR 		0x00
#define CONFIG_VERSION_SUBMINOR 	0x00
#define FIRMWARE_VERSION_MAJOR  	0x00
#define FIRMWARE_VERSION_MINOR 		0x0A
#define FIRMWARE_VERSION_SUBMINOR 	0x11

#define CURR_APP1					1
#define CURR_APP2					0

#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "Autotune101.h"
#include "Speed_Sensing.h"
#include "NTC_Temp_Reading.h"
#if PROTECTION_MODEL
#include "MCU_Protections.h"
#endif
// #include "FOC_LivGguard.h"
#include "FOC_MTPA_FWC_FF.h"
#include "Open_FOC0.h"
// #include "FOC_Basic_FF.h"
#include "fdcan.h"
#include "Rate_Limiter.h"
#include "alignment_routine.h"
#include "Eeprom.h"
#include "Sensor_Disconnection_Checks.h"
#include "Limit_Errors.h"
#include "Helper_Functions.h"
#include "Peripheral_Init.h"
#if THROTTLE_BASED_REF
#include "throttle_map.h"
#endif
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct data {
	uint8_t ctlr_derate_flag;
	uint8_t motor_derate_flag;
	uint8_t throttle_percent;
	uint8_t regen_flag;
	uint8_t z_pulse;
	uint8_t A_Pulse;
	uint8_t B_Pulse;
	uint8_t A_B_XOR;
	uint8_t motor_start;
	uint8_t start_alignment;
	uint8_t end_alignment;
	uint8_t power_pin;
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
	uint16_t offset_angle_mech_cw_16bit;
	uint16_t offset_angle_mech_ccw_16bit;
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
	uint32_t thr_v_mv;
	float pack_current;
	float offset_angle_elec;
	float offset_angle_mech_cw;
	float offset_angle_mech_ccw;
	float offset_angle_mech_avg;
	float speed_ref;
	float count_delta;
	float Kvf;
	float freq;
	float t_req;
	float ICvalue;
	float Duty;
	float abs_Angle_pwm;
	float Angle_From_Duty;
	float Frequency;
	float pole_pair;
	float Va;
	float Vb;
	float Vc;
	float Vpp;
	float Vmax_SVM;
	float vrms;
	float irms;
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
	float ATA_Offset;
} data;

typedef struct foc_pid_t {
	float Kp;
	float Ki;
	float Kd;
	float Kd_Filter;
	float Output_Up_Limit;
	float Output_Low_Limit;
	float Back_Kaw;
} foc_pid_t;

typedef struct can_data_t {
	uint8_t direction;
	uint8_t power_mode;
	uint8_t reset_flag;
	float can_Ld;
	float can_Lq;
	float can_Lambda;
	float Kfw;
	float Kaw;
	float can_instV;
	foc_pid_t canSpeed_PID;
	foc_pid_t canId_PID;
	foc_pid_t canIq_PID;
} can_data_t;

typedef struct errors {
	uint8_t error_c1;
	uint8_t error_c2;
	uint8_t error_c3;
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
	CONT_ERROR,
	RESET_STATE
} currSession;

typedef enum fnr_state_t {
	FORWARD = 1,
	REVERSE,
	NEUTRAL
} fnr_state_t;

typedef enum power_mode_t {
	ECO,
	SPORTS
} power_mode_t;

extern fnr_state_t fnr_state;
extern power_mode_t pw_state;
extern currSession cS;
extern data d;
extern can_data_t can_d;
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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */
#define POLEPAIRS 				3.0f
#define COUNTS_TO_RADS			0.001533981f//(2.0f * (PI / (TIM2_ARR+1)))
#define TWO_PI					6.283185f
#define TWO_ROOT2				2.828427f
#define ROOT2					1.414213f
#define	ROOT3					1.732051f
#define ONE_BY_ROOT2			0.70710678f
#define ADC_TO_CURR				0.0407496f
#define ALIGN_DUTY				1000
#define RS		  				0.01047f
#define LQ						0.000386f
#define LD						0.000148f
#define LAMBDA					0.0236f
#define CURR_TORQUE_RATIO		0.1673f //(Max_Torque/Max_A)
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

#define ALIGNMENT_PULSE_MS		40
#define ALIGNMENT_REP_COUNT		5

#define ECO_MAX_SPEED			4500.0f
#define SPORTS_MAX_SPEED		6000.0f
#define REV_MAX_SPEED			6000.0f
#define FWC_LIMIT				10.0f

#define TIM1_PSC			9
#define TIM1_ARR			2499
#define TIM1_DEAD_TIME		100
#define TIM1_ARR_HALF		1250.0f
#define TIM2_ARR			4095//(MAX_COUNT of your position sensor - 1)
#define TIM5_PSC			99
#define TIM5_ARR			0xFFFFFFFF
#define TIM17_PSC			39
#define TIM17_ARR			2499
#define HIGH_PULSE16_ERROR	0.024574f
#define OFFSET_CALC_ELEC 	0.15f//1.1913f
#define OFFSET_CALC_MECH_CW		0.6211f
#define OFFSET_CALC_MECH_CCW	0.6502f
#define OFFSET_CALC_MECH_AVG	0.63565f

#define MTR_NTC_R25			10000.0f
#define MTC_NTC_R25			10000.0f
#define CAN_BUS_CYCLE		500
#define BUS_VDC_SCALE		0.00206f
#define AUX_VDC_SCALE		0.000188658f

#define MAX_PHASE_CURRENT		512.0f
#define BUS_DC_OV_LIMIT			80
#define BUS_DC_UV_LIMIT			30
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

/* FOC PID Default Settings */
/* FW Kfw and Kaw */
#define FW_KFW					0.001f
#define FW_KAW					10.0f
/* Speed PID */
#define SPEED_KP				4.0f
#define SPEED_KI				8.0f
#define SPEED_KD				0.00001f
#define SPEED_KD_FILTER			5.0f
#define SPEED_PID_OUT_UPL		MOTOR_PEAK_AC
#define SPEED_PID_OUT_LOWL		0.0f
#define SPEED_PID_BACK_KAW		ROOT2
/* ID PID */
#define ID_KP					0.4f
#define ID_KI					6.0f
#define ID_KD					0.00001f
#define ID_KD_FILTER			5.0f
#define ID_PID_OUT_UPL			SVM_VOLTAGE_LIMIT
#define ID_PID_OUT_LOWL			-SVM_VOLTAGE_LIMIT
#define ID_PID_BACK_KAW			3.87298f
/* IQ PID */
#define IQ_KP					0.3f
#define IQ_KI					7.0f
#define IQ_KD					0.00001f
#define IQ_KD_FILTER			5.0f
#define IQ_PID_OUT_UPL			SVM_VOLTAGE_LIMIT
#define IQ_PID_OUT_LOWL			-SVM_VOLTAGE_LIMIT
#define IQ_PID_BACK_KAW			4.8304589f

#define THR_MIN_VAL 			0.9f
#define THR_MAX_VAL				4.0f
#define MIN_RPM_CHANGE_LIM		10.0f

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
