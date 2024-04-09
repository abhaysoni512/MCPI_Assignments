/*
 * led.c
 *
 *  Created on: Mar 29, 2024
 *      Author: Nilesh
 */

#include "led.h"
#include "stm32f4xx.h"

void LedInit(uint32_t pin) {
	// enable gpio clock (in AHB1ENR)
	RCC->AHB1ENR |= BV(LED_GPIO_EN);
	// set gpio pin as output (in MODER)
//	LED_GPIO->MODER &= ~BV(pin * 2 + 1);
//	LED_GPIO->MODER |= BV(pin * 2);
	BB_ALS(&LED_GPIO->MODER, (pin*2)) = 1;
	BB_ALS(&LED_GPIO->MODER, (pin*2+1)) = 0;
	// set gpio pin speed to low (in OSPEEDR)
	//LED_GPIO->OSPEEDR &= ~(BV(pin * 2 + 1) | BV(pin * 2));
	BB_ALS(&LED_GPIO->OSPEEDR, (pin*2)) = 0;
	BB_ALS(&LED_GPIO->OSPEEDR, (pin*2+1)) = 0;
	// set gpio pin no pull up, no pull down (in PUPDR)
	//LED_GPIO->PUPDR &= ~(BV(pin * 2 + 1) | BV(pin * 2));
	BB_ALS(&LED_GPIO->PUPDR, (pin*2)) = 0;
	BB_ALS(&LED_GPIO->PUPDR, (pin*2+1)) = 0;
	// set gpio pin type as push-pull (in OTYPER)
	//LED_GPIO->OTYPER &= ~BV(pin);
	BB_ALS(&LED_GPIO->OTYPER, pin) = 0;
}

void LedOn(uint32_t pin) {
	// set led pin (in ODR)
	//LED_GPIO->ODR |= BV(pin);
	BB_ALS(&LED_GPIO->ODR, pin) = 1;
}

void LedOff(uint32_t pin) {
	// clear led pin (in ODR)
	//LED_GPIO->ODR &= ~BV(pin);
	BB_ALS(&LED_GPIO->ODR, pin) = 0;
}

void LedBlink(uint32_t pin, uint32_t delay) {
	LedOn(pin);
	DelayMs(delay);
	LedOff(pin);
}

