#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"
#include <FL/Fl.h>
#include <FL/Fl_Box.h>
#include <FL/Fl_Window.h>
#include <cmath>

// fltkd.lib wsock32.lib comctl32.lib fltkjpegd.lib fltkimagesd.lib

int main()
{
	Simple_window win{ Point{100,100},1000,1000,"Ch_12_Drill" };
	win.wait_for_button();

	// Ex_1

	Graph_lib::Arc arc{ Point{200,200},40,80,0,180 };
	win.attach(arc);
	// win.wait_for_button();

	// Ex_2

	Graph_lib::Box box1{ Point{200,600},200,100,50 };
	win.attach(box1);

	// win.wait_for_button();

	box1.set_color(Color::red);

	win.wait_for_button();

	box1.move(100, -100);

	win.wait_for_button();

	// Ex_3

	Arrow a{ Point{ 100,500 }, Point{ 900,500 } };
	win.attach(a);

	Arrow b{ Point{ 100,900 }, Point{ 900,100 } };
	win.attach(b);

	Arrow c{ Point{ 750,900 }, Point{ 250,100 } };
	win.attach(c);

	Arrow d{ Point{ 100,600 }, Point{ 900,400 } };
	win.attach(d);

	Arrow e{ Point{ 900,100 }, Point{ 100,900 } };
	win.attach(e);

	// win.wait_for_button();

	// Ex_4

	Graph_lib::Rectangle rect(Point{ 100,100 }, 300, 600);
	win.attach(rect);
	win.wait_for_button();

	Line ctone{ center(rect),se(rect) };

	win.attach(ctone);
	win.wait_for_button();

	// Ex_6

	Text_Box text{ Point{800,800},"What's up doc?" };
	win.attach(text);
	win.wait_for_button();

	// Ex_8

	Graph_lib::Regular_Hexagon hex{ Point{500,500},200 };
	win.attach(hex);
	win.wait_for_button();

	// Ex_10

	Graph_lib::Regular_Polygon poly{ Point{500,500},6,100 };
	win.attach(poly);
	win.wait_for_button();

	Graph_lib::Regular_Polygon poly2{ Point{ 500,500 },8,150,25 };
	win.attach(poly2);
	win.wait_for_button();

	
}
