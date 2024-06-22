#ifndef __HX711_H__
#define __HX711_H__

#include "stm32f1xx_hal.h"

unsigned long Sensor_Read(void);
uint32_t Get_Weight(void);
void Get_Maopi(void);

extern char hx711_YN;
void HX711_check(void);




#endif
