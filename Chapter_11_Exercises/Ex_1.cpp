#include "../../std_lib_facilities.h"

int main()
{
	string name_in,name_out,line;
	
	cout << "Please enter input file name: ";
	cin >> name_in;
	cout << "Please enter the output file name: ";
	cin >> name_out;


	ifstream ist{ name_in };
	if (!ist) error("Input failed");
	
	ofstream ost{ name_out };
	if (!ost) error("Input failed");

	while (getline(ist, line))
	{
		for (char& ch : line)
			ch = tolower(ch);
		cout << line << '\n';
		ost << line << '\n';
	}
}