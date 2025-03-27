#pragma once

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "base/type.h"
#include "platform/api/support.h"
#include "input.h"

namespace anyone {

class PlatformSupport;
// class Font;
// class FreeTypeLibrary;
// class GL_Program;
// class GL_VertexBuffer;
// class GL_Texture2D;
// class DebugText;

// struct DPI {
//     float hori;
//     float vert;
// };

// struct FramebufferSize {
//     int width;
//     int height;
// };

// struct FrameStats {
//     TimePoint frame_start;
//     TimePoint frame_stop;
//     LatestCache<TimeDuration, 8> duration_cache;
//     TimeDuration avg_duration;
//     TimeDuration avg_fps;
// };

struct StartupConfig {
    PlatformSupport* platform_support;
    String project_dir;
};

class Core : public Singleton<Core> {
public:
    Core();
    ~Core();

    void set_startup_config(const StartupConfig& config);

    // void start_game();

    // void notify_framebuffer_size_changed(int width, int height);

    PlatformSupport* get_platform_support() const { return platform_support_; }

    // void dbg_printf(int x, int y, const char* xx, ...);
    // FreeTypeLibrary* get_ft_library() const { return ft_library_.get(); }

    // void notify_dpi_changed(float hdpi, float vdpi);
    // DPI get_dpi() const { return dpi_; }

    // void add_framebuffer_size_listener(FramebufferSizeListener* l);
    // void remove_framebuffer_size_listener(FramebufferSizeListener* l);

    // FramebufferSize get_framebuffer_size() const
    // {
    //     return { framebuffer_width_, framebuffer_height_ };
    // }

    void kick_one_frame();
    void notify_keyboard_event(const KeyboardEvent& event);

private:
    // void fire_framebuffer_size_changed();

    void set_platform_support(PlatformSupport* p);
    void set_project_dir(const String& project_dir);

    void update();
    void render();

    lua_State* lua_;
    PlatformSupport* platform_support_;
    RenderAPI* render_api_;
    // UniquePtr<FreeTypeLibrary> ft_library_;

    Optional<String> project_dir_;
    // UniquePtr<Font> dbg_font_;
    // UniquePtr<DebugText> dbg_text_;

    // int framebuffer_width_;
    // int framebuffer_height_;

    // DPI dpi_;

    // Event<FramebufferSizeListener> framebuffer_size_event_;

    int load_lua();
    static int lua_loader(lua_State* L);

    void init_lua();
    // void run_project();

    // FrameStats frame_stats_;
};

} // namespace anyone

#define GET_CORE()             anyone::Core::get_singleton_ptr()
#define GET_PLATFORM_SUPPORT() ((GET_CORE())->get_platform_support())
#define LOG(...)               (GET_PLATFORM_SUPPORT())->log(__VA_ARGS__)
