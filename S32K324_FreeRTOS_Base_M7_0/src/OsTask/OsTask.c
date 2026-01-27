/*
 * OsTask.c
 *
 *  Created on: 2026年1月27日
 *      Author: li
 */



#include "OsTask.h"


TaskHandle_t xHandle1ms, xHandle10ms, xHandle100ms, xHandle1000ms;
uint32 vTask1ms_cnt, vTask10ms_cnt, vTask100ms_cnt, vTask1000ms_cnt;

/* --- 1ms task --- */
void vTask1ms(void *pvParameters)
{
	(void)pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
    	vTask1ms_cnt++;

    	if(Siul2_Dio_Ip_ReadPin(KEY1_PORT, KEY1_PIN) == 1)
    	{
    		Siul2_Dio_Ip_TogglePins(LEDR_PORT, (1U << LEDR_PIN));
    	}
    	else
    	{
    		Siul2_Dio_Ip_WritePin(LEDR_PORT, LEDR_PIN, 1);
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

    	if(Siul2_Dio_Ip_ReadPin(KEY2_PORT, KEY2_PIN) == 1)
    	{
    		Siul2_Dio_Ip_TogglePins(LEDG_PORT, (1U << LEDG_PIN));
    	}
    	else
    	{
    		Siul2_Dio_Ip_WritePin(LEDG_PORT, LEDG_PIN, 1);
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
    	if(Siul2_Dio_Ip_ReadPin(KEY3_PORT, KEY3_PIN) == 1)
    	{
    		Siul2_Dio_Ip_TogglePins(LEDR_PORT, (1U << LEDR_PIN));
    		Siul2_Dio_Ip_TogglePins(LEDG_PORT, (1U << LEDG_PIN));
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
        Siul2_Dio_Ip_TogglePins(LEDB_PORT, (1U << LEDB_PIN));
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
    }
}
