#include <iostream>
using namespace std;

// Функция Phi для перехода от функции F к функции phi.
double Phi(double x, double (*F)(double)) {
    return x + F(x); 
}

// Метод простой итерации.
 // Метод простой итерации.
double SmplItr(double x0, double (*F)(double), double eps) {

    // Устанавливаем изначальный значения.
    double x_this = x0;
    double x_prev = x0;
    double x_new = Phi(x_this, F);
    double criteria = 2 * eps;

    do 
    {
        x_prev = x_this;
        x_this = x_new;
        x_new = Phi(x_this, F);

        criteria = std::abs((x_new - x_this) / (1 - (x_new - x_this) / (x_this - x_prev)));
    }
    while (criteria > eps);


    return x_new;
}


// Примеры:
double F1(double x) {
    return (x - 1) * (x - 2) * (x - 2); 
}


int main()
{
    double root_1 = SmplItr(1.5, F1, 1e-8);
    std::cout << "Root: " << root_1 << std::endl;
}
