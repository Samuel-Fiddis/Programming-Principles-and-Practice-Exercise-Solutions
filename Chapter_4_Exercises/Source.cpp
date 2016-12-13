#include "../../std_lib_facilities.h"

int main()
{
	vector<char> rps = { 'r','r','p','r','s','r','p','s','p','p','s','r','s' };
	char choice = 'o';
	int tied = 0;
	int won = 0;
	int lost = 0;

	for (int i = 1; i < 150; ++i)
	{
		cout << "Choose one; Rock (r), Paper (p) or Sissors (s): ";
		cin >> choice;
		switch (choice) {
		case 'r':
			switch (rps[i+10]) {
			case 'r':
				cout << "Computer chooses Rock!\n\nTied game, try again!\n";
				++tied;
				break;
			case 'p':
				cout << "Computer chooses Paper!\n\nYou Lose :(, try again!\n";
				++lost;
				break;
			case 's':
				cout << "Computer chooses Sissors!\n\nYou Win!!! play again!\n";
				++won;
				break;
			}
			break;
		case 'p':
			switch (rps[i+10]) {
			case 'r':
				cout << "Computer chooses Rock!\n\nYou Win!!! play again!\n";
				++won;
				break;
			case 'p':
				cout << "Computer chooses Paper!\n\nTied game, try again!\n";
				++tied;
				break;
			case 's':
				cout << "Computer chooses Sissors!\n\nYou Lose :(, try again!\n";
				++lost;
				break;
			}
			break;
		case 's':
			switch (rps[i+10]) {
			case 'r':
				cout << "Computer chooses Rock!\n\nYou Lose :(, try again!\n";
				++lost;
				break;
			case 'p':
				cout << "Computer chooses Paper!\n\nYou Win!!! play again!\n";
				++won;
				break;
			case 's':
				cout << "Computer chooses Sissors!\n\nTied game, try again!\n";
				++tied;
				break;
			}
			break;
		case 'd':
			cout << "Dynamite wins! Kapow!\n\n";
			++won;
			break;
			}
		cout << "Games Played: " << i << "\nGames Won: " << won << "\nGames Lost: " << lost << "\nGames Tied: ";
		cout << tied << '\n';
		rps.push_back(choice);
		}
}
