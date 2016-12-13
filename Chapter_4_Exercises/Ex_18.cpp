#include "../../std_lib_facilities.h"

void main18()
{
	double a = 0;
	double b = 0;
	double c = 0;

	cout << "Please enter the constants a, b and c for as quadratic equation to be solved: ";
	cin >> a >> b >> c;
	cout << '\n';

	double root = b*b - 4 * a*c;

	if (root < 0)
		cout << "The soultion is a complex number.\n";


	double x1 = (-b + sqrt(root)) / (2 * a);
	double x2 = (-b - sqrt(root)) / (2 * a);

	cout << " The first solution is: " << x1 << "\nThe secound solution is: " << x2 << '\n';

	cout << "First check: " << a*x1*x1 + b*x1 + c << '\n' << "Second check: " << a*x2*x2 + b*x2 + c;
}