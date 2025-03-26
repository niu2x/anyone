#pragma once

#include "platform.h"
#include <unordered_set>
namespace anyone {

void set_global_gl_state();
void check_gl_version();

class GL_Object : public Ref {
public:
    GL_Object();
    ~GL_Object();

    const char* get_type() const override { return "GL_Object"; }
};

class GL_Texture2D : public GL_Object {
public:
    GL_Texture2D(int width, int height);
    GL_Texture2D(const String& key, int width, int height);
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
    const char* get_type() const override { return "GL_Texture2D"; }
    const String& get_key() const { return key_; }

private:
    GLuint name_;
    int width_, height_;
    ByteBuffer cpu_buffer_;
    String key_;
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

enum UniformType {
    TEXTURE,
    VEC2,
    VEC3,
    VEC4,
};

struct UniformVec4 {
    float data[4];
};

struct UniformVec3 {
    float data[3];
};

struct UniformVec2 {
    float data[2];
};

struct UniformTexture {
    String key;
    RefPtr<GL_Texture2D> texture;
    int tex_unit;
};

struct UniformValue {
    String name;
    UniformType type;
    std::variant<UniformTexture, UniformVec2, UniformVec3, UniformVec4> value;
};

class GL_Program : public GL_Object {
public:
    enum class ShaderType {
        VERTEX,
        FRAGMENT,
    };

    GL_Program(const String& key);
    ~GL_Program();

    bool attach_shader(ShaderType shader_type, const char* source_code);
    bool compile();

    bool is_ready() const;
    void use();

    void set_uniform_texture(const char* uniform_name, int value);
    void set_uniform_vec2(const char* uniform_name, float x, float y);
    void set_uniform_vec3(const char* uniform_name, float x, float y, float z);
    void set_uniform_vec4(const char* uniform_name,
                          float x,
                          float y,
                          float z,
                          float w);

    void set_uniform(const UniformValue& uniform);
    const String& get_key() const { return key_; }

    const char* get_type() const override { return "GL_Program"; }

private:
    String key_;
    GLuint name_;
    std::unordered_map<GLenum, GLuint> gl_shaders_;
    static GLenum to_gl(ShaderType type);

    void delete_shaders();
};

struct GL_ProgramSource {
    const char* vertex;
    const char* fragment;
};

GL_Program* create_gl_program(const String& key,

                              const GL_ProgramSource& source);
// template <class T>
// class RefManager {
// public:
//     RefManager() {}
//     ~RefManager() {}

//     void add(T *obj) {
//     }

//     void remove(const String &key) {
//     }
// private:
//     std::unordered_map<String, RefPtr<T>> objects_;
// };

enum class DrawPrimitive {
    POINT,
    LINE,
    TRIANGLE,
};

enum class VertexStrategy {
    POINT_LIST,
};

enum class PolygonMode {
    POINT,
    LINE,
    FILL,
};

class Material;

struct DrawOperation {
    DrawPrimitive primitive;
    VertexStrategy strategy;
    PolygonMode polygon_mode;

    GL_VertexBuffer* vertex_buffer;
    int vertex_count;
    Material* material;
};

void execute_operation(const DrawOperation& operation);

extern WeakRefCache<GL_Texture2D> alive_textures;
extern WeakRefCache<GL_Program> alive_programs;

} // namespace anyone