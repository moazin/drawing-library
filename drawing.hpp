#include <vector>

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
class Drawable {
    public:
        virtual vector<Point> renderPoints() = 0;        
};

class Rectangle: public Drawable {
    private:
        Point bottom_left{0,0};
        Point top_right{0,0};
    public:
        Rectangle(Point bottom_left, Point top_right);
        vector<Point> renderPoints();
};

class Canvas {
    private:
       vector<vector<int>> canvas;
       int x_size;
       int y_size;
    public:
        Canvas(int x_size, int y_size); 
        void draw(Drawable *drawable);
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
