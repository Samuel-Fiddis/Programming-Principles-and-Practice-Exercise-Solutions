# include "../../std_lib_facilities.h"

class Readings {
public:
	Readings(int x, double y, char c)
		:hour{ x }, temp{ y }, unit{ c } {
		if(!(unit == 'C' || unit == 'c' || unit == 'F' || unit == 'f')) error("Unit Incorrect");
	}
	int hour;
	double temp;
	char unit;
};

void fill_to_file(vector<Readings>& temps, const string& name)
{
	ofstream ost{ name };
	if (!ost) error("Could not open file ", name);
	for (int i = 0; i < temps.size(); ++i)
	{
		ost << temps[i].hour << ' ' << temps[i].temp << ' ' << temps[i].unit << '\n';
	}
}

int main()
{
	vector<Readings> store_temps;
	int hour_reading;
	double temp_reading;
	char unit_reading;
	char terminator = ';';

	cout << "Please enter a number of hours and temperatures and the character ';' to exit: ";
	while (cin >> hour_reading >> temp_reading >> unit_reading)
	{
		store_temps.push_back(Readings{ hour_reading,temp_reading,unit_reading });
		if (!cin)
		{
			cin.clear();
			char ch;
			cin >> ch;
			if (!cin || ch != terminator) error("Bad or wrong terminator.");
			else if (ch == terminator)break;
		}
	}
	fill_to_file(store_temps, "raw_temps2.txt");
}