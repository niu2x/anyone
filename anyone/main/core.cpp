#include "core.h"
#include "render_system.h"
#include "model.h"
#include "rml_ui.h"
#include "model_manager.h"
#include "scene_manager.h"
#include "embed/builtin.h"
#include "url-parser/url.hpp"
#include "3rd/nlohmann/json.hpp"
#include "kazmath/kazmath.h"

using json = nlohmann::json;

extern int luaopen_anyone(lua_State* tolua_S);

namespace anyone {

Core::Core()
: platform_support_(nullptr)
, render_api_(nullptr)
, builtin_archive_(nullptr)
, debug_layer_(nullptr)
, render_system_(nullptr)
, model_manager_(nullptr)
, scene_manager_(nullptr)
, project_dir_(std::nullopt)
, dpi_ { 90, 90 }
, framebuffer_size_ { 1, 1 }
, lua_(nullptr)
,lua_main_loop_(0)

{
    builtin_archive_ = nx::fs::create_zip_archive_from_memory(builtin,
                                                              builtin_length);

    camera_.set_eye(200, 200, 200);
    camera_.look_at(0, 0, 0);
    camera_.set_up(0, 1, 0);
    camera_.set_aspect(1);
    camera_.set_fov(60);
    camera_.set_near_clip(1.732);
    camera_.set_far_clip(1000);
    camera_.apply();
}

Core::~Core()
{
    cleanup_before_render_api_gone();
    render_api_ = nullptr;
    platform_support_ = nullptr;
    builtin_archive_.reset();
}

UniquePtr<Read> Core::read_builtin_file(const String& path)
{
    return builtin_archive_->open(path);
}

UniquePtr<Read> Core::read_file_system_file(const String& path)
{
    auto file = std::make_unique<nx::fs::File>(path);
    if (file->open_read()) {
        return file;
    }
    return nullptr;
}

UniquePtr<Read> Core::read_file(const String& file_uri)
{
    try {
        Url u1(file_uri);
        auto scheme = u1.scheme();
        auto path = u1.path();
        if (scheme == "file") {
            return read_file_system_file(path);
        } else if (scheme == "builtin") {
            return read_builtin_file(path);
        } else {
            return nullptr;
        }
    } catch (...) {
        LOG("url parse error: %s\n", file_uri.c_str());
        return nullptr;
    }
}

Optional<ByteBuffer> Core::read_file_data(const String& path)
{
    auto reader = read_file(path);
    if (reader == nullptr)
        return std::nullopt;

    auto ret = reader->read_all();
    if (std::holds_alternative<IO_Error>(ret)) {
        return std::nullopt;
    }
    return std::get<ByteBuffer>(std::move(ret));
}

void Core::set_startup_config(const StartupConfig& config)
{
    set_project_dir(config.project_dir);
    set_platform_support(config.platform_support);
}

void Core::notify_render_api_ready()
{
    notify_framebuffer_size_changed();
    notify_dpi_changed();
    setup_after_render_api_ready();
}

void Core::setup_after_render_api_ready()
{
    render_api_->set_frame_stats(&frame_stats_);
    render_api_->set_clear_color({0.3, 0.3, 0.3, 0.3});

    render_system_ = std::make_unique<RenderSystem>(render_api_);
    model_manager_ = std::make_unique<ModelManager>();
    scene_manager_ = std::make_unique<SceneManager>();

    RML_UI::setup();
    debug_layer_ = std::make_unique<RML_UI>();

    debug_layer_->load_document("builtin:///layout/debug_layer.rml");

    Model::setup();

    lua_ = luaL_newstate();
    init_lua();
}

void Core::cleanup_before_render_api_gone()
{
    lua_close(lua_);
    Model::cleanup();
    debug_layer_.reset();
    RML_UI::cleanup();

    scene_manager_.reset();
    model_manager_.reset();
    render_system_.reset();
}

void Core::update() { 
    if(lua_main_loop_) {
        auto L = lua_;
        lua_rawgeti(L, LUA_REGISTRYINDEX, lua_main_loop_);
        if(lua_isfunction(L, -1)) {
            lua_pcall(L, 0, 0, 0);
        }
    }
}

void Core::render()
{
    render_api_->set_clear_color(scene_manager_->get_sky_color());
    render_api_->clear();

    scene_manager_->render(&camera_);

    debug_layer_->render();
}

void Core::notify_framebuffer_size_changed()
{
    framebuffer_size_ = platform_support_->get_framebuffer_size();
    if (debug_layer_) {
        debug_layer_->notify_framebuffer_size_changed();
    }
    float aspect = (float)framebuffer_size_.width / framebuffer_size_.height;
    camera_.set_aspect(aspect);
    camera_.apply();
}

void Core::notify_dpi_changed() { dpi_ = platform_support_->get_dpi(); }

void Core::set_platform_support(PlatformSupport* p)
{
    platform_support_ = p;

    NX_ASSERT(render_api_ == nullptr, "already had render_api_");
    render_api_ = p->get_render_api();
    if (render_api_) {
        notify_render_api_ready();
        auto dpi = platform_support_->get_dpi();
        LOG("DPI h:%f v:%f", dpi.hori, dpi.vert);
    }
}

void Core::set_project_dir(const String& dir) { project_dir_ = dir; }

int Core::lua_loader(lua_State* L) { return GET_CORE()->load_lua(); }

int Core::load_lua()
{
    auto mod_name = luaL_optstring(lua_, -1, "");
    printf("lua_loader %s\n", mod_name);

    if (!project_dir_) {
        LOG("no project_dir");
        return 0;
    }

    auto file_path = fs::join_path(*project_dir_, "src");
    file_path = fs::join_path(file_path, String(mod_name) + ".lua");

    fs::File lua_file(file_path);
    if (!lua_file.open_read()) {
        LOG("open file fail: %s", file_path.c_str());
        return 0;
    }

    auto read_result = lua_file.read_all();

    if (std::holds_alternative<IO_Error>(read_result)) {
        LOG("read file fail: %s", file_path.c_str());
        return 0;
    }
    auto bytes = std::get<ByteBuffer>(std::move(read_result));
    auto buf_ptr = (const char*)bytes.data();
    auto buf_len = bytes.size();
    auto ret = luaL_loadbuffer(lua_, buf_ptr, buf_len, mod_name);
    if (ret != LUA_OK) {
        LOG("luaL_loadbuffer fail: %s", lua_tolstring(lua_, -1, nullptr));
        return 0;
    }
    return 1;
}

void Core::kick_one_frame()
{
    frame_stats_.frame_begin();

    render();
    update();

    frame_stats_.frame_end();

    char tmp[128];
    {
        auto element = debug_layer_->get_document()->QuerySelector("#fps");
        sprintf(tmp, "%.2f", frame_stats_.avg_fps);
        element->SetInnerRML(tmp);
    }
    {
        auto element = debug_layer_->get_document()->QuerySelector(
            "#draw_call");

        sprintf(tmp, "%lu", frame_stats_.draw_call);
        element->SetInnerRML(tmp);
    }
    debug_layer_->update();

}

void Core::init_lua()
{
    luaL_openlibs(lua_);

    luaopen_anyone(lua_);

    lua_pushcfunction(lua_, lua_loader);
    lua_setglobal(lua_, "__native_lua_loader");
    luaL_dostring(lua_, R"RAW(
        package.searchers = {__native_lua_loader}
    )RAW");

    // kmVec3 pos { 200+1000, 200+1000, 200+1000 };
    // kmVec4 ndc_pos;

    // camera_.transform_vp(&pos, &ndc_pos);
    // LOG("ndc_pos %f %f %f",
    //     ndc_pos.x / ndc_pos.w,
    //     ndc_pos.y / ndc_pos.w,
    //     ndc_pos.z / ndc_pos.w);
}

// void Core::run_project()
// {
//     if (!project_dir_) {
//         NX_PANIC("no project_dir");
//     }
//     auto config_path = fs::join_path(*project_dir_, "project.json");

//     fs::File config_file(config_path);
//     if (!config_file.open_read()) {
//         NX_PANIC("open file fail: %s", config_path.c_str());
//     }

//     auto read_result = config_file.read_all();

//     if (std::holds_alternative<IO_Error>(read_result)) {
//         NX_PANIC("read file fail: %s", config_path.c_str());
//     }
//     auto bytes = std::get<ByteBuffer>(std::move(read_result));
//     json config = json::parse(bytes);
//     auto entry = config["entry"].get<String>();
//     LOG("entry: %s", entry.c_str());

//     std::stringstream ss;
//     ss << "require '";
//     ss << entry;
//     ss << "'";

// }

void Core::start_game()
{
    if (luaL_dostring(lua_, "require 'entry'")) {
        const char* error_msg = lua_tolstring(lua_, -1, nullptr);
        LOG("lua error: %s", error_msg);
    }
}

// void Core::dbg_printf(int x, int y, const char* fmt, ...)
// {
//     va_list args;
//     va_start(args, fmt);
//     dbg_text_->vprintf(x, y, fmt, args);
//     va_end(args);
// }

// void Core::add_framebuffer_size_listener(FramebufferSizeListener* l)
// {
//     framebuffer_size_event_.add_listener(l);
// }

// void Core::remove_framebuffer_size_listener(FramebufferSizeListener* l)
// {
//     framebuffer_size_event_.remove_listener(l);
// }

// void Core::fire_framebuffer_size_changed()
// {
//     framebuffer_size_event_.dispatch(
//         &FramebufferSizeListener::on_framebuffer_size_changed);
// }

void Core::notify_keyboard_event(const KeyboardEvent& event)
{
    if (event.type == KeyboardEventType::PRESS) {
        if (event.key_code == KEY_F) {
            bool full_screen = platform_support_->is_full_screen();
            platform_support_->set_full_screen(!full_screen);
        } else if (event.key_code == KEY_ESCAPE) {
            platform_support_->exit();
        }
    }
}

void Core::notify_mouse_move_event(const MouseMoveEvent& e)
{
    (void)e;
    //     LOG("mouse_move x: %d, y: %d, rel_x: %d, rel_y: %d",
    //         e.x,
    //         e.y,
    //         e.rel_x,
    //         e.rel_y);
}

void Core::notify_mouse_button_event(const MouseButtonEvent& e) { (void)e; }

void Core::notify_mouse_wheel_event(const MouseWheelEvent& e) { (void)e; }

void Core::set_script_main_loop(LUA_FUNCTION func) {
    if(lua_main_loop_ != 0) {
        __tolua_unref_function(lua_, lua_main_loop_);
    }
    lua_main_loop_ = func;
}

void FrameStats::frame_begin()
{
    this->frame_start = time_now();
    this->draw_call = 0;
}

void FrameStats::frame_end()
{
    this->frame_stop = time_now();

    auto cost = time_diff(this->frame_start, this->frame_stop);
    this->duration_cache.push_back(cost);

    this->avg_duration = this->duration_cache.get_avg();
    this->avg_fps = 1000 / this->avg_duration;
}


} // namespace anyone
