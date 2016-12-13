//Write a find-and-replace operation for Documents based on §20.6.2.
#include "../../std_lib_facilities.h"

using Line = vector<char>;             // a line is a vector of characters

class Text_iterator {      // keep track of line and character position within a line
	std::list<Line>::iterator ln;
	Line::iterator pos;

public:
	// start the iterator at line ll’s character position pp:
	Text_iterator(std::list<Line>::iterator ll, Line::iterator pp)
		:ln{ ll }, pos{ pp } { }

	char& operator*() { return *pos; }
	Text_iterator& operator++();
	Text_iterator& operator--();

	bool operator==(const Text_iterator& other) const
	{	return ln == other.ln && pos == other.pos;	}
	bool operator!=(const Text_iterator& other) const
	{	return !(*this == other);	}
};

Text_iterator& Text_iterator::operator++()
{
	++pos;                                       // proceed to next character
	if (pos == (*ln).end()) {
		++ln;                                // proceed to next line
		pos = (*ln).begin();       // bad if ln==line.end(); so make sure it isn’t
	}
	return *this;
}

Text_iterator& Text_iterator::operator--()
{
	if (pos == (*ln).begin()) {
		--ln;                                
		pos = (*ln).end();       
	}
	--pos;                                    
	return *this;
}

template<typename Iter>
bool match(Iter p, Iter last, const std::string& s)
{
	auto q = p;
	for (int i = 0; i < s.size(); ++i)
	{
		if (q == last || *q != s[i]) return false;
		++q;
	}
	return true;
}

struct Document {
	std::list<Line> line;
		Document() { line.push_back(Line{}); }

	Text_iterator begin(){	return Text_iterator(line.begin(), (*line.begin()).begin());}    // first character of first line

	Text_iterator end()                 // one beyond the last character of the last line
	{
		auto last = line.end();
		--last;          // we know that the document is not empty
		return Text_iterator(last, (*last).end());
	}

	Text_iterator find(Text_iterator p, const char& c)
	{
		while (p != end() && *p != c) ++p;
		return p;
	}
};

void print(Document& d, Text_iterator p)
{
	for (; p != d.end(); ++p) std::cout << *p;
	std::cout << "\n";
}

std::istream& operator>>(std::istream& is, Document& d)
{
	for (char ch; is.get(ch); ) {
		if (ch == '*') break;
		d.line.back().push_back(ch);         // add the character
		if (ch == '\n')
			d.line.push_back(Line{});     // add another line
	}
	if (d.line.back().size()) d.line.push_back(Line{});    // add final empty line
	return is;
}

std::ostream& operator<<(std::ostream& os, Document& d)
{
	auto p = d.begin();
	while (p != d.end())
	{
		os << *p;
		++p;
	}
	return os;
}

Text_iterator find_txt(Document d, const std::string& s)
{
	if (s.size() == 0) return d.end();      // can’t find an empty string
	char first_char = s[0];
	auto q = d.begin();
	while (true) {
		auto p = d.find(q,first_char);
		if (p == d.end() || match(p, d.end(), s)) return p;
		q = ++p;                     // look at the next character
	}
}

int main()
{
	Document d;
	string s;
	std::cout << "Please enter some words for the document:\n";
	std::cin >> d;
	cout << d;
	std::cout << "What word would you like to find? ";
	std::cin >> s;
	Text_iterator p = find_txt(d, s);
	cout << *(--p);
	//for (int i = 0; i < s.size(); ++i)
	//{
	//	cout << *p;
	//	++p;
	//}

}