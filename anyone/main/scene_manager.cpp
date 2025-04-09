#include "scene_manager.h"
#include "scene_node.h"

namespace anyone {

SceneManager::SceneManager() : root_(nullptr) { root_ = new SceneNode("/"); }

SceneManager::~SceneManager()
{
    if (root_)
        delete root_;
}
void SceneManager::render() { }

} // namespace anyone