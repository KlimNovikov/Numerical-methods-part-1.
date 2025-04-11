#include <iostream>

// Функция для вычисления интеграла методом левых прямоугольников
double LeftRect(double a, double b, int Nx, double (*F)(double)) {
    // Вычисляем шаг разбиения
    double delta_x = (b - a) / Nx;
    double sum = 0.0;

    // Суммируем значения функции в левых концах прямоугольников
    for (int i = 0; i < Nx; ++i) {
        double x_i = a + i * delta_x;  // Левая граница текущего интервала
        sum += F(x_i); 
    }

    // Умножаем на шаг сетки
    return sum * delta_x;
}

// Пример :
double F1(double x) {
    return x * x;  
}

int main() {
    double result = LeftRect(-1, 1, 1001, F1);
    std::cout << "Result: " << result << std::endl;
    return 0;
}

