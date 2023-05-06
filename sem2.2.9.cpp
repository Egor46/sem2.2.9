#include <iostream>
#include <fstream>
using namespace std;

int N;

int T[12] = { 0 };

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

struct iPoint {
	int x = 0, y = 0;
};

iPoint transformI(Point x) {
	return { int(x.x * 10), int(x.y * 10) };
}

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

const double h = 0.2;

double f(Point x) {
	return x.x + x.y;
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

//void test(Point& p) {
//	system("cls");
//	cout << "Совершено блуждание из точки " << p.x << ' ' << p.y << " в точку ";
//	move(p);
//	cout << p.x << ' ' << p.y << '\n';
//	cout << "Массив направлений T: ";
//	for (int i : T) cout << i << ' ';
//	cout << '\n' << "В том числе определяющие элементы " << T[1] << ' ' << T[6] << ' ' << T[9] << endl;
//	system("pause");
//}

Point wander(Point a) {
	iPoint temp = transformI(a);
	do {
		move(a);
		temp = transformI(a);
	} while ((temp.y < -(abs(temp.x - 20)) + 20) && temp.y > 0);
	//cout << "Была достигнута граница в точке (" << a.x << ' ' << a.y << ")\n";
	//system("pause");
	return a;
}

double u(Point a) {
	iPoint temp = transformI(a);
	if ((temp.y >= -(abs(temp.x - 20)) + 20) || temp.y <= 0) {
		return (temp.y > -(abs(temp.x - 20)) + 20 || temp.y < 0) ? 0 : f(a);
	}
	double sum = 0;
	for (int i = 0; i < N; i++) sum += f(wander(a));
	return sum / N;
}

int main() {
	Point p;
	setlocale(LC_ALL, "rus");
	cout << "Введите количество блужданий: "; cin >> N;
	if (N <= 0) { cout << "Неправильный ввод"; return 1; }
	intToBin(N % 4096);
	cout << "Введите точку (x*,y*): "; cin >> p.x >> p.y;
	cout << "Результат: " << u(p);
}