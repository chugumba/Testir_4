#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

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

    if (p.x <= 0 && p.y <=0)
    {
        return true;
    }
    else
        return false; 
}
//Вычисляет периметр фигуры
double perimetr(vector<Point> points)
{
    double per = 0;
    if (points.size() == 5) {
        
        // Суммируем расстояния между соседними вершинами и замыкающими вершинами
        per = 0;
        for (int i = 0; i < 5; i++) {
            per += distance(points[i], points[(i + 1) % 5]);
        }
        return per; // Возвращаем периметр
    }
    else if(points.size() == 4) {
        // Суммируем расстояния между соседними вершинами и замыкающими вершинами
        per = 0;
        for (int i = 0; i < 4; i++) {
            per += distance(points[i], points[(i + 1) % 4]);
        }
        return per; // Возвращаем периметр
    }
    else if(points.size() == 3) {
        per = 0;
        for (int i = 0; i < 3; i++) {
            per += distance(points[i], points[(i + 1) % 3]);
        }
        return per;
    }
    else {
        cout << "Такой фигуры не существует " << endl;
        return -1;
    }

}
//Вычисляет площадь фигуры
double area(vector<Point> points) 
{
    double ar;
    double herons;
    double herons2;
    double herons3;
    if (points.size() == 5) {
        // Применяем формулу Гаусса к координатам вершин
        ar = 0;
       
        herons = heron(distance(points[0], points[1]), distance(points[0], points[2]), distance(points[1], points[2]));
        herons2 = heron(distance(points[0], points[2]), distance(points[0], points[3]), distance(points[2], points[3]));
        herons3 = heron(distance(points[0], points[3]), distance(points[0], points[4]), distance(points[3], points[4]));

        ar += herons + herons2 + herons3;
        
        return ar; // Возвращаем площадь
    }
    else if (points.size() == 4) {
        // Применяем формулу Гаусса к координатам вершин

        ar = 0;

        herons = heron(distance(points[0], points[1]), distance(points[0], points[2]), distance(points[1], points[2]));
        herons2 = heron(distance(points[0], points[2]), distance(points[0], points[3]), distance(points[2], points[3]));

        ar += herons + herons2;
        
        return ar; // Возвращаем площадь
    }
    else if (points.size() == 3) {
        ar = heron(distance(points[0], points[1]), distance(points[0], points[2]), distance(points[1], points[2]));;
            return ar;
    }
    else {
        cout << "Такой фигуры не существует " << endl;
        return -1;
    }

}
// Перегружаем операторы == и < для сравнения точек по координатам
bool operator==(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}

bool operator<(const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
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

    vector<Point> orig_points{A,B,C};

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

    Point min_orig = A;

    for (int i = 0; i < 3; i++) {

        if (isNegative(orig_points[i]) && orig_points[i].x <= min_orig.x) {

                min_orig = orig_points[i];
            
        }
        else if (isNegative(orig_points[i]) && (min_orig.x == orig_points[i].x && orig_points[i].y > min_orig.y) && orig_points[i].y < 0) {

                min_orig = orig_points[i];
        }
    }

    negative_points.push_back(min_orig);

    for (int i = 0; i < 3; i++) {

        if ((orig_points[i].y <= 0 && orig_points[i].x <= 0) && !(min_orig == orig_points[i])){

            negative_points.push_back(orig_points[i]);

        }
    }

    // Добавляем точки с координатами вида (0, Y) от наименьшего Y к наибольшему
        if (points[1].y > points[3].y) {

            min_orig = points[1];
            points[1] = points[3];
            points[3] = min_orig;
        
        }
        if (points[3].y > points[5].y) {

            min_orig = points[3];
            points[3] = points[5];
            points[5] = min_orig;
        }
        if (points[1].y > points[5].y) {

            min_orig = points[1];
            points[1] = points[5];
            points[5] = min_orig;
        }

        for (int i = 1; i <= 5; i += 2) {

            if(isNegative(points[i]) && find(negative_points.begin(), negative_points.end(), points[i]) == negative_points.end()) negative_points.push_back(points[i]);
        }

        if (x_plus && y_plus)
        {
            negative_points.push_back({ 0,0 });
        }
    // Добавляем точки с координатами вида (X, 0) от наибольшего X к наименьшему
        if (points[0].x < points[2].x) {

            min_orig = points[0];
            points[0] = points[2];
            points[2] = min_orig;

        }
        if (points[2].x < points[4].x) {

            min_orig = points[2];
            points[2] = points[4];
            points[4] = min_orig;
        }
        if (points[0].x < points[4].x) {

            min_orig = points[0];
            points[0] = points[4];
            points[4] = min_orig;
        }

        for (int i = 0; i <= 4; i += 2) {
            if (isNegative(points[i]) && find(negative_points.begin(), negative_points.end(), points[i]) == negative_points.end()) negative_points.push_back(points[i]);
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