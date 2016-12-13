#include "../../std_lib_facilities.h"

void main8()
{
	int desiered_rice = 0;
	int total_rice = 0;
	int tile_rice = 1;
	int square_number = 0;

	cout << "Please enter the total amount of rice requiered.\n";
	cin >> desiered_rice;

	for (int i = 1; total_rice < desiered_rice; ++i)
	{
		cout << "Square Number: " << i << "\n";
		if (i == 1);
		else
			tile_rice = tile_rice * 2;
		total_rice += tile_rice;
		cout << "Total Rice: " << total_rice << '\n';
		square_number = i;
	}
	cout << "The total number of squares requierd is: " << square_number << '\n';
}