/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define stby_Pin GPIO_PIN_13
#define stby_GPIO_Port GPIOC
#define KEY1_Pin GPIO_PIN_14
#define KEY1_GPIO_Port GPIOC
#define KEY2_Pin GPIO_PIN_15
#define KEY2_GPIO_Port GPIOC
#define m2_pwm_Pin GPIO_PIN_0
#define m2_pwm_GPIO_Port GPIOA
#define m1_pwm_Pin GPIO_PIN_1
#define m1_pwm_GPIO_Port GPIOA
#define m1_in2_Pin GPIO_PIN_4
#define m1_in2_GPIO_Port GPIOA
#define m1_in1_Pin GPIO_PIN_5
#define m1_in1_GPIO_Port GPIOA
#define m2_in1_Pin GPIO_PIN_6
#define m2_in1_GPIO_Port GPIOA
#define m2_in2_Pin GPIO_PIN_7
#define m2_in2_GPIO_Port GPIOA
#define m3_in1_Pin GPIO_PIN_0
#define m3_in1_GPIO_Port GPIOB
#define m3_in2_Pin GPIO_PIN_1
#define m3_in2_GPIO_Port GPIOB
#define IO1_Pin GPIO_PIN_12
#define IO1_GPIO_Port GPIOB
#define IO1_EXTI_IRQn EXTI15_10_IRQn
#define IO2_Pin GPIO_PIN_13
#define IO2_GPIO_Port GPIOB
#define IO2_EXTI_IRQn EXTI15_10_IRQn
#define IO3_Pin GPIO_PIN_14
#define IO3_GPIO_Port GPIOB
#define IO3_EXTI_IRQn EXTI15_10_IRQn
#define IO4_Pin GPIO_PIN_15
#define IO4_GPIO_Port GPIOB
#define IO4_EXTI_IRQn EXTI15_10_IRQn
#define IO5_Pin GPIO_PIN_8
#define IO5_GPIO_Port GPIOA
#define IO5_EXTI_IRQn EXTI9_5_IRQn
#define echo_Pin GPIO_PIN_11
#define echo_GPIO_Port GPIOA
#define trig_Pin GPIO_PIN_12
#define trig_GPIO_Port GPIOA
#define m4_in2_Pin GPIO_PIN_15
#define m4_in2_GPIO_Port GPIOA
#define m4_in1_Pin GPIO_PIN_3
#define m4_in1_GPIO_Port GPIOB
#define KEY3_Pin GPIO_PIN_5
#define KEY3_GPIO_Port GPIOB
#define m4_pwm_Pin GPIO_PIN_6
#define m4_pwm_GPIO_Port GPIOB
#define m3_pwm_Pin GPIO_PIN_7
#define m3_pwm_GPIO_Port GPIOB
#define hx711_data_Pin GPIO_PIN_8
#define hx711_data_GPIO_Port GPIOB
#define hx711_sck_Pin GPIO_PIN_9
#define hx711_sck_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
