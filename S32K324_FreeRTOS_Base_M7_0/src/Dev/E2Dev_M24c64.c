/*
 * E2Dev_M24c64.c
 *
 *  Created on: 2026.02.10
 *      Author: April
 */

#include "E2Dev_M24c64.h"

#define EEPROM_DEV_ADDR			0x50
#define EEPROM_PAGE_SIZE		32
#define I2C_CHANNEL_EEPROM		0

/* 封装 I2C 发送逻辑 */
Std_ReturnType bsp_eeprom_i2c_send(uint8 *buf, uint32 len)
{
    I2c_RequestType req;
    req.SlaveAddress         = (EEPROM_DEV_ADDR);
    req.BitsSlaveAddressSize = FALSE;
    req.ExpectNack           = FALSE;
    req.RepeatedStart        = FALSE;
    req.BufferSize           = len;
    req.DataDirection        = I2C_SEND_DATA;
    req.DataBuffer           = buf;

    return I2c_SyncTransmit(I2C_CHANNEL_EEPROM, &req);
}


Std_ReturnType dev_eeprom_write_byte(uint16 mem_addr, uint8 data)
{
    uint8 buf[3];
    buf[0] = (uint8)(mem_addr >> 8);   // 地址高8位
    buf[1] = (uint8)(mem_addr & 0xFF); // 地址低8位
    buf[2] = data;

    Std_ReturnType ret = bsp_eeprom_i2c_send(buf, 3);

    // 只要有写动作，必须延时 5ms
    vTaskDelay(pdMS_TO_TICKS(5));
    return ret;
}


Std_ReturnType dev_eeprom_write_page(uint16 mem_addr, uint8 *pData, uint8 len)
{
    uint8 buf[34]; // 2字节地址 + 32字节数据
    
    if(len > 32) len = 32; // 硬件限制

    buf[0] = (uint8)(mem_addr >> 8);
    buf[1] = (uint8)(mem_addr & 0xFF);
    
    // 复制数据到缓冲区
    for(uint8 i = 0; i < len; i++)
    {
        buf[i + 2] = pData[i];
    }

    // 发送整个包 (len + 2个地址字节)
    Std_ReturnType ret = bsp_eeprom_i2c_send(buf, len + 2);
    
    // 只要有写动作，必须延时 5ms
    vTaskDelay(pdMS_TO_TICKS(5)); 
    
    return ret;
}


Std_ReturnType dev_eeprom_read_byte(uint16 mem_addr, uint8 *pData)
{
    I2c_RequestType req;
    uint8 addr_buf[2];
    addr_buf[0] = (uint8)(mem_addr >> 8);
    addr_buf[1] = (uint8)(mem_addr & 0xFF);

    // 1. 发送地址 (Dummy Write)
    req.SlaveAddress         = (EEPROM_DEV_ADDR);
    req.BitsSlaveAddressSize = FALSE;
    req.ExpectNack           = FALSE;
    req.RepeatedStart        = TRUE;  // 关键：开启重复起始位
    req.BufferSize           = 2;
    req.DataDirection        = I2C_SEND_DATA;
    req.DataBuffer           = addr_buf;
    I2c_SyncTransmit(I2C_CHANNEL_EEPROM, &req);

    // 2. 接收数据
    req.RepeatedStart        = FALSE;
    req.BufferSize           = 1;
    req.DataDirection        = I2C_RECEIVE_DATA;
    req.DataBuffer           = pData;
    
    return I2c_SyncTransmit(I2C_CHANNEL_EEPROM, &req);
}


/**
 * @brief 从 EEPROM 连续读取数据
 * @param mem_addr 起始存储地址 (0x0000 - 0x1FFF)
 * @param pBuf 存放读取数据的缓冲区
 * @param len 要读取的长度 (不受32字节限制)
 */
Std_ReturnType dev_eeprom_read_multi(uint16 mem_addr, uint8 *pBuf, uint32 len)
{
    I2c_RequestType req;
    uint8 addr_buf[2];

    addr_buf[0] = (uint8)(mem_addr >> 8);
    addr_buf[1] = (uint8)(mem_addr & 0xFF);

    // 1. 发送伪写（Dummy Write）：告知 EEPROM 我要从哪个地址开始读
    req.SlaveAddress         = (EEPROM_DEV_ADDR);
    req.BitsSlaveAddressSize = FALSE;
    req.ExpectNack           = FALSE;
    req.RepeatedStart        = TRUE;  // 必须使用重复起始位，不释放总线
    req.BufferSize           = 2;
    req.DataDirection        = I2C_SEND_DATA;
    req.DataBuffer           = addr_buf;
    I2c_SyncTransmit(I2C_CHANNEL_EEPROM, &req);

    // 2. 连续接收数据：此时只需要给出长度，EEPROM 会自动把地址往后累加
    req.RepeatedStart        = FALSE;
    req.BufferSize           = len;   // 这里的 len 可以是 32, 64 甚至更多
    req.DataDirection        = I2C_RECEIVE_DATA;
    req.DataBuffer           = pBuf;
    
    return I2c_SyncTransmit(I2C_CHANNEL_EEPROM, &req);
}

/* 1000ms tsak EEPROM Routine */
void dev_eeprom_1000ms_test(uint32 vTask1000ms_cnt)
{
        (void)vTask1000ms_cnt;
    	/* V1.0 EEPROM write/read byte test */
		// uint8 test_val = 0;
		// dev_eeprom_write_byte(0x0000, (uint8)vTask1000ms_cnt);
		// dev_eeprom_read_byte(0x0000, &test_val);
		/* V1.0 EEPROM end */

		/* V2.0 EEPROM write/read page test */
		// uint8 buf[4];
		// buf[0] = (vTask1000ms_cnt >> 24) & 0xFF;
		// buf[1] = (vTask1000ms_cnt >> 16) & 0xFF;
		// buf[2] = (vTask1000ms_cnt >> 8)  & 0xFF;
		// buf[3] = (vTask1000ms_cnt >> 0)  & 0xFF;
		// dev_eeprom_write_page(0x0000, buf, 4);

		// // read page test
		// uint8 rbuf[4];
		// uint32 counter_read;
		// dev_eeprom_read_multi(0x0000, rbuf, 4);
		// counter_read = ((uint32)rbuf[0] << 24) |
		// 			((uint32)rbuf[1] << 16) |
		// 			((uint32)rbuf[2] << 8)  |
		// 			((uint32)rbuf[3]);
		/* V2.0 EEPROM end */
}