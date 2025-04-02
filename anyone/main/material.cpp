#include "material.h"
#include "main/core.h"

namespace anyone {

Material::~Material() { }

Material::Material() : blend_type_(BlendType::NONE), program_(nullptr) { }

void Material::set_program(Program* p) { program_ = p; }

void Material::set_blend_type(BlendType b) { blend_type_ = b; }

void Material::use()
{
    auto api = GET_RENDER_API();
    api->set_blend_type(blend_type_);
    program_->use();
}

// void Material::use(RenderAPI* api) { api->set_blend_type(blend_type_); }

// Material::Material() : program_(nullptr), blend_(BlendType::NONE) { }

// Material::~Material() { SAFE_RELEASE(program_); }

// void Material::set_program(GL_Program* p)
// {
//     SAFE_RETAIN(p);
//     SAFE_RELEASE(program_);
//     program_ = p;
// }

// void Material::use()
// {
//     program_->use();
//     for (auto u : uniforms_) {
//         if (u.second.type == UniformType::TEXTURE) {
//             auto& tex = std::get<UniformTexture>(u.second.value);
//             if (tex.texture) {
//                 tex.texture->bind(tex.tex_unit);
//             }
//         }
//         program_->set_uniform(u.second);
//     }

//     GET_RENDER_API()->set_blend_type(blend_);
// }

// void Material::compile()
// {
//     int tex_unit = 0;
//     for (auto u : uniforms_) {
//         if (u.second.type == UniformType::TEXTURE) {
//             auto& tex = std::get<UniformTexture>(u.second.value);
//             tex.tex_unit = tex_unit++;
//             if (tex.key != "") {
//                 tex.texture = alive_textures.get(tex.key);
//             }
//         }
//     }
// }

// void Material::set_uniform(const UniformValue& u) { uniforms_[u.name] = u; }

// void Material::unset_uniform(const String& name) { uniforms_.erase(name); }

} // namespace anyone