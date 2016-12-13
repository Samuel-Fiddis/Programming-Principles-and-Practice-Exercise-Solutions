#include "../../std_lib_facilities.h"

int factorial(int x)
{
	if (x == 0)
		return 1;
	else if (x < 0) error("Can't factorial a number less than 0");
	else if (x > 0)
	{
		int ret = 1;
		for (int i = 1; i <= x; ++i)
		{
			ret *= i;
		}
		return ret;
	}
}

int P(int a, int b)
{
	return factorial(a) / factorial(a - b);
}

int C(int a, int b)
{
	return P(a, b) / factorial(b);
}

int main()
{
	string Choice;
	int a;
	int b;

	while (cin)
	{
		cout << "Please enter two digits and either P or C. Enter Ctrl Z to exit. ";
		cin >> a >> b >> Choice;

		if (Choice == "P")
			cout << P(a, b) << '\n';
		else if (Choice == "C")
			cout << C(a, b) << '\n';
	}

}