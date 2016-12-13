#include "../../std_lib_facilities.h"

class Rational {
public:
	Rational(int d, int n);
	int Denom() const{ return denom; }
	int Numer() const{ return numer; }
	double Rational_to_Double(Rational a);
	
private:
	int denom;
	int numer;
};

Rational::Rational(int n, int d) :
	denom{ d }, numer{ n } {}

double Rational::Rational_to_Double(Rational a)
{
	double A = a.Numer() / a.Denom();
	return A;
}

Rational& operator+(Rational a, Rational b)
{
	int n = a.Numer()*b.Denom() + a.Denom()*b.Numer();
	int d = a.Denom()*b.Denom();
	return Rational(n, d);
}

Rational& operator-(Rational a, Rational b)
{
	int n = a.Numer()*b.Denom() - a.Denom()*b.Numer();
	int d = a.Denom()*b.Denom();
	return Rational(n, d);
}

Rational& operator*(Rational a, Rational b)
{
	int n = a.Numer()*b.Numer();
	int d = a.Denom()*b.Denom();
	return Rational(n, d);
}

Rational& operator/(Rational a, Rational b)
{
	int n = a.Numer()*b.Denom();
	int d = a.Denom()*b.Numer();
	return Rational(n, d);
}

bool operator==(Rational a,Rational b)
{
	double A = a.Numer() / a.Denom();
	double B = b.Numer() / b.Denom();
	return A == B;
}

ostream& operator<<(ostream& os,Rational a)
{
	os << a.Numer() << '/' << a.Denom();
	return os;
}

int main()
{
	Rational test1(2, 7);
	cout << test1 << '\n';

	Rational test2(3, 4);
	cout << "multiplication: " << test1*test2 << '\n';
	cout << "devision: " << test1/test2 << '\n';
	cout << "additon: " << test1 + test2 << '\n';
	cout << "subtraction: " << test1 - test2 << '\n';
}