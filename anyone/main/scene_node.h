#pragma once

#include "base/type.h"
#include "kazmath/kazmath.h"

namespace anyone {

class Renderable;
class Camera;

class SceneNode {
public:
    SceneNode(const String& name);
    ~SceneNode();

    void attach_object(Renderable* a);
    void detach_object(Renderable* a);

    SceneNode* create_child_node(const String& name);
    SceneNode* get_child(const String& name);
    SceneNode* find_node(const String& name);
    void remove_child(const String& name);
    void remove_child(SceneNode*);

    const kmMat4* get_transform() const { return &transform_; }
    void render(const Camera* camera);

    void apply_transform_recursive(const kmMat4* parent_transform, bool force);

    void set_position(float x, float y, float z);
    void rotate_by_local_z_axis(float r);
    void rotate_by_local_x_axis(float r);
    void rotate_by_local_y_axis(float r);

private:
    String name_;
    Vector<SceneNode*> children_;
    Vector<Renderable*> renderables_;
    kmVec3 position_;
    kmVec3 scale_;
    kmQuaternion quaternion_;
    kmMat4 transform_;
    bool transform_dirty_;
    void apply_transform(const kmMat4* parent_transform);
};

} // namespace anyone