#pragma once

#include "platform/api/support.h"

namespace anyone {

struct TextureLoader {
    static Texture2D* load_2d_jpg(const uint8_t* data, size_t len);
    static CubeMap* load_cube_map_png(const String& uri);
};

} // namespace anyone