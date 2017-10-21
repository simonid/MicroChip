#include "reg51.h"
sbit P3_0 = P3^0;


/*
void delay(unsigned int time){
 	unsigned int j = 0;
	for(;time>0;time--)
	for(j=0;j<250;j++);
}	*/
void main(){
	int n=0;
	TMOD = 0x05;	 //T0计数模式，方式1
	TR0 = 1;		 //开启计数器0
	TL0=0Xff;		  //一个外来脉冲来了之后就溢出
	while(1){
		
	 do{n++;}while(!TF0);		  //10个脉冲到来	
		TF0=0; 	  //TF0复位
		while(n==10);//等待10个脉冲		
		n=0;					
		TMOD = 0x01;						   //T0定时方式1
		TH0 = (65536-1000*2)/256;				//赋初值，1ms
		TL0 = (65536-1000*2)%256;
		while(!TF0);							//等待定时溢出
		TF0=0;								  //TF0复位
		TMOD = 0x05;						   //重新设置T0计数模式1
		TL0=0xff;								 //赋予初值
	}
}