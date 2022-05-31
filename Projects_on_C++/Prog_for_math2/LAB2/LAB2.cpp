#include <iostream>
#include <cfloat>
#include <fstream>
#include <cmath>
using namespace std;

//Некоторые полезные макросы
#define ABS(x) (((x) >= 0) ? (x) : -(x))
#define MAX(x, y) (((x) >= (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define SIGN0(x) (((x) > 0) ? 1 : -1)
#define SIGN(x) (((x) == 0) ? 0 : SIGN0(x))
#define SIGN2(a, b) (SIGN(b)*ABS(a))
#define MAXIMUM DBL_MAX


void Solve(unsigned int n, double* A, double* b, int* ipvt)
{
  unsigned int k, i;
  int m;
  double t;
  if (!n) return;
  //Прямой ход
  if (n == 1)
  {
    b[0] /= *A;
    return;
  }

  for (k = 0; k < (n - 1); k++)
  {
    m = ipvt[k];

    t = b[m];
    b[m] = b[k];
    b[k] = t;

    for (i = k + 1; i < n; i++) b[i] += A[i * n + k] * t;
  }
  //Обратная подстановка
  for (k = n - 1; k > 0; k--)
  {
    b[k] /= A[k * (n + 1)];
    t = -b[k];
    for (i = 0; i < k; i++) b[i] += A[i * n + k] * t;
  }
  b[0] /= *A;
}


void Decomp(const unsigned int n, double* A, double* cond, int* ipvt)
{
  unsigned int i, j, k;
  int kp1, m;
  double ek, t, anorm, ynorm, znorm;
  double work[8];
  if (!n) return;//размерность матрицы не может быть нулевой
  ipvt[n - 1] = 1;
  if (n == 1)//Случай матрицы 1x1
  {
    *cond = 1.0;
    if (*A == 0.0) *cond = MAXIMUM;//Точная вырожденность
    return;
  }

  //Вычислить 1-норму матрицы A
  anorm = 0.0;
  for (j = 0; j < n; j++)
  {
    t = 0.0;
    for (i = j; i < n * n; i += n) t += ABS(A[i]);
    if (t > anorm) anorm = t;
  }

  //Гауссова исключение с частичным выбором ведущего элемента
  for (k = 0; k < (n - 1); k++)
  {
    kp1 = k + 1;
    //Найти ведущий элемент
    m = k * n + k;
    for (i = (kp1 * n + k); i < n * n; i += n) if (ABS(A[i]) > ABS(A[m])) m = i;
    m /= n;
    ipvt[k] = m;
    if (m != k) ipvt[n - 1] = -ipvt[n - 1];

    t = A[m * n + k];
    A[m * n + k] = A[k * (n + 1)];
    A[k * (n + 1)] = t;

    //Пропустить этот шаг, если ведущий элемент равен нулю
    if (t != 0.0)
    {
      //Вычислить множители
      for (i = (kp1 * n + k); i < n * n; i += n) A[i] = -A[i] / t;
      //Переставлять и исключать по столбцам
      for (j = kp1; j < n; j++)
      {
        int temp = k - j;

        t = A[m * n + j];
        A[m * n + j] = A[k * n + j];
        A[k * n + j] = t;

        if (t != 0.0) for (i = (kp1 * n + j); i < n * n; i += n) A[i] += A[i + temp] * t;
      }
    }
  }

  //work = new double[n];
  //Решить систему (транспонированная A)*Y = I
  for (k = 0; k < n; k++)
  {
    t = 0.0;
    if (k != 0) for (i = k, j = 0; j < (k - 1); i += n, j++) t += A[i] * work[j];
    if (t < 0.0) ek = -1.0;
    else ek = 1.0;
    double temp = A[k * (n + 1)];
    if (temp == 0.0)
    {
      *cond = MAXIMUM;
      delete[] work;
      return;
    }
    work[k] = -(ek + t) / temp;
  }

  k = n - 2;
  do
  {
    t = work[k];
    kp1 = k + 1;
    for (i = kp1 * n + k, j = kp1; j < n; i += n, j++) t += A[i] * work[j];
    work[k] = t;
    m = ipvt[k];
    if (m != k)
    {
      t = work[m];
      work[m] = work[k];
      work[k] = t;
    }
  } while (k--);

  ynorm = 0.0;
  for (i = 0; i < n; i++) ynorm += ABS(work[i]);
  //Решить систему A*Z = Y
  Solve(n, A, work, ipvt);
  znorm = 0.0;
  for (i = 0; i < n; i++) znorm += ABS(work[i]);
  //Оценить обусловленность
  *cond = anorm * znorm / ynorm;
  if (*cond < 1.0) *cond = 1.0;
  //delete[] work;
}

int main() {

  ofstream f("output.txt");

  double p = 0.1;


  double A[8][8]
  {
          { p + 13, 2, 8, -7, 7, 5, -7, -7 },
          { 7, 2, -4, 2, 3, 3, -1, -2 },
          { -7, 2, 1, 3, 6, -6, -3, -4 },
          { -2, -8, -6, -1, 6, 2, 1, -4 },
          { 0, 4, -7, 1, 22, 0, -6, -6 },
          { 0, -3, -6, 6, 4, 13, 0, 6 },
          { -8, -6, -4, 7, -5, -5, -2, 1 },
          { 5, 5, -2, -2, -3, 0, -7, 14 },
  };
  double B[8][1]
  {
          {4 * p + 6}, { 36 }, { -25 }, { -57 }, { 32 }, { 62 }, { -71 }, { 70 }
  };

  double* cond1 = new double();
  int* ipvt = new int();

  cout << endl << "A * x1 = b" << endl;
  cout << "[1]Decomp..." << endl;
  Decomp(8, *A, cond1, ipvt);

  cout << "[1]Solve..." << endl << endl;
  Solve(8, *A, *B, ipvt);


  double Aa[8][8]
  {
          { p + 13, 2, 8, -7, 7, 5, -7, -7 },
          { 7, 2, -4, 2, 3, 3, -1, -2 },
          { -7, 2, 1, 3, 6, -6, -3, -4 },
          { -2, -8, -6, -1, 6, 2, 1, -4 },
          { 0, 4, -7, 1, 22, 0, -6, -6 },
          { 0, -3, -6, 6, 4, 13, 0, 6 },
          { -8, -6, -4, 7, -5, -5, -2, 1 },
          { 5, 5, -2, -2, -3, 0, -7, 14 },
  };

  double Bb[8][1]
  {
          {4 * p + 6}, { 36 }, { -25 }, { -57 }, { 32 }, { 62 }, { -71 }, { 70 }
  };


  //нахождение транспонированной матрицы (T)
  double T[8][8];
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      T[i][j] = Aa[j][i];
    }
  }



  //умножение T на A (результат в А2)
  double A2[8][8];
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
    {
      A2[i][j] = 0;
      for (int z = 0; z < 8; z++) {
        A2[i][j] += T[i][z] * Aa[z][j];
      }

    }

  //умножение T на В (результат в В2)
  double B2[8][1];
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 1; j++)
    {
      B2[i][j] = 0;
      for (int z = 0; z < 8; z++)
        B2[i][j] += T[i][z] * Bb[z][j];
    }

  double* cond2 = new double();
  int* ipvt2 = new int();

  cout << endl << "T * A * x2 = T * b" << endl;
  cout << "[2]Decomp..." << endl;
  Decomp(8, *A2, cond2, ipvt2);

  cout << "[2]Solve..." << endl << endl;
  Solve(8, *A2, *B2, ipvt2);

  double maxX1 = B[0][0];
  double maxErr = abs(B[0][0] - B2[0][0]);

  for (int i = 0; i < 8; i++) {

    f << "[" << i << "]" << endl;
    cout << "blabla";
    cout << "x1[" << i << "] = " << B[i][0] << endl;

    f << B[i][0] << endl;
    cout << "x2[" << i << "] = " << B2[i][0] << endl << endl;
    f << B2[i][0] << endl;

    f << abs(B[i][0] - B2[i][0]) << endl;

    if (maxX1 < B[i][0])
      maxX1 = B[i][0];
    if (maxErr < abs(B[i][0] - B2[i][0]))
      maxErr = abs(B[i][0] - B2[i][0]);
  }

  //числа обусловленности
  cout << endl << "cond(1) = " << *cond1 << endl;
  f << endl << *cond1 << endl;
  cout << "cond(2) = " << *cond2 << endl;
  f << *cond2 << endl;

  cout << "d = " << maxErr / maxX1 << endl << endl;
  f << maxErr / maxX1 << endl;

  f.close();

  system("pause");
}