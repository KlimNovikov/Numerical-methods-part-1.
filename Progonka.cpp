#include <iostream>

// Решение трёхдиагональной СЛАУ методом прогонки
// N    - размерность системы
// a[i] - поддиагональные коэффициенты (a[0] = 0 по соглашению)
// b[i] - диагональные коэффициенты
// c[i] - наддиагональные коэффициенты (c[N-1] = 0 по соглашению)
// d[i] - правая часть
// ANS  - массив, куда будет записано решение x[i]


void Progonka(int N, double* a, double* b, double* c, double* d, double* ANS) {

    // Вспомогательные массивы для прогоночных коэффициентов
    double* alpha   = new double[N];
    double* beta    = new double[N];

    // Инициализация alpha[0] и beta[0]
    alpha[0]    = -c[0] / b[0];
    beta[0]     = d[0] / b[0];

    // Прямой ход: вычисляем alpha[i], beta[i]
    for (int i = 1; i < N; ++i) {
        double denom    = b[i] + a[i] * alpha[i - 1];
        alpha[i]        = -c[i] / denom;
        beta[i]         = (d[i] - a[i] * beta[i - 1]) / denom;
    }

    // Обратный ход: восстанавливаем решение
    ANS[N - 1] = beta[N - 1];
    for (int i = N - 2; i >= 0; --i) {
        ANS[i] = alpha[i] * ANS[i + 1] + beta[i];
    }

    // Освобождаем динамическую память
    delete[] alpha;
    delete[] beta;
}

int main() {
    // Пример: Решим систему размерности N=3:
    //  b0*x0 + c0*x1         = d0
    //  a1*x0 + b1*x1 + c1*x2 = d1
    //         a2*x1 + b2*x2 = d2

    int N = 3;
    double a[3] = { 0.0,  1.0,  2.0 };  // Поддиагональ (a[0]=0)
    double b[3] = { 4.0,  5.0,  3.0 };  // Главная диагональ
    double c[3] = { -1.0, -2.0, 0.0 };  // Наддиагональ (c[2]=0)
    double d[3] = { 1.0, -1.0, 2.0 };   // Правая часть

    double ANS[3];

    Progonka(N, a, b, c, d, ANS);

    std::cout << "Solution:\n";
    for (int i = 0; i < N; ++i) {
        std::cout << "x" << i << " = " << ANS[i] << "\n";
    }

    return 0;
}
