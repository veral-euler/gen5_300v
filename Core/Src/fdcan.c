#include "fdcan.h"

extern FDCAN_HandleTypeDef hfdcan2;

void FDCAN_SETUP()
{
	if(HAL_FDCAN_Start(&hfdcan2) != HAL_OK)
	{
		Error_Handler();
	};
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

	uint16_t rpm_ref = (uint16_t)(FOC_LivGguard_U.Ref_Speed_mech_rpm * 10.0f);
	uint16_t rpm_fdbk = (uint16_t)((d.RPM + 3250.0f) * 10.0f);
	uint16_t Id = (uint16_t)(FOC_LivGguard_Y.Id + 512.0f);
	uint16_t Iq = (uint16_t)(FOC_LivGguard_Y.Iq + 512.0f);

	can_data[0] = (uint8_t)(rpm_ref & 0xFF);
	can_data[1] = (uint8_t)((rpm_ref >> 8) & 0xFF);
	can_data[2] = (uint8_t)(rpm_fdbk & 0xFF);
	can_data[3] = (uint8_t)((rpm_fdbk >> 8) & 0xFF);
	can_data[4] = (uint8_t)(Id & 0xFF);
	can_data[5] = (uint8_t)((Id >> 8) & 0xFF);
	can_data[6] = (uint8_t)(Iq & 0xFF);
	can_data[7] = (uint8_t)((Iq >> 8) & 0xFF);

	_fdcan_transmit_on_can(0x401, 0, can_data, 0x08);
}

void Send_Data_On_CAN_402(void)
{
	// Implement similar to Send_Data_On_CAN_401 with different data
	uint8_t can_data[8] = {0};

	uint16_t Vd = (uint16_t)(FOC_LivGguard_Y.Vd + SVM_VOLTAGE_LIMIT);
	uint16_t Vq = (uint16_t)(FOC_LivGguard_Y.Vq + SVM_VOLTAGE_LIMIT);
	uint16_t Iq_ref = (uint16_t)(FOC_LivGguard_Y.Iq_ref + 512.0f);
	uint16_t Id_ref = (uint16_t)(FOC_LivGguard_Y.Id_ref + 512.0f);
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

	_fdcan_transmit_on_can(0x402, 0, can_data, 0x08);
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
	can_data[6] = 0;
	can_data[7] = 0;

	_fdcan_transmit_on_can(0x403, 0, can_data, 0x08);
}
