
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef GUI_GUARD
#define GUI_GUARD

#include "Window.h"
#include "Graph.h"

namespace Graph_lib {

//------------------------------------------------------------------------------

    typedef void* Address;    // Address is a synonym for void*
    typedef void(*Callback)(Address, Address);    // FLTK's required function type for all callbacks

//------------------------------------------------------------------------------

    template<class W> W& reference_to(Address pw)
    // treat an address as a reference to a W
    {
        return *static_cast<W*>(pw);
    }

//------------------------------------------------------------------------------

    class Widget {
    // Widget is a handle to an Fl_widget - it is *not* an Fl_widget
    // We try to keep our interface classes at arm's length from FLTK
    public:
        Widget(Point xy, int w, int h, const string& s, Callback cb)
            : loc(xy), width(w), height(h), label(s), do_it(cb)
        {}

        virtual void move(int dx,int dy) { hide(); pw->position(loc.x+=dx, loc.y+=dy); show(); }
        virtual void hide() { pw->hide(); }
        virtual void show() { pw->show(); }
        virtual void attach(Window&) = 0;

        Point loc;
        int width;
        int height;
        string label;
        Callback do_it;

        virtual ~Widget() { }

    protected:
        Window* own;    // every Widget belongs to a Window
        Fl_Widget* pw;  // connection to the FLTK Widget
    private:
        Widget& operator=(const Widget&); // don't copy Widgets
        Widget(const Widget&);
    };

//------------------------------------------------------------------------------

    struct Button : Widget {
        Button(Point xy, int w, int h, const string& label, Callback cb)
            : Widget(xy,w,h,label,cb)
        {}

        void attach(Window&);
    };

//------------------------------------------------------------------------------

    struct In_box : Widget {
        In_box(Point xy, int w, int h, const string& s)
            :Widget(xy,w,h,s,0) { }
        int get_int();
        string get_string();

        void attach(Window& win);
    };

//------------------------------------------------------------------------------

    struct Out_box : Widget {
        Out_box(Point xy, int w, int h, const string& s)
            :Widget(xy,w,h,s,0) { }
        void put(int);
        void put(const string&);

        void attach(Window& win);
    };

//------------------------------------------------------------------------------

    struct Menu : Widget {
        enum Kind { horizontal, vertical };
        Menu(Point xy, int w, int h, Kind kk, const string& label)
            : Widget(xy,w,h,label,0), k(kk), offset(0)
        {}

        Vector_ref<Button> selection;
        Kind k;
        int offset;
        int attach(Button& b);      // Menu does not delete &b
        int attach(Button* p);      // Menu deletes p

        void show()                 // show all buttons
        {
            for (unsigned int i = 0; i<selection.size(); ++i)
                selection[i].show();
        }
        void hide()                 // hide all buttons
        {
            for (unsigned int i = 0; i<selection.size(); ++i) 
                selection[i].hide(); 
        }
        void move(int dx, int dy)   // move all buttons
        {
            for (unsigned int i = 0; i<selection.size(); ++i) 
                selection[i].move(dx,dy);
        }

        void attach(Window& win)    // attach all buttons
        {
            for (int i=0; i<selection.size(); ++i) win.attach(selection[i]);
            own = &win;
        }

    };

//------------------------------------------------------------------------------

	struct Lines_window : Window {
		Graph_lib::Lines_window(Point xy, int w, int h, const string& title);
		Open_polyline lines;

		static void cb_red(Address, Address);         // callback for red button
		static void cb_blue(Address, Address);       // callback for blue button
		static void cb_black(Address, Address);      // callback for black button
		static void cb_menu(Address, Address);

		static void cb_dot(Address, Address);         // callback for red button
		static void cb_dash(Address, Address);       // callback for blue button
		static void cb_line(Address, Address);      // callback for black button
		static void cb_style(Address, Address);

		// the actions:
		void red_pressed() { change(Color::red); hide_menu();}
		void blue_pressed() { change(Color::blue); hide_menu();}
		void black_pressed() { change(Color::black); hide_menu();}
		void menu_pressed() { menu_button.hide(); color_menu.show(); }
		void change(Color c) { lines.set_color(c); redraw();}
		
		void dash_pressed() { style(Line_style::dash); hide_style(); }
		void dot_pressed() { style(Line_style::dot); hide_style(); }
		void line_pressed() { style(Line_style::solid); hide_style(); }
		void style_pressed() { style_button.hide(); style_menu.show(); }
		void style(Line_style s) { lines.set_style(s); redraw();}

		void hide_menu() { color_menu.hide(); menu_button.show(); }
		void hide_style() { style_menu.hide(); style_button.show(); }

	private:

		Button next_button;          // add (next_x,next_y) to lines
		Button quit_button;
		In_box next_x;
		In_box next_y;
		Out_box xy_out;
		Menu color_menu;
		Button menu_button;
		Menu style_menu;
		Button style_button;

		void next();
		void quit();
	};

//------------------------------------------------------------------------------

} // of namespace Graph_lib

#endif // GUI_GUARD
