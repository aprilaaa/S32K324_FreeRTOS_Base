/*
 * OsTask.c
 *
 *  Created on: 2026年1月27日
 *      Author: li
 */



#include "OsTask.h"


TaskHandle_t xHandle1ms, xHandle10ms, xHandle100ms, xHandle1000ms;
uint32 vTask1ms_cnt, vTask10ms_cnt, vTask100ms_cnt, vTask1000ms_cnt;
extern volatile uint8 VarNotification_0;
extern Adc_ValueGroupType AdcReadGroupResult;

uint8 Can_au8Sdu8bytes[8U] = {0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08};

/* 定义要发送给 SSD1306 的数据（例如初始化序列或清屏命令） */
uint8 ssd1306_cmd_buffer[] = {0x00, 0xAF}; // 0x00: 控制字节(命令), 0xAF: 开启显示命令



Can_PduType Can_CreatePduInfo(Can_IdType id, PduIdType swPduHandle, uint8 length, uint8* sdu)
{
    Can_PduType PduInfo;

    PduInfo.id = id;
    PduInfo.swPduHandle = swPduHandle;
    PduInfo.length = length;
    PduInfo.sdu = sdu;

    return PduInfo;
}


/* --- 1ms task --- */
void vTask1ms(void *pvParameters)
{
	(void)pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
    	vTask1ms_cnt++;

    	 if(Dio_ReadChannel(DioConf_DioChannel_DioChannel_KEY1) == 1)
    	 {
    	 	Dio_FlipChannel(DioConf_DioChannel_DioChannel_LEDR);
    	 }
    	 else
    	 {
    	 	Dio_WriteChannel(DioConf_DioChannel_DioChannel_LEDR, STD_HIGH);
    	 }


        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1));
    }
}

/* --- 10ms task --- */
void vTask10ms(void *pvParameters)
{
	(void)pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
		vTask10ms_cnt++;
		Can_43_FLEXCAN_MainFunction_Write();
		Can_43_FLEXCAN_MainFunction_Read();

		if(Dio_ReadChannel(DioConf_DioChannel_DioChannel_KEY2) == 1)
		{
			Dio_FlipChannel(DioConf_DioChannel_DioChannel_LEDG);
		}
		else
		{
			Dio_WriteChannel(DioConf_DioChannel_DioChannel_LEDG, STD_HIGH);
		}

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(10));
    }
}

/* --- 100ms task --- */
void vTask100ms(void *pvParameters)
{
	(void)pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
		vTask100ms_cnt++;
		if(Dio_ReadChannel(DioConf_DioChannel_DioChannel_KEY3) == 1)
		{
			Dio_FlipChannel(DioConf_DioChannel_DioChannel_LEDR);
			Dio_FlipChannel(DioConf_DioChannel_DioChannel_LEDG);
		}

		/* Can Test */
		static Can_PduType Can_PduInfo;
		static uint32 CanTx_cnt = 0;
		extern uint32 CanRx_cnt;
		Can_PduInfo = Can_CreatePduInfo(0U, 0U, 8U, Can_au8Sdu8bytes);
		if(E_OK == Can_43_FLEXCAN_Write(Can_43_FLEXCANConf_CanHardwareObject_CAN00_MailBox1_TX, &Can_PduInfo))
		{
			CanTx_cnt++;
		}


		/* ADC Test */
		Adc_StartGroupConversion(AdcGroupSoftwareOneShot);
		while (VarNotification_0 == 0u){}
		VarNotification_0 = 0;
		Adc_ReadGroup(AdcGroupSoftwareOneShot, &AdcReadGroupResult);

		/* OLED Test */
		char buf[20];
		sprintf(buf, "CNT_S:%u", (unsigned int)vTask1000ms_cnt);
		dev_ssd1306_show_string(16, 0, 0, (uint8 *)buf);

		sprintf(buf, "ADC_V:%-5u", (unsigned int)AdcReadGroupResult);
		dev_ssd1306_show_string(16, 0, 2, (uint8 *)buf);

		// sprintf(buf, "CANRX:%u", (unsigned int)CanRx_cnt);
		// dev_ssd1306_show_string(16, 0, 4, (uint8 *)buf);

		// sprintf(buf, "CANTX:%u", (unsigned int)CanTx_cnt);
		// dev_ssd1306_show_string(16, 0, 6, (uint8 *)buf);

		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(100));
    }
}



Std_ReturnType dev_eeprom_write_byte_ret;
Std_ReturnType dev_eeprom_read_byte_ret;
uint8 test_val = 0;
/* --- 1000ms task --- */
void vTask1000ms(void *pvParameters)
{
	(void)pvParameters;
	TickType_t xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
		vTask1000ms_cnt++;

		Dio_FlipChannel(DioConf_DioChannel_DioChannel_LEDB);




		// write byte test
		// dev_eeprom_write_byte_ret = dev_eeprom_write_byte(0x0000, (uint8)vTask1000ms_cnt);
		// read byte test
		// dev_eeprom_read_byte_ret = dev_eeprom_read_byte(0x0000, &test_val);

		// write page test
		uint8 buf[4];
		buf[0] = (vTask1000ms_cnt >> 24) & 0xFF;
		buf[1] = (vTask1000ms_cnt >> 16) & 0xFF;
		buf[2] = (vTask1000ms_cnt >> 8)  & 0xFF;
		buf[3] = (vTask1000ms_cnt >> 0)  & 0xFF;
		dev_eeprom_write_page(0x0000, buf, 4);

		// read page test
		uint8 rbuf[4];
		uint32 counter_read;
		dev_eeprom_read_multi(0x0000, rbuf, 4);
		counter_read = ((uint32)rbuf[0] << 24) |
					((uint32)rbuf[1] << 16) |
					((uint32)rbuf[2] << 8)  |
					((uint32)rbuf[3]);
					
		// 在 OLED 上显示读取到的值
		char buf1[20];
		sprintf(buf1, "EE_RD:%d", counter_read);
		dev_ssd1306_show_string(16, 0, 4, (uint8 *)buf1);

		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
    }
}
