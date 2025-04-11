#include <iostream>

// Функция для вычисления интеграла методом средних прямоугольников
double MiddleRect(double a, double b, int Nx, double (*F)(double)) {
    // Шаг разбиения
    double delta_x = (b - a) / Nx;
    double sum = 0.0;

    // Суммируем значения функции в серединах подынтервалов
    for (int i = 0; i < Nx; ++i) {
        double x_i = a + i * delta_x;       // Левая граница i-го подынтервала
        double mid = x_i + delta_x / 2.0;   // Середина i-го подынтервала
        sum += F(mid);
    }

    // Умножаем на шаг сетки
    return sum * delta_x;
}

// Пример:
double F1(double x) {
    return x * x;
}

int main() {
    double result = MiddleRect(-1.0, 1.0, 1001, F1);
    std::cout << "Result: " << result << std::endl;

    return 0;
}
