#include "model_manager.h"
#include "model.h"

namespace anyone {

ModelManager::ModelManager() { }
ModelManager::~ModelManager() { }

Model* ModelManager::load_model(const String& name, const String& path)
{
    auto model = new Model(name);
    if (!model->load_from_file(path)) {
        delete model;
        return nullptr;
    }
    NX_ASSERT(
        model_cache_.count(name) == 0, "already exist model: %s", name.c_str());
    model_cache_[name] = model;
    return model;
}

Model* ModelManager::get_model(const String& name) const
{
    auto it = model_cache_.find(name);
    if (it != model_cache_.end()) {
        return it->second;
    }
    return nullptr;
}

} // namespace anyone