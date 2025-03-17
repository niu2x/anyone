#include "ttf.h"

namespace anyone {

FreeTypeLibrary::FreeTypeLibrary()
{
    if (FT_Init_FreeType(&ft_library_)) {
        NX_PANIC("freetype init fail");
    }
}
FreeTypeLibrary::~FreeTypeLibrary()
{
    clear_faces();
    FT_Done_FreeType(ft_library_);
}

bool FreeTypeLibrary::load_face(const char* key,
                                const uint8_t* data,
                                size_t len)
{
    FT_Face face;
    if (0 != FT_New_Memory_Face(ft_library_, data, len, 0, &face)) {
        return false;
    }

    if (faces_.find(key) != faces_.end()) {
        NX_PANIC("face already exist: %s", key);
    }

    faces_[key] = face;
    return true;
}

void FreeTypeLibrary::unload_face(const char* key)
{
    auto it = faces_.find(key);
    if (it != faces_.end()) {
        FT_Done_Face(it->second);
        faces_.erase(it);
    }
}

void FreeTypeLibrary::clear_faces()
{
    for (auto& it : faces_) {
        FT_Done_Face(it.second);
    }
    faces_.clear();
}

FT_Face FreeTypeLibrary::get_face(const char* key) const
{
    auto it = faces_.find(key);
    if (it != faces_.end()) {
        return it->second;
    }
    NX_PANIC("no such face: %s", key);
    return {};
}

} // namespace anyone

namespace anyone {

Font::Font(int width, int height, int cell_size) : cell_size_(cell_size)
{
    texture_ = new GL_Texture2D(width, height);
}

Font::~Font() { delete texture_; }

void Font::build_ascii_chars(const uint8_t* font_ptr, size_t font_len)
{
    build_chars(font_ptr,
                font_len,
                "01234567890abcdefghigklmnopqrstuvwxyzABCDEFGHIGKLMNOPQRSTUVWXY"
                "Z:;'\"[]{}!@#$%^&*()-=_+,.<>/?|\\~` ");
}

void Font::build_chars(const uint8_t* font_ptr,
                       size_t font_len,
                       const char* chars)
{
    texture_->alloc_cpu_buffer();

    auto ft = GET_CORE()->get_ft_library();
    ft->load_face("dbg_font", font_ptr, font_len);
    auto face = ft->get_face("dbg_font");

    auto dpi = GET_CORE()->get_dpi();

    FT_Set_Char_Size(face, 50 * 64, 0, dpi.hori, dpi.vert);
    auto slot = face->glyph;

    auto pixels = (uint32_t*)texture_->get_cpu_buffer();

    int tex_width = texture_->get_width();
    int tex_height = texture_->get_height();

    if (!FT_Load_Char(face, 'A', FT_LOAD_RENDER)) {
        for (int x = 0; x < slot->bitmap.width; x++) {
            for (int y = 0; y < slot->bitmap.rows; y++) {
                pixels[y * tex_width + x + slot->bitmap_left]
                    = slot->bitmap.buffer[y * slot->bitmap.width + x];
            }
        }

        LOG("load char");
    }

    ft->unload_face("dbg_font");
    texture_->apply();
    texture_->free_cpu_buffer();

    // GLenum err;
    // while ((err = glGetError()) != GL_NO_ERROR) {
    //     LOG("opengl error");
    // }
}

} // namespace anyone
