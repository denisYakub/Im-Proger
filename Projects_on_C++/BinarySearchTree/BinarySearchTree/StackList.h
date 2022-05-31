#pragma once
#include<iostream>
template <class T>
class StackList
{
public:
	StackList()
	{
		head_ = nullptr;
		size = 0;
	}
	~StackList() {}
	void push(const T& i)
	{
		if (size == 0)
		{
			head_ = new Node<T>(i);
			size++;
		}
		else
		{
			head_ = new Node<T>(i, head_);
			size++;
		}
	}
	T pop()
	{
		T data = T();
		if (size == 0)
		{
			std::cerr << "ERROR_YOUR_STACK_IS_0" << std::endl;
		}
		Node<T>* temp = head_;
		data = temp->data;
		head_ = head_->next_;
		delete temp;
		size--;
		return data;
	}
private:
	template <class T>
	class Node
	{
	public:
		T data;
		Node* next_;
		Node(T data = T(), Node* next_ = nullptr)
		{
			this->data = data;
			this->next_ = next_;
		}
	};
	Node<T>* head_;
	int size = 0;
};

