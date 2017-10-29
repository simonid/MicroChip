/*甲机程序*/

#include "reg51.h"
unsigned char code table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
void delay(unsigned int time){	   //延时
 	unsigned int j = 0;
	for(;time>0;time--)
		for(j=0;j<125;j++);
}

void main(void){
 	unsigned char counter = 0;	//计数
	TMOD = 0x20;   //T1定时方式2
	TH1=TL1=0xf4;//2400b/s
	PCON=0;		  //波特率不加倍
	SCON=0x50;	//串口工作方式1，TI和RI清零，允许接收
	TR1=1;	//开定时器1
	while(1){
	 	SBUF = counter;	 //发送信号
		while(TI==0);	   //等待发送完成
		TI=0;	//清除标志位
		while(RI==0);	//等待接收
		RI=0;		//清接收标志
		if(SBUF==counter){	//如果发送=接收
		 	P2=table[counter];	  //显示发送值
			if(++counter>9) counter=0;	 //重置
			delay(500);
		}
	}
}