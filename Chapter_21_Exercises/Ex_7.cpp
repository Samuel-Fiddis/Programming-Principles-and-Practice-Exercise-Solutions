#include "../../std_lib_facilities.h"

bool binary_find_vi(const vector<int>& v, int i)
{
	int mid = v.size() / 2;
	int begin = 0;
	int end = v.size() - 1;
	while (v[mid] != i && mid != begin && mid != end)
	{
		if (v[mid] < i)
		{
			begin = mid;
			mid = begin + ((end - begin) / 2);
		}
		else if (v[mid]> i)
		{
			end = mid;
			mid = begin + ((end - begin) / 2);
		}
	}
	if (v[mid] == i)
	{
		return true;
	}
	else return false;
}

void advance(list<string>::iterator& l,int i)
{
	while (i > 0)
	{
		++l;
		--i;
	}
	while (i < 0)
	{
		--l;
		++i;
	}
}

bool binary_find_ls(const list<string>& ls, string s)
{
	auto begin = ls.begin();
	auto mid = ls.begin();
	int step = ls.size() / 2;
	advance(mid, step);
	auto end = ls.end();
	while (*mid != s && mid != begin && mid != end)
	{
		if (*mid < s)
		{
			begin = mid;
			step = step / 2;
			advance(mid,step);
		}
		else if (*mid > s)
		{
			end = mid;
			step = step / 2;
			advance(mid,-step);
		}
	}
	if (*mid == s)
	{
		return true;
	}
	else return false;
}

int main()
{
	vector<int> vi{ 1,2,4,8,16,32,64,128,256,512,1024,2048,4096 };

	int i = 1023;

	if(binary_find_vi(vi, i)) cout << "We found the value ";
	else cout << "Couldn't find the value ";
	cout << i << " in this vector.\n";

	list<string> ls{ "What","am","I","doing","with","my","life","?","I","should","just","quit","this","stupid","job!" };

	ls.sort();

	string s = "am";

	if (binary_find_ls(ls, s)) cout << "We found the value ";
	else cout << "Couldn't find the value ";
	cout << s << " in this list.\n";
}