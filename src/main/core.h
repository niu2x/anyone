#pragma once

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "type.h"
// #include "platform.h"

namespace anyone {

class PlatformSupport;
class Font;
class FreeTypeLibrary;
class GL_Program;
class GL_VertexBuffer;
class GL_Texture2D;

struct DPI {
    float hori;
    float vert;
};

class Core : public Singleton<Core> {
public:
    Core();
    ~Core();

    void set_platform_support(UniquePtr<PlatformSupport> p);
    void set_project_dir(const String& project_dir);

    void start_game();
    void update();
    void render();

    void notify_framebuffer_size_changed(int width, int height);

    PlatformSupport* get_platform_support() const
    {
        return platform_support_.get();
    }

    void dbg_text(int x, int y, const char* xx);
    FreeTypeLibrary* get_ft_library() const { return ft_library_.get(); }

    void notify_dpi_changed(float hdpi, float vdpi);
    DPI get_dpi() const { return dpi_; }

private:
    lua_State* lua_;
    UniquePtr<PlatformSupport> platform_support_;
    UniquePtr<FreeTypeLibrary> ft_library_;

    Optional<String> project_dir_;
    UniquePtr<Font> dbg_font_;

    int framebuffer_width_;
    int framebuffer_height_;

    GL_Program* test_program_;
    GL_VertexBuffer* test_vertex_buffer_;

    DPI dpi_;

    int load_lua();
    static int lua_loader(lua_State* L);
};

} // namespace anyone