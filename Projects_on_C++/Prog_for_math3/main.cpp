#include <cstdio>
#include <cmath>
#include "trkf45_1\rkf45.h"

void f(float t, float *x, float *dx) {
    dx[0] = -155 * x[0] - 750 * x[1] + sin(1 + t);
    dx[1] = x[0] - cos(1 - t) + t + 1;
    return;
}

int main() {
    int n = 2;
    float x0[2] = { 5, -1 };
    float t = 0, tout = 0;
    float re = 0.0001, ae = 0.0001;
    int iflag = 1;
    float work[15];
    int iwork[30];
    float h = 0.04;
    printf("rkf45, eps = 0.0001, h = %.2f\n", h);
    while (tout < 1.01) {
        RKF45(f, n, x0, &t, &tout, &re, &ae, &iflag, work, iwork);
        printf("t = %.2f, x = { %f; %f }, iflag = %d\n", t, x0[0], x0[1], iflag);
        tout += h;
    }

    printf("\nRK 2nd degree of accuracy, h = 0.02\n");
    x0[0] = 5; x0[1] = -1;
    t = 0;
    h = 0.02;
    float z16[2], z1[2], dx[2];

    while (t < 1.01) {
        f(t, x0, dx);
        z16[0] = x0[0] + h / 6 * dx[0];
        z16[1] = x0[1] + h / 6 * dx[1];

        float dx2[2];
        f(t, z16, dx2);
        z1[0] = x0[0] + h * ( -2 * dx[0] + 3 * dx2[0]);
        z1[1] = x0[1] + h * (-2 * dx[1] + 3 * dx2[1]);

        printf("t = %.2f, x = { %f; %f }\n", t, z1[0], z1[1]);

        x0[0] = z1[0];
        x0[1] = z1[1];
        t += h;
    }

    printf("\nRK 2nd degree of accuracy, h = 0.013\n");
    x0[0] = 5; x0[1] = -1;
    t = 0;
    h = 0.013;

    while (t < 1.005) {
        f(t, x0, dx);
        z16[0] = x0[0] + h / 6 * dx[0];
        z16[1] = x0[1] + h / 6 * dx[1];

        float dx2[2];
        f(t, z16, dx2);
        z1[0] = x0[0] + h * (-2 * dx[0] + 3 * dx2[0]);
        z1[1] = x0[1] + h * (-2 * dx[1] + 3 * dx2[1]);

        printf("t = %.3f, x = { %f; %f }\n", t, z1[0], z1[1]);

        x0[0] = z1[0];
        x0[1] = z1[1];
        t += h;
    }

    getchar();
}