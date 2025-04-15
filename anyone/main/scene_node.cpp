#include "scene_node.h"
#include "core.h"
#include "attachment.h"

namespace anyone {

SceneNode::SceneNode(const String& name)
: name_(name)
, children_ {}
, renderables_ {}
, transform_dirty_(true)
{
    kmVec3Zero(&position_);
    scale_.x = scale_.y = scale_.z = 1;
    kmQuaternionIdentity(&quaternion_);
}

SceneNode::~SceneNode()
{
    for (auto child : children_) {
        delete child;
    }

    renderables_.clear();
    children_.clear();
}

void SceneNode::attach_object(Renderable* a) { renderables_.push_back(a); }
void SceneNode::detach_object(Renderable* a)
{
    auto it = std::remove(renderables_.begin(), renderables_.end(), a);
    renderables_.erase(it, renderables_.end());
}

SceneNode* SceneNode::create_child_node(const String& name)
{
    auto child = new SceneNode(name);
    children_.push_back(child);
    return child;
}

SceneNode* SceneNode::get_child(const String& name)
{
    auto it = std::find_if(
        children_.begin(), children_.end(), [&name](auto child) {
            return child->name_ == name;
        });
    if (it != children_.end())
        return *it;
    return nullptr;
}

SceneNode* SceneNode::find_node(const String& name)
{
    if (name_ == name)
        return this;

    for (auto child : children_) {
        auto node = child->find_node(name);
        if (node)
            return node;
    }

    return nullptr;
}

void SceneNode::remove_child(const String& name)
{
    auto it = std::remove_if(
        children_.begin(), children_.end(), [&name](auto child) {
            return child->name_ == name;
        });
    children_.erase(it, children_.end());
}

void SceneNode::remove_child(SceneNode* n)
{
    auto it = std::remove(children_.begin(), children_.end(), n);
    children_.erase(it, children_.end());
}

void SceneNode::apply_transform(const kmMat4* parent_transform)
{
    kmMat4Scaling(&transform_, scale_.x, scale_.y, scale_.z);

    kmMat4 tmp_1;
    kmMat4Translation(&tmp_1, position_.x, position_.y, position_.z);

    kmMat4 tmp_2;
    kmMat4RotationQuaternion(&tmp_2, &quaternion_);

    kmMat4Multiply(&transform_, &transform_, &tmp_2);
    kmMat4Multiply(&transform_, &transform_, &tmp_1);

    if (parent_transform) {
        kmMat4Multiply(&transform_, &transform_, parent_transform);
    }
}

void SceneNode::apply_transform_recursive(const kmMat4* parent_transform,
                                          bool force)
{

    bool force_apply_children = false;

    if (transform_dirty_ || force) {
        transform_dirty_ = false;
        apply_transform(parent_transform);
        force_apply_children = true;
    }

    for (auto child : children_) {
        child->apply_transform_recursive(&transform_, force_apply_children);
    }
}

void SceneNode::render(const Camera* camera, CubeMap* sky_box)
{
    for (auto r : renderables_) {
        r->draw(camera, &transform_, sky_box);
    }
}

void SceneNode::set_position(float x, float y, float z) {
	position_.x = x;	
	position_.y = y;	
	position_.z = z;	
	transform_dirty_ = true;
}

void SceneNode::rotate_by_local_z_axis(float r)
{
    kmQuaternion tmp;
    kmVec3 axis { 0, 0, 1 };
    kmQuaternionRotationAxisAngle(&tmp, &axis, r);
    kmQuaternionMultiply(&quaternion_, &quaternion_, &tmp);
    transform_dirty_ = true;
}
void SceneNode::rotate_by_local_x_axis(float r)
{
    kmQuaternion tmp;
    kmVec3 axis { 1, 0, 0 };
    kmQuaternionRotationAxisAngle(&tmp, &axis, r);
    kmQuaternionMultiply(&quaternion_, &quaternion_, &tmp);
    transform_dirty_ = true;
}
void SceneNode::rotate_by_local_y_axis(float r)
{
    kmQuaternion tmp;
    kmVec3 axis { 0, 1, 0 };
    kmQuaternionRotationAxisAngle(&tmp, &axis, r);
    kmQuaternionMultiply(&quaternion_, &quaternion_, &tmp);
    transform_dirty_ = true;
}

} // namespace anyone