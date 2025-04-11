#include <iostream>
#include <cmath>

// ������� ��� ���������� ����� �� ������� [a, b] ������� ���������.
double Dihotomy(double a, double b, double (*F)(double), double eps) {
    // ���� ����� ������� ������ �������� ��������
    while ((b - a) / 2 > eps) {
        // ������� �������� �������
        double c = (a + b) / 2;

        // ��������� ���� ������� � �������� �������
        if (F(c) == 0) {
            return c;  // ���� F(c) == 0, �� c � ��� ������
        }
        else if (F(a) * F(c) < 0) {
            // ������ ����� � ����� �������� �������
            b = c;
        }
        else {
            // ������ ����� � ������ �������� �������
            a = c;
        }

    }

    // ���������� �������� ������� ��� ������������ �������� �����
    return (a + b) / 2;
}

// ������ ������� ��� ������ �����
double F1(double x) {
    return x * x - 2;   // ������: ������ �� 2
}

double F2(double x) {
    return x;           // ������: 0           
}


double F3(double x) {
    return log10(x);    // ������: 1
}



int main() {
    // �������.
    double root_1 = Dihotomy(-1, 1.5, F1, 1e-8);
    std::cout << "Root F1: " << root_1 << std::endl;

    double root_2 = Dihotomy(-1, 1.5, F2, 1e-8);
    std::cout << "Root F2: " << root_2 << std::endl;

    double root_3 = Dihotomy(-1, 1.5, F3, 1e-8);
    std::cout << "Root F3: " << root_3 << std::endl;

    return 0;
}
