#include "stdafx.h"
#include<iostream>
#include<graphics.h>
#include<time.h>
using namespace std;

#if 0
int main()
{
		int p[4][2] = { { 20,20 },{ 80,20 },{ 80,80 },{ 20,80 } };
		int n, speed;
		IMAGE w;
		int x_max;
		int p_x_min = 1000, p_y_min = 1000, p_x_max = 0, p_y_max = 0;
		int x_buff, y_buff;
		for (int i = 0; i < 4; i++) {
			if (p_x_min > p[i][0]) p_x_min = p[i][0];
			if (p_x_max < p[i][0]) p_x_max = p[i][0];
			if (p_y_min > p[i][1]) p_y_min = p[i][1];
			if (p_y_max < p[i][1]) p_y_max = p[i][1];
		}
		cout << "请输入三角形的水平位置：" << endl;
		cin >> n;
		cout << "请输入移动的速度:" << endl;
		cin >> speed;
		int a[3][2] = { { 40,10 },{ 10,80 },{ 70,80 } };
		x_max = a[1][0] + n;
		int gdrive = DETECT, gmode;
		initgraph(&gdrive, &gmode, "");
		setcolor(RED);
		//line(0, 100, 638, 100);//大概估计了屏幕的宽度

		for (int i = 0; i < 3; i++) {
			line(p[i][0], p[i][1], p[i + 1][0], p[i + 1][1]);
		}
		line(p[3][0], p[3][1], p[0][0], p[0][1]);
		getimage(&w, 20, 20, 100, 100);
		setcolor(GREEN);
		for (int i = 0; i < 2; i++) {
			line(a[i][0] + n, a[i][1], a[i + 1][0] + n, a[i + 1][1]);
		}
		line(a[2][0] + n, a[2][1], a[0][0] + n, a[0][1]);
		y_buff = p_y_min;
		x_buff = p_x_min;
		for (int i = 0; i < 500; i++) {
			if (x_buff > x_max) {
				break;
			}
			if (x_buff > 638) {
				char *p = "Coordinate out of range";
				settextcolor(RED);
				settextstyle(16, 10, _T("宋体"));
				for (int i = 0; i < 22; i++)
					outtextxy(200 + 10 * i, 200, *(p + i));
				break;
			}
			putimage(x_buff, 20, &w,0);
			x_buff += 20;
			putimage(x_buff, 20, &w);
			Sleep(speed);
		}

		getchar();
		getchar();
		closegraph();
		return 0;
	}
#endif