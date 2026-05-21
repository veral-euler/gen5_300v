#ifndef __APP_TYPES_H_
#define __APP_TYPES_H_

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
	RESET_STATE,
	ENC_READ
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

extern fnr_state_t fnr_state;
extern power_mode_t pw_state;
extern currSession cS;
extern errors_nums err;

#endif /* end of file __APP_TYPES_H_ */