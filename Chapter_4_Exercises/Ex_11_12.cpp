#include "../../std_lib_facilities.h"

void main11_12()
{
	vector<int> primes = { 2, 3, 5 };
	int remainder = 1;
	int max = 0;

	cout << "Please enter the number for which you want to view all lesser prime numbers: ";
	cin >> max;
	cout << '\n';

	for (int i = 6; i <= max; ++i)
	{

		for (int a = 0; a < primes.size(); ++a)
		{
			remainder = i%primes[a];
			if (remainder == 0)
				break;
			if (a == primes.size() - 1)
			{
				primes.push_back(i);
			}
		}
	}

	for (int x = 0; x < primes.size(); ++x)
		cout << primes[x] << ", ";
}