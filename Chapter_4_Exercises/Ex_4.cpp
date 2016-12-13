#include "../../std_lib_facilities.h"

// read some temperatures into a vector

void main4()

{
	int n = 0;
	string answer = "nil";
	int guess_low = 1;
	int guess_middle = 50;
	int guess_high = 100;
	int guess_final = 101;

	cout << "Please think of an integer value between 1 and 100.\n";

	cout << "\nIs the number less than  or equal to " << guess_middle << "?\n";
	cin >> answer;

	while (n != guess_final)
	{
		if (answer == "yes" || answer == "y")
		{
			if (guess_low == guess_middle)
			{
				cout << "Your number is " << guess_low << "!\n";
				break;
			}
			guess_high = guess_middle;
			guess_middle = (guess_middle + guess_low) / 2;
			cout << "Is the number between " << guess_low << " and " << guess_middle << "?\n";
			cin >> answer;
		}
		else if (answer == "no" || answer == "n")
		{
			if (guess_low == guess_middle)
			{
				cout << "Your number is " << guess_high << "!\n!";
				break;
			}
			guess_low = guess_middle;
			guess_middle = (guess_middle + guess_high) / 2;
			cout << "Is the number between " << guess_low << " and " << guess_middle << "?\n";
			cin >> answer;
		}
		else break;
	}
}
