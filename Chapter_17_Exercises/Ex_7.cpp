#include "../../std_lib_facilities.h"

char* read_to_array()
{
	int i = 0;
	char c = '0';
	char* n = nullptr;
	char* p = nullptr;

	while (true)
	{
		cin.get(c);
		char* m = new char[i];

		if (i > 0)
			for (int j = 0; j <= i; ++j)
				m[j] = p[j];

		m[i] = c;

		n = p;
		p = m;
		m = nullptr;

		++i;

		if (c == '!') break;
	}
	return p;
}

int main()
{
	char* p = read_to_array();

	cout << p;
}