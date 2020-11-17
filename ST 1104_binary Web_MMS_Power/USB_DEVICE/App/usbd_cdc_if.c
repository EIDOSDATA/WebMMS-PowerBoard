/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : usbd_cdc_if.c
 * @version        : v2.0_Cube
 * @brief          : Usb device for Virtual Com Port.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc_if.h"

/* USER CODE BEGIN INCLUDE */
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
//uint8_t pstat[6] ={ 0, };
uint8_t pstat;
extern uint8_t PwrSFlag;
extern float _bresult;
extern float _cresult;
char buf[20];
uint8_t action = 0;
char Manual[] = "EACH POWER STOPS WHEN YOU PRESS ONE MORE TIME.\r\n\r\n"
		"Print Manual : M\r\n"
		"K : View Voltage\r\n"
		"Q : No.1 Power ON\r\n"
		"W : No.2 Power ON\r\n"
		"E : No.3 Power ON\r\n"
		"R : No.4 Power ON\r\n"
		"T : No.5 Power ON\r\n"
		"Y : No.6 Power ON\r\n\r\n"
		"A : All Activated\r\n"
		"S : Shutdown\r\n"
		"P : Print Power status\r\n\r\n"
		"Z : No.1 Power OFF\r\n"
		"X : No.2 Power OFF\r\n"
		"C : No.3 Power OFF\r\n"
		"V : No.4 Power OFF\r\n"
		"B : No.5 Power OFF\r\n"
		"N : No.6 Power OFF\r\n";
/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
 * @brief Usb device library.
 * @{
 */

/** @addtogroup USBD_CDC_IF
 * @{
 */

/** @defgroup USBD_CDC_IF_Private_TypesDefinitions USBD_CDC_IF_Private_TypesDefinitions
 * @brief Private types.
 * @{
 */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
 * @}
 */

/** @defgroup USBD_CDC_IF_Private_Defines USBD_CDC_IF_Private_Defines
 * @brief Private defines.
 * @{
 */

/* USER CODE BEGIN PRIVATE_DEFINES */
/* USER CODE END PRIVATE_DEFINES */

/**
 * @}
 */

/** @defgroup USBD_CDC_IF_Private_Macros USBD_CDC_IF_Private_Macros
 * @brief Private macros.
 * @{
 */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
 * @}
 */

/** @defgroup USBD_CDC_IF_Private_Variables USBD_CDC_IF_Private_Variables
 * @brief Private variables.
 * @{
 */
/* Create buffer for reception and transmission           */
/* It's up to user to redefine and/or remove those define */
/** Received data over USB are stored in this buffer      */
uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];

/** Data to send over USB CDC are stored in this buffer   */
uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
 * @}
 */

/** @defgroup USBD_CDC_IF_Exported_Variables USBD_CDC_IF_Exported_Variables
 * @brief Public variables.
 * @{
 */

extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */

/**
 * @}
 */

/** @defgroup USBD_CDC_IF_Private_FunctionPrototypes USBD_CDC_IF_Private_FunctionPrototypes
 * @brief Private functions declaration.
 * @{
 */

static int8_t CDC_Init_FS(void);
static int8_t CDC_DeInit_FS(void);
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t *pbuf, uint16_t length);
static int8_t CDC_Receive_FS(uint8_t *pbuf, uint32_t *Len);

/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */
/*
 void GetStatus() __attribute__((always_inline))
 {
 pstat[0] = (PWR1_GPIO_Port->IDR & PWR1_Pin)?0:1;
 pstat[1] = (PWR2_GPIO_Port->IDR & PWR2_Pin)?0:1;
 pstat[2] = (PWR3_GPIO_Port->IDR & PWR3_Pin)?0:1;
 pstat[3] = (PWR4_GPIO_Port->IDR & PWR4_Pin)?0:1;
 pstat[4] = (PWR5_GPIO_Port->IDR & PWR5_Pin)?0:1;
 pstat[5] = (PWR6_GPIO_Port->IDR & PWR6_Pin)?0:1;
 }
 */
void GetStatus()
{
	register uint32_t pstat32;
	pstat32 = (GPIOB->IDR);
	pstat32 >>= 10;
	pstat32 &= 0x3f;
	pstat = (uint8_t) pstat32;
	CDC_Transmit_FS((uint8_t*) &pstat, 1);
}
/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
 * @}
 */

USBD_CDC_ItfTypeDef USBD_Interface_fops_FS =
{ CDC_Init_FS, CDC_DeInit_FS, CDC_Control_FS, CDC_Receive_FS };

/* Private functions ---------------------------------------------------------*/
/**
 * @brief  Initializes the CDC media low layer over the FS USB IP
 * @retval USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CDC_Init_FS(void)
{
	/* USER CODE BEGIN 3 */
	/* Set Application Buffers */
	USBD_CDC_SetTxBuffer(&hUsbDeviceFS, UserTxBufferFS, 0);
	USBD_CDC_SetRxBuffer(&hUsbDeviceFS, UserRxBufferFS);
	return (USBD_OK);
	/* USER CODE END 3 */
}

/**
 * @brief  DeInitializes the CDC media low layer
 * @retval USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CDC_DeInit_FS(void)
{
	/* USER CODE BEGIN 4 */
	return (USBD_OK);
	/* USER CODE END 4 */
}

/**
 * @brief  Manage the CDC class requests
 * @param  cmd: Command code
 * @param  pbuf: Buffer containing command data (request parameters)
 * @param  length: Number of data to be sent (in bytes)
 * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t *pbuf, uint16_t length)
{
	/* USER CODE BEGIN 5 */
	switch (cmd)
	{
	case CDC_SEND_ENCAPSULATED_COMMAND:

		break;

	case CDC_GET_ENCAPSULATED_RESPONSE:

		break;

	case CDC_SET_COMM_FEATURE:

		break;

	case CDC_GET_COMM_FEATURE:

		break;

	case CDC_CLEAR_COMM_FEATURE:

		break;

		/*******************************************************************************/
		/* Line Coding Structure                                                       */
		/*-----------------------------------------------------------------------------*/
		/* Offset | Field       | Size | Value  | Description                          */
		/* 0      | dwDTERate   |   4  | Number |Data terminal rate, in bits per second*/
		/* 4      | bCharFormat |   1  | Number | Stop bits                            */
		/*                                        0 - 1 Stop bit                       */
		/*                                        1 - 1.5 Stop bits                    */
		/*                                        2 - 2 Stop bits                      */
		/* 5      | bParityType |  1   | Number | Parity                               */
		/*                                        0 - None                             */
		/*                                        1 - Odd                              */
		/*                                        2 - Even                             */
		/*                                        3 - Mark                             */
		/*                                        4 - Space                            */
		/* 6      | bDataBits  |   1   | Number Data bits (5, 6, 7, 8 or 16).          */
		/*******************************************************************************/
	case CDC_SET_LINE_CODING:

		break;

	case CDC_GET_LINE_CODING:

		break;

	case CDC_SET_CONTROL_LINE_STATE:

		break;

	case CDC_SEND_BREAK:

		break;

	default:
		break;
	}

	return (USBD_OK);
	/* USER CODE END 5 */
}

/**
 * @brief  Data received over USB OUT endpoint are sent over CDC interface
 *         through this function.
 *
 *         @note
 *         This function will issue a NAK packet on any OUT packet received on
 *         USB endpoint until exiting this function. If you exit this function
 *         before transfer is complete on CDC interface (ie. using DMA controller)
 *         it will result in receiving more data while previous ones are still
 *         not sent.
 *
 * @param  Buf: Buffer of data to be received
 * @param  Len: Number of data received (in bytes)
 * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CDC_Receive_FS(uint8_t *Buf, uint32_t *Len)
{
	/* USER CODE BEGIN 6 */

	/*--- ON ACTION ---*/
	USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
	USBD_CDC_ReceivePacket(&hUsbDeviceFS);
	if (Buf[0] == 0b00000001 || Buf[0] == 'q' || Buf[0] == 'Q')
	{
		HAL_GPIO_WritePin(PWR1_GPIO_Port, PWR1_Pin, RESET);
		GetStatus();
	}
	else if (Buf[0] == 0b00000010 || Buf[0] == 'w' || Buf[0] == 'W')
	{
		HAL_GPIO_WritePin(PWR2_GPIO_Port, PWR2_Pin, RESET);

	}
	else if (Buf[0] == 0b00000100 || Buf[0] == 'e' || Buf[0] == 'E')
	{
		HAL_GPIO_WritePin(PWR3_GPIO_Port, PWR3_Pin, RESET);
		GetStatus();
	}
	else if (Buf[0] == 0b00001000 || Buf[0] == 'r' || Buf[0] == 'R')
	{
		HAL_GPIO_WritePin(PWR4_GPIO_Port, PWR4_Pin, RESET);
		GetStatus();
	}
	else if (Buf[0] == 0b00010000 || Buf[0] == 't' || Buf[0] == 'T')
	{
		HAL_GPIO_WritePin(PWR5_GPIO_Port, PWR5_Pin, RESET);
		GetStatus();
	}
	else if (Buf[0] == 0b00100000 || Buf[0] == 'y' || Buf[0] == 'Y')
	{
		HAL_GPIO_WritePin(PWR6_GPIO_Port, PWR6_Pin, RESET);
		GetStatus();
	}
	/*--- OFF ACTION ---*/
	if (Buf[0] == 0b00000001 || Buf[0] == 'z' || Buf[0] == 'Z')
	{
		HAL_GPIO_WritePin(PWR1_GPIO_Port, PWR1_Pin, SET);
		GetStatus();
	}
	else if (Buf[0] == 0b00000010 || Buf[0] == 'x' || Buf[0] == 'X')
	{
		HAL_GPIO_WritePin(PWR2_GPIO_Port, PWR2_Pin, SET);
		GetStatus();
	}
	else if (Buf[0] == 0b00000100 || Buf[0] == 'c' || Buf[0] == 'C')
	{
		HAL_GPIO_WritePin(PWR3_GPIO_Port, PWR3_Pin, SET);
		GetStatus();
	}
	else if (Buf[0] == 0b00001000 || Buf[0] == 'v' || Buf[0] == 'V')
	{
		HAL_GPIO_WritePin(PWR4_GPIO_Port, PWR4_Pin, SET);
		GetStatus();
	}
	else if (Buf[0] == 0b00010000 || Buf[0] == 'b' || Buf[0] == 'B')
	{
		HAL_GPIO_WritePin(PWR5_GPIO_Port, PWR5_Pin, SET);
		GetStatus();
	}
	else if (Buf[0] == 0b00100000 || Buf[0] == 'n' || Buf[0] == 'N')
	{
		HAL_GPIO_WritePin(PWR6_GPIO_Port, PWR6_Pin, SET);
		GetStatus();
	}
	if (Buf[0] == 0b00111111 || Buf[0] == 0b11111111 || Buf[0] == 'a'
			|| Buf[0] == 'A')
	{
		HAL_GPIO_WritePin(GPIOB, 0xFC00, RESET);
		GetStatus();
	}
	if (Buf[0] == 0x00 || Buf[0] == 's' || Buf[0] == 'S')
	{
		HAL_GPIO_WritePin(GPIOB, 0xFC00, SET);
		GetStatus();
	}
	if (Buf[0] == 'P' || Buf[0] == 'p')
	{
		GetStatus();
	}

	if (Buf[0] == 'm' || Buf[0] == 'M')
	{
		CDC_Transmit_FS((uint8_t*) Manual, strlen(Manual));
	}
	if (Buf[0] == 'i' || Buf[0] == 'I')
	{
		action = 1;
	}
	if (Buf[0] == 'k' || Buf[0] == 'K') // View Voltage
	{
		int btmp = _bresult * 10;
		int ctmp = _cresult * 10;
		sprintf(buf, "bat : %d%d.%d :: cap : %d%d.%d\r\n", btmp / 100,
				(btmp % 100) / 10, btmp % 10, ctmp / 100, (ctmp % 100) / 10,
				ctmp % 10);
		//sprintf(buf, "%d\r\n", tmp);
		CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
	}
	//Buf[0] = -1;
	return (USBD_OK);
	/* USER CODE END 6 */
}

/**
 * @brief  CDC_Transmit_FS
 *         Data to send over USB IN endpoint are sent over CDC interface
 *         through this function.
 *         @note
 *
 *
 * @param  Buf: Buffer of data to be sent
 * @param  Len: Number of data to be sent (in bytes)
 * @retval USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY
 */
uint8_t CDC_Transmit_FS(uint8_t *Buf, uint16_t Len)
{
	uint8_t result = USBD_OK;
	/* USER CODE BEGIN 7 */
	USBD_CDC_HandleTypeDef *hcdc =
			(USBD_CDC_HandleTypeDef*) hUsbDeviceFS.pClassData;
	if (hcdc->TxState != 0)
	{
		return USBD_BUSY;
	}
	USBD_CDC_SetTxBuffer(&hUsbDeviceFS, Buf, Len);
	result = USBD_CDC_TransmitPacket(&hUsbDeviceFS);
	/* USER CODE END 7 */
	return result;
}

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
