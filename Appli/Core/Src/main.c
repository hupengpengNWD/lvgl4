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
#include "dma2d.h"
#include "fatfs.h"
#include "flash.h"
#include "i2c.h"
#include "ltdc.h"
#include "sdmmc.h"
#include "tim.h"
#include "usb_otg.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ux_device_cdc_acm.h"
#include "gt9xx.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_demos.h"
#include "backlight_lcd.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* 使用lvgl文件读写接口测试时打开的文件的名字 */
#define FILE_NAME	"lv_fs_test.txt"
/* 使用lvgl文件读写接口测试时打开的文件的路径 */
#define DIR_PATH	"S:/"
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* 虚拟串口打印的回调函数 */
void my_log_cb(lv_log_level_t level, const char * buf)
{
	ux_device_cdc_acm_printf("%s", buf);
}

/* 滑动条回调函数 */
static void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);
    int32_t slider_value = (int32_t)lv_slider_get_value(slider);

    lcd_backlight_set_value(slider_value);
}

/* 滑动条控件*/
static void slider_set_backlight_init(void)
{
	lv_obj_t * slider = lv_slider_create(lv_layer_sys());
	lv_slider_set_range(slider, LCD_MIN_BACKLIGHT, LCD_MAX_BACKLIGHT);
	lv_slider_set_value(slider, LCD_MAX_BACKLIGHT, LV_ANIM_OFF);
	lv_obj_center(slider);

	lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
}

/* 读文件测试 */
static void lv_fs_read_all_txt_files(char * dir_path, char * txt_files[])
{
    // 遍历用户提供的NULL终止文件数组
    for (int i = 0; txt_files[i] != NULL; i++) {
        
        // 构造完整文件路径
        char full_path[256];
        snprintf(full_path, sizeof(full_path), "%s%s", dir_path, txt_files[i]);

        lv_fs_file_t f;
        lv_fs_res_t res;

        // 打开文件
        res = lv_fs_open(&f, full_path, LV_FS_MODE_RD);
        if (res != LV_FS_RES_OK) {
            LV_LOG_USER("Open error for %s! Error code: %d", full_path, res);
            continue; // 跳到下一个文件
        }

        uint32_t read_num;
        uint8_t buf[100];

        // 读取文件内容
        while (1) {
            res = lv_fs_read(&f, buf, 100, &read_num);
            if (res != LV_FS_RES_OK) {
                LV_LOG_USER("Read error for %s! Error code: %d", full_path, res);
                break;
            }

            // 确保缓冲区以空字符终止，以便作为字符串打印
            if (read_num < 100) {
                buf[read_num] = '\0';
            } else {
                buf[99] = '\0'; // 防止溢出
            }

            // 打印读取到的内容
            LV_LOG_USER("file:%s", buf);

            if (read_num != 100) {
                break; // 文件读取完毕
            }
        }

        // 关闭文件
        lv_fs_close(&f);
    }
}



/* 读目录测试 */
static void lv_fs_read_dir_test(char * path)
{
    lv_fs_dir_t dir;
    lv_fs_res_t res;
    int file_count = 0; // 记录读取到的文件或目录数量

    // 打开目录
    res = lv_fs_dir_open(&dir, path);
    if (res != LV_FS_RES_OK) {
        LV_LOG_USER("Open DIR error! Error code: %d", res);
        return;
    }

    // 目录打开成功
    LV_LOG_USER("Directory %s opened successfully", path);

    char fn[128]; // 缓冲区，与原函数保持一致
    while (1) {
        // 读取目录项
        res = lv_fs_dir_read(&dir, fn, 128);
        if (res != LV_FS_RES_OK) {
            LV_LOG_USER("Read DIR error! Error code: %d", res);
            break;
        }

        // 检查是否读取到空文件名（表示目录读取结束）
        if (strlen(fn) == 0) {
            LV_LOG_USER("files to read in %s. Total items: %d", path, file_count);
            break;
        }

        // 打印读取到的文件或目录名
        LV_LOG_USER("Found item: %s", fn);
        file_count++;
    }

    // 关闭目录
    lv_fs_dir_close(&dir);
}



/* freetype测试 */
static void lv_Text_tag(void)
{
                                              
    /*Create a font*/
    lv_font_t * font = lv_freetype_font_create("S:/100ask/SourceHanSansCN-Bold-2.otf",
                                               LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
                                               22,
                                               LV_FREETYPE_FONT_STYLE_NORMAL);
    if(!font) {
        LV_LOG_USER("freetype font create failed.");
        return;
    }

    /*Create style with the new font*/
    static lv_style_t style;
    lv_style_init(&style);
    //lv_style_set_text_font(&style, &lv_font_montserrat_14);
    lv_style_set_text_font(&style, font);
    lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);

    /*Create a label with the new style*/
    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_obj_add_style(label, &style, 0);
    lv_label_set_text(label, "你好\n" "kkkkkkkkkkkkkkkkkkk");
    lv_obj_center(label);

    //lv_freetype_font_delete(font);
}

static void my_lv_fs_test_timer2(lv_timer_t * timer)
{
    LV_LOG("skdjflsdjkafjioe");
    LV_LOG("98fd9u98783249");

}

static void my_lv_fs_test_timer3(lv_timer_t * timer)
{
    (void)timer;
    char *root_path = "S:/";
    char *sub_path = "S:/100ask/";
    char * my_txt_files[] = {
        "DshanMCUH7R.TXT",
        "hello.txt",
        "lv_fs_test.txt",
        NULL // 结束标志
    };

    /* 统计根文件目录下的文件和目录的总个数 */
    LV_LOG_USER("Testing root directory:%s", root_path);
    lv_fs_read_dir_test(root_path);

    /* 统计100ask子目录下的文件和目录的总个数 */
    LV_LOG_USER("Testing 100ask directory:");
    lv_fs_read_dir_test(sub_path);
    
    /* 测试100ask子目录下的文件访问 */ 
    LV_LOG_USER("Testing open S:/100ask/SourceHanSansCN-Bold-2.otf filse:");
    lv_fs_file_t file;
    lv_fs_res_t res = lv_fs_open(&file, "S:/100ask/SourceHanSansCN-Bold-2.otf", LV_FS_MODE_RD);
    if (res == LV_FS_RES_OK) {
        LV_LOG_USER("Font file exists");
        lv_fs_close(&file);
    } else {
        LV_LOG_USER("Cannot open font file, error code: %d", res);
    }

    /* 读取根目录下txt文件测试*/
    LV_LOG_USER("Testing read root txt:");
    lv_fs_read_all_txt_files(root_path, my_txt_files);

}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  lv_timer_t *test_timer = NULL;
  /* USER CODE END 1 */

  /* Enable the CPU Cache */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Update SystemCoreClock variable according to RCC registers values. */
  SystemCoreClockUpdate();

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  __HAL_RCC_SBS_CLK_ENABLE();
  /* USER CODE END Init */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
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
  /* USER CODE BEGIN 2 */
  drv_i2c_touchpad_init();
  lv_init();
  lv_tick_set_cb(HAL_GetTick);
  lv_delay_set_cb(HAL_Delay);
  lv_port_disp_init();
  lv_port_indev_init();
  lv_log_register_print_cb(my_log_cb);
  lcd_backlight_init();
  lcd_backlight_set_value(LCD_MAX_BACKLIGHT);
  ux_device_cdc_acm_printf("system start ok\r\n");

  /* lvgl界面gul测试：demo界面、滑动条（背光调节）界面、文本标签界面，三选一 */
  // lv_demo_widgets();
  // slider_set_backlight_init();
  lv_Text_tag();

  /* 文件系统读写测试，原始Fatfs文件系统接口测试和对接lvgl文件系统后的文件操作接口测试，二选一*/
  // FS_FileTest();
  // test_timer = lv_timer_create(my_lv_fs_test_timer3, 5000, NULL);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    lv_timer_handler();
    HAL_Delay(1);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
	if (htim == (&htim2)) {
		ux_system_tasks_run();
	}
  /* USER CODE END Callback 1 */
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

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
