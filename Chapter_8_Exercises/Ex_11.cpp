#include "../../std_lib_facilities.h"

double maxv(const vector<double>& x)
{
	double max = x[0];
	if (x.size() == 0) cerr << "Error, vector is empty.";
	else if (x.size() == 1) return max;
	else 
		for (int i = 1; i < x.size(); ++i)
		if (x[i] > max) max = x[i];
	return max;
}

double minv(const vector<double>& x)
{
	double min = x[0];
	if (x.size() == 0) cerr << "Error, vector is empty.";
	else if (x.size() == 1) return min;
	else
		for (int i = 1; i < x.size(); ++i)
			if (x[i] < min) min = x[i];
	return min;
}

double median(vector<double> x)
{
	sort(x.begin(), x.end());
	if (x.size() % 2 == 1)
		return x[(x.size() / 2) + 1];
	else
	{
		double med = (x[(x.size() / 2) - 1] + x[(x.size() / 2)]) / 2;
		return med;
	}
}

double mean(const vector<double>& x)
{
	double sum = 0;
	for (int i = 0; i < x.size(); ++i)
		sum += x[i];
	double mean = sum / x.size();
	return mean;
}

int main() 
{
	vector<double> numbers;
	double temp;
	
	cout << "Please enter a number of values to be entered into a vector: ";

	while (cin >> temp)
		numbers.push_back(temp);

	double max = maxv(numbers);
	double min = minv(numbers);
	double mean1 = mean(numbers);
	double median1 = median(numbers);

	cout << "\nThe largest number is: " << max << "\n";
	cout << "The smallest number is: " << min << "\n";
	cout << "The mean value is: " << mean1 << "\n";
	cout << "The median value is: " << median1 << "\n";
}