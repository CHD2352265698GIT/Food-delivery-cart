#include "infrared.h"        
#include "gpio.h"
#include "stdio.h"
#include "motor.h"           
#include "car_control.h"
infared Infared={0,0,0,0,0,0};

void Set_Value(char a,char b,char c,char d,char e)
{
	Infared.IO1=a;
	Infared.IO2=b;
	Infared.IO3=c;
	Infared.IO4=d;
	Infared.IO5=e;
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

switch(GPIO_Pin)
{
	case IO1_Pin:printf("IO1,向左0\n"); 
									if(Areturn.EnReturn == 1 )Areturn.ReAdd++;
									if(Infared.switchtemp)
									{
										Motor_left();	
										Set_Value(1,0,0,0,0);	
									}										
	break;                       
	case IO2_Pin:printf("IO2,向左1\n");
									if(Areturn.EnReturn == 1)Areturn.ReAdd++;
									if(Infared.switchtemp)
									{
										Motor_leftIN();
										Set_Value(0,1,0,0,0);	
									}										
							
	break;                       
	case IO3_Pin:printf("IO4,向右1\n");
									if(Areturn.EnReturn==1 && Areturn.ReAdd>0)Areturn.ReAdd--;
								
									if(Infared.switchtemp)
									{
										Motor_rightIN();
										Set_Value(0,0,0,1,0);
									}										
								
	break;                       
	case IO4_Pin:printf("IO3,直走\n");
									if(Infared.switchtemp)
									{
										Motor_advance();
										Set_Value(0,0,1,0,0);
									}										
	break;                       
	case IO5_Pin:printf("IO5,向右0\n");
									if(Areturn.EnReturn==1 && Areturn.ReAdd>0)Areturn.ReAdd--;
									if(Infared.switchtemp)
									{
										Motor_right();	
										Set_Value(0,0,0,0,1);		
									}										
	break;                      
}
}

