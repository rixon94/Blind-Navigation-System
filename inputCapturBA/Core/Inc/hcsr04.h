/*
 * hcsr04.h
 *
 *  Created on: Apr 17, 2021
 *      Author: Marcin Kacprzycki
 */

#ifndef INC_HCSR04_H_
#define INC_HCSR04_H_

#define usTIM TIM1

double sensorGetInputCapture(int);
void deactiveAllSensors(void);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void us_delay(uint32_t);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void sensorTrigerSet(int number);
void WaitfortTicks(TIM_HandleTypeDef, uint32_t ,uint32_t);
#endif /* INC_HCSR04_H_ */
