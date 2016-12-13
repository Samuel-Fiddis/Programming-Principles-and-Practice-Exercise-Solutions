#include "../../std_lib_facilities.h"
#include "Vector.h"

template<class T> T* allocatr<T>::allocate(int n) {
	T* p = calloc(n, sizeof(T));
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
	*p = new T(v);
}

template<typename T>
void allocatr<T>::destroy(T * p)
{
	p->~T;
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
Vectr<T, A>::Vectr(const Vectr<T,A> & a)
	: sz(a.sz), elem(alloc.allocate(a.sz)), space(a.sz)
{
	for (int i = 0; i<sz; ++i)
		alloc.construct(&elem[i], a.elem[i]);
}

template<typename T, typename A>
Vectr<T,A> & Vectr<T, A>::operator=(const Vectr<T,A> & a)
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
Vectr<T,A>::Vectr(Vectr<T,A>&& a)
	:sz{ a.sz }, elem{ a.elem }                // copy a’s elem and sz
{
	a.sz = 0;                                          // make a the empty vector
	a.elem = nullptr;
}

template<typename T, typename A>
Vectr<T,A>& Vectr<T,A>::operator=(Vectr<T,A>&& a) // move a to this vector
{
	delete[] elem;                                // deallocate old space
	elem = a.elem;                              // copy a’s elem and sz
	sz = a.sz;
	a.elem = nullptr;                          // make a the empty vector
	a.sz = 0;
	return *this;                                 // return a self-reference (see §17.10)
}