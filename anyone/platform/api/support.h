#pragma once

#include "base/type.h"
#include "main/color.h"

namespace anyone {

enum class VertexAttr {
    POSITION_XYZ,
    POSITION_XY,
    COLOR_RGBA,
    UV,
    COUNT,
};

using VertexLayout = Vector<VertexAttr>;

class VertexBuffer {
public:
    VertexBuffer();
    virtual ~VertexBuffer();

    virtual void apply() = 0;
    virtual void bind() = 0;

    void alloc_cpu_buffer(size_t buf_size);
    void free_cpu_buffer();

    uint8_t* get_cpu_buffer()
    {
        NX_ASSERT(cpu_buffer_.size() > 0, "no cpu_buffer");
        return cpu_buffer_.data();
    }

    void set_vertex_layout(const VertexLayout& layout);

protected:
    size_t buf_size_;
    ByteBuffer cpu_buffer_;
    VertexLayout vertex_layout_;
};

class RenderAPI {
public:
    virtual ~RenderAPI() = 0;
    virtual void clear() = 0;
    virtual void set_clear_color(const Color& color) = 0;
    virtual VertexBuffer* create_vertex_buffer() = 0;
    virtual void destroy_vertex_buffer(VertexBuffer* vbo) = 0;
};

class PlatformSupport {
public:
    virtual ~PlatformSupport() = 0;

    virtual void init_window() = 0;
    virtual void swap_buffers() = 0;
    virtual bool poll_events() = 0;

    virtual void log(const char* fmt, ...) = 0;
    virtual void set_full_screen(bool full_screen) = 0;

    virtual RenderAPI* get_render_api() = 0;
};

} // namespace anyone