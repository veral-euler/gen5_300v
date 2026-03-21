#ifndef __EEPROM_H
#define __EEPROM_H

#include "main.h"

#define EEPROM_ADDRESS          0xA0 // Adjust based on your EEPROM's I2C address
#define EEPROM_MAGIC_NUM        0x69
#define EEPROM_NO_MAGIC_NUM     2
#define EEPROM_PAGE_SIZE        8
#define EEPROM_WRITE_TIMEOUT    5

/* EEPROM Mem Layout:
        Byte    Data
Page 0  0       EEPROM_MAGIC_NUM
        1       Offset cw
        2       Offset cw
        3       Offset ccw
        4       Offset ccw
        5       CALIB DONE bit
        6       CRC
*/

uint8_t EEPROM_Write(uint16_t addr, uint8_t *data, uint16_t size);
uint8_t EEPROM_Read(uint16_t addr, uint8_t *data, uint16_t size);
void Read_EEPROM_at_init(void);

uint8_t EEPROM_Write_Page0(uint16_t offset_cw, uint16_t offset_ccw);
uint8_t EEPROM_Read_Page0(uint16_t* offset_cw, uint16_t* offset_ccw);

#endif
