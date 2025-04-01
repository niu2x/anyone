#include "mesh_manager.h"
#include "mesh.h"

namespace anyone {

MeshManager::MeshManager() { }
MeshManager::~MeshManager() { }

Mesh* MeshManager::load_mesh(const String& name, const String& path)
{
    auto mesh = new Mesh(name);
    if (!mesh->load_from_file(path)) {
        delete mesh;
        return nullptr;
    }
    NX_ASSERT(
        mesh_cache_.count(name) == 0, "already exist mesh: %s", name.c_str());
    mesh_cache_[name] = mesh;
    return mesh;
}

} // namespace anyone