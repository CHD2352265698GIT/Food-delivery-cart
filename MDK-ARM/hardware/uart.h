#ifndef __UART_H
#define __UART_H
#include "usart.h"

struct uart{						//自定义串口结构体
	char temp;						//接收完毕标志位
	char aRxBuffer;		//接收中断缓冲
	unsigned int Uart_Rx_Cnt;			//接收缓冲计数
	char RxBuffer[100];   //数据收发区域
};
typedef struct uart uart;//类型重命名
extern uart UART1;
extern uart UART3;
extern char Speakerdata[15];
#define Uart_Timeout 0xff
void UartInit(UART_HandleTypeDef* UartX,uart* Uarts);	 //串口初始化
//串口发送字符串
void UartSend(UART_HandleTypeDef *huart,char* String);
//播放声音
void Speaker( char* Speakerdata);
//音量加
void Speaker_up(char up);
//音量减
void Speaker_down(char up);

#endif

