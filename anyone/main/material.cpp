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

} // namespace anyone