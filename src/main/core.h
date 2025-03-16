#pragma once

#include "type.h"
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

namespace anyone {
class Core : public Singleton<Core> {
public:
    Core();
    ~Core();

    void update();
    void render();

private:
    lua_State* lua_;
};
} // namespace anyone