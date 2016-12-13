#include "../../std_lib_facilities.h"

template <class T> class Number {
	T i;

public:
	Number() : i{ T() } {}
	explicit Number(T n) : i{ n } {}
	T get() const { return i; }
};

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

template<typename T> void multi_vector(vector<T>& v1, const vector<T>& v2)
{
	int size = v1.size();
	if (v1.size() > v2.size()) size = v2.size();
	for (int i = 0; i < size; ++i) v1[i] = v1[i] * v2[i];
}

template<typename T> void add_vector(vector<T>& v1, const vector<T>& v2)
{
	int size = v1.size();
	if (v1.size() > v2.size()) size = v2.size();
	for (int i = 0; i < size; ++i) v1[i] = v1[i] + v2[i];
}

int main()
{
	Number<int> a;
	Number<int> b(3);

	a = b;

	cout << a << '\n';

	vector<Number<int>> vi1 { Number<int>(1),Number<int>(2),Number<int>(3),Number<int>(4),Number<int>(5) };
	vector<Number<int>> vi2 { Number<int>(-1),Number<int>(2),Number<int>(-3),Number<int>(4) };
	vector<double> vd1 = { 1.2,3.4,5.6,7.8,9.0 };
	vector<double> vd2 = { -1.2,3.4,-5.6,7.8,-9.0 };

	add_vector(vi1, vi2);

	for (int i = 0; i < vi1.size(); ++i) cout << vi1[i] << ", ";

	multi_vector(vd1, vd2);

	for (int i = 0; i < vd1.size(); ++i) cout << vd1[i] << ", ";
}