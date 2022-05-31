#include <iostream>

#include <math.h>
#include "rkf45.cpp"
#define HPRINT 0.0075 //step
#define H_OPT 0.005 //stability condition - optimal integration step
#define EPS 0.0001 //abs error
#define N 2 //number of equations
const double Y0[N] = { 3.0, -1.0 };

double Y[N], YP[N];

int F(int n, double T, double* Y, double* YP);

int rkf3(int(*F)(int n, double t, double y[], double yp[]), int NEQN,
  double Y[], double YP[], double* T, double H);

int main()
{
  double H, T = 0.0, TOUT, RELERR = EPS, ABSERR = EPS;
  int NFE, MAXNFE = 1000, IFLAG = 1, NEQN = N, fail;

  //first part: RKF45
  rkfinit(NEQN, &fail);
  if (fail)
  {
    printf("RKFINIT ERROR!\n");
    exit(1);
  }
  printf("SOLUTION WITH RKF45:\n\n");
  Y[0] = Y0[0];
  Y[1] = Y0[1];
  printf("T: %.4f, Y : %.4f %.4f\n", T, Y[0], Y[1]);
  for (TOUT = HPRINT; TOUT < 0.15 + HPRINT; TOUT += HPRINT)
  {
    rkf45(F, NEQN, Y, YP, &T, TOUT, &RELERR, ABSERR, &H, &NFE, MAXNFE, &IFLAG);
    if (IFLAG == 8) { printf("IFLAG ERROR!\n"); break; }
    printf("T: %.4f, Y : %.4f %.4f\n", T, Y[0], Y[1]);
  }
  printf("\nFLAG: %d, NFE: %d\n\n", IFLAG, NFE);
  rkfend();

  //second part: RKF3
  printf("\nSOLUTION WITH RKF3:\n");
  H = HPRINT;
  printf("\nSTEP = %.4f\n\n", H);
  Y[0] = Y0[0];
  Y[1] = Y0[1];
  for (T = H; T < 0.15 + H; T += H)
  {
    rkf3(F, N, Y, YP, &T, H);
    printf("T: %.4f, Y : %.4f %.4f\n", T, Y[0], Y[1]);
  }

  Y[0] = Y0[0];
  Y[1] = Y0[1];
  H = H_OPT;
  printf("\nSTEP = %.4f\n\n", H);
  for (T = H; T < 0.15; T += H)
  {
    rkf3(F, N, Y, YP, &T, H);
    printf("T: %.4f, Y : %.4f %.4f\n", T, Y[0], Y[1]);
  }
  system("pause");
  return 0;
}

int F(int NEQN, double T, double Y[], double YP[])
{
  YP[0] = -130 * Y[0] + 900 * Y[1] + exp(-10 * T);
  YP[1] = 30 * Y[0] - 300 * Y[1] + log(1 + 100 * T * T);
  return 0;
}

int rkf3(int(*F)(int n, double t, double y[], double yp[]), int NEQN,
  double Y[], double YP[], double* T, double H)
{
  double oldYP[N], oldY[N]; //temporary variables
  double k1[N], k2[N], k3[N];

  oldY[0] = Y[0]; oldY[1] = Y[1];
  (*F)(NEQN, *T, Y, YP);
  oldYP[0] = YP[0];
  oldYP[1] = YP[1];
  //k1
  k1[0] = H * YP[0];
  k1[1] = H * YP[1];
  //k2
  Y[0] = oldY[0] + k1[0] / 2;
  Y[1] = oldY[1] + k1[1] / 2;
  (*F)(NEQN, *T + H / 2, Y, YP);
  k2[0] = H * YP[0];
  k2[1] = H * YP[1];
  //k3
  Y[0] = oldY[0] + 3 * k2[0] / 4;
  Y[1] = oldY[1] + 3 * k2[1] / 4;
  (*F)(NEQN, *T + 3 * H / 4, Y, YP);
  k3[0] = H * YP[0];
  k3[1] = H * YP[1];
  //Zn+1
  Y[0] = oldY[0] + (2 * k1[0] + 3 * k2[0] + 4 * k3[0]) / 9;
  Y[1] = oldY[1] + (2 * k1[1] + 3 * k2[1] + 4 * k3[1]) / 9;
}
