#include "support.h"
#include "glad/include/glad/glad.h"

namespace anyone {

OpenGL_API::OpenGL_API() { }
OpenGL_API::~OpenGL_API() { }

void OpenGL_API::clear() { glClear(GL_COLOR_BUFFER_BIT); }

void OpenGL_API::set_clear_color(const Color& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

VertexBuffer* OpenGL_API::create_vertex_buffer() { return new GL_VertexBuffer; }

void OpenGL_API::destroy_vertex_buffer(VertexBuffer* vbo) { delete vbo; }

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

GL_VertexBuffer::GL_VertexBuffer() : name_(0) { glGenBuffers(1, &name_); }

GL_VertexBuffer::~GL_VertexBuffer() { glDeleteBuffers(1, &name_); }

void GL_VertexBuffer::apply()
{
    auto cpu_buf = cpu_buffer_.data();
    // NX_ASSERT(cpu_buffer_.size() > 0, "no cpu_buffer");
    glBindBuffer(GL_ARRAY_BUFFER, name_);
    glBufferData(GL_ARRAY_BUFFER, buf_size_, cpu_buf, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

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

} // namespace anyone