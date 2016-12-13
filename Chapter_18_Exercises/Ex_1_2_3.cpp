#include "../../std_lib_facilities.h"

char* strdup2(const char* ch)
{
	int i = 0;
	while (*ch) {
		++i;
		++ch;
	}

	ch -= i;
	char* ch2 = new char[i+1];

	while (*ch) {
		*ch2 = *ch;
		++ch2;
		++ch;
	}
	
	*ch2 = 0;

	ch -= i;
	ch2 -= i;

	return ch2;
}

char* findx(const char* s, const char* x)
{
	const char* p = s;
	const char* q = x;

	while (*p)
	{
		int a = 0;
		if (*q != *p) ++p;
		else {
			while (*q) {

				if (*q == *p) {
					++q;
					++p;
					++a;
				}
				else {
					p -= a-1;
					q -= a;
					break;
				}
				if (!*q) {
					p -= a;
					return const_cast<char*>(p);
				}
			}
		}
	}
	return nullptr;
}

int strcmp(const char* s1, const char* s2)
{
	int i1 = 0;
	int i2 = 0;

	while (*s1 && *s2)
	{

		// Chech if it is a capital letter
		if (64 < *s1 && *s1 < 91) i1 = *s1 + 32;
		else i1 = *s1;
		if (64 < *s2 && *s2 < 91) i2 = *s2 + 32;
		else i2 = *s2;

		if (i1 == i2);
		else if (i1 > i2) return 1;
		else if (i1 < i2) return -1;
		++s1;
		++s2;
	}
	return 0;
}

string cat_dot(const string& s1, const string& s2,string sep = ".")
{
	return s1 + sep+ s2;
}

char* cat_dot(const char* s1, const char* s2)
{
	int s1_size = 0;
	while (*s1++) s1_size++;
	
	s1 -= s1_size + 1;

	int s2_size = 0;
	while (*s2++) s2_size++;
	
	s2 -= s2_size + 1;

	int size = s1_size + s2_size + 2;

	char* s = new char[size+2];

	int i = 0;

	for (int i = 0; i < s1_size; ++i)
	{
		s[i] = s1[i];
	}
	
	s[s1_size] = '.';

	for (int i = s1_size + 1; i < size; ++i)
	{
		s[i] = s2[i - (s1_size+1)];
	}

	s[size-1] = 0;
	
	return s;
}

bool is_palindrome(const string& s)
{
	string z = s;
	for (int i = 0; i < s.size(); ++i)
		z[i] = s[s.size() - i - 1];

	for (int i = 0; i < s.size(); ++i)
		if (z[i] != s[i]) return false;

	return true;
}

bool is_palindrome(const char s[], int n)
{
	int count = 0;
	const char* p = s;
	while (*p++) count++;

	char* z = new char[count];

	for (int i = 0; i < count; ++i) z[i] = s[count - 1 - i];

	for (int i = 0; i < count; ++i)
		if (z[i] != s[i]) return false;
	return true;
}


int main()
{
	char g[] = "woow";

	//cout << g << '\n';

	char* h = strdup2(g);

	//cout << h;

	char j[] = "What are you talking about?";

	char* x = findx(g, j);
	if(x) cout << findx(g, j) << '\n';
	else cout << "No valuse was found!\n";

	int i = strcmp(g, j);
	cout << i << '\n';

	string a = "Hello";
	string b = "friend";
	cout << cat_dot(a, b," my dear ") << '\n';

	char* s = cat_dot(g, j);

	cout << s;

	if (is_palindrome(g)) cout << "\nthats numberwang!";
}