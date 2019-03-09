#include "drawing.hpp"
#include <iostream>
#include <cmath>

Point::Point(float x, float y){
    this->x = x;
    this->y = y;
}

float Point::getX(){
    return this->x;
}

float Point::getY(){
    return this->y;
}

Dot::Dot(Point point){
    this->point = point;
}

vector<Point> Dot::renderPoints(){
    vector<Point> points;
    points.push_back(this->point);
    return points;
}

Rectangle::Rectangle(Point bottom_left, Point top_right){
    this->bottom_left = bottom_left;
    this->top_right = top_right;
}

vector<Point> Rectangle::renderPoints(){
    vector<Point> points;
    // let's draw bottom and top lines
    for(int x = this->bottom_left.getX(); x <= this->top_right.getX(); x++){
        points.push_back(Point(x, bottom_left.getY()));
        points.push_back(Point(x, top_right.getY()));
    }
    // let's draw left and right lines
    for(int y = this->bottom_left.getY(); y <= this->top_right.getY(); y++){
        points.push_back(Point(bottom_left.getX(), y));
        points.push_back(Point(top_right.getX(), y)); 
    }
    return points;
}

Line::Line(Point one, Point two){
    this->one = one;
    this->two = two;
}

vector<Point> Line::renderPoints(){
    vector<Point> points;
    float slope = ((float)two.getY() - (float)one.getY())/((float)two.getX() - (float)one.getX());
    for(int x = one.getX(); x <= two.getX(); x++){
        float y = slope*(x-one.getX()) + one.getY();
        points.push_back(Point(x, y));
    }
    return points;
}

Circle::Circle(Point center, int radius){
    this->center = center;
    this->radius = radius;
}

vector<Point> Circle::renderPoints(){
    vector<Point> points;
    for(int x = this->center.getX()-radius; x <= this->center.getX() + this->radius; x++){
        float y_up = sqrt(pow(this->radius, 2) - pow((x-this->center.getX()), 2)) + this->center.getY();
        float y_down = -sqrt(pow(this->radius, 2) - pow((x-this->center.getX()), 2)) + this->center.getY();
        points.push_back(Point(x, y_up));
        points.push_back(Point(x, y_down));
    }    
    return points;
}

Canvas::Canvas(int x_size, int y_size){
    this->x_size = x_size;
    this->y_size = y_size;
    for(int i = 0; i < y_size; i++){
        vector<int> row_tmp; 
        for(int j = 0; j < x_size; j++){
            row_tmp.push_back(0); 
        }
        this->canvas.push_back(row_tmp);
    }
}

int Canvas::getXSize(){
    return this->x_size;
}

int Canvas::getYSize(){
    return this->y_size;
}

vector<vector<int>> Canvas::getCanvas(){
    return this->canvas;
}

void Canvas::draw(MyDrawable *drawable){
    vector<Point> points;
    points = drawable->renderPoints();
    for(int i = 0; i < points.size(); i++){
        Point current_point = points[i];
        int x = (int)current_point.getX();
        int y = (int)current_point.getY();
        if ((x >= 0) && (x <= (x_size-1))){
            if((y >= 0) && (y <= (y_size-1))){
                this->canvas[y][x] = 1;
            }
        }
    }
}

CanvasDrawerScreen::CanvasDrawerScreen(Canvas can){
    this->canvas = can;
}

void CanvasDrawerScreen::draw(){
    vector<vector<int>> canvas;
    canvas = this->canvas.getCanvas();
    for(int i = this->canvas.getYSize()-1; i >= 0; i--){
        for(int j = 0; j < this->canvas.getXSize(); j++){
            if(canvas[i][j] == 1)
                cout << ".";
            else
                cout << " ";
        }
        cout << endl;
    }
}


CanvasDrawerWindow::CanvasDrawerWindow(Canvas can){
    this->canvas = can;
}

// helper method
void drawpixel(Display* di, Window wi, GC gc, int x, int y, int color)
{
	XSetForeground(di, gc, color);
	XDrawPoint(di, wi, gc, x, y);
}
int CanvasDrawerWindow::draw(){
    //Open Display
    Display *di = XOpenDisplay(getenv("DISPLAY"));
    if (di == NULL) {
            printf("Couldn't open display.\n");
            return -1;
    }
    //Create Window
    int const x = 0, y = 0, width = this->canvas.getXSize(), height = this->canvas.getYSize(), border_width = 1;
    int sc    = DefaultScreen(di);
    Window ro = DefaultRootWindow(di);
    Window wi = XCreateSimpleWindow(di, ro, x, y, width, height, border_width, 
                            BlackPixel(di, sc), WhitePixel(di, sc));
    XMapWindow(di, wi); //Make window visible
    XStoreName(di, wi, "Drawing"); // Set window title
    
    //Prepare the window for drawing
    GC gc = XCreateGC(di, ro, 0, NULL);

    //Select what events the window will listen to
    XSelectInput(di, wi, KeyPressMask | ExposureMask);
    XEvent ev;
    int quit = 0;
    while (!quit) {
            int a = XNextEvent(di, &ev);
            if (ev.type == KeyPress)
                    quit = 1; // quit if someone presses a key
            if (ev.type == Expose) {
                    vector<vector<int>> canvas = this->canvas.getCanvas();
                    int xSize = this->canvas.getXSize();
                    int ySize = this->canvas.getYSize();
                    for(int i = 0; i < ySize; i++){
                        for(int j = 0; j < xSize; j++){
                            if(canvas[i][j] == 1){
                                drawpixel(di, wi, gc, j, ySize - 1 - i, 0x000000);
                            }
                        }
                    }
            }
    }
    XFreeGC(di, gc);
    XDestroyWindow(di, wi);
    XCloseDisplay(di);
    return 0;
}

Plotter::Plotter(vector<Point> points){
    this->points = points;
}

void Plotter::plot(){
    // start a canvas
    Canvas canvas{1000, 1000};

    // draw the rectangle bounding box
    Rectangle rect{Point(100, 100), Point(900, 900)};
    canvas.draw(&rect);

    float x_min = this->points[0].getX();
    float x_max = this->points[this->points.size() - 1].getX();
    float y_max = this->points[0].getY();
    float y_min = y_max;
    for(int i = 0; i < this->points.size(); i++){
        Point point = this->points[i];
        if(point.getY() > y_max)
            y_max = point.getY();
        if(point.getY() < y_min)
            y_min = point.getY();
    }

    float slope_x = (900 - 100)/(x_max - x_min);
    float slope_y = (900 - 100)/(y_max - y_min);
    for(int i = 0; i < this->points.size(); i++){
        Point point = this->points[i];
        float real_x = slope_x*(point.getX() - x_min);
        float real_y = slope_y*(point.getY() - y_min);
        real_x += 100;
        real_y += 100;
        Dot dot{Point(real_x, real_y)};
        canvas.draw(&dot);
    }    

    // draw on a new window
    CanvasDrawerWindow canvasDrawerWindow(canvas);
    canvasDrawerWindow.draw();
}


