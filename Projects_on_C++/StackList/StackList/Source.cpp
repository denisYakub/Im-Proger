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
bool testBalanceBrackets(const char* text, int maxDeep = 30)
{
    bool  isBalanceBrackets = true;
    StackList<char> stack;
    char cText = '\0';
    for (int i = 0; ((cText = text[i]) != '\0') && (isBalanceBrackets == true); i++)
    {
        switch (cText)
        {
        case '(': case '[': case '{':
            stack.push(cText); 
            break;
        case ')': 
            if (stack.pop() != '(')
            {
                isBalanceBrackets = false;
            }
            break;
        case ']':
            if (stack.pop() != '[')
            {
                isBalanceBrackets = false;
            }
            break;
        case '}':
            if (stack.pop() != '{')
            {
                isBalanceBrackets = false;
            }
            break;
        }
    }

	return  isBalanceBrackets;
}

int main()
{
    const char* text00 = " ok ";
    std:: cout << text00 << ": " << (testBalanceBrackets(text00) ? "right" : "wrong") << std::endl;
    const char* text01 = "( ) ok ";
    std::cout << text01 << ": " << (testBalanceBrackets(text01) ? "right" : "wrong") << std::endl;
    const char* text02 = "( ( [] ) ) ok ";
    std::cout << text02 << ": " << (testBalanceBrackets(text02) ? "right" : "wrong") << std::endl;
    const char* text03 = "( ( [ { } [ ] ( [ ] ) ] ) ) OK";
    std::cout << text03 << ": " << (testBalanceBrackets(text03) ? "right" : "wrong") << std::endl;
    const char* text04 = "( ( [ { } [ ] ( [ ] ) ] ) ) ) extra right parenthesis ";
    std::cout << text04 << ": " << (testBalanceBrackets(text04) ? "right" : "wrong") << std::endl;
    const char* text05 = "( ( [{ }[ ]([ ])] ) extra left parenthesis ";
    std::cout << text05 << ": " << (testBalanceBrackets(text05) ? "right" : "wrong") << std::endl;
    const char* text06 = "( ( [{ ][ ]([ ])]) ) unpaired bracket ";
    std::cout << text06 << ": " << (testBalanceBrackets(text06) ? "right" : "wrong") << std::endl;

	return 0;
}