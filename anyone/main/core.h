#pragma once

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "base/type.h"
#include "platform/api/support.h"
#include "input.h"
#include "archive.h"
// #include "rml_ui.h"

namespace anyone {

class PlatformSupport;
class MeshManager;
class RenderSystem;
class RML_UI;

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

    void start_game();

    PlatformSupport* get_platform_support() const { return platform_support_; }
    const DPI& get_dpi() const { return dpi_; }
    RenderAPI* get_render_api() const { return render_api_; }
    MeshManager* get_mesh_manager() const { return mesh_manager_.get(); }
    RenderSystem* get_render_system() const { return render_system_.get(); }

    // void dbg_printf(int x, int y, const char* xx, ...);
    // FreeTypeLibrary* get_ft_library() const { return ft_library_.get(); }

    void notify_dpi_changed();
    void notify_framebuffer_size_changed();
    void notify_keyboard_event(const KeyboardEvent& event);

    // void add_framebuffer_size_listener(FramebufferSizeListener* l);
    // void remove_framebuffer_size_listener(FramebufferSizeListener* l);

    const IntSize& get_framebuffer_size() const { return framebuffer_size_; }

    UniquePtr<Read> read_builtin_file(const String& path);
    UniquePtr<Read> read_file_system_file(const String& path);
    UniquePtr<Read> read_file(const String& file_uri);
    Optional<ByteBuffer> read_file_data(const String& file_uri);

private:
    // void fire_framebuffer_size_changed();

    void set_platform_support(PlatformSupport* p);
    void set_project_dir(const String& project_dir);

    void update();
    void render();

    void setup_after_render_api_ready();
    void cleanup_before_render_api_gone();

    PlatformSupport* platform_support_;
    RenderAPI* render_api_;
    UniquePtr<Archive> builtin_archive_;
    // UniquePtr<FreeTypeLibrary> ft_library_;

    UniquePtr<RML_UI> debug_layer_;
    UniquePtr<RenderSystem> render_system_;
    UniquePtr<MeshManager> mesh_manager_;

    Optional<String> project_dir_;
    DPI dpi_;
    IntSize framebuffer_size_;
    lua_State* lua_;

    // Event<FramebufferSizeListener> framebuffer_size_event_;

    int load_lua();
    static int lua_loader(lua_State* L);

    void init_lua();
    // void run_project();

    FrameStats frame_stats_;

    void notify_render_api_ready();
};

} // namespace anyone

#define GET_CORE()             anyone::Core::get_singleton_ptr()
#define GET_PLATFORM_SUPPORT() ((GET_CORE())->get_platform_support())
#define GET_RENDER_API()       ((GET_CORE())->get_render_api())
#define LOG(...)               (GET_PLATFORM_SUPPORT())->log(__VA_ARGS__)
