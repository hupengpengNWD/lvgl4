/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "task.h"
#include "main.h"
#include "dma2d.h"
#include "fatfs.h"
#include "flash.h"
#include "i2c.h"
#include "ltdc.h"
#include "sdmmc.h"
#include "tim.h"
#include "usb_otg.h"
#include "gpio.h"


#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_demos.h"
#include <src/misc/lv_log.h>
#include <src/tick/lv_tick.h>

/* freertos使用的ram */
uint8_t ucHeap[configTOTAL_HEAP_SIZE] __attribute__((section(".freertos_heap")));//sul

void Lvgl_Timer_Handler_Task(void *argument);
void vApplicationTickHook(void);

osThreadId_t Lvgl_Timer_Handler_Task_Handle;
const osThreadAttr_t Lvgl_Timer_Handler_Task_Attributes = {
  .name = "Lvgl_Timer_Handler_Task_Name",
  .stack_size = 1024 * 10,
  .priority = (osPriority_t) osPriorityNormal,
};



void vApplicationTickHook( void )
{
   /* This function will be called by each tick interrupt if
   configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h. User code can be
   added here, but the tick hook is called from an interrupt context, so
   code must not attempt to block, and only the interrupt safe FreeRTOS API
   functions can be used (those that end in FromISR()). */
   lv_tick_inc(1);
}


/* 测试usbx */
static void my_lv_timer_callback(lv_timer_t * timer)
{
    (void)timer;
    // LV_LOG("测试freertos使用单独SDRAM\r\n");
    LV_LOG("测试lvgl的tick使用tick的hook函数\r\n");

}


/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void task_init(void) {

  lv_timer_create(my_lv_timer_callback, 1000, NULL);
  Lvgl_Timer_Handler_Task_Handle = osThreadNew(Lvgl_Timer_Handler_Task, NULL, &Lvgl_Timer_Handler_Task_Attributes);



}



/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
void Lvgl_Timer_Handler_Task(void *argument)
{

  for(;;)
  {
    lv_timer_handler();
    osDelay(10);
  }

}



