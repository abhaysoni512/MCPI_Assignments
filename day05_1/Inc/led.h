/*
 * led.h
 *
 *  Created on: Mar 29, 2024
 *      Author: Nilesh
 */

#ifndef LED_H_
#define LED_H_

#include "stm32f407xx.h"

#define LED_GPIO	GPIOD
#define LED_GPIO_EN	3

#define LED_GREEN	12
#define LED_ORANGE	13
#define LED_RED		14
#define LED_BLUE	15

#define BB_BASE		0x40000000
#define BB_ALS_BASE	0x42000000

//#define BB_ALS_ADDR(b,n) (BB_ALS_BASE + ((uint32_t)b - BB_BASE) * 32 + n * 4)
#define BB_ALS_ADDR(b,n) (BB_ALS_BASE + (((uint32_t)b - BB_BASE) << 5) + (n << 2))
#define BB_ALS(b,n) *((uint32_t*)BB_ALS_ADDR(b,n))

void LedInit(uint32_t pin);
void LedOn(uint32_t pin);
void LedOff(uint32_t pin);
void LedBlink(uint32_t pin, uint32_t delay);

#endif /* LED_H_ */

