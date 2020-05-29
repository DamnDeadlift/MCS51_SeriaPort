/*
 * @Author: Johnny Zheng
 */ 

#include "uart.h"
#include "STC89xx.h"

extern void UartReceiveTimer_Init(void);

void Uart_Init(enum Baud baud)
{
    SCON = 0x50;		//8位数据,可变波特率
	// AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
	// AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式

    switch (baud)
    {
    case BAUD_9600:
        PCON &= 0x7F;		//波特率不倍速
        TL1 = 0xFD;		//设定定时初值
	    TH1 = 0xFD;		//设定定时器重装值
        break;
        
    case BAUD_19200:
        PCON |= 0x80;		//使能波特率倍速位SMOD
        TL1 = 0xFD;		//设定定时初值
	    TH1 = 0xFD;		//设定定时器重装值
        break;

    default:
        break;
    }

    ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1

    UartReceiveTimer_Init();  
    
    EA = 1;  // 打开总中断
    ES = 1;  // 打开串口中断

    
}

void Uart_SendByte(uint8_t byte)
{
    SBUF = byte;
    while(!TI);
    TI = 0;
}




