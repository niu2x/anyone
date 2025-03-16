#pragma once

#include "platform.h"

namespace anyone {

class PlatformSupportLinux : public PlatformSupport {
public:
    ~PlatformSupportLinux() { }

    void log(const char* fmt, ...) override;
    char get_path_separator() const override;
};

} // namespace anyone