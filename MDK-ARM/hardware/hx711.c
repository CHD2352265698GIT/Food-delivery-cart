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
	
	//每次读取数据前保证数据线电平稳定
	//此处只是为了稳定电平 拉高或拉低效果相同
	
	//为了等待输出电平稳定
	//在每次一操作电平时加微小延时
	Delay_us(2);
	
	//时钟线拉低 空闲时时钟线保持低电位
	HAL_GPIO_WritePin(GPIOB,hx711_sck_Pin,GPIO_PIN_RESET);
	value=0;
	Delay_us(2);	
	
	//等待AD转换结束
	while(HAL_GPIO_ReadPin(hx711_data_GPIO_Port,hx711_data_Pin));
	
	for(i=0;i<24;i++)
	{
		//时钟线拉高 开始发送时钟脉冲
		HAL_GPIO_WritePin(GPIOB,hx711_sck_Pin,GPIO_PIN_SET);
		
		Delay_us(2);
		
		//左移位 右侧补零 等待接收数据
		value = value << 1;
		
		//时钟线拉低
		HAL_GPIO_WritePin(GPIOB,hx711_sck_Pin,GPIO_PIN_RESET);
		
		Delay_us(2);
		
		//读取一位数据
		if(HAL_GPIO_ReadPin(hx711_data_GPIO_Port,hx711_data_Pin))
			value ++;
		Delay_us(2);
	}
	
	//第25个脉冲
	HAL_GPIO_WritePin(GPIOB,hx711_sck_Pin,GPIO_PIN_SET);
	
	Delay_us(2);
 
	//第25个脉冲下降沿到来时 转换数据
	//此处说明：
	//			HX711是一款24位的AD转换芯片
	//			最高位是符号位 其余为有效位
	//			输出数组最小值0x800000
	//					最大值0x7FFFFF
	//异或运算：
	//			相同为0 
	//			不同为1
	//数据处理说明：
	//			之所以会发生 INPA-INNA < 0mv 的情况
	//			是因为发生了零点漂移
	//			例如上面的数据就是初始状态INPA-INNA = -0.5mv
	//			然后随着重量的增加会发生过零点
	//			这时如果直接使用读取到的数据就会发生错误
	//			因为读取到的是小于0的二进制补码
	//			是不能直接使用的 需要转换成其原码
 
	//			比较简单的处理方法就是读到的数据直接和0x800000进行异或
	//			这时最高位可以看做是有效位
	//			不代表符号位而代表的下一位的进位
	//			这样数据会一直往上增长 
	//			我们可以直接拿来进行使用
	value = value^0x800000;
//	value = value&0x7FFFFF;
	
	//第25个脉冲结束
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
float P_;  //对应公式中的p'
float X=0;
float X_;  //X'
float K=0;
float Q=0.01;//噪声
//float R=0.2;  //R如果很大，更相信预测值，那么传感器反应就会迟钝，反之相反
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
//称重
//****************************************************
uint32_t Get_Weight(void)
{
	HX711_Buffer = Sensor_Read();
	if(HX711_Buffer <= Weight_Maopi)			
	{
		Weight_Shiwu = HX711_Buffer;
		Weight_Shiwu = Weight_Maopi-Weight_Shiwu;				      //获取实物的AD采样数值。	
		Weight_Shiwu = (int32_t)((float)Weight_Shiwu/GapValue); 	//计算实物的实际重量
		//因为不同的传感器特性曲线不一样，因此，每一个传感器需要矫正这里的GapValue这个除数。
		//当发现测试出来的重量偏大时，增加该数值。
		//如果测试出来的重量偏小时，减小改数值。
		Weight_Shiwu=KLM(Weight_Shiwu);
	}else Weight_Shiwu=0;
   return  Weight_Shiwu;
}
 //是否有物体
char hx711_YN=0;
void HX711_check(void)
{
	if(Get_Weight())
	{
	 hx711_YN=1;
	}else hx711_YN=0;
}
