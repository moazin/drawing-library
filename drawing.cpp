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


// Box
Box::Box(int x_size, int y_size){
    this->x_size = x_size;
    this->y_size = y_size;  
    for(int i = 0; i < this->y_size; i++){
        vector<int> tmp;
        for(int j = 0; j < this->x_size; j++){
            tmp.push_back(1); 
        }
        this->image.push_back(tmp);
    }
}

int Box::getXSize(){
    return this->x_size;
}
int Box::getYSize(){
    return this->y_size;
}

vector<vector<int>> Box::getImage(){
    return this->image;
}

int Char::getXSize(){
    return this->x_size;
}

int Char::getYSize(){
    return this->y_size;
}

Char::Char(char character, int size){
    FT_Library ft;
    if(!FT_Init_FreeType(&ft)) {
        FT_Face face;
        if(!FT_New_Face(ft, "lucida.ttf", 0, &face)) {
            FT_Set_Pixel_Sizes(face, 0, size);
            if(!FT_Load_Char(face, character, FT_LOAD_RENDER)) {
                // load the main thing we want!
                FT_GlyphSlot g = face->glyph;
                this->x_size = g->bitmap.width;
                this->y_size = g->bitmap.rows;
                int count = 0;
                vector<vector<int>> tmp_array;
                for(int i = 0; i < this->y_size; i++){
                    vector<int> tmp;
                    for(int j = 0; j < this->x_size; j++){
                        int num = g->bitmap.buffer[count];
                        if(num > 120)
                            tmp.push_back(1);
                        else
                            tmp.push_back(0);
                        count++;
                    }
                    tmp_array.push_back(tmp);
                }
            } else {
                fprintf(stderr, "Could not load character\n");
            }
        } else {
            fprintf(stderr, "Could not open font\n");
        }
    } else {
        fprintf(stderr, "Could not init freetype library\n");
    }
}

vector<vector<int>> Char::getImage(){
    return this->image;
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

void Canvas::paste(Image *image, int x, int y){
    int x_size = image->getXSize();
    int y_size = image->getYSize();
    vector<vector<int>> img = image->getImage();
    for(int i = 0; i < y_size; i++){
        for(int j = 0; j < x_size; j++){
            if(img[i][j] == 1){
                this->canvas[i+y][j+x] = 1;
            } else {
                this->canvas[i+y][j+x] = 0;
            }
        }
    } 
}

void CanvasDrawerScreen::draw(Canvas canvas_passed){
    this->canvas = canvas_passed;
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


// helper method
void CanvasDrawerWindow::drawpixel(Display* di, Window wi, GC gc, int x, int y, int color)
{
	XSetForeground(di, gc, color);
	XDrawPoint(di, wi, gc, x, y);
}
void CanvasDrawerWindow::draw(Canvas canvas){
    this->canvas = canvas;
    //Open Display
    Display *di = XOpenDisplay(getenv("DISPLAY"));
    if (di == NULL) {
            printf("Couldn't open display.\n");
            throw "Couldn't open display";
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
                        this->drawpixel(di, wi, gc, j, ySize - 1 - i, 0x000000);
                    }
                }
            }
        }
    }
    XFreeGC(di, gc);
    XDestroyWindow(di, wi);
    XCloseDisplay(di);
}

Plotter::Plotter(int width, int height, Point box_bottom_left, Point box_top_right, MyDrawer* drawer){
    this->width = width;
    this->height = height;
    this->box_bottom_left = box_bottom_left;
    this->box_top_right = box_top_right;
    this->drawer = drawer;
}

void Plotter::setPoints(vector<Point> points){
    this->points = points;
}

void Plotter::plot(){
    // start a canvas
    Canvas canvas{this->width, this->height};

    // draw the rectangle bounding box
    Rectangle rect{this->box_bottom_left, this->box_top_right};
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

    float slope_x = (this->box_top_right.getX() - this->box_bottom_left.getX())/(x_max - x_min);
    float slope_y = (this->box_top_right.getY() - this->box_bottom_left.getY())/(y_max - y_min);
    for(int i = 0; i < this->points.size(); i++){
        Point point = this->points[i];
        float real_x = slope_x*(point.getX() - x_min);
        float real_y = slope_y*(point.getY() - y_min);
        real_x += this->box_bottom_left.getX();
        real_y += this->box_bottom_left.getY();
        Dot dot{Point(real_x, real_y)};
        canvas.draw(&dot);
    }    

    this->drawer->draw(canvas);
}

