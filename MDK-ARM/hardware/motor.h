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
//ǰ��
void Motor_advance(void);
//����
void Motor_retreat(void);
//ת��
void Motor_turnTo(char Duty_cycle);
//ͣ��
void Motor_stop(void);
//��ʼ�����
void Motor_init(void);
//��ת
void Motor_left(void);
//��ת
void Motor_right(void);
void Motor_start(void);


//��ת��
void Motor_leftIN(void);
//��ת��
void Motor_rightIN(void);
//ת��
void turnto(void);
void Motor_rightRe(void);

#endif
