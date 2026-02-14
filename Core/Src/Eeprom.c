#include "Eeprom.h"

extern I2C_HandleTypeDef hi2c2;

static uint8_t crc8(const uint8_t *data, uint8_t len){
  uint8_t crc = 0;

  for(uint8_t i = 0; i < len; i++){
    crc ^= data[i];
  }
  return crc;
}

uint8_t EEPROM_Write_Page0(uint16_t offset){
  uint8_t page[5];

  page[0] = EEPROM_MAGIC_NUM;

  page[1] = (offset >> 8) & 0xFF;
  page[2] = (offset >> 0) & 0xFF;

  page[3] = 1;

  page[4] = crc8(page, 4);

  return EEPROM_Write(0x00, page, 5);
}

uint8_t EEPROM_Read_Page0(uint16_t* offset){
  uint8_t page[5];

  if(EEPROM_Read(0x00, page, 5) != HAL_OK){
    return HAL_ERROR;
  }

  if (page[3] == 1) {
    cS = ANGLE_CALIB_DONE;
    d.start_alignment = 0;
    d.end_alignment = 1;
  } else {
    cS = INIT;
  }

  uint8_t calc_crc = crc8(page, 4);

  if(calc_crc != page[4]){
    return HAL_ERROR;
  }

  if(page[0] != EEPROM_MAGIC_NUM){
    return EEPROM_NO_MAGIC_NUM;
  }

  *offset = (page[1] << 8) | page[2];

  return HAL_OK;
}

void Read_EEPROM_at_init(void) {
  if (EEPROM_Read_Page0(&d.offset_angle_elec_16bit) == HAL_OK) {
    d.offset_angle_elec = (float)d.offset_angle_elec_16bit / 100.0f;
  } else {
    er.eeprom_read_error = 1;
    err = EEPROM_READ_ERROR;
    d.offset_angle_elec = OFFSET_CALC_ELEC;
  }
}

uint8_t EEPROM_Write(uint16_t mem_addr, uint8_t* data, uint16_t size){
  /* 1. I2C Write*/
  if(HAL_I2C_Mem_Write(&hi2c2, EEPROM_ADDRESS, mem_addr, I2C_MEMADD_SIZE_8BIT, data, size, HAL_MAX_DELAY) != HAL_OK){
    return HAL_ERROR;
  }

  /*2. ACK POLLING*/
  while (HAL_I2C_IsDeviceReady(&hi2c2, EEPROM_ADDRESS, 1, 5) != HAL_OK){

  }

  return HAL_OK;
}

uint8_t EEPROM_Read(uint16_t Mem_Addr, uint8_t* data, uint16_t size){
  if(HAL_I2C_Mem_Read(&hi2c2, EEPROM_ADDRESS, Mem_Addr, I2C_MEMADD_SIZE_8BIT, data, size, HAL_MAX_DELAY) != HAL_OK){
    return HAL_ERROR;
  }

  return HAL_OK;
}
