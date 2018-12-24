
#include "stdafx.h"
#include<graphics.h>
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

#if 1
typedef struct node {
	int x;//�߽�x
	int y;//�߽�y
}Node;

typedef struct Border {
	int xr;
	int xl;
}Border;

//���ƽ�淽�̵�ϵ��
void get_coe(vector<int> &A, vector<POINT > ptr, vector<int> z) {
	A[0] = (ptr[1].y - ptr[0].y)*(z[2] - z[0]) - (z[1] - z[0])*(ptr[2].y - ptr[0].y);
	A[1] = (ptr[2].x - ptr[0].x)*(z[1] - z[0]) - (ptr[1].x - ptr[0].x)*(z[2] - z[0]);
	A[2] = (ptr[1].x - ptr[0].x)*(ptr[2].y - ptr[0].y) - (ptr[2].x - ptr[0].x)*(ptr[1].y - ptr[0].y);
	A[3] = -(A[0] * ptr[0].x + A[1] * ptr[0].y + A[2] * z[0]);
}

//�����ÿ������yֵ������xֵ
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

//�����ÿ������С��yֵ����С��xֵ
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

void get_eidge_point(map<int, int> eidge, POINT point1,POINT point2) {
	float k = (float)(point1.y - point2.y) / (float)(point1.x - point2.x);
	if (point1.x > point2.x) {
		POINT buff;
		buff = point1;
		point2 = buff;
		point1 = point2;
	}
	float detx, dety;
	if (k > 1) {
		detx = 1 / k;
		dety = 1;
	}
	else {
		detx = 1;
		dety = k;
	}
	float x = point1.x;
	float y = point1.y;
	while (true) {
		eidge[(int)(y + 0.5)] = (int)(x + 0.5);
		x += detx;
		y += dety;
		if (x >= point2.x) break;
	}
}

void get_Eidge(vector<map<int, Border> > &Eidge, vector<vector<POINT > >ptr) {
	for (int i = 0; i < ptr.size(); i++) {
		//eidge1��eidge2��eidge3�ֱ�洢�������ÿһ�����ϵĵ�����
		vector<map<int, int>> eidge;
		get_eidge_point(eidge[0], ptr[i][0], ptr[i][1]);
		get_eidge_point(eidge[1], ptr[i][1], ptr[i][2]);
		get_eidge_point(eidge[2], ptr[i][2], ptr[i][0]);
		int y[3];
		for (int pp = 0; pp < 3; pp++)
			y[pp] = ptr[i][pp].y;
		sort(y[0],y[2]);
		for (int pp = 0; pp < 2; pp++) {
			int count = 2;//ѡ����yֵΪy[pp]�ı�
			vector<int> e;
			for (int j = 0; j < 3; j++) {
				if (eidge[j].find(y[pp]) != eidge[j].end() && count >= 0) {
					count--;
					e.push_back(j);
				}
			}
//////////////////////////////////////////////////////////////////////////////////////////////
		}
	}
}

int main() {
	COLORREF color[4] = { RED,YELLOW,BLUE,GREEN };
	//����Ķ����x��y����
	vector<vector<POINT> > ptr = { { { 100,100 },{ 50,340 },{ 350,250 } },
								   { { 75,210 },{ 200,75 },{ 550,200 } } ,
								   { { 150,330 },{ 250,150 },{ 300,350 } } ,
							       { { 400,50 },{ 500,50 },{ 450,300 } } };
	//��������淽�̵�ϵ��
	vector<vector <int> > A = { { 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } };
	//��������涥���z����
	vector<vector<int> > z = { { 20,30,1 },
							   { 4,5,200 } ,
							   { 10,20,1 } ,
							   { 14,16,18 } };


	vector<Node *> min;
	vector<Node *> max;
	/*
		ʹ��map���洢ÿһ���������һ��y���ϵ�����x�ı߽�ֵ�������ڸ���Z_BUFFER�е�zֵʹ�á�	
	*/
	vector<map<int, Border> > Eidge;
	get_Eidge(Eidge,ptr);

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
	vector<vector <COLORREF > > color_buffer;
	vector<vector<float > > z_buffer;

	int gdrive = DETECT, gmode;
	cout << &gdrive << endl;
	return 0;
	
}
#endif