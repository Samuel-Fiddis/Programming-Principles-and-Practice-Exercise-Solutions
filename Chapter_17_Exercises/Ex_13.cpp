#include "../../std_lib_facilities.h"

class Link {
public:
	struct God {
		string name, mythology, vehicle, weapon;

		God(string n, string m = "", string v = "", string w = "") :
			name(n), mythology(m), vehicle(v), weapon(w) {}
	};

	God value;

	Link(const God& v, Link* p = nullptr, Link* s = nullptr)
		: value{ v }, prev{ p }, succ{ s } { }

	Link* insert(Link* n);								// insert n before this object
	Link* add(Link* n);									// insert n after this object
	Link* erase();										// remove this object from list
	Link* find(const string& s);						// find s in list
	//const Link* find(const string& s) const;			// find s in const list (see §18.5.1)

	void print_all();

	Link* advance(int n) const;							// move n positions in list

	Link* next() const { return succ; }
	Link* previous() const { return prev; }

private:
	Link* prev;
	Link* succ;
};

Link* Link::insert(Link* n)			// insert n before this object; return n
{
	if (n == nullptr) return this;
	if (this == nullptr) return n;
	n->succ = this;					// this object comes after n
	if (prev) prev->succ = n;
	n->prev = prev;					// this object’s predecessor becomes n’s predecessor
	prev = n;						// n becomes this object’s predecessor
	return n;
}

Link* Link::erase()					// remove *p from list; return p’s successor
{
	if (this == nullptr) return nullptr;
	if (succ) succ->prev = prev;
	if (prev) prev->succ = succ;
	return succ;
}

Link* Link::add(Link* n)			// insert n after this object; return n
{
	if (n == nullptr) return this;
	if (this == nullptr) return n;
	n->prev = this;					// this object comes before n
	if (succ) succ->prev = n;
	n->succ = succ;					// this object’s succecessor becomes n’s succecessor
	succ = n;						// n becomes this object’s succecessor
	return n;
}

Link* Link::find(const string& s)	// find s in list; return nullptr for “not found”
{
	Link* p = this;
	if (p == nullptr) return nullptr;
	while (p) {
		if (p->value.name == s) return p;
		p = p->succ;
	}
	return nullptr;
}

Link* Link::advance(int n) const	// move n positions in list
									// return nullptr for “not found”
									// positive n moves forward, negative backward
{
	Link* p = const_cast<Link*> (this);
	if (this == nullptr) return nullptr;
	if (0<n) {
		while (n--) {
			if (succ == nullptr) return nullptr;
			p = p->succ;
		}
	}
	else if (n<0) {
		while (n++) {
			if (prev == nullptr) return nullptr;
			p = p->prev;
		}
	}
	return p;
}

void Link::print_all()
{
	Link* p = this;
	
	while (p) {
		cout << "{ ";
		cout << p->value.name << ", " << p->value.mythology << ", " << p->value.vehicle << ", " << p->value.weapon;
		cout << " }\n";
		p = p->succ;
	}
	
}

int main()
{
	Link* norse_gods = new Link{ Link::God{"Thor","Norse","","Hammer" } };
	norse_gods = norse_gods->insert(new Link{ Link::God{ "Odin", "Norse", "Sleipner", "Spear called Gungnir"} });
	norse_gods = norse_gods->insert(new Link{ Link::God{ "Zeus", "Greek", "", "lightning" } });
	norse_gods = norse_gods->insert(new Link{ Link::God{"Freia", "Norse","","Necklace"} });

	Link* greek_gods = new Link{ Link::God{"Hera","Greek","",""} };
	greek_gods = greek_gods->insert(new Link{ Link::God{"Athena"} });
	greek_gods = greek_gods->insert(new Link{ Link::God{"Mars","Greek","","Sword" } });
	greek_gods = greek_gods->insert(new Link{ Link::God{"Poseidon","Greek","Chariot","Trident" } });

	norse_gods->print_all();
	cout << "\n";
	greek_gods->print_all();
	cout << "\n";

	Link* p2 = greek_gods->find("Mars");
	if (p2) p2->value.name = "Ares";

	Link* p = norse_gods->find("Zeus");
	if (p) {
		if (p == norse_gods) norse_gods = p->next();
		p->erase();
		greek_gods = greek_gods->insert(p);
	}

	norse_gods->print_all();
	cout << "\n";
	greek_gods->print_all();
	cout << "\n";
}