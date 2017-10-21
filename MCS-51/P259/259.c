#include "reg51.h"
unsigned char code table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
sbit ge = P3^0;
sbit shi = P3^1;
int num=0;
int n=60;	   //计数

char gewei;	 
char shiwei;
void delay(int m)		 //延时
{
        int i,j;
        for(i=m;i>0;i--)
        for(j=125;j>0;j--);
}
void main(){
	TMOD = 0x01;	 //定时器0，方式1
	TH0 = (65536-50000)/256;	  //初值，50ms
	TL0 = (65536-50000)%256;
	EA=1;	//开总中断
	ET0=1;	//开定时器0中断允许位
	TR0=1;	 //	开定时器0
 	while(1){
		ge=1;//个位显示
		P2 = table[gewei];
		delay(2);
		ge=0;
		delay(2);

		shi=1; //十位显示
		P2=table[shiwei];
		delay(2);
		shi=0;
		delay(2);
	}
}
timer() interrupt 1{	 //中断处理
	TH0=(65536-50000)/256;                          //定时器重装初值
	TL0=(65536-50000)%256;
	num++;
	if(num==20)	 //1s到了
	{
	 	num=0;	//重置
		n--;   //每定时1s，60s倒计时减一
		if(n==0)  n=60;	//重置
		shiwei=n/10;   //十位
		gewei=n%10;	   //个位
	}
}




  /*

#include "reg51.h"
unsigned char code table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
sbit ge = P3^1;
sbit shi = P3^0;
int num=0;
int n=60;

char gewei;
char shiwei;
void delay(int m)
{
        int i,j;
        for(i=m;i>0;i--)
        for(j=125;j>0;j--);
}
void main(){
char point=0;
	TMOD = 0x01;
	TH0 = (65536-50000)/256;
	TL0 = (65536-50000)%256;
	//EA=1;
	//ET0=1;
	TR0=1;
	 
while(1){	
	num++;
	if(num==20)
	{
	 	num=0;
		n--;
		if(n==0)  n=60;
		shiwei=n/10;
		gewei=n%10;
		point=0;
	}
	//do{num++;}while((!TF0)&&(num==20));
	while(!TF0);
	TF0=0;
 	P3=2-point;
	if(point==1)P2=table[gewei];  
	else P2=table[shiwei];  
	point=1-point;
	
	}

}
  */