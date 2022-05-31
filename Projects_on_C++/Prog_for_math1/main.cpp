#include <iostream>
#include <cmath>
#include <iomanip>
#include "quanc8.c"
#include "spline.c"

const double MIN_X = 3.0;
const double MAX_X = 5.0;
const double H = 0.25;
const int N = static_cast<int>((MAX_X - MIN_X) / H) + 1;
const int K = 8;
const double xk0 = 3.125;

double f(double);
double lagrange(double, double*, double*);

int main()
{
/*--------------------------FIRST PART OF TASK----------------------------*/
/*-----------------------FIND FUNCTION VALUES WITH QUANC8-----------------*/

/*------INPUT------*/
    const double a = 1.0;
    double b = MIN_X;
    const double abserr = 0.0;
    const double relerr = 1.0e-10;

/*------OUTPUT------*/
    double result = 0.0;
    double errest = 0.0;
    int nofun = 0;
    double posn = 0.0;
    int quancFlag = 0;

/*------PRINT ARRAYS------*/
    double node[N];
    double quancResult[N];

/*------------USING QUANC8------------*/
    std::cout << "THE RESULT OF QUANC8:\n";
    for (int i = 0; i < N; ++i) {
        quanc8(f, a, b, abserr, relerr, &result, &errest, &nofun, &posn, &quancFlag);
        node[i] = b;
        quancResult[i] = result;
        std::cout << "x = " << node[i] << ";  f(x) = " << quancResult[i] << "\n";
        b += H;
    }
    std::cout << "\nFlag QUANC8 = " << quancFlag << "\n";

/*--------------------------SECOND PART OF TASK----------------------------*/
/*-------------FIND VALUES IN POINTS Xk WITH SPLINE, LAGRANGE, QUANC8------*/

/*------Xk ARRAY------*/
    double Xk[K];
    for (int i = 0; i < K; ++i) {
        Xk[i] = xk0 + H * i;
    }

/*------------USING SPLINE------------*/
    double B[N];
    double C[N];
    double D[N];
    int splineFlag = 0;
    int sevalLast = 0;
    spline(N, 0, 0, 0, 06, node, quancResult, B, C, D, &splineFlag);
    std::cout << "Flag Spline = " << splineFlag << "\n\n\n";

    double splineXk[K];
    for (int i = 0; i < K; ++i) {
        splineXk[i] = seval(N, Xk[i], node, quancResult, B, C, D, &sevalLast);
    }

/*------------USING LAGRANGE------------*/
    double lagrangeXk[K];
    for (int i = 0; i < K; ++i) {
        lagrangeXk[i] = lagrange(Xk[i], node, quancResult);
    }

/*------------USING QUANC8 FOR Xk------------*/
    double quancXk[K];
    for (int i = 0; i < K; ++i) {
        b = Xk[i];
        quanc8(f, a, b, abserr, relerr, &result, &errest, &nofun, &posn, &quancFlag);
        quancXk[i] = result;
    }

    std::cout << " " << std::left << std::setw(7) << "№"
              << std::setw(7) << "xk"
              << std::setw(12) << "Spline"
              << std::setw(12) << "Lagrange"
              << std::setw(12) << "f(xk)"
              << std::setw(12) << "|f - Spl|"
              << std::setw(12) << "|f - Lagr|\n" << std::endl;
    for (int i = 0; i < K; ++i){
        std::cout << " " << std::left << std::setw(5) << std::fixed << i;
        std::cout << std::setw(7) << std::setprecision(1) << Xk[i];
        std::cout << std::setw(12) << std::setprecision(6) << splineXk[i];
        std::cout << std::setw(12) << std::setprecision(6) << lagrangeXk[i];
        std::cout << std::setw(12) << std::setprecision(6) << quancXk[i];
        std::cout << std::setw(12) << abs(quancXk[i] - splineXk[i]);
        std::cout << std::setw(12) << abs(quancXk[i] - lagrangeXk[i]) << std::endl;
    }
    std::cout << std::endl;

    return 0;
}

/*------------INTEGRAND------------*/
double f(double t)
{
    return ((sin(t))/t);
}

/*------------LAGRANGE FUNCTION------------*/
double lagrange(double x, double *node, double *func)
{
    double L = 0.0;
    double wkx[N], wkxk[N];
    for (int i = 0; i < N; ++i) {
        wkx[i] = 1.0;
        wkxk[i] = 1.0;
        for (int j = 0; j < N; ++j) {
            if (i == j)
                continue;
            wkx[i] *= (x - node[j]);
            wkxk[i] *= (node[i] - node[j]);
        }

        if (wkxk[i] != 0.0)
            L += (wkx[i] / wkxk[i]) * func[i];
    }
    return L;
}