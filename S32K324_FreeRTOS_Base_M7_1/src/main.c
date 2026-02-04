/*==================================================================================================
* Project : RTD AUTOSAR 4.7
* Platform : CORTEXM
* Peripheral : S32K3XX
* Dependencies : none
*
* Autosar Version : 4.7.0
* Autosar Revision : ASR_REL_4_7_REV_0000
* Autosar Conf.Variant :
* SW Version : 5.0.0
* Build Version : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
* Copyright 2020 - 2024 NXP
*
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be 
*   used strictly in accordance with the applicable license terms.  By expressly 
*   accepting such terms or by downloading, installing, activating and/or otherwise 
*   using the software, you are agreeing that you have read, and that you agree to 
*   comply with and are bound by, such license terms.  If you do not agree to be 
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

/**
*   @file main.c
*
*   @addtogroup main_module main module documentation
*   @{
*/

/* Including necessary configuration files. */
#include "OsTask.h"
#include "OsIf.h"
#include "Clock_Ip.h"
#include "Siul2_Port_Ip_Cfg.h"
#include "Siul2_Port_Ip.h"
#include "Siul2_Dio_Ip.h"

volatile int exit_code = 0;
/* User includes */

/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
int main(void)
{
    /* Write your code here */
    Clock_Ip_Init(&Clock_Ip_aClockConfig[0]);
    Siul2_Port_Ip_Init(
    NUM_OF_CONFIGURED_PINS_PortContainer_0_BOARD_InitPeripherals, g_pin_mux_InitConfigArr_PortContainer_0_BOARD_InitPeripherals);


    xTaskCreate(vTask1ms_core1, "Task1ms_core1", configMINIMAL_STACK_SIZE, NULL, PRIO_1MS, &xHandle1ms_core1);
    xTaskCreate(vTask10ms_core1, "Task10ms_core1", configMINIMAL_STACK_SIZE, NULL, PRIO_10MS, &xHandle10ms_core1);
    xTaskCreate(vTask100ms_core1, "Task100ms_core1", configMINIMAL_STACK_SIZE, NULL, PRIO_100MS, &xHandle100ms_core1);
    xTaskCreate(vTask1000ms_core1, "Task1000ms_core1", configMINIMAL_STACK_SIZE, NULL, PRIO_1000MS, &xHandle1000ms_core1);
    vTaskStartScheduler();


    for(;;){}
    return exit_code;
}

/** @} */
