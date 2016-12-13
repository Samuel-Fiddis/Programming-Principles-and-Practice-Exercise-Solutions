#include "../../std_lib_facilities.h"

template<typename T> class allocatr {
public:
	// . . .
	T* allocate(int n);                  // allocate space for n objects of type T
	void deallocate(T* p, int n);        // deallocate n objects of type T starting at p

	void construct(T* p, const T& v);    // construct a T with the value v in p
	void destroy(T* p);                             // destroy the T in p
};

// an almost real vector of Ts:
template<typename T,typename A = allocatr<T>>
class Vectr {      // read “for all types T” (just like in math)
	int sz;         // the size
	T* elem;        // a pointer to the elements
	int space;		// size + free space
	A alloc;		// Allocator for reserve()

public:
	Vectr() : sz{ 0 }, elem{ nullptr }, space{ 0 } { }
	explicit Vectr(int s) :sz{ s }, elem{ new T[s] }, space{ s }
	{
		for (int i = 0; i<sz; ++i) elem[i] = 0;          // elements are initialized
	}

	Vectr(const Vectr& a);                             // copy constructor
	Vectr& operator=(const Vectr& a);                  // copy assignment

	Vectr(Vectr&&);                                  // move constructor
	Vectr& operator=(Vectr&&);                       // move assignment
	
	~Vectr() { delete[] elem; }                         // destructor

	T& operator[](int n) { return elem[n]; }           // access: return reference
	const T& operator[](int n) const { return elem[n]; }

	int size() const { return sz; }                              // the current size
	int capacity() const { return space; }

	void resize(int newsize, T val = T());                                   // growth
	void push_back(const T& val);
	void reserve(int newalloc);
};


template<class T> T* allocatr<T>::allocate(int n) {
	T* p = static_cast<T*>(calloc(n,sizeof(T)));
	return p;
}

template<typename T>
void allocatr<T>::deallocate(T * p, int n)
{
	free(p);
}

template<typename T>
void allocatr<T>::construct(T * p, const T & v)
{
	*p = T(v);
}

template<typename T>
void allocatr<T>::destroy(T * p)
{
	p->~T();
}

template<typename T, typename A>
void Vectr<T, A>::reserve(int newalloc)
{
	if (newalloc <= space) return;               // never decrease allocation
	T* p = alloc.allocate(newalloc);          // allocate new space
	for (int i = 0; i<sz; ++i) alloc.construct(&p[i], elem[i]);       // copy
	for (int i = 0; i<sz; ++i) alloc.destroy(&elem[i]);                 // destroy
	alloc.deallocate(elem, space);             // deallocate old space
	elem = p;
	space = newalloc;
}

template<typename T, typename A>
void Vectr<T, A>::push_back(const T& val)
{
	if (space == 0) reserve(8);                            // start with space for 8 elements
	else if (sz == space) reserve(2 * space);      // get more space
	alloc.construct(&elem[sz], val);                 // add val at end
	++sz;                                                              // increase the size
}

template<typename T, typename A>
void Vectr<T, A>::resize(int newsize, T val = T())
{
	reserve(newsize);
	for (int i = sz; i<newsize; ++i) alloc.construct(&elem[i], val);   // construct
	for (int i = newsize; i<sz; ++i) alloc.destroy(&elem[i]);          // destroy
	sz = newsize;
}

template<typename T, typename A>
Vectr<T, A>::Vectr(const Vectr<T, A> & a)
	: sz(a.sz), elem(alloc.allocate(a.sz)), space(a.sz)
{
	for (int i = 0; i<sz; ++i)
		alloc.construct(&elem[i], a.elem[i]);
}

template<typename T, typename A>
Vectr<T, A> & Vectr<T, A>::operator=(const Vectr<T, A> & a)
{
	if (this == &a) return *this; // self-assignment, no work needed

	if (a.sz <= space) {          // enough space, no need for new allocation
		for (int i = 0; i<a.sz; ++i)
			alloc.construct(&elem[i], a.elem[i]);
		sz = a.sz;
		return *this;
	}

	T* p = alloc.allocate(a.sz);            // allocate new space
	for (int i = 0; i<a.sz; ++i) alloc.construct(&p[i], a.elem[i]);
	for (int i = 0; i<sz; ++i) alloc.destroy(&elem[i]);
	alloc.deallocate(elem);                 // deallocate old space
	sz = a.sz;                      // set new size
	space = a.sz;
	elem = p;                               // set new elements
	return *this;
}

template<typename T, typename A>
Vectr<T, A>::Vectr(Vectr<T, A>&& a)
	:sz{ a.sz }, elem{ a.elem }                // copy a’s elem and sz
{
	a.sz = 0;                                          // make a the empty vector
	a.elem = nullptr;
}

template<typename T, typename A>
Vectr<T, A>& Vectr<T, A>::operator=(Vectr<T, A>&& a) // move a to this vector
{
	delete[] elem;                                // deallocate old space
	elem = a.elem;                              // copy a’s elem and sz
	sz = a.sz;
	a.elem = nullptr;                          // make a the empty vector
	a.sz = 0;
	return *this;                                 // return a self-reference (see §17.10)
}