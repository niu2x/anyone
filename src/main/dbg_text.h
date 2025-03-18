#pragma once

#include "gl.h"
#include "ttf.h"

namespace anyone {

class DebugText : public FramebufferSizeListener {
public:
    DebugText(Font* font);
    ~DebugText();
    void render();
    void printf(int x, int y, const char* msg);
    void clear();

    void on_framebuffer_size_changed() override;

private:
    Vector<char> screens_;
    Font* font_;
    bool dirty_;
    GL_VertexBuffer* vbo_;
    int vertex_count_;
    GL_Texture2D* texture_;
    GL_Program* program_;
};

} // namespace anyone