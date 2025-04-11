#include <iostream>
using namespace std;


// Функция для нахождения корня методом Ньютона
double Newton(double x0, double (*F)(double), double (*dF)(double), double eps) {

    //Если мы попали в корень, выводит ответ.
    if (0 == F(x0)) return x0;

    double x = x0; // Присваиваем x = x0.

    // Пока не достигли нужной точности, используем формулу.
    while (abs(F(x)) > eps) {
        x = x - F(x) / dF(x);
    }

    return x;
}

// Пример 1.
double F1(double x) {
    return x * x - 2;
}
double dF1(double x) {
    return 2 * x;
}


//Пример 2.
double F2(double x) {
    return x - 2;
}
double dF2(double x) {
    return 1;
}


int main()
{
    // Пример 1.
    double root_1 = Newton(1.0, F1, dF1, 1e-8);
    std::cout << "Root 1: " << root_1 << std::endl;

    // Пример 2.
    double root_2 = Newton(1.0, F2, dF2, 1e-8);
    std::cout << "Root 2: " << root_2 << std::endl;
    return 0;
}
