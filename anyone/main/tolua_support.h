#include "tolua++.h"
#include "lua_support.h"

using LUA_FUNCTION = anyone::LuaFunction*;
using LUA_TABLE = anyone::LuaTable*;

bool __tolua_is_lua_function(lua_State* L,
                             int lo,
                             const char* type,
                             int def,
                             tolua_Error* err);
LUA_FUNCTION __tolua_create_lua_function(lua_State* L, int lo, int def);

bool __tolua_is_lua_table(lua_State* L,
                          int lo,
                          const char* type,
                          int def,
                          tolua_Error* err);
LUA_TABLE __tolua_create_lua_table(lua_State* L, int lo, int def);
