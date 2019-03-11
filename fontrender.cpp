#include <iostream>
#include <stdio.h>
#include <ft2build.h>
#include <vector>
#include <string>
#include FT_FREETYPE_H

using namespace std;

class Character {
    public:
        vector<vector<int>> pixels;
        int width;
        int height;
        int shift_left;
        int shift_top;
        int advance_x;
        int advance_y;
};
class FontRenderer {
    private:
        FT_Face face;
        vector<vector<int>> pixels;
    public:
        FontRenderer(int size){
            FT_Library ft;
            if(FT_Init_FreeType(&ft)) {
                throw "Couldn't init the library";
            }
            if(FT_New_Face(ft, "lucida.ttf", 0, &this->face)) {
                throw "Couldn't open the font";
            }
            FT_Set_Pixel_Sizes(this->face, 0, size);
        }
        Character render(char character){
            if(FT_Load_Char(this->face, character, FT_LOAD_RENDER)) {
                throw "Couldn't render the character";
            }
            FT_GlyphSlot g = this->face->glyph;
            int width = g->bitmap.width;
            int height = g->bitmap.rows;
            vector<vector<int>> pixel_canvas;
            int count = 0;
            for(int i = 0; i < height; i++){
                vector<int> row;
                for(int j = 0; j < width; j++){
                    row.push_back(g->bitmap.buffer[count]);
                    count++;
                }
                pixel_canvas.push_back(row); 
            } 
            Character new_char;
            new_char.pixels = pixel_canvas;
            new_char.width = g->bitmap.width;
            new_char.height = g->bitmap.rows;
            new_char.shift_left = g->bitmap_left;
            new_char.shift_top = g->bitmap_top;
            new_char.advance_x = g->advance.x;
            new_char.advance_y = g->advance.y;
            return new_char;
        }
};

int main(void){
    FontRenderer renderer(10);
    vector<vector<int>> canvas;
    int current_height = 0;
    int current_width = 0;
    int cursor = -1;
    string sentence = "Nomi jannati";
    for(int z = 0; z < sentence.size(); z++){
        char c = sentence[z];
        Character chr = renderer.render(c);
        vector<vector<int>> pixels_character = chr.pixels;
        int width = chr.width;
        int height = chr.height;
        if(height > current_height){
            int diff = height - current_height;
            vector<int> tmp;
            canvas.insert(canvas.begin(), diff, tmp);
            current_height = height;
        }
        for(int i = 0; i < current_height; i++){
            int width_to_alocate = current_width + width;
            int width_current_row = canvas[i].size();
            for(int j = width_current_row; j < width_to_alocate; j++){
                canvas[i].push_back(0);
            }
        }
        current_width = canvas[0].size();
        // let's paste the stuff inside the array
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                int pixel = pixels_character[i][j];
                canvas[i + (current_height - height)][cursor + 1 + j] = pixel;
            }
        }
        cursor = current_width - 1;
    }
    for(int i = 0; i < current_height; i++){
        for(int j = 0; j < current_width; j++){
            if(canvas[i][j] > 100)
                cout << "\033[1;31m1" << " ";
            else
                cout << "\033[0m0" << " ";
        }
        cout << endl;
    }
    return 0;
}
