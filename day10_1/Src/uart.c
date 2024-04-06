/*
 * UART.c
 *
 *  Created on: Apr 1, 2024
 *      Author: abhaysoni512
 */

#include "uart.h"




#define TX_PIN 2
#define RX_PIN 3
#define USART_ALT_FN  7
void UartInit(uint32_t baud){

	//clk enable
	RCC->AHB1ENR |= BV(RCC_AHB1ENR_GPIOAEN_Pos);
	// alt fn =0111 at Uart tx and rx

	GPIOA->AFR[0] |= ((USART_ALT_FN << GPIO_AFRL_AFSEL3_Pos) | (USART_ALT_FN << GPIO_AFRL_AFSEL2_Pos));
	// MODER 10
	GPIOA->MODER &= ~(BV(TX_PIN *2 )|BV(RX_PIN *2));


	//OPSPEEDR 00
	GPIOA->OSPEEDR &= ~(BV(TX_PIN *2 )|BV(RX_PIN *2)|BV(TX_PIN *2 +1)|BV(RX_PIN *2+1));

	//PUPDR -00
	GPIOA->PUPDR &= ~(BV(TX_PIN *2 )|BV(RX_PIN *2)|BV(TX_PIN *2 +1)|BV(RX_PIN *2+1));

	//OTYPER - 0
	GPIOA->MODER &= ~(BV(TX_PIN *2 )|BV(RX_PIN *2));

	//Uart config

	//enable uart clk
	RCC->APB1ENR |= BV(RCC_APB1ENR_USART3EN_Pos); //doubt

	//CR1 TE=1 ,rx en  ,(RE =1), word length=8(M=0) ,OVER8 =0 , PCE =0
	USART2->CR1 = BV((USART_CR1_TE_Pos) |(USART_CR1_RE_Pos));

	//CR2 STOP -00 CLKEN -0
	USART2->CR2 = 0x0;

	//CR3 DEFAULT
	USART2->CR3 = 0x0;

	switch(baud){
	case BAUD_115200 :
		USART2->BRR = BAUD_BRR_115200;
		break;
	case BAUD_9600 :
			USART2->BRR = BAUD_BRR_9600;
			break;
	case BAUD_38400 :
			USART2->BRR = BAUD_BRR_38400;
			break;
	}

	//uart enable (UE=1)
	USART2->CR1 |= BV(USART_CR1_UE_Pos);


}
void UartPutch(uint8_t ch) {
	// wait until TDR is empty (i.e. prev byte transmitted)
	while((USART2->SR & BV(USART_SR_TXE_Pos)) == 0)
		;
	// write new byte in TDR
	USART2->DR = ch;
}

uint8_t UartGetch(void) {
	// wait until RDR is not empty (i.e. new byte received)
	while((USART2->SR & BV(USART_SR_RXNE_Pos)) == 0)
		;
	// read received byte from RDR
	char ch = USART2->DR;
	return ch;
}

void UartPuts(char str[]) {
	int i;
	for(i=0; str[i]!='\0'; i++)
		UartPutch(str[i]);
}

void UartGets(char str[]) {
	int i=0;
	char ch;
	do {
		ch = UartGetch();
		str[i] = ch;
		i++;
	} while(ch != '\r');
	str[i] = '\n';
	i++;
	str[i] = '\0';
}



