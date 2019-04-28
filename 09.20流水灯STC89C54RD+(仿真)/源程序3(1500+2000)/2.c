#include "reg51.h"
#define uchar unsigned char    //�궨��
#define uint unsigned int
sbit TEST_LED = P1^0;               //work LED, flash once per second 
uint count;                         //1000 times counter
uchar a,b,c;
sbit key1=P0^0;
sbit key2=P0^1;

void delay(uint i)		//��ʱ�ӳ���
{
	while(i--);	
}
void main()
{
	TMOD = 0x00; //ѡ��ʱ��ģʽ
	TH0 = (8192 - 1000)/32;	    //��ʱ��0��ֵ,1ms
	TL0 = (8192 - 1000)%32;		//��ʱ��0��ֵ,1ms
    TR0 = 1;                    //timer0 start running
    ET0 = 1;                    //enable timer0 interrupt
    EA = 1;                     //open global interrupt switch
    
	a=0;
	c=0;
	b=0;
	P0=0xff;
	P1=0xff;
	P3=0xfF;
	P2=0xff;
    while (1)
	{
		if(key1==0&&a==0)	   //����ж�
		{
		 	delay(10);
			if(key1==0&&a==0)
			{
			 	a=1;
			 	b=0;
				c=0;
				count = 0;
			}		
		}
		if(key2==0&&a==0)		//�Ҽ��ж�
		{
		 	delay(10);
			if(key2==0&&a==0)
			{	  
			 	a=2;
			 	b=0;
				c=0;
				count = 0;
			}		
		}
		if(a==1)					 //������º��Ч��
		{
			
			if(b<=2)
			{
				P1=0xfb;
				P3=0xff;
				P2=0xff;
			}
			else if(b<=5)
			{
				P1=0xf5;
				P3=0xff;
				P2=0xff;
			}
			else if(b<=8)
			{
				P1=0xee;
				P3=0xff;
				P2=0xff;
			}
			else if(b<=11)
			{
				P1=0xdf;
				P3=0xff;
				P2=0xff;
			}
			else if(b<=14)
			{
				P1=0xbf;
				P3=0xff;
				P2=0xff;
			}		
			else if(b<=17)
			{
				P1=0x7f;
				P3=0xff;
				P2=0xff;
			}
			else if(b<=21)
			{
				P1=0xff;
				P3=0xfe;
				P2=0xff;
			}
			else if(b<=25)
			{
				P1=0xff;
				P3=0xfd;
				P2=0xff;
			}
			else if(b<=29)
			{
				P1=0xff;
				P3=0xfb;
				P2=0xff;
			}
			else if(b<=33)
			{
				P1=0xff;
				P3=0xf7;
				P2=0xff;
			}
			else if(b<=37)
			{
				P1=0xff;
				P3=0xef;
				P2=0xff;
			}
			else if(b<=40)
			{
				P1=0xff;
				P3=0xdf;
				P2=0xff;
			}
			else if(b<=43)
			{
				P1=0xff;
				P3=0xbf;
				P2=0xff;
			}
			else if(b<=46)
			{
				P1=0xff;
				P3=0x7f;
				P2=0xff;
			}
			else if(b<=49)
			{
				P1=0xff;
				P3=0xff;
				P2=0xfe;
			}
			else if(b<=52)
			{
				P1=0xff;
				P3=0xff;
				P2=0xfd;
			}
			else if(b<=55)
			{
				P1=0xff;
				P3=0xff;
				P2=0xfb;
			}
			else if(b<=58)
			{
				P1=0xff;
				P3=0xff;
				P2=0xf7;
			}
			else if(b<=59)
			{
				P1=0xff;
				P2=0xff;
				P3=0xff;
			}


		}
		else if(a==2)		   //�Ҽ����º��Ч��
		{
			
			if(c<=2)
			{
				P2=0xfd;
				P3=0xff;
				P1=0xff;
			}
			else if(c<=5)
			{
				P2=0xfa;
				P3=0xff;
				P1=0xff;
			}
			else if(c<=8)
			{
				P2=0xf7;
				P3=0x7f;
				P1=0xff;
			}
			else if(c<=11)
			{
				P2=0xff;
				P3=0xbf;
				P1=0xff;
			}
			else if(c<=14)
			{
				P2=0xff;
				P3=0xdf;
				P1=0xff;
			}		
			else if(c<=15)
			{
				P1=0xff;
				P3=0xff;
				P2=0xff;
			}
			



		}






	 	if (count>=500)               //1ms * 500 -> 0.5s
    	{
        	count = 0;               
        	if(a==1&&b<60)
			b++;				
			
			else if(a==2&&c<16)
			c++;
			 
			if(b>=60)
			a=0;
			if(c>=16)
			a=0;  
    	}
	}
}
 void T0zd(void) interrupt 1      //3����ʱ��1���жϺ�  1����ʱ��0���жϺ� 0���ⲿ�ж�1 2���ⲿ�ж�2  4�������ж�
{	 
	 TH0 = (8192 - 1000)/32;	 //��ʱ��0��ֵ,1ms
	 TL0 = (8192 - 1000)%32;  	 //��ʱ��0��ֵ,1ms
	 count++;

}
