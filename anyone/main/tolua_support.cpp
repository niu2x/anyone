#include "tolua_support.h"
#include <math.h>

bool __tolua_is_lua_function(lua_State* L,
                             int lo,
                             const char* type,
                             int def,
                             tolua_Error* err)
{
    if (lua_gettop(L) >= abs(lo) && lua_isfunction(L, lo))
    {
        return true;
    }
    err->index = lo;
    err->array = 0;
    err->type = "[not function]";
    return false;
}

LUA_FUNCTION __tolua_create_lua_function(lua_State* L, int lo, int def)
{
    if (!lua_isfunction(L, lo)) return 0;
    return new anyone::LuaFunction(L, lo);
}
