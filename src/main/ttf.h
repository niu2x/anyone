#pragma once

#include "gl.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

namespace anyone {

class FreeTypeLibrary {
public:
    FreeTypeLibrary();
    ~FreeTypeLibrary();

private:
    FT_Library ft_library_;
};

} // namespace anyone