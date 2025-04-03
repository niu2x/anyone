#pragma once

#include "base/type.h"
#include "platform/api/support.h"

namespace anyone {

class Mesh;
class Model;
class Camera;

class RenderSystem {
public:
    RenderSystem(RenderAPI* api);
    ~RenderSystem();
    void draw_mesh(Mesh*, Camera* camera);
    void draw_model(Model*, Camera* camera);

private:
    RenderAPI* api_;
};

} // namespace anyone