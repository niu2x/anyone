#pragma once

#include "gl.h"

namespace anyone {

class Material {
public:
    Material();
    ~Material();

    void set_program(GL_Program* p);
    void use();

    void set_uniform(const UniformValue& uniform);
    void unset_uniform(const String& name);
    void compile();

private:
    GL_Program* program_;
    std::unordered_map<String, UniformValue> uniforms_;
};

} // namespace anyone