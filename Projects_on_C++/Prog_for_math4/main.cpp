#include "math.h"
#include <iostream>

double expX (double x, double e) {
    double x2,c,n,f;
    x2= x;//числитель
    f= 1;//знаменатель
    c= 1;// Тут копим сумму
    n= 2;// начальное значение n
    while (fabs(x2/f)>=e) {//Суммировать будем пока член ряда an не станет достаточно маленьким по модулю
        c=c+(x2/f);
        n=n+1;// переходим к следующему члену
        x2=x2*x;// пересчитываем x
        f=f*(n-1);// пересчитываем f через f(n-1)
    }
    return c;
}
int main() {

    double E = 0.00001;
    double E2 = 0.000001;
    double x1 = 0.5, x2 = -0.5, x3 = -10.5;
    std::cout << std::endl << "Task E = 0.00001"<< std::endl;
    std::cout << "My e^x result: " << expX(x1, E) << " " << expX(x2, E) << " " << expX(x3, E) << std::endl;
    printf(" Real  result: 1.64872 0.606530 0.00002");
    std::cout << std::endl << "If E = 0.000001"<< std::endl;
    std::cout << "My e^x result: " << expX(x1, E2) << " " << expX(x2, E2) << " " << expX(x3, E2) << std::endl;
    printf(" Real  result: 1.64872 0.606530 0.00002");
    return 0;
}