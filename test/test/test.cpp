// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<graphics.h>
using namespace std;

void DDA(int x1, int y1, int x2, int y2)
{
	int dx, dy, max, i;
	double th, x, y, xInce, yInce;
	dx = x2 - x1;
	dy = y2 - y1;
	max = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
	th = 1.0 / max;
	xInce = th * dx;
	yInce = th * dy;
	x = x1;
	y = y1;
	for (i = 0; i <= max; i++)
	{
		putpixel(int(x + 0.5), int(y + 0.5), RED);
		x += xInce;
		y += yInce;
	}
}
/*
当差值过小的时候，会出现刚画的线在下一秒就会被清除的情况，这是一个bug
*/
void draw(int *p,int n) {
	drawpoly(n + 1, p);
	int xmin, xmax, ymin, ymax;
	xmin =xmax= p[0];
	ymin = ymax = p[1];
	for (int i = 0; i < 2 * n; i+=2)
	{
		if (p[i] < xmin) xmin = p[i];
		if (p[i] > xmax) xmax = p[i];
		if (p[i + 1] < ymin) ymin = p[i + 1];
		if (p[i + 1] > ymax) ymax = p[i + 1];
	}
	int x0, y0, x1, y1;
	for (int i = 0; i < 2 * n; i += 2) {
		x0 = p[i];
		y0 = p[i + 1];
		x1 = p[i + 2];
		y1 = p[i + 3];
		if (x0 > x1) {
			int buff = x0;
			int buff1 = y0;
			x0 = x1;
			y0 = y1;
			x1 = buff;
			y1 = buff1;
		}
		
		int dx = x1-x0;//之前是x0-x1，是存在错误的
		int dy = y1 - y0;
		int espl = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);//espl应该为正值，存在错误
		float x = x0, y = y0;
		float xince = ((float)dx / (float)espl);//必须加上float，否则会出错
		float yince = ((float)dy / (float)espl);
		float last=-100;//用来记录上一个点，以防止重叠造成误擦或误画
		for (;abs(y-(float)y1)>=1;) {
			if (last != y) {
				float xx = (float)x;
				for (; xx >= xmin&&xx <= xmax; xx += xince) {//xx为int类型，所以加上0.5之后，值是不会改变的
					if (getpixel(int(xx + 0.5), int(y + 0.5)) == RED) continue;
					else if (getpixel(int(xx + 0.5), int(y + 0.5)) == BLACK) putpixel(int(xx + 0.5), int(y + 0.5), BLUE);
					else putpixel(int(xx + 0.5), int(y + 0.5), BLACK);//存在无法填色问题，原因出自drawpoly函数在画直线时误差大
				}
			}
			last = y;
			y += yince;
			x += xince;
		//	line(x, y, 200, 100);
		}
		for (int i = 0; i < 1000000000; i++);
	}
	//line(0, 0, 100, 100);
}
int main()
{	
	int gdrive = DETECT, gmode;
	initgraph(&gdrive, &gmode, "");
	setcolor(RED);
	setbkcolor(WHITE);
	int p[10] = { 10,260,100,160,300,10,210,100,10,260 };
	draw(p, 4);
	for (int i = 0; i < 5; i++)
		cout << "dfad" << endl;
	getchar();
	closegraph();
	cout << "chen" << endl;
	cout << "hello world" << endl;
    return 0;
}

