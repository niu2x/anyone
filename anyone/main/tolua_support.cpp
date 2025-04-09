#include "tolua_support.h"
#include <math.h>

int __tolua_is_function(lua_State* L, int lo, const char* type, int def, tolua_Error* err)
{
    if (lua_gettop(L) >= abs(lo) && lua_isfunction(L, lo))
    {
        return 1;
    }
    err->index = lo;
    err->array = 0;
    err->type = "[not function]";
    return 0;
}


int __tolua_ref_function(lua_State* L, int lo, int def)
{
    if (!lua_isfunction(L, lo)) return 0;
	lua_pushvalue(L, lo);    
    return luaL_ref(L, LUA_REGISTRYINDEX);
}

void __tolua_unref_function(lua_State* L, int ref) {
	luaL_unref(L, LUA_REGISTRYINDEX, ref);
}
