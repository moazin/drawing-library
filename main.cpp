#include <iostream>
#include <cmath>
#include "drawing.hpp"

using namespace std;

float function(float x){
    return cos(10*x);
}

int main(void){
    //Canvas canvas{1500, 1000};
    //Text text("10", 10);
    //canvas.paste(&text, 100, 100);
    //CanvasDrawerWindow drawer;
    //drawer.draw(canvas);
    vector<Point> points; 
    for(float x = -6; x <= 6; x+= 0.01){
        points.push_back(Point{x, function(x)});
    }
    CanvasDrawerWindow drawer;
    Plotter plotter(1500, 1000, Point(100, 100), Point(1400, 900), &drawer);
    plotter.setPoints(points);
    plotter.plot();
    return 0;
}
