#include "main.h"
#include "key_it.h"


static uint8_t my_key_points[MY_KEY_SUM];

uint64_t system_get_ns(void)
{
    extern TIM_HandleTypeDef        htim1;
    TIM_HandleTypeDef *hHalTim = &htim1;

    uint64_t ns = HAL_GetTick();
    uint64_t cnt;
    uint64_t reload;

    cnt = __HAL_TIM_GET_COUNTER(hHalTim);
    reload = __HAL_TIM_GET_AUTORELOAD(hHalTim);

    ns *= 1000000;
    ns += cnt * 1000000 / reload;
    return ns;
}



void Key_IRQ_Callback(uint16_t GPIO_Pin)
{
    static uint64_t pre_time = 0;

    // 消抖
#if 1
    uint64_t time = 0;

	/* 1. 记录中断发生的时刻 */
	time = system_get_ns();

	/* 上升沿触发: 必定是高电平
	 * 防抖
	 */
	if (time - pre_time < 2000000) /* 当前中断的时间 跟 上次中断的时间 < 2ms的话,认为是抖动 */
	{
		pre_time = time;
		return;
	}
	pre_time = time;
#endif

	switch (GPIO_Pin)
	{
		case USER_KEY1_Pin:
			my_key_points[0] = 1;
			break;
		case USER_KEY2_Pin:
			my_key_points[1] = 1;
			break;
		case USER_KEY3_Pin:
			my_key_points[2] = 1;
			break;
		case USER_KEY4_Pin:
			my_key_points[3] = 1;
			break;
		default:
			break;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    switch (GPIO_Pin)
    {
        case USER_KEY1_Pin:
        case USER_KEY2_Pin:
        case USER_KEY3_Pin:
        case USER_KEY4_Pin:
        	Key_IRQ_Callback(GPIO_Pin);
            break;
        default:
        	break;
    }
}

bool key_is_pressed(uint8_t id)
{

    /*Your code comes here*/
    if(id >= MY_KEY_SUM) return false;

    uint8_t key_points = my_key_points[id];

    my_key_points[id] = 0;

    return key_points;
}

