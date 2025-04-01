#include "render_system.h"

namespace anyone {

RenderSystem::RenderSystem(RenderAPI* api) : api_(api) { }
RenderSystem::~RenderSystem() { }

} // namespace anyone