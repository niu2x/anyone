#include "core.h"
#include "platform.h"

namespace anyone {

Core::Core() { }

Core::~Core() { }

void Core::update() { }

void Core::render()
{
    // glViewport(0, 0, 1, 1);
    glClearColor(1.f, 0.f, 1.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);
}

} // namespace anyone