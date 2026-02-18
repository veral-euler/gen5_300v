#ifndef __SENSOR_DISCONNECTION_CHECKS_H
#define __SENSOR_DISCONNECTION_CHECKS_H

#include "main.h"

#define ENCODER_ERROR_THRESHOLD 60 // Adjust this threshold based on your system's characteristics

uint8_t encoder_ab_error_check(void);
uint8_t encoder_z_index_check(void);
uint8_t temp_sensor_disconnection_check(uint16_t temperature, uint16_t threshold);
void Sensor_Disconnection_Check(void);

#endif /* __SENSOR_DISCONNECTION_CHECKS_H */