#include "../../std_lib_facilities.h"

class Book
{
public:

	const string& get_ISBN() const { return ISBN; }


private:

	string ISBN;
	string title;
	string author;
	Date copywright_date;

}