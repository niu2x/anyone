#include "scene_manager.h"
#include "scene_node.h"

namespace anyone {

SceneManager::SceneManager() : root_(nullptr)
{
    root_ = new SceneNode("/");
    root_->apply_transform(nullptr);
}

SceneManager::~SceneManager()
{
    if (root_)
        delete root_;
}
void SceneManager::render(const Camera* camera) { root_->render(camera); }

} // namespace anyone