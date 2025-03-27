#pragma once

#include <SDL2/SDL.h>
#include "platform/api/support.h"
#include "glad/include/glad/glad.h"

namespace anyone {

class GL_VertexBuffer : public VertexBuffer {
public:
    GL_VertexBuffer();
    ~GL_VertexBuffer();
    void apply() override;
    void bind() override;

private:
    GLuint name_;
};

class OpenGL_API : public RenderAPI {
public:
    OpenGL_API();
    ~OpenGL_API();
    void clear() override;
    void set_clear_color(const Color& color) override;

    VertexBuffer* create_vertex_buffer() override;
    void destroy_vertex_buffer(VertexBuffer* vbo) override;
};

class PlatformLinux : public PlatformSupport {
public:
    PlatformLinux();
    ~PlatformLinux();

    void init_window() override;
    void log(const char* fmt, ...) override;
    void set_full_screen(bool full_screen) override;

    void swap_buffers() override;
    bool poll_events() override;

    RenderAPI* get_render_api() override { return &render_api_; }

private:
    SDL_Window* native_window_;
    SDL_GLContext gl_context_;
    uint32_t window_flags_;
    OpenGL_API render_api_;
};

} // namespace anyone