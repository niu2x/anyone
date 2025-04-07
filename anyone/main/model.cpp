#include "model.h"
#include "main/core.h"
#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags

namespace anyone {

Model::Model(const String& name) : name_(name), meshes_ {} { }

Model::~Model() { meshes_.clear(); }

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

bool Model::load_from_file(const String& path)
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

        for (unsigned int i = 0; i < mesh_num; i++) {
            auto ai_mesh = mesh_list[i];

            auto mesh = std::make_unique<Mesh>();
            mesh->load(ai_mesh);
            meshes_.push_back(std::move(mesh));
        }

        load_node(root_node);
    }

    // We're done. Everything will be cleaned up by the importer destructor

    return true;
}

Mesh::Mesh() : vbo_(nullptr), veo_(nullptr), primitive_(PrimitiveType::POINT)
{
    auto api = GET_RENDER_API();
    vbo_ = api->create_vertex_buffer();
    veo_ = api->create_indice_buffer();
}

Mesh::~Mesh()
{
    auto api = GET_RENDER_API();
    api->destroy_vertex_buffer(vbo_);
    api->destroy_indice_buffer(veo_);
}

bool Mesh::load(aiMesh* ai_mesh)
{
    auto num_vertices = ai_mesh->mNumVertices;
    auto num_faces = ai_mesh->mNumFaces;
    auto primitive_types = ai_mesh->mPrimitiveTypes;
    LOG("mesh : num_vertices: %d, num_faces %d, primitive_types: %x",
        num_vertices,
        num_faces,
        primitive_types);

    // LOG("mesh AABB: %f %f %f, %f %f %f"
    //     , ai_mesh->mAABB.mMin.x
    //     , ai_mesh->mAABB.mMin.y
    //     , ai_mesh->mAABB.mMin.z
    //     , ai_mesh->mAABB.mMax.x
    //     , ai_mesh->mAABB.mMax.y
    //     , ai_mesh->mAABB.mMax.z
    // );

    unsigned int expect_indice_num = 0;

    if (primitive_types == aiPrimitiveType_POINT) {
        primitive_ = PrimitiveType::POINT;
        expect_indice_num = 1;
    } else if (primitive_types == aiPrimitiveType_LINE) {
        primitive_ = PrimitiveType::LINE;
        expect_indice_num = 2;
    } else if (primitive_types | aiPrimitiveType_TRIANGLE) {
        primitive_ = PrimitiveType::TRIANGLE;
        expect_indice_num = 3;
    } else {
        LOG("Mesh::load fail, unsupport primitive_types: %x", primitive_types);
        return false;
    }

    struct GPU_Vertex {
        float x, y, z;
    };

    vbo_->alloc_cpu_buffer(sizeof(GPU_Vertex) * num_vertices);
    auto vertices = (GPU_Vertex*)vbo_->get_cpu_buffer();
    for (unsigned int i = 0; i < num_vertices; i++) {
        vertices[i].x = ai_mesh->mVertices[i].x;
        vertices[i].y = ai_mesh->mVertices[i].y;
        vertices[i].z = ai_mesh->mVertices[i].z;

        //         LOG("mesh AABB: %f %f %f"
        //     , vertices[i].x
        //     , vertices[i].y
        //     , vertices[i].z
        // );
    }
    vbo_->apply();
    vbo_->free_cpu_buffer();

    vbo_->set_vertex_layout({ VertexAttr::POSITION_XYZ });

    veo_->alloc_cpu_buffer(num_faces * expect_indice_num);
    auto indices = veo_->get_cpu_buffer();
    size_t indices_index = 0;

    for (unsigned int i = 0; i < num_faces; i++) {
        auto face = ai_mesh->mFaces[i];
        NX_ASSERT(face.mNumIndices == expect_indice_num,
                  "face.mNumIndices(%d) must be %d",
                  face.mNumIndices,
                  expect_indice_num);
        // LOG("face %u, mNumIndices %u", i, face.mNumIndices);
        for (unsigned int j = 0; j < expect_indice_num; j++) {
            indices[indices_index++] = face.mIndices[j];
        }
    }

    NX_ASSERT(indices_index == num_faces * expect_indice_num, "");

    veo_->apply();
    veo_->free_cpu_buffer();

    return true;
}

void Model::draw(const Camera* camera)
{
    GET_RENDER_API()->set_depth_test(true);
    program_->use();
    GET_RENDER_API()->set_blend_type(BlendType::NORMAL);

    auto view = camera->get_view_matrix();
    auto proj = camera->get_proj_matrix();

    program_->set_param_mat4("view", view.mat);
    program_->set_param_mat4("proj", proj.mat);

    for (auto& mesh : meshes_) {
        auto vbo = mesh->get_vbo();
        auto veo = mesh->get_veo();

        GET_RENDER_API()->draw(DrawOperation {
            .primitive = PrimitiveType::TRIANGLE,
            .polygon_mode = PolygonMode::LINE,
            .vertex_buffer = vbo,
            .indice_buffer = veo,
            .count = veo->get_indice_count(),
        });
    }
}

Program* Model::program_ = nullptr;

void Model::setup() { program_ = GET_RENDER_API()->create_model_program(); }

void Model::cleanup() { GET_RENDER_API()->destroy_program(program_); }

} // namespace anyone
