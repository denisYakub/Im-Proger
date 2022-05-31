#pragma once
#include <iostream>

class Shape{
public:
	Shape()
	{
		std::cout << "Shape()\n";
	}

	virtual ~Shape() {
		std::cout << "~Shape()\n";
	}
	virtual void Draw(){
		std::cout << "Draw::Shape()\n";
	}
	virtual void setXY(const int& x, const int& y) = 0;
};

class Triangle: public Shape
{
public:
	Triangle(): x(0), y(0)
	{
		std::cout << "Triangle()\n";
	}
	virtual ~Triangle()
	{
		std::cout << "~Triangle()\n";
	}
	void Draw() override {
		std::cout << "Draw::Triangle()\n";
	}
	void setXY(const int& x, const int& y) override {
		this->x = x;
		this->y = y;
		std::cout << "setXY::Triangle()"<< x << y <<"\n";
	}

	void operator +=(Triangle a) {
		this->x += a.x;
		this->y += a.y;
	}

	bool operator !=(Triangle b) {
		if (this->x != b.x)
			return true;
		if (this->y != b.y)
			return true;
	}
private:
	int x;
	int y;
};

class Circle :public Triangle {
public:
	Circle() : x(0), y(0)
	{
		std::cout << "Circle()\n";
	}
	~Circle()
	{
		std::cout << "~Circle()\n";
	}
	void Draw() override{
		std::cout << "Draw::Circle()\n";
	}
	void setXY(const int& x, const int& y) override {
		this->x = x;
		this->y = y;
		std::cout << "setXY::Circle()" << x << y << "\n";
	}
private:
	int x;
	int y;
};

int Pus = 10;