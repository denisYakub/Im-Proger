#pragma once
#include <exception>
//========================================================================
// ������ QueueOverflow � QueueUnderflow ������������ ��� ��������
// �������������� ��������, ������� ����� ���������� ��� ������ � ��������
//========================================================================
class QueueOverflow : public std::exception
{
public:
	QueueOverflow() : reason("Queue Overflow") {}
	const char* what() const { return reason; }
private:
	const char* reason; // ! const
};
class QueueUnderflow : public std::exception
{
public:
	QueueUnderflow() : reason("Queue Underflow") {}
	const char* what() const { return reason; }
private:
	const char* reason; // ! const
};
//==============================================================
// �������������� �������� WrongQueueSize ����� �������y��,
// ���� � ������������ ������� ����������� ����� ������.
//==============================================================
class WrongQueueSize : public std::exception
{
public:
	WrongQueueSize() : reason("Wrong Queue Size") {}
	const char* what() const { return reason; }
private:
	const char* reason;
};
// =============================================================
// ������ ������ Queue ������������ ������� ������������ �������
//==============================================================
template <class T>
class Queue
{
public:
	virtual ~Queue() {}// ����������� - ��� ���������������
	// ����������� �������� �� ������
	virtual void enQueue(const T& e) = 0; // ���������� �������� � ����
	virtual const T& deQueue() = 0;// �������� � ����������� �������� ��������.
	 // ���� ��������� ���, ����� ���������� QueuekUnderflow
	virtual bool isEmpty() = 0; // �������� �� �������
};
//==============================================================
// ������ ������ QueueArray - ���������� ������������ �������.
// �������� ������� ���������� � ������.
//==============================================================
template <class T>
class QueueArray : public Queue<T>
{
public:
	QueueArray(int size = 100); // size ������ ������ "�� ���������"
	QueueArray(const QueueArray<T>& src);
	virtual ~QueueArray() { delete[] array_; }
	void enQueue(const T& e);
	const T& deQueue();
	bool isEmpty() { return head_ == tail_; }
private:
	T* array_; // ������ ��������� �������
	int head_ = 1; // ������� �����, ���� head[Q] = tail[Q].
	int tail_ = 1; // �������������: head[Q] = tail[Q] = 1;
	int size_; // ������ �������
};
template <class T>
QueueArray<T>::QueueArray(int size) {
	try {
		array_ = new T[size_ = size];// �������� �������� ������ ��� �������� �����...
	}
	catch (...) { // ���� ���-�� ��������� (��������, ������ ������� �������
		throw WrongQueueSize(); // ��� �������������) - ��������� ����.��������
	}
	head_ = 1;
	tail_ = 1;
}
template <class T>
QueueArray<T>::QueueArray(const QueueArray<T>& src) {
	try {
		array_ = new T[size_ = src.size_];
	}
	catch (...) {
		throw WrongQueueSize();
	}
	int temp = 0;
	while (temp != (src.size_ + 1)) {
		this->enQueue(src.array_[temp]);
		temp++;
	}
}
template <class T>
void QueueArray<T>::enQueue(const T& e)
{
	if (head_ == tail_ + 1)
		throw QueueOverflow(); // ��� ����� ��� ������ ��������
	array_[tail_] = e;
	tail_ = (tail_ + 1);
}
template <class T>
const T& QueueArray<T>::deQueue()
{
	if (head_ == tail_)
		throw QueueUnderflow(); // ������� �����
	T temp = array_[head_];
	head_ = (head_ + 1);
	return temp;
}

