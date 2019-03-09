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
    Plotter plotter(1500, 1000, Point(100, 100), Point(1400, 900), &drawer);
    plotter.setPoints(points);
    plotter.plot();
    return 0;
}
