#include "mesh.h"
#include "main/core.h"
#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags

namespace anyone {

Mesh::Mesh(const String& name) : name_(name) { }
Mesh::~Mesh() { }

std::string get_file_extension(const String& filename)
{
    // 找到最后一个点的位置
    size_t dot_position = filename.find_last_of('.');
    // 如果找不到点或点在字符串的开头（隐藏文件），返回空字符串
    if (dot_position == std::string::npos || dot_position == 0) {
        return "";
    }
    // 提取并返回扩展名
    return filename.substr(dot_position + 1);
}

bool Mesh::load_from_file(const String& path)
{
    auto maybe_data = GET_CORE()->read_file_data(path);
    if (!maybe_data)
        return false;

    ByteBuffer& data = *maybe_data;

    static auto flags = aiProcess_CalcTangentSpace | aiProcess_Triangulate
                        | aiProcess_JoinIdenticalVertices
                        | aiProcess_SortByPType;

    auto hint = get_file_extension(path);
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFileFromMemory(
        data.data(), data.size(), flags, hint.c_str());

    if (nullptr == scene) {
        LOG("assimp load fail: %s, data_size: %lu, msg: %s",
            path.c_str(),
            data.size(),
            importer.GetErrorString());
        return false;
    }

    {
        auto root_node = scene->mRootNode;

        auto mesh_list = scene->mMeshes;
        auto mesh_num = scene->mNumMeshes;

        auto skeleton_num = scene->mNumSkeletons;
        auto skeleton_list = scene->mSkeletons;

        auto animation_list = scene->mAnimations;
        auto animation_num = scene->mNumAnimations;

        LOG("mesh_num %d", mesh_num);
        LOG("skeleton_num %d", skeleton_num);
        LOG("animation_num %d", animation_num);

        for(unsigned int i = 0; i < mesh_num; i ++){
            auto mesh = mesh_list[i];
            auto num_vertices = mesh->mNumVertices;
            auto num_faces = mesh->mNumFaces;
            auto primitive_types = mesh->mPrimitiveTypes;
            LOG("mesh %d: num_vertices: %d, num_faces %d, primitive_types: %x", i, num_vertices, num_faces, primitive_types);
        }
    }

    // We're done. Everything will be cleaned up by the importer destructor

    return true;
}

} // namespace anyone
