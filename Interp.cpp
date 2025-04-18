﻿#include <iostream>
using namespace std;

// Функция для инициализации массивов абсцисс и значений функции.
// В данном примере функция задается как U(x) = sin(x),
// при этом абсциссы равномерно распределены на отрезке [a, b].
void GetData(int N, double* x, double* u, double a, double b) {
	double h = (b - a) / (N - 1);
	for (int i = 0; i < N; i++) {
		x[i] = a + i * h;
		u[i] = sin(x[i]);
	}
}

// Вычисление конечных разностей.
// Параметры:
//   double **U – двумерный массив, в который будут записаны конечные разности;
//   int N – количество точек интерполяции;
//   double *x – массив абсцисс известных точек;
//   double *u – массив значений функции в известных точках.
// Реализация:
//   Первый ряд U[0][i] заполняется значениями функции u[i].
//   Далее для порядков k = 1 ... N-1 вычисляются конечные разности по формуле:
//       U[k][i] = (U[k-1][i+1] - U[k-1][i]) / (x[i+k] - x[i])
//   для i от 0 до N - k - 1.
void FinitDifferences(double** U, int N, double* x, double* u) {
	// Инициализация нулевого порядка конечных разностей: U[0][i] = u[i]
	for (int i = 0; i < N; i++) {
		U[0][i] = u[i];
	}
	// Вычисление конечных разностей для порядков от 1 до N-1
	for (int k = 1; k < N; k++) {
		for (int i = 0; i < N - k; i++) {
			U[k][i] = (U[k - 1][i + 1] - U[k - 1][i]) / (x[i + k] - x[i]);
		}
	}
}

// Интерполяция многочленом Ньютона.
// Параметры:
//   int N – количество точек интерполяции;
//   double *x – массив абсцисс известных точек;
//   double **U – двумерный массив конечных разностей (предварительно вычисленный функцией FinitDifferences);
//   double x0 – точка, в которой необходимо вычислить значение интерполированного многочлена.
// Функция возвращает значение интерполированной функции в точке x0.
// Формула интерполяционного многочлена Ньютона:
// P(x0) = U[0][0] + (x0 - x[0])*U[1][0] + (x0 - x[0])*(x0 - x[1])*U[2][0] + ... + 
//         (x0 - x[0])*(x0 - x[1])*...*(x0 - x[N-2])*U[N-1][0]
double Interp(int N, double* x, double** U, double x0) {
	double result = U[0][0];
	double term = 1.0;
	for (int k = 1; k < N; k++) {
		term *= (x0 - x[k - 1]);
		result += term * U[k][0];
	}
	return result;
}



int main() {
	// Заданные параметры
	const double M_PI = 3.14159265358979323846;
	int N = 5;              // Количество точек интерполяции
	double a = 0.0;         // Начало отрезка
	double b = 0.5 * M_PI;  // Конец отрезка (для функции sin(x) можно взять, например, [0, π/2])
	double x0 = M_PI / 2.5;   // Точка интерполяции (ожидаемое значение sin(π/6) = 0.5)

							  // Выделение памяти для одномерных массивов x и u
	double* x = new double[N];
	double* u = new double[N];

	// Выделение памяти для двумерного массива конечных разностей U (размер N x N)
	double** U = new double*[N];
	for (int i = 0; i < N; i++) {
		U[i] = new double[N];
	}

	// Инициализация таблицы значений функции
	GetData(N, x, u, a, b);

	// Вычисление конечных разностей и заполнение массива U
	FinitDifferences(U, N, x, u);

	// Вычисление значения интерполяционного многочлена Ньютона в точке x0
	double y0 = Interp(N, x, U, x0);

	// Вывод результата
	cout << "Real Number: 		" << y0 << endl;
	cout << "Interpolated number: 	" << sin(x0) << endl;

	return 0;
}

