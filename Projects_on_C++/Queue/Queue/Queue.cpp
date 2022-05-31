#include <iostream>;
#include"TestsQueueList.h"
using namespace std;
int main() 
{
	if (testDelete()) { cout << "elements are deleted correctly" << endl; }

	if (testCope()) { cout << "elements are copied correctly" << endl; }

	if (testAdd()) { cout << "elements are added correctly" << endl; }

	return 0;
}