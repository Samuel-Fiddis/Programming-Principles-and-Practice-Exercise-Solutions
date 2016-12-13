#include "../../std_lib_facilities.h"

double maxv(vector<double> x)
{
	sort(x.begin(), x.end());
		return x[x.size() - 1];
}