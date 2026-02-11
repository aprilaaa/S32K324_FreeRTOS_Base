/**************************************************************************
* @Copyright: (c) 2024 by wang All Rights Reserved.
* @version: V1.0.0
* @Author: wang
* @Date: 2024-11-05 09:06:00
* @LastEditors: wang
* @LastEditTime: 2024-11-10 21:53:28
* @FilePath: \src\dev\dev_ssd1306.h
* @Description: 
**************************************************************************/


#ifndef __DEV_SSD1306_H__
#define __DEV_SSD1306_H__


#include "Platform_Types.h"
#include "CDD_I2c_Types.h"
#include "Std_Types.h"
#include "CDD_I2c.h"

/**************************************************************************
  Global Function Prototypes
**************************************************************************/
Std_ReturnType bsp_i2c0_send(uint32 addr, uint8 *buf, uint32 len);
Std_ReturnType dev_ssd1306_init(void);
sint32 dev_ssd1306_set_pos(uint32 x, uint32 y);
sint32 dev_ssd1306_draw_pattern(uint8 pattern);
sint32 dev_ssd1306_draw_bmp(uint32 x0,uint32 y0,uint32 x1,uint32 y1, uint8* bmp);
sint32 dev_ssd1306_display_on(void);
sint32 dev_ssd1306_display_off(void);
void dev_ssd1306_show_char(uint8 type, uint8 x, uint8 y, uint8 chr);
void dev_ssd1306_show_string(uint8 type, uint8 x,uint8 y,uint8 *chr);



#endif

