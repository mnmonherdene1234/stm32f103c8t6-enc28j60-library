/*
 * enc28j60.c
 *
 *  Created on: Aug 24, 2023
 *      Author: mnmon
 */

#include "stm32f1xx_hal.h"
#include "enc28j60.h"

SPI_HandleTypeDef *spi_enc28j60;

void enc28j60_init(SPI_HandleTypeDef *spi) {
	spi_enc28j60 = spi;
}

void enc28j60_cs_on() {
	HAL_GPIO_WritePin(CS_PORT, CS_PIN, SET);
}

void enc28j60_cs_off() {
	HAL_GPIO_WritePin(CS_PORT, CS_PIN, RESET);
}

uint8_t enc28j60_read_eth(uint8_t address) {
	uint8_t command = READ_OP | (address & ADDR_MASK);
	uint8_t data;

	enc28j60_cs_off();
	HAL_SPI_Transmit(spi_enc28j60, &command, 1, 3000);
	HAL_SPI_Receive(spi_enc28j60, &data, 1, 3000);
	enc28j60_cs_on();

	return data;
}

void enc28j60_write_eth(uint8_t address, uint8_t data) {
	uint8_t command = WRITE_OP | (address & ADDR_MASK);

	enc28j60_cs_off();
	HAL_SPI_Transmit(spi_enc28j60, &command, 1, 3000);
	HAL_SPI_Transmit(spi_enc28j60, &data, 1, 3000);
	enc28j60_cs_on();
}

void enc28j60_system_reset_command() {
	uint8_t command = 0b11111111;

	enc28j60_cs_off();
	HAL_SPI_Transmit(spi_enc28j60, &command, 1, 3000);
	enc28j60_cs_on();
}

void enc28j60_read_buffer(uint16_t length, uint8_t* data){
	uint8_t command = READ_BUFFER_MEMORY;

	enc28j60_cs_off();

	HAL_SPI_Transmit(spi_enc28j60, &command, 1, 1000);

	HAL_SPI_Receive(spi_enc28j60, data, length, 1000 * length);

	enc28j60_cs_on();
}








