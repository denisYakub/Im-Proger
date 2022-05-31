#pragma once
#include"QueueList.h";
#include <iostream>;
using namespace std;
//======================
//Tests for QueueList.h
//======================
bool testCope()
{
	QueueList<int>a;
	a.enQueueList(2);
	a.enQueueList(3);
	a.enQueueList(-5);
	QueueList<int>b(a);
	if ((a.first->key_ != b.first->key_) and 
		(a.last->key_ != b.last->key_) and 
		(a.first->p_next->key_ != b.first->p_next->key_)) { return false; }
	return true;
}

bool testAdd()
{
	QueueList<int>a;
	a.enQueueList(2345);
	a.enQueueList(0);
	a.enQueueList(-5);
	if ((a.first->key_ != 2345) and (a.first->p_next->key_ != 0) and (a.last->key_ != -5)) { return false; }
	return true;
}

bool testDelete()
{
	QueueList<int>a;//ситуация когда 1 элемент
	a.enQueueList(1);
	a.deQueueList();
	if ((a.first != a.last)and((a.first == nullptr) and (a.last==nullptr))) {
		return false;
	}

	QueueList<int>b;//ситуация когда нет элемент
	if (!(b.deQueueList())) {
		return false;
	}

	QueueList<int>c;//стондартная ситуация
	c.enQueueList(2);
	c.enQueueList(3);
	c.enQueueList(-5);
	if ((c.deQueueList())!=2) {
		return false;
	}
	return true;
}