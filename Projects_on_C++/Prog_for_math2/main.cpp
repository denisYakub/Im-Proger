#include <iostream>
#include <cmath>
#include <iomanip>
#include "decomp.c"

const int N = 8;

int main()
{
    double P[] = { 1e0, 1e-1, 1e-2, 1e-4, 1e-6 };
    double cond = 0;
    int ipvt[N];
    int flag;

    for (double p: P)
    {
        double A_source[N][N] = { { p + 27,  -6,  -1,  -6,  -3,   -4,  -3,  -4 },
                                  {     -6,  35,  -1,  -6,  -5,   -6,  -3,  -8 },
                                  {     -1,  -1,  19,  -6,  -8,   -2,   0,  -1 },
                                  {     -6,  -6,  -6,  36,  -4,   -3,  -4,  -7 },
                                  {     -3,  -5,  -8,  -4,  25,    0,  -1,  -4 },
                                  {     -4,  -6,  -2,  -3,   0,   28,  -8,  -5 },
                                  {     -3,  -3,   0,  -4,  -1,   -8,  21,  -2 },
                                  {     -4,  -8,  -1,  -7,  -4,   -5,  -2,  31 } };

        double A[N * N];
        size_t m = 0;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < N; ++j)
                A[m++] = A_source[i][j];

        double A_Reverse[N][N];

        /*----------REVERSE MATRIX FINDING----------*/
        decomp(N, N, A, &cond, ipvt, &flag);

        for (size_t i = 0; i < N; ++i)
        {
            double X[N];
            for (size_t j = 0; j < N; ++j)
            {
                X[j] = (i == j) ? 1 : 0;
            }

            solve(N, N, A, X, ipvt);

            for (size_t j = 0; j < N; ++j)
            {
                A_Reverse[j][i] = X[j];
            }
        }

        /*----------FIND R----------*/
        double R[N][N];
        for (size_t i = 0; i < N; ++i)
        {
            for (size_t j = 0; j < N; ++j)
            {
                R[i][j] = (i == j) ? 1 : 0;
                for (size_t k = 0; k < N; ++k)
                {
                    R[i][j] -= A_source[i][k] * A_Reverse[k][j];
                }
            }
        }

        /*----------NORM R----------*/
        double norm = 0;
        for (size_t i = 0; i < N; ++i)
        {
            double strSum = 0;
            for (size_t j = 0; j < N; ++j)
            {
                strSum += abs(R[i][j]);
            }

            if (strSum > norm)
            {
                norm = strSum;
            }
        }

        /*----------PRINT----------*/
        std::cout << "\np = " << p << "\n";
        for (size_t i = 0; i < N; ++i)
        {
            for (size_t j = 0; j < N; ++j)
            {
                std::cout << std::setw(13) << A_Reverse[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
        std::cout << "cond of A = " << cond << "\n";
        std::cout << "norm of R = " << norm << "\n\n";
    }
    return 0;
}