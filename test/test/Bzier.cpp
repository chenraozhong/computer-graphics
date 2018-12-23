// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "stdafx.cpp"
#include <graphics.h>
#include<iostream>
#include<vector>

using namespace std;
#if 0

int qiujie(int n) {
	int sum = 1;
	for (int i = 1; i <= n; i++)
		sum = sum*i;
	return sum;
}

float zhishu(float x, float n)//x的n次方
{
	if (n == 0) return 1.0;
	if (x == 0) return 0.0;
	float sum = 1.0;
	for (int i = 0; i < n; i++)
		sum = sum*x;
	return sum;
}

float BEN(int k, int n, float t) {
	float sum;
	sum = ((float)(qiujie(n)) / (float)(qiujie(k)*qiujie(n - k)))*(zhishu(t, k)*zhishu(1 - t, n - k));
	return sum;
}

int main()
{
	int n;
	cout << "请输入控制点的个数" << endl;
	cin >> n;
	cout << "请输入各控制点的坐标:" << endl;
	vector<int> pointx;
	vector<int> pointy;
	for (int i = 0; i < n; i++)
	{
		int buff;
		cin >> buff;
		pointx.push_back(buff);
		cin >> buff;
		pointy.push_back(buff);
	}

	int gdrive = DETECT, gmode;
	initgraph(&gdrive, &gmode, "");
	setcolor(RED);
	for (int i = 0; i < n - 1; i++) {
		line(pointx[i], pointy[i], pointx[i + 1], pointy[i + 1]);
	}

	for (float i = 0; i <= 1.0; i += 0.01)
	{
		float x = 0;
		float y = 0;
		for (int j = 0; j < n; j++)
		{
			x += pointx[j] * BEN(j, n - 1, i);
			y += pointy[j] * BEN(j, n - 1, i);
		}
		putpixel((int)(x + 0.5), (int)(y + 0.5), GREEN);
	}
	getchar();
	getchar();
	closegraph();

	return 0;
}
#endif
