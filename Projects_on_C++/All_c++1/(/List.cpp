#include <cstddef>
#include <iostream>
#include "List.h"
#include "Node.h"

template <class T> List<T>::List()
{
  head = NULL;
  size = 0;
}

template <class T> void List<T>::Add(const T data)
{
  Node<T>* curr = new Node<T>(data, NULL);
  if (size == 0)
  {
    head = curr;
    temp = head;
  }
  else {
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = curr;
  }
  size++;
}

template <class T> T List<T>::GetByNum(const int num)
{
  if (num > this->size) {
    std::cout << "There is no such number!\n";
    return T();
  }
  else {
    int curr = 1;
    Node<T>* currNode = new Node<T>();
    currNode = head;
    while (curr != num)
    {
      currNode = currNode->next;
      curr++;
    }
    return currNode->data;
  }
}