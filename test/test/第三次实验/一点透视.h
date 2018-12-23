#include "stdafx.h"
#include<iostream>
#include<graphics.h>
using namespace std;
#if one_point
int main()
{
	float m, n, l, d;
	l = 8;
	m = 16;
	n = 20;
	d = 50;
	float a[4][4] = { { 1,0,0,0 },{ 0,1,0,0 },{ 0,0,0,1 / d },{ l,m,0,1 + n / d } };

	int x_x = 50, y_y = 50;
	int p[8][4] = { { 0,0,0,1 },{ 100,0,0,1 },{ 100,100,0,1 },{ 0,100,0,1 },{ 0,0,100,1 },{ 100,0,100,1 },{ 100,100,100,1 },{ 0,100,100,1 } };


	float aa[8][4];
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++) {
			aa[i][j] = 0;
			int pp;
			for (pp = 0; pp < 4; pp++)
			{
				float xxx = p[i][pp];
				float yyy = a[pp][j];
				aa[i][j] += xxx*yyy;
			}
		}
	}

	for (int i = 0; i < 8; i++) {
		aa[i][0] = aa[i][0] / aa[i][3];
		aa[i][1] = aa[i][1] / aa[i][3];
		aa[i][2] = aa[i][2] / aa[i][3];
	}


	for (int i = 0; i < 8; i++) {
		cout << endl;
		for (int j = 0; j < 4; j++)
			cout << aa[i][j] << "  ";
	}
	int gdrive = DETECT, gmode;
	initgraph(&gdrive, &gmode, "");
	
	setcolor(GREEN);

	line((int)(aa[0][0] + 0.5), (int)(aa[0][1] + 0.5), (int)(aa[1][0] + 0.5), (int)(aa[1][1] + 0.5));//AB
	line((int)(aa[0][0] + 0.5), (int)(aa[0][1] + 0.5), (int)(aa[4][0] + 0.5), (int)(aa[4][1] + 0.5));//AE
	line((int)(aa[0][0] + 0.5), (int)(aa[0][1] + 0.5), (int)(aa[3][0] + 0.5), (int)(aa[3][1] + 0.5));//AD
	line((int)(aa[3][0] + 0.5), (int)(aa[3][1] + 0.5), (int)(aa[2][0] + 0.5), (int)(aa[2][1] + 0.5));//DC
	line((int)(aa[3][0] + 0.5), (int)(aa[3][1] + 0.5), (int)(aa[7][0] + 0.5), (int)(aa[7][1] + 0.5));//DH
	line((int)(aa[6][0] + 0.5), (int)(aa[6][1] + 0.5), (int)(aa[7][0] + 0.5), (int)(aa[7][1] + 0.5));//GH
	line((int)(aa[6][0] + 0.5), (int)(aa[6][1] + 0.5), (int)(aa[2][0] + 0.5), (int)(aa[2][1] + 0.5));//GC
	line((int)(aa[6][0] + 0.5), (int)(aa[6][1] + 0.5), (int)(aa[5][0] + 0.5), (int)(aa[5][1] + 0.5));//GF
	line((int)(aa[1][0] + 0.5), (int)(aa[1][1] + 0.5), (int)(aa[5][0] + 0.5), (int)(aa[5][1] + 0.5));//BF
	line((int)(aa[4][0] + 0.5), (int)(aa[4][1] + 0.5), (int)(aa[5][0] + 0.5), (int)(aa[5][1] + 0.5));//EF
	line((int)(aa[4][0] + 0.5), (int)(aa[4][1] + 0.5), (int)(aa[7][0] + 0.5), (int)(aa[7][1] + 0.5));//EH
	line((int)(aa[1][0] + 0.5), (int)(aa[1][1] + 0.5), (int)(aa[2][0] + 0.5), (int)(aa[2][1] + 0.5));//BC

	getchar();
	getchar();
	closegraph();
	return 0;
}
#endif