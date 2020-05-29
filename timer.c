/*
 * @Author: Johnny Zheng
 */ 

#include "STC89xx.h"

/***************串口相关定时器**********************/
//3ms 误差0.01%
#define TH2_VALUE 0xF5
#define TL2_VALUE 0x33

void UartReceiveTimer_Init(void)
{
    T2MOD = 0;		//初始化模式寄存器
	T2CON = 0;		//初始化控制寄存器
	TL2 = TL2_VALUE;		//设置定时初值
	TH2 = TH2_VALUE;		//设置定时初值
	RCAP2L = 0x33;		//设置定时重载值
	RCAP2H = 0xF5;		//设置定时重载值
	TR2 = 0;		//定时器2关闭

    ET2 = 1; //打开定时器中断
}

void ResetReceiveTimer(void)
{
	TL2 = TL2_VALUE;		//设置定时初值
	TH2 = TH2_VALUE;		//设置定时初值
}

void StartReceiveTimer(void)
{
    TR2 = 1;
}

void StopReceiveTimer(void)
{
    TR2 = 0;
}


/**************************************************/