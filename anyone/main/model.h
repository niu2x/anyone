#pragma once

#include "base/type.h"
#include "platform/api/support.h"

class aiMesh;

namespace anyone {

class Mesh {
public:
    Mesh();
    ~Mesh();
    bool load(aiMesh* ai_mesh);

private:
    VertexBuffer* vbo_;
    IndiceBuffer* veo_;
};

class Model {
public:
    Model(const String& name);
    ~Model();
    bool load_from_file(const String& name);

private:
    String name_;
    Vector<UniquePtr<Mesh>> meshes_;
};

} // namespace anyone