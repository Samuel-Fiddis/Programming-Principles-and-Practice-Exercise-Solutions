#include "../../std_lib_facilities.h"

template <class T> class Number {
	T i;

public:
	explicit Number(T n) : i{ n } {}
	T get() const { return i; }
	Number& operator=(const Number a);
	Number& operator=(const T a);
};


template <class T> Number<T>& Number<T>::operator=(const Number<T> a)
{
	Number<T> c(a.get());
	return c;
}

template <class T> Number<T>& Number<T>::operator=(const T a)
{
	Number<T> c(a);
	return c;
}

template <class T> Number<T>& operator+(const Number<T> a, const Number<T> b)
{
	Number<T> c(a.get() + b.get());
	return c;
}

template <class T> Number<T>& operator-(const Number<T> a, const Number<T> b)
{
	Number<T> c(a.get() - b.get());
	return c;
}

template <class T> Number<T>& operator*(const Number<T> a, const Number<T> b)
{
	Number<T> c(a.get() * b.get());
	return c;
}

template <class T> Number<T>& operator/(const Number<T> a, const Number<T> b)
{
	Number<T> c(a.get() / b.get());
	return c;
}

template <class T> ostream& operator<<(ostream& os, const Number<T>& a)
{
	os << a.get();
	return os;
}

int main()
{
	Number<int> a(4);
	Number<int> b = a;
	Number<int> c = a + b;
	Number<int> d(2);
	Number<int> e = d*a;
	Number<int> f = b / d;

	cout << a << '\n';
	cout << b << '\n';
	cout << c << '\n';
	cout << d << '\n';
	cout << e << '\n';
	cout << f << '\n';

	Number<double> g(4.4);
	Number<double> h = g;
	Number<double> i = g + h;
	Number<double> j(2.6);
	Number<double> k = j*g;
	Number<double> l = g / j;

	cout << g << '\n';
	cout << h << '\n';
	cout << i << '\n';
	cout << j << '\n';
	cout << k << '\n';
	cout << l << '\n';
}