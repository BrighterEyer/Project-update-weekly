#include <reg52.h>//ͷ�ļ�
#define uint unsigned int//�궨��
#define uchar unsigned char
sbit k=P3^0;//�ܿ��ư�����P3.0�˿�
sbit qingling=P3^1;//�ܿ��ư�����P3.0�˿�
sbit g1=P3^2;
sbit g2=P3^3;
sbit feng=P3^7;
uchar fangui;
uchar com=0;
uchar miao=10;
uchar miaoshi=0;
uchar qdb;
uchar code tab[]={//����ܵ����� һά����
	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xbf
};
uchar buf[]={
	0,0
};
uchar xuanshou=10;//ѡ�ֺ�  ��ֵΪʲôҲ������ʾ
void yanshi(uint x)//������ʱ����
{
	uchar i;
	while(x--)
		for(i=0;i<123;i++);
}
void fuzhi()
{
	buf[0]=miao/10%10;
	buf[1]=miao%10;
}
void xuanshouhaofuzhi()
{
	buf[0]=xuanshou/10%10;
	buf[1]=xuanshou%10;
}
void xianshi()//��ʾ����
{
	g1=1;
	g2=0;
	P0=tab[buf[0]];
	yanshi(1);
	g1=0;
	P0=0xff;
	g2=1;
	P0=tab[buf[1]];
	yanshi(1);
	g2=0;
}
void qingchu()//����Ӻ���
{
	xuanshou=10;//ѡ�ֺ�Ϊ10������ܲ���ʾ
	P1=0xff;//���е�ָʾ����
	miao=0;
	qdb=0;
}
void sss()interrupt 3
{
	TH1=(65536-50000)/256;//50ms�ж���һ��
	TL1=(65536-50000)%256;
	if(qdb==1)
	{
		miaoshi++;
		if(miaoshi==20&miao>0&com==0)
		{
			miaoshi=0;
			miao--;
		}
		if(com==1)
			xuanshouhaofuzhi();
		else
			fuzhi();
	}
	xianshi();//�������ʾ��������ж���Ϊ�˷�ֹ�������˸
}
void xs()interrupt 1//��ʱ���ж�0
{
	uchar i;
	TH0=(65536-5000)/256;//50ms�ж���һ��
	TL0=(65536-5000)%256;
	if(fangui==1)
	{
		i++;
		feng=!feng;
		if(i==100)
		{
			i=0;
			fangui=0;
		}
	}
}
void main()
{
	TMOD=0x11;//�����жϷ�ʽΪT0 16Ϊ��ʱ���ж�
	TH0=(65536-5000)/256;//����ʼֵ50ms�ж�һ��
	TL0=(65536-5000)%256;
	TH1=(65536-50000)/256;//����ʼֵ50ms�ж�һ��
	TL1=(65536-50000)%256;
	EA=1; //��������λ
	ET0=1;//����T0�ж�
	ET1=1;
	TR1=1;
	TR0=1;//��T0����ʼ��ʱ
	while(1)//��ѭ��
	{
LL:
		if((P2&0x0f)!=0x0f)
			fangui=1;
		if(!k)//����ܰ�������
		{
			yanshi(50);//��ʱ100ms����
			if(!k)//����ܰ���������
			{
				miao=10;
				miaoshi=0;
				qdb=1;
				while(!k);//���ܰ����ɿ�����ִ��
				while(1)//��ѭ��
				{
					if(!qingling&com==1)//
					{
L1:
						qingchu();//���һ������
						fuzhi();
						com=0;//�������ۼ�
						goto LL;
					}
					if(miao==0)
					{
						com=1;
						goto L1;
					}
					if(com==0&miao>0)//�����ʼ������û���������
					{
						switch(P2)//�ж�P2�˿�
						{
							case 0xfe:xuanshou=1;com=1;break;//1��ѡ������ɹ�
							case 0xfd:xuanshou=2;com=1;break;//2��ѡ������ɹ�
							case 0xfb:xuanshou=3;com=1;break;//3��ѡ������ɹ�
							case 0xf7:xuanshou=4;com=1;break;//4��ѡ������ɹ�
							default: xuanshou=11;break;//�������ǰ���ж��˰����Լ��ļ�����Ч
						}
					}
					if(com==1)//����������
					{
						switch(xuanshou)//�ж�ѡ�ֺ�
						{
							case 1:P1=0xfe;break;//1��ѡ��ѡ����1�ŵ���
							case 2:P1=0xfd;break;//2��ѡ��ѡ����1�ŵ���
							case 3:P1=0xfb;break;//3��ѡ��ѡ����1�ŵ���
							case 4:P1=0xf7;break;//4��ѡ��ѡ����1�ŵ���
							default: break;//���������ޱ仯
						}
					}
				}
			}
		}
	}
}
