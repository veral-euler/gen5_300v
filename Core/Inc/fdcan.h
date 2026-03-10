#ifndef __FDCAN_H_
#define __FDCAN_H_

#include "main.h"

/* CAN Message Queue Configuration */
#define CAN_TX_QUEUE_SIZE 15

typedef struct {
    uint32_t arbitration_id;
    uint8_t format;
    uint8_t data[8];
    uint8_t dlc;
} CAN_TxMessage_t;

typedef struct {
    CAN_TxMessage_t buffer[CAN_TX_QUEUE_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
    volatile uint16_t count;
} CAN_TxQueue_t;

void FDCAN_SETUP();
void _fdcan_transmit_on_can(uint32_t arbitration_id, uint8_t format, uint8_t * can_data, uint8_t dlc);
void _fdcan_filter_IDList(uint32_t can_receive_id, uint8_t format, uint32_t filter_bank, uint32_t fifo);
#if DEBUG_CAN_ID
void Send_Data_On_CAN_401(void);
void Send_Data_On_CAN_402(void);
void Send_Data_On_CAN_403(void);
void Send_Data_On_CAN_404(void);
void Send_Data_On_CAN_405(void);
#endif

#if VH_CAN_ID
/* Vehicle */
void Send_on_CAN_705(float Mtr_Temp, float Cntrl_Temp);
void Send_on_CAN_706(float bus_voltage, float Speed_KMPH, uint8_t error_c);
void Send_on_CAN_708(uint8_t error_c_1, uint8_t error_c_2);
void Send_on_CAN_709(uint8_t historic_errors);
void Send_on_CAN_710(float throttle_percent, float throttle_voltage);
void Send_on_CAN_715(float rpm, float bus_voltage, float lv_12v_voltage);
void Send_on_CAN_716(float vrms, float irms);
void Send_on_CAN_717(float rpm);
void Send_on_CAN_724(float torque_ref);
void Send_on_CAN_726(void);
#endif

void CAN_Queue_Init(void);
uint8_t CAN_Queue_Push(uint32_t arbitration_id, uint8_t format, uint8_t *data, uint8_t dlc);
uint8_t CAN_Queue_IsEmpty(void);
void CAN_Queue_Process(void);
uint16_t CAN_Queue_GetCount(void);
void CAN_Queue_Push_And_Kickstart(uint32_t arbitration_id, uint8_t format, uint8_t *data, uint8_t dlc);

extern CAN_TxQueue_t can_tx_queue;
extern FDCAN_RxHeaderTypeDef RxMessageBuf;

#endif
