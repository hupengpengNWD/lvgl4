#ifndef __USER_TEST_H___
#define __USER_TEST_H___

#ifdef __cplusplus
extern "C" {
#endif

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

void test_lv_slider_set_backlight_init(void);
void test_lv_Text_tag(void);
void test_lv_fs_test_timer_callback(lv_timer_t * timer);
void test_lv_print_log_timer_callback(lv_timer_t * timer);

#ifdef __cplusplus
}
#endif

#endif  