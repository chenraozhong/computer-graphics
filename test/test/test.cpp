// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "graphics.h"
#include "stdio.h"
#include "math.h"
#include "conio.h"
#include <iostream>

using namespace std;
void Edge(int a[6][2]);			//���廭�ߺ���
void PutColor(int x1, int y1, int x2, int y2);		//������ɫ����
int main()
{
	int  gdriver, gmode;
	int a[6][2];			//���嶥��
	printf("�����������εĸ�������\n");
	printf("�������һ���������:");
	scanf_s("%d,%d", &a[0][0], &a[0][1]);
	printf("������ڶ����������:");
	scanf_s("%d,%d", &a[1][0], &a[1][1]);
	printf("������������������:");
	scanf_s("%d,%d", &a[2][0], &a[2][1]);
	printf("��������ĸ��������:");
	scanf_s("%d,%d", &a[3][0], &a[3][1]);
	printf("�����������������:");
	scanf_s("%d,%d", &a[4][0], &a[4][1]);
	printf("������������������:");
	scanf_s("%d,%d", &a[5][0], &a[5][1]);
	gdriver = DETECT;
	initgraph(&gdriver, &gmode, "");
	Edge(a);
	getchar();
	closegraph();
	return 0;
}
void Edge(int a[6][2])
{
	setcolor(RED);		//���廭����ɫ
	line(a[0][0], a[0][1], a[1][0], a[1][1]);		//����
	line(a[1][0], a[1][1], a[2][0], a[2][1]);
	line(a[2][0], a[2][1], a[3][0], a[3][1]);
	line(a[3][0], a[3][1], a[4][0], a[4][1]);
	line(a[4][0], a[4][1], a[5][0], a[5][1]);
	line(a[5][0], a[5][1], a[0][0], a[0][1]);



	PutColor(a[0][0], a[0][1], a[1][0], a[1][1]);	//��ɫ
	PutColor(a[1][0], a[1][1], a[2][0], a[2][1]);
	PutColor(a[2][0], a[2][1], a[3][0], a[3][1]);
	PutColor(a[3][0], a[3][1], a[4][0], a[4][1]);
	PutColor(a[4][0], a[4][1], a[5][0], a[5][1]);
	PutColor(a[5][0], a[5][1], a[0][0], a[0][1]);

}
void PutColor(int x1, int y1, int x2, int y2)
{

	int dx, dy, max, i, j, x0;
	double lasty = 0;
	double th, x, y, xInce, yInce;
	dx = x2 - x1;
	dy = y2 - y1;
	if (abs(dx) >= abs(dy))		//DDA�㷨
	{
		max = abs(dx);
	}
	else
	{
		max = abs(dy);
	}
	th = 1.0 / max;
	xInce = th * dx;			//x����
	yInce = th * dy;			//y����

	if (y1 <= y2)					//���ǵ�y1��y2�����¹�ϵ
	{
		x = x1;
		x0 = x1;
		y = y1;
	}
	else
	{
		x = x2;
		x0 = x2;
		y = y2;
		xInce = -xInce;		 //���ϻ���Ļ�������Ϊ��
		yInce = -yInce;
	}



	lasty = y;				//���Ʊ�����ֹ���ص�
	for (i = 0; i <= max - 1; i++)
	{
		x = x0 + (i + 1)*xInce;		//�ҵ�
		y += yInce;
		if (int(lasty) == int(y))		//��������ͬ������������
		{
			continue;
		}
		else
		{
			lasty = y;
			for (j = 0; j < 65535; j++)		//���Ҳ໭��
			{
				if (getpixel(int(x + 0.5), int(y + 0.5)) == BLACK)	//��
					putpixel(int(x + 0.5), int(y + 0.5), RED);
				else
					putpixel(int(x + 0.5), int(y + 0.5), BLACK);
				x = x + 1;		//����һ����
			}
		}
	}

}



