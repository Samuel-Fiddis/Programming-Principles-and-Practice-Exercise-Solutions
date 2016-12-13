#include "../../std_lib_facilities.h"

int main()
{
	vector<int> Scores;
	vector<string> Names;

	cout << "Please enter a Name followed by a Score. Enter ';' to exit and see all scores.\n";

	while (cin)
	{
		string wub;
		int dub;
		
		cin >> wub;
		if (wub == ";")
			break;
		
		cin >> dub;

		Names.push_back(wub);
		Scores.push_back(dub);
	}

	cout << "The scores are:\n";

	for (int i = 0; i < Scores.size(); ++i)
	{
		cout << Names[i] << " " << Scores[i] << "\n";
	}
}