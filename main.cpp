#include <iostream>
#include <cmath>
#include "drawing.hpp"

using namespace std;

float function(float x){
    return x*x;
}

int main(void){
    vector<Point> points;
    for(float x = 0; x < 20; x+=0.01){
        points.push_back(Point(x, function(x)));
    }
    CanvasDrawerWindow drawer;
    Plotter plotter(1500, 1000, Point(100, 100), Point(1400, 900), &drawer);
    plotter.setPoints(points);
    plotter.plot();
    for(char c = '0'; c <= 'z'; c++)
    {
        Char img(c, 10);
        cout << img.getXSize() << ", " << img.getYSize() << endl;
    }
    return 0;
}
