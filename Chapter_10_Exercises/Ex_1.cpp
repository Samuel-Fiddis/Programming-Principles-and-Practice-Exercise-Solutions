#include "../../std_lib_facilities.h"

void fill_from_file(vector<int>& points,const string& name)
{
	fstream ist( name );
	if (!ist) error("can't open input file ", name);
	int p;
	while (ist >> p)
		points.push_back(p);
}

int main()
{
	vector<int> Sum_Parts;
	int Sum = 0;

	cout << "Please enter the file name to be read: ";
	string name;
	cin >> name;

	fill_from_file(Sum_Parts, name);

	for (int i = 0; i < Sum_Parts.size(); ++i)
	{
		cout << Sum_Parts[i] << '\n';
		Sum += Sum_Parts[i];
	}
	cout << "\nThe total sum is: " << Sum << '\n';
}