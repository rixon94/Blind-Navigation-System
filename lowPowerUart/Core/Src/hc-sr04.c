/*
 * hc-sr04.c
 *
 *  Created on: 24 lut 2021
 *      Author: Marcin Kacprzycki
 *
 Software Beschreibung:
Dieses Software dient zum  Steurung 3 hcsr04-ultraschalt Sensoren.
Es enthaelt funktionen fur initialisung 3 Ultra schalt Sensoren - HCSR04
als auch daten von sensoren auslesen.
*/

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "main.h"
#include "buzzer.h"
#include "hc-sr04.h"

const float speedOfSound = 0.0343; // speed of sound wave in cm/uSec
uint32_t numTicks;

void deactiveAllSensors(void){

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_LEFT_SENSOR_TRIG, GPIO_PIN_RESET);	//set the TRIG1 to low for 10 uSec
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_FRONT_SENSOR_TRIG, GPIO_PIN_RESET);//set the TRIG2 to low for 10 uSec
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_RIGHT_SENSOR_TRIG, GPIO_PIN_RESET);//set the TRIG3 to low for 10 uSec
	us_delay(3);
}

float distanceGet(float distanceSensor){

	distanceSensor = (numTicks + 0.0f)*2.8*speedOfSound;//count distance in cm (2.8 is number of microseconds pro takt)

	return distanceSensor;
}

void sensorTrigerSet(int number)
{
	switch(number){
	case 0:
		//measure of ultrasonic sensor 1 start
		//Output TRIG1 for 10 uSec
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_LEFT_SENSOR_TRIG, GPIO_PIN_SET);
		us_delay(10);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_LEFT_SENSOR_TRIG, GPIO_PIN_RESET);
		break;

	case 1:
		//measure of ultrasonic sensor 2 start
		//Output TRIG2 for 10 uSec
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_FRONT_SENSOR_TRIG, GPIO_PIN_SET);
		us_delay(10);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_FRONT_SENSOR_TRIG, GPIO_PIN_RESET);
		break;

	case 2:
		//measure of ultrasonic sensor 3 start
		//Output TRIG3 for 10 uSec
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_RIGHT_SENSOR_TRIG, GPIO_PIN_SET);
		us_delay(10);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_RIGHT_SENSOR_TRIG, GPIO_PIN_RESET);
		break;

	default:
		break;
	}
}

void sensorEchoSet(int number){

	switch(number){
		case 0:
			while( HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_LEFT_SENSOR_ECHO) == GPIO_PIN_RESET);//wait for ECHO1  pin rising edge

			//measuring ECHO1 pulse width in uSec
			numTicks = 0 ;
			while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_LEFT_SENSOR_ECHO) == GPIO_PIN_SET)
			{
				numTicks++;
				us_delay(2);
			};
			break;

		case 1:
			while( HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_FRONT_SENSOR_ECHO) == GPIO_PIN_RESET);//wait for ECHO2  pin rising edge

			//measuring ECHO2 pulse width in uSec
			numTicks = 0 ;
			while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_FRONT_SENSOR_ECHO) == GPIO_PIN_SET)
			{
				numTicks++;
				us_delay(2);
			};
			break;

		case 2:
			while( HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_RIGHT_SENSOR_ECHO) == GPIO_PIN_RESET);//wait for ECHO3  pin rising edge

			//measuring ECHO3 pulse width in uSec
			numTicks = 0 ;
			while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_RIGHT_SENSOR_ECHO) == GPIO_PIN_SET)
			{
				numTicks++;
				us_delay(2);
			};
			break;

		default:
			break;
	}
}


double sensorGet(int number){

	float distance = 0.0f;

	deactiveAllSensors();

	switch(number){
	case 0:
		sensorTrigerSet(0);
		sensorEchoSet(0);
		break;

	case 1:
		sensorTrigerSet(1);
		sensorEchoSet(1);
		break;

	case 2:
		sensorTrigerSet(2);
		sensorEchoSet(2);
		break;

	default :
		return 0.0;
	}
	return distanceGet(distance);
}

void us_delay(uint32_t uSec){
	if(uSec < 2) uSec = 2;
	usTIM->ARR = uSec-1;// set the value in the auto-reload register
	usTIM->EGR = 1;//re-init the timer
	usTIM->SR &=~1;//reset the flag
	usTIM->CR1 |=1;//enable the counter
	while((usTIM->SR&0x0001) !=1);
	usTIM->SR &=~(0X0001);
}

