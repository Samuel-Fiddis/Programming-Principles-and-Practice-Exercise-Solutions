#include "../../std_lib_facilities.h"

// 31 squares using ints, 64 using doubles

void main9()
{
	double desiered_rice = 0;
	double total_rice = 0;
	double tile_rice = 1;
	double square_number = 0;

	cout << "(ints) Please enter the total number of squares.\n";
	cin >> square_number;

	for (int i = 1; i <= square_number; ++i)
	{
		cout << "Square Number: " << i << "\n";
		if (i == 1);
		else
			tile_rice = tile_rice * 2;
		total_rice += tile_rice;
		cout << "Total Rice: " << total_rice << '\n';
	}
	cout << "The amount of rice is: " << total_rice << '\n';
}