#include "stdafx.h"
#include<iostream>
#include<graphics.h>
#include<time.h>
#include<math.h>
using namespace std;

#if 0
int main()
{
	float m, n, l, d;
	float det = (30.0 / 180.0)*3.14;//½Ç¶È
	float p1 = -0.1, q = 0, r = -0.45;
	float arf = acos(2) / asin(2);
	float bet = (30.0 / 180.0)*3.14;
	float a3[4][4] = { { 1,0,0,0 },{ 0,1,0,0 },{ (1.0 / 2.0)* (float)cos(bet),(1.0 / 2.0) * (float)sin(bet),0,0 },{ 0,0,0,1 } };

	for (int i = 0; i < 4; i++) {
		cout << endl;
		for (int j = 0; j < 4; j++)
			cout << a3[i][j] << " ";
	}


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
				float yyy = a3[pp][j];
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

	line((int)(aa[0][0] + 0.5 + 100), (int)(aa[0][1] + 0.5 + 100), (int)(aa[1][0] + 0.5 + 100), (int)(aa[1][1] + 0.5 + 100));//AB
	line((int)(aa[0][0] + 0.5 + 100), (int)(aa[0][1] + 0.5 + 100), (int)(aa[4][0] + 0.5 + 100), (int)(aa[4][1] + 0.5 + 100));//AE
	line((int)(aa[0][0] + 0.5 + 100), (int)(aa[0][1] + 0.5 + 100), (int)(aa[3][0] + 0.5 + 100), (int)(aa[3][1] + 0.5 + 100));//AD
	line((int)(aa[3][0] + 0.5 + 100), (int)(aa[3][1] + 0.5 + 100), (int)(aa[2][0] + 0.5 + 100), (int)(aa[2][1] + 0.5 + 100));//DC
	line((int)(aa[3][0] + 0.5 + 100), (int)(aa[3][1] + 0.5 + 100), (int)(aa[7][0] + 0.5 + 100), (int)(aa[7][1] + 0.5 + 100));//DH
	line((int)(aa[6][0] + 0.5 + 100), (int)(aa[6][1] + 0.5 + 100), (int)(aa[7][0] + 0.5 + 100), (int)(aa[7][1] + 0.5 + 100));//GH
	line((int)(aa[6][0] + 0.5 + 100), (int)(aa[6][1] + 0.5 + 100), (int)(aa[2][0] + 0.5 + 100), (int)(aa[2][1] + 0.5 + 100));//GC
	line((int)(aa[6][0] + 0.5 + 100), (int)(aa[6][1] + 0.5 + 100), (int)(aa[5][0] + 0.5 + 100), (int)(aa[5][1] + 0.5 + 100));//GF
	line((int)(aa[1][0] + 0.5 + 100), (int)(aa[1][1] + 0.5 + 100), (int)(aa[5][0] + 0.5 + 100), (int)(aa[5][1] + 0.5 + 100));//BF
	line((int)(aa[4][0] + 0.5 + 100), (int)(aa[4][1] + 0.5 + 100), (int)(aa[5][0] + 0.5 + 100), (int)(aa[5][1] + 0.5 + 100));//EF
	line((int)(aa[4][0] + 0.5 + 100), (int)(aa[4][1] + 0.5 + 100), (int)(aa[7][0] + 0.5 + 100), (int)(aa[7][1] + 0.5 + 100));//EH
	line((int)(aa[1][0] + 0.5 + 100), (int)(aa[1][1] + 0.5 + 100), (int)(aa[2][0] + 0.5 + 100), (int)(aa[2][1] + 0.5 + 100));//BC

	getchar();
	getchar();
	closegraph();
	return 0;
}
#endif
