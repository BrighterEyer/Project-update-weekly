#include<reg52.h>
#define uchar unsigned char 
#define uint unsigned int
#define ulong unsigned long
unsigned char code dispbitcode[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char dispbuf[4];
unsigned int i;
unsigned int j;
unsigned char getdata;
unsigned int temp,Num1,Num2,Num3;
unsigned int temp1;
unsigned char count;
unsigned char d,a,b,c,e,f,g;
//unsigned char tab_H[8]={100,100,100,100,100,100,100,100};
unsigned char tab_8[9]={0,0,0,0,0,0,0,0,0};

unsigned char wen_H[9]={100,100,100,100,100,100,100,100,100};
unsigned char wen_L[9]={60,60,60,60,60,60,60,60,60};

unsigned char tab_flag[9]={0,0,0,0,0,0,0,0,0};

sbit ST=P1^2;
sbit OE=P1^0;
sbit EOC=P1^1;
sbit CLK=P1^3;



sbit A5=P3^0;
sbit A1=P1^4;
sbit A2=P1^5;
sbit A3=P1^6;
sbit A4=P1^7;
sbit ADD_A=P3^1;
sbit ADD_B=P3^2;
sbit ADD_C=P3^3;
sbit K1=P3^4;
sbit K2=P3^5;
sbit K3=P3^6;
//sbit K4=P3^7;
sbit LED_R=P3^7;
bit flag0,flag1,flag2,flag3;


void TimeInitial();
void Delay(unsigned int i);//
void TimeInitial()
{  
  TMOD=0x10;
  TH1=(65536-200)/256;//��ʱʱ��Ϊ2us,�༴CLK����Ϊ0.4us
  TL1=(65536-200)%256;
  EA=1;
  ET1=1;
  TR1=1;
 }

void Delay(unsigned int i)//��ʱ����
{
  unsigned int j;
  for(;i>0;i--)
  {
   for(j=0;j<125;j++)
  {;}
  }
}
void scan(uint data_ad)
{ 
  dispbuf[0]=data_ad%10;//�ٷ�λ
  dispbuf[1]=data_ad/10%10;//ʮ��λ
  dispbuf[2]=data_ad/100%10;//��λ
  dispbuf[3]=data_ad/1000;//ʮλ   
} 
void Display()//

{ 
  P0=0xff;   
  if(b==1)
  P0=0xc7;
  else if(b==2)
  P0=0x89;
  A1=1;
  A2=0;
  A3=0;
  A4=0;
  A5=0;
  Delay(1);
  P0=0xff;
  if(b!=0&&flag1==1)
  P0=0xff;//�ٷ�λ
  else
  {
  if(dispbuf[2]==0)
  P0=0xff;
  else
  P0=dispbitcode[dispbuf[2]];//��λ
  }
  A1=0;
  A2=1;
  A3=0;
  A4=0;
  A5=0;
  Delay(1); 
  P0=0xff;
    if(b!=0&&flag1==1)
  P0=0xff;//�ٷ�λ
  else
  P0=dispbitcode[dispbuf[1]];//ʮ��λ
  A1=0;
  A2=0;
  A3=1;
  A4=0;
  A5=0;
  Delay(1);
  P0=0xff;
    if(b!=0&&flag1==1)
  P0=0xff;//�ٷ�λ
  else
  P0=dispbitcode[dispbuf[0]];//�ٷ�λ
  A1=0;
  A2=0;
  A3=0;
  A4=1;
  A5=0;
  Delay(1);
  P0=0xff;
  if(b==0)
  {
  if(tab_flag[a]==0)
  		P0=dispbitcode[a];//�ٷ�λ
  else
  {
	  if(flag1==1)
	  P0=0xff;//�ٷ�λ
	  else
	  P0=dispbitcode[a];//�ٷ�λ
  }
  
  
  }
  else
  P0=dispbitcode[a];
  
  
  A1=0;
  A2=0;
  A3=0;
  A4=0;
  A5=1;
  Delay(1);
}

void main()//������
{
 TimeInitial();
 a=1;
 ADD_A=0;
  ADD_B=0;
   ADD_C=0;
   //wen_H=100;
   //wen_L=60;
   LED_R=0;
 while(1)
 {
  ST=0;//�ر�ת��
  OE=0;//�ر����
  ST=1;//����ת��
  ST=0;//�ر�ת��

  while(EOC==0);//�ж��Ƿ�ת������:����ִ���������,����ȴ�
  OE=1;//���������������
  getdata=P2;//������ȡ��,����ڱ���getdata��
  OE=0;//�ر����
  temp=getdata/1.7;//��ѹֵת��,5V��Ϊ�ο���ѹ,�ֳ�256��

  Display(); 
  if(K1==0)
  {
   	while(K1==0);
  	b++;
	if(b>2)
	b=0;
	Num2=0;
	if(b!=0)
	LED_R=1;

  }
    if(LED_R==0&&b!=0)
  {
   	while(LED_R==0);
  	a++;
	if(a>8)
	a=1;
	
  }
  /*
  if(K4==0&&flag0==1)
  {
   while(K4==0);
   a++;
   if(a>8)
   	a=1;
  }
  */
  if(b==1)
  scan(wen_L[a]);
  else if(b==2)
  scan(wen_H[a]);



  if(b==2&&K2==0)
  {
     while(K2==0);
  	 if( wen_H[a]<150)
	  wen_H[a]= wen_H[a]+10;
   }
   else if(b==1&&K2==0)
  {
     while(K2==0);
  	 if(wen_H[a]>wen_L[a]&&(wen_H[a]-wen_L[a]>10))
	 wen_L[a]=wen_L[a]+10;
   }
   else if(b==1&&K3==0)
  {
     while(K3==0);
  	 if(wen_L[a]>10)
	 wen_L[a]=wen_L[a]-10;
   }
  else if(b==2&&K3==0)
  {
     while(K3==0);
  	 
  	 if(wen_H[a]>wen_L[a]&&(wen_H[a]-wen_L[a]>10))
	 wen_H[a]=wen_H[a]-10;
   }
   if(b==0&&Num2>10000)
   {
   a++;
   if(a>8)
   a=1;
   Num2=0;
   
   }
   if(b==0)
   {
    scan(temp);
	tab_8[a]=temp;
   	if(a==1)
	{
	
	 ADD_A=0;
     ADD_B=0;
     ADD_C=0;	
	}
	else if(a==2)
	{
	 ADD_A=1;
     ADD_B=0;
     ADD_C=0;	
	}
		else if(a==3)
	{
	 ADD_A=0;
     ADD_B=1;
     ADD_C=0;	
	}
		else if(a==4)
	{
	 ADD_A=1;
     ADD_B=1;
     ADD_C=0;	
	}
		else if(a==5)
	{
	 ADD_A=0;
     ADD_B=0;
     ADD_C=1;	
	}
		else if(a==6)
	{
	 ADD_A=1;
     ADD_B=0;
     ADD_C=1;	
	}
		else if(a==7)
	{
	 ADD_A=0;
     ADD_B=1;
     ADD_C=1;	
	}
		else if(a==8)
	{
	 ADD_A=1;
     ADD_B=1;
     ADD_C=1;	
	}
   	 if(tab_8[a]<wen_L[a]||tab_8[a]>wen_H[a])
   	 {
	  
	  tab_flag[a] =1;
	 
	 }
	 else if(tab_8[a]>=wen_L[a]&&tab_8[a]<=wen_H[a])
	 tab_flag[a] =0;


   	 if(tab_flag[1]||tab_flag[2]||tab_flag[3]||tab_flag[4]||tab_flag[5]||tab_flag[6]||tab_flag[7]||tab_flag[8])
   	 flag2=1;
	 else if((tab_flag[1]==0&&tab_flag[2]==0&&tab_flag[3]==0&&tab_flag[4]==0&&tab_flag[5]==0&&tab_flag[6]==0&&tab_flag[7]==0&&tab_flag[8]==0))
   	 flag2=0;
   }
	if(flag2==0&&b==0)
	
	LED_R=0;

	



  
  
   
 }
}

void t1(void) interrupt 3 using 0//��ʱ���жϷ�����;����:����CLK�ź�
 {
   TH1=(65536-200)/256;
   TL1=(65536-200)%256;
   CLK=~CLK;
   Num1++;
   if(Num1>2000)
   {
   		Num1=0;
		flag1=~flag1;   
   }
   
   if(b==0 )
   Num2++;

   if(b==0)
   {
   if(Num3<300)
	{
	 if(flag2==1)
	 LED_R=~LED_R;
	 }
	 else if(Num3<1000&&b==0)
	 LED_R=0;

	 if(Num3>1000)
	 Num3=0;
   }



 } 





/*

#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
//�����ֵ�����ܶ��루������
uchar code DSY_CODE[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
sbit CLK=P1^3;		//ʱ���ź�
sbit ST=P1^2;		//�����ź�
sbit EOC=P1^1;		//ת�������ź�
sbit OE=P1^0;		//���ʹ��
//��ʱ
void DelayMS(uint ms)
{
	uchar i;
	while(ms--) for(i=0;i<120;i++);
}
//��ʾת�����
void Display_Result(uchar d)
{
	P2=0x8F;		//��4���������ʾ��λ��
	P0=DSY_CODE[d%100%10];
	//P0=0xc0;
	DelayMS(30);
	P2=0x4F;		//��3���������ʾʮλ��
	P0=DSY_CODE[d%100/10];
	DelayMS(30);
	P2=0x2F;		//��2���������ʾ��λ��
	P0=DSY_CODE[d/100];
	DelayMS(30);
}
//������
void main()
{
	TMOD=0x02;		//T1����ģʽ2
	TH0=0x14;		
	TL0=0x00;
	IE=0x82;
	TR0=1;
	//P1=0x3f;		//ѡ��ADC0809��ͨ��3��0111����P1.4~P1.6��
	while(1)
	{
		ST=0;ST=1;ST=0;		//����A/Dת��
		while(EOC==0);		//�ȴ�ת�����
		OE=1;
		Display_Result(P3);
		OE=0;



	}
}
//T0��ʱ���жϸ�ADC0808�ṩʱ���ź�
void Timer0_INT() interrupt 1
{
	CLK=~CLK;
}
*/