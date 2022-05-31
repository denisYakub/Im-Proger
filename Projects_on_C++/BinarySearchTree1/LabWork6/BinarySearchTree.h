#pragma once
#include"Queue.h"
#include"Stack.h"
#include <iostream>
using namespace std;
template <class T>
class BinarySearchTree
{
public:
	// Описание структуры узла со ссылками на детей
	class Node {
	public:
		T key_; // значение ключа, содержащееся в узле
		Node* left_; // указатель на левое поддерево
		Node* right_; // указатель на правое поддерево
		Node* p_; // указатель на родителя !!! не используется
		//_________________________ Конструктор узла
		Node(const T& key = T(), Node* left = nullptr, Node* right = nullptr,
			Node* p = nullptr) {
			key_ = key;
			left_ = left;
			right_ = right;
			p_ = p;
		}
	};
	// Дерево реализовано в виде указателя на корневой узел.
	Node* root_;
	// Конструктор "по умолчанию" создает пустое дерево
	BinarySearchTree()
	{
		root_ = nullptr;
	}
	BinarySearchTree(Node* root)
	{
		root_ = root;
	}
	// Деструктор освобождает память, занятую узлами дерева
	virtual ~BinarySearchTree()
	{
		deleteSubtree(root_);
	}
	// Печать строкового изображения дерева в выходной поток out
	void print(ostream& out) const
	{
		printNode(out, root_);
		out << endl;
	}
	// Функция поиска по ключу в бинарном дереве поиска
	bool iterativeSearch(const T& key) const
	{
		return (iterativeSearchNode(key) != nullptr);
	}
	// Вставка нового элемента в дерево, не нарушающая порядка
	// элементов. Вставка производится в лист дерева
	void insert(const T& key)
	{
		if (root_ == nullptr)
		{
			root_ = new Node(key);
			return;
		}
		Node* prev, * current;
		current = root_;
		prev = current;
		while (current != nullptr)
		{
			prev = current;
			if (key < current->key_)
			{
				current = current->left_;
			}
			else if (key > current->key_)
			{
				current = current->right_;
			}
			else
			{
				return;
			}
		}
		Node* newNode = new Node(key);
		if (key < prev->key_)
		{
			prev->left_ = newNode;
			return;
		}
		else
		{
			prev->right_ = newNode;
			return;
		}

	}
	void insertRec(const T& key)
	{
		insertNodeRec(this->root_, key);
	}
	// Удаление элемента из дерева, не нарушающее порядка элементов
	void deleteKey(const T& key)
	{
		Node* current = this->iterativeSearchNode(key);
		Node* prev = this->parentSearch(key);
		//элемент не имеет наследников
		if (current->left_ == nullptr && current->right_ == nullptr) {
			if (prev->key_ > current->key_)
				prev->left_ = nullptr;
			else
				prev->right_ = nullptr;
			delete current;
		}
		//элемент имеет одного наследника
		else if (current->left_ != nullptr && current->right_ == nullptr) {
			Node* temp = current->left_;
			if (prev->key_ > current->key_)
				prev->left_ = temp;
			else
				prev->right_ = temp;
			delete current;
		}
		else if (current->right_ != nullptr && current->left_ == nullptr) {
			Node* temp = current->right_;
			if (prev->key_ > current->key_)
				prev->left_ = temp;
			else
				prev->right_ = temp;
			delete current;
		}
		//если элемент имеет двух наследников
		else if (current->left_ != nullptr && current->right_ != nullptr)
		{
			if (current == prev->right_)
			{
				Node* temp = current->right_;
				prev->right_ = current->right_;
				while (temp->left_ != nullptr) {
					temp = temp->left_;
				}
				temp->left_ = current->left_;
				delete current;
			}
			if (current == prev->left_)
			{
				Node* temp = current->right_;
				prev->left_ = current->right_;
				while (temp->left_ != nullptr) {
					temp = temp->left_;
				}
				temp->left_ = current->left_;
				delete current;
			}
		}
	}
	// Определение количества узлов дерева
	int getCount() const
	{
		return getCountSubTree(this->root_);
	}
	// Определение высоты дерева
	int getHeight() const
	{
		return getHeightSubTree(this->root_);
	}
	//Поиск элемента, следующего за указанным
	T findNextNode(const T& num)
	{
		if (num == this->root_->key_) {
			return this->root_->left_->key_;
		}
		if (num > this->root_->key_) {
			Node* temp1 = this->root_->right_;
			while ((temp1 != nullptr) and (num != temp1->key_)) {
				if (num > temp1->key_) {
					temp1 = temp1->right_;
				}
				else {
					temp1 = temp1->left_;
				}
			}
			return temp1->right_->key_;
		}
		else {
			Node* temp2 = this->root_->left_;
			while ((temp2 != nullptr) and (num != temp2->key_)) {
				if (num > temp2->key_) {
					temp2 = temp2->right_;
				}
				else {
					temp2 = temp2->left_;
				}
			}
			return temp2->right_->key_;
		}
	}
	T getNode(const int index) const
	{
		Node* current = this->root_;
		while (current->left_ != nullptr)
		{
			current = current->left_;
		}
		for (int i = 1; i <= index; i++)
		{
			current = findTheFollowingNode(current->key_);
		}
		return current->key_;
	}
	//=================================================================
	//Итеративный метод обхода двоичного дерева по уровням(в ширину).В
	//реализации использовать класс очередь.
	//=================================================================
	void levelWalk(Node* root_) const
	{
		if (root_ != nullptr) {
			Queue<Node*> queueList;
			queueList.enQueue(root_);
			while (queueList.size_ != 0) {
				Node* temp = queueList.deQueue();
				cout << temp->key_ << "_";
				if (temp->left_ != nullptr) {
					queueList.enQueue(temp->left_);
				}
				if (temp->right_ != nullptr) {
					queueList.enQueue(temp->right_);
				}
			}
		}
	}
	//========================================================
	//итеративный метод обхода двоичного дерева слева направо
	//(префиксный).В реализации использовать класс стек.
	//========================================================
	void prefixLeftToRightWalk(Node* root_)
	{
		if (root_ != nullptr) {
			Stack<Node*>stackList;
			Node* temp = root_;
			while ((stackList.size != 0) or (temp != nullptr)) {
				if (temp != nullptr) {
					stackList.push(temp);
					temp = temp->left_;
				}
				else {
					temp = stackList.pop();
					cout << temp->key_ << "_";
					temp = temp->right_;
				}
			}
		}
	}
	//=============================================================================
	//Похожими будем называть деверья поиска, содержащие одинаковые наборы ключей.
	//Написать метод, определяющий, являются ли два дерева похожими.
	//=============================================================================
	bool sameTreeElemets(Node* first_root, Node* second_root)
	{
		if ((first_root == nullptr) and (second_root == nullptr)) {
			return true;
		}
		if (((first_root != nullptr) and (second_root == nullptr)) or ((first_root == nullptr) and (second_root!= nullptr))) {
			return false;
		}
		Stack<Node*>stackList1;
		Stack<Node*>stackList2;
		Node* curr1 = first_root;
		Node* curr2 = second_root;
		while (((stackList1.size != 0) or (curr1 != nullptr)) and ((stackList2.size != 0) or (curr2 != nullptr))) {
			if (curr1 != nullptr) {
				stackList1.push(curr1);
				curr1 = curr1->left_;
			}
			if (curr2 != nullptr) {
				stackList2.push(curr2);
				curr2 = curr2->left_;
			}
			curr1 = stackList1.pop();
			curr2 = stackList2.pop();
			if (curr1->key_ != curr2->key_) {
				return false;
			}
			curr1 = curr1->right_;
			curr2 = curr2->right_;
		}
		return true;
	}
private:
	// Функция поиска адреса узла по ключу в бинарном дереве поиска
	Node* iterativeSearchNode(const T& key) const
	{
		if (root_ == nullptr)
			return root_;
		Node* current = root_;
		while (current != nullptr)
		{
			if (key < current->key_)
			{
				current = current->left_;
			}
			else if (key > current->key_)
			{
				current = current->right_;
			}
			if (current == nullptr || current->key_ == key)
			{
				return current;
			}
		}
	}
	//поиск родителя
	Node* parentSearch(const T& key) const
	{
		if (root_ == nullptr)
			return nullptr;
		Node* current = root_;
		Node* prev = current;
		while (current != nullptr) {

			if (key < current->key_) {

				prev = current;
				current = current->left_;
				/*current = current->left_;
				prev = current;*/
			}
			else {
				prev = current;
				current = current->right_;
				/*current = current->right_;
				prev = current;*/
			}
			if (current == nullptr || current->key_ == key)
			{
				return prev;
			}
		}
	}
	// Рекурсивные функции, представляющие рекурсивные тела основных интерфейсных методов
	//
	// Рекурсивная функция для освобождения памяти
	void deleteSubtree(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}
		else
		{
			if (node->left_ != nullptr)
				deleteSubtree(node->left_);
			if (node->right_ != nullptr)
				deleteSubtree(node->right_);
			delete node;
		}
	}
	// Рекурсивная функция определения количества узлов дерева
	int getCountSubTree(Node* node) const
	{
		if (node == nullptr)
			return 0;
		return (1 + getCountSubTree(node->left_) +
			getCountSubTree(node->right_));
	}
	// Рекурсивная функция определения высоты дерева
	int getHeightSubTree(Node* node) const
	{
		int h1 = 0, h2 = 0;
		if (node == nullptr)
			return 0;
		if (node->left_)
			h1 = getHeightSubTree(node->left_);
		if (node->right_)
			h2 = getHeightSubTree(node->right_);
		return(std::_Max_value(h1, h2) + 1);
	}
	// Рекурсивная функция для вывода изображения дерева в выходной поток
	void printNode(ostream& out, Node* root) const
	{
		// Изображение дерева заключается в круглые скобки.
		out << '(';
		if (root) {
			// Для узлов дерева должна быть определена (или переопределена)
			// операция вывода в выходной поток <<
			out << root->key_;
			printNode(out, root->left_);
			printNode(out, root->right_);
		}
		out << ')';
	}
	// Рекурсивная функция для организации обхода узлов дерева.
	void inorderWalk(Node* node) const
	{
		while (node != nullptr) {
			inorderWalk(*node->left_);
			inorderWalk(*node->right_);
		}
	}
	void insertNodeRec(Node* node, const T& key)const
	{
		if (node == nullptr)
		{
			node = new Node(key);
		}
		else
		{
			if (key < node->key_)
				insertNodeRec(node->left_, key);
			else if (key > node->key_)
				insertNodeRec(node->right_, key);
		}
	}
};

