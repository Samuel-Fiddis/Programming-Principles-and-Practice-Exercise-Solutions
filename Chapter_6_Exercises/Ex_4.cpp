#include "../../std_lib_facilities.h"

class Name_value {
public:
	string Name;
	int Score;
};

Name_value get() {
	
	Name_value NS;
	string n_temp;
	int s_temp;

	cin >> n_temp;
	if (n_temp == ";")
	{
		NS.Name = n_temp;
		NS.Score = 0;
		return NS;
	}
	cin >> s_temp;

	NS.Name = n_temp;
	NS.Score = s_temp;
	return NS;
}

int main()
{
	vector<Name_value> ns;
	
	cout << "Please enter a Name followed by a Score. Enter ';' to exit and see all scores.\n";

	while (cin)
	{
		ns.push_back(get());
		if (ns[ns.size()-1].Name == ";")
			break;
	}

	cout << "The scores are:\n";

	for (int i = 0; i < ns.size()-1; ++i)
	{
		cout << ns[i].Name << " " << ns[i].Score << "\n";
	}
}