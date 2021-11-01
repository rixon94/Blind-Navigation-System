/*
 * led.c
 *
 *  Created on: 5 mar 2021
 *      Author: Marcin Kacprzycki
 */
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "main.h"
#include "led.h"

void greenLED(uint32_t delay){
	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);//set the green led on
	 HAL_Delay(delay);
	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);//set the green led off
	 HAL_Delay(delay);
}

void redLED(uint32_t delay){
	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);//set the red led on
	 HAL_Delay(delay);
	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);//set the red led off
	 HAL_Delay(delay);
}

void alarmLed(void){
	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);//set the green led on
	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);//set the green led off
	 HAL_Delay(4);
	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);//set the green led off
	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);//set the red led off


}
