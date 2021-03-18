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
extern float voltage_bat;
extern float voltage_cam;
char buf[50];

uint8_t Action_Flag[6] =
{ 0, 0, 0, 0, 0, 0 };
char Action_Flag_S[6];

char Manual[] = "EACH POWER STOPS WHEN YOU PRESS ONE MORE TIME.\r\n\r\n"
		"Print Manual : M\r\n"
		"K : View Voltage\r\n"
		"Q : No.1 Power ON\r\n"
		"W : No.2 Power ON\r\n"
		"E : No.3 Power ON\r\n"
		"R : No.4 Power ON\r\n"
		"T : No.5 Power ON\r\n"
		"Y : No.6 Power ON\r\n"
		"A : All Activated\r\n"
		"S : Shutdown\r\n\r\n"
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
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length);
static int8_t CDC_Receive_FS(uint8_t* pbuf, uint32_t *Len);

/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */
void Port_ReFresh() __attribute__((always_inline)) // static inline void Port_ReFresh() // void Port_ReFresh() __attribute__((always_inline))
{
	// ON : 1, OFF : 07
	// ON : O, OFF : F, NonConnect : N
	Action_Flag[0] = (PWR1_GPIO_Port->IDR & PWR1_Pin) ? 0 : 1; // 1
	Action_Flag[1] = (PWR1_GPIO_Port->IDR & PWR2_Pin) ? 0 : 1; // 2
	Action_Flag[2] = (PWR1_GPIO_Port->IDR & PWR3_Pin) ? 0 : 1; // 3
	Action_Flag[3] = (PWR1_GPIO_Port->IDR & PWR4_Pin) ? 0 : 1; // 4
	Action_Flag[4] = (PWR1_GPIO_Port->IDR & PWR5_Pin) ? 0 : 1; // 5
	Action_Flag[5] = (PWR1_GPIO_Port->IDR & PWR6_Pin) ? 0 : 1; // 6

	for (int i = 0; i < 6; i++)
	{
		if (Action_Flag[i] == 1)
		{
			Action_Flag_S[i] = 'O';
		}

		else if (Action_Flag[i] == 0)
		{
			Action_Flag_S[i] = 'F';
			/*
			 if(NonConnect)
			 {
			 P_Stat_S[i] = 'N';
			 }
			 */
		}
	}
}

void ResPonse_PSTAT(int p) __attribute__((always_inline)) //static inline void ResPonse_PSTAT(int p) // void ResPonse_PSTAT(int p) __attribute__((always_inline))
{
	Port_ReFresh();
	switch (p)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		sprintf(buf, "#pstat,%d,%c\r\n", p, Action_Flag_S[p - 1]);
		break;
	default:
		sprintf(buf, "\r\n#pstat,1,%c\r\n"
				"#pstat,2,%c\r\n"
				"#pstat,3,%c\r\n"
				"#pstat,4,%c\r\n"
				"#pstat,5,%c\r\n"
				"#pstat,6,%c\r\n\r\n", Action_Flag_S[0], Action_Flag_S[1], Action_Flag_S[2],
				Action_Flag_S[3], Action_Flag_S[4], Action_Flag_S[5]);
		break;
	}
}



/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */

USBD_CDC_ItfTypeDef USBD_Interface_fops_FS =
{
  CDC_Init_FS,
  CDC_DeInit_FS,
  CDC_Control_FS,
  CDC_Receive_FS
};

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
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length)
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
		// 115200bps, 1stop, no parity, 8bit
		static uint8_t lineCoding[7] =
		{ 0x00, 0xC2, 0x01, 0x00, 0x00, 0x00, 0x08 }; // 0001c200 >> 115200 arr[3],arr[2],arr[1],arr[0]
	case CDC_SET_LINE_CODING:
		memcpy(lineCoding, pbuf, sizeof(lineCoding));
		break;

	case CDC_GET_LINE_CODING:
		memcpy(pbuf, lineCoding, sizeof(lineCoding));
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
static int8_t CDC_Receive_FS(uint8_t* Buf, uint32_t *Len)
{
  /* USER CODE BEGIN 6 */
	USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
	USBD_CDC_ReceivePacket(&hUsbDeviceFS);
	Port_ReFresh(); // USB Key INPUT : Data ReFresh	
	
	
	/*--- ON ACTION ---*/
	if (Buf[0] == 'q' || Buf[0] == 'Q')
	{
		if (Action_Flag_S[0] == 'O')
		{
			sprintf(buf, "#Already On\r\n");
			CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
		}
		else if (Action_Flag_S[0] == 'F')
		{
			sprintf(buf, "#Activated\r\n");
			CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
			HAL_GPIO_WritePin(PWR1_GPIO_Port, PWR1_Pin, RESET);
		}
		else // NON Connect
		{
			sprintf(buf, "#No Cable Connected\r\n");
			CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
		}
	}
	else if (Buf[0] == 'w' || Buf[0] == 'W')
	{
		if (Action_Flag_S[1] == 'O')
		{
			sprintf(buf, "#Already On\r\n");
			CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
		}
		else if (Action_Flag_S[1] == 'F')
		{
			sprintf(buf, "#Activated\r\n");
			CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
			HAL_GPIO_WritePin(PWR2_GPIO_Port, PWR2_Pin, RESET);
		}
		else // NON Connect
		{
			sprintf(buf, "#No Cable Connected\r\n");
			CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
		}
	}
	else if (Buf[0] == 'e' || Buf[0] == 'E')
	{
		if (Action_Flag_S[2] == 'O')
		{
			sprintf(buf, "#Already On\r\n");
			CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
		}
		else if (Action_Flag_S[2] == 'F')
		{
			sprintf(buf, "#Activated\r\n");
			CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
			HAL_GPIO_WritePin(PWR3_GPIO_Port, PWR3_Pin, RESET);
		}
		else // NON Connect
		{
			sprintf(buf, "#No Cable Connected\r\n");
			CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
		}
	}
	else if (Buf[0] == 'r' || Buf[0] == 'R')
	{
		if (Action_Flag_S[3] == 'O')
		{
			sprintf(buf, "#Already On\r\n");
			CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
		}
		else if (Action_Flag_S[3] == 'F')
		{
			sprintf(buf, "#Activated\r\n");
			CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
			HAL_GPIO_WritePin(PWR4_GPIO_Port, PWR4_Pin, RESET);
		}
		else // NON Connect
		{
			sprintf(buf, "#No Cable Connected\r\n");
			CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
		}
	}
	else if (Buf[0] == 't' || Buf[0] == 'T')
	{
		if (Action_Flag_S[4] == 'O')
		{
			sprintf(buf, "#Already On\r\n");
			CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
		}
		else if (Action_Flag_S[4] == 'F')
		{
			sprintf(buf, "#Activated\r\n");
			CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
			HAL_GPIO_WritePin(PWR5_GPIO_Port, PWR5_Pin, RESET);
		}
		else // NON Connect
		{
			sprintf(buf, "#No Cable Connected\r\n");
			CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
		}
	}
	else if (Buf[0] == 'y' || Buf[0] == 'Y')
	{
		if (Action_Flag_S[5] == 'O')
		{
			sprintf(buf, "#Already On\r\n");
			CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
		}
		else if (Action_Flag_S[5] == 'F')
		{
			sprintf(buf, "#Activated\r\n");
			CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
			HAL_GPIO_WritePin(PWR6_GPIO_Port, PWR6_Pin, RESET);
		}
		else // NON Connect
		{
			sprintf(buf, "#No Cable Connected\r\n");
			CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
		}
	}
	/*--- OFF ACTION ---*/
	if (Buf[0] == 'z' || Buf[0] == 'Z')
	{
		HAL_GPIO_WritePin(PWR1_GPIO_Port, PWR1_Pin, SET);
		CDC_Transmit_FS((uint8_t*) "PW1 : OFF\r\n", 11);		
	}
	else if (Buf[0] == 'x' || Buf[0] == 'X')
	{
		HAL_GPIO_WritePin(PWR2_GPIO_Port, PWR2_Pin, SET);
		CDC_Transmit_FS((uint8_t*) "PW2 : OFF\r\n", 11);		
	}
	else if (Buf[0] == 'c' || Buf[0] == 'C')
	{
		HAL_GPIO_WritePin(PWR3_GPIO_Port, PWR3_Pin, SET);
		CDC_Transmit_FS((uint8_t*) "PW3 : OFF\r\n", 11);		
	}
	else if (Buf[0] == 'v' || Buf[0] == 'V')
	{
		HAL_GPIO_WritePin(PWR4_GPIO_Port, PWR4_Pin, SET);
		CDC_Transmit_FS((uint8_t*) "PW4 : OFF\r\n", 11);		
	}
	else if (Buf[0] == 'b' || Buf[0] == 'B')
	{
		HAL_GPIO_WritePin(PWR5_GPIO_Port, PWR5_Pin, SET);
		CDC_Transmit_FS((uint8_t*) "PW5 : OFF\r\n", 11);		
	}
	else if (Buf[0] == 'n' || Buf[0] == 'N')
	{
		HAL_GPIO_WritePin(PWR6_GPIO_Port, PWR6_Pin, SET);
		CDC_Transmit_FS((uint8_t*) "PW6 : OFF\r\n", 11);		
	}
	
	
	if (Buf[0] == 'a' || Buf[0] == 'A')
	{
		Action_Flag_S[0] == 'O' ?
				NULL : HAL_GPIO_WritePin(PWR1_GPIO_Port, PWR1_Pin, RESET);
		Action_Flag_S[1] == 'O' ?
				NULL : HAL_GPIO_WritePin(PWR2_GPIO_Port, PWR2_Pin, RESET);
		Action_Flag_S[2] == 'O' ?
				NULL : HAL_GPIO_WritePin(PWR3_GPIO_Port, PWR3_Pin, RESET);
		Action_Flag_S[3] == 'O' ?
				NULL : HAL_GPIO_WritePin(PWR4_GPIO_Port, PWR4_Pin, RESET);
		Action_Flag_S[4] == 'O' ?
				NULL : HAL_GPIO_WritePin(PWR5_GPIO_Port, PWR5_Pin, RESET);
		Action_Flag_S[5] == 'O' ?
				NULL : HAL_GPIO_WritePin(PWR6_GPIO_Port, PWR6_Pin, RESET);
		
		CDC_Transmit_FS((uint8_t*) "PW ALL : ON\r\n", 13);		
	}
	if (Buf[0] == 's' || Buf[0] == 'S')
	{
		CDC_Transmit_FS((uint8_t*) "PW ALL : OFF\r\n", 14);
		HAL_GPIO_WritePin(GPIOB, 0xFC00, SET);		
	}
	
	if (Buf[0] == 'm' || Buf[0] == 'M')
	{
		CDC_Transmit_FS((uint8_t*) Manual, strlen(Manual));
	}
	if (Buf[0] == 'k' || Buf[0] == 'K')
	{		
		sprintf(buf,"#vin,%d.%d\r\n"
								"#vcam,%d.%d\r\n\r\n",
		(int) voltage_bat, (int) (voltage_bat * 100) % 100,
		(int) voltage_cam, (int) (voltage_cam * 100) % 100);

		CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
	}
	if (Buf[0] == 'p' || Buf[0] == 'P')
	{
		ResPonse_PSTAT(0);
		CDC_Transmit_FS((uint8_t*) buf, strlen(buf));
	}
	
	
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
uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len)
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
