#include "scene_node.h"

namespace anyone {

SceneNode::SceneNode(const String& name)
: name_(name)
, children_ {}
, attachments_ {}
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

    attachments_.clear();
    children_.clear();
}

void SceneNode::attach_object(Attachment* a) { attachments_.push_back(a); }
void SceneNode::detach_object(Attachment* a)
{
    auto it = std::remove(attachments_.begin(), attachments_.end(), a);
    attachments_.erase(it, attachments_.end());
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

} // namespace anyone