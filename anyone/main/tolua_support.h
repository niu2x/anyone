#include "tolua++.h"
#include "lua_support.h"

using LUA_FUNCTION = anyone::LuaFunction*;

bool __tolua_is_lua_function(lua_State* L,
                             int lo,
                             const char* type,
                             int def,
                             tolua_Error* err);
LUA_FUNCTION __tolua_create_lua_function(lua_State* L, int lo, int def);
