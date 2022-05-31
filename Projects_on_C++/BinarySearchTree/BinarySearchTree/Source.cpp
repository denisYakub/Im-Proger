#include"BinarySearchTree.h"
#include<iostream>
using namespace std;

int main()
{
	BinarySearchTree<int> intTree;

	intTree.insert(10);
	intTree.insert(3);
	intTree.insert(20);
	intTree.insert(15);
	intTree.insert(30);
	intTree.insert(2);
	intTree.insert(5);
	intTree.insert(32);
	intTree.insert(22);
	intTree.insert(11);
	intTree.insert(16);

	intTree.nodeInfotmation(7);

	

	intTree.print(cout);

	// ѕоиск в дереве по ключу
	int keyFound = intTree.iterativeSearch(15); // поиск должен быть успешным
	cout << "Key " << 15 << (keyFound ? " found successfully" : " not found") << " in the tree" << endl;
	keyFound = intTree.iterativeSearch(23); // поиск должен быть неудачным
	cout << "Key " << 23 << (keyFound ? " found successfully" : " not found") << " in the tree" << endl;
	// определение высоты и количества узлов дерева
	cout << "height = " << intTree.getHeight() << endl;
	cout << "count = " << intTree.getCount() << endl;

	return 0;
}