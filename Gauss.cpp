#include <iostream>
#include <cmath>
#include <algorithm>

void Gauss(int N, double** A, double* B, double* ANS) {

    // Для каждого столбца в матрице.
    for (int i = 0; i < N; ++i) { 

        // 1. Находим максимальный элемент в i - ом столбце, который находится под диагональю.
        int pivot = i;
        double maxVal = std::fabs(A[i][i]);         // fabs - функция модуля для нецелых чисел
        for (int row = i + 1; row < N; ++row) {
            double val = std::fabs(A[row][i]);
            if (val > maxVal) {
                maxVal = val;
                pivot = row;
            }
        }

        // 2. Меняем строки так, чтобы максимальный элемент оказался на диагонали.
        if (pivot != i) {
            std::swap(A[i], A[pivot]);  // Меняем указатели на строки
            std::swap(B[i], B[pivot]);  // Меняем местами элементы свободных членов
        }

        // 3. Обнуление элементов под диагональю (Вычитание строк)
        for (int row = i + 1; row < N; ++row) {
            double c = A[row][i] / A[i][i];         // Находим коэффициент, который обнулит определенный элемент i - го столбца под диагональю, A[row][i] - c * A[i][i] = 0
            B[row] -= c * B[i];                     // Используем данный коэффициент для нахождения нового значения в столбце B[row] = B[row] - c * B[i]
            for (int col = i; col < N; ++col) {     // Вычитаем из row строки i - ую строку. Получили 0.
                A[row][col] -= c * A[i][col];       
            }
        }

    }

    // После получения верхне-треугольной матрицы(все элементы под диагональю == 0), подставляем значения.
    for (int i = N - 1; i >= 0; --i) {
        double sum = B[i];
        for (int j = i + 1; j < N; ++j) {
            sum -= A[i][j] * ANS[j];
        }
        ANS[i] = sum / A[i][i];
    }
}

// Пример для проверки
int main() {
    int N = 3;
    double** A = new double* [N];
    for (int i = 0; i < N; ++i) {
        A[i] = new double[N];
    }

    // Заполнение A
    A[0][0] = 4; A[0][1] = -3; A[0][2] = -3;
    A[1][0] = 4; A[1][1] = -1; A[1][2] = 0;
    A[2][0] = 5; A[2][1] = 1; A[2][2] = 5;

    // Вектор B
    double* B = new double[N];
    B[0] = 4;
    B[1] = 5;
    B[2] = 9;

    // Массив для ответа
    double* ANS = new double[N];

    // Вызываем метод Гаусса
    Gauss(N, A, B, ANS);

    // Выводим решение
    std::cout << "Solution:\n";
    for (int i = 0; i < N; ++i) {
        std::cout << "x" << i + 1 << " = " << ANS[i] << std::endl;
    }

    return 0;
}
