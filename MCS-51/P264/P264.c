/*�׻�����*/

#include "reg51.h"
unsigned char code table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
void delay(unsigned int time){	   //��ʱ
 	unsigned int j = 0;
	for(;time>0;time--)
		for(j=0;j<125;j++);
}

void main(void){
 	unsigned char counter = 0;	//����
	TMOD = 0x20;   //T1��ʱ��ʽ2
	TH1=TL1=0xf4;//2400b/s
	PCON=0;		  //�����ʲ��ӱ�
	SCON=0x50;	//���ڹ�����ʽ1��TI��RI���㣬�������
	TR1=1;	//����ʱ��1
	while(1){
	 	SBUF = counter;	 //�����ź�
		while(TI==0);	   //�ȴ��������
		TI=0;	//�����־λ
		while(RI==0);	//�ȴ�����
		RI=0;		//����ձ�־
		if(SBUF==counter){	//�������=����
		 	P2=table[counter];	  //��ʾ����ֵ
			if(++counter>9) counter=0;	 //����
			delay(500);
		}
	}
}