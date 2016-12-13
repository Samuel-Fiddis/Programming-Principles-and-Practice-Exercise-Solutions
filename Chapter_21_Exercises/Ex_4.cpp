#include "../../std_lib_facilities.h"

template<typename In, typename Pred>
int my_count_if(In first, In last, Pred pred)
{
	int i = 0;
	while (first != last) {
		if (pred(*first)) ++i;
		++first;
	}
	return i;
}


class number_of_char
{
	int num;
public:
	number_of_char(int n) : num{ n } {}

	bool operator() (const string& s)
	{
		if (s.size() == num) return true;
		else return false;
	}
};

int main()
{
	ifstream is{ "In.txt" };                  // open input stream
	ofstream os{ "Out.txt" };                    // open output stream

	istream_iterator<string> ii{ is };                // make input iterator for stream
	istream_iterator<string> eos;                  // input sentinel
	ostream_iterator<string> oo{ os," " }; // make output iterator for stream

	vector<string> b{ ii,eos };                         // b is a vector initialized from input
	copy(b.begin(), b.end(), oo);                 // copy buffer to output

	cout << "Number of times a string 3 charaters long is given in this sequence is: " << my_count_if(b.begin(), b.end(), number_of_char(3)) << '\n';
}