#include "../../std_lib_facilities.h"

template<typename T> void add_vector(vector<T>& v1, const vector<T>& v2)
{
	int size = v1.size();
	if (v1.size() > v2.size()) size = v2.size();
	for (int i = 0; i < size; ++i) v1[i] += v2[i];
}

template<typename T> void multi_vector(vector<T>& v1, const vector<T>& v2)
{
	int size = v1.size();
	if (v1.size() > v2.size()) size = v2.size();
	for (int i = 0; i < size; ++i) v1[i] = v1[i]*v2[i];
}

int main()
{
	vector<int> vi1 = { 1,2,3,4,5 };
	vector<int> vi2 = { -1,2,-3,4};
	vector<double> vd1 = { 1.2,3.4,5.6,7.8,9.0 };
	vector<double> vd2 = { -1.2,3.4,-5.6,7.8,-9.0 };

	add_vector(vi1, vi2);

	for (int i = 0; i < vi1.size(); ++i) cout << vi1[i] << ", ";

	multi_vector(vd1, vd2);

	for (int i = 0; i < vd1.size(); ++i) cout << vd1[i] << ", ";
}