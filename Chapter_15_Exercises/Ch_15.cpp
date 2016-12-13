#include "Graph.h"
#include "Simple_window.h"
#include "Window.h"
#include <FL/Fl.h>
#include <FL/Fl_Box.h>
#include <FL/Fl_Window.h>
#include "../../std_lib_facilities.h"
#include <cmath>

// Ex_1 Factorial Function

int fac(int n) { return n>1 ? n*fac(n - 1) : 1; }    // factorial n!

double term(double x, int n) { return pow(x, n) / fac(n); }

double expe(double x, int n)           // sum of n terms for x
{
	double sum = 0;
	for (int i = 0; i<n; ++i) sum += term(x, i);
	return sum;
}

// Functions for use in Drill

double one(double x) { return 1; }
double slope(double x) { return x / 2; }
double square(double x) { return x*x; }
double sloping_cos(double x) { return cos(x) + slope(x); }
double square_div_2(double x) { return x*x/2; }

// Ex_4 Functions

double sincos(double x) { return sin(x) + cos(x); }
double sincos_multi(double x) { return sin(x)*sin(x) + (cos(x)*cos(x)); }
double trig_sin(double x) { return sin(x); }
double trig_cos(double x) { return cos(x); }

// Ex_5

double Leibniz(double x, int n) {
	if (n == 0) return 0.0;
	if (n < 0) cerr << "Error, n less than zero.";
	double sum = 0.0;
	for (int i = 1; i <= n;++i)
		sum += (-1)*(i + 1) / (-1 + (2 * i));
	return sum;
}

// Class Definition Drill

struct Person {
	Person(string name, int age);
	Person();

	string name() const { return Person::n; }
	int age() const { return Person::a; }
	
	void set_name(string n1) { 
		string error = ";:\"\'[]*&^%$~@!.";
		int count = 0;

		for (int i = 0; i < n1.size(); ++i)
		
			for (int x = 0; x < error.size(); ++x)
				if (n1[i] == error[x]) ++count;
			if (count >= 1) cerr << "Error, name in error.";
			else n = n1; }

	void set_age(int a1) { a = a1; }

private:
	string n;
	int a;
};

Person::Person(string name, int age)
	: n(name), a(age) {
	
	string error = ";:\"\'[]*&^%$~@!.";

	if (age < 0 || age > 150) cerr << "Error, age not in range.\n";
	int count = 0;
	for (int i = 0; i < name.size(); ++i)
		for (int x = 0; x < error.size(); ++x)
			if (name[i] == error[x]) ++count;
		if (count > 1) cerr << "Error, name in error";
}

Person::Person()
	: n(""), a(150) {}

istream& operator>>(istream& is, Person& p)
{
	string name;
	int age;

	if (is >> name >> age)
	{
		p.set_name(name);
		p.set_age(age);
		return is;
	}
}

ostream& operator>>(ostream& os, Person pp)
{
	if (os << pp.name() << pp.age())
		return os;
}

int main()
{

	//Drill
	
	/*
	Person p1("Goofy", 63);
	Person p2;

	cin >> p2;
	cout << '\n' << p2.name() << " " << p2.age();
	*/

	int x_max = 600;
	int y_max = 600;
	int x_length = 400;
	int y_length = 400;
	int x_offset = (x_max - x_length) / 2;
	int y_offset = (y_max - y_length) / 2;

	Simple_window win(Point{ 100,100 }, x_max, y_max, "Function graphs.");
	Axis x(Axis::x, Point{ x_offset,y_max / 2 }, x_length, x_length / 20, "1 == 20 Pixels");
	Axis y(Axis::y, Point{ x_max / 2,y_max - y_offset }, y_length, y_length / 20, "1 == 20 Pixels");

	win.attach(x);
	win.attach(y);
	win.wait_for_button();
		
	/*Function f1 (one, -10, 10, Point{ x_max / 2,y_max / 2 }, 400,20,20);
	f1.set_color(Color::red);

	win.attach(f1);
	win.wait_for_button();

	Function f2(slope, -10, 10, Point{ x_max / 2,y_max / 2 }, 400, 20, 20);
	f2.set_color(Color::blue);

	win.attach(f2);
	win.wait_for_button();

	Text f2_label(Point{ 100,420 }, "x/2");
	f2_label.set_color(Color::blue);

	win.attach(f2_label);
	win.wait_for_button();

	Function f3(square, -10, 10, Point{ x_max / 2,y_max / 2 }, 400, 20, 20);
	f3.set_color(Color::green);

	win.attach(f3);
	win.wait_for_button();

	Function f4([](double x) {return cos(x); }, -10, 10, Point{ x_max / 2,y_max / 2 }, 400, 20, 20);
	f4.set_color(Color::dark_yellow);

	win.attach(f4);
	win.wait_for_button();

	Flex_fct f5(sloping_cos, -10, 10, Point{ x_max / 2,y_max / 2 }, 400, 20, 20);
	f5.set_color(Color::dark_magenta);

	win.attach(f5);
	win.wait_for_button();
	
	f5.set_origin(Point{ 500,300 });
	f5.set_fct(square_div_2);
	win.wait_for_button();*/
	
	// Ex_1
	
	vector<int> factorials;

	for (int i = 1; i <= 20; ++i)
		factorials.push_back(fac(i));

	for (int i = 0; i < factorials.size(); ++i)
		cout << i + 1 << ' ' << factorials[i] << '\n';

	// Ex_2



	// Ex_4

	Flex_fct f6 (trig_sin, - 10, 10, Point{ x_max / 2,y_max / 2 }, 400, 20, 20);
	Flex_fct f7(trig_cos, -10, 10, Point{ x_max / 2,y_max / 2 }, 400, 20, 20);
	Flex_fct f8(sincos, -10, 10, Point{ x_max / 2,y_max / 2 }, 400, 20, 20);
	Flex_fct f9(sincos_multi, -10, 10, Point{ x_max / 2,y_max / 2 }, 400, 20, 20);

	win.attach(f6);
	f6.set_color(Color::yellow);
	win.attach(f7);
	f7.set_color(Color::red);
	win.attach(f8);
	f8.set_color(Color::blue);
	win.attach(f9);
	f8.set_color(Color::green);

	win.wait_for_button();

	// Ex_5

	for (int n = 0; n < 50; ++n)
	{
		double term = Leibniz(0, n);
		Function f9(  -10, 10, Point{ x_max / 2,y_max / 2 }, 400, 20, 20 );
		win.attach(f9);
		win.wait_for_button();
		win.detach(f9);
	}
}


