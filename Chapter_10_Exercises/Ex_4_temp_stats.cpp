# include "../../std_lib_facilities.h"

class Readings {
public:
	Readings(int x, double y, char c)
		:hour{ x }, temp{ y }, unit{ c } {
		if (!(unit == 'C' || unit == 'c' || unit == 'F' || unit == 'f')) error("Unit Incorrect");
	}
	int hour;
	double temp;
	char unit;
};

void fill_from_file(vector<Readings>& temps, const string& name)
{
	ifstream ist{ name };
	if (!ist) error("Could not open file ", name);
	int hour;
	double temp;
	char unit;
	while (ist >> hour >> temp >> unit)
	{
		if (unit == 'C' || unit == 'c')
		{
			temp = 1.8*temp + 32;
			unit = 'F';
		}
		temps.push_back(Readings{ hour,temp,unit });
	}
}

double median_readings(vector<Readings> temps)
{
	int size = temps.size();
	vector<double> temp;
	for (int i = 0; i < size; ++i)
		temp.push_back(temps[i].temp);
	sort(temp);

	if (size % 2 == 1)
		return temp[size / 2];
	else return (temp[size / 2] + temp[size / 2 - 1]) / 2.0;
}

double mean_readings(const vector<Readings>& temps)
{
	double sum_temps = 0;
	for (int i = 0; i < temps.size(); ++i)
	{
		sum_temps += temps[i].temp;
	}
	return sum_temps / temps.size();
}

int main()
{
	vector<Readings> read_temps;

	fill_from_file(read_temps, "raw_temps2.txt");

	cout << "The mean reading is: " << mean_readings(read_temps) << '\n';
	cout << "The median reading is: " << median_readings(read_temps) << '\n';
}