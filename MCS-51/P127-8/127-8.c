#include "reg51.h"
sbit P1_1=P1^1;

void main(){	 
	TMOD = 0x05;	 //T0����ģʽ����ʽ1	
	TH0=0Xff;		  
	TL0=0xf6; //10��
	TR0 = 1;		 //����������0
	while(1){	
	 do{} while(!TF0);		  //�������	
		TF0=0; 	  //TF0��λ
		P1_1=0;					
		TMOD = 0x01;						   //T0��ʱ��ʽ1
		TH0 = 0xfe;				//����ֵ��1ms
		TL0 = 0x0c;
		while(!TF0);							//�ȴ���ʱ���
		TF0=0;
		P1_1=1;								  //TF0��λ
		TMOD = 0x05;						   //��������T0����ģʽ1
		TH0=0xff;								 //�����ֵ
		TL0=0xf6;

	}
}

