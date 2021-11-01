/*
 * led.c
 *
 *  Created on: 5 mar 2021
 *      Author: Marcin Kacprzycki
 */
/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "main.h"
#include "led.h"
/* defines------------------------------------*/
#define GPIO_PIN_RED_LED GPIO_PIN_12
#define GPIO_PIN_GREEN_LED GPIO_PIN_0

void statusLED(void){
	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);//set the green led on

}
void greenLED(uint32_t delay){
	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_GREEN_LED, GPIO_PIN_SET);//set the green led on
	 HAL_Delay(delay);
	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_GREEN_LED, GPIO_PIN_RESET);//set the green led off
	 HAL_Delay(delay);
}

void redLED(uint32_t delay){
	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_RED_LED, GPIO_PIN_SET);//set the red led on
	 HAL_Delay(delay);
	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_RED_LED, GPIO_PIN_RESET);//set the red led off
	 HAL_Delay(delay);
}

void alarmLed(void){
	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);//set the green led on
	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);//set the green led off
	 HAL_Delay(4);
	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);//set the green led off
	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);//set the red led off


}
