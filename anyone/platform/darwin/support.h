#pragma once

#include <SDL2/SDL.h>
#include "platform/api/support.h"

namespace anyone {

class Metal_API : public RenderAPI {
public:
    Metal_API(SDL_Renderer *sdl_renderer);
    ~Metal_API();
    void clear() override;

    void set_clear_color(const Color& color) override;
    VertexBuffer* create_vertex_buffer() override;
    void destroy_vertex_buffer(VertexBuffer* vbo) override;
    IndiceBuffer* create_indice_buffer() override;
    void destroy_indice_buffer(IndiceBuffer* vbo) override;
    Texture2D* create_texture_2d() override;
    void destroy_texture_2d(Texture2D* vbo) override;
    void draw(const DrawOperation& operation) override;
    Program* create_rml_ui_program() override;
    void destroy_program(Program* vbo) override;
    void set_blend_type(BlendType b) override;

private:
    void *pimp_;
};

class PlatformDarwin : public PlatformSupport {
public:
    PlatformDarwin();
    ~PlatformDarwin();

    void init_window() override;
    void log(const char* fmt, ...) override;
    void set_full_screen(bool full_screen) override;

    void swap_buffers() override;
    bool poll_events() override;

    RenderAPI* get_render_api() override { return render_api_; }

    IntSize get_framebuffer_size() const override;
    DPI get_dpi() const override;
    bool is_full_screen() const override;

private:
    SDL_Window* native_window_;
    SDL_Renderer *sdl_renderer_;
    uint32_t window_flags_;
    Metal_API *render_api_;
};

} // namespace anyone