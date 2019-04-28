#include<reg52.h>

#define uchar unsigned char
#define uint unsigned int

sbit duan = P1^6; //��ѡ
sbit wei = P1^7; //λѡ
sbit S1 = P3^0;	//��ʼ�޸Ĳ�����
sbit S2 = P3^6;	//���Ӽ�
sbit S3 = P3^7;	//���ټ�

uchar code aaa[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uchar temp,out = 1,qq = 0,ww = 0,H,M,S,j1,j2,k1,k2,l1,l2;
uchar H1 = 0,M1 = 0,Sa = 0,j10,j20,k10,k20,l10,l20,SS = 0;
uint UT;
//�ް������¿�ʼ������־
uint num=0;


void TIM0_Init()
{
	TMOD = 0x01; 
	TH0 = (65536 - 50000)/256; //��ֵ��2^16=65536  12M 50ms��ʱ
	TL0 = (65536 - 50000)%256;
	EA=1;
	ET0 = 1; //�жϴ򿪣����ⲿ�ж�0�Ͷ�ʱ��0�ж�
	TR0=1;                     //�򿪶�ʱ������
}
void TIM1_Init(void)
{
         TMOD |= 0x10;
        TH1=(65536-50000)/256;
        TL1=(65536-50000)%256;
        EA=1;
        ET1=1;
        TR1=1;   
}




void delayMS(x) //��ʱ��������λ����
{
	uint a , b;
	for(a = 0 ; a < x ; a++ )
	for(b = 0 ; b < 110 ; b++);
}


void play(uint h1 , uint h2 , uint m1 , uint m2 , uint s1 , uint s2) //ʱ�������ʾ
{
	wei = 1; //ʱ��ʮλ
	P2 = 0x7f;
	wei = 0; 

	duan = 1;
	P0 = aaa[h1];
	duan = 0;
	delayMS(3);

	wei = 1; //ʱ�ĸ�λ
	P2 = 0xbf;
	wei = 0; 

	duan = 1;
	P0 = aaa[h2];
	duan = 0;	
	delayMS(3);

	wei = 1; //�ֵ�ʮλ
	P2 = 0xdf;
	wei = 0; 

	duan = 1;
	P0 = aaa[m1];
	duan = 0;
	delayMS(3);

	wei = 1; //�ֵĸ�λ
	P2 = 0xef;
	wei = 0; 

	duan = 1;
	P0 = aaa[m2];
	duan = 0;
	delayMS(3);

	wei = 1; //���ʮλ
	P2 = 0xf7;
	wei = 0; 

	duan = 1;
	P0 = aaa[s1];
	duan = 0;
	delayMS(3);

	wei = 1; //��ĸ�λ
	P2 = 0xfb; 
	wei = 0; 

	duan = 1;
	P0 = aaa[s2];
	duan = 0;
	delayMS(3);		
}  

void stopfunc() //S1��������ʼ�޸Ĳ���
{
	if(S1 == 0)
	{
		while(!S1);
		qq++;
		out = 0; //��ͣ
		TR0 = 0;
		TR1=1;
		num=0;
	}		
}


void buttfunc() //S2����S3������ ��ʱ
{
	
	if(qq == 1) //��һ�ΰ�S1ʱ������
	{
		if(S2 == 0)
		{
			while(!S2);
			if(S < 59)
			{
				S++;
			}
			else
			{
				S = 0;	
			}
			delayMS(5);
			num==0;
		}
		if(S3 == 0)
		{
			while(!S3);
			if(S > 0)
			{					
				S--;
			}
			else
			{
				S = 59;
			}
			delayMS(5);
			num==0;
		}
			j1=H%10;
			j2=H/10;
			k1=M%10;
			k2=M/10;
			l1=S%10;
			l2=S/10;
			play(j2,j1,k2,k1,l2,l1);
	}
	if(qq == 2) //�ڶ��ΰ�S1ʱ������
	{
		if(S2 == 0)
		{
			while(!S2);
			if(M < 59)
			{
				M++;
			}
			else
			{
				M = 0;
			}
			num==0;
			delayMS(5);
		}
		if(S3 == 0)
		{
			while(!S3);
			if(M > 0)
			{					
				M--;
			}
			else
			{
				M = 59;
			}
			num==0;
			delayMS(5);
		}
			j1=H%10;
			j2=H/10;
			k1=M%10;
			k2=M/10;
			l1=S%10;
			l2=S/10;
			play(j2,j1,k2,k1,l2,l1);
	}
	if(qq == 3) //�����ΰ�S1ʱ����ʱ
	{
		if(S2 == 0)
		{
			while(!S2);
			if(H < 23)
			{
				H++;
			}
			else
			{
				H = 0;
			}
			num==0;
			delayMS(5);
		}
		if(S3 == 0)
		{
			while(!S3);
			if(H > 0)
			{					
				H--;
			}
			else
			{
				H = 23;
			}
			num==0;
			delayMS(5);

		}
			j1=H%10;
			j2=H/10;
			k1=M%10;
			k2=M/10;
			l1=S%10;
			l2=S/10;
			play(j2,j1,k2,k1,l2,l1);
	}
}






void main()
{
	TIM0_Init();
	TIM1_Init();
	while(1)
	{ 
		stopfunc();
		if(out == 1)
		{
			TR0 = 1;
			TR1=0;
			if(UT == 20) //1���ӵ���----20*50=1000ms
			{	
				UT = 0;
				S++;
				if(S == 60)
				{
					S=0;
					M++;
					if(M == 60)
					{
						M = 0;
						H++;
						if(H == 24) //24Сʱ��
						{
							H = 0;
						}
					}
				}
			}
		
			j1=H%10;
			j2=H/10;
			k1=M%10;
			k2=M/10;
			l1=S%10;
			l2=S/10;
			play(j2,j1,k2,k1,l2,l1);
		
		}
		else
		{
			buttfunc();	
		}
	}
}

void TIME() interrupt 1
{
	TH0 = (65536 - 50000)/256; //��ֵ��2^16=65536  12M 50ms��ʱ
	TL0 = (65536 - 50000)%256;
	UT++;
}

void Timer1_isr(void) interrupt 3 using 1
{
	TH1 = (65536-50000)/256;//����12M 50ms 16bit �Զ�����
 	TL1 = (65536-50000)%256;
	num++;
	if(num==60)
	{
	qq=0;
	out=1;
	num=0;
	}
}




		










 

