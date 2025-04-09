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
    void apply_transform(const kmMat4* parent_transform);

private:
    String name_;
    Vector<SceneNode*> children_;
    Vector<Renderable*> renderables_;
    kmVec3 position_;
    kmVec3 scale_;
    kmQuaternion quaternion_;
    kmMat4 transform_;
};

} // namespace anyone