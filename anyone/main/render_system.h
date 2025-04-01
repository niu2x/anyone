#pragma once

#include "base/type.h"
#include "platform/api/support.h"

namespace anyone {

class Mesh;
class Camera;

class RenderSystem {
public:
    RenderSystem(RenderAPI* api);
    ~RenderSystem();
    void draw_mesh(const Mesh*, const Camera* camera);

private:
    RenderAPI* api_;
};

} // namespace anyone