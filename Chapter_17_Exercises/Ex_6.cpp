#include "../../std_lib_facilities.h"

int main()
{
	int j = 0;
	int i = 0;
	while(true)
	{
		char* p = new char[i*i];
		j += i*i;
		cout << i << '\t' << j << '\n';
		++i;
	}
}