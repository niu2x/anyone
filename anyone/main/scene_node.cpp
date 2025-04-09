#include "scene_node.h"
#include "attachment.h"

namespace anyone {

SceneNode::SceneNode(const String& name)
: name_(name)
, children_ {}
, renderables_ {}
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

void SceneNode::render(const Camera* camera)
{
    for (auto r : renderables_) {
        r->draw(camera, &transform_);
    }
}

} // namespace anyone