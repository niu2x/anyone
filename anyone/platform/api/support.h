#pragma once

#include "base/type.h"
#include "base/color.h"

namespace anyone {

struct FrameStats {
    TimePoint frame_start;
    TimePoint frame_stop;
    LatestCache<TimeDuration, 8> duration_cache;
    TimeDuration avg_duration;
    TimeDuration avg_fps;
    size_t draw_call;
    void frame_begin();
    void frame_end();
};

struct DPI {
    float hori;
    float vert;
};

struct IntSize {
    int width, height;
};

enum class VertexAttr {
    POSITION_XYZ,
    POSITION_XY,
    COLOR_BYTE_RGBA,
    // COLOR_RGBA,
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

enum ProgramParamType {
    TEXTURE,
    VEC2,
    VEC3,
    VEC4,
};

struct ProgramParamValue {
    ProgramParamType type;
    union {
        int tex_unit;
        float* args;
    };
};

struct ProgramParam {
    const char* name;
    ProgramParamValue value;
};

enum class BlendType {
    NONE,
    // ADD,
    NORMAL,
};

class RenderAPI;

class IndiceBuffer {
public:
    IndiceBuffer();
    virtual ~IndiceBuffer();

    virtual void apply() = 0;
    virtual void bind() = 0;

    void alloc_cpu_buffer(size_t indice_count);
    void free_cpu_buffer();

    uint16_t* get_cpu_buffer()
    {
        NX_ASSERT(cpu_buffer_.size() > 0, "no cpu_buffer");
        return cpu_buffer_.data();
    }

    size_t get_indice_count() const { return count_; }

protected:
    Vector<uint16_t> cpu_buffer_;
    size_t count_;
};

struct VertexIndiceBuffer {
    VertexBuffer* vbo;
    IndiceBuffer* veo;
};

class Texture2D {
public:
    Texture2D();
    virtual ~Texture2D();

    virtual void apply() = 0;
    virtual void bind(int tex_unit) = 0;

    void alloc_cpu_buffer(int w, int h);
    void free_cpu_buffer();

    uint8_t* get_cpu_buffer()
    {
        NX_ASSERT(cpu_buffer_.size() > 0, "no pixels_buffer");
        return cpu_buffer_.data();
    }

    int get_width() const { return width_; }
    int get_height() const { return height_; }

protected:
    int width_, height_;
    ByteBuffer cpu_buffer_;
};

// enum class VertexStrategy {
//     POINT_LIST,
// };

// enum class DrawPrimitive {
//     POINT,
//     LINE,
//     TRIANGLE,
// };

class Program {
public:
    Program();
    virtual ~Program();
    virtual void use() = 0;

    virtual void set_param_texture(const char* name, int tex_unit) = 0;
    virtual void set_param_vec2(const char* name, float args[]) = 0;
    virtual void set_param_vec3(const char* name, float args[]) = 0;
    virtual void set_param_vec4(const char* name, float args[]) = 0;
};

enum class PolygonMode {
    POINT,
    LINE,
    FILL,
};

struct DrawOperation {
    // DrawPrimitive primitive;
    // VertexStrategy strategy;
    PolygonMode polygon_mode;
    VertexBuffer* vertex_buffer;
    IndiceBuffer* indice_buffer;
    size_t count;
    Texture2D* texture;
    Texture2D** textures;

    Program* program;
    ProgramParam* program_params;
    size_t program_params_count;
};

class RenderAPI {
public:
    RenderAPI();
    virtual ~RenderAPI() = 0;
    virtual void clear() = 0;
    virtual void set_clear_color(const Color& color) = 0;
    virtual VertexBuffer* create_vertex_buffer() = 0;
    virtual void destroy_vertex_buffer(VertexBuffer* vbo) = 0;
    virtual IndiceBuffer* create_indice_buffer() = 0;
    virtual void destroy_indice_buffer(IndiceBuffer* vbo) = 0;
    virtual Texture2D* create_texture_2d() = 0;
    virtual void destroy_texture_2d(Texture2D* vbo) = 0;
    virtual void draw(const DrawOperation& operation);
    virtual Program* create_rml_ui_program() = 0;
    virtual void destroy_program(Program* vbo) = 0;
    virtual void set_blend_type(BlendType b) = 0;

    void set_frame_stats(FrameStats* stats) { frame_stats_ = stats; }

private:
    FrameStats* frame_stats_;
};

class PlatformSupport {
public:
    virtual ~PlatformSupport() = 0;

    virtual void init_window() = 0;
    virtual IntSize get_framebuffer_size() const = 0;
    virtual DPI get_dpi() const = 0;
    virtual void swap_buffers() = 0;
    virtual bool poll_events() = 0;

    virtual void log(const char* fmt, ...) = 0;

    virtual void set_full_screen(bool full_screen) = 0;
    virtual bool is_full_screen() const = 0;

    virtual RenderAPI* get_render_api() = 0;
};

} // namespace anyone