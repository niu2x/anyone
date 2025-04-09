#pragma once

#include "base/type.h"

namespace anyone {

class Attachment;

class SceneNode {
public:
    SceneNode(const String& name);
    ~SceneNode();

    void attach_object(Attachment* a);
    void detach_object(Attachment* a);

    SceneNode* create_child_node(const String& name);
    SceneNode* get_child(const String& name);
    SceneNode* find_node(const String& name);
    void remove_child(const String& name);
    void remove_child(SceneNode*);

private:
    String name_;
    Vector<SceneNode*> children_;
    Vector<Attachment*> attachments_;
};

} // namespace anyone