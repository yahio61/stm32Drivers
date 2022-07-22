/*
 * agile_i2c.h
 *      Author: yahya
 */
#include "stdint.h"

#ifndef INC_AGILE_I2C_H_
#define INC_AGILE_I2C_H_

void i2c_init();
void i2c_start();
void i2c_sendData(int8_t data );
void i2c_sendAddress(int8_t address);
char i2c_receive(int8_t slaveAdd, int8_t regAdd);






#endif /* INC_AGILE_I2C_H_ */
