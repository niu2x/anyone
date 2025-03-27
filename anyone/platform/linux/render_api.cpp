#include "support.h"
#include "glad/include/glad/glad.h"

namespace anyone {

OpenGL_API::OpenGL_API() { }
OpenGL_API::~OpenGL_API() { }

void OpenGL_API::clear() { glClear(GL_COLOR_BUFFER_BIT); }

void OpenGL_API::set_clear_color(const Color& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

} // namespace anyone