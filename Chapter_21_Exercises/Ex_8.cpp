#include "../../std_lib_facilities.h"
#include <map>

struct Cmp_by_int {
	bool operator()(const pair<int,string>& a, const pair<int,string>& b) const
	{
		return a.first > b.first;
	}
};

int main()
{
	map<string, int> words;         // keep (word,frequency) pairs
	vector<pair<int, string>> v;

	ifstream is{ "C++ Text.txt." };
	if (!is) cerr << "Error: Could not open file.\n";

	for (string s; is >> s; )
		++words[s];                   // note: words is subscripted by a string

	for (const auto& p : words)
	{
		v.push_back({ p.second,p.first });
	}
	
	sort(v.begin(), v.end(), Cmp_by_int());


	for (const pair<int,string>& p : v)
	{
		cout << p.first << " : " << p.second << '\n';
	}
}

