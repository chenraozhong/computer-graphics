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
								   { { 400,100 },{ 30,150 },{ 50,300 } } };
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



	POINT ptr1[3] = { { 10,10 },{ 150,150 },{ 200,400 } };
	int z1[3] = { 20,30,1 };
	int A1[3];
	get_coe(A1, ptr1, z1);
	Node *max1 = getmax(ptr1, z1);
	Node *min1 = getmin(ptr1, z1);
	POINT ptr2[3] = { { 20,20 },{ 200,20 },{ 200,200 } };
	int z2[3] = { 5,4,2 };
	int A2[3];
	get_coe(A2, ptr2, z2);
	Node *max2 = getmax(ptr2, z2);
	Node *min2 = getmin(ptr2, z2);
	POINT ptr3[3] = { { 400,100 },{ 30,150 },{ 50,300 } };
	int z3[3] = { 80,45,19 };
	int A3[3];
	get_coe(A3, ptr3, z3);
	Node *max3 = getmax(ptr3, z3);
	Node *min3 = getmin(ptr3, z3);
	POINT ptr4[3] = { { 400,100 },{ 300,150 },{ 500,10 } };
	int z4[3] = { 14,16,18 };
	int A4[3];
	get_coe(A4, ptr4, z4);
	Node *max4 = getmax(ptr4, z4);
	Node *min4 = getmin(ptr4, z4);
	vector<POINT* > p;
	p.push_back(ptr1);
	p.push_back(ptr2);
	p.push_back(ptr3);
	p.push_back(ptr4);
	vector<Node *> max;
	max.push_back(max1);
	max.push_back(max2);
	max.push_back(max2);
	max.push_back(max2);
	vector<Node *> min;
	min.push_back(min1);
	min.push_back(min2);
	min.push_back(min3);
	min.push_back(min4);
	vector<int> line;//优先级队列,优先级越高，越在后面

					 //进行优先级排序
	{
		line.push_back(0);
		for (int i = 1; i < 4; i++) {
			int flagsize = line.size();
			for (int j = 0; j < line.size(); j++) {
				int buff = line[j];
				if ((min[i]->x > max[buff]->x) || (min[buff]->x > max[i]->x))//表示两个图形不重叠，则继续往下比
				{
					continue;
				}
				else {
					if (max[buff]->x > min[i]->x) {
						if (max[buff]->z < min[i]->z) {//表示当前的优先级更高，应继续往下比
							continue;
						}
						else {
							line.insert(line.begin() + j, i);
							break;
						}
					}
					else {
						if (max[i]->z > min[buff]->z) {
							continue;
						}
						else {
							line.insert(line.begin() + j, i);
						}
					}
				}
			}
			if (flagsize == line.size()) {//表示当前优先级最高
				line.insert(line.end(), i);
			}
		}
	}
	int gdrive = DETECT, gmode;
	initgraph(&gdrive, &gmode, "");

	for (int i = 3; i >= 0; i--) {
		switch (line[i])
		{
		case 0: {
			setpolyfillmode(WINDING);
			setfillcolor(GREEN);
			solidpolygon(ptr1, 3);
			break;
		}
		case 1: {
			setpolyfillmode(WINDING);
			setfillcolor(RED);
			solidpolygon(ptr2, 3);
			break;
		}
		case 2: {
			setpolyfillmode(WINDING);
			setfillcolor(YELLOW);
			solidpolygon(ptr3, 3);
			break;
		}
		case 3: {
			setpolyfillmode(WINDING);
			setfillcolor(BLUE);
			solidpolygon(ptr4, 3);
			break;
		}
		default:
			break;
		}
		getchar();
	}
	getchar();
	closegraph();
	return 0;
}
