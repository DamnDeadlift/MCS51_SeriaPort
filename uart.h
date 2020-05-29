#ifndef __UART_H__
#define __UART_H__

#include "STC89xx.h"

enum Baud
{
    BAUD_9600,
    BAUD_19200
};



void Uart_Init(enum Baud baud);
void Uart_SendByte(uint8_t byte);

#endif