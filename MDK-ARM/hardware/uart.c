#include "UART.h"      
#include "stdio.h"      
#include "string.h"      
uart UART1;
uart UART3;


//�������
void Uart1_Send(uint8_t *buf,uint32_t size)//����һ���������ݷ��ͺ���
{
	HAL_UART_Transmit(&huart1, buf, size, Uart_Timeout);
}

int fputc(int data, FILE *f)//������fputc��������fputc�����ĽӿڸĴ����ϣ���Ϊprintf������õ���fputc�����Ե�ʱ�Ϳ���ֱ����printf�����ʹ�������
{
  Uart1_Send((uint8_t *)&data,1);//�����¸ղ������Ĵ��ڷ��ͺ���
	return data;
}

//���ڷ����ַ���
void UartSend(UART_HandleTypeDef *huart,char* String)
{
		HAL_UART_Transmit(huart, (uint8_t*)String, strlen(String), Uart_Timeout);
}

//������ڽṹ�建��
void UartClean(uart* Uart)
{
	memset(Uart,0,sizeof(uart));//��ջ���ṹ��
}


void UartInit(UART_HandleTypeDef* UartX,uart* Uarts)	 //���ڳ�ʼ��
{
	HAL_UART_Receive_IT(UartX, (uint8_t *)&Uarts->aRxBuffer, 1);   //���������ж�
	UartClean(Uarts);//��սṹ��
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)	//�����жϻص�����
{
  if(huart == &huart1)
	{
  		HAL_UART_Transmit(&huart3, (uint8_t*)&UART1.aRxBuffer,1, Uart_Timeout);
			UartClean(&UART1);
		HAL_UART_Receive_IT(&huart1, (uint8_t *)&UART1.aRxBuffer, 1);   //�ٴο��������ж�
	}
	if(huart == &huart3)
	{
		HAL_UART_Transmit(&huart1, (uint8_t*)&UART3.aRxBuffer, 1, Uart_Timeout);
		HAL_UART_Receive_IT(&huart3, (uint8_t *)&UART3.aRxBuffer, 1);   //�ٴο��������ж�
	}
}
char Speakerdata[15]={
0xAA, 0x08, 0x0B, 0x02 // 0  ����stm32���׶�԰�����Ͳ�С����ƣ�Ů��						
};
//2F 30 30 30 30 31 2A 4D 50 33
//��������
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
//������
void Speaker_up(char up)
{
	uint8_t data[4]={0xAA, 0x14, 0x00, 0xBE};
	for(char i=0;i<up;i++)
	{
	  HAL_UART_Transmit(&huart3, data, 4, Uart_Timeout);
	}
}
//������
void Speaker_down(char up)
{
	uint8_t data[4]={0xAA, 0x15, 0x00, 0xBF};
	for(char i=0;i<up;i++)
	{
	  HAL_UART_Transmit(&huart3, data, 4, Uart_Timeout);
	}
}
