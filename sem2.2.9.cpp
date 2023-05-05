#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

// короче надо сделать N попыток из (x*,y*), и каждый раз когда мы приходим в точку (xi,yi) границы мы типа
// суммируем значение f в этой точке границы и так N раз
// цель: переделать систему определения границы, потому что пока что это такое себе, можно лучше,
// причём есть вероятность попасть в неграничную точку, но тогда мы выберем точку, ближайшую к этой
//
// среди идей сделать чтобы wander возвращала точку прихода, чтобы потом передать её в f

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
	float x = 0, y = 0;
};

Point transformToLocal(Point x) {
	return { x.x * 5, x.y * 5 };
}

int N;

//Point border[60];

//void generateBorder() {
//	for (int i = 0; i < 20; i += 2) {
//		border[i] = { i / 10.f, i / 10.f };
//		border[i + 1] = { i / 10.f, (i + 2) / 10.f };
//		border[20 + i] = { (20 + i) / 10.f, 4 - (20 + i) / 10.f };
//		border[20 + i + 1] = { (20 + i + 2) / 10.f, 4 - (20 + i) / 10.f };
//	}
//	for (int i = 40; i < 60; i++) {
//		border[i] = { 4 - (i - 40) / 5.f, 0 };
//	}
//}

//(x   + h, y), (x   + h, y−h), (x   + h, y + h),       (x−h, y), (x−h, y−h), (x−h, y   + h),  (x, y−h), (x, y   + h)

const float h = 0.2;

float f(Point x) {
	return 0.f;
}

void move(Point& p) {
	unsigned short int direction = T[1] * 4 + T[6] * 2 + T[9];
	float x = p.x, y = p.y;
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

void test(Point&);

Point wander(Point a) {
	do {
		test(a);
	} while ((a.y < -(abs(a.x-2)) + 2) && a.y > 0);
	cout << "Была достигнута граница в точке (" << a.x << ' ' << a.y <<')';
	system("pause");
	return a;
}

float u(Point a) {
	float sum = 0;
	for (int i = 0; i < N; i++) sum+= f(wander(a));
	return sum;
}

void test(Point& p) {
	//while (true) {
		system("cls");
		cout << "Совершено блуждание из точки " << p.x << ' ' << p.y << " в точку ";
		move(p);
		cout << p.x << ' ' << p.y << '\n';
		cout << "Массив направлений T: ";
		for (int i : T) cout << i << ' ';
		cout << '\n' << "В том числе определяющие элементы " << T[1] << ' ' << T[6] << ' ' << T[9] << endl;
		system("pause");
	//}
}

int main() {
	/*generateBorder();*/
	Point p;
	setlocale(LC_ALL, "rus");
	cout << "Введите количество блужданий: "; cin >> N;
	cout << "Введите точку (x*,y*): "; cin >> p.x >> p.y;
	p.x = round(p.x * 10) / 10;
	p.y = round(p.y * 10) / 10;
	cout << u(p);
	//cout << "Результат: " << u(p);
}