#pragma once

#include "base/type.h"
#include "platform/api/support.h"

namespace anyone {

class RenderSystem {
public:
    RenderSystem(RenderAPI* api);
    ~RenderSystem();

private:
    RenderAPI* api_;
};

} // namespace anyone