#pragma once

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

namespace anyone {

class LuaFunction {
public:
    LuaFunction();
    ~LuaFunction();

private:
    // managed by luaL_ref/luaL_unref
    int ref_;
    lua_State* L_;
};

} // namespace anyone