// 12. Complete the definition of list from §20.4.1–2 and get the high() example to run. Allocate a Link to represent one past the end.

#include "../../std_lib_facilities.h"

template<typename Elem>
struct Link {
	Link(const Elem& v = Elem(), Link* p = nullptr, Link* s = nullptr)
		:prev(p), succ(s), val(v) { }
	Link* prev;               // previous link
	Link* succ;               // successor (next) link
	Elem val;                   // the value
};

template<typename Elem>
class dlist {
	Link<Elem>* first;
	Link<Elem>* last;
public:
	dlist() : first{new Link<Elem>() }, last{ first } {}
	class iterator;                 // member type: iterator

	iterator begin() { return iterator(first); };            // iterator to first element
	iterator end() { return iterator(last); };              // iterator to one beyond last element

	//iterator insert(iterator p, const Elem& v);        // insert v into list after p
	//iterator erase(iterator p);                        // remove p from the list

	void push_back(const Elem& v);                      // insert v at end
	void push_front(const Elem& v);                     // insert v at front
	//void pop_front();          // remove the first element
	//void pop_back();          // remove the last element

	Elem& front() { return *first };               // the first element
	Elem& back() { return *last };               // the last element

								// . . .
};

template<typename Elem>
void dlist<Elem>::push_back(const Elem& v)
{
	last->val = v;
	Link<Elem>* p = new Link<Elem>(Elem(), last, 0);
	last->succ = p;
	last = p;
};

template<typename Elem>
void dlist<Elem>::push_front(const Elem& v)
{
	first = new Link<Elem>(v, 0, first);
};

template<typename Elem>         // requires Element<Elem>() (§19.3.3)
class dlist<Elem>::iterator {
	Link<Elem>* curr;              // current link
public:
	iterator(Link<Elem>* p) :curr{ p } { }

	iterator &operator++() { curr = curr->succ; return *this; }   // forward
	iterator &operator--() { curr = curr->prev; return *this; }   // backward
	Elem &operator*() { return curr->val; }   // get value (dereference)

	bool operator==(const iterator& b) const { return curr == b.curr; }
	bool operator!= (const iterator& b) const { return curr != b.curr; }
};

template<typename Iter>  // requires Input_iterator<Iter>() (§19.3.3)
Iter high(Iter first, Iter last)
// return an iterator to the element in [first,last) that has the highest value
{
	Iter high = first;
	for (Iter p = first; p != last; ++p)
		if (*high<*p) high = p;
	return high;
};

int main()
{
	dlist<int> l;
	l.push_back(1);
	l.push_front(2);
	l.push_back(3);
	l.push_front(-2);
	l.push_back(2);
	l.push_back(5);
	l.push_back(4);
	l.push_back(1);

	auto p = high(l.begin(), l.end());
	cout << *p << '\n';
};