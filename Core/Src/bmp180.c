/*
 * bmp180.c
 *
 *  Created on: 6 Tem 2022
 *      Author: yahya
 */

#include "main.h"
#include "stdint.h"
#include "agile_i2c.h"
#include "math.h"
#include "bmp180.h"


int16_t AC1 = 0;
int16_t AC2 = 0;
int16_t AC3 = 0;
uint16_t AC4 = 0;
uint16_t AC5 = 0;
uint16_t AC6 = 0;
int16_t B1 = 0;
int16_t B2 = 0;
int16_t MB = 0;
int16_t MC = 0;
int16_t MD = 0;
int16_t UT = 0;

char data[22];

static void bmp180_parametreAl();
static void bmp180_hamSicaklik_al();

void bmp180_baslat()
{
	bmp180_parametreAl();
}


static void bmp180_parametreAl()
{
	i2c_veriAl(0xEE, 0xAA, 22, &data[0]);
	AC1 = data[0]<<8 | data[1];
	AC2 = data[2]<<8 | data[3];
	AC3 = data[4]<<8 | data[5];
	AC4 = data[6]<<8 | data[7];
	AC5 = data[8]<<8 | data[9];
	AC6 = data[10]<<8 | data[11];
	B1 = data[12]<<8 | data[13];
	B2 = data[14]<<8 | data[15];
	MB = data[16]<<8 | data[17];
	MC = data[18]<<8 | data[19];
	MD = data[20]<<8 | data[21];
}


static void bmp180_hamSicaklik_al()
{
	i2c_yaz(0xEE, 0xF4, 0x2E);
	HAL_Delay(5);
	i2c_veriAl(0xEE, 0xF6, 2, &data[0]);
	UT = data[0]<<8 | data[1];
}


double bmp180_sicaklikAl()
{
	bmp180_hamSicaklik_al();
	int32_t X1 = (UT - AC6) * AC5 / pow(2,15);
	int32_t X2 = MC * pow(2,11) / (X1 + MD);
	int32_t B5 = X1 + X2;
	double T = (B5 + 8) / pow(2,4) /10;
	return T;
}
