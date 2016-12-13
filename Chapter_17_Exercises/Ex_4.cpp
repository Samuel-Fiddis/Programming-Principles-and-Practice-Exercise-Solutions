#include "../../std_lib_facilities.h"

char* what(const char* s)
{
	int i = 0;
	while (s[i] != 0) ++i;

	char* q = new char[i+1];
	for (int a = 0; a < i; a++)
		q[a] = s[a];
	return q;
}

int main()
{
	string hello = "Hello, World!0";
	char* p = &hello[0];

	char* q = what(p);

	for (int i = 0; i < 14; ++i) cout << q[i];
}