/*
 * hc-sr04.h
 *
 *  Created on: 24 lut 2021
 *      Author: Marcin Kacprzycki
 */

#ifndef INC_HC_SR04_H_
#define INC_HC_SR04_H_

#define usTIM TIM1
#define GPIO_PIN_LEFT_SENSOR_TRIG GPIO_PIN_1
#define GPIO_PIN_LEFT_SENSOR_ECHO GPIO_PIN_0

#define GPIO_PIN_FRONT_SENSOR_TRIG GPIO_PIN_5
#define GPIO_PIN_FRONT_SENSOR_ECHO GPIO_PIN_4

#define GPIO_PIN_RIGHT_SENSOR_TRIG GPIO_PIN_7
#define GPIO_PIN_RIGHT_SENSOR_ECHO GPIO_PIN_6

#define EXTI11 GPIO_PIN_11


void sensorTrigerSet(int);
void sensorEchoSet(int);
double sensorGet(int);
float distanceGet(float);
void deactiveAllSensors(void);
extern void us_delay(uint32_t);


#endif /* INC_HC_SR04_H_ */
