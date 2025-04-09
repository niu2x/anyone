#pragma once

#include "base/type.h"
#include "platform/api/support.h"

namespace anyone {

class Model;

class ModelManager {
public:
    ModelManager();
    ~ModelManager();
    Model* load_model(const String& name, const String& path);
    Model* get_model(const String& name) const;
    void unload_model(const String& name);

private:
    Map<String, Model*> model_cache_;
};

} // namespace anyone