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

     	/* Can_CreatePduInfo(id, swPduHandle,length, sdu) */
        static Can_PduType Can_PduInfo;
        Can_PduInfo = Can_CreatePduInfo(0U, 0U, 8U, Can_au8Sdu8bytes);
     	Can_43_FLEXCAN_Write(Can_43_FLEXCANConf_CanHardwareObject_CAN00_MailBox1_TX, &Can_PduInfo);

     	Adc_StartGroupConversion(AdcGroupSoftwareOneShot);
        while (VarNotification_0 == 0u){}
		VarNotification_0 = 0;
     	Adc_ReadGroup(AdcGroupSoftwareOneShot, &AdcReadGroupResult);

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(100));
    }
}




/* --- 1000ms task --- */
void vTask1000ms(void *pvParameters)
{
	(void)pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
    	vTask1000ms_cnt++;
    	Dio_FlipChannel(DioConf_DioChannel_DioChannel_LEDB);
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
    }
}
