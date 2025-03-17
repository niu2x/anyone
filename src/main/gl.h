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
        NX_ASSERT(cpu_buffer_.data() != nullptr, "no pixels_buffer");
        return cpu_buffer_.data();
    }

    int get_width() const { return width_; }
    int get_height() const { return height_; }

private:
    GLuint name_;
    int width_, height_;
    ByteBuffer cpu_buffer_;
};

enum class VertexAttr {
    POSITION_XYZ,
    COLOR_RGBA,
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
        NX_ASSERT(cpu_buffer_.data() != nullptr, "no cpu_buffer");
        return cpu_buffer_.data();
    }

    void set_vertex_layout(const VertexLayout& layout);

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

private:
    GLuint name_;
    std::unordered_map<GLenum, GLuint> gl_shaders_;
    static GLenum to_gl(ShaderType type);

    void delete_shaders();
};

} // namespace anyone