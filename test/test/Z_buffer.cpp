
#include "stdafx.h"
#include<graphics.h>
#include<iostream>
#include<vector>
using namespace std;


typedef struct node {
	int x;//边界x
	int y;//边界y
}Node;

//求出平面方程的系数
void get_coe(vector<int> &A, vector<POINT > ptr, vector<int> z) {
	A[0] = (ptr[1].y - ptr[0].y)*(z[2] - z[0]) - (z[1] - z[0])*(ptr[2].y - ptr[0].y);
	A[1] = (ptr[2].x - ptr[0].x)*(z[1] - z[0]) - (ptr[1].x - ptr[0].x)*(z[2] - z[0]);
	A[2] = (ptr[1].x - ptr[0].x)*(ptr[2].y - ptr[0].y) - (ptr[2].x - ptr[0].x)*(ptr[1].y - ptr[0].y);
	A[3] = -(A[0] * ptr[0].x + A[1] * ptr[0].y + A[2] * z[0]);
}


//计算出每个最大的y值和最大的x值
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

//计算出每个面最小的y值和最小的x值
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

int main() {
	COLORREF color[4] = { RED,YELLOW,BLUE,GREEN };
	//各面的顶点的x和y坐标
	vector<vector<POINT> > ptr = { { { 100,100 },{ 50,340 },{ 350,250 } },
								   { { 75,210 },{ 200,75 },{ 550,200 } } ,
								   { { 150,330 },{ 250,150 },{ 300,350 } } ,
							       { { 400,50 },{ 500,50 },{ 450,300 } } };
	//用来存放面方程的系数
	vector<vector <int> > A = { { 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } };
	//用来存放面顶点的z坐标
	vector<vector<int> > z = { { 20,30,1 },
							   { 4,5,200 } ,
							   { 10,20,1 } ,
							   { 14,16,18 } };


	vector<Node *> min;
	vector<Node *> max;

	for (int i = 0; i < 4; i++) {
		get_coe(A[i], ptr[i], z[i]);
		max.push_back(getmax(ptr[i]));
		min.push_back(getmin(ptr[i]));
	}
	int buff_minx = min[0]->x;
	int buff_miny = min[0]->y;
	int buff_maxx = max[0]->x;
	int buff_maxy = max[0]->y;

	for (int i = 1; i < 4; i++) {
		if (buff_minx > min[i]->x) buff_minx = min[i]->x;
		if (buff_miny > min[i]->y) buff_miny = min[i]->y;
		if (buff_maxx < max[i]->x) buff_maxx = max[i]->x;
		if (buff_maxy < max[i]->y) buff_maxy = max[i]->y;
	}
	
	int gdrive = DETECT, gmode;
	cout << &gdrive << endl;
	return 0;
	
}