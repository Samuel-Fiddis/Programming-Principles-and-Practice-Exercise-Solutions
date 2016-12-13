#include "../../std_lib_facilities.h"

void to_lower(char* s)
{
	for (int i = 0; s[i] != '0'; ++i)
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
}

int main()
{
	char* hello = new char[15] {"Hello, World!0"};
	to_lower(hello);

	cout << hello << '\n';
}