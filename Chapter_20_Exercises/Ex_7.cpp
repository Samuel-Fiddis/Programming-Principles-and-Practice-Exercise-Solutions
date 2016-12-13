// 7. Find the lexicographical last string in an unsorted vector<string>.

#include "../../std_lib_facilities.h"

template<typename Iter>
Iter high(Iter first, Iter last)
{
	auto highest = first;
	auto p = first;
	while (p != last)
	{
		if (*highest < *p) highest = p;
		++p;
	}
	return highest;
}

int main()
{
	vector<string> vs = { "Hey", "how", "zoltan" , "are", "you?"};
	
	auto p = high(vs.begin(), vs.end());
	cout << *p << '\n';
}