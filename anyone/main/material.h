#pragma once

#include "platform/api/support.h"

namespace anyone {

// class Material : public Ref {
// public:
//     Material();
//     ~Material();

//     void set_program(GL_Program* p);
//     void use();

//     void set_uniform(const UniformValue& uniform);
//     void unset_uniform(const String& name);
//     void compile();
//     const char* get_type() const override { return "Material"; }
//     void set_blend_type(BlendType b) { blend_ = b; }

// private:
//     GL_Program* program_;
//     std::unordered_map<String, UniformValue> uniforms_;

//     BlendType blend_;
// };

class Material {
public:
    Material();
    virtual ~Material();
    virtual void set_param_texture(const char* name, int tex_unit) = 0;
    virtual void set_param_vec2(const char* name, float args[]) = 0;
    virtual void set_param_vec3(const char* name, float args[]) = 0;
    virtual void set_param_vec4(const char* name, float args[]) = 0;
    virtual void use();
    void set_blend_type(BlendType b) { blend_type_ = b; }

private:
    BlendType blend_type_;
};

} // namespace anyone