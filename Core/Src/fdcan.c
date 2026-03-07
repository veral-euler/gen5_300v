#include "fdcan.h"

extern FDCAN_HandleTypeDef hfdcan2;
FDCAN_RxHeaderTypeDef RxMessageBuf;

CAN_TxQueue_t can_tx_queue = {0};

/* Initialize the queue */
void CAN_Queue_Init(void)
{
    can_tx_queue.head = 0;
    can_tx_queue.tail = 0;
    can_tx_queue.count = 0;
}

/* Add message to queue - ISR safe */
uint8_t CAN_Queue_Push(uint32_t arbitration_id, uint8_t format, uint8_t *data, uint8_t dlc)
{
    // Check if queue is full (read-only, safe without critical section)
    if (can_tx_queue.count >= CAN_TX_QUEUE_SIZE) {
        return 0;  // Queue full
    }
    
    // Get current head position
    uint16_t current_head = can_tx_queue.head;
    
    // Copy message to queue buffer
    can_tx_queue.buffer[current_head].arbitration_id = arbitration_id;
    can_tx_queue.buffer[current_head].format = format;
    can_tx_queue.buffer[current_head].dlc = dlc;
    
    for (uint8_t i = 0; i < dlc && i < 8; i++) {
        can_tx_queue.buffer[current_head].data[i] = data[i];
    }
    
    // Critical section only for updating pointers
    // uint32_t primask = __get_PRIMASK();
    // __disable_irq();
    
    can_tx_queue.head = (current_head + 1) % CAN_TX_QUEUE_SIZE;
    can_tx_queue.count++;
    
    // __set_PRIMASK(primask);
    
    return 1;  // Success
}

/* Check if queue has messages */
uint8_t CAN_Queue_IsEmpty(void)
{
    return (can_tx_queue.count == 0);
}

/* Process queue - send one message if available - CALL FROM MAIN LOOP ONLY */
void CAN_Queue_Process(void)
{
    // Quick check without critical section
    if (can_tx_queue.count == 0) {
        return;  // Nothing to send
    }
    
    // Check if FDCAN Tx FIFO has space
    if (HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan2) == 0) {
        return;  // FDCAN FIFO is full, try again later
    }
    
    // Get current tail position
    uint16_t current_tail = can_tx_queue.tail;
    
    // Read message data (safe to read without lock)
    CAN_TxMessage_t *msg = &can_tx_queue.buffer[current_tail];
    
    FDCAN_TxHeaderTypeDef TxMsg;
    TxMsg.IdType = msg->format;
    TxMsg.TxFrameType = FDCAN_DATA_FRAME;
    TxMsg.Identifier = msg->arbitration_id;
    TxMsg.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    TxMsg.BitRateSwitch = FDCAN_BRS_OFF;
    TxMsg.FDFormat = FDCAN_CLASSIC_CAN;
    TxMsg.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    TxMsg.MessageMarker = 0;
    TxMsg.DataLength = msg->dlc;
    
    // Try to send
    if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &TxMsg, msg->data) == HAL_OK) {
        // Message sent successfully, update tail pointer atomically
        // uint32_t primask = __get_PRIMASK();
        // __disable_irq();
        
        can_tx_queue.tail = (current_tail + 1) % CAN_TX_QUEUE_SIZE;
        can_tx_queue.count--;
        
        // __set_PRIMASK(primask);
    }
}

/* Get queue status */
uint16_t CAN_Queue_GetCount(void)
{
    return can_tx_queue.count;
}

/* Kick-start transmission when first message is queued */
void CAN_Queue_Push_And_Kickstart(uint32_t arbitration_id, uint8_t format, uint8_t *data, uint8_t dlc)
{
    uint8_t was_empty = CAN_Queue_IsEmpty();
    
    if (CAN_Queue_Push(arbitration_id, format, data, dlc)) {
        // If queue was empty, kickstart transmission
        if (was_empty) {
            CAN_Queue_Process();
        }
    }
}

void _fdcan_filter_IDList(uint32_t can_receive_id, uint8_t format, uint32_t filter_bank, uint32_t fifo)
{
	FDCAN_FilterTypeDef sFilterConfig;

	sFilterConfig.FilterType = FDCAN_FILTER_MASK;
	sFilterConfig.FilterIndex = filter_bank;

	if(format == 0){
		sFilterConfig.IdType = FDCAN_STANDARD_ID;
	}
	else if(format == 1){
		sFilterConfig.IdType = FDCAN_EXTENDED_ID;
	}
	sFilterConfig.FilterID1 = can_receive_id;
	sFilterConfig.FilterID2 = 0x7FF;

	if (fifo == 0)
	{
		sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
	}
	else if (fifo == 1)
  	{
   		sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO1;
	}

	if(HAL_FDCAN_ConfigFilter(&hfdcan2, &sFilterConfig) != HAL_OK) {
		//Error Handler Code to be added later to act as redundancy.
      Error_Handler();
    }

    /* Configure global filter to reject all non-matching frames */
    HAL_FDCAN_ConfigGlobalFilter(&hfdcan2, FDCAN_REJECT, FDCAN_REJECT, FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE);

    /* Configure Rx FIFO 0 watermark to 5 */
    HAL_FDCAN_ConfigFifoWatermark(&hfdcan2, FDCAN_CFG_RX_FIFO0, 1);

    /* Activate Rx FIFO 0 watermark notification */
    HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
}

void FDCAN_SETUP()
{
	_fdcan_filter_IDList(0x102, 0, 0, 0);
	_fdcan_filter_IDList(0x103, 0, 1, 0);
	HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_TX_COMPLETE, 0);

	if(HAL_FDCAN_Start(&hfdcan2) != HAL_OK)
	{
		Error_Handler();
	}
}

void _fdcan_transmit_on_can(uint32_t arbitration_id, uint8_t format, uint8_t * can_data, uint8_t dlc)
{
	FDCAN_TxHeaderTypeDef TxMsg;

	TxMsg.IdType 				= format;
	TxMsg.TxFrameType           = FDCAN_DATA_FRAME;
	TxMsg.Identifier            = arbitration_id;
	TxMsg.ErrorStateIndicator   = FDCAN_ESI_ACTIVE;
	TxMsg.BitRateSwitch         = FDCAN_BRS_OFF;
	TxMsg.FDFormat              = FDCAN_CLASSIC_CAN;
	TxMsg.TxEventFifoControl    = FDCAN_NO_TX_EVENTS;
	TxMsg.MessageMarker         = 0;
	TxMsg.DataLength			= dlc;

	if(HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &TxMsg, can_data) != HAL_OK)
		__HAL_FDCAN_CLEAR_FLAG(&hfdcan2, FDCAN_TXBC_TFQM);
}

void Send_Data_On_CAN_401(void)
{
	uint8_t can_data[8] = {0};

	uint16_t rpm_ref = (uint16_t)(FOC_MTPA_FF_U.Ref_Speed_mech_rpm * 10.0f);
	uint16_t rpm_fdbk = (uint16_t)((d.RPM + 3250.0f) * 10.0f);
	uint16_t Id = (uint16_t)(FOC_MTPA_FF_Y.Id + 512.0f);
	uint16_t Iq = (uint16_t)(FOC_MTPA_FF_Y.Iq + 512.0f);

	can_data[0] = (uint8_t)(rpm_ref & 0xFF);
	can_data[1] = (uint8_t)((rpm_ref >> 8) & 0xFF);
	can_data[2] = (uint8_t)(rpm_fdbk & 0xFF);
	can_data[3] = (uint8_t)((rpm_fdbk >> 8) & 0xFF);
	can_data[4] = (uint8_t)(Id & 0xFF);
	can_data[5] = (uint8_t)((Id >> 8) & 0xFF);
	can_data[6] = (uint8_t)(Iq & 0xFF);
	can_data[7] = (uint8_t)((Iq >> 8) & 0xFF);

	// _fdcan_transmit_on_can(0x401, 0, can_data, 0x08);
	CAN_Queue_Push_And_Kickstart(0x401, 0, can_data, 0x08);
}

void Send_Data_On_CAN_402(void)
{
	// Implement similar to Send_Data_On_CAN_401 with different data
	uint8_t can_data[8] = {0};

	uint16_t Vd = (uint16_t)(FOC_MTPA_FF_Y.Vd + SVM_VOLTAGE_LIMIT);
	uint16_t Vq = (uint16_t)(FOC_MTPA_FF_Y.Vq + SVM_VOLTAGE_LIMIT);
	uint16_t Iq_ref = (uint16_t)(FOC_MTPA_FF_Y.Iq_sat + 512.0f);
	uint16_t Id_ref = (uint16_t)(FOC_MTPA_FF_Y.Id_ref + 512.0f);
	uint16_t enc_cnt = (uint16_t)(d.encoder_count);

	// Fill can_data with appropriate values for message 402
	can_data[0] = (uint8_t)(Iq_ref & 0xFF);
	can_data[1] = (uint8_t)((Iq_ref >> 8) & 0xFF);
	can_data[2] = (uint8_t)(Id_ref & 0xFF);
	can_data[3] = (uint8_t)((Id_ref >> 8) & 0xFF);
	can_data[4] = (uint8_t)(Vd);
	can_data[5] = (uint8_t)(Vq);
	can_data[6] = (uint8_t)(enc_cnt & 0xFF);
	can_data[7] = (uint8_t)((enc_cnt >> 8) & 0xFF);

	// _fdcan_transmit_on_can(0x402, 0, can_data, 0x08);
	CAN_Queue_Push_And_Kickstart(0x402, 0, can_data, 0x08);
}

void Send_Data_On_CAN_403(void)
{
	uint8_t can_data[8] = {0};

	uint16_t bus_voltage = (uint16_t)(d.Vdc * 100.0f);
	uint16_t aux_voltage = (uint16_t)(d.Aux_dc * 100.0f);
	uint16_t motor_temp = (uint16_t)(d.Mtr_temp + 50.0f);
	uint16_t mc_temp = (uint16_t)(d.Mtc_temp + 50.0f);

	can_data[0] = (uint8_t)(bus_voltage & 0xFF);
	can_data[1] = (uint8_t)((bus_voltage >> 8) & 0xFF);
	can_data[2] = (uint8_t)(aux_voltage & 0xFF);
	can_data[3] = (uint8_t)((aux_voltage >> 8) & 0xFF);
	can_data[4] = (uint8_t)(motor_temp);
	can_data[5] = (uint8_t)(mc_temp);
	can_data[6] = (uint8_t)err;
	can_data[7] = (uint8_t)((uint16_t)FOC_MTPA_FF_Y.T_gen);

	// _fdcan_transmit_on_can(0x403, 0, can_data, 0x08);
	CAN_Queue_Push_And_Kickstart(0x403, 0, can_data, 0x08);
}

void Send_Data_On_CAN_404(void) {
	uint8_t can_data[8] = {0};

	uint16_t Ld_LUT = (uint16_t)(FOC_MTPA_FF_U.Ld * 1.0E8f);
	uint16_t Lq_LUT = (uint16_t)(FOC_MTPA_FF_U.Lq * 1.0E7f);
	uint16_t lambda_LUT = (uint16_t)(FOC_MTPA_FF_U.Lambda * 1.0E5f);

	can_data[0] = (uint8_t)(Ld_LUT & 0xFF);
	can_data[1] = (uint8_t)((Ld_LUT >> 8) & 0xFF);
	can_data[2] = (uint8_t)(Lq_LUT & 0xFF);
	can_data[3] = (uint8_t)((Lq_LUT >> 8) & 0xFF);
	can_data[4] = (uint8_t)(lambda_LUT & 0xFF);
	can_data[5] = (uint8_t)((lambda_LUT >> 8) & 0xFF);
	can_data[6] = (uint8_t)((uint16_t)d.cycles & 0xFF);
	can_data[7] = (uint8_t)(((uint16_t)d.cycles >> 8) & 0xFF);

	// _fdcan_transmit_on_can(0x404, 0, can_data, 0x08);
	CAN_Queue_Push_And_Kickstart(0x404, 0, can_data, 0x08);
}

void Send_Data_On_CAN_405(void) {
	uint8_t can_data[8] = {0};

	can_data[0] = (uint8_t)(fnr_state);
	can_data[1] = (uint8_t)(cS);
	if (rtmGetErrorStatus(FOC_MTPA_FF_M) == "Overrun") {
		can_data[2] = 0x01;
	} else {
		can_data[2] = 0x00;
	}

	CAN_Queue_Push_And_Kickstart(0x405, 0, can_data, 0x08);
}
