#include <iostream>
#include <cmath>
#include "drawing.hpp"

using namespace std;

float function(float x){
    return cos(10*x)*exp(-x);
}

int main(void){
    Canvas canvas{1500, 1000};
    Text text("10", 10);
    canvas.paste(&text, 100, 100);
    CanvasDrawerWindow drawer;
    drawer.draw(canvas);
    return 0;
}
