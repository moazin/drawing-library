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

void Canvas::draw(Drawable *drawable){
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

