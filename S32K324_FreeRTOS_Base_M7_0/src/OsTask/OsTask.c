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
extern Adc_ValueGroupType AdcReadGroupResult[];

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

    	Adc_StartGroupConversion(AdcGroupSoftwareOneShot);
        /* Check if notification is called */
        while (VarNotification_0 == 0u)
        {}
    	Adc_ReadGroup(AdcGroupSoftwareOneShot, AdcReadGroupResult);

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
    }
}
