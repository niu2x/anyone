#include "scene_manager.h"
#include "scene_node.h"

namespace anyone {

SceneManager::SceneManager()
: root_(nullptr)
, ambient_color_(Color::DARK_SLATE_GRAY)
, sky_color_(Color::DARK_SLATE_GRAY)
{
    root_ = new SceneNode("/");
    // root_->apply_transform(nullptr);
}

SceneManager::~SceneManager()
{
    if (root_)
        delete root_;
}
void SceneManager::render(const Camera* camera)
{
    root_->apply_transform_recursive(nullptr, false);
    root_->render(camera);
}

} // namespace anyone