#include "Graph.h"
#include "Simple_window.h"
#include "Window.h"
#include <FL/Fl.h>
#include <FL/Fl_Box.h>
#include <FL/Fl_Window.h>
#include "../../std_lib_facilities.h"
#include <cmath>

int main()
{
	//Drill-------------------------------------------------------

	//Lines_window win{ Point{ 100,100 },600,400,"lines" };
	//return gui_main();

	//Ex_1--------------------------------------------------------
	
	My_window win2 { Point{100,100},800,800,"Quit" };
	
	Graph_lib::Rectangle rect{ Point(100,100),100,200 };
	Graph_lib::Circle circ{ Point{300,300},100 };
		
	win2.wait_for_next_button();

	win2.attach(rect);

	win2.wait_for_next_button();

	win2.attach(circ);

	win2.wait_for_next_button();
}
