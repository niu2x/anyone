#pragma once

#include "gl.h"
#include "ttf.h"
#include "material.h"
#include <stdarg.h>

namespace anyone {

class DebugText : public FramebufferSizeListener {
public:
    DebugText(Font* font);
    ~DebugText();
    void render();
    void vprintf(int x, int y, const char* msg, va_list args);
    void clear();

    void on_framebuffer_size_changed() override;

private:
    Vector<char> screens_;
    Font* font_;
    bool dirty_;
    
    GL_VertexBuffer* vbo_;
    int vertex_count_;

    // GL_Texture2D* texture_;
    // GL_Program* program_;
    //
    Material* material_;
    DrawOperation draw_operation_;

    int get_font_width() const;
    int get_font_height() const;
    int get_cell_count() const;
};

} // namespace anyone