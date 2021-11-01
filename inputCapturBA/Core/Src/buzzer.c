/*
 * buzzer.c
 *
 *  Created on: 24 lut 2021
 *      Author: Marcin Kacprzycki
 *
 *Softwarebeschreibung: dieses datei enthalt funktionen fur zwei buzzers steurung, sowie LED's signaliesierung
 */


#include "main.h"
#include "buzzer.h"

#define GPIO_PIN_BUZZER_1 GPIO_PIN_9
#define GPIO_PIN_BUZZER_2 GPIO_PIN_10
#define GPIO_PIN_BUZZER_3 GPIO_PIN_8

void Buzzer_1(uint32_t delay){

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_BUZZER_1, GPIO_PIN_SET);//set the buzzer 1 on
	HAL_Delay(delay);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_BUZZER_1, GPIO_PIN_RESET);//set the buzzer 1 off
	HAL_Delay(delay);

}

void Buzzer_2(uint32_t delay){

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_BUZZER_2, GPIO_PIN_SET);//set the buzzer 2 on
	HAL_Delay(delay);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_BUZZER_2, GPIO_PIN_RESET);//set the buzzer 2 off
	HAL_Delay(delay);
}

void Buzzer_3(uint32_t delay){

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_BUZZER_3, GPIO_PIN_SET);//set the buzzer 2 on
	HAL_Delay(delay);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_BUZZER_3, GPIO_PIN_RESET);//set the buzzer 2 off
	HAL_Delay(delay);
}

void alarmBuzzer(int nr){

	switch(nr)
		{
		case 0:
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_BUZZER_3, GPIO_PIN_SET);//set the buzzer 2 on
	HAL_Delay(2000);
	break;

		case 1:
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_BUZZER_1, GPIO_PIN_SET);//set the buzzer 1 on
	HAL_Delay(2000);
		case 2:
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_BUZZER_2, GPIO_PIN_SET);//set the buzzer 1 on
	HAL_Delay(2000);

		default:
			break;
		}
}

