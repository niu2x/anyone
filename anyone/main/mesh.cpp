#include "mesh.h"
#include "main/core.h"

namespace anyone {

Mesh::Mesh(const String& name) : name_(name) { }
Mesh::~Mesh() { }

bool Mesh::load_from_file(const String& name)
{
    LOG("Mesh::load_from_file %s", name.c_str());
    auto data = GET_CORE()->read_file_data(name);
    LOG("Mesh::load_from_file data: %d", !!data);
    return false;
}

} // namespace anyone
