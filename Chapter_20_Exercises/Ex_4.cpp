#include "../../std_lib_facilities.h"

double* get_from_jack(int* count) // Jack puts doubles into an array and returns the number of elements in *count
{
	ifstream jack{ "Jack_File.txt" };
	double* d = new double[*count];
	for (int c = 0; c < (*count); ++c)
		jack >> d[c];
	return d;
};

vector<double>* get_from_jill()	// Jill fills the vector
{
	ifstream jill{ "Jill_File.txt" };
	vector<double>* v = new vector<double>;
	double i = 0;
	while (jill >> i)
		v->push_back(i);
	return v;
};

template<typename Iterator>
Iterator high(Iterator first, Iterator last)
// return an iterator to the element in [first:last) that has the highest value
{
	Iterator high = first;
	for (Iterator p = first; p != last; ++p)
		if (*high<*p) high = p;
	return high;
}

void fct()
{
	int jack_count = 10;
	double* jack_data = get_from_jack(&jack_count);
	vector<double>* jill_data = get_from_jill();

	double* jack_high = high(jack_data, jack_data + jack_count);
	vector<double>& v = *jill_data;
	double* jill_high = high(&v[0], &v[0] + v.size());
	cout << "Jill's high " << *jill_high << "; Jack's high " << *jack_high << '\n';
	// . . .
	delete[] jack_data;
	delete jill_data;
}

int main()
{
	fct();
}