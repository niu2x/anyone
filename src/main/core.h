#pragma once

#include "type.h"

namespace anyone {
class Core : public Singleton<Core> {
public:
    Core();
    ~Core();

    void update();
    void render();
};
} // namespace anyone