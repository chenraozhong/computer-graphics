// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include<graphics.h>
using namespace std;


int main()
{	
	int gdrive = DETECT, gmode;
	initgraph(&gdrive, &gmode, "");
	line(0, 0, 100, 100);
	getchar();
	closegraph();
	cout << "hello world" << endl;
    return 0;
}

