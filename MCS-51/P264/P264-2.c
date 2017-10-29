/*乙机程序：使用中断法*/

#include "reg51.h"

unsigned char code table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
 unsigned char receiv; //接收数值
void main(void){
 	
	TMOD=0x20;	 //T1定时方式2
	TH1=TL1=0xf4;  //2400b/s
	PCON=0;		   //波特率不加倍
	SCON=0x50;	   //串口工作方式1，TI和RI清零，允许接收
	ES = 1;		   //串口中断允许开启
    EA = 1;		//总中断开启
	TR1=1;    //定时器1开启
	while(1);	//一直在等待
}

rec() interrupt 4{
 	if(RI){  //如果接收到了数据
		RI=0;  //清除RI标志位
		receiv=SBUF;  //取得接收值
		P2=table[receiv];	//显示接收数据
		SBUF=receiv;  //返回接收值给甲	
	}
	if(TI) {	//如果发送出去了
	 TI = 0;                //清除中断标志
	}
}

