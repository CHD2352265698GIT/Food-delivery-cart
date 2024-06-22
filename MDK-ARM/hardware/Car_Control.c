#include "car_control.h"
#include "motor.h"           
#include "UART.h"      
#include "stdio.h"      
#include "hc_sr04.h"           
#include "infrared.h"        
#include "hx711.h"                 
#include "delay.h"

enum {
	NO,
	YES
};

#define Speak_Evade()  Speaker("/00004*MP3")
#define Speak_Place()  Speaker("/00003*MP3")
#define Speak_Arrive() Speaker("/00006*MP3")
#define Speak_return() Speaker("/00005*MP3")
#define  turn_Round1(ms) \
Infared.switchtemp=0; \
Motor_rightRe();\
Delay_ms(ms);

#define  turn_Round() \
Infared.switchtemp=0; \
Areturn.EnReturn=1;\
Motor_rightRe();\
while(Areturn.ReAdd<2);\
	Areturn.ReAdd=0;\
	Areturn.EnReturn=0;

#define Car_Stop() \
Motor_stop(); \
Infared.switchtemp=0; \


Return Areturn;

//�����Ʒ�Ƿ����
char Check_Have_object(void)
{
	if( Get_Weight() >1000)  //������Ϊ0
	return YES;
	return NO;
}

//����ϰ���
char Check_Have_barrier(void)
{
	Hcsr04Start();
	Hcsr04Read();
	Delay_ms(200);
//	printf("distance:%.1f cm\n", Hcsr04Info.distance);
	if(Hcsr04Info.distance<9.0)return YES;
	return NO;
}

//����Ƿ񵽴����
char Check_Have_wire(void)
{
	char IO[5] ={0};
	IO[0] = HAL_GPIO_ReadPin(IO1_GPIO_Port,IO1_Pin);
	IO[1] = HAL_GPIO_ReadPin(IO2_GPIO_Port,IO2_Pin);
	IO[2] = HAL_GPIO_ReadPin(IO3_GPIO_Port,IO3_Pin);
	IO[3] = HAL_GPIO_ReadPin(IO4_GPIO_Port,IO4_Pin);
	IO[4] = HAL_GPIO_ReadPin(IO5_GPIO_Port,IO5_Pin);
	if(IO[0] == IO[1] && IO[0] == IO[2] && IO[0] == IO[3] && IO[0] == IO[4])
	{
		if(IO[0]==0) return YES;
	}
	return NO;
}
//��鰴��3�Ƿ���
char Check_Have_key3(void)
{
	return !HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin);
}

//������Ŀ�ĵ�
char Car_depart(char* startflage)
{
	static char warning_speak=1;
	if(Check_Have_object() == YES)//��Ʒ����
	{
		Speak_Place();
		*startflage = 1;
		while(Check_Have_key3()!=YES);//�ȴ�����3����
		Motor_start();
		Motor_advance();Delay_ms(500);  //ʻ����ʼ��
		while(Check_Have_wire() != YES) //ֱ����⵽����
		{
			Infared.switchtemp=1;    //�������������
			char exit=1;
			if(Check_Have_barrier() == YES) //��鵽�ϰ���
			{
				while(exit)
				{
					Infared.switchtemp=0;   //�رպ��������
					Motor_rightRe(); //��ת
					Delay_ms(200);
					if(Check_Have_barrier() == NO)
					{
						Motor_advance();//ǰ�����ϰ�ǰ��
						Delay_ms(200);
						Motor_leftIN();
						exit=0;
					}
				}
			}	
			else if(warning_speak)
			{
//				Speak_Evade();   
				warning_speak=0;
			}			
		}
		Speak_Arrive();
		Car_Stop();
		warning_speak=1;
		Delay_ms(3000);
		return 1;
	}
	return 0;
}

//����
char Car_return(char* startflage)
{
	static char warning_speak=1;
	if(Check_Have_object() == NO)//��Ʒȡ��
	{
		Speak_return();
		*startflage=0;
//		while(Check_Have_key3()!=YES);//�ȴ�����3����
		
		turn_Round1(1900);//��ͷ
		
		Motor_advance();Delay_ms(500);  //ʻ����ʼ��
		
		while(Check_Have_wire() != YES) //ֱ����⵽����
		{
			Infared.switchtemp=1;    //�������������
			char exit=1;
			if(Check_Have_barrier() == YES) //��鵽�ϰ���
			{
				while(exit)
				{
					Infared.switchtemp=0;   //�رպ��������
					Motor_rightRe(); //��ת
					Delay_ms(200);
					if(Check_Have_barrier() == NO)
					{
						Motor_advance();//ǰ�����ϰ�ǰ��
						Delay_ms(200);
						Motor_leftIN();
						exit=0;
					}
				}
			}	
			else if(warning_speak)
			{
//				Speak_Evade();
				warning_speak=0;
			}			
		}
		Car_Stop();
		warning_speak=1;
		Delay_ms(3000);
		return 1;
	}
	return 0;
}

