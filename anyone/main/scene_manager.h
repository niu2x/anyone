#pragma once

namespace anyone {

class SceneNode;

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    void render();
    SceneNode* get_root_node() const { return root_; }

private:
    SceneNode* root_;
};

} // namespace anyone