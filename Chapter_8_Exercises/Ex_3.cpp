#include "../../std_lib_facilities.h"

void print(string s, const vector<int>& v)
{
	for (int i = 0; i < v.size(); ++i)
		cout << s << ' ' << v[i] << '\n';
}

void fibonaci(int x, int y, vector<int>& v, int n)
{
	v.push_back(y);
	v.push_back(x);
	for (int i = 1; i < n; ++i)
	{
		v.push_back(v[i - 1] + v[i]);
	}
}

int main()
{
	vector<int> numbers;
	string name;
	int entry1 = 0;
	int entry2 = 0;
	int n;

	cout << "Enter two numbers to begin a fibonaci sequence. ";
	cin >> entry1 >> entry2;

	cout << "\nPlease the number of integers for this fibonaci sequence. ";
	cin >> n;

	cout << " The fibonacci sequence for these two starting numbers is: ";
	fibonaci(entry1, entry2, numbers, n);

	print(name, numbers);

}