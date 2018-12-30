// 2.cpp.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include<graphics.h>
#include<iostream>
#include<vector>
using namespace std;

#if 0
typedef struct node {
	int x;//边界x
	int y;//边界y
}Node;

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

//求出平面方程的系数
void get_coe(vector<int> &A, vector<POINT > ptr, vector<int> z) {
	A[0] = (ptr[1].y - ptr[0].y)*(z[2] - z[0]) - (z[1] - z[0])*(ptr[2].y - ptr[0].y);
	A[1] = (ptr[2].x - ptr[0].x)*(z[1] - z[0]) - (ptr[1].x - ptr[0].x)*(z[2] - z[0]);
	A[2] = (ptr[1].x - ptr[0].x)*(ptr[2].y - ptr[0].y) - (ptr[2].x - ptr[0].x)*(ptr[1].y - ptr[0].y);
	A[3] = -(A[0] * ptr[0].x + A[1] * ptr[0].y + A[2] * z[0]);
}

//优先级排序
void Sort(vector<int > &line, vector<Node*> max, vector<Node*> min, vector<vector <int> > A,vector<vector <int> >sort_array) {
	
	vector<int> wait_line;//当两个面不重叠时，不对这两个面进行优先级排序，将面插入到等待队列当中。待其他面都排序完成之后
						//再重新进行插入排序。若最后仍不与优先队列中的面重叠，则插入到队列最后，设为优先级最高
	line.push_back(0);
	for (int i = 1; i < 4; i++) {
		int flagsize = line.size();//判断优先队列中是否有新的插入
		int wait_flag = 1;//判断是否与优先队列中的面存在重叠
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

	//对等待队列中的面再进行排序
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

//得到优先级矩阵
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
	//各面的顶点的x和y坐标
	vector<vector<POINT> > ptr = { { { 100,100 },{ 50,340 },{ 350,250 } },
								   { { 75,210 },{ 200,75 },{ 550,200 } } ,
								   { { 150,330 },{ 250,150 },{ 300,350 } } ,
								   { { 400,50 },{ 500,50 },{ 450,300 } } };
	//用来存放面方程的系数
	vector<vector <int> > A = { {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} };
	//用来存放面顶点的z坐标
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
	优先级矩阵，用来存储各个面之间优先级大小的关系。
	例如：A[0][1]=0:表示第1个面和第2个面不重叠
		  A[0][1]=1:表示第1个面的优先级大于第2个面
		  A[0][1]=-1:表示第1个面的优先级小于第2个面
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
	return 0;
}
#endif