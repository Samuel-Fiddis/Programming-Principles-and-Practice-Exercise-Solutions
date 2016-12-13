#include "../../std_lib_facilities.h"

class Name_pairs {
public:

	Name_pairs(vector<string> n, vector<int> a)
		: Names{ n }, Age{ a }
	{

	}

	const vector<string>& get_name() const { return Names; }
	const vector<int>& get_age() const { return Age; }
	const string& get_names(int i) const { return Names[i]; }
	const int& get_ages(int i) const { return Age[i]; }

	void read_names()
	{
		string n;
		cout << "Please enter a series of Names followed by a ';' to terminate input: ";
		while (cin >> n && n != ";")
		{
				Names.push_back(n);
		}
	};

	void read_age()
	{
		int age = 0;
		for (int i = 0; i < Names.size(); ++i)
		{
			cout << "Please enter the age of " << Names[i] << ": ";
			cin >> age;
			Age.push_back(age);
		}
	}

	void print() const
	{
		cout << "Name:    Age:\n";
		for (int i = 0; i < Names.size(); ++i)
		{
			if (Names.size() != Age.size())
			{
				cerr << "Vectors not the same size!";
				break;
			}
			cout << Names[i] << " " << Age[i] << "\n";
		}
	}

	void sort()
	{
		if (Names.size() != Age.size())
		{
			cerr << "Vectors not the same size! Cannot sort.";
			return;
		}

		string temp_name;
		int temp_age = 0;
		for (int i = 0; i < Names.size()-1; ++i)
		{
			if (Names[i] < Names[i + 1])
			{
				temp_name = Names[i];
				temp_age = Age[i];
				Names[i] = Names[i + 1];
				Age[i] = Age[i + 1];
				Names[i + 1] = temp_name;
				Age[i + 1] = temp_age;
			}
		}

	}


private:
	vector<string> Names;
	vector<int> Age;

};

ostream& operator<<(ostream& os, const Name_pairs& n)
{
	if (n.get_name().size() != n.get_age().size()) error("Vectors not the same size");
	for (int i = 0; i < n.get_name().size(); ++i)
		os << n.get_names(i) << " " << n.get_ages(i) << "\n";
	return os;
}

bool& operator==(const Name_pairs& a, const Name_pairs& b)
{
	bool t = (a.get_name() == b.get_name() && a.get_age() == b.get_age());
	return t;
}

bool& operator!=(const Name_pairs& a, const Name_pairs& b)
{
	bool t = !(a.get_name() == b.get_name() && a.get_age() == b.get_age());
	return t;
}

int main()
{
	vector<string> name_list{ "Sam","Sammy","Michael" };
	vector<int> age_list{ 26,4,93 };

	Name_pairs List1(name_list, age_list);

	List1.print();

	

	vector<string> name_list2;
	vector<int> age_list2;

	Name_pairs List2(name_list2,age_list2);

	List2.read_names();
	List2.read_age();
	List2.print();
//	List2.sort();
//	List2.print();

	if (List1 == List2) cout << "Both lists same\n";
	if (List1 != List2) cout << "Not the same\n";
}