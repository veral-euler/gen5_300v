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
    HAL_FDCAN_ConfigFifoWatermark(&hfdcan2, FDCAN_CFG_RX_FIFO0, 8);

    /* Activate Rx FIFO 0 watermark notification */
    HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
}

void FDCAN_SETUP()
{
	_fdcan_filter_IDList(0x102, 0, 0, 0);
	_fdcan_filter_IDList(0x103, 0, 1, 0);
	_fdcan_filter_IDList(0x104, 0, 2, 0);
	_fdcan_filter_IDList(0x105, 0, 3, 0);
	_fdcan_filter_IDList(0x106, 0, 4, 0);
	_fdcan_filter_IDList(0x107, 0, 5, 0);
	_fdcan_filter_IDList(0x108, 0, 6, 0);
	_fdcan_filter_IDList(0x109, 0, 7, 0);
	_fdcan_filter_IDList(0x110, 0, 8, 0);
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

#if DEBUG_CAN_ID
void Send_Data_On_CAN_401(void)
{
	uint8_t can_data[8] = {0};

	uint16_t rpm_ref = (uint16_t)(FOC_MTPA_FWC_FF_U.Ref_Speed_mech_rpm * 10.0f);
	uint16_t rpm_fdbk = (uint16_t)(fabsf(d.RPM) * 10.0f);
	uint16_t Id = (uint16_t)(FOC_MTPA_FWC_FF_Y.Id + 512.0f);
	uint16_t Iq = (uint16_t)(FOC_MTPA_FWC_FF_Y.Iq + 512.0f);

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

	uint16_t Vd = (uint16_t)(FOC_MTPA_FWC_FF_Y.Vd + SVM_VOLTAGE_LIMIT);
	uint16_t Vq = (uint16_t)(FOC_MTPA_FWC_FF_Y.Vq + SVM_VOLTAGE_LIMIT);
	uint16_t Iq_ref = (uint16_t)(FOC_MTPA_FWC_FF_Y.Iq_ref_final + 512.0f);
	uint16_t Id_ref = (uint16_t)(FOC_MTPA_FWC_FF_Y.Id_ref_final + 512.0f);
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
	can_data[7] = (uint8_t)((uint16_t)(fabsf(FOC_MTPA_FWC_FF_Y.Iq_gen) * CURR_TORQUE_RATIO));

	// _fdcan_transmit_on_can(0x403, 0, can_data, 0x08);
	CAN_Queue_Push_And_Kickstart(0x403, 0, can_data, 0x08);
}

void Send_Data_On_CAN_404(void) {
	uint8_t can_data[8] = {0};

	uint16_t Ld_LUT = (uint16_t)(FOC_MTPA_FWC_FF_U.Motor_Parameters.Ld * 1.0E8f);
	uint16_t Lq_LUT = (uint16_t)(FOC_MTPA_FWC_FF_U.Motor_Parameters.Lq * 1.0E7f);
	uint16_t lambda_LUT = (uint16_t)(FOC_MTPA_FWC_FF_U.Motor_Parameters.Lambda * 1.0E5f);

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

	uint16_t can_offsetAngle = (uint16_t)(d.offset_angle_elec * 1000.0f);
	uint16_t can_thrVoltage = (uint16_t)(d.throttle_v * 1000.0f);

	can_data[0] = (uint8_t)(fnr_state);
	can_data[1] = (uint8_t)(cS);
	if (rtmGetErrorStatus(FOC_MTPA_FWC_FF_M) == "Overrun") {
		can_data[2] = 0x01;
	} else {
		can_data[2] = 0x00;
	}
	can_data[3] = (uint8_t)(pw_state);
	can_data[4] = (uint8_t)(can_offsetAngle & 0xFF);
	can_data[5] = (uint8_t)((can_offsetAngle >> 8) & 0xFF);
	can_data[6] = (uint8_t)(can_thrVoltage & 0xFF);
	can_data[7] = (uint8_t)((can_thrVoltage >> 8) & 0xFF);

	CAN_Queue_Push_And_Kickstart(0x405, 0, can_data, 0x08);
}

void Send_Data_On_CAN_406(void) {
	uint8_t can_data[8] = {0};

	uint16_t can_tx_Kfw = (uint16_t)(can_d.Kfw * 1.0E3f);
	uint16_t can_tx_Kaw = (uint16_t)(can_d.Kaw * 1.0E3f);

	can_data[0] = (uint8_t)(can_tx_Kfw & 0xFF);
	can_data[1] = (uint8_t)((can_tx_Kfw >> 8) & 0xFF);
	can_data[2] = (uint8_t)(can_tx_Kaw & 0xFF);
	can_data[3] = (uint8_t)((can_tx_Kaw >> 8) & 0xFF);

	CAN_Queue_Push_And_Kickstart(0x406, 0, can_data, 0x08);
}

void Send_Data_On_CAN_407(void) {
	uint8_t can_data[8] = {0};

	uint16_t can_tx_speed_kp = (uint16_t)(FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Kp_speed_PID_MTPA * 1.0E2f);
	uint16_t can_tx_speed_ki = (uint16_t)(FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Ki_speed_PID_MTPA * 1.0E2f);
	uint16_t can_tx_speed_kd = (uint16_t)(FOC_MTPA_FWC_FF_U.MTPA_PID.Speed_PID_MTPA.Kd_speed_PID_MTPA * 1.0E5f);

	can_data[0] = (uint8_t)(can_tx_speed_kp & 0xFF);
	can_data[1] = (uint8_t)((can_tx_speed_kp >> 8) & 0xFF);
	can_data[2] = (uint8_t)(can_tx_speed_ki & 0xFF);
	can_data[3] = (uint8_t)((can_tx_speed_ki >> 8) & 0xFF);
	can_data[4] = (uint8_t)(can_tx_speed_kd & 0xFF);
	can_data[5] = (uint8_t)((can_tx_speed_kd >> 8) & 0xFF);

	CAN_Queue_Push_And_Kickstart(0x407, 0, can_data, 0x08);
}

void Send_Data_On_CAN_408(void) {
	uint8_t can_data[8] = {0};

	uint16_t can_tx_speed_kp = (uint16_t)(FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Kp_flux_PID_MTPA * 1.0E2f);
	uint16_t can_tx_speed_ki = (uint16_t)(FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Ki_flux_PID_MTPA * 1.0E2f);
	uint16_t can_tx_speed_kd = (uint16_t)(FOC_MTPA_FWC_FF_U.MTPA_PID.Flux_PID_MTPA.Kd_flux_PID_MTPA * 1.0E5f);

	can_data[0] = (uint8_t)(can_tx_speed_kp & 0xFF);
	can_data[1] = (uint8_t)((can_tx_speed_kp >> 8) & 0xFF);
	can_data[2] = (uint8_t)(can_tx_speed_ki & 0xFF);
	can_data[3] = (uint8_t)((can_tx_speed_ki >> 8) & 0xFF);
	can_data[4] = (uint8_t)(can_tx_speed_kd & 0xFF);
	can_data[5] = (uint8_t)((can_tx_speed_kd >> 8) & 0xFF);

	CAN_Queue_Push_And_Kickstart(0x408, 0, can_data, 0x08);
}

void Send_Data_On_CAN_409(void) {
	uint8_t can_data[8] = {0};

	uint16_t can_tx_speed_kp = (uint16_t)(FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Kp_torque_PID_MTPA * 1.0E2f);
	uint16_t can_tx_speed_ki = (uint16_t)(FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Ki_torque_PID_MTPA * 1.0E2f);
	uint16_t can_tx_speed_kd = (uint16_t)(FOC_MTPA_FWC_FF_U.MTPA_PID.Torque_PID_MTPA.Kd_torque_PID_MTPA * 1.0E5f);

	can_data[0] = (uint8_t)(can_tx_speed_kp & 0xFF);
	can_data[1] = (uint8_t)((can_tx_speed_kp >> 8) & 0xFF);
	can_data[2] = (uint8_t)(can_tx_speed_ki & 0xFF);
	can_data[3] = (uint8_t)((can_tx_speed_ki >> 8) & 0xFF);
	can_data[4] = (uint8_t)(can_tx_speed_kd & 0xFF);
	can_data[5] = (uint8_t)((can_tx_speed_kd >> 8) & 0xFF);

	CAN_Queue_Push_And_Kickstart(0x409, 0, can_data, 0x08);
}
#endif

#if VH_CAN_ID
/* Vehicle CAN Matrix */
/*****************************************************************************/
void Send_on_CAN_705(float Mtr_Temp, float Cntrl_Temp)
{
	uint8_t data[8] = {0};

	float mt_t = Mtr_Temp + 50.0f;
	float ct_t = Cntrl_Temp + 50.0f;
	float can_iq = FOC_MTPA_FWC_FF_Y.Iq + 512.0f;
	float can_id = FOC_MTPA_FWC_FF_Y.Id + 512.0f;
	float offset_angle = d.offset_angle_elec * 100.0f;

	data[0] = (uint8_t)((uint16_t)mt_t);
	data[1] = (uint8_t)((uint16_t)ct_t);

	data[2] = (uint8_t)((uint16_t)can_iq & 0x00FF);
	data[3] = (uint8_t)(((uint16_t)can_iq & 0xFF00) >> 8);

	data[4] = (uint8_t)((uint16_t)can_id & 0x00FF);
	data[5] = (uint8_t)(((uint16_t)can_id & 0xFF00) >> 8);

	data[6] = (uint8_t)((uint16_t)offset_angle & 0x00FF);
	data[7] = (uint8_t)(((uint16_t)offset_angle & 0xFF00) >> 8);

	CAN_Queue_Push_And_Kickstart(0x705, 0, data, 0x08);
}

void Send_on_CAN_706(float bus_voltage, float Speed_KMPH, uint8_t error_c)
{
	uint8_t data[8] = {0};

	if (fnr_state == REVERSE)
		data[0] = 0x04;
	else if (fnr_state == NEUTRAL)
		data[0] = 0x01;

	if (pw_state == SPORTS && fnr_state == FORWARD) {
		data[0] = 0x08;
	} else if (pw_state == ECO && fnr_state == FORWARD) {
		data[0] = 0x02;
	}

	if (d.regen_flag) {
		data[1] |= (1 << 2);
	} else {
		data[1] &= ~(1 << 2);
	}

	if (bus_voltage <= 40)
		data[1] |= (1 << 3);
	else
		data[1] &= ~(1 << 3);
	
	data[1] |= (1 << 5);

	if (er.mtc_temp_ot_error) {
		data[1] |= (1 << 4);
	}

	data[3] = error_c;

	Speed_KMPH *= 10.0f;
	data[4] = (uint8_t)((uint16_t)(Speed_KMPH) & 0x00FF);
	data[5] = (uint8_t)(((uint16_t)(Speed_KMPH) & 0xFF00) >> 8);

	// data[6] = (uint8_t)((uint16_t)(CAN_Counter) & 0x00FF);
	// data[7] = (uint8_t)(((uint16_t)(CAN_Counter) & 0xFF00) >> 8);

	CAN_Queue_Push_And_Kickstart(0x706, 0, data, 0x08);
}

void Send_on_CAN_708(uint8_t error_c_1, uint8_t error_c_2)
{
	uint8_t data[8] = {0};

	float theta_elec = d.elec_angle * 100.0f;
	uint16_t encoder_count = (uint16_t)(TIM2->CNT);

	data[0] = error_c_1;
	data[1] = error_c_2;

	if (d.ctlr_derate_flag) {
		data[1] |= (1 << 3);
	} else {
		data[1] &= ~(1 << 3);
	}

	if (d.motor_derate_flag) {
		data[1] |= (1 << 4);
	} else {
		data[1] &= ~(1 << 4);
	}

	data[2] = (uint8_t)((uint16_t)theta_elec & 0x00FF);
	data[3] = (uint8_t)(((uint16_t)theta_elec & 0xFF00) >> 8);

	data[4] = (uint8_t)(encoder_count & 0x00FF);
	data[5] = (uint8_t)((encoder_count & 0xFF00) >> 8);

	// data[6] = (uint8_t)(CAN_Error_Occured);

	CAN_Queue_Push_And_Kickstart(0x708, 0, data, 0x08);
}

void Send_on_CAN_709(uint8_t historic_errors)
{
	uint8_t data[8] = {0};
	UNUSED(historic_errors);


	CAN_Queue_Push_And_Kickstart(0x709, 0, data, 0x08);
}

void Send_on_CAN_710(float throttle_percent, float throttle_voltage) {
	uint8_t data[8] = {0};

	data[0] = (uint8_t)((uint16_t)throttle_percent);
	data[3] = (uint8_t)((uint16_t)(throttle_voltage * 10.0f));
	data[4] = 0x00;
	// data[6] = OTA_State;
	// data[7] = OTA_Source_ECU; 

	CAN_Queue_Push_And_Kickstart(0x710, 0, data, 0x08);
}

void Send_on_CAN_715(float RPM, float bus_voltage, float lv_12v_voltage)
{
	uint8_t data[8] = {0};

	data[3] = (uint8_t)((uint16_t)d.Vdc);
	data[4] = (uint8_t)((uint16_t)bus_voltage);
	data[5] = (uint8_t)((uint16_t)lv_12v_voltage);
	data[6] = (uint8_t)((uint16_t)RPM & 0x00FF);
	data[7] = (uint8_t)(((uint16_t)RPM & 0xFF00) >> 8);

	CAN_Queue_Push_And_Kickstart(0x715, 0, data, 0x08);
}

void Send_on_CAN_716(float vrms, float irms)
{
	uint8_t data[8] = {0};

	float pack_dc = d.pack_current + 500.0f;

	data[2] = (uint8_t)((uint16_t)pack_dc & 0x00FF);
	data[3] = (uint8_t)(((uint16_t)pack_dc & 0xFF00) >> 8);
	data[4] = (uint8_t)((uint16_t)((vrms/d.Vdc) * 100.0f));
	data[5] = (uint8_t)((uint16_t)vrms);
	data[6] = (uint8_t)((uint16_t)irms & 0x00FF);
	data[7] = (uint8_t)(((uint16_t)irms & 0xFF00) >> 8);

	CAN_Queue_Push_And_Kickstart(0x716, 0, data, 0x08);
}

void Send_on_CAN_717(float rpm)
{
	uint8_t data[8] = {0};

	volatile float Hz = (rpm * POLEPAIRS * 2.0f) / 120.0f;

	data[0] = (uint8_t)((uint16_t)Hz & 0x00FF);
	data[1] = (uint8_t)(((uint16_t)Hz & 0xFF00) >> 8);

	// data[2] = (uint8_t)((uint16_t)L_g.Is_ref_woDCLO & 0x00FF);
	// data[3] = (uint8_t)(((uint16_t)L_g.Is_ref_woDCLO & 0xFF00) >> 8);

	// data[4] = (uint8_t)((uint16_t)L_g.Is_ref_wDCLO & 0x00FF);
	// data[5] = (uint8_t)(((uint16_t)L_g.Is_ref_wDCLO & 0xFF00) >> 8);

	CAN_Queue_Push_And_Kickstart(0x717, 0, data, 0x08);
}

void Send_on_CAN_724(float torque_ref)
{
	uint8_t data[8] = {0};

	float can_vq = FOC_MTPA_FWC_FF_Y.Vq + 62.0f;
	float can_vd = FOC_MTPA_FWC_FF_Y.Vd + 62.0f;
	torque_ref *= 10.0f;

	data[0] = (uint8_t)((uint16_t)torque_ref & 0x00FF);
	data[1] = (uint8_t)(((uint16_t)torque_ref & 0xFF00) >> 8);

	data[2] = (uint8_t)((uint16_t)can_vq & 0x00FF);
	data[3] = (uint8_t)(((uint16_t)can_vq & 0xFF00) >> 8);

	data[4] = (uint8_t)((uint16_t)can_vd & 0x00FF);
	data[5] = (uint8_t)(((uint16_t)can_vd & 0xFF00) >> 8);

	#if CURR_APP1
		data[6] = 0x01;
	#endif

	#if CURR_APP2
		data[6] = 0x02;
	#endif

	data[7] = 0x00;

	CAN_Queue_Push_And_Kickstart(0x724, 0, data, 0x08);
}

void Send_on_CAN_726()
{
	uint8_t data[8] = {0};

	data[0] = (uint8_t)(CONFIG_VERSION_MAJOR);
	data[1] = (uint8_t)(CONFIG_VERSION_MINOR);
	data[2] = (uint8_t)(CONFIG_VERSION_SUBMINOR);
	data[3] = 0xE2;
	data[4] = 0x58;
	data[5] = (uint8_t)(FIRMWARE_VERSION_MAJOR);
	data[6] = (uint8_t)(FIRMWARE_VERSION_MINOR);
	data[7] = (uint8_t)(FIRMWARE_VERSION_SUBMINOR);

	CAN_Queue_Push_And_Kickstart(0x726, 0, data, 0x08);
}
#endif
