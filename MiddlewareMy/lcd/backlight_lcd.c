


#include "backlight_lcd.h"
#include "tim.h"

extern TIM_HandleTypeDef htim12;

static uint16_t lcd_current_backlight = 0;

void lcd_backlight_init(void)
{
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);
}


void lcd_backlight_set_value(uint16_t pwm_value)
{
	lcd_current_backlight = pwm_value;

	__HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_2, pwm_value);
}

uint16_t lcd_backlight_get_value(void)
{
	return lcd_current_backlight;
}

void lcd_backlight_test(void)
{
	lcd_backlight_init();

	uint16_t pwmVal=0;   //PWM占空�?
    while (1)
    {
    	while (pwmVal< 1000)
		{
		  pwmVal++;
		  lcd_backlight_set_value(pwmVal);  // 修改比较值，修改占空比
		  //TIM3->CCR1 = pwmVal;      		// 与上方效果一样
		  HAL_Delay(1);
		}
		while (pwmVal)
		{
		  pwmVal--;
		  lcd_backlight_set_value(pwmVal);  // 修改比较值，修改占空比
		  //TIM3->CCR1 = pwmVal;      		// 与上方效果一样
		  HAL_Delay(1);
		}

		HAL_Delay(200);
    }
}


