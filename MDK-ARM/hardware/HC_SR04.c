#include "hc_sr04.h"           
#include "tim.h"
#include "stdio.h"
#include "gpio.h"
#include "stm32f1xx_hal.h"
#include "delay.h"           
#include "motor.h"           
#include "infrared.h"        

Hcsr04InfoTypeDef Hcsr04Info;

/**
 * @description: ������ģ������벶��ʱ��ͨ����ʼ��
 * @param {TIM_HandleTypeDef} *htim
 * @param {uint32_t} Channel
 * @return {*}
 */
void Hcsr04Init(TIM_HandleTypeDef *htim, uint32_t Channel)
{
  /*--------[ Configure The HCSR04 IC Timer Channel ] */
  // MX_TIM2_Init();  // cubemx������
  Hcsr04Info.prescaler = htim->Init.Prescaler; //  72-1
  Hcsr04Info.period = htim->Init.Period;       //  65535

  Hcsr04Info.instance = htim->Instance;        //  TIM1
  Hcsr04Info.ic_tim_ch = Channel;
  if(Hcsr04Info.ic_tim_ch == TIM_CHANNEL_1)
  {
    Hcsr04Info.active_channel = HAL_TIM_ACTIVE_CHANNEL_1;             //  TIM_CHANNEL_4
  }
  else if(Hcsr04Info.ic_tim_ch == TIM_CHANNEL_2)
  {
    Hcsr04Info.active_channel = HAL_TIM_ACTIVE_CHANNEL_2;             //  TIM_CHANNEL_4
  }
  else if(Hcsr04Info.ic_tim_ch == TIM_CHANNEL_3)
  {
    Hcsr04Info.active_channel = HAL_TIM_ACTIVE_CHANNEL_3;             //  TIM_CHANNEL_4
  }
  else if(Hcsr04Info.ic_tim_ch == TIM_CHANNEL_4)
  {
    Hcsr04Info.active_channel = HAL_TIM_ACTIVE_CHANNEL_4;             //  TIM_CHANNEL_4
  }
  else if(Hcsr04Info.ic_tim_ch == TIM_CHANNEL_4)
  {
    Hcsr04Info.active_channel = HAL_TIM_ACTIVE_CHANNEL_4;             //  TIM_CHANNEL_4
  }
  /*--------[ Start The ICU Channel ]-------*/
  HAL_TIM_Base_Start_IT(htim);
  HAL_TIM_IC_Start_IT(htim, Channel);
}

/**
 * @description: HC-SR04����
 * @param {*}
 * @return {*}
 */
void Hcsr04Start()
{
  HAL_GPIO_WritePin(GPIOA, trig_Pin, GPIO_PIN_SET);
  Delay_us(10);  //  10us����
  HAL_GPIO_WritePin(GPIOA, trig_Pin, GPIO_PIN_RESET);
}

/**
 * @description: ��ʱ����������жϴ�����
 * @param {*}    main.c���ض���void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
 * @return {*}
 */
void Hcsr04TimOverflowIsr(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == Hcsr04Info.instance) 
  {
    Hcsr04Info.tim_overflow_counter++;
  }
}

/**
 * @description: ���벶�����ߵ�ƽʱ��->����
 * @param {*}    main.c���ض���void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * @return {*}
 */
void Hcsr04TimIcIsr(TIM_HandleTypeDef* htim)
{
  if((htim->Instance == Hcsr04Info.instance) && (htim->Channel == Hcsr04Info.active_channel))
  {
    if(Hcsr04Info.edge_state == 0)      //  ����������
    {
      // �õ������ؿ�ʼʱ��T1�����������벶��Ϊ�½���
      Hcsr04Info.t1 = HAL_TIM_ReadCapturedValue(htim, Hcsr04Info.ic_tim_ch);
      __HAL_TIM_SET_CAPTUREPOLARITY(htim, Hcsr04Info.ic_tim_ch, TIM_INPUTCHANNELPOLARITY_FALLING);
      Hcsr04Info.tim_overflow_counter = 0;  //  ��ʱ���������������
      Hcsr04Info.edge_state = 1;        //  �����ء��½��ز����־λ
    }
    else if(Hcsr04Info.edge_state == 1) //  �����½���
    {
      // �����½���ʱ��T2��������ߵ�ƽʱ��
      Hcsr04Info.t2 = HAL_TIM_ReadCapturedValue(htim, Hcsr04Info.ic_tim_ch);
      Hcsr04Info.t2 += Hcsr04Info.tim_overflow_counter * Hcsr04Info.period; //  ��Ҫ���Ƕ�ʱ������ж�
      Hcsr04Info.high_level_us = Hcsr04Info.t2 - Hcsr04Info.t1; //  �ߵ�ƽ����ʱ�� = �½���ʱ��� - ������ʱ���
      // �������
      Hcsr04Info.distance = (Hcsr04Info.high_level_us / 1000000.0) * 340.0 / 2.0 * 100.0;
      // ���¿��������ز���
      Hcsr04Info.edge_state = 0;  //  һ�βɼ���ϣ�����
      __HAL_TIM_SET_CAPTUREPOLARITY(htim, Hcsr04Info.ic_tim_ch, TIM_INPUTCHANNELPOLARITY_RISING);
    }
  }
}

/**
 * @description: ��ȡ����
 * @param {*}
 * @return {*}
 */
float Hcsr04Read()
{
  // ������޷�
  if(Hcsr04Info.distance >= 450)
  {
    Hcsr04Info.distance = 450;
  }
  return Hcsr04Info.distance;
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//��ʱ���жϺ���
{
  Hcsr04TimIcIsr(htim);
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)//��ʱ������ж�
{
  Hcsr04TimOverflowIsr(htim);
}

//����������
void Hcsr04_OA(void)
{
	static char sequence=0;
	extern char SpeakerToWarning;
  	//ǰ����⵽�ϰ����رպ����⣬��ת
		if(Hcsr04Info.distance<9.0)
		{
			SpeakerToWarning=1;
			Infared.switchtemp=0;
			//��ת
			Motor_rightRe();
			Delay_ms(200);
			sequence=1;
		}
		else{
			//ǰ�����ϰ���ǰ��һ�ξ���
			if(sequence==1)
			{
   			Motor_advance();
				Delay_ms(200);
				Motor_leftIN();

				sequence=0;
				SpeakerToWarning=0;
				Infared.switchtemp=1;//�ָ�������
			}
		}	
	//��ת������������
}

//				if(Infared.IO1){
//					Motor_left();
//				}else if(Infared.IO2)
//				{
//					Motor_leftIN();
//				}else if(Infared.IO3)
//				{
//					Motor_advance();
//				}else if(Infared.IO4)
//				{
//				  Motor_rightIN();
//				}else if(Infared.IO5)
//				{
//					Motor_right();
//				}
