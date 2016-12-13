#include "../../std_lib_facilities.h"

vector<string> split(const string& s)
{
	istringstream buffer;
	vector<string> splits;
	string temp;

	buffer.str(s);
	while (buffer >> temp)
		splits.push_back(temp);
	return splits;
}

int main()
{
	string line;
	vector<string> splits;

	cout << "Please enter a sentance: ";
	getline(cin, line);
	splits = split(line);
	
	for (int i = 0; i < splits.size(); ++i)
	{
		cout << splits[i] << ' ';
	}
}