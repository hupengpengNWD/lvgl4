/**
 * @file lv_port_disp_templ.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp.h"
#include <stdbool.h>
#include <string.h>
#include "ltdc.h"
#include "dma2d.h"
/*********************
 *      DEFINES
 *********************/
#define MY_DISP_HOR_RES    480
#define MY_DISP_VER_RES    480
#define STM32_DMA2D_MODE   1
#define USER_INTERNAL_RAM   1

#if STM32_DMA2D_MODE == 1
static void disp_flush_complete (DMA2D_HandleTypeDef*);
#endif

#define BYTE_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565)) /*will be 2 for RGB565 */

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);

static void disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map);

/**********************
 *  STATIC VARIABLES
 **********************/
static uint8_t * buf_1 = (uint8_t *)(uint32_t) 0xC0000000;
static uint8_t * buf_2 = (uint8_t *)(uint32_t) 0xC0100000;
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_disp_init(void)
{
    /*-------------------------
     * Initialize your display
     * -----------------------*/
    disp_init();

    /*------------------------------------
     * Create a display and set a flush_cb
     * -----------------------------------*/
    lv_display_t * disp = lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_display_set_flush_cb(disp, disp_flush);

    LV_ATTRIBUTE_MEM_ALIGN
#if STM32_DMA2D_MODE == 0
    lv_display_set_buffers(disp, buf_1, buf_2, (MY_DISP_HOR_RES*MY_DISP_VER_RES*BYTE_PER_PIXEL), LV_DISPLAY_RENDER_MODE_DIRECT);
#else
    #if USER_INTERNAL_RAM == 1
    __attribute__((section(".lv_ram"))) static uint8_t buf1[256*1024];
    lv_display_set_buffers(disp, (void*) buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);
    #else
        lv_display_set_buffers(disp, buf_2, NULL, (MY_DISP_HOR_RES*MY_DISP_VER_RES*BYTE_PER_PIXEL), LV_DISPLAY_RENDER_MODE_PARTIAL);
    #endif
	hdma2d.XferCpltCallback = disp_flush_complete;
#endif

}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    /*You code here*/
}

volatile bool disp_flush_enabled = true;

/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void)
{
    disp_flush_enabled = true;
}

/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void)
{
    disp_flush_enabled = false;
}

/*Flush the content of the internal buffer the specific area on the display.
 *`px_map` contains the rendered image as raw pixel map and it should be copied to `area` on the display.
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_display_flush_ready()' has to be called when it's finished.*/
static void disp_flush(lv_display_t * disp_drv, const lv_area_t * area, uint8_t * px_map)
{

    if(disp_flush_enabled) {
      
        #if STM32_DMA2D_MODE == 0        
            if(lv_display_flush_is_last(disp_drv)){               
                SCB_CleanInvalidateDCache();
                while (!(LTDC->CDSR & LTDC_CDSR_VSYNCS));
                HAL_LTDC_SetAddress(&hltdc, (uint32_t)(lv_display_get_buf_active(lv_display_get_default())->data), LTDC_LAYER_1);
            }
        #else
            lv_coord_t width = lv_area_get_width(area);
            lv_coord_t height = lv_area_get_height(area);

            SCB_CleanInvalidateDCache();

            DMA2D->CR = 0x0U << DMA2D_CR_MODE_Pos;
            DMA2D->FGPFCCR = DMA2D_INPUT_RGB565;	                                                     /* 设置前景色颜色格式 */ 
            DMA2D->FGMAR = (uint32_t)px_map;		                                                     /* 设置前景数据内存地址 */ 
            DMA2D->FGOR = 0;						                                                     /* 设置前景数据传输偏移 */ 
            DMA2D->OPFCCR = DMA2D_OUTPUT_RGB565;	                                                     /* 设置颜色格式 */ 
            DMA2D->OMAR = hltdc.LayerCfg[0].FBStartAdress + 2 * (area->y1 * MY_DISP_HOR_RES + area->x1); /* 填充区域的起始内存地址 */                         
            DMA2D->OOR = MY_DISP_HOR_RES - width;	                                                     /* 行偏移，即每行多少像素（以像素为单位） */ 
            DMA2D->NLR = (width << DMA2D_NLR_PL_Pos) | (height << DMA2D_NLR_NL_Pos);                     /* 设置填充区域的宽和高（单位：像素） */ 
            DMA2D->IFCR = 0x3FU;		                                                                 /* 设置DMA2D中断标志清除寄存器 */
            DMA2D->CR |= DMA2D_CR_TCIE;
            DMA2D->CR |= DMA2D_CR_START;                                                                 /* 启动传输 */
        #endif
    }



    #if STM32_DMA2D_MODE == 0
        lv_display_flush_ready(disp_drv);
    #endif
}

#if STM32_DMA2D_MODE == 1

static void disp_flush_complete (DMA2D_HandleTypeDef *hdma2d)
{
  lv_display_flush_ready(lv_display_get_default());
}

#endif

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
