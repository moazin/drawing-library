#include <iostream>
#include "drawing.hpp"

using namespace std;

int main(void){
    Canvas canvas{1000, 1000};

    Rectangle rect{Point(100, 100), Point(900, 900)};
    canvas.draw(&rect);

    Line line{Point(100, 100), Point(900, 900)};
    canvas.draw(&line);

    Dot dot{Point(100, 950)};
    canvas.draw(&dot);

    CanvasDrawerWindow canvasDrawerWindow(canvas);
    canvasDrawerWindow.draw();
    return 0;
}
