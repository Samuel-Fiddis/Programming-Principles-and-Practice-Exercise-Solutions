# include "../../std_lib_facilities.h"

void print(const vector<string>& v)
{
	for (int i = 0; i < v.size(); ++i)
		cout << v[i] << ' ';
	cout << '\n';
}

vector<string> vector_swap_v(vector<string> v)
{
	for (int i = 0; i < v.size() / 2; ++i)
		swap(v[i], v[v.size() - 1 - i]);
	return v;
}

void vector_swap_r(vector<string>& v)
{
	for (int i = 0; i < v.size() / 2; ++i)
		swap(v[i], v[v.size() - 1 - i]);
}

int main()
{
	vector<string> numbers;
	string entry;

	cout << "Enter a series of words to be stored into a vector, place a ';' at the end of the sentance to complete input: ";
	while (cin >> entry)
	{
		if (entry == ";") break;
		else numbers.push_back(entry);
	}

	cout << "These numbers reversed using pass by value are: ";
	vector<string> swap(numbers.size());
	swap = vector_swap_v(numbers);
	print(swap);

	cout << "These numbers reversed using pass by reference are: ";
	vector_swap_r(numbers);
	print(numbers);
}