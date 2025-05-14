/**
 * @file lv_port_indev.c
 *
 */


#include "lv_port_indev.h"
#include "gt9xx.h"
#include "key_it.h"



static void touchpad_read(lv_indev_t * indev, lv_indev_data_t * data);
static void button_read(lv_indev_t * indev, lv_indev_data_t * data);
static int8_t button_get_pressed_id(void);
static bool button_is_pressed(uint8_t id);


lv_indev_t * indev_touchpad;
lv_indev_t * indev_mouse;
lv_indev_t * indev_keypad;
lv_indev_t * indev_encoder;
lv_indev_t * indev_button;



void lv_port_indev_init(void)
{
    /*------------------
     * Touchpad
     * -----------------*/

    /*Initialize your touchpad if you have*/
    drv_i2c_touchpad_init();
    /*Register a touchpad input device*/
    indev_touchpad = lv_indev_create();
    lv_indev_set_type(indev_touchpad, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev_touchpad, touchpad_read);


    /*------------------
	 * Button
	 * -----------------*/
	/*Register a button input device*/
	indev_button = lv_indev_create();
	lv_indev_set_type(indev_button, LV_INDEV_TYPE_BUTTON);
	lv_indev_set_read_cb(indev_button, button_read);

	/*Assign buttons to points on the screen*/
	static const lv_point_t btn_points[MY_KEY_SUM] = {
		{100, 20},  /*Button 0 -> x:100; y:20*/
		{220, 20},  /*Button 1 -> x:220; y:20*/
		{380, 20},  /*Button 2 -> x:380; y:20*/
		{270, 220}, /*Button 3 -> x:270; y:220*/
	};
	lv_indev_set_button_points(indev_button, btn_points);
  
}




/*Will be called by the library to read the touchpad*/
static void touchpad_read(lv_indev_t * indev_drv, lv_indev_data_t * data)
{
    static int32_t last_x = 0;
    static int32_t last_y = 0;
    uint16_t last_x_u16 = 0;
    uint16_t last_y_u16 = 0;
    
    HAL_StatusTypeDef err;

    /*Save the pressed coordinates and the state*/
    err = touchpad_is_touched();
    if(HAL_OK == err) {
    	touchpad_get_pos(&last_x_u16, &last_y_u16, 0);

        last_x = (int32_t)last_x_u16;
        last_y = (int32_t)last_y_u16;

        data->state = LV_INDEV_STATE_PRESSED;
    }
    else {
        data->state = LV_INDEV_STATE_RELEASED;
    }

    /*Set the last pressed coordinates*/
    data->point.x = last_x;
    data->point.y = last_y;
}




/*Will be called by the library to read the button*/
static void button_read(lv_indev_t * indev_drv, lv_indev_data_t * data)
{

    static uint8_t last_btn = 0;

    /*Get the pressed button's ID*/
    int8_t btn_act = button_get_pressed_id();

    if(btn_act >= 0) {
        data->state = LV_INDEV_STATE_PRESSED;
        last_btn = btn_act;
    }
    else {
        data->state = LV_INDEV_STATE_RELEASED;
    }

    data->btn_id = last_btn;
}

/*Get ID  (0, 1, 2 ..) of the pressed button*/
static int8_t button_get_pressed_id(void)
{
    uint8_t i;

    for(i = 0; i < MY_KEY_SUM; i++) {
        if(button_is_pressed(i)) {
            return i;
        }
    }
    return -1;
}

/*Test if `id` button is pressed or not*/
static bool button_is_pressed(uint8_t id)
{
    return key_is_pressed(id);
}

