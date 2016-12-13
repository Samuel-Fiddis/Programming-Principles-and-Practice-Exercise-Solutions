# include "../../std_lib_facilities.h"

void print(const vector<int>& v)
{
	for (int i = 0; i < v.size(); ++i)
		cout << v[i] << '\n';
}

vector<int> vector_swap_v(vector<int> v)
{
	for (int i = 0; i < v.size() / 2; ++i)
		swap(v[i], v[v.size() - 1 - i]);
	return v;
}

void vector_swap_r(vector<int>& v)
{
	for (int i = 0; i < v.size()/2; ++i)
		swap(v[i], v[v.size() - 1 - i]);
}

int main()
{
	vector<int> numbers;
	int entry = 0;

	cout << "Enter a series of integers to be stored into a vector: ";
		while (cin >> entry)
		{
			if (entry == ';') break;
			else numbers.push_back(entry);
		}

		cout << "These numbers reversed using pass by value are: ";
		vector<int> swap(numbers.size());
		swap = vector_swap_v(numbers);
		print(swap);

		cout << "These numbers reversed using pass by reference are: ";
		vector_swap_r(numbers);
		print(numbers);
}