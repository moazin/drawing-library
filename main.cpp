#include <iostream>
#include <cmath>
#include "drawing.hpp"

using namespace std;

float function(float x){
    return x*x*x;
}

int main(void){
    vector<Point> points;
    for(float x = -8; x < 8; x+=0.01){
        points.push_back(Point(x, function(x)));
    }
    CanvasDrawerWindow drawer;
    Plotter plotter(100, 40, Point(0, 0), Point(99, 39), &drawer);
    plotter.setPoints(points);
    plotter.plot();
    return 0;
}
