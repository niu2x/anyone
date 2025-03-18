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
class DebugText;

struct DPI {
    float hori;
    float vert;
};

struct FramebufferSize {
    int width;
    int height;
};

class Core : public Singleton<Core> {
public:
    class FramebufferSizeListener {
    public:
        virtual ~FramebufferSizeListener() { }
        virtual void on_framebuffer_size_changed() { }
    };

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

    void add_framebuffer_size_listener(FramebufferSizeListener* l);
    void remove_framebuffer_size_listener(FramebufferSizeListener* l);

    FramebufferSize get_framebuffer_size() const
    {
        return { framebuffer_width_, framebuffer_height_ };
    }

    GL_Program* get_dbg_text_program() const { return dbg_text_program_; }

private:
    void fire_framebuffer_size_changed();

    lua_State* lua_;
    UniquePtr<PlatformSupport> platform_support_;
    UniquePtr<FreeTypeLibrary> ft_library_;

    Optional<String> project_dir_;
    UniquePtr<Font> dbg_font_;
    UniquePtr<DebugText> dbg_text_;
    GL_Program* dbg_text_program_;

    int framebuffer_width_;
    int framebuffer_height_;

    GL_Program* test_program_;
    GL_VertexBuffer* test_vertex_buffer_;

    DPI dpi_;

    Event<FramebufferSizeListener> framebuffer_size_event_;

    int load_lua();
    static int lua_loader(lua_State* L);
};

} // namespace anyone