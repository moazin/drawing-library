#include <iostream>
#include <cmath>
#include "drawing.hpp"

using namespace std;

float function(float x){
    return exp(-x)*cos(10*x);
}

int main(void){
    vector<Point> points;
    for(float x = -5; x < 0.5; x+=0.01){
        points.push_back(Point(x, function(x)));
    }
    Plotter plotter(points);
    plotter.plot();
    return 0;
}
