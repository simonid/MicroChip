
#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
#define KEY  P3										  //键盘端口
#define LIE  P2										  //列选端口 
#define HANG P0										  //行选端口
#define SLONG 10									  //蛇的最大长度
sbit UP   =P3^0;									  //上
sbit DOWN =P3^1;									  //下
sbit RIGHT=P3^2;									  //右
sbit LEFT =P3^3;									  //左
int   temp,i,s;										  //定义temp用于读取端口数据，i用于循环,s用于果实的随机显示
uchar X[SLONG+1];									  //定义数据存放小蛇的横坐标
uchar Y[SLONG+1];
uchar  SL;
uchar  v;
char   add_x,add_y;
uchar TABLE1[] ={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,0x00};	//列
uchar TABLE2[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe,0x00};	//行
uchar TABLE3[]={0x7e,0xbd,0xdb,0xe7,0xe7,0xdb,0xbd,0x7e,0x00};	//行
sbit stop = P1^7;


  void delay(int ms)
  {
   int i,j;
   for(i=ms;i>0;i--)
       for(j=110;j>0;j--);
  }

  void keyscan()
  {
  if(UP==0)							   //片段上按键被按下
  {
    add_x=0;						   //去除x轴的偏移
	  if(add_y!=-1)					   //检查是否有反方向的偏移
	  {
	     add_y=1;					   //没有就改变偏移方向
	  }  
  }
  if(DOWN==0)
  {
   add_x=0;
	  if(add_y!=1)
	  {
	     add_y=-1;
	  }
  }
  if(RIGHT==0)
  {
   add_y=0;
	  if(add_x!=-1)
	  {
	     add_x=1;
	  }
  }
  if(LEFT==0)
  {
    add_y=0;
	  if(add_x!=1)
	  {
	     add_x=-1;
	  }
  }
  }

  void display(int a)
  {
   while(a--)						   //通过循环的次数控制，小蛇前进的速度
   {
   for(i=0;i<SLONG+1;i++)			   //通过循环显示小蛇的所有部分
      {
	   LIE=TABLE1[X[i]];				   //列坐标
	   HANG=TABLE2[Y[i]];			   //行坐标
	   keyscan();					   //键盘扫描程序
	   delay(1);					   //延时1ms
	   LIE=0X00;					   //关闭点阵再重新开启，防止产生重影
	   HANG=0XFF;					   //关闭点阵再重新开启，防止产生重影
	  }
   }  
  }


  void unit()
  {
   HANG=0XFF;						   //先关闭点阵
   LIE =0X00;						   
   KEY =0XFF;						   //在51中没有专用的读取寄存器，所以在读取之前要将端口给高电平，才能读到正确的结果
   v   =50;							   //通过这个形参控制小蛇的速度,s实参在显示函数中
   for(i=3;i<SLONG+1;i++)			   //给没有小蛇和食物的地方关闭显示
   {
       X[i]=8;
       Y[i]=8;
   }
   X[0]=5;							   //初始化食物的位置横坐标
   Y[0]=3;							   //初始化食物的位置纵坐标
   SL  =2;							   //初始化蛇的长
   X[1]=0;							   //初始化蛇头的横坐标
   Y[1]=2;							   //初始化蛇头的纵坐标
   X[2]=0;							   //初始化蛇尾的横坐标
   Y[2]=1;							   //初始化蛇尾的纵坐标
   add_x=0;							   //初始化X轴偏移为0
   add_y=0;							   //初始化Y轴偏移为0
   s =2;							   //初始化果实参数

}

  bit knock()
  {
  bit k;							   //定义一个标志位用于判断是否发生碰撞
  k=0;								   //先初始为0，表示未碰撞
  if(X[1]>7||Y[1]>7)k=1;			   //蛇头对应的横或纵坐标为7时撞墙，K=1表示撞墙
  for(i=2;i<SL+1;i++)				   //蛇头坐标与蛇尾坐标相等的时候撞自己
  {									   //身体有几段就要检测几次
   if(X[1]==X[i]&Y[1]==Y[i])
   k=1;								   //撞墙标志
  }
  return k;							   //返回撞墙的标志
  }

  void main()
  {
   unit();							   //初始化
   while(1)							   //进入循环
   {
	  temp=0x0f&KEY;				   //读取P3端口的值，屏蔽掉高四位
	  if(temp!=0x0f)				   //如果不等于初始值说明有按键按下
      break;						   //跳出循环
   display(1);						   //否则就执行显示程序
   }
   while(1)							   //进入循环
   {   
   if(knock())						   //检测碰撞
   {								   //如果碰撞则初始化速度，重新开始
   v=50;
   //display()
   while(1){
    int i;
   	for(i=0;i<=7;i++){
	   LIE=TABLE1[i];				   //列坐标
	   HANG=TABLE3[i];			   //行坐标
	   delay(3);
   	}

   }

   }
   display(v);						   //调用显示函数，显示速度为V
   if((X[0]==X[1]+add_x)&(Y[0]==Y[1]+add_y))       //判断是否吃到果子
   	{
	SL++;							   //蛇长度加1
	if(SL==SLONG)					   //如果蛇身长度等于最大长度则过关
	{
	 SL=3;							   //初始化蛇身长度
	 v=v-5;						   //增加速度
	 for(i=3;i<SLONG+1;i++)			   //初始化不显示的区域
      X[i]=8;
     for(i=3;i<SLONG+1;i++)
      Y[i]=8;
	
	}
	s++;							   //对食物参数加1，大于4则变为2，用来使果实看起来随机显示
	if(s>4)
	   s=2;
	if(X[1]>4)						   //根据蛇头所在的位置，和参数S设置果子的位置
	{
	X[0]=X[1]-s;
	}
	else
	X[0]=X[1]+s;
	if(Y[1]>4)
	{
	Y[0]=Y[1]-s;
	}
	else
	Y[0]=Y[1]+s;
	}
   for(i=SL;i>1;i--)				 //通过对每个块的坐标的重新设置达到移动的目的
   {
   X[i]=X[i-1];
   Y[i]=Y[i-1];
   }
   X[1]=X[2]+add_x;
   Y[1]=Y[2]+add_y;					 //蛇头根据偏移的方向设计
   
   }
  }

