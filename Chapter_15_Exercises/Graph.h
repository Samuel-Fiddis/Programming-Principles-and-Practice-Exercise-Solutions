
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef GRAPH_GUARD
#define GRAPH_GUARD 1

#include <FL/fl_draw.H>
#include <FL/Fl_Image.H>
#include "Point.h"
#include "std_lib_facilities.h"

namespace Graph_lib {

// defense against ill-behaved Linux macros:
#undef major
#undef minor

//------------------------------------------------------------------------------

// Color is the type we use to represent color. We can use Color like this:
//    grid.set_color(Color::red);
struct Color {
    enum Color_type {
        red=FL_RED,
        blue=FL_BLUE,
        green=FL_GREEN,
        yellow=FL_YELLOW,
        white=FL_WHITE,
        black=FL_BLACK,
        magenta=FL_MAGENTA,
        cyan=FL_CYAN,
        dark_red=FL_DARK_RED,
        dark_green=FL_DARK_GREEN,
        dark_yellow=FL_DARK_YELLOW,
        dark_blue=FL_DARK_BLUE,
        dark_magenta=FL_DARK_MAGENTA,
        dark_cyan=FL_DARK_CYAN
    };

    enum Transparency { invisible = 0, visible=255 };

    Color(Color_type cc) :c(Fl_Color(cc)), v(visible) { }
    Color(Color_type cc, Transparency vv) :c(Fl_Color(cc)), v(vv) { }
    Color(int cc) :c(Fl_Color(cc)), v(visible) { }
    Color(Transparency vv) :c(Fl_Color()), v(vv) { }    // default color

    int as_int() const { return c; }

    char visibility() const { return v; } 
    void set_visibility(Transparency vv) { v=vv; }
private:
    char v;    // invisible and visible for now
    Fl_Color c;
};

//------------------------------------------------------------------------------

struct Line_style {
    enum Line_style_type {
        solid=FL_SOLID,            // -------
        dash=FL_DASH,              // - - - -
        dot=FL_DOT,                // ....... 
        dashdot=FL_DASHDOT,        // - . - . 
        dashdotdot=FL_DASHDOTDOT,  // -..-..
    };

    Line_style(Line_style_type ss) :s(ss), w(0) { }
    Line_style(Line_style_type lst, int ww) :s(lst), w(ww) { }
    Line_style(int ss) :s(ss), w(0) { }

    int width() const { return w; }
    int style() const { return s; }
private:
    int s;
    int w;
};

//------------------------------------------------------------------------------

class Font {
public:
    enum Font_type {
        helvetica=FL_HELVETICA,
        helvetica_bold=FL_HELVETICA_BOLD,
        helvetica_italic=FL_HELVETICA_ITALIC,
        helvetica_bold_italic=FL_HELVETICA_BOLD_ITALIC,
        courier=FL_COURIER,
        courier_bold=FL_COURIER_BOLD,
        courier_italic=FL_COURIER_ITALIC,
        courier_bold_italic=FL_COURIER_BOLD_ITALIC,
        times=FL_TIMES,
        times_bold=FL_TIMES_BOLD,
        times_italic=FL_TIMES_ITALIC,
        times_bold_italic=FL_TIMES_BOLD_ITALIC,
        symbol=FL_SYMBOL,
        screen=FL_SCREEN,
        screen_bold=FL_SCREEN_BOLD,
        zapf_dingbats=FL_ZAPF_DINGBATS
    };

    Font(Font_type ff) :f(ff) { }
    Font(int ff) :f(ff) { }

    int as_int() const { return f; }
private:
    int f;
};

//------------------------------------------------------------------------------

template<class T> class Vector_ref {
    vector<T*> v;
    vector<T*> owned;
public:
    Vector_ref() {}
    Vector_ref(T& a) { push_back(a); }
    Vector_ref(T& a, T& b);
    Vector_ref(T& a, T& b, T& c);
    Vector_ref(T* a, T* b = 0, T* c = 0, T* d = 0)
    {
        if (a) push_back(a);
        if (b) push_back(b);
        if (c) push_back(c);
        if (d) push_back(d);
    }

    ~Vector_ref() { for (int i=0; i<owned.size(); ++i) delete owned[i]; }

    void push_back(T& s) { v.push_back(&s); }
    void push_back(T* p) { v.push_back(p); owned.push_back(p); }

    T& operator[](int i) { return *v[i]; }
    const T& operator[](int i) const { return *v[i]; }

    int size() const { return v.size(); }
};

//------------------------------------------------------------------------------

typedef double Fct(double);

class Shape  {        // deals with color and style, and holds sequence of lines 
public:
    void draw() const;                 // deal with color and draw lines
    virtual void move(int dx, int dy); // move the shape +=dx and +=dy

    void set_color(Color col) { lcolor = col; }
    Color color() const { return lcolor; }
    void set_style(Line_style sty) { ls = sty; }
    Line_style style() const { return ls; }
    void set_fill_color(Color col) { fcolor = col; }
    Color fill_color() const { return fcolor; }

    Point point(int i) const { return points[i]; } // read only access to points
    int number_of_points() const { return int(points.size()); }

    virtual ~Shape() { }
protected:
    Shape();    
    virtual void draw_lines() const;   // draw the appropriate lines
    void add(Point p);                 // add p to points
    void set_point(int i,Point p);     // points[i]=p;
private:
    vector<Point> points;              // not used by all shapes
    Color lcolor;                      // color for lines and characters
    Line_style ls; 
    Color fcolor;                      // fill color

    Shape(const Shape&);               // prevent copying
    Shape& operator=(const Shape&);
};

//------------------------------------------------------------------------------

struct Function : Shape {
    // the function parameters are not stored
    Function(Fct f, double r1, double r2, Point orig,
        int count = 100, double xscale = 25, double yscale = 25);    
};

//Ch_15_Ex_2--------------------------------------------------------------------

struct Flex_fct : Shape {
	// the function parameters are stored
	Flex_fct(Fct f, double r1, double r2, Point orig,
		int count = 100, double xscale = 25, double yscale = 25);

	void set_range(double range1, double range2);
	void set_origin(Point p);
	void set_scale(double xscale1, double yscale2);
	void set_fct(Fct fun);


private:
	Fct fun;
	double r1, r2, xscale, yscale;
	int count;
	Point orig;
};

//------------------------------------------------------------------------------

struct Line : Shape {            // a Line is a Shape defined by two Points
    Line(Point p1, Point p2);    // construct a line from two points
};

//------------------------------------------------------------------------------

struct Rectangle : Shape {

    Rectangle(Point xy, int ww, int hh) : w(ww), h(hh)
    {
        add(xy);
        if (h<=0 || w<=0) error("Bad rectangle: non-positive side");
    }

    Rectangle(Point x, Point y) : w(y.x-x.x), h(y.y-x.y)
    {
        add(x);
        if (h<=0 || w<=0) error("Bad rectangle: non-positive width or height");
    }
    void draw_lines() const;

    int height() const { return h; }
    int width() const { return w; }
private:
    int h;    // height
    int w;    // width
};

//------------------------------------------------------------------------------

struct Open_polyline : Shape {         // open sequence of lines
    void add(Point p) { Shape::add(p); }
    void draw_lines() const;
};

//------------------------------------------------------------------------------

struct Closed_polyline : Open_polyline { // closed sequence of lines
    void draw_lines() const;
};

//------------------------------------------------------------------------------

struct Polygon : Closed_polyline {    // closed sequence of non-intersecting lines
    void add(Point p);
    void draw_lines() const;
};

//------------------------------------------------------------------------------

struct Lines : Shape {                 // related lines
    void draw_lines() const;
    void add(Point p1, Point p2);      // add a line defined by two points
};

//------------------------------------------------------------------------------

struct Text : Shape {
    // the point is the bottom left of the first letter
    Text(Point x, const string& s) : lab(s), fnt(fl_font()), fnt_sz(fl_size()) { add(x); }

    void draw_lines() const;

    void set_label(const string& s) { lab = s; }
    string label() const { return lab; }

    void set_font(Font f) { fnt = f; }
    Font font() const { return Font(fnt); }

    void set_font_size(int s) { fnt_sz = s; }
    int font_size() const { return fnt_sz; }
private:
    string lab;    // label
    Font fnt;
    int fnt_sz;
};

//------------------------------------------------------------------------------

struct Axis : Shape {
    enum Orientation { x, y, z };
    Axis(Orientation d, Point xy, int length,
        int number_of_notches=0, string label = "");

    void draw_lines() const;
    void move(int dx, int dy);
    void set_color(Color c);

    Text label;
    Lines notches;
};

//Ch_15_Ex_6-------------------------------------------------------------------------

struct Bar_graph : Shape {

	Bar_graph(vector<double> N, Point xy, double xlength, double yscale);

	void draw_lines() const;
	void set_bar_color(int n, Color c);
	void label_bar(int n, string t);

private:
	vector<double> N;
	double xlength, yscale;
	Point orig;
	Vector_ref<Rectangle> bars;
	Vector_ref<Text> labels;
	Text label{ Point{0,0},"" };
};

//------------------------------------------------------------------------------

struct Circle : Shape {
    Circle(Point p, int rr);    // center and radius

    void draw_lines() const;

    Point center() const ; 
    int radius() const { return r; }
    void set_radius(int rr) { r=rr; }
private:
    int r;
};

//Ch_13-Ex_1 -------------------------------------------------------------------------

struct Arc : Shape {
	Arc(Point p, int w, int h, int a, int b)
		: w(w), h(h), a(a), b(b)
	{
		add(Point(p.x - w, p.y - h));
	}

	void draw_lines() const;

	Point center() const { return Point(point(0).x + w, point(0).y + h); }
	Point focus1() const { return Point(center().x + int(sqrt(double(w*w - h*h))), center().y); }
	Point focus2() const { return Point(center().x - int(sqrt(double(w*w - h*h))), center().y); }

	void set_major(int ww) { w = ww; }
	int major() const { return w; }
	void set_minor(int hh) { h = hh; }
	int minor() const { return h; }

private:
	int a, b, w, h;
};

//Ch_13-Ex_2--------------------------------------------------------------------------

struct Box : Shape {
	Box(Point p, int l, int w, int r)
		: l(l), w(w), r(r)
	{
		if (2 * r > l || 2 * r > w) error("Radius too large.");
		add(Point(p.x, p.y));
	}
		
	void draw_lines() const;

private:
	int l, w, r;
};

//Ch_13-Ex_3--------------------------------------------------------------------------

struct Arrow : Shape {
	Arrow(Point p1, Point p2)
	{
		add(p1);    // add p1 to this shape
		add(p2);    // add p2 to this shape) : l(l) {
	}

	void draw_lines() const;
};

//Ch_13-Ex_4--------------------------------------------------------------------------

Point n(const Rectangle& r);

Point ne(const Rectangle& r);

Point e(const Rectangle& r);

Point se(const Rectangle& r);

Point s(const Rectangle& r);

Point sw(const Rectangle& r);

Point w(const Rectangle& r);

Point nw(const Rectangle& r);

Point center(const Rectangle& r);

//Ch_13-Ex_6--------------------------------------------------------------------------

struct Text_Box : Shape {
	Text_Box(Point p, string s)
		: s(s)
	{
		add(Point(p.x, p.y));
		w = 10+ s.size() * 8;
	}

	void draw_lines() const;

private:
	string s;
	int r = 3;
	int w;
	int l=20;
};

//Ch_13-Ex_8--------------------------------------------------------------------------

struct Regular_Hexagon : Shape {
	Regular_Hexagon(Point p, int r)
		: r(r) {
		add(p);
	}

	void draw_lines() const;

private:
	int r;
	Point center;
};

//Ch_13-Ex_10-------------------------------------------------------------------------

struct Regular_Polygon : Closed_polyline {
	Regular_Polygon(Point p, int s, int r, int angle);

	Regular_Polygon(Point p, int s, int r);
	
	void draw_lines() const;

private:
	int s, r, angle;
	double theta;
};

//Ch_14-Ex_1-------------------------------------------------------------------------

struct Smiley : Circle {
	using Circle::Circle;
	void draw_lines() const;
};

struct Frowny : Circle {
	using Circle::Circle;
	void draw_lines() const;
};

struct Frowny_Hat : Frowny {
	using Frowny::Frowny;
	void draw_lines()const;
};

struct Smiley_Hat : Smiley {
	using Smiley::Smiley;
	void draw_lines()const;
};

//Ch_14-Ex_5--------------------------------------------------------------------

struct Striped_rectangle :Rectangle {
	using Rectangle::Rectangle;
	void draw_lines() const;
};

//Ch_14-Ex_6--------------------------------------------------------------------

struct Striped_circle : Circle {
	using Circle::Circle;
	void draw_lines() const;
};

//Ch_14-Ex_7--------------------------------------------------------------------

struct Striped_closed_polyline : Closed_polyline {
	using Closed_polyline::Closed_polyline;
	void draw_lines() const;
};

//Ch_14-Ex_8--------------------------------------------------------------------

struct Octagon : Closed_polyline {
	Octagon(Point p, int r, int angle = 0);

	void draw_lines() const;

private:
	int r, angle;
};

//------------------------------------------------------------------------------

struct Ellipse : Shape {
    Ellipse(Point p, int w, int h)    // center, min, and max distance from center
        : w(w), h(h)
    { 
        add(Point(p.x-w,p.y-h));
    }

    void draw_lines() const;

    Point center() const { return Point(point(0).x+w,point(0).y+h); }
    Point focus1() const { return Point(center().x+int(sqrt(double(w*w-h*h))),center().y); }
    Point focus2() const { return Point(center().x-int(sqrt(double(w*w-h*h))),center().y); }

    void set_major(int ww) { w=ww; }
    int major() const { return w; }
    void set_minor(int hh) { h=hh; }
    int minor() const { return h; }
private:
    int w;
    int h;
};

//------------------------------------------------------------------------------

struct Marked_polyline : Open_polyline {
    Marked_polyline(const string& m) :mark(m) { }
    void draw_lines() const;
private:
    string mark;
};

//------------------------------------------------------------------------------

struct Marks : Marked_polyline {
    Marks(const string& m) :Marked_polyline(m)
    {
        set_color(Color(Color::invisible));
    }
};

//------------------------------------------------------------------------------

struct Mark : Marks {
    Mark(Point xy, char c) : Marks(string(1,c))
    {
        add(xy);
    }
};

//------------------------------------------------------------------------------

struct Suffix {
    enum Encoding { none, jpg, gif  };
};

Suffix::Encoding get_encoding(const string& s);

//------------------------------------------------------------------------------

struct Image : Shape {
    Image(Point xy, string file_name, Suffix::Encoding e = Suffix::none);
    ~Image() { delete p; }
    void draw_lines() const;
    void set_mask(Point xy, int ww, int hh) { w=ww; h=hh; cx=xy.x; cy=xy.y; }
private:
    int w,h;  // define "masking box" within image relative to position (cx,cy)
    int cx,cy; 
    Fl_Image* p;
    Text fn;
};

//------------------------------------------------------------------------------

struct Bad_image : Fl_Image {
    Bad_image(int h, int w) : Fl_Image(h,w,0) { }
    void draw(int x,int y, int, int, int, int) { draw_empty(x,y); }
};

//------------------------------------------------------------------------------

} // of namespace Graph_lib

#endif
