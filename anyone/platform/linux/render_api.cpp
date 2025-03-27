#include "support.h"
#include "glad/include/glad/glad.h"

namespace anyone {

OpenGL_API::OpenGL_API() { }
OpenGL_API::~OpenGL_API() { }

void OpenGL_API::clear()
{
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);
}

} // namespace anyone