#include "../../std_lib_facilities.h"

template <class T, class V> class Pair {
public:
	Pair(T t,V v):
		v1{ t }, v2{ v }{}

	T value1() const { return v1; }
	V value2() const { return v2; }

private:
	T v1;
	V v2;
};

template <class T, class V> ostream& operator<<(ostream& os,const Pair<T,V>& p)
{
	os << p.value1() << '\t' << p.value2();
	return os;
}

int main()
{
	vector<Pair<int, string>> v1;
	v1.push_back({ 1,"Hello" });
	v1.push_back({ 2,"World" });
	v1.push_back({ 3,"Goodbye!" });
	for (int i = 0; i < v1.size(); ++i) cout << v1[i] << '\n';

	vector<Pair<double, char>> v2;
	v2.push_back({ 1.0,'H' });
	v2.push_back({ 1.1,'e' });

	for (int i = 0; i < v2.size(); ++i) cout << v2[i] << '\n';
}