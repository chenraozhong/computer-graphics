// 2.cpp.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include<graphics.h>
#include<iostream>
#include<vector>
using namespace std;

typedef struct node {
	int x;//边界x
	int y;//边界y
}Node;

Node* getmax(vector<POINT> ptr) {
	int maxx = ptr[0].x;
	int maxy = ptr[0].y;
	for (int i = 1; i < 3; i++)
	{
		if (maxx < ptr[i].x) maxx = ptr[i].x;
		if (maxy < ptr[i].y) maxy = ptr[i].y;
	}
	Node *n = new Node();
	n->x = maxx;
	n->y = maxy;
	return n;
}

Node* getmin(vector<POINT > ptr) {
	int minx = ptr[0].x;
	int miny = ptr[0].y;
	for (int i = 1; i < 3; i++) {
		if (minx > ptr[i].x) minx = ptr[i].x;
		if (miny > ptr[i].y) miny = ptr[i].y;
	}
	Node *n = new Node();
	n->x = minx;
	n->y = miny;
	return n;
}

void get_coe(vector<int> A, vector<POINT > ptr, vector<int> z) {//求出平面方程的系数
	A[0] = (ptr[1].y - ptr[0].y)*(z[2] - z[0]) - (z[1] - z[0])*(ptr[2].y - ptr[0].y);
	A[1] = (ptr[2].x - ptr[0].x)*(z[1] - z[0]) - (ptr[1].x - ptr[0].x)*(z[2] - z[0]);
	A[2] = (ptr[1].x - ptr[0].x)*(ptr[2].y - ptr[0].y) - (ptr[2].x - ptr[0].x)*(ptr[1].y - ptr[0].y);
	A[3] = -ptr[0].x*ptr[1].y*z[2] + ptr[0].x + ptr[2].y*z[1] + ptr[1].x*ptr[0].y*z[2]
		- ptr[1].x*ptr[2].y*z[0] - ptr[2].x*ptr[0].y*z[1] + ptr[2].x*ptr[1].y*z[0];
}

void Sort(vector<int > &line, vector<Node*> max, vector<Node*> min, vector<vector <int> > A) {
	line.push_back(0);
	for (int i = 1; i < 4; i++) {
		int buff = line[0];
		int flagsize = line.size();
		for (int j = 0; j < line.size(); j++) {
			if ((max[buff]->x < min[i]->x) || (max[i]->x < min[buff]->x)) {//如果在x方向上不重叠
				continue;
			}
			else {
				if ((max[buff]->y < min[i]->y) || (max[i]->y < min[buff]->y)) {
					continue;
				}
				else {
					int x_left = min[buff]->x > min[i]->x ? min[buff]->x : min[i]->x;
					int x_right = max[buff]->x < max[i]->x ? max[buff]->x : max[i]->x;
					int y_up = max[buff]->y < max[i]->y ? max[buff]->y : max[i]->y;
					int y_down = min[buff]->y > min[i]->y ? min[buff]->y : min[i]->y;
					int x_middle = (x_left + x_right) / 2;
					int y_middle = (y_up + y_down) / 2;
					float z_i = (float)(-A[i][0] * x_middle - A[i][1] * y_middle - A[i][3]) / (float)A[i][2];
					float z_buff = (float)(-A[buff][0] * x_middle - A[buff][1] * y_middle - A[buff][3])/ (float)A[i][2];
					if (z_i > z_buff) {
						continue;
					}
					else {
						line.insert(line.begin() + j, i);
						break;
					}
				}
			}
		}
		if (flagsize == line.size()) {
			line.insert(line.end(), i);
		}
	}
}

int main()
{
	COLORREF color[4] = { RED,YELLOW,BLUE,GREEN };
	vector<vector<POINT> > ptr = { { { 10,10 },{ 150,150 },{ 200,400 } },
								   { { 20,20 },{ 200,20 },{ 200,200 } } ,
								   { { 400,100 },{ 30,150 },{ 50,300 } } ,
								   { { 40,10 },{ 300,150 },{ 130,30 } } };
	vector<vector <int> > A = { {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} };
	vector<vector<int> > z = { { 20,30,1 },
							   { 5,4,2 } ,
							   { 80,45,19 } ,
							   { 14,16,18 } };
	vector<Node *> min;
	vector<Node *> max;

	for (int i = 0; i < 4; i++) {
		get_coe(A[i], ptr[i], z[i]);
		max.push_back(getmax(ptr[i]));
		min.push_back(getmin(ptr[i]));
	}
	vector<int > line;
	Sort(line, max, min, A);

	int gdrive = DETECT, gmode;
	initgraph(&gdrive, &gmode, "");
	for (int i = 0; i < 4; i++) {
		POINT point[3];
		for (int j = 0; j <3; j++) {
			point[j].x = ptr[line[i]][j].x;
			point[j].y = ptr[line[i]][j].y;
		}
		setpolyfillmode(WINDING);
		setfillcolor(color[line[i]]);
		solidpolygon(point, 3);
		for (int pp = 0; pp < 3; pp++) {
			settextcolor(WHITE);
			settextstyle(9, 9, _T("楷体"));
			int zz = z[line[i]][pp];
			int x = ptr[line[i]][pp].x;
			int y = ptr[line[i]][pp].y;
			while (true) {
				outtextxy(x, y, char((zz % 10)+48));
				zz = zz / 10;
				if (zz == 0) break;
				x -= 9;
			}
		}
		getchar();
	}
	getchar();
	closegraph();
	for (int i = 0; i < 4; i++)
		cout << line[i] << endl;
	return 0;
}
