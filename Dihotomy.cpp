#include <iostream>
#include <cmath>

// Функция для нахождения корня на отрезке [a, b] методом дихотомии.
double Dihotomy(double a, double b, double (*F)(double), double eps) {
    // Пока длина отрезка больше заданной точности
    while ((b - a) / 2 > eps) {
        // Находим середину отрезка
        double c = (a + b) / 2;

        // Проверяем знак функции в середине отрезка
        if (F(c) == 0) {
            return c;  // Если F(c) == 0, то c — это корень
        }
        else if (F(a) * F(c) < 0) {
            // Корень лежит в левой половине отрезка
            b = c;
        }
        else {
            // Корень лежит в правой половине отрезка
            a = c;
        }

    }

    // Возвращаем середину отрезка как приближенное значение корня
    return (a + b) / 2;
}

// Пример функций для поиска корня
double F1(double x) {
    return x * x - 2;   // Пример: корень из 2
}

double F2(double x) {
    return x;           // Пример: 0           
}


double F3(double x) {
    return log10(x);    // Пример: 1
}



int main() {
    // Примеры.
    double root_1 = Dihotomy(-1, 1.5, F1, 1e-8);
    std::cout << "Root F1: " << root_1 << std::endl;

    double root_2 = Dihotomy(-1, 1.5, F2, 1e-8);
    std::cout << "Root F2: " << root_2 << std::endl;

    double root_3 = Dihotomy(-1, 1.5, F3, 1e-8);
    std::cout << "Root F3: " << root_3 << std::endl;

    return 0;
}
