#include <iostream>
using namespace std;

//------------------------------------------------------------------------------
// Функция: MatrixVectorMultiplication
// Описание: Вычисляет произведение квадратной матрицы A размера N×N на вектор vect.
// Результат записывается в массив ans (предварительно очищается).
//------------------------------------------------------------------------------
void MatrixVectorMultiplication(int N, double* ans, double** A, double* vect) {
    for (int i = 0; i < N; i++) {
        ans[i] = 0;
        for (int j = 0; j < N; j++) {
            ans[i] += A[i][j] * vect[j];
        }
    }
}

//------------------------------------------------------------------------------
// Функция: ScalarMultiplication
// Описание: Вычисляет скалярное произведение двух векторов vect1 и vect2 длины N.
//------------------------------------------------------------------------------
double ScalarMultiplication(int N, double* vect1, double* vect2) {
    double sum = 0.0;
    for (int i = 0; i < N; i++) {
        sum += vect1[i] * vect2[i];
    }
    return sum;
}

//------------------------------------------------------------------------------
// Функция: VectorNumberMultiplication
// Описание: Умножает вектор vect на число Number, результат помещает в ans.
//------------------------------------------------------------------------------
void VectorNumberMultiplication(int N, double* ans, double* vect, double Number) {
    for (int i = 0; i < N; i++) {
        ans[i] = vect[i] * Number;
    }
}

//------------------------------------------------------------------------------
// Функция: VectorSubstraction
// Описание: Вычитает покомпонентно вектор vect2 из vect1 и результат записывает в ans.
//------------------------------------------------------------------------------
void VectorSubstraction(int N, double* ans, double* vect1, double* vect2) {
    for (int i = 0; i < N; i++) {
        ans[i] = vect1[i] - vect2[i];
    }
}

//------------------------------------------------------------------------------
// Функция: VectorsCopy
// Описание: Копирует вектор vect в вектор ans (аналог присваивания ans = vect).
//------------------------------------------------------------------------------
void VectorsCopy(int N, double* ans, double* vect) {
    for (int i = 0; i < N; i++) {
        ans[i] = vect[i];
    }
}

//------------------------------------------------------------------------------
// Функция: MinRes
// Описание: Метод минимизации невязки для решения СЛАУ A*x = F.
// Параметры:
//   N   - размерность системы.
//   A   - матрица коэффициентов (двумерный массив размером N×N).
//   F   - вектор правой части.
//   ANS - вектор, куда будет записано найденное решение.
//   eps - требуемая точность.
// Примечание: реализована в полученном виде, включая порядок вызовов VectorsCopy.
//------------------------------------------------------------------------------
void MinRes(int N, double** A, double* F, double* ANS, double eps) {
    // Выделение памяти для векторов
    double* x0 = new double[N];   // предыдущее приближение
    double* x1 = new double[N];   // текущее приближение
    double* x2 = new double[N];   // следующее приближение
    double* r = new double[N];    // невязка
    double* Ar = new double[N];   // A*r
    double tau;
    double* rtau = new double[N]; // tau * r
    double* Ax = new double[N];   // A*x
    double cur_err;
    double* delta0 = new double[N]; // разность приближений (x1 - x0)
    double* delta1 = new double[N]; // разность приближений (x2 - x1)
    double dif_norm0;
    double dif_norm1;

    // Инициализация: задаём x0 = 0, вычисляем начальную невязку r = -F
    for (int i = 0; i < N; i++) {
        x0[i] = 0;
        r[i] = -F[i];
    }

    // Первая итерация:
    MatrixVectorMultiplication(N, Ar, A, r);                                // Вычисляем Ar.
    tau = ScalarMultiplication(N, r, Ar) / ScalarMultiplication(N, Ar, Ar); // Вычисляем шаг tau.
    VectorNumberMultiplication(N, rtau, r, tau);                            // Вычисляем rtau = tau * r.                         
    VectorSubstraction(N, x1, x0, rtau);                                    // x1 = x0 - rtau.
    VectorSubstraction(N, delta0, x1, x0);                                  // delta0 = x1 - x0.
    dif_norm0 = sqrt(ScalarMultiplication(N, delta0, delta0));              // Вычисляем норму сдвига (delta0).

    // Итерационный процесс
    do {
        // Вычисляем новое приближение:
        MatrixVectorMultiplication(N, Ax, A, x1);                               // Вычисляем Ax.
        VectorSubstraction(N, r, Ax, F);                                        // r = Ax - F (обновляем невязку).             
        MatrixVectorMultiplication(N, Ar, A, r);                                // Вычисляем Ar.
        tau = ScalarMultiplication(N, r, Ar) / ScalarMultiplication(N, Ar, Ar); // Вычисляем tau = (r, Ar) / (Ar, Ar).
        VectorNumberMultiplication(N, rtau, r, tau);
        VectorSubstraction(N, x2, x1, rtau);                                    // x2 = x1 - tau*r

        // Критерий остановки:
        VectorSubstraction(N, delta1, x2, x1);                      // delta1 = x2 - x1
        dif_norm1 = sqrt(ScalarMultiplication(N, delta1, delta1));  // Вычисляем норму сдвига (delta1).
        if (dif_norm1 > dif_norm0) break;                           // Если новая разница ||x2 - x1|| вдруг увеличилась, выходим.
        cur_err = dif_norm1 / (1 - dif_norm1 / dif_norm0);          // Вычисляем ошибку на текущем шаге.
        dif_norm0 = dif_norm1;                                      // Переприсваеваем значение сдвиг для следующей итерации цикла.

        // Сдвиг индексов векторов.
        VectorsCopy(N, x0, x1);
        VectorsCopy(N, x1, x2);

    } while (cur_err > eps); // Работаем, пока точность выше заданной.

    VectorsCopy(N, ANS, x1);

    // Освобождение памяти
    delete[] x0;
    delete[] x1;
    delete[] x2;
    delete[] r;
    delete[] Ar;
    delete[] rtau;
    delete[] Ax;
    delete[] delta0;
    delete[] delta1;
}

//------------------------------------------------------------------------------
// Описание: Пример использования метода MinRes для проверки корректности работы.
//------------------------------------------------------------------------------
int main() {
    // Размер системы
    const int N = 2;
    // Заданная точность вычислений
    double eps = 1e-6;

    // Выделяем память для матрицы A (двумерный массив)
    double** A = new double* [N];
    for (int i = 0; i < N; i++) {
        A[i] = new double[N];
    }
    // Инициализация матрицы A:
    // [4  1]
    // [1  3]
    A[0][0] = 4;  A[0][1] = 1;
    A[1][0] = 1;  A[1][1] = 3;

    // Формирование вектора F
    // Задаём истинное решение x = (1, 1), тогда F = A*(1,1) = (5, 4)
    double* F = new double[N];
    F[0] = 4 * 1 + 1 * 1;  // 5
    F[1] = 1 * 1 + 3 * 1;  // 4

    // Выделяем память под найденное решение ANS
    double* ANS = new double[N];

    // Вызов метода минимизации невязки
    MinRes(N, A, F, ANS, eps);

    // Вывод найденного решения
    cout << "System Solution:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "x[" << i << "] = " << ANS[i] << endl;
    }

    // Освобождение памяти для матрицы и векторов
    for (int i = 0; i < N; i++) {
        delete[] A[i];
    }
    delete[] A;
    delete[] F;
    delete[] ANS;

    return 0;
}
