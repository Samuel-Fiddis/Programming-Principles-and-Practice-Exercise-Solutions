#include "../../std_lib_facilities.h"

void print(string s, const vector<int>& v)
{
	for (int i = 0; i < v.size(); ++i)
		cout << s << ' ' << v[i] << '\n';
}

int main()
{
	vector<int> numbers;
	string name;
	int entry;

	cout << "What would you like the name of this vector to be? ";
	cin >> name;

	cout << "\nPlease enter a series of integers to put into the Vector. Please enter ; to stop input. ";

	while (cin >> entry)
	{
		if (entry == ';') break;
		else numbers.push_back(entry);
	}

	print(name, numbers);

}