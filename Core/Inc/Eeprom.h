#ifndef __EEPROM_H
#define __EEPROM_H

#include "main.h"

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
