#include "../../std_lib_facilities.h"

int main()
{
	string ifile1, ifile2, ofile;
	vector<string> file1, file2;
	string temp;

	cout << "Please enter input file 1 name: ";
	cin >> ifile1;
	cout << "\nPlease enter input file 2 name: ";
	cin >> ifile2;

	ifstream is1{ ifile1 };
	ifstream is2{ ifile2 };
	if (!is1 || !is2) error("Cant open input files");

	cout << "\nPlease enter output file name: ";
	cin >> ofile;
	ofstream os{ ofile };
	
	while (is1>>temp) file1.push_back(temp);


	while (is2 >> temp)	file2.push_back(temp);

	for (int i = 0; i < file1.size(); ++i)
	{
		os << file1[i] << ' ';
	}

	for (int i = 0; i < file2.size(); ++i)
	{
		os << file2[i] << ' ';
	}
}