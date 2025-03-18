#pragma once

#include "gl.h"

#include <unordered_map>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

namespace anyone {

class FreeTypeLibrary {
public:
    FreeTypeLibrary();
    ~FreeTypeLibrary();
    bool load_face(const char* key, const uint8_t* data, size_t len);
    void unload_face(const char* key);
    FT_Face get_face(const char* key) const;

private:
    FT_Library ft_library_;
    void clear_faces();
    std::unordered_map<String, FT_Face> faces_;
};

class Font {
public:
    Font(int tex_width, int tex_height, int font_pixel_size);
    ~Font();
    void build_ascii_chars(const uint8_t* font_ptr, size_t font_len);
    void build_chars(const uint8_t* font_ptr,
                     size_t font_len,
                     const char* chars);

    GL_Texture2D* get_texture(int index) const { return textures_[index]; }
    int get_page_num() const { return textures_.size(); }

private:
    Vector<GL_Texture2D*> textures_;
    int cell_size_;
    int tex_width_;
    int tex_height_;
    int font_pixel_size_;
};

} // namespace anyone