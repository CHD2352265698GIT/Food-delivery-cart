#ifndef __HC_SR04_H
#define __HC_SR04_H

#include "main.h"

typedef struct
{
	uint8_t  edge_state;
	uint16_t tim_overflow_counter;
	uint32_t prescaler;
	uint32_t period;
	uint32_t t1;	//	������ʱ��
	uint32_t t2;	//	�½���ʱ��
	uint32_t high_level_us;	//	�ߵ�ƽ����ʱ��
	volatile float    distance; //����
	TIM_TypeDef* instance;
  uint32_t ic_tim_ch;
	HAL_TIM_ActiveChannel active_channel;
}Hcsr04InfoTypeDef;

extern Hcsr04InfoTypeDef Hcsr04Info;

/**
 * @description: ������ģ������벶��ʱ��ͨ����ʼ��
 * @param {TIM_HandleTypeDef} *htim
 * @param {uint32_t} Channel
 * @return {*}
 */
void Hcsr04Init(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @description: HC-SR04����
 * @param {*}
 * @return {*}
 */
void Hcsr04Start(void);

/**
 * @description: ��ʱ����������жϴ�����
 * @param {*}    main.c���ض���void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
 * @return {*}
 */
void Hcsr04TimOverflowIsr(TIM_HandleTypeDef *htim);

/**
 * @description: ���벶�����ߵ�ƽʱ��->����
 * @param {*}    main.c���ض���void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * @return {*}
 */
void Hcsr04TimIcIsr(TIM_HandleTypeDef* htim);

/**
 * @description: ��ȡ����
 * @param {*}
 * @return {*}
 */
float Hcsr04Read(void);
//����������
void Hcsr04_OA(void);

#endif

