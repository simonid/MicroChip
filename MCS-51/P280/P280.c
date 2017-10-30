#include "reg51.h"

#define uchar unsigned char 
#define uint unsigned int
sbit OE =P2^7;
sbit EOC=P2^6;
sbit ST=P2^5;
sbit CLK=P2^4;
sbit P2_0=P2^0;	  //P2_0~P2_3:位选
sbit P2_1=P2^1;
sbit P2_2=P2^2;
sbit P2_3=P2^3;
uint dat,volt;
uchar table[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90}; //共阳
uchar table2[]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};	 //带小数点
void delayms(uint ms)
{
	uchar j;
	while(ms--)
	{
		for(j=0;j<120;j++);
		}
}
void ADC_read()
{	
	ST=0;
	ST=1;
	ST=0;	 //一个正脉冲开启转换
		   while(EOC==0);	//等待转换结束
		   OE=1;	//输出允许信号，为真可以输出					  
		   dat=P1;	  //读取数据
		   OE=0;   //关闭允许输出
}
void display(uint dat)
{
	P2_0=1;P2_1=0;P2_2=0;P2_3=0;   //开第一个数码管位选，后面类似
	P0=table2[dat/100]; 
	 
	delayms(1);
	P0=0xFF;			 //消隐
	P2_0=0;P2_1=1;P2_2=0;P2_3=0;
	P0=table[dat%100/10];
	delayms(1);
	P0=0xFF;
	P2_0=0;P2_1=0;P2_2=1;P2_3=0;
	P0=table[dat/10%10];
	delayms(1);
	P0=0xFF;
	P2_0=0;P2_1=0;P2_2=0;P2_3=1;
	P0=table[dat%10];
	delayms(1);
	P0=0xFF;
}
void t0()interrupt 1
{
	CLK=~CLK;  //取反
}
void init()
{
	TMOD=0x02;		//定时器0方式2
	TH0=0x14;
	TL0=0x00;
	TR0=1;		//开定时器0
	ET0=1;	   //开定时器0中断
	EA=1;	   //开总中断
}
void main(void)
{
	init();	 //初始化定时器
	while(1)
	{
		ADC_read();	//读取数值
		display(1.96*dat);	//显示		 1.96=2/255

	}
}


