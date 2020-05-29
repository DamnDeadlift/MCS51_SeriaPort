#ifndef __TIMER_H__
#define __TIMER_H__


/***************串口相关定时器**********************/
//用于检测串口接收超时,设置超时时间为3ms
void UartReceiveTimer_Init(void);

//打开串口接收超时定时器
void StartReceiveTimer(void);

//关闭
void StopReceiveTimer(void);

// 重置串口接收超时定时器
void ResetReceiveTimer(void);



/**************************************************/





#endif