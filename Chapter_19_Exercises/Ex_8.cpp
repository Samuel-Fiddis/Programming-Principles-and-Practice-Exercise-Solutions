// Implement an allocator (§19.3.7) using the basic allocation functions malloc() and free() (§B.11.4).
// Get vector as defined by the end of §19.4 to work for a few simple test cases. 
// Hint: Look up “placement new” and “explicit call of destructor” in a complete C++ reference.

#include "../../std_lib_facilities.h"
#include "Vector.h"

int main()
{
	Vectr<int> v = Vectr<int>(3);
	v[1] = 1;
	v.push_back(5);

	Vectr<int> v1 = v;

	for (int i = 0; i < v.size(); ++i) cout << v[i];

	v1.resize(2);

	for (int i = 0; i < v1.size(); ++i) cout << v[i];

}