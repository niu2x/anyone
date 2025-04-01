#include "support.h"
#include "main/core.h"
#include "glad/include/glad/glad.h"

namespace anyone {

// Shader sources
const char* vertex_source = R"(
    #version 330 core
    uniform vec2 offset;
    uniform vec2 canvas_size;

    layout(location = 0) in vec2 position;
    layout(location = 1) in vec2 uv;
    layout(location = 2) in vec4 color;
    out vec4 v_color;
    out vec2 v_uv;
    void main() {
        vec2 pos = position;
        pos += offset;
        pos.y = canvas_size.y - pos.y;
        gl_Position = vec4(pos/canvas_size*2-vec2(1.0,1.0), 0.0, 1.0);
        v_color = color;
        v_uv = uv;
    }

)";

const char* fragment_source = R"(
    #version 330 core
    uniform sampler2D tex;

    in vec2 v_uv;
    in vec4 v_color;
    out vec4 color;
    void main() {
        color = texture(tex, v_uv) * v_color;
    }
)";

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

GLuint compile_program(GLuint shaders[], int nr)
{
    GLuint name = glCreateProgram();
    for (int i = 0; i < nr; i++) {
        glAttachShader(name, shaders[i]);
    }
    glLinkProgram(name);

    GLint status;
    glGetProgramiv(name, GL_LINK_STATUS, &status);

    if (status != GL_TRUE) {
        GLint log_ength;
        glGetProgramiv(name, GL_INFO_LOG_LENGTH, &log_ength);

        char* log = new char[log_ength];
        glGetProgramInfoLog(name, log_ength, nullptr, log);
        LOG("Program link error: %s", log);
        delete[] log;
        glDeleteProgram(name);
        name = 0;
    }

    return name;
}

OpenGL_API::OpenGL_API() { }
OpenGL_API::~OpenGL_API() { }

void OpenGL_API::clear()
{
    // glViewport(0, 0, framebuffer_width_, framebuffer_height_);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGL_API::set_clear_color(const Color& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

Material* OpenGL_API::create_rml_ui_material()
{
    auto m = new GL_Material;
    bool succ = m->compile_program(vertex_source, fragment_source);
    NX_ASSERT(succ, "create_rml_ui_material fail");
    return m;
}
void OpenGL_API::destroy_material(Material* m) { delete m; }

VertexBuffer* OpenGL_API::create_vertex_buffer() { return new GL_VertexBuffer; }

void OpenGL_API::destroy_vertex_buffer(VertexBuffer* vbo) { delete vbo; }

Texture2D* OpenGL_API::create_texture_2d() { return new GL_Texture2D; }

void OpenGL_API::destroy_texture_2d(Texture2D* tex) { delete tex; }

IndiceBuffer* OpenGL_API::create_indice_buffer() { return new GL_IndiceBuffer; }

void OpenGL_API::destroy_indice_buffer(IndiceBuffer* veo) { delete veo; }

struct AttrDesc {
    int num_component;
    GLenum type;
    bool normalized;
};
const AttrDesc attrs_desc[] = {
    { 3, GL_FLOAT, false },
    { 2, GL_FLOAT, false },
    { 4, GL_UNSIGNED_BYTE, true },
    { 2, GL_FLOAT, false },
};

GL_VertexBuffer::GL_VertexBuffer() : name_(0) { glGenBuffers(1, &name_); }

GL_VertexBuffer::~GL_VertexBuffer() { glDeleteBuffers(1, &name_); }

void GL_VertexBuffer::apply()
{
    auto cpu_buf = cpu_buffer_.data();
    // NX_ASSERT(cpu_buffer_.size() > 0, "no cpu_buffer");
    glBindBuffer(GL_ARRAY_BUFFER, name_);
    glBufferData(GL_ARRAY_BUFFER, buf_size_, cpu_buf, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

size_t gl_sizeof(GLenum type)
{
    switch (type) {
        case GL_BYTE:
        case GL_UNSIGNED_BYTE:
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

GL_IndiceBuffer::GL_IndiceBuffer() : name_(0) { glGenBuffers(1, &name_); }

GL_IndiceBuffer::~GL_IndiceBuffer() { glDeleteBuffers(1, &name_); }

void GL_IndiceBuffer::apply()
{
    auto cpu_buf = cpu_buffer_.data();
    auto buf_size = count_ * sizeof(uint16_t);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, name_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, buf_size, cpu_buf, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GL_IndiceBuffer::bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, name_); }

void OpenGL_API::draw(const DrawOperation& op)
{
    RenderAPI::draw(op);

    op.vertex_buffer->bind();
    op.indice_buffer->bind();

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

    if (op.texture) {
        op.texture->bind(0);
    }

    if (op.material) {
        op.material->use();

        if (op.material_params) {
            for (size_t i = 0; i < op.material_params_count; i++) {
                auto* param = &op.material_params[i];
                switch (param->value.type) {
                    case MaterialParamType::TEXTURE: {
                        op.material->set_param_texture(param->name,
                                                       param->value.tex_unit);
                        break;
                    }
                    case MaterialParamType::VEC2: {
                        op.material->set_param_vec2(param->name,
                                                    param->value.args);
                        // LOG("set vec2 %s %f %f",
                        //     param->name,
                        //     param->value.args[0],
                        //     param->value.args[1]);
                        break;
                    }
                    case MaterialParamType::VEC3: {
                        op.material->set_param_vec3(param->name,
                                                    param->value.args);
                        break;
                    }
                    case MaterialParamType::VEC4: {
                        op.material->set_param_vec4(param->name,
                                                    param->value.args);
                        break;
                    }
                }
            }
        }
        // op.material->set_param_texture("tex", 1);
    }

    // auto location = glGetUniformLocation(program, "tex");
    // LOG("op.count %d", op.count);
    // LOG("op.material %p", op.material);
    // LOG("op.texture %p", op.texture);
    // glUniform1i(location, 1);

    glDrawElements(GL_TRIANGLES, op.count, GL_UNSIGNED_SHORT, (void*)0);
}

GL_Texture2D::GL_Texture2D() : name_(0) { glGenTextures(1, &name_); }
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
void GL_Texture2D::bind(int tex_unit)
{
    glActiveTexture(GL_TEXTURE0 + tex_unit);
    glBindTexture(GL_TEXTURE_2D, name_);
}

GL_Material::GL_Material() : program_(0) { }
GL_Material::~GL_Material()
{
    if (program_)
        glDeleteProgram(program_);
}

bool GL_Material::compile_program(const char* vertex, const char* fragment)
{

    GLuint shaders[2] = { 0, 0 };
    shaders[0] = compile_shader(GL_VERTEX_SHADER, vertex);
    shaders[1] = compile_shader(GL_FRAGMENT_SHADER, fragment);

    if (shaders[0] && shaders[1]) {
        program_ = anyone::compile_program(shaders, 2);
    }

    if (shaders[0])
        glDeleteShader(shaders[0]);

    if (shaders[1])
        glDeleteShader(shaders[1]);

    return program_ != 0;
}

void GL_Material::set_param_texture(const char* name, int tex_unit)
{
    auto location = glGetUniformLocation(program_, name);
    NX_ASSERT(location >= 0, "invalid uniform: %s", name);
    glUniform1i(location, tex_unit);
    // LOG("set tex %s:%d %d", name, location, tex_unit);
}
void GL_Material::set_param_vec2(const char* name, float args[])
{
    auto location = glGetUniformLocation(program_, name);
    NX_ASSERT(location >= 0, "invalid uniform: %s", name);
    glUniform2fv(location, 1, args);
    // LOG("set vec2 %s:%d %f %f", name, location, args[0], args[1]);
}
void GL_Material::set_param_vec3(const char* name, float args[])
{
    auto location = glGetUniformLocation(program_, name);
    NX_ASSERT(location >= 0, "invalid uniform: %s", name);
    glUniform3fv(location, 1, args);
}
void GL_Material::set_param_vec4(const char* name, float args[])
{
    auto location = glGetUniformLocation(program_, name);
    NX_ASSERT(location >= 0, "invalid uniform: %s", name);
    glUniform4fv(location, 1, args);
}
void GL_Material::use() { glUseProgram(program_); }

} // namespace anyone