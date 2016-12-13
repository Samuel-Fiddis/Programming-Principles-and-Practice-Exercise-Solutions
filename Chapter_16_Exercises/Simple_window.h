
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef SIMPLE_WINDOW_GUARD
#define SIMPLE_WINDOW_GUARD 1

#include "GUI.h"    // for Simple_window only (doesn't really belong in Window.h)
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

struct Simple_window : Window {
    Simple_window(Point xy, int w, int h, const string& title );

    bool wait_for_button(); // simple event loop

private:
    Button next_button;     // the "next" button
    bool button_pushed;     // implementation detail

    static void cb_next(Address, Address); // callback for next_button
    void next();            // action to be done when next_button is pressed

};

//Ch_16_Ex_1--------------------------------------------------------------------------

struct My_window : Window {
	My_window(Point xy, int w, int h, const string& title);

	bool wait_for_next_button(); // simple event loop
	
private:
	Button next_button;     // the "next" button
	Button quit_button;
	bool next_button_pushed;     // implementation detail

	static void cb_next(Address, Address); // callback for next_button
	static void cb_quit(Address, Address);
	void next();
	void quit();
};
#endif // SIMPLE_WINDOW_GUARD
