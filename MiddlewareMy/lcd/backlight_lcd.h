


#ifndef _LCD_BACKLIGHT_H
#define _LCD_BACKLIGHT_H

#include "main.h"

#define LCD_MAX_BACKLIGHT       1000
#define LCD_MIN_BACKLIGHT       200

void lcd_backlight_init(void);
void lcd_backlight_set_value(uint16_t pwm_value);

uint16_t lcd_backlight_get_value(void);

void lcd_backlight_test(void);

#endif /* _DRIVER_LCD_BACKLIGHT_H */

