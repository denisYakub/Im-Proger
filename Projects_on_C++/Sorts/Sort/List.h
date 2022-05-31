#pragma once
#ifndef LIST_H
#define LIST_H

#include <iostream>

template<class T>
class List {
public:

    List() : tail_(nullptr), head_(nullptr) {
    }

    int operator+=(T value) {
        int counter = 0;
        if (head_ == nullptr) {
            head_ = new Node(value, nullptr);
            tail_ = head_;
            return 1;
        }
        Node* curr = head_;
        if (head_->getData() > value) {
            head_ = new Node(value, curr);
            return 1;
        }
        else if (tail_->getData() < value) {
            tail_->setNext(new Node(value, nullptr));
            tail_ = tail_->getNext();
            return 1;
        }
        else {
            while (curr != nullptr) {
                counter++;
                if (curr->getData() >= value) {
                    T tmpValue = curr->getData();
                    Node* tmpPointer = curr->getNext();
                    curr->setData(value);
                    curr->setNext(new Node(tmpValue, tmpPointer));
                    if (curr == tail_) {
                        tail_ = curr->getNext();
                    }
                    return counter;
                }
                curr = curr->getNext();
            }
        }
    }


    ~List() {
        while (head_ != nullptr) {
            Node* curr = head_;
            head_ = head_->getNext();
            delete (curr);
        }
    }


    bool isEmpty() const {
        return head_ == nullptr;
    }

    struct Node {
    public:
        Node(T value, Node* next) : value_(value), next_(next) {
        }

        Node* getNext() const {
            return next_;
        }

        void setData(T value) {
            value_ = value;
        }

        void setNext(Node* next) {
            next_ = next;
        }

        T getData() const {
            return value_;
        }

    private:
        Node* next_;
        T value_;
    };

    Node* head_;
    Node* tail_;
};

#endif