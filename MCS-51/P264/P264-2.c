/*�һ�����ʹ���жϷ�*/

#include "reg51.h"

unsigned char code table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
 unsigned char receiv; //������ֵ
void main(void){
 	
	TMOD=0x20;	 //T1��ʱ��ʽ2
	TH1=TL1=0xf4;  //2400b/s
	PCON=0;		   //�����ʲ��ӱ�
	SCON=0x50;	   //���ڹ�����ʽ1��TI��RI���㣬�������
	ES = 1;		   //�����ж�������
    EA = 1;		//���жϿ���
	TR1=1;    //��ʱ��1����
	while(1);	//һֱ�ڵȴ�
}

rec() interrupt 4{
 	if(RI){  //������յ�������
		RI=0;  //���RI��־λ
		receiv=SBUF;  //ȡ�ý���ֵ
		P2=table[receiv];	//��ʾ��������
		SBUF=receiv;  //���ؽ���ֵ����	
	}
	if(TI) {	//������ͳ�ȥ��
	 TI = 0;                //����жϱ�־
	}
}

