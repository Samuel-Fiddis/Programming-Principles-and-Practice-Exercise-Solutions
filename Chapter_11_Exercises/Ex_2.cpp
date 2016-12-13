#include "../../std_lib_facilities.h"

int main()
{
	string name_in, name_out, line, word;
	int x = 1;

	cout << "Please enter input file name: ";
	cin >> name_in;

	ifstream ist{ name_in };
	if (!ist) error("Input failed");

	cout << "Please enter the word you want to check for: ";
	cin >> word;
	
	while (getline(ist, line))
	{
		istringstream s{ line };
		for (string i; s >> i;)
		{
			if (i == word)
			{
				cout << x << ". " << line << '\n';
			}
		}
		++x;
	}
}