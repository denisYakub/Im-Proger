#pragma once
#include"Node.h"
template <class T>
class List
{
public:
  List();

  void Add(const T data);

  T GetByNum(const int num);
private:
  Node<T>* head;
  Node<T>* temp;
  int size;
};

static int Ni = 20;
