#include "../../std_lib_facilities.h"

vector<string> split(const string& s, const string& w)
{
	istringstream buffer;
	vector<string> splits;
	string temp;

	buffer.str(s);
	while (buffer >> temp)
	{
		for (char& c1 : temp)
			for (char c2 : w)
				if (c1 == c2) c1 = ' ';
		splits.push_back(temp);
	}
	return splits;
}

int main()
{
	string line, white;
	vector<string> splits;

	cout << "Please enter a sentance: ";
	getline(cin, line);

	cout << "Please enter white space charcters: ";
	getline(cin, white);

	splits = split(line,white);

	for (int i = 0; i < splits.size(); ++i)
	{
		cout << splits[i] << ' ';
	}
}