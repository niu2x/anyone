_is_functions = _is_functions or { }
_to_functions = _to_functions or { }
_push_functions = _push_functions or { }
local toWrite = { }
local currentString = ''
local out
local WRITE , OUTPUT = write , output
function output ( s )
    out = _OUTPUT
    output = OUTPUT
    output ( s )
end
function write ( a )
    if out == _OUTPUT then
        currentString = currentString .. a
        if string.sub ( currentString , - 1 ) == '\n' then
            toWrite[# toWrite + 1]= currentString
            currentString = ''
        end
    else
        WRITE ( a )
    end
end
function post_output_hook ( package )
    local result = table.concat ( toWrite )
    local function replace ( pattern , replacement )
        local k = 0
        local nxt , currentString = 1 , ''
        repeat local s , e = string.find ( result , pattern , nxt , true )
        if e then
            currentString = currentString .. string.sub ( result , nxt , s - 1 ) .. replacement
            nxt = e + 1
            k = k + 1
        end until not e
        result = currentString .. string.sub ( result , nxt )
        -- if k == 0 then
            -- print ( 'Pattern not replaced' , pattern )
        -- end
    end
    replace ( [[#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"]] , [[

#include "stdlib.h"
#include "string.h"
#include "tolua++.h"

#define tolua_iscppstring                       tolua_isstring
#define anyone_pushcppstring(lua_state, sz) lua_pushlstring(lua_state, sz.c_str(), sz.size())
]] )

    -- replace ( [[*((LUA_FUNCTION*)]] , [[(]] )
    -- replace ( [[tolua_usertype(tolua_S,"LUA_FUNCTION");]] , [[]] )
    -- replace ( [[*((map<string,string>*)]] , [[(]] )
    -- replace ( [[tolua_usertype(tolua_S,"map<string,string>");]] , [[]] )
    -- replace ( [[VECTOR_MAP_SS]] , [[vector<map<string,string>>]] )
    -- replace ( [[*((vector<map<string,string>>*)]] , [[(]] )
    -- replace ( [[tolua_usertype(tolua_S,"vector<map<string,string>>");]] , [[]] )
    -- replace ( [[*((vector<string>*)]] , [[(]] )
    -- replace ( [[tolua_usertype(tolua_S,"vector<string>");]] , [[]] )
    replace ( [[tolua_pushcppstring(tolua_S,(const char*)]] , [[anyone_pushcppstring(tolua_S,]] )
    replace ( '\t' , '    ' )
    WRITE ( result )
end
