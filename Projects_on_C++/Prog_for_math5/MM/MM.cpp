#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>
#include <complex>

float p1 = 1;
int p3 = 20;
int p4 = 10;
double p5 = 0.6;
int p6 = -5;

const double PI = 3.1415926535897932384626433832795;

double AParamForA() {
  double a, b, c, d , k;
  a = p6;
  b = p5;
  c = p4;
  d = p3;
  k = p1;
  return (-b * b - 2 * b * k - 2 * k + 1);
}

double BParamForA() {
  double a, b, c, d, k;
  a = p6;
  b = p5;
  c = p4;
  d = p3;
  k = p1;
  return (a * b * b + 2 * a * b * k - a * b + b * b * d * d - 2 * b * b * d + b * c + 2 * b * d * d - 4 * b * d * k + 2 * c * k + d * d - 4 * d * k + 2 * d);
}

double CParamForA() {
  double a, b, c, d, k;
  a = p6;
  b = p5;
  c = p4;
  d = p3;
  k = p1;
  return (-2 * a * b * b * d * d + 2 * a * b * b * d - 2 * a * b * d * d + 4 * a * b * d * k - 2 * a * b * d - b * b * d * d - b * c * d * d + 2 * b * c * d - 2 * b * d * d * k - c * d * d + 4 * c * d * k - 2 * d * d * k + d * d);
}

double DParamForA() {
  double a, b, c, d, k;
  a = p6;
  b = p5;
  c = p4;
  d = p3;
  k = p1;
  return (a * a * a * b * b * d * d + a * b * b * d * d + a * b * c * d * d + 2 * a * b * d * d * k - a * b * d * d + b * c * d * d + 2 * c * d * d * k);
}

double AParamForB() {
  double a, b, c, d, k;
  a = p6;
  b = p5;
  c = p4;
  d = p3;
  k = p1;
  return (b * b + 2 * b * k + k * k);
}

double BParamForB() {
  double a, b, c, d, k;
  a = p6;
  b = p5;
  c = p4;
  d = p3;
  k = p1;
  return (-2 * a * b * b - 2 * a * b * k - b * b - b * c * k - 2 * b * k - c * k * k - k * k);
}

double CParamForB() {
  double a, b, c, d, k;
  a = p6;
  b = p5;
  c = p4;
  d = p3;
  k = p1;
  return (a * a * b * b + a * b * b + a * b * c * k + a * b * k + b * c * k + 2 * c * k * k);
}

double eA_(double x2) {
  double sum = 1.0;
  int n = 100;
  for (size_t i = n - 1; i > 0; --i)
  {
    sum = 1 + (x2* p3 / (p3 + x2)) * sum / i;
  }
  //std::cout << "eA " << sum << "\n";
  return sum;
}

double eB_(double x2) {
  double sum = 1.0;
  int n = 1000;
  for (size_t i = n-1; i>0; --i)
  {
    sum = 1 + x2 * sum / i;
  }
  //std::cout << "eB " << sum << "\n";
  return sum;
}

double x1_(double x2) {
  return ((x2*(p1 + p5) - p5 * p6)/(p4 * p1));
}

double p2_(double x1, double e) {
  return ((x1*p1) / ((1 - x1)*e));
}

void checkBifDotsForA(double p1, double p2, double p3, double p4, double p5, double p6, double x1, double x2, double e) {
  double res = (-2 * p1 - p5 - p2 * e + ((p4 * p2 * e) * (1 - x1)) / pow((1 + (x2 / p3)), 2));
  double a11 = -p1 - p2*e;
  double a12 = (p2*(1 - x1)*e) / pow((1 + (x2 / p3)), 2);
  double a21 = -p2*p4*e;
  double a22 = -p1 - p5 + (p2*p4*e*(1 - x1)) / pow((1 + (x2 / p3)), 2);

  double a = 1;
  double b = -(a11+a22);
  double c = (a11*a22-a21*a12);
  double d1 = b * b - 4 * a * c;

  std::cout << std::endl << "For: " << x2 << std::endl;
  std::cout << "Ur result for a11 + a12 = 0 is: " << res << std::endl;
  std::cout << "(" << a11 << " " << a12 << ")" << std::endl;
  std::cout << "(" << a21 << " " << a22 << ")" << std::endl;

  if (d1 > 0)
  {
    x1 = ((-b) + sqrt(d1)) / (2 * a);
    x2 = ((-b) - sqrt(d1)) / (2 * a);
    std::cout << "Real eigenvalues have been found:" << "\n";
    std::cout << "x = " << x1 << "\n";
    std::cout << "x = " << x2 << "\n";
  }
  else {
    std::cout << "Real eigenvalues were not found!" << "\n";
  }
}

void checkBifDotsForB(double p1, double p2, double p3, double p4, double p5, double p6, double x1, double x2, double e) {
  double res = (-2 * p1 - p5 - p2 * e + ((p4 * p2 * e) * (1 - x1)));
  double a11 = -p1 - p2*e;
  double a12 = p2*(1 - x1)*e;
  double a21 = -p2*p4*e;
  double a22 = -p1 - p5 + p2*p4*e*(1 - x1);

  double a = 1;
  double b = -(a11 + a22);
  double c = (a11 * a22 - a21 * a12);
  double d1 = b * b - 4 * a * c;

  std::cout << std::endl << "For: " << x2 << std::endl;
  std::cout << "Ur result for a11 + a12 = 0 is: " << res << std::endl;
  std::cout << "(" << a11 << " " << a12 << ")" << std::endl;
  std::cout << "(" << a21 << " " << a22 << ")" << std::endl;

  if (d1 > 0)
  {
    x1 = ((-b) + sqrt(d1)) / (2 * a);
    x2 = ((-b) - sqrt(d1)) / (2 * a);
    std::cout << "Real eigenvalues have been found:" << "\n";
    std::cout << "x = " << x1 << "\n";
    std::cout << "x = " << x2 << "\n";
  }
  else {
    std::cout << "Real eigenvalues were not found!" << "\n";
  }
}

int main()
{
  double a, b, c, d, disc, q, r, dum1, s, t, term1, r13, value1, value2, value3, x1, x2, d1;

  a = AParamForA();
  b = BParamForA();
  c = CParamForA();
  d = DParamForA();

  std::cout << "A)" << "\n";

  std::cout << "a=" << a << " " << "b=" << b << " " << "c=" << c << " " << "d=" << d << "\n";
  b /= a;
  c /= a;
  d /= a;
  q = (3.0 * c - (b * b)) / 9.0;
  r = -(27.0 * d) + b * (9.0 * c - 2.0 * (b * b));
  r /= 54.0;
  disc = q * q * q + r * r;
  value1 = 0;
  term1 = (b / 3.0);
  if (disc > 0) { // one root real, two are complex
    s = r + sqrt(disc);
    s = ((s < 0) ? -pow(-s, (1.0 / 3.0)) : pow(s, (1.0 / 3.0)));
    t = r - sqrt(disc);
    t = ((t < 0) ? -pow(-t, (1.0 / 3.0)) : pow(t, (1.0 / 3.0)));
    value1 = -term1 + s + t;
    term1 += (s + t) / 2.0;
    value3 = value2 = -term1;
    term1 = sqrt(3.0) * (-t + s) / 2;
    value2 = term1;
    value3 = -term1;
  }
  if (disc == 0) { // All roots real, at least two are equal.
    r13 = ((r < 0) ? -pow(-r, (1.0 / 3.0)) : pow(r, (1.0 / 3.0)));
    value1 = -term1 + 2.0 * r13;
    value3 = value2 = -(r13 + term1);
  }
  if (disc < 0) { // Only option left is that all roots are real and unequal (to get here, q < 0)
    q = -q;
    dum1 = q * q * q;
    dum1 = acos(r / sqrt(dum1));
    r13 = 2.0 * sqrt(q);
    value1 = -term1 + r13 * cos(dum1 / 3.0);
    value2 = -term1 + r13 * cos((dum1 + 2.0 * PI) / 3.0);
    value3 = -term1 + r13 * cos((dum1 + 4.0 * PI) / 3.0);
  }
 
  /*value1 = 0.0295404;
  value2 = 2.89545;
  value3 = 365.356;*/

  std::cout << "x = " << value1 << "\n";
  std::cout << "x = " << value2 << "\n";
  std::cout << "x = " << value3 << "\n";
  std::cout << "x1 = " << x1_(value1) << ", " << x1_(value2) << ", " << x1_(value3) << "\n";
  std::cout << "p2 = " << p2_(x1_(value1), eA_(value1)) << ", " << p2_(x1_(value2), eA_(value2)) << ", " << p2_(x1_(value3), eA_(value3)) << "\n";
  checkBifDotsForA(p1, p2_(x1_(value1), eA_(value1)), p3, p4, p5, p6, x1_(value1), value1, eA_(value1));
  checkBifDotsForA(p1, p2_(x1_(value2), eA_(value2)), p3, p4, p5, p6, x1_(value2), value2, eA_(value2));
  checkBifDotsForA(p1, p2_(x1_(value3), eA_(value3)), p3, p4, p5, p6, x1_(value3), value3, eA_(value3));
  std::cout << "\n" << "B)" << "\n";

  p1 = 0.5;
  p3 = std::numeric_limits<double>::max();
  p4 = 9;
  p5 = 0.8;
  p6 = 0;

  while (p4<11)
  {
    std::cout << "P4 =" << p4 << "\n";

    a = AParamForB();
    b = BParamForB();
    c = CParamForB();

    d1 = b * b - 4 * a * c;
    if (d1 > 0)
    {
      x1 = ((-b) + sqrt(d1)) / (2 * a);
      x2 = ((-b) - sqrt(d1)) / (2 * a);
      std::cout << "x = " << x1 << "\n";
      std::cout << "x = " << x2 << "\n";
    }
    if (d1 == 0)
    {
      x1 = -(b / (2 * a));
      std::cout << "x = x = " << x1 << "\n";
    }
    if (d1 < 0) {
      std::cout << "D < 0, There are no real roots of the equation";
    }
    std::cout << "x1 = " << x1_(x1) << ", " << x1_(x2) << "\n";
    std::cout << "p2 = " << p2_(x1_(x1), eB_(x1)) << ", " << p2_(x1_(x2), eB_(x2)) << "\n";
    checkBifDotsForB(p1, p2_(x1_(x1), eB_(x1)), p3, p4, p5, p6, x1_(x1), x1, eB_(x1));
    checkBifDotsForB(p1, p2_(x1_(x2), eB_(x2)), p3, p4, p5, p6, x1_(x2), x2, eB_(x2));
    p4++;
    std::cout << "\n";
  }

  return 0;
}
