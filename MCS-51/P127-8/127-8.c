#include "reg51.h"
sbit P1_1=P1^1;

void main(){	 
	TMOD = 0x05;	 //T0计数模式，方式1	
	TH0=0Xff;		  
	TL0=0xf6; //10个
	TR0 = 1;		 //开启计数器0
	while(1){	
	 do{} while(!TF0);		  //脉冲计数	
		TF0=0; 	  //TF0复位
		P1_1=0;					
		TMOD = 0x01;						   //T0定时方式1
		TH0 = 0xfe;				//赋初值，1ms
		TL0 = 0x0c;
		while(!TF0);							//等待定时溢出
		TF0=0;
		P1_1=1;								  //TF0复位
		TMOD = 0x05;						   //重新设置T0计数模式1
		TH0=0xff;								 //赋予初值
		TL0=0xf6;

	}
}

