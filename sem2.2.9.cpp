#include <iostream>
#include <fstream>
using namespace std;

int T[12] = { 1, 0, 1, 1 };

void intToBin(int x) {
	for (int i = 11; i >= 0; i--) {
		T[i] = x % 2;
		x /= 2;
	}
}

void transformT() {
	int t = 0;
	int st2 = 1;
	for (int i = 1; i <= 12; i++) {
		t += T[i - 1] * st2;
		st2 *= 2;
	}
	intToBin((7 * t + 11) % 4087);
}

struct Point {
	double x = 0, y = 0;
};

Point transformToLocal(Point x) {
	return {x.x*5, x.y*5};
}

struct Plot {
	bool** oblast;
	Plot() {
		oblast = new bool* [21];
		for (int i = 0; i < 21; i++) {
			oblast[i] = new bool[12];
			for (int r = 0; r < 12; r++) oblast[i][r] = true;
		}
	}
	~Plot() {
		for (int i = 0; i < 21; i++) {
			delete[] oblast[i];
		}
		delete[] oblast;
	}
} base;


//(x   + h, y), (x   + h, y−h), (x   + h, y + h),       (x−h, y), (x−h, y−h), (x−h, y   + h),  (x, y−h), (x, y   + h)

Point bp;
const double h = 0.2;

double f(Point x) {
	return 0.f;
}

void move(Point& p) {
	unsigned short int direction = T[1] * 4 + T[6] * 2 + T[9];
	double x = p.x, y = p.y;
	switch (direction) {
	case 0:
		p = { x + h, y };
		break;
	case 1:
		p = { x + h, y - h };
		break;
	case 2:
		p = { x + h, y + h };
		break;
	case 3:
		p = { x - h, y };
		break;
	case 4:
		p = { x - h, y - h };
		break;
	case 5:
		p = { x - h, y + h };
		break;
	case 6:
		p = { x, y - h };
		break;
	case 7:
		p = { x, y + h };
		break;
	}
	transformT();
}

/*
	короче видимо смысл в том, что я должен из какой то конкретной точки найти количество блужданий в точку (xi,yi) и найти значение f(xi,yi)
	а потом ещё нужно сделать так для каждой точки границы
	и нужно поделить на количество блужданий? в общем непонятно в обозначениях здесь всё

	нужно ещё возможно переделать способ хранения границы в массиве и для нормальной индексации создать массив с граничными точками, чтоб можно было по i обращаться
*/

int wander(Point a) {
	/*int phi = 0;
	while (base.oblast[int(transformToLocal(a).x)][int(transformToLocal(a).y)] == false) {
		move(a);
		phi++;
	}
	bp = a;
	return phi;*/
}

double u(Point a) {
	int phi = wander(a);
	double sum = 0;
}

int main() {
	int N;
	cout << "Количество блужданий N: ";
	cin >> N;
	for (int i = 1; i < 11; i++) {
		for (int j = i; j <= 20 - i; j++) base.oblast[j][i] = false;
	}
	cout << "\nКоординаты (x,y): ";
	Point x;
	cin >> x.x >> x.y;
	double resU = u(x);
}