#include "string.h"
#include "delay.h"
#include "uart.h"
#define MAIN_Fosc		22118400L	//������ʱ��
#define	RX1_Lenth		32			//���ڽ��ջ��峤��
#define	BaudRate1		115200UL	//ѡ������


#define	Timer1_Reload	(65536UL -(MAIN_Fosc / 4 / BaudRate1))		//Timer 1 ��װֵ�� ��Ӧ300KHZ
#define	Timer2_Reload	(65536UL -(MAIN_Fosc / 4 / BaudRate1))		//Timer 2 ��װֵ�� ��Ӧ300KHZ

#include	"STC15Fxxxx.H"
#define uchar unsigned char
#define uint  unsigned int
#define ulong  unsigned long




//u8 Time_count=0;
bdata u8 Flag;//��ʱ����־λ
sbit Timer0_start =Flag^0;	//��ʱ��0��ʱ����������
sbit Uart2_Start  =Flag^1;	//����2��ʼ��������
sbit Uart2_End		=Flag^2;	//����2�������ݽ���

bit flag0=0;


sbit SDA1=P1^4;		//���ݴ���595����
sbit SCL1=P1^5;		//595��λ��ʱ������

sbit SCL11=P1^2;		//���ݴ���595����

sbit SCL2=P1^3;		//595�Ĳ���ʱ������



sbit key=P1^7;		//595�Ĳ���ʱ������



unsigned char code duan[]={	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
                     0x80,0x90,0x83,0xc6,0xa1,0x86,0x8e };//��������ܵ͵�ƽ����
unsigned char code wei[]={0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};//�ߵ�ƽλѡ
unsigned char Data1,Data2,Data3,Data4,Data5;
unsigned char cent[10]={0,0,0,0,0,0,0,0,0,0};
unsigned char cent1[10]={0,0,0,0,0,0,0,0,0,0};
unsigned char receive[2]={0,0};



/*************	���غ�������	**************/
void GPIO_config(void); //�˿ڳ�ʼ������
void Timer0Init(void);  //��ʱ��0��ʼ��
void CLR_Buf2(void);    //�������2���ջ���
u8 Find(u8 *a);         //�����ַ���
void Second_AT_Command(u8 *b,u8 *a,u8 wait_time); //����ATָ���
void Set_Pdu_Mode(void);//���ö���ģʽPDU
void Wait_CREG(void);   //��ѯ�ȴ�ģ��ע��ɹ�
void Send_Pdu_Sms(void);//����һ�����Ķ���


void Delay(void)                       //��ʱ����
{
 unsigned char i,j;
 for(i=133;i>0;i--)
 for(j=6;j>0;j--);
}
/*********************************/
void W595_in(unsigned char Data)   //���һ���ֽ�8λ������
{
  unsigned char i;
  for(i=0;i<8;i++)
  {
   SCL1=0;			  //����λ��ʱ���ź���
   SDA1=Data&0x80;	 //�����λ��ֵ��SDA1����595���ݴ�������
   Data<<=1;		 //��������һλ
   SCL1=1;			 //����λ��ʱ���ź��� �����һλ�Ĵ洢
  }
}

void W595_in1(unsigned char Data1)   //���һ���ֽ�8λ������
{
  unsigned char i;
  for(i=0;i<8;i++)
  {
   SCL11=0;			  //����λ��ʱ���ź���
   SDA1=Data1&0x80;	 //�����λ��ֵ��SDA1����595���ݴ�������
   Data1<<=1;		 //��������һλ
   SCL11=1;			 //����λ��ʱ���ź��� �����һλ�Ĵ洢
  }
}
/*****************************/
void W595_out(void)      //��ɲ������ݹ���
{
 SCL2=0;		  //���Ͳ���ʱ���ź���
 _nop_();
 SCL2=1;		  //���߲���ʱ���ź���

}
/**************************/

void Disp(uchar *s)	
{
	unsigned char i;
	for(i=0;i<10;i++)
	W595_in(wei[s[9-i]]);
	W595_out();
	Delay();
}
void Disp1(uchar *w)	
{
	unsigned char i;
	for(i=0;i<10;i++)
	W595_in1(wei[w[9-i]]);
	W595_out();
	Delay();
}
void main(void)
{
	//GPIO_config();
	Timer0Init();


	EA=1;	//�����ж�
	Data1=76;
	
	flag0=1;
	
	while(1)
	{
		unsigned char i;
		if(key==0&&flag0==0)
		{
		 	flag0=1;
			Data1++;	
			while(key==0);
		}

		//if(flag0==1&&receive[0]<=78)
		if(flag0==1&&Data1<=78)
		{  	
			
			ES=1;
			flag0=0;
			Data2=(Data1-1)/8;
			Data3=((Data1-1)%8+1);
	  		cent[Data2]=Data3;

			
			Disp(cent);
			receive[0]=0;
			for(i=0;i<10;i++)
			cent[i]=0;
		}
		else if(flag0==1&&Data1>78&&Data1<157)
		{  
			
			ES=1;
			flag0=0;

			Data2=(Data1-79)/8;
			Data3=((Data1-79)%8+1);
	  		cent1[Data2]=Data3;

			
			Disp1(cent1);
			receive[0]=0;
			for(i=0;i<10;i++)
			cent1[i]=0;
		}


		else if(flag0==1&&receive[0]>156)
		{
		 	ES=1;
			receive[0]=0;
			flag0=0;
		}

		
		
	}
	
}

/*******************************************************************************
* ������ : Uart1 
* ����   : ����1�жϷ�����ں���
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/

void	GPIO_config(void)
{
		P3M1 &= 0XC3;  //����P32~P35Ϊ�������
		P3M0 |=	~0XC3;
	
}
void Timer0Init(void)		//20����@22.1184MHz
{

	S1_8bit();				//8λ����
	S1_USE_P30P31();		//UART1 ʹ��P30 P31��	Ĭ��


	AUXR &= ~(1<<4);	//Timer stop		������ʹ��Timer2����
	AUXR |= 0x01;		//S1 BRT Use Timer2;
	AUXR |=  (1<<2);	//Timer2 set as 1T mode
	TH2 = (u8)(Timer2_Reload >> 8);
	TL2 = (u8)Timer2_Reload;
	AUXR |=  (1<<4);	//Timer run enable

	REN = 1;	//�������
	ES  = 1;	//�����ж�

	EA = 1;		//����ȫ���ж�
	


}

void UART1_int (void) interrupt UART1_VECTOR
{
	
	if(RI==1)
	{
		static unsigned char count;//���ڽ��ռ����ı���
		receive[count]=SBUF;
		flag0=1;	
		RI=0;//�ֶ���ĳ���Ĵ�������Ҷ�����
	 	ES  = 0;
	}
	if(TI)
	{
		TI = 0;
	}


}




