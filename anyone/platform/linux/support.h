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

class GL_IndiceBuffer : public IndiceBuffer {
public:
    GL_IndiceBuffer();
    ~GL_IndiceBuffer();
    void apply() override;
    void bind() override;

private:
    GLuint name_;
};

class GL_Texture2D : public Texture2D {
public:
    GL_Texture2D();
    ~GL_Texture2D();
    void apply() override;
    void bind(int tex_unit) override;

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

    IndiceBuffer* create_indice_buffer() override;
    void destroy_indice_buffer(IndiceBuffer* vbo) override;

    void draw(const DrawOperation& operation) override;

    Texture2D* create_texture_2d() override;
    void destroy_texture_2d(Texture2D* vbo) override;
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