#ifndef __HC_SR04_H
#define __HC_SR04_H

#include "main.h"

typedef struct
{
	uint8_t  edge_state;
	uint16_t tim_overflow_counter;
	uint32_t prescaler;
	uint32_t period;
	uint32_t t1;	//	上升沿时间
	uint32_t t2;	//	下降沿时间
	uint32_t high_level_us;	//	高电平持续时间
	volatile float    distance; //距离
	TIM_TypeDef* instance;
  uint32_t ic_tim_ch;
	HAL_TIM_ActiveChannel active_channel;
}Hcsr04InfoTypeDef;

extern Hcsr04InfoTypeDef Hcsr04Info;

/**
 * @description: 超声波模块的输入捕获定时器通道初始化
 * @param {TIM_HandleTypeDef} *htim
 * @param {uint32_t} Channel
 * @return {*}
 */
void Hcsr04Init(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @description: HC-SR04触发
 * @param {*}
 * @return {*}
 */
void Hcsr04Start(void);

/**
 * @description: 定时器计数溢出中断处理函数
 * @param {*}    main.c中重定义void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
 * @return {*}
 */
void Hcsr04TimOverflowIsr(TIM_HandleTypeDef *htim);

/**
 * @description: 输入捕获计算高电平时间->距离
 * @param {*}    main.c中重定义void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * @return {*}
 */
void Hcsr04TimIcIsr(TIM_HandleTypeDef* htim);

/**
 * @description: 读取距离
 * @param {*}
 * @return {*}
 */
float Hcsr04Read(void);
//超声波避障
void Hcsr04_OA(void);

#endif

