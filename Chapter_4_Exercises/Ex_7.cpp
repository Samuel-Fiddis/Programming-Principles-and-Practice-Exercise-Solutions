#include "../../std_lib_facilities.h"

void main7()

{

	vector<string> numbers = { "zero","one","two","three","four","five","six","seven","eight","nine" };
	vector<string> letters = { "0","1","2","3","4","5","6","7","8","8","9" };
	string digit_1 = "nil";
	string digit_2 = "nil";
	double a = 0;
	double b = 0;
	char o = '?';

	cout << "Please enter a two single-digit integer values in numeric or word format followed by an opporation.\n";
	cin >> digit_1 >> digit_2 >> o;

	for (double i = 0; i <= 9; ++i)
	{
		if (digit_1 == letters[i])
			a = i;
		if (digit_1 == numbers[i])
			a = i;
	}

	for (double i = 0; i <= 9; ++i)
	{
		if (digit_2 == letters[i])
			b = i;
		if (digit_2 == numbers[i])
			b = i;
	}

	switch (o) {
	case '+':
		cout << "The sum of " << a << " and " << b << " is " << a + b << '\n';
		break;
	case '-':
		cout << "The difference of " << a << " and " << b << " is " << a - b << '\n';
		break;
	case '*':
		cout << "The product of " << a << " and " << b << " is " << a * b << '\n';
		break;
	case '/':
		cout << "The division of " << a << " by " << b << " is " << a / b << '\n';
		break;
	}
}
