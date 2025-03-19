#include "material.h"

namespace anyone {

Material::Material() : program_(nullptr) { }

Material::~Material() { SAFE_RELEASE(program_); }

void Material::set_program(GL_Program* p)
{
    SAFE_RETAIN(p);
    SAFE_RELEASE(program_);
    program_ = p;
}

void Material::use()
{
    program_->use();
    for (auto u : uniforms_) {
        if (u.second.type == UniformType::TEXTURE) {
            auto& tex = std::get<UniformTexture>(u.second.value);
            if (tex.texture) {
                tex.texture->bind(tex.tex_unit);
            }
        }
        program_->set_uniform(u.second);
    }
}

void Material::compile()
{
    int tex_unit = 0;
    for (auto u : uniforms_) {
        if (u.second.type == UniformType::TEXTURE) {
            auto& tex = std::get<UniformTexture>(u.second.value);
            tex.tex_unit = tex_unit++;
            if (tex.key != "") {
                tex.texture = GL_Texture2D::get_texture(tex.key);
            }
        }
    }
}

void Material::set_uniform(const UniformValue& u) { uniforms_[u.name] = u; }

void Material::unset_uniform(const String& name) { uniforms_.erase(name); }

} // namespace anyone