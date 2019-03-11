#include <iostream>
#include <cmath>
#include "drawing.hpp"

using namespace std;

float function(float x){
    return cos(10*x)*exp(-x);
}

int main(void){
    vector<Point> points;
    for(float x = 0; x < 1; x+=0.001){
        points.push_back(Point(x, function(x)));
    }
    //CanvasDrawerWindow drawer;
    //Plotter plotter(1500, 1000, Point(100, 100), Point(1400, 900), &drawer);
    //plotter.setPoints(points);
    //plotter.plot();
    Canvas canvas{40, 30};
    Rectangle rect{Point(10, 10), Point(20, 20)};
    canvas.draw(&rect);
    CanvasDrawerScreen drawer;
    drawer.draw(canvas);

    return 0;
}
