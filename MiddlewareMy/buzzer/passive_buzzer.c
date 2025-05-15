
#include "passive_buzzer.h"
#include "tim.h"

extern TIM_HandleTypeDef htim4;

static TIM_HandleTypeDef *g_HPWM_PassiveBuzzer = &htim4;

/**********************************************************************
 * 函数名称： PassiveBuzzer_Init
 * 功能描述： 无源蜂鸣器的初始化函数
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期：      版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2023/08/04	     V1.0	  韦东山	      创建
 ***********************************************************************/
void PassiveBuzzer_Init(void)
{
}


/**********************************************************************
 * 函数名称： PassiveBuzzer_Control
 * 功能描述： 无源蜂鸣器控制函数
 * 输入参数： on - 1-响, 0-不响
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期：      版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2023/08/04	     V1.0	  韦东山	      创建
 ***********************************************************************/
void PassiveBuzzer_Control(int on)
{
    if (on)
    {
        HAL_TIM_PWM_Start(g_HPWM_PassiveBuzzer, TIM_CHANNEL_2);
    }        
    else
    {
        HAL_TIM_PWM_Stop(g_HPWM_PassiveBuzzer, TIM_CHANNEL_2);
    }
}

/**********************************************************************
 * 函数名称： PassiveBuzzer_Set_Freq_Duty
 * 功能描述： 无源蜂鸣器控制函数: 设置频率和占空比
 * 输入参数： freq - 频率, duty - 占空比
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期：      版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2023/08/04	     V1.0	  韦东山	      创建
 ***********************************************************************/
void PassiveBuzzer_Set_Freq_Duty(int freq, int duty)
{
    TIM_OC_InitTypeDef sConfig = { 0 };

    HAL_TIM_PWM_Stop(g_HPWM_PassiveBuzzer, TIM_CHANNEL_2);

    HAL_TIM_Base_DeInit(g_HPWM_PassiveBuzzer);
    g_HPWM_PassiveBuzzer->Instance = TIM4;
    g_HPWM_PassiveBuzzer->Init.Prescaler = 71;
    g_HPWM_PassiveBuzzer->Init.CounterMode = TIM_COUNTERMODE_UP;
    g_HPWM_PassiveBuzzer->Init.Period = 1000000 / freq - 1;  
    g_HPWM_PassiveBuzzer->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    g_HPWM_PassiveBuzzer->Init.RepetitionCounter = 0;
    g_HPWM_PassiveBuzzer->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_Base_Init(g_HPWM_PassiveBuzzer);


    sConfig.OCMode = TIM_OCMODE_PWM1;        // PWM 输出的两种模式:PWM1 当极性为低,CCR<CNT,输出低电平,反之高电平
    sConfig.OCPolarity = TIM_OCPOLARITY_HIGH; // 设置极性为低(硬件上低电平亮灯)
    sConfig.OCFastMode = TIM_OCFAST_DISABLE; // 输出比较快速使能禁止(仅在 PWM1 和 PWM2 可设置)
    sConfig.Pulse      = (1000000 / freq - 1) * duty / 100;                // 在 PWM1 模式占空比
    
    HAL_TIM_PWM_ConfigChannel(g_HPWM_PassiveBuzzer, &sConfig, TIM_CHANNEL_2);

    HAL_TIM_PWM_Start(g_HPWM_PassiveBuzzer, TIM_CHANNEL_2);
}


/**********************************************************************
 * 函数名称： PassiveBuzzer_Test
 * 功能描述： 无源蜂鸣器测试程序
 * 输入参数： 无
 * 输出参数： 无
 *            无
 * 返 回 值： 无
 * 修改日期        版本号     修改人        修改内容
 * -----------------------------------------------
 * 2023/08/04        V1.0     韦东山       创建
 ***********************************************************************/
void PassiveBuzzer_Test(void)
{
    PassiveBuzzer_Init();;

    while (1)
    {
    	//PassiveBuzzer_Set_Freq_Duty(2000, 20);
        PassiveBuzzer_Control(1);
        //HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_RESET);
        HAL_Delay(1000);

        //PassiveBuzzer_Set_Freq_Duty(5000, 60);
        PassiveBuzzer_Control(0);
        //HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_SET);
        HAL_Delay(1000);
    }
}

