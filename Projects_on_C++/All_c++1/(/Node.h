#pragma once
#include <cstddef>
template <class T>
class Node
{
public:
  Node(T data, Node* next)
  {
    this->data = data;
    this->next = next;
  }

  Node(T data)
  {
    this->data = data;
  }

  Node() {
    this->data = T();
    this->next = NULL;
  }

  Node<T>* next;
  T data;
};