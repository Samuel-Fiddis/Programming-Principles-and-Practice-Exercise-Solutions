#include "../../std_lib_facilities.h"

char* findx(const char* s, const char* x)
{
	//Check length of x
	int i = 0;
	while (x[i] != '0') ++i;

	//Check lenght of s
	int j = 0;
	while (s[j] != '0') ++j;

	for (int a = 0; a < j; ++a)
	{
		if (s[a] == x[0])
		{
			for (int b = 0; b < i; ++b)
			{
				if (s[a + b] != x[b]) break;
				else if (b == i-1) return const_cast<char*>(&s[a]);
			}
		}
	}
	return nullptr;
}

int main()
{
	char* d = new char[28]{ "Hello, World! How are you?0" };
	char* e = new char[4]{ "lo0" };

	char* q = findx(d, e);

	if(q) cout << "The sting segment is at: " << q << '\n';

}