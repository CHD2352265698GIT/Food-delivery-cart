#include "motor.h"           
#include "gpio.h"
#include "tim.h"
#include "infrared.h"        

motor Motor={99,99,99,99};
//M1 右前轮
//M2 左前轮
//M3 左后轮
//M4 右后轮

void Set_ThresholdValue(char* value,char up,char button)
{
		if(*value>up)*value=up;
		if(*value<button)*value=button;
}
//前进
void Motor_advance(void)
{
	Set_ThresholdValue(&Motor.speed1,99,0);
	Set_ThresholdValue(&Motor.speed2,99,0);
	Set_ThresholdValue(&Motor.speed3,99,0);
	Set_ThresholdValue(&Motor.speed4,99,0);
	
	
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,Motor.speed1);     //右后轮
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,Motor.speed2);     //左后轮
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,Motor.speed3);     //左前轮
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,Motor.speed4);     //右前轮
	HAL_GPIO_WritePin(GPIOB, m4_in1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, m4_in2_Pin, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(GPIOA, m2_in2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, m2_in1_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOB, m3_in2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, m3_in1_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOA, m1_in2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, m1_in1_Pin, GPIO_PIN_RESET);
}

//后退
void Motor_retreat(void)
{
	HAL_GPIO_WritePin(stby_GPIO_Port, stby_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB,m4_pwm_Pin | m3_pwm_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, m2_pwm_Pin | m1_pwm_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOA, m4_in2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, m4_in1_Pin, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(GPIOA, m2_in2_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, m2_in1_Pin, GPIO_PIN_SET);
	
  HAL_GPIO_WritePin(GPIOA,m1_in2_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,m1_in1_Pin, GPIO_PIN_SET);
	
	HAL_GPIO_WritePin(GPIOB, m3_in1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, m3_in2_Pin, GPIO_PIN_RESET);
}

//停车
void Motor_stop(void)
{
	HAL_GPIO_WritePin(stby_GPIO_Port, stby_Pin, GPIO_PIN_RESET);
}
//恢复
void Motor_start(void)
{
	HAL_GPIO_WritePin(stby_GPIO_Port, stby_Pin, GPIO_PIN_SET);
}
//转向
void Motor_turnTo(char Duty_cycle)
{
	//舵机旋转
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,Duty_cycle);
}
//初始化电机
void Motor_init(void)
{
 //舵机初始化
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_PWM_Start_IT(&htim3,TIM_CHANNEL_1);
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_PWM_Start_IT(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start_IT(&htim2,TIM_CHANNEL_2);
	HAL_TIM_Base_Start_IT(&htim4);
	HAL_TIM_PWM_Start_IT(&htim4,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start_IT(&htim4,TIM_CHANNEL_2);
//	Motor_turnTo(55); //方向回正
	HAL_GPIO_WritePin(stby_GPIO_Port, stby_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, m4_in2_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, m4_in1_Pin, GPIO_PIN_SET);
	
	HAL_GPIO_WritePin(GPIOA, m2_in2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, m2_in1_Pin, GPIO_PIN_RESET);
	
  HAL_GPIO_WritePin(GPIOA,m1_in2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA,m1_in1_Pin, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(GPIOB, m3_in1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, m3_in2_Pin, GPIO_PIN_SET);
	HAL_Delay(500);
}
#define duty_max 88
#define duty_min 20

//舵机测试
void Motor_test()
{
	static char dyct=30;
	static char adv=0;		
	Motor_turnTo(55);
		HAL_Delay(1500);
  Motor_turnTo(duty_max);
		HAL_Delay(1500);
	Motor_turnTo(duty_min);
		HAL_Delay(1500);
		HAL_Delay(20);
		if(dyct!=duty_max && !adv)dyct+=1;
		if(dyct==duty_max || dyct==duty_min) adv=!adv;
		if(dyct!=duty_min && adv)dyct-=1;
		 Motor_turnTo(dyct);
}


//左转外
void Motor_left(void)
{
	HAL_GPIO_WritePin(stby_GPIO_Port, stby_Pin, GPIO_PIN_SET);
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,99); //右
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,5); //左
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,5); //左
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,99); //右
	HAL_GPIO_WritePin(GPIOB, m4_in1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, m4_in2_Pin, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(GPIOA, m2_in2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, m2_in1_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOB, m3_in2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, m3_in1_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOA, m1_in2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, m1_in1_Pin, GPIO_PIN_RESET);
	
}

//右转外
void Motor_right(void)
{
	HAL_GPIO_WritePin(stby_GPIO_Port, stby_Pin, GPIO_PIN_SET);
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,5);  //左
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,99); //右
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,99); //右
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,5);  //左

	HAL_GPIO_WritePin(GPIOB, m4_in1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, m4_in2_Pin, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(GPIOA, m2_in2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, m2_in1_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOB, m3_in2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, m3_in1_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOA, m1_in2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, m1_in1_Pin, GPIO_PIN_RESET);//左转外
}


//左转里
void Motor_leftIN(void)
{
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,99); //右
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,20); //左
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,20); //左
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,99); //右	
}

//右转里
void Motor_rightIN(void)
{
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,20); //右
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,99); //左
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,99); //左
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,20); //右
	
}


//转向
void turnto(void)
{
		if(Infared.IO1){
										Motor.speed1=30;  //向左
										Motor.speed4=30;
									}
		if(Infared.IO2) {
										Motor.speed1=30;  //向左
										Motor.speed4=30;
									}
		if(Infared.IO3) {
										Motor.speed1=99; 
										Motor.speed4=99;
										Motor.speed2=99; 
										Motor.speed3=99;
		}
		if(Infared.IO4)	{
										Motor.speed2=30;  //向右
										Motor.speed3=30;
									}
		if(Infared.IO5){
										Motor.speed2=30;  //向右
										Motor.speed3=30;
									}
}
//后退右转
void Motor_rightRe(void)
{
	//调整方向
		HAL_GPIO_WritePin(stby_GPIO_Port, stby_Pin, GPIO_PIN_SET);
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,99);  //左
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,99); //右
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,99); //右
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,99);  //左

	HAL_GPIO_WritePin(GPIOB, m4_in1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, m4_in2_Pin, GPIO_PIN_SET);
	
	HAL_GPIO_WritePin(GPIOA, m2_in2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, m2_in1_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOB, m3_in2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, m3_in1_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOA, m1_in2_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, m1_in1_Pin, GPIO_PIN_SET);//左转外
}
