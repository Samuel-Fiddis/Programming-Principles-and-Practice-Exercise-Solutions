#include "../../std_lib_facilities.h"
#include "Unique_ptr.h"
#include"Count_ptr.h"

void f(Count_ptr<int>& c)
{
	Count_ptr<int> d{ c };
	d.set_pointer(2);
	cout << d.count() << '\n';
}

int main()
{
	int* p = new int[3] { 1, 2, 3 };
	Unique_ptr<int> u{ p };
	Unique_ptr<int> v{ p };

	cout << *u << '\n';
	cout << *v << '\n';

	int* a = u.release();
	int* b = v.release();

	cout << *a << '\n';
	cout << *b << '\n';

	Count_ptr<int> c {new int[2]{ 1,2 }};
	cout << c.count() << '\n';
}