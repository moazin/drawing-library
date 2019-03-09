#include <iostream>
#include <stdio.h>
#include <ft2build.h>
#include FT_FREETYPE_H

using namespace std;

int main(void){
    FT_Library ft;
    if(FT_Init_FreeType(&ft)) {
        fprintf(stderr, "Could not init freetype library\n");
        return 1;
    }
    FT_Face face;
    if(FT_New_Face(ft, "lucida.ttf", 0, &face)) {
        fprintf(stderr, "Could not open font\n");
        return 1;
    }
    FT_Set_Pixel_Sizes(face, 0, 10);
    if(FT_Load_Char(face, 'M', FT_LOAD_RENDER)) {
        fprintf(stderr, "Could not load character 'X'\n");
        return 1;
    }
    FT_GlyphSlot g = face->glyph;
    cout << g->bitmap.width << endl;
    cout << g->bitmap.rows << endl;
    int count = 0;
    for(int i = 0; i < g->bitmap.rows; i++){
        for(int j = 0; j < g->bitmap.width; j++){
            int num = *(g->bitmap.buffer+count);
            if(num > 100)
                cout << "1, ";
            else
                cout << "0, ";
            count++;
        }
        cout << endl;
    }

    return 0;
}
