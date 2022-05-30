#pragma once
#include <string>
#include<iostream>

template<class T>
struct XYZ
{
public:
	T x;
	T y;
	T z;
};

template<class T>
class Class
{
private:
	std::string name;
	XYZ<T> coord;
	
public:
	Class()
	{
		std::cout << "Constr po umolchan\n";
		name = "???";
		coord.x = T();
		coord.y = T();
		coord.z = T();
	}
	Class(std::string name1, XYZ<T> coord1)
	{
		std::cout << "Constr\n";
		name = name1;
		coord.x = coord1.x;
		coord.y = coord1.y;
		coord.z = coord1.z;
	}
	Class(const Class& class1)
	{
		std::cout << "Constr-conir\n";
		name = class1.name;
		coord.x = class1.coord.x;
		coord.y = class1.coord.y;
		coord.z = class1.coord.z;
	}
	Class(const Class&& class1) noexcept
	{
		std::cout << "Constr-conir-prisvaivan\n";
		name = class1.name;
		coord.x = class1.coord.x;
		coord.y = class1.coord.y;
		coord.z = class1.coord.z;

	}
	Class& operator=(const Class& class1)
	{
		std::cout << "Operator-conir\n";
		name = class1.name;
		coord.x = class1.coord.x;
		coord.y = class1.coord.y;
		coord.z = class1.coord.z;

		return this;
	}
	Class& operator=(const Class&& class1)
	{
		std::cout << "Operator-conir-prisvaivan\n";
		name = class1.name;
		coord.x = class1.coord.x;
		coord.y = class1.coord.y;
		coord.z = class1.coord.z;

		return this;
	}
	void Print()
	{
		std::cout << "My name is: " << this->name << " and my coordinates are: " << this->coord.x << ", " << this->coord.y << ", " << this->coord.z << ".\n";
	}
	
	~Class()
	{
		std::cout << "~Class\n";
	}
};

