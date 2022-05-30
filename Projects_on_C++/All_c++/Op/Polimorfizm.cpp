#include<iostream>

//����������� ��������(���������) � ������������ � ����������� �������
class Animal {
public:
	virtual void name() = 0;
	virtual void says() = 0;
};

class Cat :public Animal {
public:
	void name() override { std::cout << "Cat_"; }
	void says() override { std::cout << "Mauy_"; }
};

class Dog :public Animal {
private:
	void name() override { std::cout << "Dog_"; }
	void says() override { std::cout << "ofof_"; }
};

//����������� (Ad-hoc) ����������� � ���������� ������� � ����������; ���������� ���
//������, ����� ������� ������ ���� �������.
class A {
public:
	void sum(int a, int b) { std::cout << a + b <<"\n"; }
	void sum(double a, double b) { std::cout << a + b << "\n"; }
};

//��������������� ����������� � ������������� ����� ���������� ��� ��������� �����
//������(�������).

template<typename T>
class Sum {
public:
	T sum(T a, T b) { return a + b; }
};