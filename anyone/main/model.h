#pragma once

#include "base/type.h"
#include "platform/api/support.h"
#include "kazmath/kazmath.h"
#include "attachment.h"

class aiMesh;

namespace anyone {

class Camera;

class Mesh {
public:
    Mesh();
    ~Mesh();
    bool load(aiMesh* ai_mesh);

    VertexBuffer* get_vbo() const { return vbo_; }
    IndiceBuffer* get_veo() const { return veo_; }

    PrimitiveType get_primitive_type() const { return primitive_; }
    int get_material_index() const { return material_; }

private:
    VertexBuffer* vbo_;
    IndiceBuffer* veo_;
    PrimitiveType primitive_;
    int material_;
};

class Material {
public:
    Material();
    ~Material();

    void set_albedo(const Color& c) { albedo_ = c; }
    const Color& get_albedo() const { return albedo_; }

    void set_metallic(float c) { metallic_ = c; }
    float get_metallic() const { return metallic_; }

    void set_roughness(float c) { roughness_ = c; }
    float get_roughness() const { return roughness_; }

    void set_albedo_texture(Texture2D* tex) { albedo_tex_ = tex; }
    Texture2D* get_albedo_texture() const { return albedo_tex_; }

private:
    Color albedo_;
    float metallic_;
    float roughness_;
    Texture2D* albedo_tex_;
};

class Model : public Renderable {
public:
    Model(const String& name);
    ~Model();
    bool load_from_file(const String& name);
    void draw(const Camera* camera, const kmMat4* transform) override;

    static void setup();
    static void cleanup();

    struct Node {
        Vector<Node*> children;
        Vector<size_t> meshes;
        kmMat4 transform;
        Node* parent;
    };

    static Program* get_program() { return program_; }

private:
    String name_;
    Vector<UniquePtr<Mesh>> meshes_;
    Vector<UniquePtr<Material>> materials_;
    Vector<Texture2D*> textures_;
    Node* root_node_;
    static Program* program_;
    void destroy_node(Node* node);
    void draw_node(Node* node, const kmMat4* transform);
};

} // namespace anyone