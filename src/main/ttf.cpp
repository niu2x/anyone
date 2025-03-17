#include "ttf.h"

namespace anyone {

FreeTypeLibrary::FreeTypeLibrary()
{
    if (FT_Init_FreeType(&ft_library_)) {
        NX_PANIC("freetype init fail");
    }
}
FreeTypeLibrary::~FreeTypeLibrary() { FT_Done_FreeType(ft_library_); }

} // namespace anyone

namespace anyone {

MiniFont::MiniFont(int width, int height, int cell_size) : cell_size_(cell_size)
{
    texture_ = new GL_Texture2D(width, height);
}

MiniFont::~MiniFont() { delete texture_; }

void MiniFont::build_ascii_chars(const uint8_t* ttf_font_data)
{
    build_chars(ttf_font_data,
                "01234567890abcdefghigklmnopqrstuvwxyzABCDEFGHIGKLMNOPQRSTUVWXY"
                "Z:;'\"[]{}!@#$%^&*()-=_+,.<>/?|\\~` ");
}

void MiniFont::build_chars(const uint8_t* ttf_font_data, const char* chars) { }

} // namespace anyone
