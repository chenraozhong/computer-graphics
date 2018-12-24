
#include "stdafx.h"
#include<iostream>
#include<graphics.h>
#include<time.h>
#include<map>
using namespace std;

#if 0
int main()
{
	map<int, int> e;
	e[1] = 0;
	e[2] = 8;
	e[3] = 4;
	map<int, int>::iterator item;

	item = e.lower_bound(2);
	cout <<item->second << endl;
	return 0;
}
#endif