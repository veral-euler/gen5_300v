#ifndef __SENSOR_DISCONNECTION_CHECKS_H
#define __SENSOR_DISCONNECTION_CHECKS_H

#include "main.h"

uint8_t encoder_ab_error_check(void);
uint8_t encoder_z_index_check(void);
uint8_t encoder_pwm_error_check(void);
uint8_t temp_sensor_disconnection_check(uint16_t temperature_analog_val, uint16_t threshold);
uint8_t encoder_5v_error_check(void);
uint8_t Initial_Fault_Check(void);
void Model_Params_Input(void);
void Model_Output_Flag_Checks(void);
void ADC1_Analog_Val_Update(void);
void Sensor_Disconnection_Check(void);

#endif /* __SENSOR_DISCONNECTION_CHECKS_H */