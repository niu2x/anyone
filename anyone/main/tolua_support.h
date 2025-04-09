#include "tolua++.h"

using LUA_FUNCTION = int;

int __tolua_is_function(lua_State* L, int lo, const char* type, int def, tolua_Error* err);
int __tolua_ref_function(lua_State* L, int lo, int def);
void __tolua_unref_function(lua_State* L, int ref);
