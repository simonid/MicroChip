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
	TMOD = 0x05;	 //T0����ģʽ����ʽ1
	TR0 = 1;		 //����������0
	TL0=0Xff;		  //һ��������������֮������
	while(1){
		
	 do{n++;}while(!TF0);		  //10�����嵽��	
		TF0=0; 	  //TF0��λ
		while(n==10);//�ȴ�10������		
		n=0;					
		TMOD = 0x01;						   //T0��ʱ��ʽ1
		TH0 = (65536-1000*2)/256;				//����ֵ��1ms
		TL0 = (65536-1000*2)%256;
		while(!TF0);							//�ȴ���ʱ���
		TF0=0;								  //TF0��λ
		TMOD = 0x05;						   //��������T0����ģʽ1
		TL0=0xff;								 //�����ֵ
	}
}