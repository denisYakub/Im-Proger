#include<iostream>
#include<exception>
using namespace std;

class Operator//класс для присваивания приоритетов 
{
public:
	Operator(const char sight);
	~Operator() {}
	int getPriority();
	char getSight() { return sight; }
private:
	char sight;
};
Operator::Operator(const char sight)
{
	this->sight = sight;
}

int Operator::getPriority()
{
	int priority = -1;
	switch (sight)
	{
	case '(':
		return (priority = 0);
		break;
	case ')':
		return (priority = 1);
		break;
	case '+':
		return (priority = 2);
		break;
	case '-':
		return (priority = 2);
		break;
	case '/':
		return (priority = 3);
		break;
	case '*':
		return (priority = 3);
		break;
	case '^':
		return (priority = 4);
		break;
	default:
		return (priority = -1);
		break;
	}
}

class StackOverflow : public std::exception
{
public:
	StackOverflow() : reason("Stack Overflow") {}
	const char* what() const { return reason; }
private:
	const char* reason;
};
class StackUnderflow : public std::exception
{
public:
	StackUnderflow() : reason("Stack Underflow") {}
	const char* what() const { return reason; }
private:
	const char* reason;
};

template <class T>
class Stack
{
public:
	virtual ~Stack() {}
	virtual void push(const T& e) = 0;
	virtual const T& pop() = 0;
	virtual bool isEmpty() = 0;
};

class WrongStackSize : public std::exception
{
public:
	WrongStackSize() : reason("Wrong Stack Size") {}
	const char* what() const { return reason; }
private:
	const char* reason;
};

template <class T>
class StackArray : public Stack<T>
{
public:
	StackArray(int size = 30);
	StackArray(const StackArray<T>& src);
	virtual ~StackArray() { delete[] array_; }
	void push(const T& e);
	const T& pop();
	bool isEmpty() { return top_ == 0; }
private:
	T* array_;
	int top_ = 0;
	int size_;
};
template<class T>
inline StackArray<T>::StackArray(int size)
{
	try {
		array_ = new T[size_ = size];
	}
	catch (...) {
		throw WrongStackSize();
	}
	top_ = 0;
}

template<class T>
StackArray<T>::StackArray(const StackArray<T>& src)
{
	try {
		array_ = new T[size_ = src.size_];
	}
	catch (...) {
		throw WrongStackSize();
	}
	for (int i = 0; i < src.top_; i++) {
		array_[i] = src.array_[i];
	}
	top_ = src.top_;
}

template<class T>
void StackArray<T>::push(const T& e)
{
	if (top_ == size_)
		throw StackOverflow();
	top_++;
	array_[top_] = e;
}

template<class T>
const T& StackArray<T>::pop()
{
	if (top_ == 0)
		throw StackUnderflow();
	return array_[top_--];
}

void translationFromInfToPostf(const char* text, int maxDeep = 30)// функция переводит строку из инф. в постф. и выводит в консоль 
{

	Stack<char>* stack = new StackArray<char>(maxDeep);
	try {
		char cText = '\0';

		for (int i = 0; ((cText = text[i]) != '\0'); i++) {
			if ((cText >= 'A' && cText <= 'Z' || cText >= 'a' && cText <= 'z')) {
				std::cout << cText;
			}
			else {
				if (stack->isEmpty()) {
					stack->push(cText);
				}
				else {
					if (cText == '(' || cText == ')') {
						if (cText == '(') {
							stack->push(cText);
						}
						if (cText == ')') {
							char res = stack->pop();
							while (res != '(')
							{
								cout << res;
								res = stack->pop();
							}
						}
					}
					else {
						Operator s2(cText);
						if (s2.getPriority() > 1) {
							char a = stack->pop();
							Operator s1(a);
							if (s1.getPriority() >= s2.getPriority()) {
								cout << s1.getSight();
								stack->push(cText);
							}
							else {
								stack->push(a);
								stack->push(cText);
							}
						}
						else {
							stack->push(cText);
						}
					}
				}
			}
		}
		while (!stack->isEmpty()) {
			std::cout << stack->pop();
		}
	}
	catch (StackUnderflow) {
		std::cerr << "Your stack is udnerflow!" << std::endl;
	}
	catch (StackOverflow) {
		std::cerr << "Your stack is overflow!" << std::endl;
	}
	delete stack;
}

int calculate(const char* expression, int maxDeep = 30)//функция получает строку в постф. и находит значение 
{
	int result = 0;
	Stack<int>* stack = new StackArray<int>(maxDeep);
	try {
		char cText = '\0';
		for (int i = 0; ((cText = expression[i]) != '\0'); i++) {
			int num = 0;
			int num1 = 0;
			int num2 = 0;
			int sum = 0;
			switch (cText)
			{
			case '+':
				num2 = stack->pop();
				num1 = stack->pop();
				sum = num1 + num2;
				stack->push(sum);
				break;
			case '-':
				num2 = stack->pop();
				num1 = stack->pop();
				sum = num1 - num2;
				stack->push(sum);
				break;
			case '/':
				num2 = stack->pop();
				num1 = stack->pop();
				sum = num1 / num2;
				stack->push(sum);
				break;
			case '*':
				num2 = stack->pop();
				num1 = stack->pop();
				sum = num1 * num2;
				stack->push(sum);
				break;
			case '^':
				num2 = stack->pop();
				num1 = stack->pop();
				sum = num1 ^ num2;
				stack->push(sum);
				break;
			default:
				num = atoi(&cText);
				stack->push(num);
				break;
			}


		}
	}
	catch (StackUnderflow) {
		std::cerr << "Your stack is udnerflow!" << std::endl;
	}
	catch (StackOverflow) {
		std::cerr << "Your stack is overflow!" << std::endl;
	}
	result = stack->pop();
	delete stack;

	return result;
}

int main()
{
	const char* text1 = "(a+b)/(c-c)";
	translationFromInfToPostf(text1, 13);
	const char* text2 = "463-*86-2/+";
	int res = calculate(text2, 13);
	cout << endl << res << endl;
	return 0;
}