#include "model.h"
#include "main/core.h"
#include "main/texture_loader.h"
#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags

namespace anyone {

Model::Model(const String& name)
: name_(name)
, meshes_ {}
, materials_ {}
, textures_ {}
, root_node_(nullptr)
{
}

Model::~Model()
{
    for (auto tex : textures_) {
        GET_RENDER_API()->destroy_texture_2d(tex);
    }
    textures_.clear();
    materials_.clear();
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

    // for (int i = 0; i < 16; i++) {
    //     LOG("out->mat %i %f", i, out->mat[i]);
    // }
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

        auto meta = scene->mMetaData;

        // int32_t up_axis = 0;
        // int32_t up_axis_sign = 0;

        if (meta) {
            for (unsigned int i = 0; i < meta->mNumProperties; i++) {
                auto key = String(meta->mKeys[i].data);
                auto value = meta->mValues[i];

                // if(key == "UpAxis") {
                //     NX_ASSERT(value.mType == AI_INT32, "");
                //     up_axis = *(int32_t*)(value.mData);
                // }
                // else if(key == "UpAxisSign") {
                //     NX_ASSERT(value.mType == AI_INT32, "");
                //     up_axis_sign = *(int32_t*)(value.mData);
                // }

                switch (value.mType) {
                    case AI_BOOL: {
                        LOG("meta %s(%s): ", key.c_str(), "AI_BOOL");
                        break;
                    }
                    case AI_INT32: {
                        LOG("meta %s(%s): %d",
                            key.c_str(),
                            "AI_INT32",
                            *(int32_t*)(value.mData));
                        break;
                    }

                    case AI_UINT64: {
                        LOG("meta %s(%s): ", key.c_str(), "AI_UINT64");
                        break;
                    }
                    case AI_FLOAT: {
                        LOG("meta %s(%s): %f",
                            key.c_str(),
                            "AI_FLOAT",
                            *(float*)(value.mData));
                        break;
                    }
                    case AI_DOUBLE: {
                        LOG("meta %s(%s): ", key.c_str(), "AI_DOUBLE");
                        break;
                    }
                    case AI_AISTRING: {
                        LOG("meta %s(%s): ", key.c_str(), "AI_AISTRING");
                        break;
                    }
                    case AI_AIVECTOR3D: {
                        LOG("meta %s(%s): ", key.c_str(), "AI_AIVECTOR3D");
                        break;
                    }
                    case AI_AIMETADATA: {
                        LOG("meta %s(%s): ", key.c_str(), "AI_AIMETADATA");
                        break;
                    }
                    case AI_INT64: {
                        LOG("meta %s(%s): ", key.c_str(), "AI_INT64");
                        break;
                    }
                    case AI_UINT32: {
                        LOG("meta %s(%s): ", key.c_str(), "AI_UINT32");
                        break;
                    }
                }
            }
        }

        for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
            aiMaterial* material = scene->mMaterials[i];

            auto my_material = std::make_unique<Material>();

            // 1. 获取基础颜色（Albedo）
            aiColor4D base_color;
            if (AI_SUCCESS == material->Get(AI_MATKEY_BASE_COLOR, base_color)) {
                // 使用 base_color.r/g/b/a
                LOG("material(%d) base_color %f %f %f %f",
                    i,
                    base_color.r,
                    base_color.g,
                    base_color.b,
                    base_color.a);

                my_material->set_albedo(RGBA_F(
                    base_color.r, base_color.g, base_color.b, base_color.a));
            }

            // 2. 获取金属度和粗糙度
            float metallic = 0, roughness = 0;
            if (AI_SUCCESS
                == material->Get(AI_MATKEY_METALLIC_FACTOR, metallic)) {
                LOG("material(%d) metallic %f", i, metallic);
                my_material->set_metallic(metallic);
            }
            if (AI_SUCCESS
                == material->Get(AI_MATKEY_ROUGHNESS_FACTOR, roughness)) {
                LOG("material(%d) roughness %f", i, roughness);
                my_material->set_roughness(roughness);
            }

            // 3. 获取贴图路径
            aiString texturePath;
            if (material->GetTexture(aiTextureType_BASE_COLOR, 0, &texturePath)
                == AI_SUCCESS) {
                auto path = texturePath.C_Str(); // 基础颜色贴图路径
                if (path[0] == '*') {
                    unsigned int tex_index = std::stoi(path + 1);
                    aiTexture* tex = scene->mTextures[tex_index];
                    LOG("tex(%d) format_hint: %s",
                        tex_index,
                        tex->achFormatHint);
                    if (tex->mHeight == 0) {
                        if (strcasecmp(tex->achFormatHint, "jpg") == 0) {

                            auto texture = TextureLoader::load_2d_jpg(
                                (const uint8_t*)tex->pcData, tex->mWidth);
                            if (texture) {
                                my_material->set_albedo_texture(texture);
                                textures_.push_back(texture);
                            }

                        } else {
                            NX_PANIC("don't support compressed format: %s",
                                     tex->achFormatHint);
                        }
                    } else {
                        NX_PANIC("don't support uncompressed material texture");
                    }
                } else {
                    NX_PANIC("only support embed texture");
                }
            }

            materials_.push_back(std::move(my_material));

            // if (material->GetTexture(
            //         aiTextureType_NORMAL_CAMERA, 0, &texturePath)
            //     == AI_SUCCESS) {
            //     std::string path = texturePath.C_Str(); // 法线贴图路径
            // }
        }

        root_node_ = load_node(root_node);
    }

    // We're done. Everything will be cleaned up by the importer destructor

    return true;
}

Mesh::Mesh()
: vbo_(nullptr)
, veo_(nullptr)
, primitive_(PrimitiveType::POINT)
, material_(-1)
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

    int num_colors = 0;
    for (; num_colors < AI_MAX_NUMBER_OF_COLOR_SETS; num_colors++) {
        if (!ai_mesh->mColors[num_colors]) {
            break;
        }
    }

    int num_uv = 0;
    for (; num_uv < AI_MAX_NUMBER_OF_TEXTURECOORDS; num_uv++) {
        if (!ai_mesh->mTextureCoords[num_uv]) {
            break;
        }
    }

    LOG("mesh : num_vertices: %d, num_faces %d, primitive_types: %x, normals: "
        "%p, num_colors: %d, num_uv: %d",
        num_vertices,
        num_faces,
        primitive_types,
        ai_mesh->mNormals,
        num_colors, num_uv);

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
        float u0, v0;
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

        if(num_uv > 0) {
            vertices[i].u0 = ai_mesh->mTextureCoords[0][i].x;
            vertices[i].v0 = ai_mesh->mTextureCoords[0][i].y;
        }

        //         LOG("mesh AABB: %f %f %f"
        //     , vertices[i].x
        //     , vertices[i].y
        //     , vertices[i].z
        // );
    }
    vbo_->apply();
    vbo_->free_cpu_buffer();

    vbo_->set_vertex_layout({ VertexAttr::POSITION_XYZ, VertexAttr::NORMAL , VertexAttr::UV});

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

    material_ = ai_mesh->mMaterialIndex;

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

            int material_index = mesh->get_material_index();
            if (material_index >= 0 && material_index < materials_.size()) {
                auto material = materials_[material_index].get();
                auto albedo_texture = material->get_albedo_texture();
                if (albedo_texture) {
                    program_->set_param_int("use_albedo_tex", 1);
                    program_->set_param_texture("albedo_tex", 0);
                    albedo_texture->bind(0);
                } else {

                    program_->set_param_color("albedo_color",
                                              material->get_albedo());
                    program_->set_param_int("use_albedo_tex", 0);
                }

                program_->set_param_float("metallic", material->get_metallic());
                program_->set_param_float("roughness",
                                          material->get_roughness());
            } else {
                program_->set_param_color("albedo_color", Color::WHITE);
                program_->set_param_int("use_albedo_tex", 0);
            }

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

float get_time()
{
    static auto init = nx::time_now();
    return nx::time_diff(init, nx::time_now());
}

void Model::draw(const Camera* camera,
                 const kmMat4* transform,
                 CubeMap* sky_box)
{
    GET_RENDER_API()->set_depth_test(true);
    program_->use();
    GET_RENDER_API()->set_blend_type(BlendType::NORMAL);

    auto view = camera->get_view_matrix();
    auto proj = camera->get_proj_matrix();

    float ambient[] = { 0.5, 0.5, 0.5 };
    float light_direction[] = {1/3.0, 1/3.0, 1/3.0};
    program_->set_param_vec3("ambient_color", ambient);
    program_->set_param_vec3("light_position", 3, 0, 3);
    program_->set_param_vec3("light_color", 10, 10, 10);
    auto eye_pos = camera->get_eye();
    program_->set_param_vec3("eye_pos", eye_pos->x, eye_pos->y, eye_pos->z);
    program_->set_param_mat4("view", view->mat);
    program_->set_param_mat4("proj", proj->mat);

    float time[] = { get_time(), 0, 0, 0 };
    program_->set_param_vec4("time", time);

    program_->set_param_int("use_environment", sky_box != nullptr);
    if (sky_box) {
        sky_box->bind(1);
        program_->set_param_texture("environment_tex", 1);
    }

    // kmMat4 adjust_axis;
    // kmMat4RotationX(&adjust_axis, -PI / 2);
    // kmMat4Multiply(&adjust_axis, &adjust_axis, transform);

    if (root_node_) {
        // draw_node(root_node_, &adjust_axis);
        draw_node(root_node_, transform);
    }
}

Program* Model::program_ = nullptr;

void Model::setup() { program_ = GET_RENDER_API()->create_model_program(); }

void Model::cleanup() { GET_RENDER_API()->destroy_program(program_); }

Material::Material()
: albedo_(Color::GRAY)
, metallic_(0)
, roughness_(0)
, albedo_tex_(nullptr)
{
}
Material::~Material() { }

} // namespace anyone
