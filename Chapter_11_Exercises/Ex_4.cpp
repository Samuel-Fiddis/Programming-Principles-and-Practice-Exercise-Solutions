#include "../../std_lib_facilities.h"

int main()
{
	cin.unsetf(ios::hex);
	cin.unsetf(ios::dec);
	cin.unsetf(ios::oct);

	int temp;
	vector<int> integers;
	vector<char> base;


	cout << "Please enter a number of integers in dec, hex or oct form followed by ';' to exit: ";

		for (char c; cin.get(c);)
		{
			if (c == ';') break;
			else if (c == '0')
			{
				cin.get(c);
				if (c == 'x' || c == 'X')
				{
					cin >> hex >> temp;
					integers.push_back(temp);
					base.push_back('h');
				}
				else if (isdigit(c))
				{
					cin.unget();
					cin >> oct >> temp;
					integers.push_back(temp);
					base.push_back('o');
				}
			}
			else if (isdigit(c))
			{
				cin.unget();
				cin >> dec >> temp;
				integers.push_back(temp);
				base.push_back('d');
			}
		}

		for (int i = 0; i < integers.size(); ++i)
		{
			if (base[i] == 'd')
				cout << setw(6) << dec << integers[i] << "\tIn decimal converts to " << integers[i] << " In decimal\n";
			else if (base[i] == 'h')
				cout << setw(6) << hex << integers[i] << "\tIn hexadecimal converts to " << dec << integers[i] << " In decimal\n";
			else if (base[i] == 'o')
				cout << setw(6) << oct << integers[i] << "\tIn octal converts to " << dec << integers[i] << " In decimal\n";
		}
}