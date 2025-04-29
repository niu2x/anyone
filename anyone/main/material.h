#pragma once

#include "platform/api/support.h"

namespace anyone {

class Material {
public:
    Material();
    ~Material();
    void set_param_texture(const char* name, int tex_unit);
    void set_param_vec2(const char* name, float args[]);
    void set_param_vec3(const char* name, float args[]);
    void set_param_vec4(const char* name, float args[]);
    void use();
    void set_blend_type(BlendType b);
    void set_program(Program* p);

private:
    BlendType blend_type_;
    Program* program_;
};

} // namespace anyone