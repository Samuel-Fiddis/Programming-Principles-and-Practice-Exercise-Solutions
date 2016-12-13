#include "../../std_lib_facilities.h"



int main()
{
	string vowels = "aeiouAEIOU";

	string name_in, name_out, line;
	
	cout << "Please enter input file name: ";
	cin >> name_in;

	ifstream ist{ name_in };
	if (!ist) error("Input failed");

	cout << "Please enter output file name: ";
	cin >> name_out;

	ofstream ost{ name_out };
	if (!ost) error("Output failed");

	while (getline(ist, line))
	{
		for (char& ch : line)
			switch (ch)
			{
			case'a': case 'e': case'i': case 'o': case'u': case'A': case 'E': case 'I': case'O': case'U': break;
			default:
				ost << ch;
				break;
			}
		ost << '\n';
	}
}