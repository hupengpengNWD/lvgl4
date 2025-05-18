

#include "test.h"

/* 滑动条回调函数 */
static void slider_set_backlight_event_callback(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);
    int32_t slider_value = (int32_t)lv_slider_get_value(slider);

    lcd_backlight_set_value(slider_value);
}

/* 读文件测试 */
static void lv_fs_read_all_txt_files(char * dir_path, char * txt_files[])
{
    /* 遍历用户提供的NULL终止文件数组 */ 
    for (int i = 0; txt_files[i] != NULL; i++) {
        
        /* 构造完整文件路径 */ 
        char full_path[256];
        snprintf(full_path, sizeof(full_path), "%s%s", dir_path, txt_files[i]);

        lv_fs_file_t f;
        lv_fs_res_t res;

        /* 打开文件 */ 
        res = lv_fs_open(&f, full_path, LV_FS_MODE_RD);
        if (res != LV_FS_RES_OK) {
            LV_LOG_USER("Open error for %s! Error code: %d", full_path, res);
            /* 跳到下一个文件 */ 
            continue; 
        }

        uint32_t read_num;
        uint8_t buf[100];

        /* 读取文件内容 */ 
        while (1) {
            res = lv_fs_read(&f, buf, 100, &read_num);
            if (res != LV_FS_RES_OK) {
                LV_LOG_USER("Read error for %s! Error code: %d", full_path, res);
                break;
            }

            /* 确保缓冲区以空字符终止，以便作为字符串打印 */ 
            if (read_num < 100) {
                buf[read_num] = '\0';
            } else {
                buf[99] = '\0'; // 防止溢出
            }

            /* 打印读取到的内容 */ 
            LV_LOG_USER("file:%s", buf);

            if (read_num != 100) {
                break; /* 文件读取完毕 */ 
            }
        }

        /* 关闭文件 */ 
        lv_fs_close(&f);
    }
}

/* 读目录测试 */
static void lv_fs_read_dir_test(char * path)
{
    lv_fs_dir_t dir;
    lv_fs_res_t res;
    int file_count = 0; /* 记录读取到的文件或目录数量 */ 

    /* 打开目录 */ 
    res = lv_fs_dir_open(&dir, path);
    if (res != LV_FS_RES_OK) {
        LV_LOG_USER("Open DIR error! Error code: %d", res);
        return;
    }

    /* 目录打开成功 */ 
    LV_LOG_USER("Directory %s opened successfully", path);

    char fn[128];  
    while (1) {

        /* 读取目录项 */ 
        res = lv_fs_dir_read(&dir, fn, 128);
        if (res != LV_FS_RES_OK) {
            LV_LOG_USER("Read DIR error! Error code: %d", res);
            break;
        }
        /* 检查是否读取到空文件名（表示目录读取结束） */ 
        if (strlen(fn) == 0) {
            LV_LOG_USER("files to read in %s. Total items: %d", path, file_count);
            break;
        }
        /* 打印读取到的文件或目录名 */ 
        LV_LOG_USER("Found item: %s", fn);
        file_count++;
    }
    /* 关闭目录 */ 
    lv_fs_dir_close(&dir);
}



/* freetype测试 */
void test_lv_Text_tag(void)
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
    lv_label_set_text(label, "你好\n" "hello");
    lv_obj_center(label);

    //lv_freetype_font_delete(font);
}

/* 测试lvgl对接usbx后的日志打印功能 */
void test_lv_print_log_timer_callback(lv_timer_t * timer)
{
    LV_LOG("skdjflsdjkafjioe\r\n");
    LV_LOG("98fd9u98783249\r\n");

}

/* 测试lvgl对接fatfs后其文件系统接口 */
void test_lv_fs_test_timer_callback(lv_timer_t * timer)
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


/* 滑动条控件测试，主要是测试背光调节*/
void test_lv_slider_set_backlight_init(void)
{
	lv_obj_t * slider = lv_slider_create(lv_layer_sys());
	lv_slider_set_range(slider, LCD_MIN_BACKLIGHT, LCD_MAX_BACKLIGHT);
	lv_slider_set_value(slider, LCD_MAX_BACKLIGHT, LV_ANIM_OFF);
	lv_obj_center(slider);

	lv_obj_add_event_cb(slider, slider_set_backlight_event_callback, LV_EVENT_VALUE_CHANGED, NULL);
}

