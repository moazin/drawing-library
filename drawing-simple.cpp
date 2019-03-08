#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Point {
    public:
        float x;
        float y;
        Point(float x, float y);
};

Point::Point(float x, float y){
    this->x = x;
    this->y = y;
}

int main(void){
    int canvas[40][40];
    // initialize with zeros
    for(int i = 0; i < 40; i++){
        for(int j = 0; j < 40; j++){
            canvas[i][j] = 0;
        }
    }

    // draw shapes here
    vector<Point> points;

    // let's draw a circle
    int radius = 5;
    int center_x = 20;
    int center_y = 20;
    for(float x = (center_x - radius); x <= (center_x + radius); x = x + 0.1){
        float y_up = sqrt(pow(radius, 2) - pow(x - center_x, 2)) + center_y;
        float y_down = -sqrt(pow(radius, 2) - pow(x - center_x, 2)) + center_y;
        points.push_back(Point(x, y_up));
        points.push_back(Point(x, y_down));
    }

    // let's draw a rectangle 
    int length = 12;
    int height = 10;
    int bottom_left_corner_x = 5;
    int bottom_left_corner_y = 5;
    for(int x = bottom_left_corner_x; x <= bottom_left_corner_x + length; x++){
        // top and bottom lines
        int y_down = bottom_left_corner_y;
        points.push_back(Point(x, y_down));
        int y_up = bottom_left_corner_y + height;
        points.push_back(Point(x, y_up));
    }
    // left line
    for(int y = bottom_left_corner_y; y <= bottom_left_corner_y + height; y++){
        int x_left = bottom_left_corner_x;
        int x_right = bottom_left_corner_x + length;
        points.push_back(Point(x_left, y));
        points.push_back(Point(x_right, y));
    }


    // let's iterate through the points
    for(int i = 0; i < points.size(); i++){
        Point current_point = points[i];
        int x = (int)current_point.x;
        int y = (int)current_point.y;
        if ((x >= 0) && (x <= 39)){
            if((y >= 0) && (y <= 39)){
                canvas[y][x] = 1;
            }
        }
    } 

    for(int i = 39; i >= 0; i--){
        for(int j = 0; j < 40; j++){
            if(canvas[i][j] == 1)
                cout << ".";
            else
                cout << " ";
        }
        cout << endl;
    }
    return 0;
}
