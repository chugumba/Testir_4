#include <iostream>
#include <cmath>

using namespace std;

struct Point {
	double x, y;
};

double distance(Point p1, Point p2) {

	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

double heron(double a, double b, double c) {
	double s = (a + b + c) / 2;
	return sqrt(s * (s - a) * (s - b) * (s - c));
}

int main() {
	Point a, b, c;
	

	setlocale(LC_ALL, "Russian");

	cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;

	//длины исходного треугольника
	double ab = distance(a,b), ac = distance(a,c), bc = distance(b,c);

	//периметр и площадь
	double per = ab + ac + bc, area = heron(ab, ac, bc);

	//Если в 3 квадранте нет точек
	if (a.x >= 0 && a.y >= 0 && b.x >= 0 && b.y >= 0 && c.x >= 0 && c.y >= 0) {
		cout << "В 3 квадранте нет точек" << endl;
		return 0;
	}

	//Если все точки в 3 квадранте
	if (a.x <= 0 && a.y <= 0 && b.x <= 0 && b.y <= 0 && c.x <= 0 && c.y <= 0){
		cout << "Периметр - " << per << endl << "Площадь - " << area;
	}

	return 0;

}
