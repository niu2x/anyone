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

Font::Font(int tex_width, int tex_height, int font_pixel_size)
: tex_width_(tex_width)
, tex_height_(tex_height)
, font_pixel_size_(font_pixel_size)
, cell_size_(0)
{
    cell_size_ = font_pixel_size_ + 4;
}

Font::~Font()
{
    for (auto tex : textures_) {
        delete tex;
    }
    textures_.clear();
}

void Font::build_ascii_chars(const uint8_t* font_ptr, size_t font_len)
{
    build_chars(font_ptr,
                font_len,
                "0123456789abcdefghigklmnopqrstuvwxyzABCDEFGHIGKLMNOPQRSTUVWXY"
                "Z:;'\"[]{}!@#$%^&*()-=_+,.<>/?|\\~` ");
}

void Font::build_chars(const uint8_t* font_ptr,
                       size_t font_len,
                       const char* chars)
{

    auto ft = GET_CORE()->get_ft_library();
    ft->load_face("dbg_font", font_ptr, font_len);
    auto face = ft->get_face("dbg_font");

    GL_Texture2D* current_tex = nullptr;
    int page_index = -1;

    int page_width = tex_width_ / cell_size_;
    int page_height = tex_height_ / cell_size_;
    FT_Set_Pixel_Sizes(face, font_pixel_size_, font_pixel_size_);
    auto slot = face->glyph;

    auto str_len = strlen(chars);
    for (int i = 0; i < str_len; i++) {
        if (current_tex == nullptr
            || i >= (page_index + 1) * page_width * page_height) {

            if (current_tex) {
                current_tex->apply();
                current_tex->free_cpu_buffer();
            }

            page_index++;
            current_tex = new GL_Texture2D(tex_width_, tex_height_);
            textures_.push_back(current_tex);
            current_tex->alloc_cpu_buffer();
        }

        auto pixels = (uint32_t*)current_tex->get_cpu_buffer();

        if (!FT_Load_Char(face, chars[i], FT_LOAD_RENDER)) {
            for (int x = 0; x < slot->bitmap.width; x++) {
                for (int y = 0; y < slot->bitmap.rows; y++) {
                    auto ii = (i % (page_width * page_height));
                    pixels[(y + ii / page_width * cell_size_) * tex_width_
                           + (x + ii % page_width * cell_size_)
                           + slot->bitmap_left]
                        = slot->bitmap.buffer[y * slot->bitmap.width + x];
                }
            }
            LOG("load char");
        }
    }
    ft->unload_face("dbg_font");

    if (current_tex) {
        current_tex->apply();
        current_tex->free_cpu_buffer();
    }
}

} // namespace anyone
