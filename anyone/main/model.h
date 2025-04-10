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

private:
    VertexBuffer* vbo_;
    IndiceBuffer* veo_;
    PrimitiveType primitive_;
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
    Node* root_node_;
    static Program* program_;
    void destroy_node(Node* node);
    void draw_node(Node* node, const kmMat4* transform);
};

} // namespace anyone