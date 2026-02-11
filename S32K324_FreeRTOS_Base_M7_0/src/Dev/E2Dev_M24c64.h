/*
 * E2Dev_M24c64.h
 *
 *  Created on: 2026.02.10
 *      Author: April
 */


#ifndef E2DEV_M24C64_H_
#define E2DEV_M24C64_H_

#include "Platform_Types.h"
#include "CDD_I2c_Types.h"
#include "Std_Types.h"
#include "CDD_I2c.h"
#include "FreeRTOS.h"
#include "task.h"

Std_ReturnType bsp_eeprom_i2c_send(uint8 *buf, uint32 len);                         
Std_ReturnType dev_eeprom_write_byte(uint16 mem_addr, uint8 data);
Std_ReturnType dev_eeprom_write_page(uint16 mem_addr, uint8 *pData, uint8 len);
Std_ReturnType dev_eeprom_read_byte(uint16 mem_addr, uint8 *pData);
Std_ReturnType dev_eeprom_read_multi(uint16 mem_addr, uint8 *pBuf, uint32 len);

#endif /* E2DEV_M24C64_H_ */
