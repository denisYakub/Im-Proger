#pragma once
#include <iostream>;
#include <exception>
using namespace std;
class QueueUnderflow : public std::exception
{
public:
    QueueUnderflow() : reason("Queue Underflow") {}
    const char* what() const { return reason; }
private:
    const char* reason;
};

template <class T>
class Queue
{
public:
    Queue()
    {
        first = last = nullptr;
        size_ = 0;
    }
    ~Queue()
    {
        while (first) {
            last = first->p_next;
            delete first;
            first = last;
        }
    }
    Queue(Queue<T>& scr);

    void enQueue(const T& data);
    T deQueue();

    template<class T>
    class Node
    {
    public:
        T key_;
        Node* p_next;
        Node* p_prev;
        Node(T key_ = T(), Node* p_next = nullptr, Node* p_prev = nullptr) {
            this->key_ = key_;
            this->p_next = p_next;
            this->p_prev = p_prev;
        }
    };
    Node<T>* first;
    Node<T>* last;
    int size_ = 0;
};

template<class T>
inline Queue<T>::Queue(Queue<T>& scr)
{
    Node<T>* temp = scr.first;
    while (temp != nullptr) {
        this->enQueueList(temp->key_);
        temp = temp->p_next;
    }
}

template<class T>
inline void Queue<T>::enQueue(const T& data)
{
    Node<T>* temp = new Node<T>(data);
    temp->p_next = nullptr;
    if (first != nullptr) {
        temp->p_prev = last;
        last->p_next = temp;
        last = temp;
    }
    else {
        temp->p_prev = nullptr;
        first = last = temp;
    }
    size_++;
}

template<class T>
inline T Queue<T>::deQueue()
{
    try
    {
        if (first == nullptr) {
            throw QueueUnderflow();
        }
        else {
            if (first == last) {
                T curr = first->key_;
                first = last = nullptr;
                size_--;
                return curr;
            }
            else {
                T curr = first->key_;
                Node<T>* temp = new Node<T>;
                temp = first;
                first = first->p_next;
                first->p_prev = nullptr;
                delete temp;
                size_--;
                return curr;
            }
        }
    }
    catch (const std::exception&)
    {

    }
}

