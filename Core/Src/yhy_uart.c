/*
 * yhy_uart.c
 *
 *  Created on: Apr 10, 2022
 *      Author: yahya
 */

#include "yhy_uart.h"
#include "main.h"

//Main frequency = 48mhz
//APB1 frequency = 24mhz


void yhy_uart_init(int baudRate){
//-----CLOCK-----
RCC->AHB1ENR |= 1;
HAL_Delay(5);
RCC->APB1ENR |= (1<<17);
HAL_Delay(5);

//-----GPIOA-----
GPIOA->MODER |= (0xA<<4); //alternative funct
GPIOA->OSPEEDR |= (0xF<<4); //very high
GPIOA->AFR[0] |= (0x77<<8); //AF7

//-----USART2-----
if (baudRate == 115200){
	USART2->BRR = (0xD<<4);
}
else{
	USART2->BRR = (0x9C<<4);
	}
USART2->CR1 = 0x200C;//9600
}


void yhy_uart_refresh(void){

}


void yhy_uart_write(int size, char data[size]){
	int sayac = 0;
	while(sayac <= size-1){

		while((USART2->SR & (1<<7)) ==  0); //Is transmission register empty?
		USART2->DR = data[sayac];
		while((USART2->SR & (1<<6)) ==  0); //Transmission completed register wait
		sayac++;
	}
	USART2->DR = 13; //carriage return
	while((USART2->SR & (1<<6)) ==  0); //Transmission completed register wait
	USART2->DR = 10;  //line feed

}


char yhy_uart_read(void){

}
