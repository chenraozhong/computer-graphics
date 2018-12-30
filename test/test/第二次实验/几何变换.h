#pragma once
#include<iostream>
#include<graphics.h>
#include<math.h>
using namespace std;

#define pi 3.14
class Transformation {
public:
	void test();//测试函数
	void test_rocate();//测试旋转
	void test_sym();//测试对称变换
	void test_scaling();//测试缩放变换
	void scaling_trans(int a[15][2],float x0,float y0,float size);//进行缩放变换
	void rocate_trans(int a[14][2], float x0, float y0,float det);//进行旋转变换
	void sym(int a[14][2], float y_standard);//进行对称变换
};

//矩阵相乘，结果放在第一个矩阵当中
void array_mul(float a[3][3], float b[3][3]) {
	for (int i = 0; i < 3; i++) {
		int buff = 0;
		float sum[3];
		for (int j = 0; j < 3; j++)
		{
			sum[buff] = 0;
			for (int p = 0; p < 3; p++)
				sum[buff] += a[i][p] * b[p][j];
			buff++;
		}
		for (int p = 0; p < 3; p++)
			a[i][p] = sum[p];
	}
}

void Transformation::test() {
	int i;
	cout << endl << "请输入测试编码：" << endl;
	cout << "1.测试缩放变换" << endl << "2.测试旋转变换" << endl << "3.对称变换"<<endl<<"4.退出" << endl;
	cin >> i;
	while (i == 1 || i == 2||i==3) {
		if (i == 1) test_scaling();
		else if (i == 2) test_rocate();
		else if (i == 3) test_sym();
		cout << endl << "请输入测试编码：" << endl;
		cout << "1.测试缩放变换" << endl << "2.测试旋转变换" << endl << "3.对称变换" << endl << "4.退出" << endl;
		cin >> i;
	}
}

void get_trans(float a[3][3], float b[3][3], float c[3][3], float d[3][3]) {
	array_mul(b, d);
	array_mul(b, c);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			a[i][j] = b[i][j];
}

void Transformation::rocate_trans(int a[14][2], float x0, float y0,float det) {
	float trans1[3][3] = { { 1,0,0 },{ 0,1,0 },{ -x0,-y0,1 } };
	float trans2[3][3] = { { 1,0,0 },{ 0,1,0 },{ x0,y0,1 } };
	float trans3[3][3] = { { (float)cos(det*pi/180),(float)sin(det*pi/180),0 },{ (float)-sin(det*pi/180),(float)cos(det*pi/180),0 },{ 0,0,1 } };
	float trans[3][3];
	get_trans(trans, trans1, trans2, trans3);
	for (int i = 0; i < 3; i++)
	{
		cout << endl;
			for (int j = 0; j < 3; j++)
				cout << trans[i][j]<<"    ";
	}

	float aa[14][2];
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 2; j++) {
			aa[i][j] = 0;
			int p;
			for (p = 0; p < 2; p++)
			{
				aa[i][j] += a[i][p] * trans[j][p];
			}
			aa[i][j] += 1 * trans[p][j];
		}
	}
	for (int i = 0; i < 14; i++)
		cout << aa[i][0] << "  " << aa[i][0] << endl;

	for (int i = 0; i < 13; i++)
	{
		getchar();
		line(int(aa[i][0]), int(aa[i][1]), int(aa[i + 1][0]), int(aa[i + 1][1]));
	}
	line(int(aa[13][0]), int(aa[13][1]), int(aa[0][0]), int(aa[0][1]));
}

void Transformation::scaling_trans(int a[15][2],float x0,float y0,float size) {
	float trans1[3][3] = { {1,0,0},{0,1,0},{-x0,-y0,1} };
	float trans2[3][3]= { { 1,0,0 },{ 0,1,0 },{ x0,y0,1 } };
	float trans3[3][3]= { { size,0,0 },{ 0,size,0 },{0,0,1 } };
	float trans[3][3];
	get_trans(trans, trans1, trans2, trans3);
	float aa[15][2];
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 2; j++) {
			aa[i][j] = 0;
			int p;
			for (p = 0; p < 2; p++)
			{
				aa[i][j] += a[i][p] * trans[j][p];
			}
			aa[i][j] += 1 * trans[p][j];
		}
	}
	for (int i = 0; i < 14; i++)
	{
		getchar();
		line(int(aa[i][0]), int(aa[i][1]), int(aa[i + 1][0]), int(aa[i + 1][1]));
	}
	line(int(aa[14][0]), int(aa[14][1]), int(aa[0][0]), int(aa[0][1]));
}

void Transformation::sym(int a[14][2], float y_standard) {
	float trans[3][3] = { { 1,0,0 },{ 0,1,0 },{ 0,-y_standard,1 } };
	float b[3][3] = { { 1,0,0 },{ 0,-1,0 },{ 0,0,1 } };
	float c[3][3] = { { 1,0,0 },{ 0,1,0 },{ 0,y_standard,1 } };

	array_mul(trans, b);
	array_mul(trans, c);

	for (int i = 0; i < 3; i++) {
		cout << endl;
		for (int j = 0; j < 3; j++)
			cout << trans[i][j] << "  ";
	}

	float aa[14][2];
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 2; j++) {
			aa[i][j] = 0;
			int p;
			for (p = 0; p < 2; p++)
			{
				aa[i][j] += a[i][p] * trans[j][p];
			}
			aa[i][j] += 1 * trans[p][j];
		}
	}

	setcolor(RED);
	for (int i = 0; i < 13; i++)
	{
		getchar();
		line(int(aa[i][0]), int(aa[i][1]), int(aa[i + 1][0]), int(aa[i + 1][1]));
	}
	line(int(aa[13][0]), int(aa[13][1]), int(aa[0][0]), int(aa[0][1]));
}

void Transformation::test_scaling() {
	int a[15][2] = { { 110,65 },{ 100,70 },{ 80,70 },{ 50,110 },{ 65,70 },{ 45,70 },{ 25,90 },{ 35,65 },{ 25,40 },{ 45,60 },{ 65,60 },{50,20},{80,60},{100,60},{100,60} };
	int gdrive = DETECT, gmode;
	float size;
	float x0, y0;
	cout << "请输入缩放的参考点:";
	cin >> x0 >> y0;
	cout << "请输入缩放的比例:";
	cin >> size;
	initgraph(&gdrive, &gmode, "");
	setcolor(GREEN);
	for (int i = 0; i < 14; i++)
	{
		line(a[i][0], a[i][1], a[i + 1][0], a[i + 1][1]);
	}
	line(a[14][0], a[14][1], a[0][0], a[0][1]);
	setcolor(RED);
	scaling_trans(a, x0, y0, size);
	getchar();
	closegraph();
}

void Transformation::test_rocate() {
	int a[14][2] = { { 210,165 },{ 200,170 },{ 180,170 },{ 150,210 },{ 165,170 },{ 145,170 },{ 125,190 },{ 135,165 },{ 125,140 },{ 145,160 },{ 165,160 },{ 150,120 },{ 180,160 },{ 200,160 }};
	int gdrive = DETECT, gmode;
	
	float det;
	float x0, y0;
	cout << "请输入旋转中心:";
	cin >> x0 >> y0;
	cout << "请输入旋转角度:";
	cin >> det;
	initgraph(&gdrive, &gmode, "");
	setcolor(GREEN);
	for (int i = 0; i < 13; i++)
	{
		line(a[i][0], a[i][1], a[i + 1][0], a[i + 1][1]);
	}
	line(a[13][0], a[13][1], a[0][0], a[0][1]);
	setcolor(RED);
	rocate_trans(a, x0, y0, det);
	getchar();
	closegraph();
	
}

void Transformation::test_sym() {
	int a[14][2] = { { 110,65 },{ 100,70 },{ 80,70 },{ 50,110 },{ 65,70 },{ 45,70 },{ 25,90 },{ 35,65 },{ 25,40 },{ 45,60 },{ 65,60 },{ 50,20 },{ 80,60 },{ 100,60 } };
	float y_standard;
	cout << "请输入水平线的y坐标:" << endl;
	cin >> y_standard;
	int gdrive = DETECT, gmode;
	initgraph(&gdrive, &gmode, "");
	setcolor(GREEN);
	for (int i = 0; i < 13; i++)
	{
		line(a[i][0], a[i][1], a[i + 1][0], a[i + 1][1]);
	}
	line(a[13][0], a[13][1], a[0][0], a[0][1]);
	setcolor(BLUE);
	line(0, (int)y_standard, 800, (int)y_standard);
	sym(a, y_standard);
	getchar();
	getchar();
	closegraph();
}