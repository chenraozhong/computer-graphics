#include<graphics.h>
#include<iostream>
using namespace std;

#if 1
class Cohen {
private:
	int ywt, ywb, xwl, xwr;
	int x1, y1, x2, y2;
public:
	void test_tailor();
	void tailor(int a[8][2],int x0,int y0,int height,int width);
	void code(int code1[4],int x, int y);
	bool Or(int code1[4], int code2[4]);
	bool And(int code[4], int code2[4]);
	bool if_inside(int code1[4]);
	void get_point(int i);
	void test();
	void array_mul(float a[3][3], float b[3][3]);
};

void Cohen::test() {
	test_tailor();

}

void Cohen::get_point(int i) {
	int edge;
	int xx, yy;
	float k = (float)(y2 - y1) /(float) (x2 - x1);
	if (i == 0 || i == 1) {
		if (i == 0) edge = ywt;
		else edge = ywb;
		xx = (int)((float)(edge - y2)/k + x2+0.5);
		yy = edge;
		setcolor(BLACK);
		line(xx, yy, x1, y1);
		line(xx + 1, yy, x1 + 1, y1);
		line(xx - 1, yy, x1 - 1, y1);
		x1 = xx;
		y1 = yy;
	}
	else {
		if (i == 2) edge = xwr;
		else  edge = xwl;
		yy = (int)(k*(edge - x2) + y2+0.5);
		xx = edge;
		setcolor(BLACK);
		line(xx, yy, x1, y1);
		line(xx + 1, yy, x1 + 1, y1);
		line(xx - 1, yy, x1 - 1, y1);
		x1 = xx;
		y1 = yy;
	}
}

bool Cohen::if_inside(int code1[4]) {
	for (int i = 0; i < 4; i++) {
		if (code1[i] != 0) return false;
	}
	return true;
}

bool Cohen::And(int code1[4], int code2[4]) {
	for (int i = 0; i < 4; i++)
	{
		if (code1[i] * code2[i] != 0) return false;
	}
	return true;
}

bool Cohen::Or(int code1[4], int code2[4]) {
	for (int i = 0; i < 4; i++)
		if (code1[i] != 0 || code2[i] != 0) return false;
	return true;
}

void Cohen::code(int code1[4],int x,int y){
	if (y > ywt) {
		code1[0] = 1;
		code1[1] = 0;
	}
	else {
		if (y >= ywb) {
			code1[0] = 0;
			code1[1] = 0;
		}
		else {
			code1[0] = 0;
			code1[1] = 1;
		}
	}
	if (x > xwr) {
		code1[2] = 1;
		code1[3] = 0;
	}
	else {
		if (x >= xwl) {
			code1[2] = 0;
			code1[3] = 0;
		}
		else {
			code1[2] = 0;
			code1[3] = 1;
		}
	}
}

void Cohen::tailor(int a[8][2],int x0,int y0,int height,int width) {
	ywt = y0 + height;
	ywb = y0;
	xwl = x0;
	xwr = x0 + width;
	int code1[4];
	int code2[4];
	bool flag = true;
	for (int i = 0; i < 7; i += 1) {
		flag = true;
		x1 = a[i][0];
		y1 = a[i][1];
		x2 = a[i + 1][0];
		y2 = a[i + 1][1];
		while (flag) {
			code(code1, x1, y1);
			code(code2, x2, y2);
			if (Or(code1, code2)) {
				flag = false;
				continue;
			}
			else {
				if (!And(code1, code2)) {
					setcolor(BLACK);
					line(x1, y1, x2, y2);
					line(x1 + 1, y1, x2 + 1, y2);
					flag = false;
				}
				else {
					if (if_inside(code1)) {//判断头端点是否在矩形内部
						int buffx = x1;
						int buffy = y1;
						x1 = x2;
						y1 = y2;
						x2 = buffx;
						y2 = buffy;
						code(code1, x1, y1);
						code(code2, x2, y2);
					}
					int ii;
					for (ii = 0; ii < 4; ii++) {
						if (code1[ii] != 0) break;
					}
					get_point(ii);
					flag= true;
				}
			}
		}
	}
}

void Cohen::test_tailor() {
	int a[8][2] = { {50,300},{200,30},{250,90},{350,210},{200,250},{400,350},{230,450},{330,350} };
	int width, height, x0, y0;
	cout << "请输入矩形的长和宽:" << endl;
	cin >> width >> height;
	cout << "请输入矩形的起始位置:" << endl;
	cin >> x0 >> y0;
	int gdrive = DETECT, gmode;
	initgraph(&gdrive, &gmode, "");
	setcolor(GREEN);
	for (int i = 0; i < 7; i += 1) {
		line(a[i][0], a[i][1], a[i + 1][0], a[i + 1][1]);
	}
	setcolor(BLUE);
	line(x0, y0, x0 + width, y0 );
	line(x0, y0, x0, y0 + height);
	line(x0+width, y0+height, x0 + width, y0);
	line(x0 + width, y0 + height, x0, y0 + height);
	getchar();
	getchar();
	tailor(a,x0, y0, height, width);
	getchar();
	getchar();
	closegraph();
}

void Cohen::array_mul(float a[3][3], float b[3][3]) {
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

int main() {
	Cohen c;
	c.test();
	return 0;
}
#endif 

