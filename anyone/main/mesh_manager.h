#pragma once

#include "base/type.h"
#include "platform/api/support.h"

namespace anyone {

class Mesh;

class MeshManager {
public:
    MeshManager();
    ~MeshManager();
    Mesh* load_mesh(const String& name, const String& path);

private:
    Map<String, Mesh*> mesh_cache_;
};

} // namespace anyone