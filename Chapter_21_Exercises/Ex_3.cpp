#include "../../std_lib_facilities.h"

template<typename In, typename T>
int my_count(In first, In last, T init)
{
	int i = 0;
	while (first != last)
	{
		if (*first == init) ++i;
		++first;
	}
	return i;
}

int main()
{
	ifstream is{ "In.txt" };                  // open input stream
	ofstream os{ "Out.txt" };                    // open output stream

	istream_iterator<string> ii{ is };                // make input iterator for stream
	istream_iterator<string> eos;                  // input sentinel
	ostream_iterator<string> oo{ os," " }; // make output iterator for stream

	vector<string> b{ ii,eos };                         // b is a vector initialized from input
	copy(b.begin(), b.end(), oo);                 // copy buffer to output

	cout << "Number of times \"is\" is given in this sequence is: " << my_count(b.begin(), b.end(), "is") << '\n';
}