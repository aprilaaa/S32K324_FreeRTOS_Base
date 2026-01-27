/*
 * OsTask.c
 *
 *  Created on: 2026年1月27日
 *      Author: li
 */



#include "OsTask.h"


TaskHandle_t xHandle1ms_core1, xHandle10ms_core1, xHandle100ms_core1, xHandle1000ms_core1;
uint32 vTask1ms_core1_cnt, vTask10ms_core1_cnt, vTask100ms_core1_cnt, vTask1000ms_core1_cnt;

/* --- 1ms task --- */
void vTask1ms_core1(void *pvParameters)
{
	(void)pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
    	vTask1ms_core1_cnt++;
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1));
    }
}

/* --- 10ms task --- */
void vTask10ms_core1(void *pvParameters)
{
	(void)pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
    	vTask10ms_core1_cnt++;
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(10));
    }
}

/* --- 100ms task --- */
void vTask100ms_core1(void *pvParameters)
{
	(void)pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
    	vTask100ms_core1_cnt++;
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(100));
    }
}

/* --- 1000ms task --- */
void vTask1000ms_core1(void *pvParameters)
{
	(void)pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
    	vTask1000ms_core1_cnt++;
        Siul2_Dio_Ip_TogglePins(LEDY_PORT, (1U << LEDY_PIN));
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
    }
}
