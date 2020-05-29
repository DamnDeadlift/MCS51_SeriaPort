/*
 * @Author: Johnny Zheng
 */ 
#include "STC89xx.h"
#include "uart.h"
#include "timer.h"
#include <string.h>
#include <intrins.h>
#include <stdio.h>

#define BUF_LEN 20   //串口接收缓冲大小



uint8_t g_uart_buff[BUF_LEN] = {0};
uint8_t g_uart_len = 0;
volatile bit g_recv_flag = 0;

void DataProcessing(uint8_t msg[], uint8_t len);


void Uart_IRQHandler(void) interrupt 4
{
	if(RI)
	{
		RI = 0;
	
		//先关定时器，并重新将定时器的值变回3ms的初始数据
		StopReceiveTimer();
		ResetReceiveTimer();

		g_uart_buff[g_uart_len++] = SBUF;   

		StartReceiveTimer();
	}
}

void UartReceiveTimeout_IRQHandler(void) interrupt 5
{
	TF2 = 0;

	StopReceiveTimer();
	//ResetReceiveTimer();

	g_recv_flag = 1;
}


int main(void)
{
	uint8_t msg_len = 0;
	uint8_t uart_msg[BUF_LEN] = {0};
	uint8_t i = 0;

	Uart_Init(BAUD_19200);
	
	while(1)
	{
		if (g_recv_flag)
		{
			
			//将缓存区的数据依次赋值给另一个数组，避免处理过程中发送数据影响缓冲区域的数据
			for (i = 0; i < g_uart_len; i++)
			{
				uart_msg[i] = g_uart_buff[i];
			}
			msg_len = g_uart_len;
			
			//将缓存区的数据清零
			memset(g_uart_buff, 0, BUF_LEN * sizeof(uint8_t));
			g_uart_len = 0;

			//数据处理
			DataProcessing(uart_msg, msg_len);

			//将数据数组的数据清零
			memset(uart_msg, 0, msg_len * sizeof(uint8_t));

			g_recv_flag = 0;
		}
		
	}
	
	return 0;
}

void DataProcessing(uint8_t msg[], uint8_t len)
{
	uint8_t i = 0;
	for (i = 0; i < len; i++)
	{
		Uart_SendByte(msg[i]);
	}
	
}