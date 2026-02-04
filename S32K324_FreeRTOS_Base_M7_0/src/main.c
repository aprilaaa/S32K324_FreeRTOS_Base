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
#include "Mcal.h"
#include "OsIf.h"
#include "Clock_Ip.h"
#include "Port.h"
#include "Mcu.h"
#include "Platform.h"
#include "Can_43_FLEXCAN.h"
#include "CanIf.h"

volatile int exit_code = 0;

Adc_ValueGroupType    AdcResult;
Adc_ValueGroupType    AdcReadGroupResult;
volatile uint8 VarNotification_0 = 0u;

extern ISR(Adc_Sar_1_Isr);

void Notification_0(void)
{
    VarNotification_0++;
}
/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
int main(void)
{

    /* Initialize the Mcu driver */
	#if (MCU_PRECOMPILE_SUPPORT == STD_ON)
		Mcu_Init(NULL_PTR);
	#elif (MCU_PRECOMPILE_SUPPORT == STD_OFF)
		Mcu_Init(&Mcu_Config);
	#endif /* (MCU_PRECOMPILE_SUPPORT == STD_ON) */

    /* Initialize the clock tree and apply PLL as system clock */
    Mcu_InitClock(McuClockSettingConfig_0);

    /* Apply a mode configuration */
    Mcu_SetMode(McuModeSettingConf_0);

    /* Initialize all pins using the Port driver */
    Port_Init(NULL_PTR);

    /* Initialize Platform Driver */
    Platform_Init(NULL_PTR);
    Platform_InstallIrqHandler(ADC1_IRQn, Adc_Sar_1_Isr, NULL_PTR);
    Platform_SetIrq(ADC1_IRQn, TRUE);

    /* Initialize ADC Driver */
	#if (ADC_PRECOMPILE_SUPPORT == STD_ON)
		Adc_Init(NULL_PTR);
	#else
		Adc_Init(&Adc_Config_VS_0);
	#endif /* (ADC_PRECOMPILE_SUPPORT == STD_ON) */


    /* Initilize Can driver */
	#if (CAN_43_FLEXCAN_PRECOMPILE_SUPPORT == STD_ON)
		Can_43_FLEXCAN_Init(NULL_PTR);
	#else
		Can_43_FLEXCAN_Init(&Can_43_FLEXCAN_Config);
	#endif

	#if (STD_ON == CANIF_PRECOMPILE_SUPPORT)
	CanIf_Init(NULL_PTR);
	#else
	CanIf_Init(&CanIf_Config);
	#endif

	Can_43_FLEXCAN_SetControllerMode(Can_43_FLEXCANConf_CanController_CanController_0, CAN_CS_STARTED);

    Adc_SetupResultBuffer(AdcGroupSoftwareOneShot, &AdcResult);
    Adc_EnableGroupNotification(AdcGroupSoftwareOneShot);


    xTaskCreate(vTask1ms, "Task1ms", configMINIMAL_STACK_SIZE, NULL, PRIO_1MS, &xHandle1ms);
    xTaskCreate(vTask10ms, "Task10ms", configMINIMAL_STACK_SIZE, NULL, PRIO_10MS, &xHandle10ms);
    xTaskCreate(vTask100ms, "Task100ms", configMINIMAL_STACK_SIZE, NULL, PRIO_100MS, &xHandle100ms);
    xTaskCreate(vTask1000ms, "Task1000ms", configMINIMAL_STACK_SIZE, NULL, PRIO_1000MS, &xHandle1000ms);
    vTaskStartScheduler();

    for(;;);
    return exit_code;
}

/** @} */
