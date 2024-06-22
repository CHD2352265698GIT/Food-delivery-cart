#include "UART.h"      
#include "stdio.h"      
#include "string.h"      
uart UART1;
uart UART3;


//串口输出
void Uart1_Send(uint8_t *buf,uint32_t size)//定义一个串口数据发送函数
{
	HAL_UART_Transmit(&huart1, buf, size, Uart_Timeout);
}

int fputc(int data, FILE *f)//改造下fputc函数，将fputc函数的接口改串口上，因为printf里面调用的有fputc，所以到时就可以直接用printf来发送串口数据
{
  Uart1_Send((uint8_t *)&data,1);//调用下刚才声明的串口发送函数
	return data;
}

//串口发送字符串
void UartSend(UART_HandleTypeDef *huart,char* String)
{
		HAL_UART_Transmit(huart, (uint8_t*)String, strlen(String), Uart_Timeout);
}

//清除串口结构体缓存
void UartClean(uart* Uart)
{
	memset(Uart,0,sizeof(uart));//清空缓存结构体
}


void UartInit(UART_HandleTypeDef* UartX,uart* Uarts)	 //串口初始化
{
	HAL_UART_Receive_IT(UartX, (uint8_t *)&Uarts->aRxBuffer, 1);   //开启接收中断
	UartClean(Uarts);//清空结构体
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)	//串口中断回调函数
{
  if(huart == &huart1)
	{
  		HAL_UART_Transmit(&huart3, (uint8_t*)&UART1.aRxBuffer,1, Uart_Timeout);
			UartClean(&UART1);
		HAL_UART_Receive_IT(&huart1, (uint8_t *)&UART1.aRxBuffer, 1);   //再次开启接收中断
	}
	if(huart == &huart3)
	{
		HAL_UART_Transmit(&huart1, (uint8_t*)&UART3.aRxBuffer, 1, Uart_Timeout);
		HAL_UART_Receive_IT(&huart3, (uint8_t *)&UART3.aRxBuffer, 1);   //再次开启接收中断
	}
}
char Speakerdata[15]={
0xAA, 0x08, 0x0B, 0x02 // 0  基于stm32的幼儿园智能送餐小车设计，女声						
};
//2F 30 30 30 30 31 2A 4D 50 33
//播放声音
void Speaker(char* file)
{
	
	uint32_t TEMP=0;
	for(char i=0;i<14;i++)
	{
		(i<10)?Speakerdata[i+4]=file[i]:NULL;
		 TEMP += Speakerdata[i];
	}
	Speakerdata[14]=(uint8_t)TEMP;
//	HAL_UART_Transmit(&huart1, (uint8_t*)Speakerdata, 15, Uart_Timeout);
	HAL_UART_Transmit(&huart3, (uint8_t*)Speakerdata, 15, Uart_Timeout);
	
}
//音量加
void Speaker_up(char up)
{
	uint8_t data[4]={0xAA, 0x14, 0x00, 0xBE};
	for(char i=0;i<up;i++)
	{
	  HAL_UART_Transmit(&huart3, data, 4, Uart_Timeout);
	}
}
//音量减
void Speaker_down(char up)
{
	uint8_t data[4]={0xAA, 0x15, 0x00, 0xBF};
	for(char i=0;i<up;i++)
	{
	  HAL_UART_Transmit(&huart3, data, 4, Uart_Timeout);
	}
}
