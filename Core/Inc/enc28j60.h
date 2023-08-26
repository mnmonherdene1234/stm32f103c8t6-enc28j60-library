/*
 * enc28j60.h
 *
 *  Created on: Aug 24, 2023
 *      Author: mnmon
 */

#ifndef INC_ENC28J60_H_
#define INC_ENC28J60_H_

#include "stm32f1xx_hal.h"

#define CS_PORT GPIOA
#define CS_PIN GPIO_PIN_4

#define ADDR_MASK 0b00011111

#define READ_BUFFER_MEMORY 0b00111010

#define READ_OP 0b00000000
#define WRITE_OP 0b01000000

void enc28j60_init(SPI_HandleTypeDef *spi);
void enc28j60_cs_on();
void enc28j60_cs_off();
uint8_t enc28j60_read_eth(uint8_t address);
void enc28j60_write_eth(uint8_t address, uint8_t data);
void enc28j60_system_reset_command();
void enc28j60_read_buffer(uint16_t length, uint8_t* data);

#endif /* INC_ENC28J60_H_ */
