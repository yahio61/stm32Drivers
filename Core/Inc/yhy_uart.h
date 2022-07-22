/*
 * yhy_uart.h
 *
 *  Created on: 3 Haz 2022
 *      Author: yahya
 */

#ifndef INC_YHY_UART_H_
#define INC_YHY_UART_H_

void yhy_uart_init(int baudRate);	//uart2'yi kurar
void yhy_uart_refresh(void);
void yhy_uart_write(int size, char data[size]);
char yhy_uart_read(void);


#endif /* INC_YHY_UART_H_ */
