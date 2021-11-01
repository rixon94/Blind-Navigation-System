/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include <string.h>

#include "hcsr04.h"
#include "buzzer.h"
#include "led.h"

#define AREA_RADIUS 300

void setBuzzerLed(int nr){

	switch(nr){
	case 0:
		Buzzer_3((uint32_t)sensorGetInputCapture(0)*10);
		greenLED((uint32_t)sensorGetInputCapture(0)*10);
		redLED((uint32_t)sensorGetInputCapture(0)*10 );
		break;

	case 1:
		 Buzzer_1((uint32_t)sensorGetInputCapture(1)*10);
		 greenLED((uint32_t)sensorGetInputCapture(1)*10);
		  break;

	case 2:
		Buzzer_2((uint32_t)sensorGetInputCapture(2)*10);
		redLED((uint32_t)sensorGetInputCapture(2)*10);
		break;

	default:
		break;
	}

}
void uartOutput(void){
	int transferSize;
	char buffer[150];


	if(sensorGetInputCapture(1) < AREA_RADIUS){//if the range from sensor 1 is smaller than AREA_RADIUS
		setBuzzerLed(1);
		if(sensorGetInputCapture(1)<35){
			alarmBuzzer(0);
		}
	}
	else if(sensorGetInputCapture(0) < AREA_RADIUS){//if the range from sensor 1 is smaller than AREA_RADIUS
		setBuzzerLed(1);
		if(sensorGetInputCapture(0)<35){
			alarmBuzzer(1);
		}
	  }
	else if(sensorGetInputCapture(2) < AREA_RADIUS){//if the range from sensor 3 is smaller than AREA_RADIUS
	  setBuzzerLed(2);
		if(sensorGetInputCapture(2)<35){
			alarmBuzzer(2);
		}
	 }

	  transferSize = snprintf(&buffer[0],150*sizeof(char), " Distance from left sensor_1 to Objekt: %.2f cm\n Distance from right sensor_1 to Objekt: %.2f cm\n Distance from front sensor_1 to Objekt: %.2f cm\n  ",  sensorGetInputCapture(0), sensorGetInputCapture(1), sensorGetInputCapture(2));
	  if(HAL_UART_Transmit(&hlpuart1, (uint8_t*)buffer, transferSize, 100)!= HAL_OK)
	  {
		  Error_Handler();

	  }
}
/* USER CODE END 0 */

UART_HandleTypeDef hlpuart1;

/* LPUART1 init function */

void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 9600;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==LPUART1)
  {
  /* USER CODE BEGIN LPUART1_MspInit 0 */

  /* USER CODE END LPUART1_MspInit 0 */
    /* LPUART1 clock enable */
    __HAL_RCC_LPUART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**LPUART1 GPIO Configuration
    PA2     ------> LPUART1_TX
    PA3     ------> LPUART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_LPUART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN LPUART1_MspInit 1 */

  /* USER CODE END LPUART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==LPUART1)
  {
  /* USER CODE BEGIN LPUART1_MspDeInit 0 */

  /* USER CODE END LPUART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LPUART1_CLK_DISABLE();

    /**LPUART1 GPIO Configuration
    PA2     ------> LPUART1_TX
    PA3     ------> LPUART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

  /* USER CODE BEGIN LPUART1_MspDeInit 1 */

  /* USER CODE END LPUART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
