#include <iostream>
using namespace std;

int main() {
	cout << "ВВедите n" << endl;
	int n;
		cin >> n;
	int sov = 0;
	int ned = 0;
	int izb = 0;
	int s;
	int j = 0;
	for (size_t i = 0; i < n; i++)
	{
		s = 0;
		while (j != i/2)
		{
			if (i % j == 0)
				s += j;
			j++;
		}
		if (s = i)
			++sov;
		if (s < i)
			++izb;
	}
	cout << sov;
	cout << ned;
	cout << izb;
	cout << endl;
	return 0;
}