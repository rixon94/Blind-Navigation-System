/*
 * hcsr04.c
 *
 *  Created on: Apr 17, 2021
 *      Author: Marcin Kacprzycki
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

#include "main.h"
#include "buzzer.h"
#include "hcsr04.h"
#include "led.h"

#define GPIO_PIN_LEFTSENSOR GPIO_PIN_4
#define GPIO_PIN_RIGHTSENSOR GPIO_PIN_5
#define GPIO_PIN_FRONTSENSOR GPIO_PIN_4

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim16;

uint8_t volatile icFlag = 0;
uint8_t  volatile captureIdx = 0;
//left sensor edges
uint32_t volatile edge2Time = 0;
uint32_t volatile edge1Time = 0;
//right sensor edges
uint32_t volatile edge4Time = 0;
uint32_t volatile edge3Time = 0;
//front sensor edges
uint32_t volatile edge5Time = 0;
uint32_t volatile edge6Time = 0;

/* USER CODE BEGIN 1 */
float distance = 0.0f;

const float speedOfSound = 0.0343/2; // speed of sound wave in cm/uSec

void us_delay(uint32_t uSec){
	if(uSec < 2) uSec = 2;
	usTIM->ARR = uSec-1;// set the value in the auto-reload register
	usTIM->EGR = 1;//re-init the timer
	usTIM->SR &=~1;//reset the flag
	usTIM->CR1 |=1;//enable the counter
	while((usTIM->SR&0x0001) !=1);
	usTIM->SR &=~(0X0001);
}

void deactiveAllSensors(void){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_RIGHTSENSOR, GPIO_PIN_RESET);	//set the TRIG1 to low for 10 uSec
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_FRONTSENSOR, GPIO_PIN_RESET);//set the TRIG2 to low for 10 uSec
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_LEFTSENSOR, GPIO_PIN_RESET);//set the TRIG3 to low for 10 uSec
	us_delay(3);
}

void sensorTrigerSet(int number){

	switch(number){
	case 0:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_LEFTSENSOR, GPIO_PIN_SET);
		us_delay(10);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_LEFTSENSOR, GPIO_PIN_RESET);
		break;

	case 1:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_RIGHTSENSOR, GPIO_PIN_SET);
		us_delay(10);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_RIGHTSENSOR, GPIO_PIN_RESET);
		break;

	case 2:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_FRONTSENSOR, GPIO_PIN_SET);
		us_delay(10);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_FRONTSENSOR, GPIO_PIN_RESET);
		break;
	}
}


void WaitfortTicks(TIM_HandleTypeDef htim ,  uint32_t tim_Channel, uint32_t tick)
{

	HAL_TIM_IC_Start_IT(&htim,tim_Channel);

	uint32_t startTick = HAL_GetTick();
	do{
		if(icFlag) break;
	}
	while((HAL_GetTick() - startTick < tick));
	icFlag = 0;

	HAL_TIM_IC_Stop_IT(&htim,tim_Channel);
}

double sensorGetInputCapture(int number){

	deactiveAllSensors();

	  switch(number){
		case 0:
			sensorTrigerSet(0);

			WaitfortTicks(htim1 , TIM_CHANNEL_4, 500);

			if(edge2Time > edge1Time){
				distance = ((edge2Time - edge1Time) + 0.0f)*speedOfSound;
			}
			else{
				distance = 0.0f;
			}

		case 1:
			sensorTrigerSet(1);


			WaitfortTicks(htim2, TIM_CHANNEL_2, 500);

			if(edge4Time > edge3Time){
				distance = ((edge4Time - edge3Time) + 0.0f)*speedOfSound;
			}
			else{
				distance = 0.0f;
			}
			break;

		case 2:
			sensorTrigerSet(2);

			WaitfortTicks(htim16, TIM_CHANNEL_1, 500);

			if(edge6Time > edge5Time){
				distance = ((edge6Time - edge5Time) + 0.0f)*speedOfSound;
			}
			else{
				distance = 0.0f;
			}
			break;

		default:
			return 0.0f;
			break;
	}
	return distance;
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){

	if(htim == &htim2){

	 if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)  // if the interrupt source is channel1
	{
		if(captureIdx == 0){ //first edge
			edge1Time = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);//get counter(htim2)
			captureIdx = 1;
		}
		else if(captureIdx == 1){//second edge
			edge2Time = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);//get counter(htim2)////
			captureIdx = 0;
			icFlag = 1;
								}
	}
	  	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)  // if the interrupt source is channel1
		{
		if(captureIdx == 0){ //first edge
			edge3Time = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);//get counter(htim2)
			captureIdx = 1;
		}
		else if(captureIdx == 1){//second edge
			edge4Time = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);//get counter(htim2)

			captureIdx = 0;
			icFlag = 1;
							}
		}
	}

	if(htim == &htim16){
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)  // if the interrupt source is channel1
			{
		if(captureIdx == 0){ //first edge
			edge5Time = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);//get counter(htim2)
			captureIdx = 1;
		}
		else if(captureIdx == 1){//second edge
			edge6Time = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);//get counter(htim2)
			captureIdx = 0;
			icFlag = 1;
		}
			}
			}
}



