#pragma once

namespace anyone {

class Camera;
class SceneNode;

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    void render(const Camera* camera);
    SceneNode* get_root_node() const { return root_; }

private:
    SceneNode* root_;
};

} // namespace anyone