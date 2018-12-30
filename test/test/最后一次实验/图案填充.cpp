#include "stdafx.h"
#include<iostream>
#include<graphics.h>
#include<vector>
#include<map>
using namespace std;

#if 0
map<int, map<int, int>> flag;

void print_model(int x0, int y0, vector<vector<int > > model,int flag1) {
	if (flag1 == 1) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (model[i][j] == 1) putpixel(x0 - 1 + j, y0 - 1 + i, WHITE);
				//flag[i][j] = 1;
			}
			flag[x0][y0] = 1;
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				putpixel(x0 - 1 + i, y0 - 1 + j, BLACK);
				//flag[i][j] = 0;
			}
			flag[x0][y0] = 0;
		}
	}
}

void init_flag(int xmin, int xmax, int ymin, int ymax) {
	for (int i = xmin; i < xmax; i++) {
		for (int j = ymin; j < ymax; j++)
			flag[i][j] = 0;
	}
}

void draw(int *p, int n,vector<vector<int> > model) {
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
		//getchar();
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
		float xince = dx / espl;
		float yince = dy / espl;
		if (dy / dx<0) {
			float last = y0;
			while (int(last + 0.5) == int(y0 + 0.5)) {
				x0 += xince;
				y0 += yince;
			}
		}
		else {
			float last = y1;
			while (int(last + 0.5) == int(y1 + 0.5)) {
				x1 -= xince;
				y1 -= yince;
			}
		}
		
		float x = (float)x0, y = (float)y0;

		int lasty = int(y0+0.5)-3;//用来记录上一个点，以防止重叠造成误擦或误画
		for (; abs(y - y1) >= 0.001;){
			if ((int(y + 0.5) - 1) % 3 == 0) {
				if (abs(int(y + 0.5) - lasty) >= 3) {
				//	getchar();
					float xx = x;
					int lastx = int(xx + 0.5) - 3;
					for (; xx >= xmin&&xx <= xmax; xx += xince) {//xx为int类型，所以加上0.5之后，值是不会改变
						if ((int(xx + 0.5) - 1) % 3 == 0) {
							if (abs(int(xx + 0.5) - lastx) >= 3) {
								if (flag[int(xx + 0.5)][int(y + 0.5)] == 0) print_model(int(xx + 0.5), int(y + 0.5), model, 1);
								else print_model(int(xx + 0.5), int(y + 0.5), model, 0);//存在无法填色问题，原因出自drawpoly函数在画直线时误差大
								lastx = int(xx + 0.5);
							}
						}
					}
					lasty = int(y + 0.5);
				}
			}
			y += yince;
			x += xince;
		}
//		getchar();
	}
}

int main()
{
	int gdrive = DETECT, gmode;
	int n;
	cout << "请输入图案模板(3*3)" << endl;
	vector<vector<int> > model;
	for (int i = 0; i < 3; i++){
		vector<int> model_buff;
		for (int j = 0; j < 3; j++)
		{
			int buff;
			cin >> buff;
			model_buff.push_back(buff);
		}
		model.push_back(model_buff);
       }
	n = 4;
	getchar();
	initgraph(&gdrive, &gmode, "");
	setcolor(RED);
	setbkcolor(WHITE);
	int p[10] = { 100,50,10,10,50,100,150,150,100,50 };
	draw(p, n,model);
	getchar();
	closegraph();
	cout << "处理完毕" << endl;
	return 0;
}
#endif