
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include <FL/Fl_GIF_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include "Graph.h"
#include <cmath>

//------------------------------------------------------------------------------

namespace Graph_lib {

//------------------------------------------------------------------------------

Shape::Shape() : 
    lcolor(fl_color()),      // default color for lines and characters
    ls(0),                   // default style
    fcolor(Color::invisible) // no fill
{}

//------------------------------------------------------------------------------

void Shape::add(Point p)     // protected
{
    points.push_back(p);
}

//------------------------------------------------------------------------------

void Shape::set_point(int i,Point p)        // not used; not necessary so far
{
    points[i] = p;
}

//------------------------------------------------------------------------------

void Shape::draw_lines() const
{
    if (color().visibility() && 1<points.size())    // draw sole pixel?
        for (unsigned int i=1; i<points.size(); ++i)
            fl_line(points[i-1].x,points[i-1].y,points[i].x,points[i].y);
}

//------------------------------------------------------------------------------

void Shape::draw() const
{
    Fl_Color oldc = fl_color();
    // there is no good portable way of retrieving the current style
    fl_color(lcolor.as_int());            // set color
    fl_line_style(ls.style(),ls.width()); // set style
    draw_lines();
    fl_color(oldc);      // reset color (to previous)
    fl_line_style(0);    // reset line style to default
}

//------------------------------------------------------------------------------


void Shape::move(int dx, int dy)    // move the shape +=dx and +=dy
{
    for (int i = 0; i<points.size(); ++i) {
        points[i].x+=dx;
        points[i].y+=dy;
    }
}

//------------------------------------------------------------------------------

Line::Line(Point p1, Point p2)    // construct a line from two points
{
    add(p1);    // add p1 to this shape
    add(p2);    // add p2 to this shape
}

//------------------------------------------------------------------------------

void Lines::add(Point p1, Point p2)
{
    Shape::add(p1);
    Shape::add(p2);
}

//------------------------------------------------------------------------------

// draw lines connecting pairs of points
void Lines::draw_lines() const
{
    if (color().visibility())
        for (int i=1; i<number_of_points(); i+=2)
            fl_line(point(i-1).x,point(i-1).y,point(i).x,point(i).y);
}

//------------------------------------------------------------------------------

// does two lines (p1,p2) and (p3,p4) intersect?
// if se return the distance of the intersect point as distances from p1
inline pair<double,double> line_intersect(Point p1, Point p2, Point p3, Point p4, bool& parallel) 
{
    double x1 = p1.x;
    double x2 = p2.x;
    double x3 = p3.x;
    double x4 = p4.x;
    double y1 = p1.y;
    double y2 = p2.y;
    double y3 = p3.y;
    double y4 = p4.y;

    double denom = ((y4 - y3)*(x2-x1) - (x4-x3)*(y2-y1));
    if (denom == 0){
        parallel= true;
        return pair<double,double>(0,0);
    }
    parallel = false;
    return pair<double,double>( ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3))/denom,
                                ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3))/denom);
}

//------------------------------------------------------------------------------

//intersection between two line segments
//Returns true if the two segments intersect,
//in which case intersection is set to the point of intersection
bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection){
   bool parallel;
   pair<double,double> u = line_intersect(p1,p2,p3,p4,parallel);
   if (parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1) return false;
   intersection.x = p1.x + u.first*(p2.x - p1.x);
   intersection.y = p1.y + u.first*(p2.y - p1.y);
   return true;
}

//------------------------------------------------------------------------------

void Polygon::add(Point p)
{
    int np = number_of_points();

    if (1<np) {    // check that thenew line isn't parallel to the previous one
        if (p==point(np-1)) error("polygon point equal to previous point");
        bool parallel;
        line_intersect(point(np-1),p,point(np-2),point(np-1),parallel);
        if (parallel)
            error("two polygon points lie in a straight line");
    }

    for (int i = 1; i<np-1; ++i) {    // check that new segment doesn't interset and old point
        Point ignore(0,0);
        if (line_segment_intersect(point(np-1),p,point(i-1),point(i),ignore))
            error("intersect in polygon");
    }
    

    Closed_polyline::add(p);
}

//------------------------------------------------------------------------------

void Polygon::draw_lines() const
{
    if (number_of_points() < 3) error("less than 3 points in a Polygon");
    Closed_polyline::draw_lines();
}

//------------------------------------------------------------------------------

void Open_polyline::draw_lines() const
{
    if (fill_color().visibility()) {
        fl_color(fill_color().as_int());
        fl_begin_complex_polygon();
        for(int i=0; i<number_of_points(); ++i){
            fl_vertex(point(i).x, point(i).y);
        }
        fl_end_complex_polygon();
        fl_color(color().as_int());    // reset color
    }
    
    if (color().visibility())
        Shape::draw_lines();
}

//------------------------------------------------------------------------------

void Closed_polyline::draw_lines() const
{
    Open_polyline::draw_lines();    // first draw the "open poly line part"
    // then draw closing line:
    if (color().visibility())
        fl_line(point(number_of_points()-1).x, 
        point(number_of_points()-1).y,
        point(0).x,
        point(0).y);
}

//------------------------------------------------------------------------------

void draw_mark(Point xy, char c)
{
    static const int dx = 4;
    static const int dy = 4;

    string m(1,c);
    fl_draw(m.c_str(),xy.x-dx,xy.y+dy);
}

//------------------------------------------------------------------------------

void Marked_polyline::draw_lines() const
{
    Open_polyline::draw_lines();
    for (int i=0; i<number_of_points(); ++i) 
        draw_mark(point(i),mark[i%mark.size()]);
}

//------------------------------------------------------------------------------

void Rectangle::draw_lines() const
{
    if (fill_color().visibility()) {    // fill
        fl_color(fill_color().as_int());
        fl_rectf(point(0).x,point(0).y,w,h);
    }

    if (color().visibility()) {    // lines on top of fill
        fl_color(color().as_int());
        fl_rect(point(0).x,point(0).y,w,h);
    }
}

//------------------------------------------------------------------------------

Circle::Circle(Point p, int rr)    // center and radius
:r(rr)
{
    add(Point(p.x-r,p.y-r));       // store top-left corner
}

//------------------------------------------------------------------------------

Point Circle::center() const
{
    return Point(point(0).x+r, point(0).y+r);
}

//------------------------------------------------------------------------------

void Circle::draw_lines() const
{
    if (color().visibility())
        fl_arc(point(0).x,point(0).y,r+r,r+r,0,360);
}

//Ch_13-Ex_1--------------------------------------------------------------------------

void Arc::draw_lines() const
{
	if (color().visibility())
		fl_arc(point(0).x, point(0).y, w + w, h + h, a, b);
}

//Ch_13-Ex_2--------------------------------------------------------------------------

void Box::draw_lines() const
{
	if (color().visibility())
	{
		fl_line((point(0).x - (w / 2) + r), (point(0).y - (l / 2)), (point(0).x + (w / 2) - r), (point(0).y - (l / 2)));
		fl_line((point(0).x + (w / 2)), (point(0).y - (l / 2)+r), (point(0).x + (w / 2)), (point(0).y + (l / 2) - r));
		fl_line((point(0).x + (w / 2) - r), (point(0).y + (l / 2)), (point(0).x - (w / 2) + r), point(0).y + (l / 2));
		fl_line((point(0).x - (w / 2)), (point(0).y + (l / 2) - r), (point(0).x - (w / 2)), (point(0).y - (l / 2) + r));
		fl_arc(point(0).x-(w/2), point(0).y-(l/2), r+r, r+r, 90,180 );
		fl_arc(point(0).x + (w / 2) -(2*r), point(0).y - (l / 2), r + r, r + r, 0, 90);
		fl_arc(point(0).x + (w / 2)- (2 * r), point(0).y + (l / 2)- (2 * r), r + r, r + r, 270, 0);
		fl_arc(point(0).x - (w / 2), point(0).y + (l / 2)- (2 * r), r + r, r + r, 180, 270);
	}
}

//Ch_13-Ex_3---------------------------------------------------------------------------

void Arrow::draw_lines() const
{
	const double quart_pi = 0.25*3.14;
	double r = 0.1*sqrt((point(1).x - point(0).x)*(point(1).x - point(0).x) + (point(1).y - point(0).y)*(point(1).y - point(0).y));
	double x1 = point(0).x;
	double x2 = point(1).x;
	double y1 = point(0).y;
	double y2 = point(1).y;
	double theta = asin((y2 - y1) / (10*r));
	theta += 3* quart_pi;
	double x3a;
	if(x2<x1) x3a = point(1).x - r*(cos(theta));
	else x3a = point(1).x + r*(cos(theta));
	double y3a = point(1).y + r*(sin(theta));
	int x3 = int(x3a);
	int y3 = int(y3a);

	double x4a;
	if (x2 < x1) x4a = point(1).x + r*(sin(theta));
	else x4a = point(1).x - r*(sin(theta));
	double y4a = point(1).y + r*(cos(theta));
	int x4 = int(x4a);
	int y4 = int(y4a);

	fl_line(point(1).x, point(1).y, point(0).x, point(0).y);
	fl_line(point(1).x, point(1).y, x3, y3);
	fl_line(point(1).x, point(1).y, x4, y4);
}

//Ch_13-Ex_4--------------------------------------------------------------------------

Point n(const Rectangle& r)
{
	return Point{ (r.point(0).x + int(0.5*r.width())),r.point(0).y };
};

Point ne(const Rectangle& r)
{
	return Point{ (r.point(0).x + r.width()),r.point(0).y };
};

Point center(const Rectangle& r)
{
	return Point{ (r.point(0).x + int(0.5*r.width())),r.point(0).y + int(0.5*r.height()) };
};

Point e(const Rectangle& r)
{
	return Point{ (r.point(0).x + r.width()),r.point(0).y + int(0.5*r.height()) };
};

Point se(const Rectangle& r)
{
	return Point{ (r.point(0).x + r.width()),r.point(0).y +r.height() };
};

Point s(const Rectangle& r)
{
	return Point{ (r.point(0).x + int(0.5*r.width())),r.point(0).y + r.height() };
};

Point sw(const Rectangle& r)
{
	return Point{ r.point(0).x,r.point(0).y + r.height() };
};

Point w(const Rectangle& r)
{
	return Point{ r.point(0).x ,r.point(0).y + int(0.5*r.height()) };
};

Point nw(const Rectangle& r)
{
	return Point{ r.point(0).x,r.point(0).y };
};

//Ch_13-Ex_6--------------------------------------------------------------------------

void Text_Box::draw_lines() const
{
	if (color().visibility())
	{
		fl_line((point(0).x - (w / 2) + 3), (point(0).y - (l / 2)), (point(0).x + (w / 2) - r), (point(0).y - (l / 2)));
		fl_line((point(0).x + (w / 2)), (point(0).y - (l / 2) + r), (point(0).x + (w / 2)), (point(0).y + (l / 2) - r));
		fl_line((point(0).x + (w / 2) - r), (point(0).y + (l / 2)), (point(0).x - (w / 2) + r), point(0).y + (l / 2));
		fl_line((point(0).x - (w / 2)), (point(0).y + (l / 2) - r), (point(0).x - (w / 2)), (point(0).y - (l / 2) + r));
		fl_arc(point(0).x - (w / 2), point(0).y - (l / 2), r + r, r + r, 90, 180);
		fl_arc(point(0).x + (w / 2) - (2 * r), point(0).y - (l / 2), r + r, r + r, 0, 90);
		fl_arc(point(0).x + (w / 2) - (2 * r), point(0).y + (l / 2) - (2 * r), r + r, r + r, 270, 0);
		fl_arc(point(0).x - (w / 2), point(0).y + (l / 2) - (2 * r), r + r, r + r, 180, 270);

		Text text = { Point{point(0).x - w/2+5,point(0).y + 5},s };
		text.draw_lines();
	}
}

//Ch_13-Ex_8--------------------------------------------------------------------------

void Regular_Hexagon::draw_lines() const
{
	int r_sin = r*sin(0.523599);
	int r_cos = r*cos(0.523599);
	Point ne((point(0).x + r_cos), (point(0).y - r_sin));
	Point n(point(0).x, point(0).y - r);
	Point nw((point(0).x - r_cos), (point(0).y - r_sin));
	Point se((point(0).x + r_cos), (point(0).y + r_sin));
	Point s(point(0).x, point(0).y + r);
	Point sw((point(0).x - r_cos), (point(0).y + r_sin));
	
	Closed_polyline hex;
	hex.add(ne);
	hex.add(n);
	hex.add(nw);
	hex.add(sw);
	hex.add(s);
	hex.add(se);

	hex.draw_lines();
}

//Ch_13-Ex_10---------------------------------------------------------------------------

Regular_Polygon::Regular_Polygon(Point p, int s, int r, int angle)
	: s(s),r(r),angle(angle), theta(2 * 3.14 / s)
{
	for (int i = 0; i < s; ++i)
	{
		add(Point{ (p.x + int(r*cos(i*theta + (angle / 360.0 * 2.0 * 3.14)))),(p.y - int(r*sin(i*theta + (angle / 360.0 * 2.0 * 3.14)))) });
	}
}

Regular_Polygon::Regular_Polygon(Point p, int s, int r)
	: s(s), r(r), angle(0), theta(2 * 3.14 / s)
{
	for (int i = 0; i < s; ++i)
	{
		add(Point{ (p.x + int(r*cos(i*theta + (angle / 360.0 * 2.0 * 3.14)))),(p.y - int(r*sin(i*theta + (angle / 360.0 * 2.0 * 3.14)))) });
	}
}

void Regular_Polygon::draw_lines() const {
	Closed_polyline::draw_lines();
}

//Ch_14-Ex_1--------------------------------------------------------------------

void Smiley::draw_lines() const
{
	Circle::draw_lines();
	
	Arc a{ Point{point(0).x+radius(),point(0).y + (5*radius() / 4) },radius() / 2,radius() / 2,180,0 };
	a.draw_lines();

	Circle c1{ Point{point(0).x + (3 * radius() / 2),point(0).y + (3*radius() / 4) },radius() / 4 };
	Circle c2{ Point{ point(0).x + radius() / 2,point(0).y + (3*radius() / 4) },radius() / 4 };
	c1.draw_lines();
	c2.draw_lines();
}

void Frowny::draw_lines() const
{
	Circle::draw_lines();

	Arc a{ Point{ point(0).x + radius(),point(0).y + (3*radius()/2) },radius() / 2,radius() / 2,0,180 };
	a.draw_lines();

	Circle c1{ Point{ point(0).x + (3 * radius() / 2),point(0).y + (3 * radius() / 4) },radius() / 4 };
	Circle c2{ Point{ point(0).x + radius() / 2,point(0).y + (3 * radius() / 4) },radius() / 4 };
	c1.draw_lines();
	c2.draw_lines();
}


void Frowny_Hat::draw_lines() const
{
	Frowny::draw_lines();

	fl_line( point(0).x,point(0).y + (radius() / 3),point(0).x + (radius() * 2),point(0).y + (radius() / 3));
	
	Rectangle r{ Point{point(0).x + (radius() / 4),point(0).y - (radius()/3)},Point{point(0).x + (7 * radius() / 4),point(0).y+(radius()/3)} };
	r.set_fill_color(Color::black);
	r.draw_lines();

}

void Smiley_Hat::draw_lines() const
{
	Smiley::draw_lines();

	fl_line(point(0).x, point(0).y + (radius() / 3), point(0).x + (radius() * 2), point(0).y + (radius() / 3));

	Rectangle r{ Point{ point(0).x + (radius() / 4),point(0).y - (4*radius() / 3) },Point{ point(0).x + (7 * radius() / 4),point(0).y + (radius() / 3) } };
	r.set_fill_color(Color::black);
	r.draw_lines();

}

//Ch_14-Ex_4--------------------------------------------------------------------



//Ch_14-Ex_5--------------------------------------------------------------------

void Striped_rectangle::draw_lines() const
{
	Rectangle::draw_lines();

	Lines lines;
	for (int i = 0; i < Rectangle::height(); i += 2)
	{
		lines.add(Point{ point(0).x,point(0).y + i }, Point{ point(0).x + width() -1,point(0).y + i });
	}
	lines.draw_lines();
}

//Ch_14-Ex_6--------------------------------------------------------------------

void Striped_circle::draw_lines() const
{
	Circle::draw_lines();

	Lines lines;
	for (int i = 0; i < (radius() * 2); i += 2)
	{
		int y = center().y + radius() - i;
		int x = sqrt(2*radius()*i-(i*i));
		lines.add(Point{ center().x + x,y }, Point{ center().x - x,y });
	}
	lines.draw_lines();
}

//Ch_14-Ex_7--------------------------------------------------------------------

void Striped_closed_polyline::draw_lines() const
{
	Closed_polyline::draw_lines();

	Lines lines;

	int tp = 0;
	int ty = 0;
	int by = 10000000;
	for (int i = 0; i < number_of_points(); ++i)
	{
		if (point(i).y > ty)
		{
			ty = point(i).y;
			tp = i;
		}
		if (point(i).y < by)
		{
			by = point(i).y;
		}
	}

	int pp = tp + 1;
	int mp = tp - 1;
	int cmp = tp;
	int cpp = tp;

	int my = ty;
	int py = ty;

	for (int i = 0; i < (ty - by); i += 2)
	{
		int y = ty - i;

		if (point(mp).y > y)
		{
			my = point(mp).y;
			if (mp == 0) mp = number_of_points() - 1;
			else --mp;
			if (cmp == 0) cmp = number_of_points() - 1;
			else --cmp;
		}

		if (point(pp).y > y)
		{
			py = point(pp).y;
			if (pp == (number_of_points() - 1)) pp = 0;
			else ++pp;
			if (cpp == 0) cpp = number_of_points() - 1;
			else ++cpp;
		}

		double g1 = double(point(cmp).y - point(mp).y) / double(point(cmp).x - point(mp).x);
		double g2 = double(point(cpp).y - point(pp).y) / double(point(cpp).x - point(pp).x);
		lines.add(Point{ point(cmp).x - int((i-(ty-my))/g1),y }, Point{ point(cpp).x - int((i-(ty-py))/g2),y });
	}

	lines.draw_lines();
}

//Ch_14-Ex_8--------------------------------------------------------------------

Octagon::Octagon(Point p, int r, int angle)
	: r(r), angle(angle) {
	for (int i = 0; i < 8; ++i)
	{
		add(Point{ (p.x + int(r*cos(i*0.785 + (angle / 360.0 * 2.0 * 3.14)))),(p.y - int(r*sin(i*0.785 + (angle / 360.0 * 2.0 * 3.14)))) });
	}
}

void Octagon::draw_lines() const
{
	Closed_polyline::draw_lines();
}

//------------------------------------------------------------------------------
void Ellipse::draw_lines() const
{
    if (color().visibility())
        fl_arc(point(0).x,point(0).y,w+w,h+h,0,360);
}

//------------------------------------------------------------------------------

void Text::draw_lines() const
{
    int ofnt = fl_font();
    int osz = fl_size();
    fl_font(fnt.as_int(),fnt_sz);
    fl_draw(lab.c_str(),point(0).x,point(0).y);
    fl_font(ofnt,osz);
}

//------------------------------------------------------------------------------

Axis::Axis(Orientation d, Point xy, int length, int n, string lab) :
    label(Point(0,0),lab)
{
    if (length<0) error("bad axis length");
    switch (d){
    case Axis::x:
    {
        Shape::add(xy); // axis line
        Shape::add(Point(xy.x+length,xy.y));

        if (1<n) {      // add notches
            int dist = length/n;
            int x = xy.x+dist;
            for (int i = 0; i<n; ++i) {
                notches.add(Point(x,xy.y),Point(x,xy.y-5));
                x += dist;
            }
        }
        // label under the line
        label.move(length/3,xy.y+20);
        break;
    }
    case Axis::y:
    {
        Shape::add(xy); // a y-axis goes up
        Shape::add(Point(xy.x,xy.y-length));

        if (1<n) {      // add notches
            int dist = length/n;
            int y = xy.y-dist;
            for (int i = 0; i<n; ++i) {
                notches.add(Point(xy.x,y),Point(xy.x+5,y));
                y -= dist;
            }
        }
        // label at top
        label.move(xy.x-10,xy.y-length-10);
        break;
    }
    case Axis::z:
        error("z axis not implemented");
    }
}

//------------------------------------------------------------------------------

void Axis::draw_lines() const
{
    Shape::draw_lines();
    notches.draw();  // the notches may have a different color from the line
    label.draw();    // the label may have a different color from the line
}

//------------------------------------------------------------------------------

void Axis::set_color(Color c)
{
    Shape::set_color(c);
    notches.set_color(c);
    label.set_color(c);
}

//------------------------------------------------------------------------------

void Axis::move(int dx, int dy)
{
    Shape::move(dx,dy);
    notches.move(dx,dy);
    label.move(dx,dy);
}

//------------------------------------------------------------------------------

Function::Function(Fct f, double r1, double r2, Point xy,
                   int count, double xscale, double yscale)
// graph f(x) for x in [r1:r2) using count line segments with (0,0) displayed at xy
// x coordinates are scaled by xscale and y coordinates scaled by yscale
{
    if (r2-r1<=0) error("bad graphing range");
    if (count <=0) error("non-positive graphing count");
    double dist = (r2-r1)/count;
    double r = r1;
    for (int i = 0; i<count; ++i) {
        add(Point(xy.x+int(r*xscale),xy.y-int(f(r)*yscale)));
        r += dist;
    }
}

//------------------------------------------------------------------------------

bool can_open(const string& s)
// check if a file named s exists and can be opened for reading
{
    ifstream ff(s.c_str());
    return (bool)ff;
}

//------------------------------------------------------------------------------

#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))

Suffix::Encoding get_encoding(const string& s)
{
    struct SuffixMap 
    { 
        const char*      extension;
        Suffix::Encoding suffix;
    };

    static SuffixMap smap[] = {
        {".jpg",  Suffix::jpg},
        {".jpeg", Suffix::jpg},
        {".gif",  Suffix::gif},
    };

    for (int i = 0, n = ARRAY_SIZE(smap); i < n; i++)
    {
        int len = strlen(smap[i].extension);

        if (s.length() >= len && s.substr(s.length()-len, len) == smap[i].extension)
            return smap[i].suffix;
    }

    return Suffix::none;
}

//------------------------------------------------------------------------------

// somewhat over-elaborate constructor
// because errors related to image files can be such a pain to debug
Image::Image(Point xy, string s, Suffix::Encoding e)
    :w(0), h(0), fn(xy,"")
{
    add(xy);

    if (!can_open(s)) {    // can we open s?
        fn.set_label("cannot open \""+s+'\"');
        p = new Bad_image(30,20);    // the "error image"
        return;
    }

    if (e == Suffix::none) e = get_encoding(s);

    switch(e) {        // check if it is a known encoding
    case Suffix::jpg:
        p = new Fl_JPEG_Image(s.c_str());
        break;
    case Suffix::gif:
        p = new Fl_GIF_Image(s.c_str());
        break;
    default:    // Unsupported image encoding
        fn.set_label("unsupported file type \""+s+'\"');
        p = new Bad_image(30,20);    // the "error image"
    }
}

//------------------------------------------------------------------------------

void Image::draw_lines() const
{
    if (fn.label()!="") fn.draw_lines();

    if (w&&h)
        p->draw(point(0).x,point(0).y,w,h,cx,cy);
    else
        p->draw(point(0).x,point(0).y);
}

//------------------------------------------------------------------------------

} // of namespace Graph_lib

