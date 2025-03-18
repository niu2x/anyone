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

    glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
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

GL_VertexBuffer::~GL_VertexBuffer() { glDeleteBuffers(1, &name_); }

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
    { 2, GL_FLOAT, false },
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

std::unordered_map<String, GL_Program*> GL_Program::alive_programs_;

GL_Program::GL_Program(const String& key) : key_(key), name_(0)
{
    NX_ASSERT(!alive_programs_.count(key), "program %s exist", key_.c_str());
    alive_programs_[key_] = this;
}

GL_Program::~GL_Program()
{
    alive_programs_.erase(key_);

    if (name_) {
        glDeleteProgram(name_);
    }

    delete_shaders();
}

GL_Program* GL_Program::get_program(const String& key)
{
    auto it = alive_programs_.find(key);
    if (it != alive_programs_.end()) {
        return it->second;
    }
    return nullptr;
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

void GL_Program::set_uniform_vec2(const char* uniform_name, float x, float y)
{
    auto location = glGetUniformLocation(name_, uniform_name);
    NX_ASSERT(location >= 0, "invalid uniform: %s", uniform_name)
    glUniform2f(location, x, y);
}

void GL_Program::set_uniform_vec4(const char* uniform_name,
                                  float x,
                                  float y,
                                  float z,
                                  float w)
{
    auto location = glGetUniformLocation(name_, uniform_name);
    NX_ASSERT(location >= 0, "invalid uniform: %s", uniform_name)
    glUniform4f(location, x, y, z, w);
}

void GL_Program::set_uniform_vec3(const char* uniform_name,
                                  float x,
                                  float y,
                                  float z)
{
    auto location = glGetUniformLocation(name_, uniform_name);
    NX_ASSERT(location >= 0, "invalid uniform: %s", uniform_name)
    glUniform3f(location, x, y, z);
}

void GL_Program::set_uniform_texture(const char* uniform_name, int value)
{
    auto location = glGetUniformLocation(name_, uniform_name);
    NX_ASSERT(location >= 0, "invalid uniform: %s", uniform_name)
    glUniform1i(location, value);
}

void GL_Program::set_uniform(const UniformValue& uniform)
{
    auto name = uniform.name.c_str();
    switch (uniform.type) {
        case UniformType::TEXTURE: {
            auto& v = std::get<UniformTexture>(uniform.value);
            set_uniform_texture(name, v.tex_unit);
            break;
        }
        case UniformType::VEC2: {
            auto& v = std::get<UniformVec2>(uniform.value);
            set_uniform_vec2(name, v.data[0], v.data[1]);
            break;
        }
        case UniformType::VEC3: {
            auto& v = std::get<UniformVec3>(uniform.value);
            set_uniform_vec3(name, v.data[0], v.data[1], v.data[2]);
            break;
        }
        case UniformType::VEC4: {
            auto& v = std::get<UniformVec4>(uniform.value);
            set_uniform_vec4(name, v.data[0], v.data[1], v.data[2], v.data[3]);
            break;
        }
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

void GL_Program::use()
{
    NX_ASSERT(is_ready(), "gl program is not ready");
    glUseProgram(name_);
}

void check_gl_version()
{
    auto gl_version = glGetString(GL_VERSION);
    LOG("OpenGL version: %s", gl_version);
    int major, minor;
    if (sscanf((const char*)gl_version, "%d.%d", &major, &minor) != 2) {
        NX_PANIC("parse gl_version error");
    }

    if (major == 3 || minor >= 3) {
    } else if (major >= 4) {
    } else {
        NX_PANIC("gl_version is too low");
    }
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

GL_Program* create_gl_program(const String& key, const GL_ProgramSource& source)
{
    auto prog = new GL_Program(key);
    prog->attach_shader(GL_Program::ShaderType::VERTEX, source.vertex);
    prog->attach_shader(GL_Program::ShaderType::FRAGMENT, source.fragment);
    prog->compile();
    return prog;
}

void execute_operation(const DrawOperation& op)
{
    switch (op.polygon_mode) {
        case PolygonMode::POINT: {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            break;
        }
        case PolygonMode::LINE: {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        }
        case PolygonMode::FILL: {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        }
    }

    switch (op.primitive) {
        case DrawPrimitive::TRIANGLE: {
            switch (op.strategy) {
                case VertexStrategy::POINT_LIST: {
                    op.vertex_buffer->bind();
                    glDrawArrays(GL_TRIANGLES, 0, op.vertex_count);
                    break;
                }
            }
            break;
        }

        case DrawPrimitive::LINE: {
            switch (op.strategy) {
                case VertexStrategy::POINT_LIST: {
                    op.vertex_buffer->bind();
                    glDrawArrays(GL_LINES, 0, op.vertex_count);
                    break;
                }
            }
            break;
        }

        case DrawPrimitive::POINT: {
            switch (op.strategy) {
                case VertexStrategy::POINT_LIST: {
                    op.vertex_buffer->bind();
                    glDrawArrays(GL_POINTS, 0, op.vertex_count);
                    break;
                }
            }
            break;
        }
    }
}

} // namespace anyone