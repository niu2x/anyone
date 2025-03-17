#include "ttf.h"

namespace anyone {

FreeTypeLibrary::FreeTypeLibrary()
{
    if (FT_Init_FreeType(&ft_library_)) {
        NX_PANIC("freetype init fail");
    }
}
FreeTypeLibrary::~FreeTypeLibrary() { FT_Done_FreeType(ft_library_); }

} // namespace anyone
