# include "../../std_lib_facilities.h"

class Readings {
public:
	Readings(int x, double y)
		:hour{ x }, temp{ y } {}
	int hour;
	double temp;
};

void fill_to_file(vector<Readings>& temps, const string& name)
{
	ofstream ost{ name };
	if (!ost) error("Could not open file ", name);
	for (int i = 0; i < temps.size(); ++i)
	{
		ost << temps[i].hour << ' ' << temps[i].temp << '\n';
	}
}

int main()
{
	vector<Readings> store_temps;
	int hour_reading;
	double temp_reading;
	char terminator = ';';

	cout << "Please enter a number of hours and temperatures and the character ';' to exit: ";
	while (cin >> hour_reading >> temp_reading)
	{
		store_temps.push_back(Readings{ hour_reading,temp_reading });
		if (!cin)
		{
			cin.clear();
			char ch;
			cin >> ch;
			if (!cin || ch != terminator) error("Bad or wrong terminator.");
			else if (ch == terminator)break;
		}
	}
	fill_to_file(store_temps, "raw_temps.txt");
}