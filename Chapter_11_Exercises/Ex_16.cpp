#include "../../std_lib_facilities.h"

void print(vector<int> n)
{
	sort(n);
	int count = 1;

	for (int i = 1; i < n.size(); ++i)
	{
		if (n[i-1] == n[i]) ++count;
		else
		{
			cout << n[i-1];
			if (count > 1)
			{
				cout << '\t' << count << '\n';
				count = 1;
			}
			else cout << '\n';
		}
	}
}

int main()
{
	string name;
	int temp;
	vector<int> numbers;

	cout << "Please enter the file name: ";
	cin >> name;

	ifstream ist{ name };

	while (ist >> temp)
		numbers.push_back(temp);

	print(numbers);
}