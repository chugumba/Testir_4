#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int quad_vert = 0;
// Структура для хранения координат точки
struct Point {
    double x, y;
};

double heron(double a, double b, double c) {
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

// Функция для нахождения расстояния между двумя точками
double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Функция для проверки, лежит ли точка на отрезке
bool onSegment(Point p, Point p1, Point p2) {
    // Сравниваем расстояния с некоторой малой погрешностью
    double eps = 1e-6;
    return abs(distance(p, p1) + distance(p, p2) - distance(p1, p2)) < eps;
}

// Функция для нахождения точки пересечения прямой, проходящей через две точки, с осью OX
Point intersectX(Point p1, Point p2) {
    Point res;
    // Если прямая параллельна оси OX, то возвращаем точку с координатами (nan, nan)
    if (p1.y == p2.y) {
        res.x = nan("");
        res.y = nan("");
    }
    else {
        // Иначе находим параметр t, при котором y = 0
        double t = -p1.y / (p2.y - p1.y);
        // Подставляем t в уравнение прямой и находим x
        res.x = p1.x + t * (p2.x - p1.x);
        res.y = 0;
        // Если точка не лежит на отрезке, то возвращаем точку с координатами (nan, nan)
        if (!onSegment(res, p1, p2)) {
            res.x = nan("");
            res.y = nan("");
        }
    }
    return res;
}

// Функция для нахождения точки пересечения прямой, проходящей через две точки, с осью OY
Point intersectY(Point p1, Point p2) {
    Point res;
    // Если прямая параллельна оси OY, то возвращаем точку с координатами (nan, nan)
    if (p1.x == p2.x) {
        res.x = nan("");
        res.y = nan("");
    }
    else {
        // Иначе находим параметр t, при котором x = 0
        double t = -p1.x / (p2.x - p1.x);
        // Подставляем t в уравнение прямой и находим y
        res.y = p1.y + t * (p2.y - p1.y);
        res.x = 0;
        // Если точка не лежит на отрезке, то возвращаем точку с координатами (nan, nan)
        if (!onSegment(res, p1, p2)) {
            res.x = nan("");
            res.y = nan("");
        }
    }
    return res;
}
//Проверка + ли X
bool is_positive_X(Point p, bool a)
{
    if (p.x >= 0)
    {
        return true;
    }
    else return a;
}
//Проверка + ли Y
bool is_positive_Y(Point p, bool a)
{
    if (p.y >= 0)
    {
        return true;
    }
    else return a;
}

// Функция для вывода координат точки на экран
void printPoint(Point p) {

    if (!isnan(p.x) && !isnan(p.y))
        cout << "(" << p.x << ", " << p.y << ")";
}

// Функция для проверки, является ли точка отрицательной по обеим координатам
bool isNegative(Point p) {

    if (p.x <= 0 && p.y <= 0)
    {
        return true;
    }
    else
        return false; 
}

double perimetr(vector<Point> points)
{
    double per = 0;
    if (points.size() == 5) {
        
        // Суммируем расстояния между соседними вершинами и замыкающими вершинами
        double per = 0;
        for (int i = 0; i < 5; i++) {
            per += distance(points[i], points[(i + 1) % 5]);
        }
        return per; // Возвращаем периметр
    }
    else if(points.size() == 4) {
        // Суммируем расстояния между соседними вершинами и замыкающими вершинами
        double per = 0;
        for (int i = 0; i < 4; i++) {
            per += distance(points[i], points[(i + 1) % 4]);
        }
        return per; // Возвращаем периметр
    }
    else {
        return -1;
    }

}

double area(vector<Point> points)
{
    double ar;
    if (points.size() == 5) {
        // Применяем формулу Гаусса к координатам вершин
        ar = 0;
        for (int i = 0; i < 5; i++) {
            ar += points[i].x * points[(i + 1) % 5].y - points[i].y * points[(i + 1) % 5].x;
        }
        ar = abs(ar) / 2; // Берем модуль и делим на два
        return ar; // Возвращаем площадь
    }
    else if (points.size() == 4) {
        // Применяем формулу Гаусса к координатам вершин
        ar = 0;
        for (int i = 0; i < 4; i++) {
            ar += points[i].x * points[(i + 1) % 4].y - points[i].y * points[(i + 1) % 4].x;
        }
        ar = abs(ar) / 2; // Берем модуль и делим на два
        return ar; // Возвращаем площадь
    }
    else {
        return -1;
    }

}

int main() {

    bool x_plus = false, y_plus = false;

    setlocale(LC_ALL, "Russian");


    double ax, ay, bx, by, cx, cy;

    cout << "Координаты 1 точки" << endl;
    cin >> ax >> ay;
    cout << "Координаты 2 точки" << endl;
    cin >> bx >> by;
    cout << "Координаты 3 точки" << endl;
    cin >> cx >> cy;

    if ((ax == bx && ay == by) || (ax == cx && ay == cy) || (bx == cx && by == cy)) {

        cout << "2 или более точек совпадают, ввод некорректный";
        return 0;

    }

    // Задаем координаты вершин треугольника
    Point A = { ax, ay };
    Point B = { bx, by };
    Point C = { cx, cy };

    double orig_per = distance(A,C) + distance(A,B) + distance(B,C);
    double orig_area = heron(distance(A, C), distance(A, B), distance(B, C));

    //Если в 3 квадранте нет точек
    if (A.x > 0 && A.y > 0 && B.x > 0 && B.y > 0 && C.x > 0 && C.y > 0) {
        cout << "В 3 квадранте нет точек" << endl;
        return 0;
    }

    //Если все точки в 3 квадранте
    if (A.x <= 0 && A.y <= 0 && B.x <= 0 && B.y <= 0 && C.x <= 0 && C.y <= 0) {
        cout << "Периметр - " << orig_per << endl << "Площадь - " << orig_area;
        return 0;
    }

    // Находим точки пересечения сторон треугольника с осями координат
    Point AB_X = intersectX(A, B); // Точка пересечения стороны AB с осью OX
    x_plus = is_positive_X(AB_X, x_plus);
    Point AB_Y = intersectY(A, B); // Точка пересечения стороны AB с осью OY
    y_plus = is_positive_Y(AB_Y, y_plus);
    Point BC_X = intersectX(B, C); // Точка пересечения стороны BC с осью OX
    x_plus = is_positive_X(BC_X, x_plus);
    Point BC_Y = intersectY(B, C); // Точка пересечения стороны BC с осью OY
    y_plus = is_positive_Y(BC_Y, y_plus);
    Point CA_X = intersectX(C, A); // Точка пересечения стороны CA с осью OX
    x_plus =  is_positive_X(CA_X, x_plus);
    Point CA_Y = intersectY(C, A); // Точка пересечения стороны CA с осью OY
    y_plus = is_positive_Y(CA_Y, y_plus);
    Point Zero = {0, 0};
    // Собираем все точки пересечения в один список
    vector<Point> points = { AB_X, AB_Y, BC_X, BC_Y, CA_X, CA_Y };

    // Создаем вектор для хранения точек пересечения, лежащих на отрицательных координатах
    vector<Point> negative_points;

    // Перебираем все точки и проверяем, являются ли они отрицательными по обеим координатам
    for (int i = 0; i < points.size(); i++) {

        if (isNegative(points[i])) {
                // Добавляем такую точку в вектор отрицательных точек
                negative_points.push_back(points[i]);
        }
    }

    if (isNegative(A))
    {
        negative_points.push_back(A);
    }

    if (isNegative(B))
    {
        negative_points.push_back(B);
    }

    if (isNegative(C))
    {
        negative_points.push_back(C);
    }

    if (x_plus && y_plus)
    {
        negative_points.push_back({0,0});
    }
    // Выводим результаты на экран
    cout << "Точки пересечения, лежащие на отрицательных координатах:\n";

    if (negative_points.empty()) {
        cout << "Таких точек нет.\n";
    }
    else {
        for (Point p : negative_points) {
            printPoint(p);
            cout << "\n";
        }
    }

    double per = perimetr(negative_points);
    double ar = area(negative_points);

    cout << "Периметр фигуры в 3 квадранте: " << per << endl << "Площадь фигуры в 3 квадранте: " << ar << endl;

    return 0;
}