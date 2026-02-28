#ifndef __LIMIT_ERRORS__H_
#define __LIMIT_ERRORS__H_

#include "main.h"

uint8_t Over_Current_Phase_Error(float a, float b, float c);
uint8_t Over_Current_Id_Iq_Error(float Id, float Iq);
uint8_t Bus_Voltage_Error(float Bus_DC);
uint8_t Aux_Voltage_Error(float Aux_DC);
uint8_t Mtr_OT_Error(float motor_temp);
uint8_t Mtc_OT_Error(float controller_temp);
void Error_Check(void);

#endif