#include<iostream>
#include<array>
#include<string>

#include <cassert>

#include "Polimorfizm.cpp"
#include "Funkchii.h"
#include"Class.h"
#include"Obedinenie_perechislenie.h"

//Виртуальные функции
void inf(Animal& animal)
{
	animal.name();
	std::cout << "says_";
	animal.says();
}

extern int Myage;
int SetMyAge()
{
	 Myage= 19;
	return Myage;
}


//Class(&&){}
template<typename T>
Class<T> CreateClass(const std::string& name, const XYZ<T> &coord)
{
	Class<T> templ(name, coord);

	return templ;
}
void ConstrConirPrisvaivan()
{
	XYZ<int> coord = { 1, 2, 3 };
	std::string name = "Crug";

	Class<int> b(name, coord);

	Class<int> a = CreateClass<int>(name, coord);
}


//Связывание
int PozdneeSvyaziv(int a, int b)//int (*PS)(int, int) = PozdneeSvyaziv;
{
	return a + b;
}


//Перечисление объединение и исключения
void UnionEnumTryCatch()
{
	try
	{
		union INT_DOUBLE uni;
		std::string a;
		std::cout << "int or double:\n";
		std::cin >> a;
		if (a == "int")
		{
			std::cout << "put ur int value:\n";
			std::cin >> uni.a;
			if (uni.a == 5)
			{
				throw ERRAY_INT_IS_5;
			}
			if (uni.a == 10)
			{
				throw ERRAY_INT_IS_10;
			}
			if (uni.a == 15)
			{
				throw ERRAY_INT_IS_15;
			}
		}
		else if(a == "double")
		{
			std::cout << "put ur double value:\n";
			std::cin >> uni.b;
		}
	}
	catch (enum INT_ERRAY &ERRAY_INT_IS_A)
	{
		std::cout << "ERRAY_INT_IS_" << ERRAY_INT_IS_A << "\n";
	}
}
int getArrayValue(const std::array<int, 10>& array, const int index)
{
	// Предполагается, что значение index-а находится между 0 и 8
	assert(index >= 0 && index <= 8);

	return array[index];
}
// вывод: Assertion failed: index >= 0 && index <=8, file C:\\VCProjects\\Program.cpp, line 6


//class Parent {
//public:
//	void says() { std::cout << "Bark\n"; }
//};
//class Child : public Parent {
//public:
//	void says() { std::cout << "Myau\n"; }
//};

void RLvalue()
{
	/*int i, j, * p;
	i = 7;
	7 = i;
	j * 4 = 7;
	*p = i;
	((i < 3) ? i : j) = 7;
	const int ci = 7;
	ci = 9;*/
}

#define SUM(x, y) x + y



int main()
{
	
	return 0;
}