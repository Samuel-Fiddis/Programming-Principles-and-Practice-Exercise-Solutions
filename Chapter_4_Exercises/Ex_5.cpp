#include "../../std_lib_facilities.h"

void main5()

{
	double a = 0;
	double b = 0;
	char o = '?';

	cout << "Please enter two numbers followed by an operation.\n";
	cin >> a >> b >> o;

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
