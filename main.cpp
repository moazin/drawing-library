#include <iostream>
#include "drawing.hpp"

using namespace std;

float function(float x){
    return (x*x)/1000;
}

int main(void){
    Canvas canvas{1000, 1000};

    Rectangle rect{Point(100, 100), Point(900, 900)};
    canvas.draw(&rect);
    for(float x = 0; x <= 800; x += 1){
        float yDot = function(x) + 100;
        float xDot = x + 100;
        if(!((xDot < 100) || (xDot > 900) || (yDot < 100) || (yDot > 900))){
            Dot dot{Point(xDot, yDot)};
            canvas.draw(&dot);
        }
    }
    CanvasDrawerWindow canvasDrawerWindow(canvas);
    canvasDrawerWindow.draw();
    return 0;
}
