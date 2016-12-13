#include "../../std_lib_facilities.h"
#include <map>
#include <unordered_map>

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

template<typename In, typename Pred>
int my_count_if(In first, In last, Pred pred)
{
	int i = 0;
	while (first != last) {
		if(pred(*first)) ++i;
		++first;
	}
	return i;
}

template<typename In, typename T, typename BinOp>
// requires Input_iterator<In>() && Number<T>()
//        && Binary_operator<BinOp,Value_type<In>,T>()
T accumulate(In first, In last, T init, BinOp op)
{
	while (first != last) {
		init = op(init, *first);
		++first;
	}
	return init;
}

template<typename In, typename In2, typename T, typename BinOp,	typename BinOp2>
	// requires Input_iterator<In> && Input_iterator<In2> && Number<T>
	//        && Binary_operation<BinOp,T, Value_type<In>()
	//        && Binary_operation<BinOp2,T, Value_type<In2>()
	T inner_product(In first, In last, In2 first2, T init, BinOp op, BinOp2 op2)
{
	while (first != last) {
		init = op(init, op2(*first, *first2));
		++first;
		++first2;
	}
	return init;
}

double weighted_value(
	const pair<string, double>& a,
	const pair<string, double>& b
	)   // extract values and multiply
{
	return a.second * b.second;
}

struct Record {
	double unit_price;
	int units;
	Record(int i, double d): unit_price { d }, units{ i } {}
};

class price
{
public:
	double operator() (double v, const Record& r) {
		return v + (r.unit_price * r.units);    // calculate price and accumulate
	}
};

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
	vector<Record> vr;
	vr.push_back(Record(3, 2.5));
	vr.push_back(Record(7, 2.25));
	vr.push_back(Record(1, 13.5));
	vr.push_back(Record(14, 1.15));

	double total = accumulate(vr.begin(), vr.end(), 0.0, price());

	cout << total << '\n';

	map<string, double> dow_price = {   // Dow Jones Industrial index (symbol,price);
										// for up-to-date quotes see
										// www.djindexes.com
		{ "MMM",81.86 },
		{ "AA",34.69 },
		{ "MO",54.45 },
		// . . .
	};

	map<string, double> dow_weight = {    // Dow (symbol,weight)
		{ "MMM", 5.8549 },
		{ "AA",2.4808 },
		{ "MO",3.8940 },
		// . . .
	};

	map<string, string> dow_name = {     // Dow (symbol,name)
		{ "MMM","3M Co." },
		{ "AA","Alcoa Inc." },
		{ "MO","Altria Group Inc." },
		// . . .
	};

	// write price for each company in the Dow index:

	for (const auto& p : dow_price) {
		const string& symbol = p.first;                         // the “ticker” symbol
		cout << symbol << '\t'
			<< p.second << '\t'
			<< dow_name[symbol] << '\n';
	}

	double dji_index =	inner_product(dow_price.begin(), dow_price.end(),     // all companies
			dow_weight.begin(),              // their weights
			0.0,                                             // initial value
			plus<double>(),                     // add (as usual)
			weighted_value);                   // extract values and weights
											   // and multiply

	cout << dji_index << '\n';

		ifstream is{ "In.txt" };                  // open input stream
	ofstream os{ "Out.txt" };                    // open output stream

	istream_iterator<string> ii{ is };                // make input iterator for stream
	istream_iterator<string> eos;                  // input sentinel
	ostream_iterator<string> oo{ os," " }; // make output iterator for stream

	vector<string> b{ ii,eos };                         // b is a vector initialized from input
	//sort(b.begin(), b.end());                           // sort the buffer
	copy(b.begin(), b.end(), oo);                 // copy buffer to output
	
	cout << "Number of times \"is\" is given in this sequence is: " << my_count(b.begin(), b.end(), "is") << '\n';
	cout << "Number of times a string 3 charaters long is given in this sequence is: " << my_count_if(b.begin(), b.end(), number_of_char(3)) << '\n';


}