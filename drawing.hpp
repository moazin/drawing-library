#include <vector>
#include <algorithm>
// imports for the graphics drawing mechanism
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
// for fonts rendering
#include <stdio.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>

using namespace std;

class Character {
    public:
        vector<vector<int>> pixels;
        int width;
        int height;
        int shift_left;
        int shift_top;
        int advance_x;
        int advance_y;
};

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

class Image {
    private:
        int x_size;
        int y_size;
        vector<vector<int>> image;
    public:
        virtual vector<vector<int>> getImage() = 0;
        virtual int getXSize() = 0;
        virtual int getYSize() = 0;
};

class Box: public Image {
    private:
        int x_size;
        int y_size;
        vector<vector<int>> image;
    public:
        Box(int x_size, int y_size);
        vector<vector<int>> getImage();
        int getXSize();
        int getYSize();
};

class FontRenderer {
    private:
        FT_Face face;
        vector<vector<int>> pixels;
    public:
        FontRenderer(int size);
        Character render(char character);
};

class Text: public Image {
    private:
       int x_size; 
       int y_size;
       vector<vector<int>> image;
    public:
       Text(string text, int size);
       vector<vector<int>> getImage();
       int getXSize();
       int getYSize();
};


class Canvas {
    private:
       vector<vector<int>> canvas;
       int x_size;
       int y_size;
    public:
        Canvas(int x_size, int y_size); 
        void draw(MyDrawable *drawable);
        void paste(Image *image, int x, int y);
        int getXSize();
        int getYSize();
        vector<vector<int>> getCanvas();
};


class MyDrawer {
    public:
        virtual void draw(Canvas canvas) = 0;
};

class CanvasDrawerScreen: public MyDrawer {
    private:
        Canvas canvas{10,10};
    public:
        void draw(Canvas canvas);
};

class CanvasDrawerWindow: public MyDrawer {
    private:
        Canvas canvas{10,10};
    public:
        void draw(Canvas canvas);
        void drawpixel(Display* di, Window wi, GC gc, int x, int y, int color);
};

class Plotter {
    private:
        int width;
        int height;
        Point box_bottom_left{0,0};
        Point box_top_right{0,0};
        MyDrawer* drawer;
        vector<Point> points;
    public:
        Plotter(int width, int height, Point box_bottom_left, Point box_top_right, MyDrawer* mydrawer);
        void setPoints(vector<Point> points);
        void plot();
};
