#include "hx711.h"                 
#include "gpio.h"
#include "stdio.h"
#include "delay.h"           
uint32_t HX711_Buffer;
uint32_t Weight_Maopi = 8300692;
uint32_t Weight_Shiwu;
uint8_t  Flag_Error=0;
#define GapValue 1
unsigned long Sensor_Read(void)
{
	unsigned long value;
	unsigned char i;
	
	//ÿ�ζ�ȡ����ǰ��֤�����ߵ�ƽ�ȶ�
	//�˴�ֻ��Ϊ���ȶ���ƽ ���߻�����Ч����ͬ
	
	//Ϊ�˵ȴ������ƽ�ȶ�
	//��ÿ��һ������ƽʱ��΢С��ʱ
	Delay_us(2);
	
	//ʱ�������� ����ʱʱ���߱��ֵ͵�λ
	HAL_GPIO_WritePin(GPIOB,hx711_sck_Pin,GPIO_PIN_RESET);
	value=0;
	Delay_us(2);	
	
	//�ȴ�ADת������
	while(HAL_GPIO_ReadPin(hx711_data_GPIO_Port,hx711_data_Pin));
	
	for(i=0;i<24;i++)
	{
		//ʱ�������� ��ʼ����ʱ������
		HAL_GPIO_WritePin(GPIOB,hx711_sck_Pin,GPIO_PIN_SET);
		
		Delay_us(2);
		
		//����λ �Ҳಹ�� �ȴ���������
		value = value << 1;
		
		//ʱ��������
		HAL_GPIO_WritePin(GPIOB,hx711_sck_Pin,GPIO_PIN_RESET);
		
		Delay_us(2);
		
		//��ȡһλ����
		if(HAL_GPIO_ReadPin(hx711_data_GPIO_Port,hx711_data_Pin))
			value ++;
		Delay_us(2);
	}
	
	//��25������
	HAL_GPIO_WritePin(GPIOB,hx711_sck_Pin,GPIO_PIN_SET);
	
	Delay_us(2);
 
	//��25�������½��ص���ʱ ת������
	//�˴�˵����
	//			HX711��һ��24λ��ADת��оƬ
	//			���λ�Ƿ���λ ����Ϊ��Чλ
	//			���������Сֵ0x800000
	//					���ֵ0x7FFFFF
	//������㣺
	//			��ͬΪ0 
	//			��ͬΪ1
	//���ݴ���˵����
	//			֮���Իᷢ�� INPA-INNA < 0mv �����
	//			����Ϊ���������Ư��
	//			������������ݾ��ǳ�ʼ״̬INPA-INNA = -0.5mv
	//			Ȼ���������������ӻᷢ�������
	//			��ʱ���ֱ��ʹ�ö�ȡ�������ݾͻᷢ������
	//			��Ϊ��ȡ������С��0�Ķ����Ʋ���
	//			�ǲ���ֱ��ʹ�õ� ��Ҫת������ԭ��
 
	//			�Ƚϼ򵥵Ĵ��������Ƕ���������ֱ�Ӻ�0x800000�������
	//			��ʱ���λ���Կ�������Чλ
	//			���������λ���������һλ�Ľ�λ
	//			�������ݻ�һֱ�������� 
	//			���ǿ���ֱ����������ʹ��
	value = value^0x800000;
//	value = value&0x7FFFFF;
	
	//��25���������
		HAL_GPIO_WritePin(GPIOB,hx711_sck_Pin,GPIO_PIN_RESET);
	
	Delay_us(2);
	
	return value;
}

void Get_Maopi(void)
{
	Weight_Maopi = Sensor_Read();	
	printf("Weight_Maopi:%d\n",Weight_Maopi);
} 


float P=1;
float P_;  //��Ӧ��ʽ�е�p'
float X=0;
float X_;  //X'
float K=0;
float Q=0.01;//����
//float R=0.2;  //R����ܴ󣬸�����Ԥ��ֵ����ô��������Ӧ�ͻ�ٶۣ���֮�෴
float R=0.5;
float distance=0;
float distance1=0;
float KLM(float Z)
{
  X_=X+0;
  P_=P+Q;
  K=P_/(P_+R);
  X=X_+K*(Z-X_);
  P=P_-K*P_;
  return X;
}
//����
//****************************************************
uint32_t Get_Weight(void)
{
	HX711_Buffer = Sensor_Read();
	if(HX711_Buffer <= Weight_Maopi)			
	{
		Weight_Shiwu = HX711_Buffer;
		Weight_Shiwu = Weight_Maopi-Weight_Shiwu;				      //��ȡʵ���AD������ֵ��	
		Weight_Shiwu = (int32_t)((float)Weight_Shiwu/GapValue); 	//����ʵ���ʵ������
		//��Ϊ��ͬ�Ĵ������������߲�һ������ˣ�ÿһ����������Ҫ���������GapValue���������
		//�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
		//������Գ���������ƫСʱ����С����ֵ��
		Weight_Shiwu=KLM(Weight_Shiwu);
	}else Weight_Shiwu=0;
   return  Weight_Shiwu;
}
 //�Ƿ�������
char hx711_YN=0;
void HX711_check(void)
{
	if(Get_Weight())
	{
	 hx711_YN=1;
	}else hx711_YN=0;
}
