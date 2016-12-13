#include "../../std_lib_facilities.h"

// read some temperatures into a vector

void main3()

{

	vector<double> temps;                  // temperatures

	for (double temp; cin >> temp; )    // read into temp

		temps.push_back(temp);     // put temp into vector

	cout << "The number of elements in the vector is: " << temps.size() << '\n';

	// compute mean temperature:

	double sum = 0;

	for (int x : temps) sum += x;

	cout << "Total distance: " << sum << '\n';
	
	// compute median temperature:

	sort(temps);                                     // sort temperatures

	cout << "Smallest distance: " << temps[0] << '\n';

	cout << "Largest distance: " << temps[temps.size()-1] << '\n';

	cout << "Average distance: " << sum / temps.size() << '\n';

	cout << "Median distance: ";

	if (temps.size() % 2 == 1)
		cout << temps[temps.size() / 2] << '\n';
	else
		cout << (temps[temps.size() / 2] + temps[(temps.size() / 2) - 1]) / 2 << '\n';

	
}