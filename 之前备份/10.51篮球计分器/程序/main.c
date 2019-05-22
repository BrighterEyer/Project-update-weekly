#include <reg52.h>
#include "lcd1602.h"

sbit S1 = P3^0;//��ͣ����ʼ
sbit S2 = P3^1;//����
sbit S3 = P3^2;//a
sbit S4 = P3^3;//b

unsigned char Ascore, Bscore; // A/B���ӱȷ֣�
unsigned char ChangeFlag;//������־�� ����������
unsigned char StartFlag = 1; //��ʼ������־��

void KeyCon(void)
{
	static unsigned char flag1, flag2, flag3, flag4;//����������
	if(S1 == 0) flag1 = 1;
	if(S1 == 1 && flag1 == 1) {flag1 = 0; StartFlag =! StartFlag; Print("                ", 0, 0);}

	if(S2 == 0) flag2 = 1;
	if(S2 == 1 && flag2 == 1) {flag2 = 0; ChangeFlag =! ChangeFlag;}

	if(S3 == 0) flag3 = 1;
	if(S3 == 1 && flag3 == 1) {flag3 = 0; if(StartFlag)Ascore++;}

	if(S4 == 0) flag4 = 1;
	if(S4 == 1 && flag4 == 1) {flag4 = 0; if(StartFlag)Bscore++;}
}

void main(void)
{	
	LCD_Initial();//��ʼ��LCD;
	while(1)
	{	
		KeyCon(); //����ɨ�裻
		if(StartFlag == 1)//������ʼ��
		{	
			Print("VS", 8, 0);//�̶���ʾ��
			Print(":", 8, 1);
			if(ChangeFlag == 1)//����ת����
			{
				Print(" IG", 2, 0);//��ʾ������
				Print("RNG", 12, 0);

				display_int( Ascore, 2, 1, 3);//��ʾ�ȷ֣�
				display_int(Bscore, 12, 1, 3);
			}
			else //������ʾ��
			{
				Print(" IG", 12, 0);
				Print("RNG", 2, 0);
				display_int( Ascore, 12, 1, 3);
				
				display_int(Bscore, 2, 1, 3);
			}
			
		}
		else  Print(" *****STOP***** ", 0, 0); //������ͣ����ͣ��ʾ��			
	}
}