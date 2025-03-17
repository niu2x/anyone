#include "gl.h"

namespace anyone {

GL_Object::GL_Object() { }
GL_Object::~GL_Object() { }

GL_Texture2D::GL_Texture2D(int w, int h) : name_(0), width_(w), height_(h)
{
    glGenTextures(1, &name_);
}

GL_Texture2D::~GL_Texture2D() { glDeleteTextures(1, &name_); }

void GL_Texture2D::apply()
{
    NX_ASSERT(cpu_buffer_.size() > 0, "no pixels_buffer");

    // LOG("cpu_buffer_.size() %lu", cpu_buffer_.size());
    // memset(cpu_buffer_.data(), 0xff, cpu_buffer_.size());
    // glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, name_);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA8,
                 width_,
                 height_,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 cpu_buffer_.data());

    LOG("glTexImage2D %d %d %d", name_, width_, height_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GL_Texture2D::alloc_cpu_buffer()
{
    cpu_buffer_.resize(width_ * height_ * 4);
}

void GL_Texture2D::bind(int tex_unit)
{
    glActiveTexture(GL_TEXTURE0 + tex_unit);
    glBindTexture(GL_TEXTURE_2D, name_);
}

void GL_Texture2D::free_cpu_buffer() { cpu_buffer_.clear(); }

} // namespace anyone

namespace anyone {

GL_VertexBuffer::GL_VertexBuffer(size_t size) : buf_size_(size)
{
    glGenBuffers(1, &name_);
}

GL_VertexBuffer::~GL_VertexBuffer() { glDeleteTextures(1, &name_); }

void GL_VertexBuffer::apply()
{
    auto cpu_buf = cpu_buffer_.data();

    NX_ASSERT(cpu_buffer_.size() > 0, "no cpu_buffer");
    glBindBuffer(GL_ARRAY_BUFFER, name_);
    glBufferData(GL_ARRAY_BUFFER, buf_size_, cpu_buf, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GL_VertexBuffer::alloc_cpu_buffer() { cpu_buffer_.resize(buf_size_); }
void GL_VertexBuffer::free_cpu_buffer() { cpu_buffer_.clear(); }

void GL_VertexBuffer::set_vertex_layout(const VertexLayout& layout)
{
    vertex_layout_ = layout;
}

struct AttrDesc {
    int num_component;
    GLenum type;
    bool normalized;
};

const AttrDesc attrs_desc[] = {
    { 3, GL_FLOAT, false },
    { 4, GL_BYTE, true },
    { 2, GL_FLOAT, false },
};

size_t gl_sizeof(GLenum type)
{
    switch (type) {
        case GL_BYTE:
            return 1;
        case GL_FLOAT:
            return 4;
    }

    NX_PANIC("gl_sizeof for %d is not implemented", type);
    return 0;
}

void GL_VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, name_);
    int attr_index = 0;
    size_t stride = 0;

    for (auto attr : vertex_layout_) {
        auto desc = attrs_desc[(int)attr];
        stride += desc.num_component * gl_sizeof(desc.type);
    }

    size_t offset = 0;
    for (auto attr : vertex_layout_) {
        auto desc = attrs_desc[(int)attr];
        glVertexAttribPointer(attr_index,
                              desc.num_component,
                              desc.type,
                              desc.normalized,
                              stride,
                              (void*)offset);
        glEnableVertexAttribArray(attr_index++);
        offset += desc.num_component * gl_sizeof(desc.type);
    }

    for (; attr_index < (int)VertexAttr::COUNT; attr_index++) {
        glDisableVertexAttribArray(attr_index);
    }
}

// void GL_VertexBuffer::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

} // namespace anyone

namespace anyone {

GLuint compile_shader(GLenum shader_type, const char* source)
{
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    // Check for compile errors
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE) {
        GLint log_length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

        char* log = new char[log_length];
        glGetShaderInfoLog(shader, log_length, nullptr, log);
        LOG("compile shader fail: %s", log);

        delete[] log;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GL_Program::GL_Program() : name_(0) { }

GL_Program::~GL_Program()
{
    if (name_) {
        glDeleteProgram(name_);
    }

    delete_shaders();
}
void GL_Program::delete_shaders()
{
    for (auto& it : gl_shaders_) {
        glDeleteShader(it.second);
    }
    gl_shaders_.clear();
}

bool GL_Program::attach_shader(ShaderType shader_type, const char* source_code)
{
    auto gl_shader_type = to_gl(shader_type);
    auto shader = compile_shader(gl_shader_type, source_code);
    if (shader > 0) {
        gl_shaders_[gl_shader_type] = shader;
        return true;
    } else {
        return false;
    }
}

void GL_Program::set_uniform_texture(const char* uniform_name, int value)
{
    auto location = glGetUniformLocation(name_, uniform_name);
    NX_ASSERT(location >= 0, "invalid uniform: %s", uniform_name)
    glUniform1i(location, value);
}

bool GL_Program::compile()
{
    name_ = glCreateProgram();
    for (auto& it : gl_shaders_) {
        glAttachShader(name_, it.second);
    }
    glLinkProgram(name_);

    GLint status;
    glGetProgramiv(name_, GL_LINK_STATUS, &status);

    if (status != GL_TRUE) {
        GLint log_ength;
        glGetProgramiv(name_, GL_INFO_LOG_LENGTH, &log_ength);

        char* log = new char[log_ength];
        glGetProgramInfoLog(name_, log_ength, nullptr, log);
        LOG("Program link error: %s", log);
        delete[] log;
        glDeleteProgram(name_);
        name_ = 0;
    }

    delete_shaders();
    return name_ != 0;
}

bool GL_Program::is_ready() const { return name_ != 0; }

GLenum GL_Program::to_gl(ShaderType type)
{
    switch (type) {
        case ShaderType::VERTEX: {
            return GL_VERTEX_SHADER;
        }
        case ShaderType::FRAGMENT: {
            return GL_FRAGMENT_SHADER;
        }
    }
    NX_PANIC("never go here!");
    return 0;
}

void GL_Program::use()
{
    NX_ASSERT(is_ready(), "gl program is not ready");
    glUseProgram(name_);
}

void set_global_gl_state()
{
    glDisable(GL_MULTISAMPLE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_BLEND);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
}

} // namespace anyone