/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
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
#include "gt9xx.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_demos.h"
#include "backlight_lcd.h"

#include "test.h"
#include "default_task.h"




/* 虚拟串口打印的回调函数 */
void lvgl_log_cb(lv_log_level_t level, const char * buf)
{
	ux_device_cdc_acm_printf("%s", buf);
}



/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  SCB_EnableICache();
  SCB_EnableDCache();
  SystemCoreClockUpdate();
  HAL_Init();
  __HAL_RCC_SBS_CLK_ENABLE();

  MX_GPIO_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_TIM2_Init();
  MX_LTDC_Init();
  MX_FLASH_Init();
  MX_I2C1_Init();
  MX_DMA2D_Init();
  MX_TIM4_Init();
  MX_TIM12_Init();
  MX_SDMMC1_SD_Init();
  MX_FATFS_Init();


  lv_init();
  lv_tick_set_cb(HAL_GetTick);
  lv_delay_set_cb(HAL_Delay);
  lv_port_disp_init();
  lv_port_indev_init();
  lv_log_register_print_cb(lvgl_log_cb);
  lcd_backlight_init();
  lcd_backlight_set_value(LCD_MAX_BACKLIGHT);
  ux_device_cdc_acm_printf("system start ok\r\n");

  /* lvgl界面gul测试：demo界面、滑动条（背光调节）界面、文本标签界面，三选一 */
  lv_demo_widgets();
  // test_slider_set_backlight_init();
  // test_lv_Text_tag();

  /* freertos测试 */
  osKernelInitialize();
  task_init();
  osKernelStart();

  while (1)
  {
    lv_timer_handler();
    HAL_Delay(1);
  }

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}


