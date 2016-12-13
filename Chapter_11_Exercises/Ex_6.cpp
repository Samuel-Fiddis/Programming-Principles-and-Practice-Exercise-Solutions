#include "../../std_lib_facilities.h"

//INCOMPLETE

void whitespace(string& s)
{
	for (char& c: s)
		switch (c)
		case'.': case ';': case',': case'?': case'-': case'\'': c = ' ';
	s = s;
	if (s == "don t"|| s == " don t" || s == "don t " || s == " don t ") s = "do not";
	else if (s == "can t" || s == " can t" || s == "can t " || s== " can t ") s = "cannot";
}

int main()
{
	string line, line2;
	int i = 0;
	istringstream buffer;

	cout << "Please enter a series of strings: ";
	getline(cin, line);
	buffer.str(line);
	while (buffer >> line2)
	{
		whitespace(line2);
		cout << line2 << ' ';
	}
}