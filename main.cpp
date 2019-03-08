#include <iostream>
#include "drawing.hpp"

using namespace std;

int main(void){
    Canvas canvas{40,40};
    Rectangle rectangle{Point(1,1), Point(20,20)};
    Drawable *rect = &rectangle;
    canvas.draw(rect);
    Rectangle rectangle2{Point(10,10), Point(30,30)};
    Drawable *rect2 = &rectangle2;
    canvas.draw(rect2);
    CanvasDrawerScreen canvasDrawerScreen(canvas);
    canvasDrawerScreen.draw();
    return 0;
}
