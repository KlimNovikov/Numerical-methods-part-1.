#include <iostream>
using namespace std;

void Progonka(int N, double* a, double* b, double* c, double* d, double* ANS) {
    double* ksi = new double[N];
    double* eta = new double[N];

    ksi[0] = -c[0] / b[0];
    eta[0] = d[0] / b[0];

    for (int i = 1; i < N; i++) {
        double znam = a[i - 1] * ksi[i - 1] + b[i];
        if (i != N - 1) {
            ksi[i] = -c[i] / znam;
        }
        eta[i] = (d[i] - a[i - 1] * eta[i - 1]) / znam;
    }

    ANS[N - 1] = eta[N - 1];
    for (int i = N - 2; i >= 0; i--) {
        ANS[i] = ksi[i] * ANS[i + 1] + eta[i];
    }
}
int main()
{
    int N = 5;
    double* a, * b, * c, * d, * ANS;
    a = new double[N - 1];
    b = new double[N];
    c = new double[N - 1];
    d = new double[N];
    ANS = new double[N];
    a[0] = -3; a[1] = -2; a[2] = -1; a[3] = 0;
    c[0] = -2; c[1] = -1; c[2] = 0; c[3] = 1;
    b[0] = 12; b[1] = 20; b[2] = 30; b[3] = 42, b[4] = 56;
    d[0] = 8; d[1] = 34; d[2] = 86; d[3] = 170, d[4] = 280;
    Progonka(N, a, b, c, d, ANS);
    for (int i = 0; i < N; i++) {
        cout << ANS[i] << endl;
    }
}
