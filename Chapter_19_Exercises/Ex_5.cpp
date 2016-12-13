#include "../../std_lib_facilities.h"

class Int {
	int i;

public:
	explicit Int(int n) : i{ n } {}
	int get() const { return i; }
	Int& operator=(const Int a);
};


Int& Int::operator=(const Int a)
{
	Int c(a.get());
	return c;
}

Int& operator+(const Int a, const Int b)
{
	Int c(a.get() + b.get());
	return c;
}

Int& operator-(const Int a, const Int b)
{
	Int c(a.get() - b.get());
	return c;
}

Int& operator*(const Int a, const Int b)
{
	Int c(a.get() * b.get());
	return c;
}

Int& operator/(const Int a, const Int b)
{
	Int c(a.get() / b.get());
	return c;
}

ostream& operator<<(ostream& os, const Int& a)
{
	os << a.get();
	return os;
}

int main()
{
	Int a(4);
	Int b = a;
	Int c = a + b;
	Int d(2);
	Int e = d*a;
	Int f = b / d;

	cout << a << '\n';
	cout << b << '\n';
	cout << c << '\n';
	cout << d << '\n';
	cout << e << '\n';
	cout << f << '\n';
}