
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"

//------------------------------------------------------------------------------

Simple_window::Simple_window(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title),
    next_button(Point(x_max()-70,0), 70, 20, "Next", cb_next),
    button_pushed(false)
{
    attach(next_button);
}

//------------------------------------------------------------------------------

bool Simple_window::wait_for_button()
// modified event loop:
// handle all events (as per default), quit when button_pushed becomes true
// this allows graphics without control inversion
{
    show();
    button_pushed = false;
#if 1
    // Simpler handler
    while (!button_pushed) Fl::wait();
    Fl::redraw();
#else
    // To handle the case where the user presses the X button in the window frame
    // to kill the application, change the condition to 0 to enable this branch.
    Fl::run();
#endif
    return button_pushed;
}

//------------------------------------------------------------------------------

void Simple_window::cb_next(Address, Address pw)
// call Simple_window::next() for the window located at pw
{  
    reference_to<Simple_window>(pw).next();    
}

//------------------------------------------------------------------------------

void Simple_window::next()
{
    button_pushed = true;
    hide();
}

//Ch_16_Ex_1--------------------------------------------------------------------

My_window::My_window(Point xy, int w, int h, const string& title):
Window(xy, w, h, title),
next_button(Point(x_max() - 70, 0), 70, 20, "Next", cb_next),
quit_button(Point(x_max() - 150, 0), 70, 20, "Quit", cb_quit),
next_button_pushed(false)
{
	attach(next_button);
	attach(quit_button);
}

bool My_window::wait_for_next_button()
// modified event loop:
// handle all events (as per default), quit when button_pushed becomes true
// this allows graphics without control inversion
{
	show();
	next_button_pushed = false;
#if 1
	// Simpler handler
	while (!next_button_pushed) Fl::wait();
	Fl::redraw();
#else
	// To handle the case where the user presses the X button in the window frame
	// to kill the application, change the condition to 0 to enable this branch.
	Fl::run();
#endif
	return next_button_pushed;
}

void My_window::cb_next(Address, Address pw)
// call Simple_window::next() for the window located at pw
{
	reference_to<My_window>(pw).next();
}

void My_window::cb_quit(Address, Address pw)
// call Simple_window::next() for the window located at pw
{
	reference_to<My_window>(pw).quit();
}

void My_window::next()
{
	next_button_pushed = true;
	hide();
}

void My_window::quit()
{
	hide();
}