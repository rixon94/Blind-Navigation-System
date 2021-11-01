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
#include <stdio.h>
#include "hc-sr04.h"
#include "buzzer.h"
#include "led.h"

#define AREA_RADIUS 190

void setBuzzerLed(int nr){

	switch(nr){
	case 0:
		Buzzer_3((uint32_t)sensorGet(1)*1.5);
		greenLED((uint32_t)sensorGet(1)*1.5);
		redLED((uint32_t)sensorGet(1)*1.5);
		break;

	case 1:
		 Buzzer_2((uint32_t)sensorGet(0)*1.5);
		 redLED((uint32_t)sensorGet(0)*1.5);
		  break;

	case 2:
		Buzzer_1((uint32_t)sensorGet(2)*1.5);
		greenLED((uint32_t)sensorGet(2)*1.5);
		break;

	default:
		break;
	}

}
void uartOutput(void){
	int transferSize, transferSize2;
	char buffer[150], buffer2[150];


	if(sensorGet(1) < AREA_RADIUS){//if the range from sensor 1 is smaller than AREA_RADIUS
		setBuzzerLed(0);
		if(sensorGet(1)<35){
			alarmBuzzer(0);
		}
	}
	else if(sensorGet(0) < AREA_RADIUS){//if the range from sensor 1 is smaller than AREA_RADIUS
		setBuzzerLed(1);
		if(sensorGet(0)<35){
			alarmBuzzer(1);
		}
	  }
	else if(sensorGet(2) < AREA_RADIUS){//if the range from sensor 3 is smaller than AREA_RADIUS
	  setBuzzerLed(2);
		if(sensorGet(2)<35){
			alarmBuzzer(2);
		}
	 }

	  transferSize = snprintf(&buffer[0],150*sizeof(char), "Distance from left sensor_1 to Objekt: %.2f cm\n Distance from front sensor_3 to Objekt: %.2f cm\n ", sensorGet(0), sensorGet(1));
	  if(HAL_UART_Transmit(&hlpuart1, (uint8_t*)buffer, transferSize, 100)!= HAL_OK)
	  {
		  Error_Handler();

	  }

	  transferSize2 = snprintf(&buffer2[0],150*sizeof(char), "\nDistance from right sensor_2 to Objekt: %.2f cm\n", sensorGet(2));
	  if(HAL_UART_Transmit(&hlpuart1, (uint8_t*)buffer2, transferSize2, 100)!= HAL_OK)
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

    /* LPUART1 interrupt Init */
    HAL_NVIC_SetPriority(LPUART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LPUART1_IRQn);
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

    /* LPUART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(LPUART1_IRQn);
  /* USER CODE BEGIN LPUART1_MspDeInit 1 */

  /* USER CODE END LPUART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
