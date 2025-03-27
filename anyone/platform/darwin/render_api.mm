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

} // namespace anyone