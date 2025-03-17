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
    NX_ASSERT(cpu_buffer_.data() != nullptr, "no pixels_buffer");
    glBindTexture(GL_TEXTURE_2D, name_);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA8,
                 width_,
                 height_,
                 0,
                 GL_RGBA,
                 GL_BYTE,
                 cpu_buffer_.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void GL_Texture2D::alloc_cpu_buffer()
{
    cpu_buffer_.resize(width_ * height_ * 4);
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

    NX_ASSERT(cpu_buf != nullptr, "no cpu_buffer");
    glBindBuffer(GL_ARRAY_BUFFER, name_);
    glBufferData(GL_ARRAY_BUFFER, buf_size_, cpu_buf, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void GL_VertexBuffer::alloc_cpu_buffer() { cpu_buffer_.resize(buf_size_); }
void GL_VertexBuffer::free_cpu_buffer() { cpu_buffer_.clear(); }

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

} // namespace anyone