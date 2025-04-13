#include <iostream>

// Метод трапеций для интегрирования F(x) на [a, b] с Nx равными шагами
double Trap_method(double a, double b, int Nx, double(*F)(double)) {
	double h = (b - a) / Nx;
	double sum = 0.5 * (F(a) + F(b));  // полусумма концов

	for (int i = 1; i < Nx; ++i) {
		double x_i = a + i * h;
		sum += F(x_i);
	}
	return sum * h;
}

// Функция для оценки эффективного порядка точности
double P_eff(double a, double b, int N, double(*F)(double), int r) {
	// Приближённые значения интеграла на N, 2N и 4N разбиениях
	double I1 = Trap_method(a, b, N, F);
	double I2 = Trap_method(a, b, r * N, F);
	double I4 = м(a, b, r * r * N, F);

	// Формула:
	// p_eff = log2( |(I2 - I1) / (I4 - I2)| )
	double numerator = I2 - I1;
	double denominator = I4 - I2;
	double ratio = std::fabs(numerator / denominator);
	double p = std::log(ratio) / std::log(2.0);         // Создаем логарифм по основанию 2: log2(x) = ln(x) / ln(2)
	return p;
}

// Пример:
double F1(double x) {
	return x * x;
}

int main() {

	double approx_integral = Trap_method(-1.0, 1.0, 1001, F1);
	double order_estimate = P_eff(-1.0, 1.0, 1001, F1, 2);

	std::cout << "Integration Result = "
		<< approx_integral << std::endl;
	std::cout << "Accuracy p_eff = "
		<< order_estimate << std::endl;

	return 0;
}
