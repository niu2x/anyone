#pragma once

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "base/type.h"
#include "platform/api/support.h"
#include "input.h"
// #include "rml_ui.h"

namespace anyone {

class PlatformSupport;
class RML_UI;
// class Font;
// class FreeTypeLibrary;
// class GL_Program;
// class GL_VertexBuffer;
// class GL_Texture2D;
// class DebugText;

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
    void kick_one_frame();

    // void start_game();

    PlatformSupport* get_platform_support() const { return platform_support_; }
    const DPI& get_dpi() const { return dpi_; }
    RenderAPI* get_render_api() const { return render_api_; }

    // void dbg_printf(int x, int y, const char* xx, ...);
    // FreeTypeLibrary* get_ft_library() const { return ft_library_.get(); }

    void notify_dpi_changed();
    void notify_framebuffer_size_changed();
    void notify_keyboard_event(const KeyboardEvent& event);

    // void add_framebuffer_size_listener(FramebufferSizeListener* l);
    // void remove_framebuffer_size_listener(FramebufferSizeListener* l);

    const IntSize& get_framebuffer_size() const { return framebuffer_size_; }

private:
    // void fire_framebuffer_size_changed();

    void set_platform_support(PlatformSupport* p);
    void set_project_dir(const String& project_dir);

    void update();
    void render();

    PlatformSupport* platform_support_;
    RenderAPI* render_api_;
    // UniquePtr<FreeTypeLibrary> ft_library_;

    UniquePtr<RML_UI> rml_ui_;

    Optional<String> project_dir_;
    DPI dpi_;
    IntSize framebuffer_size_;
    lua_State* lua_;

    // Event<FramebufferSizeListener> framebuffer_size_event_;

    int load_lua();
    static int lua_loader(lua_State* L);

    void init_lua();
    // void run_project();

    // FrameStats frame_stats_;

    void notify_render_api_ready();
};

} // namespace anyone

#define GET_CORE()             anyone::Core::get_singleton_ptr()
#define GET_PLATFORM_SUPPORT() ((GET_CORE())->get_platform_support())
#define GET_RENDER_API()       ((GET_CORE())->get_render_api())
#define LOG(...)               (GET_PLATFORM_SUPPORT())->log(__VA_ARGS__)
