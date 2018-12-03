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
void draw(int *p, int n) {
	for (int i = 0; i < 2 * n; i += 2)
		line(p[i], p[i + 1], p[i + 2], p[i + 3]);
	int xmin, xmax, ymin, ymax;
	xmin = xmax = p[0];
	ymin = ymax = p[1];
	for (int i = 0; i < 2 * n; i += 2)
	{
		if (p[i] < xmin) xmin = p[i];
		if (p[i] > xmax) xmax = p[i];
		if (p[i + 1] < ymin) ymin = p[i + 1];
		if (p[i + 1] > ymax) ymax = p[i + 1];
	}
	float x0, y0, x1, y1;
	for (int i = 0; i < 2 * n; i += 2) {
		x0 = (float)p[i];
		y0 = (float)p[i + 1];
		x1 = (float)p[i + 2];
		y1 = (float)p[i + 3];
		if (x0 > x1) {
			float buff = x0;
			float buff1 = y0;
			x0 = x1;
			y0 = y1;
			x1 = buff;
			y1 = buff1;
		}

		float dx = x1 - x0;
		float dy = y1 - y0;

		float espl = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
		float x = (float)x0, y = (float)y0;
		float xince = dx /espl;
		float yince = dy / espl;


		int lasty = -100;//用来记录上一个点，以防止重叠造成误擦或误画
		for (; abs(y - y1) >= 0.001;) {
			if (lasty !=int( y+0.5)) {
				float xx = x;
				int lastx = -100;
				for (; xx >= xmin&&xx <= xmax; xx += xince) {//xx为int类型，所以加上0.5之后，值是不会改变的
					if (lastx != int(xx + 0.5)) {
						if (getpixel(int(xx + 0.5), int(y + 0.5)) == RED) continue;
						else if (getpixel(int(xx + 0.5), int(y + 0.5)) == BLACK) putpixel(int(xx + 0.5), int(y + 0.5), BLUE);
						else putpixel(int(xx + 0.5), int(y + 0.5), BLACK);//存在无法填色问题，原因出自drawpoly函数在画直线时误差大
					}
					lastx = int(xx + 0.5);
				}
			//	for (int i = 0; i < 10000000; i++);
			}
			lasty = int(y+0.5);
			y += yince;
			x += xince;
			//	line(x, y, 200, 100);
		}
	//	for (int i = 0; i < 100000000; i++);
	}
	//line(0, 0, 100, 100);
}
int main()
{
	int gdrive = DETECT, gmode;
	int n;
	cout << "请输入多边形的顶点个数" << endl;
	cin >> n;
	cout << "请输入多边形个顶点的坐标" << endl;
	int q[20];
	for (int i = 0; i < 2 * n; i++)
		cin >> q[i];
	int jj = q[3];
	q[2 * n] = q[0];
	q[2 * n + 1] = q[1];
	getchar();
	initgraph(&gdrive, &gmode, "");
	setcolor(RED);
	setbkcolor(WHITE);
	draw(q, n);
	getchar();
	closegraph();
	cout << "处理完毕" << endl;
	return 0;
}

