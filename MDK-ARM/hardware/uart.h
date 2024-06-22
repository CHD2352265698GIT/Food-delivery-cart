#ifndef __UART_H
#define __UART_H
#include "usart.h"

struct uart{						//�Զ��崮�ڽṹ��
	char temp;						//������ϱ�־λ
	char aRxBuffer;		//�����жϻ���
	unsigned int Uart_Rx_Cnt;			//���ջ������
	char RxBuffer[100];   //�����շ�����
};
typedef struct uart uart;//����������
extern uart UART1;
extern uart UART3;
extern char Speakerdata[15];
#define Uart_Timeout 0xff
void UartInit(UART_HandleTypeDef* UartX,uart* Uarts);	 //���ڳ�ʼ��
//���ڷ����ַ���
void UartSend(UART_HandleTypeDef *huart,char* String);
//��������
void Speaker( char* Speakerdata);
//������
void Speaker_up(char up);
//������
void Speaker_down(char up);

#endif

