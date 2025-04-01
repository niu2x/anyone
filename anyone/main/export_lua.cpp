/*
** Lua binding: anyone
** Generated automatically by tolua++-1.0.93 on Tue Apr  1 18:13:11 2025.
*/

#include "stdlib.h"
#include "string.h"
#include "tolua++.h"

#define tolua_iscppstring                       tolua_isstring
#define anyone_pushcppstring(lua_state, sz) lua_pushlstring(lua_state, sz.c_str(), sz.size())


/* Exported function */
TOLUA_API int  tolua_anyone_open (lua_State* tolua_S);

#include "main/mesh_manager.h"
#include "main/mesh.h"
#include "main/core.h"
#include "platform/api/support.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"anyone::Mesh");
 tolua_usertype(tolua_S,"anyone::PlatformSupport");
 tolua_usertype(tolua_S,"anyone::MeshManager");
 tolua_usertype(tolua_S,"anyone::Core");
}

/* method: load_mesh of class  anyone::MeshManager */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_MeshManager_load_mesh00
static int tolua_anyone_anyone_MeshManager_load_mesh00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::MeshManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::MeshManager* self = (anyone::MeshManager*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* path = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'load_mesh'", NULL);
#endif
  {
   anyone::Mesh* tolua_ret = (anyone::Mesh*)  self->load_mesh(name,path);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"anyone::Mesh");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'load_mesh'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: set_full_screen of class  anyone::PlatformSupport */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_PlatformSupport_set_full_screen00
static int tolua_anyone_anyone_PlatformSupport_set_full_screen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::PlatformSupport",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::PlatformSupport* self = (anyone::PlatformSupport*)  tolua_tousertype(tolua_S,1,0);
  bool tolua_var_1 = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'set_full_screen'", NULL);
#endif
  {
   self->set_full_screen(tolua_var_1);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'set_full_screen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get_singleton_ptr of class  anyone::Core */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_Core_get_singleton_ptr00
static int tolua_anyone_anyone_Core_get_singleton_ptr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"anyone::Core",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   anyone::Core* tolua_ret = (anyone::Core*)  anyone::Core::get_singleton_ptr();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"anyone::Core");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get_singleton_ptr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get_platform_support of class  anyone::Core */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_Core_get_platform_support00
static int tolua_anyone_anyone_Core_get_platform_support00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::Core",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::Core* self = (anyone::Core*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get_platform_support'", NULL);
#endif
  {
   anyone::PlatformSupport* tolua_ret = (anyone::PlatformSupport*)  self->get_platform_support();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"anyone::PlatformSupport");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get_platform_support'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get_mesh_manager of class  anyone::Core */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_Core_get_mesh_manager00
static int tolua_anyone_anyone_Core_get_mesh_manager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::Core",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::Core* self = (anyone::Core*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get_mesh_manager'", NULL);
#endif
  {
   anyone::MeshManager* tolua_ret = (anyone::MeshManager*)  self->get_mesh_manager();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"anyone::MeshManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get_mesh_manager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_anyone_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"anyone",0);
  tolua_beginmodule(tolua_S,"anyone");
   tolua_cclass(tolua_S,"Mesh","anyone::Mesh","",NULL);
   tolua_beginmodule(tolua_S,"Mesh");
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"MeshManager","anyone::MeshManager","",NULL);
   tolua_beginmodule(tolua_S,"MeshManager");
    tolua_function(tolua_S,"load_mesh",tolua_anyone_anyone_MeshManager_load_mesh00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"PlatformSupport","anyone::PlatformSupport","",NULL);
   tolua_beginmodule(tolua_S,"PlatformSupport");
    tolua_function(tolua_S,"set_full_screen",tolua_anyone_anyone_PlatformSupport_set_full_screen00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Core","anyone::Core","",NULL);
   tolua_beginmodule(tolua_S,"Core");
    tolua_function(tolua_S,"get_singleton_ptr",tolua_anyone_anyone_Core_get_singleton_ptr00);
    tolua_function(tolua_S,"get_platform_support",tolua_anyone_anyone_Core_get_platform_support00);
    tolua_function(tolua_S,"get_mesh_manager",tolua_anyone_anyone_Core_get_mesh_manager00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_anyone (lua_State* tolua_S) {
 return tolua_anyone_open(tolua_S);
};
#endif

