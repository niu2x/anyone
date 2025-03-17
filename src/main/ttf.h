#pragma once

#include "gl.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

namespace anyone {

class FreeTypeLibrary {
public:
    FreeTypeLibrary();
    ~FreeTypeLibrary();

private:
    FT_Library ft_library_;
};

class MiniFont {
public:
    MiniFont(int width, int height, int cell_size);
    ~MiniFont();
    void build_ascii_chars(const uint8_t* ttf_font_data);
    void build_chars(const uint8_t* ttf_font_data, const char* chars);

private:
    GL_Texture2D* texture_;
    int cell_size_;
};

} // namespace anyone