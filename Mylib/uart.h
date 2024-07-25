#ifndef UART_H
#define UART_H
#include "main.h"
#include "string.h"
#include <stdio.h>

#define BUFFER_SIZE 1024

typedef struct{
	uint8_t data_rx[9];
	uint8_t uart_flag;
	uint8_t count;
	uint8_t str[BUFFER_SIZE];
	uint8_t vel_value;
	uint8_t pos_value;
	uint32_t time_uart;
	UART_HandleTypeDef *uart;
	char* commands[25];
}command_val;

void default_command(command_val *val);
void handle_command(command_val *val);
void uart_init(command_val *val,UART_HandleTypeDef *uart);
#endif
