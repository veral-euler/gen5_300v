#ifndef __FDCAN_H_
#define __FDCAN_H_

#include "main.h"

void FDCAN_SETUP();
void _fdcan_transmit_on_can(uint32_t arbitration_id, uint8_t format, uint8_t * can_data, uint8_t dlc);
void Send_Data_On_CAN_401(void);
void Send_Data_On_CAN_402(void);
void Send_Data_On_CAN_403(void);

#endif
