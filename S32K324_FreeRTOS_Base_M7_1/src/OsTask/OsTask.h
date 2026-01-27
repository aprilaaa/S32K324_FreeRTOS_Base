/*
 * OsTask.h
 *
 *  Created on: 2026年1月27日
 *      Author: li
 */

#ifndef OSTASK_OSTASK_H_
#define OSTASK_OSTASK_H_

#include "FreeRTOS.h"
#include "Siul2_Dio_Ip.h"
#include "Siul2_Port_Ip_Cfg.h"
#include "Siul2_Port_Ip.h"
#include "task.h"

#define PRIO_1MS    ( tskIDLE_PRIORITY + 5 )
#define PRIO_10MS   ( tskIDLE_PRIORITY + 4 )
#define PRIO_100MS  ( tskIDLE_PRIORITY + 3 )
#define PRIO_1000MS ( tskIDLE_PRIORITY + 2 )

extern TaskHandle_t xHandle1ms_core1, xHandle10ms_core1, xHandle100ms_core1, xHandle1000ms_core1;


void vTask1ms_core1(void *pvParameters);
void vTask10ms_core1(void *pvParameters);
void vTask100ms_core1(void *pvParameters);
void vTask1000ms_core1(void *pvParameters);


#endif /* OSTASK_OSTASK_H_ */
