#pragma once
#include <exception>
//========================================================================
// Классы QueueOverflow и QueueUnderflow представляют две основные
// исключительные ситуации, которые могут возникнуть при работе с очередью
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
// Исключительная ситуация WrongQueueSize может возникнyть,
// если в конструкторе очереди неправильно задан размер.
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
// Шаблон класса Queue представляет понятие абстрактного очередь
//==============================================================
template <class T>
class Queue
{
public:
	virtual ~Queue() {}// Виртуальный - для переопределения
	// Абстрактные операции со стеком
	virtual void enQueue(const T& e) = 0; // Добавление элемента в стек
	virtual const T& deQueue() = 0;// Удаление и возвращение верхнего элемента.
	 // Если элементов нет, может возникнуть QueuekUnderflow
	virtual bool isEmpty() = 0; // Проверка на пустоту
};
//==============================================================
// Шаблон класса QueueArray - реализация ограниченной очереди.
// Элементы очереди помещаются в массив.
//==============================================================
template <class T>
class QueueArray : public Queue<T>
{
public:
	QueueArray(int size = 100); // size задает размер "по умолчанию"
	QueueArray(const QueueArray<T>& src);
	virtual ~QueueArray() { delete[] array_; }
	void enQueue(const T& e);
	const T& deQueue();
	bool isEmpty() { return head_ == tail_; }
private:
	T* array_; // массив элементов очереди
	int head_ = 1; // Очередь пуста, если head[Q] = tail[Q].
	int tail_ = 1; // Первоначально: head[Q] = tail[Q] = 1;
	int size_; // размер очереди
};
template <class T>
QueueArray<T>::QueueArray(int size) {
	try {
		array_ = new T[size_ = size];// пытаемся заказать память под элементы стека...
	}
	catch (...) { // если что-то случилось (например, размер слишком большой
		throw WrongQueueSize(); // или отрицательный) - возникает искл.ситуация
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
		throw QueueOverflow(); // нет места для нового элемента
	array_[tail_] = e;
	tail_ = (tail_ + 1);
}
template <class T>
const T& QueueArray<T>::deQueue()
{
	if (head_ == tail_)
		throw QueueUnderflow(); // очередь пуста
	T temp = array_[head_];
	head_ = (head_ + 1);
	return temp;
}

