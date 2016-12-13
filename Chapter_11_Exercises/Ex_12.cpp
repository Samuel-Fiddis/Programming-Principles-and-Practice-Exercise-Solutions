#include "../../std_lib_facilities.h"

vector<string> reverse_words(const string& s)
{
	istringstream buffer{ s };
	vector<string> reverse;
	
	for (string temp; buffer >> temp;)
		reverse.push_back(temp);

	string temp;
	for (int i = 0; i < reverse.size()/2; i++)
	{
		temp = reverse[i];
		reverse[i] = reverse[reverse.size() - 1 - i];
		reverse[reverse.size() - 1 - i] = temp;
	}

	return reverse;
}

void reverse_characters(string& s)
{
	char temp;
	for (int i = 0; i < s.size()/2;i++)
	{
		temp = s[i];
		s[i] = s[s.size() - 1 - i];
		s[s.size() - 1 - i] = temp;
	}
}

int main()
{
	ifstream file  {"test.txt"};
	if (!file) cerr << "error!";

	ofstream to_file{ "output.txt" };
	if (!to_file) cerr << "error!";

	string test;
	//while (getline(file, test))
	//{
	//	vector<string> test2 = reverse_words(test);

	//	for (int i = 0; i < test2.size(); i++)
	//	{
	//		to_file << test2[i] << ' ';
	//	}
	//	to_file << '\n';
	//}

	while (getline(file, test))
	{
		reverse_characters(test);

		to_file << test << '\n';
	}
}