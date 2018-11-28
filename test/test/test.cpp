// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<graphics.h>
using namespace std;

void draw(int *p,int n) {
	drawpoly(n+1, p);
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
	int flag = 0;
	for (int y = ymin; y <= ymax; y++)
	{
		for (int x = xmin; x <= xmax; x++)
		{
			if (getpixel(x, y) == RED) {
				flag = 1;
				continue;
			}
			if (flag) {
				int pp = x;
				for (; pp <= xmax; pp++) {
					if (getpixel(pp, y) == RED) continue;
					else if (getpixel(pp, y) == BLACK) putpixel(pp, y, BLUE);
					else putpixel(pp, y, BLACK);
				}
			}
		}
		flag = 0;
	}
	
}
int main()
{	
	int gdrive = DETECT, gmode;
	initgraph(&gdrive, &gmode, "");
	setcolor(RED);
	setbkcolor(WHITE);
	int p[8] = { 10,20,150,150,200,30,10,20 };
	draw(p, 3);
	for (int i = 0; i < 5; i++)
		cout << "dfad" << endl;
	getchar();
	closegraph();
	cout << "chen" << endl;
	cout << "hello world" << endl;
    return 0;
}

