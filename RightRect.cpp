#include <iostream>
using namespace std;

// Функция для вычисления интеграла методом левых прямоугольников
double RightRect(double a, double b, int Nx, double (*F)(double)) {
    // Вычисляем шаг разбиения
    double delta_x = (b - a) / Nx;
    double sum = 0.0;

    // Суммируем значения функции в правых концах прямоугольников
    for (int i = 1; i <= Nx; ++i) {
        double x_i = a + i * delta_x;  // правая граница текущего интервала
        sum += F(x_i);
    }

    // Умножаем на шаг сетки.
    return sum * delta_x;
}

// Пример :
double F1(double x) {
    return x * x; 
}

int main() {
    double result = RightRect(-1, 1, 1001, F1);
    cout << "Result: " << result << endl;
    return 0;
}
