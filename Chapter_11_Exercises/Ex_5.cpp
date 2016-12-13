#include "../../std_lib_facilities.h"

int main()
{
	string line;

	cout << "Please enter a string: ";
	getline(cin, line);

	for (char c : line)
	{
		cout << "The character '" << c << "' is:\n";
		if (isspace(c)) cout << "A whitespace character.\n";
		if (isalpha(c)) cout << "A letter.\n";
		if (isdigit(c)) cout << "A decimal digit.\n";
		if (isxdigit(c)) cout << "A hexadecimal digit.\n";
		if (isupper(c)) cout << "Uppercase.\n";
		if (islower(c)) cout << "Lowercase.\n";
		if (iscntrl(c)) cout << "A control character.\n";
		if (ispunct(c)) cout << "A punctuation charater.\n";
		cout << '\n';
	}
}