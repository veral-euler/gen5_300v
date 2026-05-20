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
#define PROTECTION_MODEL	0
#define ENABLE_FAULTS		1
#define DISABLE_FAULTS		0
#define ENABLE_ENC_ERRORS	0
#define TUNING_ENABLED		1
#define RESOLVER_ENABLED	1
#define OPEN_FOC			0
#define CLOSED_FOC			1
#define OFFSET_SCHEDULER	0

#define VH_CAN_ID			0
#define DEBUG_CAN_ID		1
#define CAN_BASED_REF		1
#define CAN_BASED_DIR		1
#define THROTTLE_BASED_DIR	0
#define THROTTLE_BASED_REF  0
#define CAN_BASED_THRV		1
#define THR_BASED_THRV		0

/* Vehicle Speed Factors */
#define HLP					0
#define HI_CITY				1
#define HI_RANGE			0
#define RPM_TO_KMPH_HLP		 0.008909f
#define RPM_TO_KMPH_HI_CITY	 0.01f
#define RPM_TO_KMPH_HI_RANGE 0.01f

#define PEGASUS_DEVICE_ID			0x03
#define CONFIG_VERSION_MAJOR 		0x05
#define CONFIG_VERSION_MINOR 		0x00
#define CONFIG_VERSION_SUBMINOR 	0x00
#define FIRMWARE_VERSION_MAJOR  	0x00
#define FIRMWARE_VERSION_MINOR 		0x0A
#define FIRMWARE_VERSION_SUBMINOR 	0x11
#define HARDWARE_VERSION_MAJOR		0x04
#define HARDWARE_VERSION_MINOR		0x03
#define HARDWARE_VERSION_SUBMINOR	0x01

#define CURR_APP1					1
#define CURR_APP2					2

#define POLEPAIRS 				4.0f
#define COUNTS_TO_RADS			3.8349519E-4f//(2.0f * (PI / (TIM2_ARR+1)))
#define TWO_PI					6.283185f
#define TWO_ROOT2				2.828427f
#define ROOT2					1.414213f
#define	ROOT3					1.732051f
#define ONE_BY_ROOT2			0.70710678f
#define ADC_TO_CURR				0.0407496f
#define ALIGN_DUTY				1000
#define RS		  				0.0082f
#define LQ						0.00022287f
#define LD						0.00007346f
#define LAMBDA					0.02437364f
#define CURR_TORQUE_RATIO		0.2033239f //(Max_Torque/Max_A)
#define NO_OF_SAMPLES 			4096
#define ADC_TO_V				0.00005030822f
#define DEG_TWO_PI_3			2.094395f
#define DEG_4_PI_3				4.188790f
#define OP_VOLTAGE				77.0f
#define AUX_OP_VOLTAGE			12.0f
#define SVM_VOLTAGE_LIMIT		(OP_VOLTAGE / ROOT3)
#define MOTOR_PEAK_ARMS			385.0f
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
#define ECO_MAX_TORQUE			42.0f
#define SPORTS_MAX_TORQUE		80.0f
#define REV_MAX_TORQUE			80.0f

#define TIM1_PSC			9
#define TIM1_ARR			2499
#define TIM1_DEAD_TIME		100
#define TIM1_ARR_HALF		1250.0f
#define TIM2_ARR			16383//(MAX_COUNT of your position sensor - 1)
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
#define MTR_PTC_R25			1000.0f
#define CVD_A            	3.9083e-3f
#define CVD_B           	-5.775e-7f

#define CAN_BUS_CYCLE		500
#define BUS_VDC_SCALE		0.00206f
#define AUX_VDC_SCALE		0.000188658f

#define MAX_PHASE_CURRENT		550.0f
#define BUS_DC_OV_LIMIT			150
#define BUS_DC_UV_LIMIT			50
#define AUX_UV_LIMIT			9
#define MOTOR_TEMP_OT_LIMIT		120
#define CONTRL_TEMP_OT_LIMIT	80
#define PHASE_OC_COUNT			10
#define ID_IQ_OC_COUNT			10
#define BUS_DC_OV_COUNT			1
#define BUS_DC_UV_COUNT			1
#define CURR_SEN_ANLG_HIGH		40000
#define CURR_SEN_ANLG_LOW		14000
#define TEMP_SENS_FAULT_COUNT 	65000
#define ENCODER_CHECK_MS		20
#define ENCODER_FAULT_MAX_COUNT 5

/* EEPROM Settings */
#define EEPROM_ADDRESS          0xA0 // Adjust based on your EEPROM's I2C address
#define EEPROM_MAGIC_NUM        0x23
#define EEPROM_NO_MAGIC_NUM     2
#define EEPROM_PAGE_SIZE        8
#define EEPROM_WRITE_TIMEOUT    5

/* CAN Message Queue Configuration */
#define CAN_TX_QUEUE_SIZE       15
#define FRAME_SLOT_MS           2U   // was 1U at 1Mbps, double it at 250kbps
#define TICKS_PER_SLOT          4U   // 4 ticks × 0.5ms = 2ms per DEVICE_ID slot

/* Speed Sensing Constants */
#define T_S 0.001f
#define DERIVATIVE_CONSTANT (1.0f / T_S) // Derivative constant
#define T_F_ROTOR_SPEED 0.03f // Constant to filter rotor speed
#define SPEED_FILTER_CONSTANT_1 ((2.0f * T_F_ROTOR_SPEED - T_S) / (2.0f * T_F_ROTOR_SPEED + T_S)) // Constant to filter speed
#define SPEED_FILTER_CONSTANT_2 (T_S / (2.0f * T_F_ROTOR_SPEED + T_S)) // Constant to filter speed

/* FOC PID Default Settings */
/* FW Kfw and Kaw */
#define FW_KFW					0.0008f
#define FW_KAW					15.0f
#define FW_M2F					0.9f
#define FW_F2M					0.95f
#define FW_RST_FACTOR			0.9f
/* Speed PID */
#define SPEED_KP				5.0f
#define SPEED_KI				1.0f
#define SPEED_KD				0.00001f
#define SPEED_KD_FILTER			5.0f
#define SPEED_PID_OUT_UPL		MOTOR_PEAK_AC
#define SPEED_PID_OUT_LOWL		0.0f
#define SPEED_PID_BACK_KAW		ROOT2
/* ID PID */
#define ID_KP					0.1f
#define ID_KI					6.0f
#define ID_KD					0.00001f
#define ID_KD_FILTER			5.0f
#define ID_PID_OUT_UPL			SVM_VOLTAGE_LIMIT
#define ID_PID_OUT_LOWL			-SVM_VOLTAGE_LIMIT
#define ID_PID_BACK_KAW			3.87298f
/* IQ PID */
#define IQ_KP					0.15f
#define IQ_KI					5.5f
#define IQ_KD					0.00001f
#define IQ_KD_FILTER			5.0f
#define IQ_PID_OUT_UPL			SVM_VOLTAGE_LIMIT
#define IQ_PID_OUT_LOWL			-SVM_VOLTAGE_LIMIT
#define IQ_PID_BACK_KAW			4.8304589f

#define THR_MIN_VAL 			0.8f
#define THR_MAX_VAL				4.1f
#define MIN_RPM_CHANGE_LIM		1.0f

#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "app_types.h"
#include "Ad2s1210.h"
#include "Offset0.h"
#if OFFSET_SCHEDULER
#include "Offset_Scheduler.h"
#endif
#include "../Libs/Include/Autotune101.h"
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
#include "Torque_Management.h"
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
	uint8_t canBus_ok;
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
	uint8_t tuning_enabled;
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
	float omega_e;
	float pack_current;
	float offset_angle_elec;
	float offset_angle_mech_cw;
	float offset_angle_mech_ccw;
	float offset_angle_mech_avg;
	float speed_ref;
	float torque_final;
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
	float elec_angle_resolver;
	float omega_e_resolver;
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
	float mech_angle_resolver;
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

typedef struct foc_fw_t {
	float Kaw;
	float Kfw;
	float M_to_F;
	float F_to_M;
	float Rst_Factor;
} foc_fw_t;

typedef struct can_data_t {
	uint8_t direction;
	uint8_t power_mode;
	uint8_t reset_flag;
	float can_Ld;
	float can_Lq;
	float can_Lambda;
	float can_instV;
	foc_fw_t canFW_params;
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
void delay_us(uint32_t us);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */
extern data d;
extern can_data_t can_d;
extern errors er;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
