/*
 * agile_i2c.c
 *
 */
#include "agile_i2c.h"
#include "main.h"

void i2c_init()
{

	//Tpclk = 41.66 clock periyodu
	RCC->APB1ENR |= (1 << 21); // Enable I2C CLOCK
	RCC->AHB1ENR |= (1<<1);  // Enable GPIOB CLOCK
	HAL_Delay(5);
	GPIOB->MODER |= (2<<12) | (2<<14);  //(13:12)= 0b10 Alternate Function PB6; (15:14) = 0b10 Alternate Function PB7
	GPIOB->OTYPER |= (1<<6) | (1<<7);  //  Bit6 = 1, Bit7 = 1  output open drain
	GPIOB->OSPEEDR |= (3<<12) | (3<<14);  // (17:16) = 0b11 High Speed PB6; (19:18) = 0b11 High Speed PB7
	GPIOB->PUPDR |= (1<<12) | (1<<14);  // (17:16)= 0b01 Pull up PB6; (19:18)= 0b01 pull up PB7
	GPIOB->AFR[0] |= (4<<24) | (4<<28);  // (27:24) = 0b0100 AF4 PB6; (31:28) = 0b0100 AF4 PB7
	I2C1->CR1 |= (1<<15);  // reset the I2C
	I2C1->CR1 &= ~(1<<15);  // Normal operation

	I2C1->CR2 |= (24<<0);  // PCLK1 FREQUENCY 24 MHz.
	I2C1->CCR = 120<<0; // CCR Config
	I2C1->TRISE = 25; // TR Config
	I2C1->CR1 |= (1<<0); // Enable I2C1

}

void i2c_start()
{
	I2C1->CR1 |= (1<<10);  // Enable the ACK
	I2C1->CR1 |= (1<<8);  // Generate START
}

void i2c_sendData(int8_t data )
{
	while (!(I2C1->SR1 & (1<<7)));  // wait for TXE (TX empty) bit to set
	I2C1->DR = data;
	while (!(I2C1->SR1 & (1<<2)));  // wait for BTF (Byte Transfer Finished) bit to set
}

void i2c_sendAddress(int8_t address)
{
	I2C1->DR = address;  //  send the address
	while (!(I2C1->SR1 & (1<<1)));  // wait for ADDR bit to set
	uint8_t temp = I2C1->SR1 | I2C1->SR2;  // read SR1 and SR2 to clear the ADDR bit
}


char i2c_receive(int8_t slaveAdd, int8_t regAdd)
{

	                I2C1 -> CR1 |= 0x0100;                    // Start bit gönderilir
	                while (!(I2C1 -> SR1 & 0x0001));   // Start bitinin gönderilmesini bekle (SB = 1)
	                I2C1 -> DR = slaveAdd ;                         // Slave adresini gönder. (LSB = 1)
	               while (!(I2C1 -> SR1 & 0x0002));    // Adresin gönderilmesini bekle (ADDR = 1)
	               int Status2 = I2C1 -> SR2;                // Flag temizlemek için SR2 register’ı oku
	               I2C1 -> DR = regAdd;                           // chip adresini  gönder
	               while (!(I2C1 -> SR1 & 0x0080));   // DR register’ın boşalmasını bekle
	               while (!(I2C1 -> SR1 & 0x0004));   // Byte’ın gönderilmesini bekle

	               I2C1-> CR1 |= 0x0100;                   // Start bit gönderilir
	               while (!(I2C1 -> SR1 & 0x0001));  // Start bitinin gönderilmesini bekle (SB = 1)
	               I2C1 -> DR = slaveAdd | 1;                        // Slave adresini gönder. (LSB = 0)
	               while (!(I2C1 -> SR1 & 0x0002));  // Adresin gönderilmesini bekle (ADDR = 1)
	               int Status4 = I2C1 -> SR2;             // Flag temizlemek için SR2 register’ı oku
	               while (!(I2C1 -> SR1 & 0x0040)); // byte alınana kadar bekle
	               I2C1 -> CR1 |= 0x0200;                 // Stop biti gönder

	               return ((char)I2C1 -> DR);            // okunan byte ile geri dön

}
