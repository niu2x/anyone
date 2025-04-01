#include "mesh.h"
#include "main/core.h"
#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags

namespace anyone {

Mesh::Mesh(const String& name) : name_(name) { }
Mesh::~Mesh() { }

bool Mesh::load_from_file(const String& name)
{
    auto maybe_data = GET_CORE()->read_file_data(name);
    if (!maybe_data)
        return false;

    ByteBuffer& data = *maybe_data;

    static auto flags = aiProcess_CalcTangentSpace | aiProcess_Triangulate
                        | aiProcess_JoinIdenticalVertices
                        | aiProcess_SortByPType;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFileFromMemory(
        data.data(), data.size(), flags);

    if (nullptr == scene) {
        return false;
    }

    // We're done. Everything will be cleaned up by the importer destructor

    return true;
}

} // namespace anyone
