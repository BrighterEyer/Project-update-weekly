/***************************************
<����ADC0809�ĵ�ѹ�ɼ�ϵͳ>
�ɼ�������0.01v��
���õ�ͨ����ѯ��ʽ�ɼ���ѹ��

Lucky - D
�ۺ�QQ:810488037

2018/10/31
****************************************/

#include <reg52.h>
#include <intrins.h>

#define  DBPort P0    //LCD���ݶ˿�

sbit LcdRs = P2^5;//lcd���ƶ˿ڣ�
sbit LcdRw = P2^6;
sbit LcdEn = P2^7;
sbit Lcdbf = P0^7; //LCDæ��־ Busy Flag


sbit CLK=P1^0;		//ʱ���ź�
sbit ST=P1^3;		//�����ź�
sbit EOC=P1^2;		//ת�������ź�
sbit OE=P1^1;		//���ʹ��

unsigned char Voltage;
//-----------------------------------------------------
//-------------Lcd1602��������-------------------------
//-----------------------------------------------------
void delay(unsigned int t)	 //��ʱ
{    
	while(t--);
}

void  LCD_Wait(void)	//��æ״̬
{								   
	LcdRs=0;
	LcdRw=1;
	LcdEn=1;delay(10);LcdEn=0;	//�½���	
	while(Lcdbf)
	{
	  LcdEn=0;LcdEn=1;	 //�������Ҫ�����,ʵ��Ӳ���в���Ҫ
	}			
} 

void LCD_Write(bit style, unsigned char input)	 //д����1/����0
{
	LcdRs=style;
	LcdRw=0;		
	DBPort=input;	
	LcdEn=1;delay(10);LcdEn=0;			
	LCD_Wait();	
}

void GotoXY(unsigned char x, unsigned char y)  //�ƶ���굽ָ��λ��
{
	if(y==0)	LCD_Write(0,0x80|x);
	if(y==1)    LCD_Write(0,0xc0|x);
}

void LCD_Initial(void)			  //��ʼ��LCD
{
	LCD_Write(0,0x38);  		 //8λ���ݶ˿�,2����ʾ,5*7����
	delay(300);
	delay(300);
	LCD_Write(0,0x0c);           //��ʾģʽ
	LCD_Write(0,0x01);           //����
	LCD_Write(0,0x06);           //����ģʽ
}



void Print(unsigned char *str, unsigned char x, unsigned char y)	 //ָ����������ַ���
{
	unsigned char i=0, temp=0;
	while(*str)  
	{
		if(i==0 && temp==0)
		{
			GotoXY(x+i, y);
			temp = 1;
		}
		if(temp == 1)
		{
			GotoXY(x+i, y);
			LCD_Write(1,*str++);
			i++;
		}
	}
}
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

void display_vol(unsigned int dat, x, y)//��ѹ��ʾ��
{
		unsigned char i;
		unsigned char display[5] = {0};//0.0196	
		dat = 19.6 * dat; //���Ż�����������ת��Ϊ��ѹֵ����һǧ����
		display[0] 	= dat / 1000+'0';
		display[1]	= 0x2e;	//С�����ascii�룻
		display[2]	= dat % 1000 / 100+'0';
		display[3]	= dat % 1000 % 100 / 10+'0';
		display[4]  = dat %10+'0';
		GotoXY(x, y);
		for(i=0; i<5; i++)
		{
			LCD_Write(1, display[i]);
	    }
		LCD_Write(1, 'V');//��ʾ��λ��
}
//-------------------------------------------------------------------------------------------------


//������
void main()
{
	TMOD=0x02;		//T1����ģʽ2
	TH0=0x14;		
	TL0=0x00;
	IE=0x82;
	TR0=1;
	LCD_Initial();//LCD1602��ʼ����
	P1 = 0X0F;	  //ѡ��ͨ��0��
	while(1)
	{
		Print("Volt:", 3, 0);
		ST=0;ST=1;ST=0;		//����A/Dת��
		while(EOC==0);		//�ȴ�ת�����
		OE=1;
		Voltage = P3;
		display_vol(Voltage, 8, 0);//��ʾ��ѹ��
		OE=0;
		Print("#Detecting...#", 1, 1);//��ʾϵͳ״̬��
	}
}
//T0��ʱ���жϸ�ADC0809�ṩʱ���ź�
void Timer0_INT() interrupt 1
{
	CLK=~CLK;
}
//�ֱ���0.0196��