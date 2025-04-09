#pragma once

#include "base/type.h"
#include "platform/api/support.h"
#include "kazmath/kazmath.h"

namespace anyone {

class Mesh;
class Model;
class Camera;

class RenderSystem {
public:
    RenderSystem(RenderAPI* api);
    ~RenderSystem();
    void draw_model(Model*, Camera* camera, const kmMat4*);

private:
    RenderAPI* api_;
};

} // namespace anyone