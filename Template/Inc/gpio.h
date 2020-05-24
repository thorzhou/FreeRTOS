/**
  ******************************************************************************
  * File Name          : gpio.h
  * Description        : This file contains all the functions prototypes for 
  *                      the gpio  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */
/* Exported macro ------------------------------------------------------------*/
#define digitalHi(port,pin) {port->BSRR=pin;}
#define digitalLo(port,pin) {port->BSRR=(uint32_t)pin << 16;}
#define digitalToggle(port,pin) {port->ODR ^=pin;}

#define LED1_TOGGLE digitalToggle(LED_R_GPIO_Port,LED_R_Pin)
#define LED1_OFF  digitalHi(LED_R_GPIO_Port,LED_R_Pin)
#define LED1_ON digitalLo(LED_R_GPIO_Port,LED_R_Pin)
#define LED2_TOGGLE digitalToggle(LED_G_GPIO_Port,LED_G_Pin)
#define LED2_OFF digitalHi(LED_G_GPIO_Port,LED_G_Pin)
#define LED2_ON digitalLo(LED_G_GPIO_Port,LED_G_Pin)
#define LED3_TOGGLE digitalToggle(LED_B_GPIO_Port,LED_B_Pin)
#define LED3_OFF digitalHi(LED_B_GPIO_Port,LED_B_Pin)
#define LED3_ON digitalLo(LED_B_GPIO_Port,LED_B_Pin)
//MIX
#define LED_RED {LED1_ON;LED2_OFF;LED3_OFF;}
#define LED_GREEN {LED1_OFF;LED2_ON;LED3_OFF;}
#define LED_BLUE {LED1_OFF;LED2_OFF;LED3_ON;}
#define LED_YELLOW {LED1_ON;LED2_ON;LED3_OFF;}
#define LED_PURPLE {LED1_ON;LED2_OFF;LED3_ON;}
#define LED_CYAN {LED1_OFF;LED2_ON;LED3_ON;}
#define LED_WHITE {LED1_ON;LED2_ON;LED3_ON;}
#define LED_OFF {LED1_OFF;LED2_OFF;LED3_OFF;}

/* Exported functions prototypes ---------------------------------------------*/
void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
