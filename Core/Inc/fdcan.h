#ifndef __FDCAN_H_
#define __FDCAN_H_

#include "main.h"

/* CAN Message Queue Configuration */
#define CAN_TX_QUEUE_SIZE 32

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
void Send_Data_On_CAN_401(void);
void Send_Data_On_CAN_402(void);
void Send_Data_On_CAN_403(void);

void CAN_Queue_Init(void);
uint8_t CAN_Queue_Push(uint32_t arbitration_id, uint8_t format, uint8_t *data, uint8_t dlc);
uint8_t CAN_Queue_IsEmpty(void);
void CAN_Queue_Process(void);
uint16_t CAN_Queue_GetCount(void);
void CAN_Queue_Push_And_Kickstart(uint32_t arbitration_id, uint8_t format, uint8_t *data, uint8_t dlc);

extern CAN_TxQueue_t can_tx_queue;

#endif
