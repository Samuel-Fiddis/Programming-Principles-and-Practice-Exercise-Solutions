#include "../../std_lib_facilities.h"

int main()
{
	int* p = new int{ 1 };
	int* q = new int{ 1 };
	int* n = new int{ 1 };

	cout << p << '\n' << q << '\n' << n << '\n';

	//Free store grows up.

	int a = 1;
	int b = 2;
	int c = 3;

	cout << &a << '\n' << &b << '\n' << &c << '\n';

	//Stack grows down.
}