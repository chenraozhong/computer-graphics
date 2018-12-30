// 2.cpp.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include<graphics.h>
#include<iostream>
#include<vector>
using namespace std;

#if 0
typedef struct node {
	int x;//�߽�x
	int y;//�߽�y
}Node;

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

//���ƽ�淽�̵�ϵ��
void get_coe(vector<int> &A, vector<POINT > ptr, vector<int> z) {
	A[0] = (ptr[1].y - ptr[0].y)*(z[2] - z[0]) - (z[1] - z[0])*(ptr[2].y - ptr[0].y);
	A[1] = (ptr[2].x - ptr[0].x)*(z[1] - z[0]) - (ptr[1].x - ptr[0].x)*(z[2] - z[0]);
	A[2] = (ptr[1].x - ptr[0].x)*(ptr[2].y - ptr[0].y) - (ptr[2].x - ptr[0].x)*(ptr[1].y - ptr[0].y);
	A[3] = -(A[0] * ptr[0].x + A[1] * ptr[0].y + A[2] * z[0]);
}

//���ȼ�����
void Sort(vector<int > &line, vector<Node*> max, vector<Node*> min, vector<vector <int> > A,vector<vector <int> >sort_array) {
	
	vector<int> wait_line;//�������治�ص�ʱ��������������������ȼ����򣬽�����뵽�ȴ����е��С��������涼�������֮��
						//�����½��в�������������Բ������ȶ����е����ص�������뵽���������Ϊ���ȼ����
	line.push_back(0);
	for (int i = 1; i < 4; i++) {
		int flagsize = line.size();//�ж����ȶ������Ƿ����µĲ���
		int wait_flag = 1;//�ж��Ƿ������ȶ����е�������ص�
		for (int j = 0; j < line.size(); j++) {
			if (sort_array[i][line[j]] == -1) {
				line.insert(line.begin() + j, i);
				wait_flag = 0;
				break;
			}
			else if (sort_array[i][line[j]] == 1) {
				wait_flag = 0;
				continue;
			}
		}
		if (flagsize == line.size()) {
			if (wait_flag == 1) {
				wait_line.push_back(i);
			}
			else {
				line.push_back(i);
			}
		}
	}

	//�Եȴ������е����ٽ�������
	for (int i = 0; i < wait_line.size(); i++) {
		int flagsize = line.size();
		for (int j = 0; j < line.size(); j++) {
			 if (sort_array[wait_line[i]][line[j]] == -1) {
				line.insert(line.begin() + j, wait_line[i]);
				break;
			}
		}
		if (flagsize == line.size()) {
			line.push_back(wait_line[i]);
		}
	}
}

//�õ����ȼ�����
void get_array(vector< vector<int > > &sort_array, vector< vector<int> > A,vector<Node *> max,vector<Node*> min) {
	for (int i = 0; i < 3; i++) {
		for (int j = i+1; j < 4; j++) {
			if ((max[i]->x < min[j]->x) || (max[j]->x < min[i]->x)) {
				continue;
			}
			else {
				if ((max[i]->y < min[j]->y) || max[j]->y < min[i]->y) {
					continue;
				}
				else {
					int x_left = min[j]->x > min[i]->x ? min[j]->x : min[i]->x;
					int x_right = max[j]->x < max[i]->x ? max[j]->x : max[i]->x;
					int y_up = max[j]->y < max[i]->y ? max[j]->y : max[i]->y;
					int y_down = min[j]->y > min[i]->y ? min[j]->y : min[i]->y;
					int x_middle = (x_left + x_right) / 2;
					int y_middle = (y_up + y_down) / 2;
					float z_i = (float)(-A[i][0] * x_middle - A[i][1] * y_middle - A[i][3]) / (float)A[i][2];
					float z_j= (float)(-A[j][0] * x_middle - A[j][1] * y_middle - A[j][3]) / (float)A[j][2];
					if (z_i > z_j) {
						sort_array[i][j] = 1;
						sort_array[j][i] = -1;
					}
					else {
						sort_array[i][j] = -1;
						sort_array[j][i] = 1;
					}
				}
			}
		}
	}
}

int main()
{
	COLORREF color[4] = { RED,YELLOW,BLUE,GREEN };
	//����Ķ����x��y����
	vector<vector<POINT> > ptr = { { { 100,100 },{ 50,340 },{ 350,250 } },
								   { { 75,210 },{ 200,75 },{ 550,200 } } ,
								   { { 150,330 },{ 250,150 },{ 300,350 } } ,
								   { { 400,50 },{ 500,50 },{ 450,300 } } };
	//��������淽�̵�ϵ��
	vector<vector <int> > A = { {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} };
	//��������涥���z����
	vector<vector<int> > z = { { 20,30,1 },
							   { 40,50,200 } ,
							   { 10,20,10 } ,
							   { 14,16,180 } };
	vector<Node *> min;
	vector<Node *> max;

	for (int i = 0; i < 4; i++) {
		get_coe(A[i], ptr[i], z[i]);
		max.push_back(getmax(ptr[i]));
		min.push_back(getmin(ptr[i]));
	}

	/*
	���ȼ����������洢������֮�����ȼ���С�Ĺ�ϵ��
	���磺A[0][1]=0:��ʾ��1����͵�2���治�ص�
		  A[0][1]=1:��ʾ��1��������ȼ����ڵ�2����
		  A[0][1]=-1:��ʾ��1��������ȼ�С�ڵ�2����
	*/

	vector<vector <int> > sort_array = { {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} };

	get_array(sort_array, A,max,min);
	vector<int > line;
	Sort(line, max, min, A,sort_array);
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
			settextstyle(9, 9, _T("����"));
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
	return 0;
}
#endif