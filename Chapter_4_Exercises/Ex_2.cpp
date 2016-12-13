#include "../../std_lib_facilities.h"

// read some temperatures into a vector

void main2()

{

	vector<double> temps;                  // temperatures

	for (double temp; cin >> temp; )    // read into temp

		temps.push_back(temp);     // put temp into vector

	cout << "The number of elements in the vector is: " << temps.size() << '\n';

	// compute mean temperature:

	double sum = 0;

	for (int x : temps) sum += x;

	cout << "Average temperature: " << sum / temps.size() << '\n';


	// compute median temperature:

	sort(temps);                                     // sort temperatures

	cout << "Median temperature: ";
	
	if (temps.size() % 2 == 1)
		cout << temps[temps.size() / 2] << '\n';
	else
		cout << (temps[temps.size() / 2] + temps[(temps.size() / 2) - 1]) / 2 << '\n';

}