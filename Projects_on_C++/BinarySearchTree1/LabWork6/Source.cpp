#include"BinarySearchTree.h"
#include <iostream>;
using namespace std;
int main()
{
	bool testsFor6Task();
	if (testsFor6Task()) { cout << "All binary tree traversal methods are working well." << endl; }//сами методы записаны в BinarySearchTree.h
																								  //и начинаются с 208 строчки
	return 0;																					
}


bool testsFor6Task()
{
	BinarySearchTree<int>a;
	a.insert(14);
	a.insert(12);
	a.insert(11);
	a.insert(13);
	a.insert(20);
	a.insert(19);
	a.insert(21);
	a.insert(15);
	cout << "Binary tree method by levels(wide)" << endl;
	cout << "Result should look like this: 14 12 20 11 13 19 21 15" << endl;
	cout << "Function method works like this: ";
	a.levelWalk(a.root_);
	cout << endl;
	cout << "Are the results the same?(yes-1/no-2)";
	int e = 0;
	cin >> e;
	if (e == 2) { return false; }
	cout << endl;
	cout << "Binary tree method by left to right" << endl;
	cout << "Result should look like this: 11 12 13 14 15 19 20 21" << endl;
	cout << "Function method works like this: ";
	a.prefixLeftToRightWalk(a.root_);
	cout << endl;
	cout << "Are the results the same?(yes-1/no-2)";
	int d = 0;
	cin >> d;
	if (d == 2) { return false; }
	cout << endl;
	BinarySearchTree<int>b;
	b.insert(14);
	b.insert(12);
	b.insert(11);
	b.insert(13);
	b.insert(20);
	b.insert(19);
	b.insert(21);
	b.insert(15);
	if ((a.sameTreeElemets(a.root_, b.root_)) == false) { 
		cout << "1)method sameTreeElemets doesn't work" << endl;
		return false; 
	}
	BinarySearchTree<int>c;
	c.insert(12);
	c.insert(19);
	c.insert(11);
	c.insert(18);
	if ((a.sameTreeElemets(a.root_, c.root_)) == true) { 
		cout << "2)method sameTreeElemets doesn't work" << endl;
		return false; 
	}
	return true;
}