#ifndef __MOTOR_H
#define __MOTOR_H



struct motor{
	char speed1;
	char speed2;
	char speed3;
	char speed4;
} ;
typedef struct motor motor;
extern motor Motor;
//前进
void Motor_advance(void);
//后退
void Motor_retreat(void);
//转向
void Motor_turnTo(char Duty_cycle);
//停车
void Motor_stop(void);
//初始化电机
void Motor_init(void);
//左转
void Motor_left(void);
//右转
void Motor_right(void);
void Motor_start(void);


//左转里
void Motor_leftIN(void);
//右转里
void Motor_rightIN(void);
//转向
void turnto(void);
void Motor_rightRe(void);

#endif
