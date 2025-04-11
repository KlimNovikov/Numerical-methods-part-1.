#include <iostream>

// Метод трапеций для интегрирования F(x) на [a, b] с Nx равными шагами
double Trap(double a, double b, int Nx, double (*F)(double)) {
    double h = (b - a) / Nx;
    double sum = 0.5 * (F(a) + F(b));  // полусумма концов

    for (int i = 1; i < Nx; ++i) {
        double x_i = a + i * h;
        sum += F(x_i);
    }
    return sum * h;
}

// Функция для вычисления интеграла с заданной точностью eps (апостериорная оценка)
double Integration(double a, double b, int N, double (*F)(double), double eps) {
    // Начальное вычисление
    double I_prev = Trap(a, b, N, F);

    // Итерационный процесс
    while (true) {
        // Увеличиваем число разбиений в 2 раза
        int N_new = 2 * N;
        double I_new = Trap(a, b, N_new, F);

        // Проверяем, достигнута ли точность
        if (std::fabs(I_new - I_prev) < eps) {
            return I_new;
        }

        // Иначе продолжаем уточнять
        // Переносим результаты для следующей итерации
        I_prev = I_new;
        N = N_new;

    }
}

// Пример : 
double F1(double x) {
    return x * x;
}

int main() {

    double result = Integration(-1.0, 1.0, 1001, F1, 1e-8);
    std::cout << "Result = " << result << std::endl;

    return 0;
}
