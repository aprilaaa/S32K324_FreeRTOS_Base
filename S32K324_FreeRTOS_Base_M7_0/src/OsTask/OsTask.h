/*
 * OsTask.h
 *
 *  Created on: 2026年1月27日
 *      Author: li
 */

#ifndef OSTASK_OSTASK_H_
#define OSTASK_OSTASK_H_

#include "FreeRTOS.h"
#include "task.h"
#include "Dio.h"
#include "Adc.h"
#include "Can_43_FLEXCAN.h"
#include "CanIf.h"
#include "Platform.h"
#include "SchM_Can_43_FLEXCAN.h"
#include "dev_ssd1306.h"

#define PRIO_1MS    ( tskIDLE_PRIORITY + 5 )
#define PRIO_10MS   ( tskIDLE_PRIORITY + 4 )
#define PRIO_100MS  ( tskIDLE_PRIORITY + 3 )
#define PRIO_1000MS ( tskIDLE_PRIORITY + 2 )

extern TaskHandle_t xHandle1ms, xHandle10ms, xHandle100ms, xHandle1000ms;


void vTask1ms(void *pvParameters);
void vTask10ms(void *pvParameters);
void vTask100ms(void *pvParameters);
void vTask1000ms(void *pvParameters);


#endif /* OSTASK_OSTASK_H_ */
