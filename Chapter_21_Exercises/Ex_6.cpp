#include "../../std_lib_facilities.h"
#include <set>

struct Fruit {
	string name;
	int count;
	double unit_price;
	// . . .
	Fruit(string n, int c = 0, double up = 0.0) : name{ n }, count{ c }, unit_price{ up } {}
};

ostream &operator<<(ostream& os, const Fruit& f)
{
	os << f.name << '\t' << f.count << '\t' << f.unit_price;
	return os;
}

struct Fruit_order {
	bool operator()(const Fruit* a, const Fruit* b) const
	{
		return a->name<b->name;
	}
};

int main()
{
	set<Fruit*, Fruit_order> s;
	Fruit* b = new Fruit("Banana", 14, 0.65);
	s.insert(b);
	s.insert(new Fruit("Apple", 2, 0.35));
	s.insert(new Fruit("Orange", 5, 0.45));
	s.insert(new Fruit("Strawberry", 300, 0.06));
	s.insert(new Fruit("Peach", 16, 0.95));

	for (auto p = s.begin(); p != s.end(); ++p)
		cout << *(*p) << '\n';
}