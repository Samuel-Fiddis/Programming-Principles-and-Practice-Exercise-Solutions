#include <list>
#include <algorithm>

int main()
{
	std::list<int> ilist;
	ilist.push_back(1);
	ilist.push_back(2);
	ilist.push_back(3);

	std::list<int>::iterator findIter = std::find(ilist.begin(), ilist.end(), 1);
}