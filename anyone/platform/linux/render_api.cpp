#include "support.h"
#include "main/core.h"
#include "glad/include/glad/glad.h"

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void OpenGL_API::set_clear_color(const Color& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

Program* OpenGL_API::create_rml_ui_program()
{

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

    auto m = new GL_Program;
    bool succ = m->compile_program(vertex_source, fragment_source);
    NX_ASSERT(succ, "create_rml_ui_program fail");
    // m->set_blend_type(BlendType::NORMAL);
    return m;
}

void OpenGL_API::set_depth_test(bool b)
{
    if (b) {
        glEnable(GL_DEPTH_TEST);

    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

Program* OpenGL_API::create_model_program()
{

    // Shader sources
    const char* vertex_source = R"(
    #version 330 core

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 proj;

    uniform vec3 light_direction;

    layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 normal;
    layout(location = 2) in vec2 uv;

    out vec3 v_normal;
    out vec3 v_world_pos;
    out vec2 v_uv;

    void main() {

        vec4 tmp = vec4(position, 1.0) * model;
        gl_Position = tmp*view*proj;
        v_world_pos = tmp.xyz/tmp.w;

        mat3 norm_matrix = transpose(inverse(mat3(model)));
        v_normal = normalize(normal*norm_matrix);
        v_uv = uv;
    }

)";

    const char* fragment_source = R"(
    #version 330 core

    uniform vec3 ambient_color;
    uniform vec3 eye_pos;

    uniform vec3 light_position;
    uniform vec3 light_color;

    uniform vec4 albedo_color;
    uniform float metallic;
    uniform float roughness;

    uniform sampler2D albedo_tex;
    uniform bool use_albedo_tex;

    uniform vec4 time;

    const float PI = 3.14159265359;

    in vec3 v_normal;
    in vec3 v_world_pos;
    in vec2 v_uv;

    out vec4 color;



    float DistributionGGX(vec3 N, vec3 H, float roughness) {
        float a = roughness * roughness;
        float a2 = a * a;
        float NdotH = max(dot(N, H), 0.0);
        float NdotH2 = NdotH * NdotH;

        float denom = (NdotH2 * (a2 - 1.0) + 1.0);
        denom = PI * denom * denom;

        return a2 / max(denom, 0.0001); // 避免除以0
    }

    // ----------------------------------------------------------------------------
    // 几何遮挡函数 (Geometry Shadowing): Smith-Schlick GGX
    // ----------------------------------------------------------------------------
    float GeometrySchlickGGX(float NdotV, float roughness) {
        float r = (roughness + 1.0);
        float k = (r * r) / 8.0; // 直接光照的调整参数

        float nom = NdotV;
        float denom = NdotV * (1.0 - k) + k;

        return nom / denom;
    }

    float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
        float NdotV = max(dot(N, V), 0.0);
        float NdotL = max(dot(N, L), 0.0);
        float ggx1 = GeometrySchlickGGX(NdotV, roughness);
        float ggx2 = GeometrySchlickGGX(NdotL, roughness);

        return ggx1 * ggx2;
    }

    // ----------------------------------------------------------------------------
    // 菲涅尔方程 (Fresnel): Schlick近似
    // ----------------------------------------------------------------------------
    vec3 FresnelSchlick(float cos_theta, vec3 F0) {
        return F0 + (1.0 - F0) * pow(clamp(1.0 - cos_theta, 0.0, 1.0), 5.0);
    }

    void main() {

        vec3 albedo;
        if(use_albedo_tex) {
            albedo = pow(texture(albedo_tex, v_uv).rgb, vec3(2.2));
        }
        else {
            albedo = albedo_color.rgb;
        }

        float ao = 1.0;

        // 初始化输入向量
        vec3 N = normalize(v_normal);
        vec3 V = normalize(eye_pos - v_world_pos);

        // 基础反射率（非金属0.04，金属用Albedo）
        vec3 F0 = vec3(0.04);
        F0 = mix(F0, albedo, metallic);

        // 直接光照计算
        vec3 Lo = vec3(0.0);
        for (int i = 0; i < 1; ++i) {
            // 计算每盏光的贡献
            vec3 L = normalize(light_position - v_world_pos);
            vec3 H = normalize(V + L);

            // 光线距离衰减
            float distance = length(light_position - v_world_pos);
            float attenuation = 1.0 / (distance * distance);
            vec3 radiance = light_color * attenuation;

            // Cook-Torrance BRDF
            float NDF = DistributionGGX(N, H, roughness);
            float G = GeometrySmith(N, V, L, roughness);
            vec3 F = FresnelSchlick(max(dot(H, V), 0.0), F0);

            // 镜面反射和漫反射比例
            vec3 kS = F;
            vec3 kD = vec3(1.0) - kS;
            kD *= 1.0 - metallic; // 金属无漫反射

            // BRDF组合
            vec3 numerator = NDF * G * F;
            float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
            vec3 specular = numerator / max(denominator, 0.001);

            // 光线贡献 = (漫反射 + 镜面反射) * 辐射度
            float NdotL = max(dot(N, L), 0.0);
            Lo += (kD * albedo / PI + specular) * radiance * NdotL;
        }

        // 环境光照（简化的IBL）
        vec3 ambient = ambient_color * albedo * ao;

        // 最终颜色（HDR -> sRGB）
        color.a = 1.0;
        color.rgb = ambient + Lo;
        color.rgb = color.rgb / (color.rgb + vec3(1.0)); // Reinhard色调映射
        color.rgb = pow(color.rgb, vec3(1.0 / 2.2)); // Linear -> sRGB

    }




)";

    auto m = new GL_Program;
    bool succ = m->compile_program(vertex_source, fragment_source);
    NX_ASSERT(succ, "create_model_program fail");
    // m->set_blend_type(BlendType::NORMAL);
    return m;
}

void OpenGL_API::destroy_program(Program* m) { delete m; }

VertexBuffer* OpenGL_API::create_vertex_buffer() { return new GL_VertexBuffer; }

void OpenGL_API::destroy_vertex_buffer(VertexBuffer* vbo) { delete vbo; }

Texture2D* OpenGL_API::create_texture_2d() { return new GL_Texture2D; }

void OpenGL_API::destroy_texture_2d(Texture2D* tex) { delete tex; }

IndiceBuffer* OpenGL_API::create_indice_buffer() { return new GL_IndiceBuffer; }

void OpenGL_API::destroy_indice_buffer(IndiceBuffer* veo) { delete veo; }

void OpenGL_API::set_blend_type(BlendType b)
{
    switch (b) {
        case BlendType::NONE: {
            glDisable(GL_BLEND);
            break;
        }

        // case BlendType::ADD: {
        //     glEnable(GL_BLEND);
            // glBlendFunc(GL_ONE, GL_ONE);
        //     break;
        // }

        case BlendType::NORMAL: {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;
        }
    }
}

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
    { 3, GL_FLOAT, false },
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

    // if (op.texture) {
    //     op.texture->bind(0);
    // }

    // if (op.program) {
    //     op.program->use();

    //     if (op.program_params) {
    //         for (size_t i = 0; i < op.program_params_count; i++) {
    //             auto* param = &op.program_params[i];
    //             switch (param->value.type) {
    //                 case ProgramParamType::TEXTURE: {
    //                     op.program->set_param_texture(param->name,
    //                                                   param->value.tex_unit);
    //                     break;
    //                 }
    //                 case ProgramParamType::VEC2: {
    //                     op.program->set_param_vec2(param->name,
    //                                                param->value.args);
    //                     // LOG("set vec2 %s %f %f",
    //                     //     param->name,
    //                     //     param->value.args[0],
    //                     //     param->value.args[1]);
    //                     break;
    //                 }
    //                 case ProgramParamType::VEC3: {
    //                     op.program->set_param_vec3(param->name,
    //                                                param->value.args);
    //                     break;
    //                 }
    //                 case ProgramParamType::VEC4: {
    //                     op.program->set_param_vec4(param->name,
    //                                                param->value.args);
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    //     // op.program->set_param_texture("tex", 1);
    // }

    // auto location = glGetUniformLocation(program, "tex");
    // LOG("op.count %d", op.count);
    // LOG("op.program %p", op.program);
    // LOG("op.texture %p", op.texture);
    // glUniform1i(location, 1);

    static GLuint primitives[] = { GL_POINTS, GL_LINES, GL_TRIANGLES };
    auto prim = primitives[(int)op.primitive];
    glDrawElements(prim, op.count, GL_UNSIGNED_SHORT, (void*)0);
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
    switch (pixel_format_) {
        case PixelFormat::RGBA_U8: {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
            glTexImage2D(GL_TEXTURE_2D,
                         0,
                         GL_RGBA8,
                         width_,
                         height_,
                         0,
                         GL_RGBA,
                         GL_UNSIGNED_BYTE,
                         cpu_buffer_.data());
            break;
        }
        case PixelFormat::RGB_U8: {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D,
                         0,
                         GL_RGB8,
                         width_,
                         height_,
                         0,
                         GL_RGB,
                         GL_UNSIGNED_BYTE,
                         cpu_buffer_.data());
            break;
        }
    }

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

GL_Program::GL_Program() : program_(0) { }
GL_Program::~GL_Program()
{
    if (program_)
        glDeleteProgram(program_);
}

bool GL_Program::compile_program(const char* vertex, const char* fragment)
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

void GL_Program::set_param_texture(const char* name, int tex_unit)
{
    auto location = glGetUniformLocation(program_, name);
    // NX_ASSERT(location >= 0, "invalid uniform: %s", name);
    glUniform1i(location, tex_unit);
    // LOG("set tex %s:%d %d", name, location, tex_unit);
}

void GL_Program::set_param_int(const char* name, int arg)
{
    auto location = glGetUniformLocation(program_, name);
    // NX_ASSERT(location >= 0, "invalid uniform: %s", name);
    glUniform1i(location, arg);
    // LOG("set vec2 %s:%d %f %f", name, location, args[0], args[1]);
}

void GL_Program::set_param_float(const char* name, float arg)
{
    auto location = glGetUniformLocation(program_, name);
    // NX_ASSERT(location >= 0, "invalid uniform: %s", name);
    glUniform1f(location, arg);
    // LOG("set vec2 %s:%d %f %f", name, location, args[0], args[1]);
}

void GL_Program::set_param_vec2(const char* name, const float args[])
{
    auto location = glGetUniformLocation(program_, name);
    // NX_ASSERT(location >= 0, "invalid uniform: %s", name);
    glUniform2fv(location, 1, args);
    // LOG("set vec2 %s:%d %f %f", name, location, args[0], args[1]);
}
void GL_Program::set_param_vec3(const char* name, const float args[])
{
    auto location = glGetUniformLocation(program_, name);
    // NX_ASSERT(location >= 0, "invalid uniform: %s", name);
    glUniform3fv(location, 1, args);
}
void GL_Program::set_param_vec4(const char* name, const float args[])
{
    auto location = glGetUniformLocation(program_, name);
    // NX_ASSERT(location >= 0, "invalid uniform: %s", name);
    glUniform4fv(location, 1, args);
}

void GL_Program::set_param_mat4(const char* name, const float args[])
{
    auto location = glGetUniformLocation(program_, name);
    // NX_ASSERT(location >= 0, "invalid uniform: %s", name);
    glUniformMatrix4fv(location, 1, GL_TRUE, args);
}

void GL_Program::use() { glUseProgram(program_); }

} // namespace anyone