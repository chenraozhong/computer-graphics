// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "graphics.h"
#include "stdio.h"
#include "math.h"
#include "conio.h"
#include <iostream>

using namespace std;
void Edge(int a[6][2]);			//定义画边函数
void PutColor(int x1, int y1, int x2, int y2);		//定义填色函数
int main()
{
	int  gdriver, gmode;
	int a[6][2];			//定义顶点
	printf("请输入六边形的各点坐标\n");
	printf("请输入第一个点的坐标:");
	scanf_s("%d,%d", &a[0][0], &a[0][1]);
	printf("请输入第二个点的坐标:");
	scanf_s("%d,%d", &a[1][0], &a[1][1]);
	printf("请输入第三个点的坐标:");
	scanf_s("%d,%d", &a[2][0], &a[2][1]);
	printf("请输入第四个点的坐标:");
	scanf_s("%d,%d", &a[3][0], &a[3][1]);
	printf("请输入第五个点的坐标:");
	scanf_s("%d,%d", &a[4][0], &a[4][1]);
	printf("请输入第六个点的坐标:");
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
	setcolor(RED);		//定义画线颜色
	line(a[0][0], a[0][1], a[1][0], a[1][1]);		//画线
	line(a[1][0], a[1][1], a[2][0], a[2][1]);
	line(a[2][0], a[2][1], a[3][0], a[3][1]);
	line(a[3][0], a[3][1], a[4][0], a[4][1]);
	line(a[4][0], a[4][1], a[5][0], a[5][1]);
	line(a[5][0], a[5][1], a[0][0], a[0][1]);



	PutColor(a[0][0], a[0][1], a[1][0], a[1][1]);	//填色
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
	if (abs(dx) >= abs(dy))		//DDA算法
	{
		max = abs(dx);
	}
	else
	{
		max = abs(dy);
	}
	th = 1.0 / max;
	xInce = th * dx;			//x增量
	yInce = th * dy;			//y增量

	if (y1 <= y2)					//考虑到y1和y2的上下关系
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
		xInce = -xInce;		 //向上画点的话将增量为负
		yInce = -yInce;
	}



	lasty = y;				//控制变量防止点重叠
	for (i = 0; i <= max - 1; i++)
	{
		x = x0 + (i + 1)*xInce;		//找点
		y += yInce;
		if (int(lasty) == int(y))		//若两点相同，则跳过本点
		{
			continue;
		}
		else
		{
			lasty = y;
			for (j = 0; j < 65535; j++)		//向右侧画线
			{
				if (getpixel(int(x + 0.5), int(y + 0.5)) == BLACK)	//求补
					putpixel(int(x + 0.5), int(y + 0.5), RED);
				else
					putpixel(int(x + 0.5), int(y + 0.5), BLACK);
				x = x + 1;		//到下一个点
			}
		}
	}

}



