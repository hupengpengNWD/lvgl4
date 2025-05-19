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
#include "ux_device_cdc_acm.h"

#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_demos.h"
#include <src/misc/lv_log.h>
#include <src/tick/lv_tick.h>
#include "test.h"


/* freertos使用的ram */
uint8_t ucHeap[configTOTAL_HEAP_SIZE] __attribute__((section(".freertos_heap")));//sul

/* lvgl任务 */
void Lvgl_Timer_Handler_Task(void *argument);
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

/* 虚拟串口打印的回调函数 */
void lvgl_log_cb(lv_log_level_t level, const char * buf)
{
	ux_device_cdc_acm_printf("%s", buf);
}


/* 测试usbx */
static void my_lv_timer_callback(lv_timer_t * timer)
{
    (void)timer;
    // LV_LOG("测试freertos使用单独SDRAM\r\n");
    // LV_LOG("测试lvgl心跳使用freertos的tick的hook函数实现\r\n");
    // LV_LOG("测试lvgl相关代码移动到freertos初始化后再初始化\r\n");
    // LV_LOG("测试lvgl使用freertos的互斥量等接口\r\n");
    LV_LOG("测试lvgl使用freetype加载第三方字体库\r\n");



}


/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void task_init(void) {


  /* 创建一个lvgl任务 */
  Lvgl_Timer_Handler_Task_Handle = osThreadNew(Lvgl_Timer_Handler_Task, NULL, &Lvgl_Timer_Handler_Task_Attributes);



}



/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
void Lvgl_Timer_Handler_Task(void *argument)
{
  FATFS_Init();
  /* lvgl核心初始化 */
  lv_init();
  lv_port_disp_init();
  lv_port_indev_init();
  lv_log_register_print_cb(lvgl_log_cb);

  /* 创建一个lvgl定时器 用于打印每次实验的目的*/
  lv_timer_create(my_lv_timer_callback, 1000, NULL);

  /* 测试fatfs使用freertos的互斥量等接口，测试此项时需要将上面的语句屏蔽 */
  // lv_timer_create(test_lv_fs_test_timer_callback, 1000, NULL);

  /* 测试一个lvgl的demo界面 */
  // lv_demo_widgets();

  /* 测试一个lvgl的加载freetype字体的界面 */
  test_lv_Text_tag();

  for(;;)
  {
    lv_timer_handler();
    osDelay(10);
  }

}



