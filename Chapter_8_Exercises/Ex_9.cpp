#include "../../std_lib_facilities.h"

double maxv(vector<double> x)
{
	sort(x.begin(), x.end());
	return x[x.size() - 1];
}

int main()
{
	vector<double> price;
	vector<double> weight;
	double temp;
	double sum = 0;

	cout << "Please enter a number of weights followed by the corresponding price per weight unit for that weight.\nWeight: ";

	for (int i = 0; cin >> temp; ++i)
	{
		if (i % 2 == 1)
		{
			price.push_back(temp);
			cout << "\nWeight or ';' to exit: ";
		}
		else if (i % 2 == 0)
		{
			weight.push_back(temp);
			cout << "\nPrice: ";
		}
		else cerr << "Error";
	}

	if (price.size() != weight.size())
		cerr << "Error, vectors not the same size.";

	for (int i = 0; i < price.size(); ++i)
		sum += price[i] * weight[i];

	cout << "The total cost is " << sum << ".\n";
	cout << "The largest weight is " << maxv(weight) << ".\n";
}