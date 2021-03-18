/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "stm32f0xx_ll_crs.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_exti.h"
#include "stm32f0xx_ll_cortex.h"
#include "stm32f0xx_ll_utils.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_dma.h"
#include "stm32f0xx_ll_gpio.h"

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
#define FND_Select0_Pin LL_GPIO_PIN_13
#define FND_Select0_GPIO_Port GPIOC
#define FND_Select1_Pin LL_GPIO_PIN_14
#define FND_Select1_GPIO_Port GPIOC
#define FND_Select2_Pin LL_GPIO_PIN_15
#define FND_Select2_GPIO_Port GPIOC
#define BATT_LEVEL_Pin LL_GPIO_PIN_0
#define BATT_LEVEL_GPIO_Port GPIOA
#define CAP_LEVEL_Pin LL_GPIO_PIN_1
#define CAP_LEVEL_GPIO_Port GPIOA
#define S_CAP_CTRL_Pin LL_GPIO_PIN_2
#define S_CAP_CTRL_GPIO_Port GPIOA
#define FND0_Pin LL_GPIO_PIN_0
#define FND0_GPIO_Port GPIOB
#define FND1_Pin LL_GPIO_PIN_1
#define FND1_GPIO_Port GPIOB
#define FND2_Pin LL_GPIO_PIN_2
#define FND2_GPIO_Port GPIOB
#define PWR6_Pin LL_GPIO_PIN_10
#define PWR6_GPIO_Port GPIOB
#define PWR5_Pin LL_GPIO_PIN_11
#define PWR5_GPIO_Port GPIOB
#define PWR4_Pin LL_GPIO_PIN_12
#define PWR4_GPIO_Port GPIOB
#define PWR3_Pin LL_GPIO_PIN_13
#define PWR3_GPIO_Port GPIOB
#define PWR2_Pin LL_GPIO_PIN_14
#define PWR2_GPIO_Port GPIOB
#define PWR1_Pin LL_GPIO_PIN_15
#define PWR1_GPIO_Port GPIOB
#define FND3_Pin LL_GPIO_PIN_3
#define FND3_GPIO_Port GPIOB
#define FND4_Pin LL_GPIO_PIN_4
#define FND4_GPIO_Port GPIOB
#define FND5_Pin LL_GPIO_PIN_5
#define FND5_GPIO_Port GPIOB
#define FND6_Pin LL_GPIO_PIN_6
#define FND6_GPIO_Port GPIOB
#define FND7_Pin LL_GPIO_PIN_7
#define FND7_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
