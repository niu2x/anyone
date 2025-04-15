#include "render_system.h"
#include "model.h"

namespace anyone {

RenderSystem::RenderSystem(RenderAPI* api) : api_(api) { }
RenderSystem::~RenderSystem() { }

// void RenderSystem::draw_model(Model* m, Camera* camera, const kmMat4* mm)
// {
//     m->draw(camera, mm);
// }
// void RenderSystem::draw_mesh(Mesh*, Camera* camera) { }

} // namespace anyone