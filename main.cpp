#include <iostream>
#include "drawing.hpp"

using namespace std;

int main(void){
    Canvas canvas{40,40};

    for(int i = 5; i <= 30; i+=5){
        Line line{Point(5, 5), Point(30, i)};
        canvas.draw(&line);
    }

    CanvasDrawerScreen canvasDrawerScreen(canvas);
    canvasDrawerScreen.draw();
    return 0;
}
