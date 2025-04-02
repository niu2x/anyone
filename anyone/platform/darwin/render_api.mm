#include "support.h"
#import "render_impl.h"

namespace anyone {

Metal_API::Metal_API(SDL_Renderer *sdl_renderer):pimp_(nullptr) { 
    CAMetalLayer *layer = (__bridge CAMetalLayer *)SDL_RenderGetMetalLayer(sdl_renderer);
    pimp_ = (__bridge_retained void *)([[Metal_IMPL alloc]init_with_swap_chain: layer]);
}

Metal_API::~Metal_API() { 
    Metal_IMPL* _ = (__bridge_transfer Metal_IMPL*)pimp_;
    pimp_ = nullptr;
}

void Metal_API::clear() { 
    Metal_IMPL* impl = (__bridge Metal_IMPL*)pimp_;
    [impl clear];
}

void Metal_API::set_clear_color(const Color& color)
{
    Metal_IMPL* impl = (__bridge Metal_IMPL*)pimp_;
    // [impl set_clear_color: color];
}

// VertexBuffer* Metal_API::create_vertex_buffer() { return nullptr; }

// void Metal_API::destroy_vertex_buffer(VertexBuffer* vbo) { }

// IndiceBuffer* Metal_API::create_indice_buffer() { return nullptr; }

// void Metal_API::destroy_indice_buffer(IndiceBuffer* vbo) { }

// Texture2D* Metal_API::create_texture_2d() { return nullptr; }

// void Metal_API::destroy_texture_2d(Texture2D* vbo) { }

// void Metal_API::draw(const DrawOperation& operation) { }

// Program* Metal_API::create_rml_ui_program() { return nullptr; }

// void Metal_API::destroy_program(Program* vbo) { }

// void Metal_API::set_blend_type(BlendType b) { }

} // namespace anyone