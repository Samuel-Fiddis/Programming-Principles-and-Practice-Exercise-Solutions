#include "../../std_lib_facilities.h"

void main9()
{

	vector<char> digits;
	vector<int> numbers;
	int convert;
	vector<string> numerics{" in tens of thousands ", " in thousands "," in hundreds "," in tens and "," in ones\n" };
	cout << "Please input a number of digits (e.g. 123): ";
	int i = 0;

	for (char temp; cin >> temp;)
	{
		digits.push_back(temp);
	}

	for (int i = 0; i < digits.size(); ++i)
	{
		convert = digits[i] - '0';
		numbers.push_back(convert);
		cout << numbers[i] << numerics[numerics.size()-digits.size() +i];
	}
}