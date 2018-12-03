#pragma once
#include"stdafx.h"
#include<iostream>
#include <graphics.h>
using namespace std;

class DDA {
public:
	void draw(int x1, int y1, int x2, int y2);
	void test();
};

void DDA::draw(int x1, int y1, int x2, int y2)
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

void DDA::test() {
	int gdrive = DETECT, gmode;
	int x0, y0, x1, y1;
	cout << "请输入第一个点坐标：" << endl;
	cin >> x0 >> y0;
	cout << "请输入第二个点坐标：" << endl;
	cin >> x1 >> y1;
	initgraph(&gdrive, &gmode, "");
	setcolor(RED);
	setbkcolor(WHITE);
	draw(x0, y0, x1, y1);
	getchar();
	closegraph();
	cout << "处理完毕" << endl;
}