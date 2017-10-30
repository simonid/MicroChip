#include "reg51.h"

#define uchar unsigned char 
#define uint unsigned int
sbit OE =P2^7;
sbit EOC=P2^6;
sbit ST=P2^5;
sbit CLK=P2^4;
sbit P2_0=P2^0;	  //P2_0~P2_3:λѡ
sbit P2_1=P2^1;
sbit P2_2=P2^2;
sbit P2_3=P2^3;
uint dat,volt;
uchar table[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90}; //����
uchar table2[]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};	 //��С����
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
	ST=0;	 //һ�������忪��ת��
		   while(EOC==0);	//�ȴ�ת������
		   OE=1;	//��������źţ�Ϊ��������					  
		   dat=P1;	  //��ȡ����
		   OE=0;   //�ر��������
}
void display(uint dat)
{
	P2_0=1;P2_1=0;P2_2=0;P2_3=0;   //����һ�������λѡ����������
	P0=table2[dat/100]; 
	 
	delayms(1);
	P0=0xFF;			 //����
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
	CLK=~CLK;  //ȡ��
}
void init()
{
	TMOD=0x02;		//��ʱ��0��ʽ2
	TH0=0x14;
	TL0=0x00;
	TR0=1;		//����ʱ��0
	ET0=1;	   //����ʱ��0�ж�
	EA=1;	   //�����ж�
}
void main(void)
{
	init();	 //��ʼ����ʱ��
	while(1)
	{
		ADC_read();	//��ȡ��ֵ
		display(1.96*dat);	//��ʾ		 1.96=2/255

	}
}


