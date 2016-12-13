#include "Graph.h"
#include "Simple_window.h"
#include "Window.h"
#include <FL/Fl.h>
#include <FL/Fl_Box.h>
#include <FL/Fl_Window.h>
#include "../../std_lib_facilities.h"

int main() {
	
	int xmax = 800;
	int ymax = 800;
	int x_offset = 100;
	int y_offset = 100;
	double xlength = xmax - (x_offset * 2);
	double ylength = ymax - (y_offset * 2);
	
	Simple_window win{ Point{100,100},xmax,ymax,"Bar Graph" };
	
	win.wait_for_button();
	vector<double> heights{ 7,8,23,17,6,1};
	vector<string> bar_labels{ "170 cm","175 cm","180 cm","185 cm","190 cm","195 cm" };

	// Ex_8

	Bar_graph b{ heights,Point{x_offset,(ymax-y_offset)},xlength,ylength/23 };
	win.attach(b);
	b.set_bar_color(1, Color::yellow);
	for (int i = 0; i < bar_labels.size();i++)
		b.label_bar(i, bar_labels[i]);
	win.wait_for_button();
	
	Axis x{ Axis::x, Point{ x_offset,(ymax - y_offset) },int(xlength),0,"" };
	win.attach(x);

	Axis y{ Axis::y, Point{ x_offset,(ymax - y_offset) } ,int(ylength),23,"Number of people" };
	win.attach(y);


	win.wait_for_button();
}