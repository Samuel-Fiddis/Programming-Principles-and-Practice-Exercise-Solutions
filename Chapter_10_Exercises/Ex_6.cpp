#include "../../std_lib_facilities.h"

class Roman_int {
public:
	
	Roman_int() : roman{ "I" } {}
	Roman_int(string r)
		: roman{ r } {
		for (int i = 0; i < roman.size(); ++i)
		{
			if (!(roman[i] == 'X' || roman[i] == 'I' || roman[i] == 'V' || roman[i] == 'C' || roman[i] == 'L' || roman[i] == 'M'))
				error("Not a roman neumeral");
		}
	}
		string print() const {return roman;}
		int as_int(const Roman_int& r);

private:
	string roman;
};

istream& operator>>(istream& is, Roman_int& r)
{
	string roman;
	is >> roman;
	r = Roman_int{ roman };
	return is;
}

ostream& operator<<(istream& os,const Roman_int& r)
{
	string roman;
	roman = r.print();
	return os << roman;
}

int Roman_int::as_int(const Roman_int& r)
{
	int sum = 0;
	int max = 0;
	int size = r.roman.size() -1;
	for (int i = 0; i < size+1; ++i)
	{
		if (r.roman[size - i] == 'I' && max <= 1)
		{
			sum += 1;
			max = 1;
		}
		else if (r.roman[size - i] == 'I' && max>1) sum -= 1;
		else if (r.roman[size - i] == 'V' && max <= 5)
		{
			sum += 5;
			max = 5;
		}
		else if (r.roman[size - i] == 'V' && max>5) sum -= 5;
		else if (r.roman[size - i] == 'X' && max <= 10)
		{
			sum += 10;
			max = 10;
		}
		else if (r.roman[size - i] == 'X' && max>10) sum -= 10;
		else if (r.roman[size - i] == 'L' && max <= 50)
		{
			sum += 50;
			max = 50;
		}
		else if (r.roman[size - i] == 'L' && max>50) sum -= 50;
	}
	return sum;
}

int main()
{
	Roman_int R;
	cout << "Please enter a roman neumeral using only I, V, X and L: ";
	cin >> R;

	int integer = R.as_int(R);
	cout << "\nThis roman neumeral as an integer is: " << integer << '\n';
}