# include "../../std_lib_facilities.h"

void age_prompt(const vector<string>& names, vector<double>& ages)
{
	double temp;
	for (int i = 0; i < names.size(); ++i)
	{
		cout << "What is the age of " << names[i] << "? ";
		cin >> temp;
		ages.push_back(temp);
	}
}

void print(const vector<string>& names, const vector<double>& ages)
{
	if (names.size() != ages.size()) cerr << "vectors not the same size!";
	for (int i = 0; i < names.size(); ++i)
		cout << names[i] << ' ' << ages[i] << '\n';
}

vector<double> ages_sort(vector<string>& names, vector<double> ages)
{
	vector<string> names_copy = names;

	sort(names.begin(), names.end());

	vector<double> ages_sort(ages.size());

	for (int i = 0; i < names.size(); ++i)
	{
		for (int b = 0; b < names.size(); ++b)
		{
			if (names[i] == names_copy[b])
			{
				ages_sort[i] = ages[b];
			}
		}
	}
	return ages_sort;
}

int main()
{
	vector<string> names;
	string name;
	vector<double> ages;

	cout << "Please enter a number of names of people who's age is to be recorded (please enter a ';' to stop input): ";
	while (cin >> name)
	{
		if (name == ";") break;
		else names.push_back(name);
	}

	age_prompt(names, ages);  // Ask for each persons names

	cout << "These names with their ages are:\n";

	print(names, ages);

	ages = ages_sort(names, ages); // Sort both the names and the ages of the people
	
	cout << "These names sorted in alphabetical order with their ages are:\n";

	print(names, ages);

}