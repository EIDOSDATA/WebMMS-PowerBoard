/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "fonts.h"
#include "ssd1306.h"
#include "usbd_core.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BAT_MAX_VOLTAGE 14.9f
#define CAM_MAX_VOLTAGE 9.9f
#define ADC_MAX_VAL 4096.0f
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;
DMA_HandleTypeDef hdma_adc;

CAN_HandleTypeDef hcan;

I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim1;

/* USER CODE BEGIN PV */

// USB Setting
extern USBD_HandleTypeDef hUsbDeviceFS;
extern PCD_HandleTypeDef hpcd_USB_FS;
uint8_t usb_inited_f = 0;
uint8_t usb_init_f = 0;

// FND
const uint8_t fnd_segment_arr[] =
	{
		0x3F,	//0
		0x06,	//1
		0x5B,	//2
		0x4F,	//3
		0x66,	//4
		0x6D,	//5
		0x7D,	//6
		0x07,	//7
		0x7F,	//8
		0x6F,	//9
		0x77,	//A
		0x7C,	//B
		0x39,	//C
		0x5E,	//D
		0x79,	//E
		0x71	//F
		};
uint8_t fnd_var[3];
		
// Voltage, Current
uint16_t adc_val[2];		
float bat_volt = 0, cam_volt = 0;
char print_bat[20];
char print_cam[20];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC_Init(void);
static void MX_TIM1_Init(void);
static void MX_I2C1_Init(void);
static void MX_CAN_Init(void);
/* USER CODE BEGIN PFP */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static uint16_t now = 13;
	if (htim->Instance == TIM1)
	{
		HAL_GPIO_WritePin(GPIOC, (1 << now), GPIO_PIN_SET);
		now++;
		if (now >= 16)
		{
			now = 13;
		}
		HAL_GPIO_WritePin(GPIOB, 0x00FF, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, fnd_var[now - 13], GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, (1 << now), GPIO_PIN_RESET);
	}
}

void set_seg_val(uint16_t val, uint8_t ptDigit)
{
	fnd_var[0] = fnd_segment_arr[val / 100]; // 100
	fnd_var[1] = fnd_segment_arr[((val % 100)) / 10]; // 10
	fnd_var[2] = fnd_segment_arr[val % 10]; // 1

	for (uint8_t i = 0; i < 3; i++)
	{
		if (ptDigit & (1 << i))
		{
			fnd_var[i] |= 0x80;
		}
	}
}

void volt_print()
{
	HAL_ADC_Start_DMA(&hadc, (uint32_t *)adc_val, 2);
	for (int i = 0; i < 2; i++)
	{
		HAL_DMA_PollForTransfer(&hdma_adc, HAL_DMA_FULL_TRANSFER, 1000);
	}
	HAL_ADC_Stop_DMA(&hadc);


	bat_volt = ((BAT_MAX_VOLTAGE) / (ADC_MAX_VAL)) * ((float) adc_val[0]);
	cam_volt = ((CAM_MAX_VOLTAGE) / (ADC_MAX_VAL)) * ((float) adc_val[1]);
	if (cam_volt >= 5.3)
	{
		HAL_GPIO_WritePin(S_CAP_CTRL_GPIO_Port, S_CAP_CTRL_Pin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(S_CAP_CTRL_GPIO_Port, S_CAP_CTRL_Pin, GPIO_PIN_RESET);
	}
	set_seg_val((uint16_t) (cam_volt * 100.0), 1 << 0);
	HAL_Delay(50);
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC_Init();
  MX_USB_DEVICE_Init();
  MX_TIM1_Init();
  MX_I2C1_Init();
  MX_CAN_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim1);	
	usb_inited_f = 1;
	ssd1306_Init();
	
	// I2C OLED Init
	ssd1306_Init();
	ssd1306_Fill(Black);
	ssd1306_UpdateScreen();
	
	// I2C OLED Default Print
	ssd1306_SetCursor(18, 0);
	ssd1306_WriteString("Stryx.INC", Font_11x18, White);
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString("batV:", Font_11x18, White);
	ssd1306_SetCursor(0, 40);
	ssd1306_WriteString("camV:", Font_11x18, White);
	ssd1306_UpdateScreen();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		volt_print();
		
		sprintf(print_bat, "%d.%d", (int) bat_volt, (int) (bat_volt * 100) % 100);
		sprintf(print_cam, "%d.%d", (int) cam_volt, (int) (cam_volt * 100) % 100);		

		ssd1306_SetCursor(60, 20);
		ssd1306_WriteString(print_bat, Font_11x18, White);
		ssd1306_SetCursor(60, 40);
		ssd1306_WriteString(print_cam, Font_11x18, White);
		ssd1306_UpdateScreen();

		if (usb_init_f == 1)
		{
			MX_USB_DEVICE_Init();
			usb_init_f = 0;
		}
		else if (usb_init_f == 2)
		{
			HAL_PCD_DevDisconnect(&hpcd_USB_FS);
			USBD_Stop(&hUsbDeviceFS);
			USBD_DeInit(&hUsbDeviceFS);
			usb_init_f = 0;
		}
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
  while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_1)
  {
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {

  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_HSI14_Enable();

   /* Wait till HSI14 is ready */
  while(LL_RCC_HSI14_IsReady() != 1)
  {

  }
  LL_RCC_HSI14_SetCalibTrimming(16);
  LL_RCC_HSI48_Enable();

   /* Wait till HSI48 is ready */
  while(LL_RCC_HSI48_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI48);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI48)
  {

  }
  LL_SetSystemCoreClock(48000000);

   /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler();
  }
  LL_RCC_HSI14_EnableADCControl();
  LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_HSI);
  LL_RCC_SetUSBClockSource(LL_RCC_USB_CLKSOURCE_HSI48);
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN;
  hcan.Init.Prescaler = 3;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_13TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  /* USER CODE END CAN_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x0000020B;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 79;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 600;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

  /**/
  LL_GPIO_ResetOutputPin(FND_Select0_GPIO_Port, FND_Select0_Pin);

  /**/
  LL_GPIO_ResetOutputPin(FND_Select1_GPIO_Port, FND_Select1_Pin);

  /**/
  LL_GPIO_ResetOutputPin(FND_Select2_GPIO_Port, FND_Select2_Pin);

  /**/
  LL_GPIO_ResetOutputPin(S_CAP_CTRL_GPIO_Port, S_CAP_CTRL_Pin);

  /**/
  LL_GPIO_ResetOutputPin(FND0_GPIO_Port, FND0_Pin);

  /**/
  LL_GPIO_ResetOutputPin(FND1_GPIO_Port, FND1_Pin);

  /**/
  LL_GPIO_ResetOutputPin(FND2_GPIO_Port, FND2_Pin);

  /**/
  LL_GPIO_ResetOutputPin(FND3_GPIO_Port, FND3_Pin);

  /**/
  LL_GPIO_ResetOutputPin(FND4_GPIO_Port, FND4_Pin);

  /**/
  LL_GPIO_ResetOutputPin(FND5_GPIO_Port, FND5_Pin);

  /**/
  LL_GPIO_ResetOutputPin(FND6_GPIO_Port, FND6_Pin);

  /**/
  LL_GPIO_ResetOutputPin(FND7_GPIO_Port, FND7_Pin);

  /**/
  LL_GPIO_SetOutputPin(PWR6_GPIO_Port, PWR6_Pin);

  /**/
  LL_GPIO_SetOutputPin(PWR5_GPIO_Port, PWR5_Pin);

  /**/
  LL_GPIO_SetOutputPin(PWR4_GPIO_Port, PWR4_Pin);

  /**/
  LL_GPIO_SetOutputPin(PWR3_GPIO_Port, PWR3_Pin);

  /**/
  LL_GPIO_SetOutputPin(PWR2_GPIO_Port, PWR2_Pin);

  /**/
  LL_GPIO_SetOutputPin(PWR1_GPIO_Port, PWR1_Pin);

  /**/
  GPIO_InitStruct.Pin = FND_Select0_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(FND_Select0_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = FND_Select1_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(FND_Select1_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = FND_Select2_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(FND_Select2_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = S_CAP_CTRL_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(S_CAP_CTRL_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = FND0_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(FND0_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = FND1_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(FND1_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = FND2_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(FND2_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWR6_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(PWR6_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWR5_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(PWR5_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWR4_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(PWR4_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWR3_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(PWR3_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWR2_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(PWR2_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWR1_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(PWR1_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = FND3_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(FND3_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = FND4_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(FND4_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = FND5_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(FND5_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = FND6_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(FND6_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = FND7_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(FND7_GPIO_Port, &GPIO_InitStruct);

  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE8);

  /**/
  LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_8, LL_GPIO_PULL_NO);

  /**/
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_8, LL_GPIO_MODE_INPUT);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_8;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /* EXTI interrupt init*/
  NVIC_SetPriority(EXTI4_15_IRQn, 0);
  NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
