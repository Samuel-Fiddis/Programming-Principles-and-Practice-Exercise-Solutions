#include "../../std_lib_facilities.h"

// Needs error checking

void print_table(ifstream& ist, ofstream& ost)
{
	double temp;
	int i = 1;
	while (ist >> temp)
	{
		ost << scientific << setprecision(8) << setw(20) << temp << '|';
		if (i % 4 == 0) ost << '\n';
		++i;
	}
}

int main()
{
	cout << "Please enter the neame of the input file: ";
	string in, out;
	cin >> in;

	ifstream input{ in };

	cout << "Please enter the name of the output file: ";
	cin >> out;

	ofstream output{ out };

	print_table(input, output);
}