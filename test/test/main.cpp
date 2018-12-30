
#include "stdafx.h"
#include<iostream>
#include<graphics.h>
#include<time.h>
#include<map>
#include<math.h>
#include<Eigen/Dense>
using namespace std;
using namespace Eigen;

#if 1
int main()
{
	/*
	map<int, int> e;
	e[1] = 0;
	e[2] = 8;
	e[3] = 4;
	map<int, int>::iterator item;

	item = e.lower_bound(2);
	cout <<item->second << endl;
	*/
	MatrixXd a(1,2);
	a << 1.0,1.0;
	MatrixXd b(2, 1);
	b << sin(0), sin(3.14 / 4.0);
	cout << a*b << endl;
	return 0;
}
#endif