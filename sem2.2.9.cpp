#include <iostream>
#include <fstream>
using namespace std;

const double h = 0.2;
int T[12] = { 1 };

void intToBin(int x) {
	cout << x << '\n';
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

void move(int) {
	return;
}

struct Plot {
	bool** oblast;
	Plot() {
		oblast = new bool* [2 / h + 1];
		for (int i = 0; i < 2 / h + 1; i++) {
			oblast[i] = new bool[4 / h + 1];
			for (int j = 0; j < 4 / h + 1; j++) oblast[i][j] = false;
		}
	}
	~Plot() {
		for (int i = 0; i < 2 / h + 1; i++) {
			delete[] oblast[i];
		}
		delete[] oblast;
	}
};

int main() {
	Plot base;
	for (int i = 0; i < 2 / h + 1; i++) {
		base.oblast[i][i] = true;
		base.oblast[i][int(4 / h) - i] = true;
	}
	for (int i = 0; i < 4 / h + 1; i++) {
		base.oblast[0][i] = true;
	}
	for (int i = 0; i < 2 / h + 1; i++) {
		for (int j = 0; j < 4 / h + 1; j++) {
			cout << base.oblast[i][j];
		} cout << endl;
	}
}