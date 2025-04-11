#include <iostream>

// Функция для вычисления интеграла методом трапеций
double Trap(double a, double b, int Nx, double (*F)(double)) {
    // Шаг разбиения
    double h = (b - a) / Nx;

    // Начальное значение суммы с учётом F(a) и F(b)
    double sum = 0.5 * (F(a) + F(b));

    // Суммируем значения F(x) на промежуточных точках
    for (int i = 1; i < Nx; ++i) {
        double x_i = a + i * h;
        sum += F(x_i);
    }

    // Умножаем итоговую сумму на шаг сетки
    return sum * h;
}

// Пример :
double F1(double x) {
    return x * x;
}

int main() {
    double result = Trap(-1.0, 1.0, 1001, F1);
    std::cout << "Result: " << result << std::endl;

    return 0;
}
