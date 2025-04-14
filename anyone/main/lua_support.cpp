#include "lua_support.h"
#include "core.h"

namespace anyone {

LuaFunction::LuaFunction(lua_State* L, int slot) : ref_(0), L_(L)
{
    if (lua_isfunction(L_, slot)) {
        lua_pushvalue(L_, slot);
        ref_ = luaL_ref(L_, LUA_REGISTRYINDEX);
    } else {
        LOG("LuaFunction: is not a lua function");
    }
}

LuaFunction::~LuaFunction()
{
    if (ref_)
        luaL_unref(L_, LUA_REGISTRYINDEX, ref_);
}

void LuaFunction::protected_call()
{
    if (!ref_)
        return;

    int old_top = lua_gettop(L_);
    lua_rawgeti(L_, LUA_REGISTRYINDEX, ref_);
    if (lua_isfunction(L_, -1)) {
        lua_pcall(L_, 0, 0, 0);
    }
    lua_settop(L_, old_top);
}

} // namespace anyone