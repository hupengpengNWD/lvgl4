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
#include <src/tick/lv_tick.h>



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
  // MX_FATFS_Init();

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


