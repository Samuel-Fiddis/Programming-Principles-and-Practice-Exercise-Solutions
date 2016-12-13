#include "../../std_lib_facilities.h"

void main6()

{
	vector<string> numbers = { "zero","one","two","three","four","five","six","seven","eight","nine" };
	vector<string> letters = { "0","1","2","3","4","5","6","7","8","8","9" };
	string digit = "nil";

	cout << "Please enter a single integer value in numeric or word format.\n";
	cin >> digit;

	for (int i = 0; i <= 9; ++i)
	{
		if (digit == letters[i])
			cout << "This number in words is: " << numbers[i] << '\n';
		if (digit == numbers[i])
			cout << "This number in numerical format is: " << letters[i] << '\n';
	}
}
