#include "../../std_lib_facilities.h"

vector<double> copier(list<int> & l)
{
	vector<double> d(l.size());
	auto p = l.begin();
	auto q = d.begin();
	while (p != l.end())
	{
		*q = *p;
		++q;
		++p;
	}
	return d;
}

int main()
{
	list<int> li = { 1,2,4,8,16,32 };
	li.push_front(0);
	vector<double> vd = copier(li);
	for (int i = 0; i < vd.size(); ++i)
	cout << vd[i] << '\n';
}