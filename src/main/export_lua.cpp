/*
** Lua binding: anyone
** Generated automatically by tolua++-1.0.93 on Mon Mar 17 12:42:53 2025.
*/

#include "stdlib.h"
#include "string.h"
#include "tolua++.h"

#define tolua_pushcppstring(x, y) tolua_pushstring(x, y.c_str())
#define tolua_iscppstring         tolua_isstring
#define anyone_pushcppstring(lua_state, sz)                                    \
    lua_pushlstring(lua_state, sz.c_str(), sz.size())

/* Exported function */
TOLUA_API int tolua_anyone_open(lua_State* tolua_S);

#include "core.h"

/* function to register type */
static void tolua_reg_types(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "anyone::Core");
}

/* Open function */
TOLUA_API int tolua_anyone_open(lua_State* tolua_S)
{
    tolua_open(tolua_S);
    tolua_reg_types(tolua_S);
    tolua_module(tolua_S, NULL, 0);
    tolua_beginmodule(tolua_S, NULL);
    tolua_module(tolua_S, "anyone", 0);
    tolua_beginmodule(tolua_S, "anyone");
    tolua_cclass(tolua_S, "Core", "anyone::Core", "", NULL);
    tolua_beginmodule(tolua_S, "Core");
    tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
    return 1;
}

#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
TOLUA_API int luaopen_anyone(lua_State* tolua_S)
{
    return tolua_anyone_open(tolua_S);
};
#endif
