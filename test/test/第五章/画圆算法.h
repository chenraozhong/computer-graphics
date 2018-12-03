#pragma once
#include<iostream>
#include<graphics.h>
using namespace std;

class Circle {
public:
	void draw(int x0,int y0,int R,COLORREF color);
	void test();
};

void Circle::draw(int x0,int y0 , int R,COLORREF color) {
	int x, y, d;
	x = 0;
	y = R;
	d = 1 - R;
	while (x <= y) {
		putpixel(x+x0, y+y0, color);
		putpixel(y + x0,x+y0, color);
		putpixel(x+x0, -y+y0, color);
		putpixel(-y+x0,x + y0, color);
		putpixel(-x+x0, y+y0, color);
		putpixel( y + x0,-x+y0, color);
		putpixel(-x+x0, -y+y0,color);
		putpixel(-y + x0, -x + y0, color);
		if (d < 0) d += 2 * x + 3;
		else {
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
	}
}

void Circle::test() {
	int R, x0, y0;
	cout << "ÇëÊäÈëÔ²µÄ°ë¾¶:";
	cin >> R;
	cout << "ÇëÊäÈëÔ²µÄÔ²ÐÄ:";
	cin >> x0 >> y0;
	int gdrive = DETECT, gmode;
	initgraph(&gdrive,&gmode, "");
	draw(x0, y0, R, GREEN);
	getchar();
	getchar();
	getchar();
	closegraph();
}