
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include "GUI.h"

namespace Graph_lib {

//------------------------------------------------------------------------------

void Button::attach(Window& win)
{
    pw = new Fl_Button(loc.x, loc.y, width, height, label.c_str());
    pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window
    own = &win;
}

//------------------------------------------------------------------------------

int In_box::get_int()
{
    Fl_Input& pi = reference_to<Fl_Input>(pw);
    // return atoi(pi.value());
    const char* p = pi.value();
    if (!isdigit(p[0])) return -999999;
    return atoi(p);
}

//------------------------------------------------------------------------------

void In_box::attach(Window& win)
{
    pw = new Fl_Input(loc.x, loc.y, width, height, label.c_str());
    own = &win;
}

//------------------------------------------------------------------------------

void Out_box::put(const string& s)
{
    reference_to<Fl_Output>(pw).value(s.c_str());
}

//------------------------------------------------------------------------------

void Out_box::attach(Window& win)
{
    pw = new Fl_Output(loc.x, loc.y, width, height, label.c_str());
    own = &win;
}

//------------------------------------------------------------------------------

int Menu::attach(Button& b)
{
    b.width = width;
    b.height = height;

    switch(k) {
    case horizontal:
        b.loc = Point(loc.x+offset,loc.y);
        offset+=b.width;
        break;
    case vertical:
        b.loc = Point(loc.x,loc.y+offset);
        offset+=b.height;
        break;
    }
    selection.push_back(b); // b is NOT OWNED: pass by reference
    return int(selection.size()-1);
}

//------------------------------------------------------------------------------

int Menu::attach(Button* p)
{
    Button& b = *p;
    b.width = width;
    b.height = height;

    switch(k) {
    case horizontal:
        b.loc = Point(loc.x+offset,loc.y);
        offset+=b.width;
        break;
    case vertical:
        b.loc = Point(loc.x,loc.y+offset);
        offset+=b.height;
        break;
    }
    selection.push_back(&b); // b is OWNED: pass by pointer
    return int(selection.size()-1);
}

//Drill-------------------------------------------------------------------------

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
	:Window{ xy,w,h,title },
	next_button{ Point{ x_max() - 150,0 }, 70, 20, "Next point",
	[](Address, Address pw) {reference_to<Lines_window>(pw).next(); } },
	quit_button{ Point{ x_max() - 70,0 }, 70, 20, "Quit",
	[](Address, Address pw) {reference_to<Lines_window>(pw).quit(); } },
	next_x{ Point{ x_max()-310,0 }, 50, 20, "next x:" },
	next_y{ Point{ x_max()-210,0 }, 50, 20, "next y:" },
	xy_out{ Point{ 100,0 }, 100, 20, "current (x,y):" },
	color_menu{ Point{ x_max()-70,40 },70,20,Menu::vertical,"color" },
	menu_button{ Point{ x_max()-80,30 }, 80, 20, "color menu", cb_menu },
	style_menu{ Point{ x_max() - 70,120 },70,20,Menu::vertical,"style" },
	style_button{ Point{ x_max() - 80,110 }, 80, 20, "style menu", cb_style }
{
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	xy_out.put("no point");
	color_menu.attach(new Button{ Point{ 0,0 },0,0,"red",cb_red });
	color_menu.attach(new Button{ Point{ 0,0 },0,0,"blue",cb_blue });
	color_menu.attach(new Button{ Point{ 0,0 },0,0,"black",cb_black });
	attach(color_menu);
	color_menu.hide();
	attach(menu_button);
	attach(lines);
	style_menu.attach(new Button{ Point{ 0,0 },0,0,"dot",cb_dot });
	style_menu.attach(new Button{ Point{ 0,0 },0,0,"dash",cb_dash });
	style_menu.attach(new Button{ Point{ 0,0 },0,0,"solid",cb_line });
	attach(style_menu);
	style_menu.hide();
	attach(style_button);

}

void Lines_window::quit()
{
	hide();          // curious FLTK idiom to delete window
}

void Lines_window::next()
{
	int x = next_x.get_int();
	int y = next_y.get_int();
	lines.add(Point{ x,y });

	// update current position readout:
	ostringstream ss;
	ss << '(' << x << ',' << y << ')';
	xy_out.put(ss.str());

	redraw();
}

void Lines_window::cb_red(Address, Address pw)
{
	reference_to<Lines_window>(pw).red_pressed();
}

void Lines_window::cb_blue(Address, Address pw)
{
	reference_to<Lines_window>(pw).blue_pressed();
}

void Lines_window::cb_black(Address, Address pw)
{
	reference_to<Lines_window>(pw).black_pressed();
}

void Lines_window::cb_menu(Address, Address pw)
{
	reference_to<Lines_window>(pw).menu_pressed();
}

void Lines_window::cb_dot(Address, Address pw)
{
	reference_to<Lines_window>(pw).dot_pressed();
}

void Lines_window::cb_dash(Address, Address pw)
{
	reference_to<Lines_window>(pw).dash_pressed();
}

void Lines_window::cb_line(Address, Address pw)
{
	reference_to<Lines_window>(pw).line_pressed();
}

void Lines_window::cb_style(Address, Address pw)
{
	reference_to<Lines_window>(pw).style_pressed();
}
//------------------------------------------------------------------------------

}; // of namespace Graph_lib
