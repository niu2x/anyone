#pragma once

#include "platform.h"
#include <unordered_set>
namespace anyone {

class GL_Object {
public:
    GL_Object();
    virtual ~GL_Object() = 0;
};

class GL_Texture2D : public GL_Object {
public:
    GL_Texture2D(int width, int height);
    ~GL_Texture2D();

    void apply();
    void alloc_cpu_buffer();
    void free_cpu_buffer();

    uint8_t* get_cpu_buffer()
    {
        NX_ASSERT(cpu_buffer_.size() > 0, "no pixels_buffer");
        return cpu_buffer_.data();
    }

    int get_width() const { return width_; }
    int get_height() const { return height_; }

    void bind(int tex_unit);

private:
    GLuint name_;
    int width_, height_;
    ByteBuffer cpu_buffer_;
};

enum class VertexAttr {
    POSITION_XYZ,
    POSITION_XY,
    COLOR_RGBA,
    UV,
    COUNT,
};

using VertexLayout = Vector<VertexAttr>;

class GL_VertexBuffer : public GL_Object {
public:
    GL_VertexBuffer(size_t buf_size);
    ~GL_VertexBuffer();

    void apply();
    void alloc_cpu_buffer();
    void free_cpu_buffer();

    uint8_t* get_cpu_buffer()
    {
        NX_ASSERT(cpu_buffer_.size() > 0, "no cpu_buffer");
        return cpu_buffer_.data();
    }

    void set_vertex_layout(const VertexLayout& layout);

    void bind();

    // static void unbind();

private:
    GLuint name_;
    size_t buf_size_;
    ByteBuffer cpu_buffer_;
    VertexLayout vertex_layout_;
};

class GL_Program : public GL_Object {
public:
    enum class ShaderType {
        VERTEX,
        FRAGMENT,
    };

    GL_Program();
    bool attach_shader(ShaderType shader_type, const char* source_code);
    bool compile();
    ~GL_Program();

    bool is_ready() const;
    void use();

    void set_uniform_texture(const char* uniform_name, int value);
    void set_uniform_vec2(const char* uniform_name, float x, float y);

private:
    GLuint name_;
    std::unordered_map<GLenum, GLuint> gl_shaders_;
    static GLenum to_gl(ShaderType type);

    void delete_shaders();
};

void set_global_gl_state();
void check_gl_version();
GL_Program* create_gl_program(const char* vertex_source,
                              const char* fragment_source);

} // namespace anyone