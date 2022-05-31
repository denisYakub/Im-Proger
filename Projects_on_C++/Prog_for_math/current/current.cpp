#include <iostream>
#include "conio.h"
#include <math.h>
#include "Forsythe.h"
#include <iomanip>
#include <fstream>

double alpha2;
double omega2;

void funDiff2(double t, double x[], double dxdt[]) {

  dxdt[0] = 2 * t * (x[0]-x[0]*x[2]-(pow(x[1],3)/omega2) + (x[1]*x[2] / omega2)) - pow(alpha2,2)*x[1];
  dxdt[1] = x[0];
  dxdt[2] = (pow(x[1],2)/omega2) - (x[2] / omega2);
}

double funInt2(double x) {
  return sqrt(x - pow(x, 3));
}
void fun1() {
  std::ofstream out("out1.txt");
  // ************** Определение коэффициентов alpha и omega ****************

  // omega:
  // интеграл берётся с помощью quanc8
  double a = 0;// пределы интегрирования
  double b = 0.5;

  double epsrel = 1.0e-10;   // погрешности
  double epsabs = 0.0;
  double errest;
  int    nofun;
  double  flag;

  omega2 = 0.4493982 * Quanc8(funInt2, a, b,
    epsabs, epsrel, &errest, &nofun, &flag);

  // alpha:
  // используется метод Ньютона для решений уравнений
  double x = 1;   // начальное приближение

  for (int i = 0; i < 3; i++)
    x = x - (pow(x, 2) - tan(3.1415 * x / 3) / 2 * x - 3.1415 / 3 * cos(pow((3.1415 * x / 3), 2)));
  alpha2 = 1.142206 * x;


  // ************************ Построение таблицы ***************************
  // 0 < t < 10
  double X[3] = { 1, 0, 2 };   // начальные условия
  double h = 0.1;

  const int neqn = 3;
  unsigned char work[6 * (neqn * sizeof(Float)) + sizeof(struct rkf_inside)];

  rkf ARG;
  ARG.f = funDiff2;
  ARG.neqn = neqn;
  ARG.re = 0.0001;
  ARG.ae = 0.0001;
  ARG.work = work;
  ARG.flag = 1;
  ARG.Y = X;
  ARG.t = 0;

  // Вторая итерация для оценки погрешности
    X[0] = 1;
    X[1] = 0;
    X[2] = 2;

      alpha2 *= 0.99;
      omega2 *= 0.99;
      std::cout << "\n Assessment of the influence of the error of the initial data on the accuracy:\n"
        << std::endl;

    std::cout.precision(8);
    std::cout << "omega = " << alpha2 << "     tau  = " << omega2 << std::endl;
    std::cout.setf(std::ios::fixed);
    std::cout << "   t            U                U'           z      Flag\n";
    std::cout << "---------------------------------------------------------\n";
    for (double t = h; t < 10.0; t += h) {

      ARG.tout = t;
      rkf45(&ARG);

      std::cout << std::setw(5) << std::setprecision(1) << ARG.tout
        << std::setw(20) << std::setprecision(6) << X[2]
        << std::setw(13) << std::setprecision(6) << X[1]
        << std::setw(13) << std::setprecision(6) << X[0]
        << std::setw(4) << std::setprecision(0) << ARG.flag
        << std::endl;
    }
}
void fun2() {
  std::ofstream out("out1.txt");
  // ************** Определение коэффициентов alpha и omega ****************

  // omega:
  // интеграл берётся с помощью quanc8
  double a = 0;// пределы интегрирования
  double b = 0.5;

  double epsrel = 1.0e-10;   // погрешности
  double epsabs = 0.0;
  double errest;
  int    nofun;
  double  flag;

  omega2 = 0.4493982 * Quanc8(funInt2, a, b,
    epsabs, epsrel, &errest, &nofun, &flag);

  // alpha:
  // используется метод Ньютона для решений уравнений
  double x = 1;   // начальное приближение

  for (int i = 0; i < 3; i++)
    x = x - (pow(x, 2) - tan(3.1415 * x / 3) / 2 * x - 3.1415 / 3 * cos(pow((3.1415 * x / 3), 2)));
  alpha2 = 1.142206 * x;


  // ************************ Построение таблицы ***************************
  // 0 < t < 10
  double X[3] = { 1, 0, 2 };   // начальные условия
  double h = 0.1;

  const int neqn = 3;
  unsigned char work[6 * (neqn * sizeof(Float)) + sizeof(struct rkf_inside)];

  rkf ARG;
  ARG.f = funDiff2;
  ARG.neqn = neqn;
  ARG.re = 0.0001;
  ARG.ae = 0.0001;
  ARG.work = work;
  ARG.flag = 1;
  ARG.Y = X;
  ARG.t = 0;

  // Вторая итерация для оценки погрешности
  X[0] = 1;
  X[1] = 0;
  X[2] = 2;

  std::cout.precision(8);
  std::cout << "omega = " << alpha2 << "     tau  = " << omega2 << std::endl;
  std::cout.setf(std::ios::fixed);
  std::cout << "   t            U                U'           z      Flag\n";
  std::cout << "---------------------------------------------------------\n";
  for (double t = h; t < 10.0; t += h) {

    ARG.tout = t;
    rkf45(&ARG);

    std::cout << std::setw(5) << std::setprecision(1) << ARG.tout
      << std::setw(20) << std::setprecision(6) << X[2]
      << std::setw(13) << std::setprecision(6) << X[1]
      << std::setw(13) << std::setprecision(6) << X[0]
      << std::setw(4) << std::setprecision(0) << ARG.flag
      << std::endl;
  }
}
int main() {
  fun2();
  fun1();
  return 0;
}

//double alpha;
//double omega;
//
//// Представление исходного ДУ 2-го порядка в виде СДУ
//void funDiff(double t, double x[], double dxdt[]) {
//
//  dxdt[0] = alpha * x[0] - alpha / 3 * pow(x[0], 3) - pow(omega, 2) * x[1];
//  dxdt[1] = x[0];
//}
//
//// Подынтегральная функция omega (для quanc8)
//double funInt(double x) {
//  return 1 / (sqrt(1 - 0.25 * pow(sin(x), 2)));
//}
//
//int main() {
//
//  std::ofstream out("out.txt");
//  // ************** Определение коэффициентов alpha и omega ****************
//
//  // omega:
//  // интеграл берётся с помощью quanc8
//  double a = 0;           // пределы интегрирования
//  double b = 3.1415 / 3;
//
//  double epsrel = 1.0e-10;   // погрешности
//  double epsabs = 0.0;
//  double errest;
//  int    nofun;
//  double  flag;
//  omega = 0.9178095 * Quanc8(funInt, a, b,
//    epsabs, epsrel, &errest, &nofun, &flag);
//
//  // alpha:
//  // используется метод Ньютона для решений уравнений
//  // Хn+1 = Xn + En, En = - f(Xn)/f'(Xn)
//  // f(x) = x - 1.3^x;   f'(x) = 1 - 1.3^x * ln(a)
//  double x = 1;   // начальное приближение
//  for (int i = 0; i < 3; i++)
//    x = x - (x - pow(1.3, x)) / (1 - pow(1.3, x) * log(1.3));
//  alpha = 0.2039444 * x;
//
//  // ************************ Построение таблицы ***************************
//  // 0 < t < 16
//  double X[2] = { 2, 0 };   // начальные условия
//  double h = 0.4;
//
//  const int neqn = 2;
//  unsigned char work[6 * (neqn * sizeof(Float)) + sizeof(struct rkf_inside)];
//
//  rkf ARG;
//  ARG.f = funDiff;
//  ARG.neqn = neqn;
//  ARG.re = 0.0001;
//  ARG.ae = 0.0001;
//  ARG.work = work;
//  ARG.flag = 1;
//  ARG.Y = X;
//  ARG.t = 0;
//
//  int iter = 0;
//  // Вторая итерация для оценки погрешности
//  while (iter < 2) {
//
//    X[0] = 2;
//    X[1] = 0;
//
//    if (iter == 1) {
//      alpha *= 0.99;
//      omega *= 0.99;
//      out << "\n Оценка влияния погрешности исходных данных на точность:\n"
//        << std::endl;
//    }
//    out.precision(8);
//    out << "alpha = " << alpha << "    omega = " << omega << std::endl;
//    out.setf(std::ios::fixed);
//    out << "   t       U          U'     Flag\n";
//    out << "---------------------------------\n";
//    for (double t = h; t < 16.1; t += h) {
//
//      ARG.tout = t;
//      rkf45(&ARG);
//      out << std::setw(5) << std::setprecision(1) << ARG.t
//        << std::setw(11) << std::setprecision(6) << X[1]
//        << std::setw(11) << std::setprecision(6) << X[0]
//        << std::setw(4) << std::setprecision(0) << ARG.flag
//        << std::endl;
//    }
//    iter++;
//  }
//  
//  std::cout << "\nOut file was generated\nPress any key to continiue...\n";
//  //getch();
//  return 0;
//}