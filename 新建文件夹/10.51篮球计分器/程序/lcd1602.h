#ifndef LCD1602_H
#define LCD1602_H

#include "reg52.h"

 //�˿ڶ���
#define  DBPort P0    //LCD���ݶ˿�

sbit LcdRs		= P3^5;
sbit LcdRw		= P3^6;
sbit LcdEn  	= P3^4;
sbit Lcdbf    = P0^7; //LCDæ��־ Busy Flag

void LCD_Initial(void);                                            //��ʼ����
void delay(unsigned int t);                                        //��ʱ��
void LCD_Write(bit style, unsigned char input);										 //λд
void Print(unsigned char *str, unsigned char x, unsigned char y);	 //ָ����������ַ�����
void display_int(unsigned int dat, unsigned char x, unsigned char y, unsigned char num_size);//��ʾ���������ȿɵ�����
#endif