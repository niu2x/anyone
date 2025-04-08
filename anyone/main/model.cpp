#include "model.h"
#include "main/core.h"
#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags

namespace anyone {

Model::Model(const String& name) : name_(name), meshes_ {}, root_node_(nullptr)
{
}

Model::~Model()
{
    meshes_.clear();
    destroy_node(root_node_);
}

void Model::destroy_node(Node* node)
{
    if (!node)
        return;
    for (auto child : node->children) {
        destroy_node(node);
    }
    delete node;
}

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

void copy_transform(aiMatrix4x4* in, kmMat4* out)
{
    out->mat[0] = in->a1;
    out->mat[1] = in->a2;
    out->mat[2] = in->a3;
    out->mat[3] = in->a4;

    out->mat[4] = in->b1;
    out->mat[5] = in->b2;
    out->mat[6] = in->b3;
    out->mat[7] = in->b4;

    out->mat[8] = in->c1;
    out->mat[9] = in->c2;
    out->mat[10] = in->c3;
    out->mat[11] = in->c4;

    out->mat[12] = in->d1;
    out->mat[13] = in->d2;
    out->mat[14] = in->d3;
    out->mat[15] = in->d4;
}

Model::Node* load_node(aiNode* ai_node)
{
    if (!ai_node)
        return nullptr;

    auto node = new Model::Node;
    node->parent = nullptr;

    copy_transform(&ai_node->mTransformation, &node->transform);

    for (unsigned int i = 0; i < ai_node->mNumMeshes; i++) {
        node->meshes.push_back(ai_node->mMeshes[i]);
    }

    for (unsigned int i = 0; i < ai_node->mNumChildren; i++) {
        auto child = load_node(ai_node->mChildren[i]);
        child->parent = node;
        node->children.push_back(child);
    }

    return node;
}

bool Model::load_from_file(const String& path)
{
    auto maybe_data = GET_CORE()->read_file_data(path);
    if (!maybe_data)
        return false;

    ByteBuffer& data = *maybe_data;

    static auto flags = aiProcess_CalcTangentSpace | aiProcess_Triangulate
                        | aiProcess_JoinIdenticalVertices
                        | aiProcess_OptimizeMeshes
                        | aiProcess_OptimizeGraph
                        | aiProcess_GenNormals
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

        root_node_ = load_node(root_node);
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
    LOG("mesh : num_vertices: %d, num_faces %d, primitive_types: %x, normals: %p",
        num_vertices,
        num_faces,
        primitive_types, ai_mesh->mNormals);

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
        float nx,ny, nz;
    };

    vbo_->alloc_cpu_buffer(sizeof(GPU_Vertex) * num_vertices);
    auto vertices = (GPU_Vertex*)vbo_->get_cpu_buffer();
    for (unsigned int i = 0; i < num_vertices; i++) {
        vertices[i].x = ai_mesh->mVertices[i].x;
        vertices[i].y = ai_mesh->mVertices[i].y;
        vertices[i].z = ai_mesh->mVertices[i].z;

        if (ai_mesh->mNormals) {
            vertices[i].nx = ai_mesh->mNormals[i].x;
            vertices[i].ny = ai_mesh->mNormals[i].y;
            vertices[i].nz = ai_mesh->mNormals[i].z;
        }

        //         LOG("mesh AABB: %f %f %f"
        //     , vertices[i].x
        //     , vertices[i].y
        //     , vertices[i].z
        // );
    }
    vbo_->apply();
    vbo_->free_cpu_buffer();

    vbo_->set_vertex_layout({ VertexAttr::POSITION_XYZ, VertexAttr::NORMAL });

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

void Model::draw_node(Node* node, const kmMat4* parent_transform)
{
    kmMat4 my_transform;

    kmMat4Multiply(&my_transform, &node->transform, parent_transform);

    for (auto child : node->children) {
        draw_node(child, &my_transform);
    }

    if (node->meshes.size() > 0) {
        program_->set_param_mat4("model", my_transform.mat);
        for (auto mesh_id : node->meshes) {
            auto mesh = meshes_[mesh_id].get();
            auto vbo = mesh->get_vbo();
            auto veo = mesh->get_veo();

            GET_RENDER_API()->draw(DrawOperation {
                .primitive = mesh->get_primitive_type(),
                .polygon_mode = PolygonMode::FILL,
                .vertex_buffer = vbo,
                .indice_buffer = veo,
                .count = veo->get_indice_count(),
            });
        }
    }
}

void Model::draw(const Camera* camera, const kmMat4* transform)
{
    GET_RENDER_API()->set_depth_test(true);
    program_->use();
    GET_RENDER_API()->set_blend_type(BlendType::NORMAL);

    auto view = camera->get_view_matrix();
    auto proj = camera->get_proj_matrix();

    float ambient[] = { 0.3, 0.3, 0.6 };
    float light_direction[] = {1/3.0, 1/3.0, 1/3.0};
    program_->set_param_vec3("ambient", ambient);
    program_->set_param_vec3("light_direction", light_direction);
    program_->set_param_mat4("view", view.mat);
    program_->set_param_mat4("proj", proj.mat);

    if (root_node_) {
        draw_node(root_node_, transform);
    }
    // program_->set_param_mat4("model", model.mat);
    // for (auto& mesh : meshes_) {
    //     auto vbo = mesh->get_vbo();
    //     auto veo = mesh->get_veo();

    //     GET_RENDER_API()->draw(DrawOperation {
    //         .primitive = PrimitiveType::TRIANGLE,
    //         .polygon_mode = PolygonMode::LINE,
    //         .vertex_buffer = vbo,
    //         .indice_buffer = veo,
    //         .count = veo->get_indice_count(),
    //     });
    // }
}

Program* Model::program_ = nullptr;

void Model::setup() { program_ = GET_RENDER_API()->create_model_program(); }

void Model::cleanup() { GET_RENDER_API()->destroy_program(program_); }

} // namespace anyone
