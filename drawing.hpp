#include <vector>
// imports for the graphics drawing mechanism
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>


using namespace std;

// stores a single point
class Point {
    private:
        float x;
        float y;
    public:
        Point(float x, float y);
        float getX();
        float getY(); 
};

// abstract base class interface that all drawables must implement
class MyDrawable {
    public:
        virtual vector<Point> renderPoints() = 0;        
};

class Dot: public MyDrawable {
    private:
        Point point{0,0};
    public:
        Dot(Point point);
        vector<Point> renderPoints();
};

class Rectangle: public MyDrawable {
    private:
        Point bottom_left{0,0};
        Point top_right{0,0};
    public:
        Rectangle(Point bottom_left, Point top_right);
        vector<Point> renderPoints();
};

class Line: public MyDrawable {
    private:
        Point one{0,0};
        Point two{0,0};
    public:
        Line(Point one, Point two);
        vector<Point> renderPoints();
};

class Circle: public MyDrawable {
    private:
        Point center{0, 0};
        int radius;
    public:
        Circle(Point center, int radius);
        vector<Point> renderPoints();
};

class Canvas {
    private:
       vector<vector<int>> canvas;
       int x_size;
       int y_size;
    public:
        Canvas(int x_size, int y_size); 
        void draw(MyDrawable *drawable);
        int getXSize();
        int getYSize();
        vector<vector<int>> getCanvas();
};


class CanvasDrawerScreen {
    private:
        Canvas canvas{10,10};
    public:
        CanvasDrawerScreen(Canvas canvas); 
        void draw();
};

class CanvasDrawerWindow {
    private:
        Canvas canvas{10,10};
    public:
        CanvasDrawerWindow(Canvas canvas);
        int draw();
};

class Plotter {
    private:
        vector<Point> points;
    public:
        Plotter(vector<Point> points);
        void plot();
};
