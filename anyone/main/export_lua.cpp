/*
** Lua binding: anyone
** Generated automatically by tolua++-1.0.93 on Wed Apr  9 19:34:21 2025.
*/


#include "stdlib.h"
#include "string.h"
#include "tolua++.h"

#define tolua_iscppstring                       tolua_isstring
#define anyone_pushcppstring(lua_state, sz) lua_pushlstring(lua_state, sz.c_str(), sz.size())


/* Exported function */
TOLUA_API int  tolua_anyone_open (lua_State* tolua_S);

#include "main/model_manager.h"
#include "main/model.h"
#include "main/core.h"
#include "main/attachment.h"
#include "main/scene_node.h"
#include "main/scene_manager.h"
#include "platform/api/support.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"anyone::PlatformSupport");
 tolua_usertype(tolua_S,"anyone::SceneNode");
 tolua_usertype(tolua_S,"anyone::Core");
 tolua_usertype(tolua_S,"anyone::SceneManager");
 tolua_usertype(tolua_S,"anyone::Model");
 tolua_usertype(tolua_S,"anyone::Renderable");
 tolua_usertype(tolua_S,"anyone::Attachment");
 tolua_usertype(tolua_S,"anyone::ModelManager");
}

/* method: load_model of class  anyone::ModelManager */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_ModelManager_load_model00
static int tolua_anyone_anyone_ModelManager_load_model00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::ModelManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::ModelManager* self = (anyone::ModelManager*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* path = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'load_model'", NULL);
#endif
  {
   anyone::Model* tolua_ret = (anyone::Model*)  self->load_model(name,path);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"anyone::Model");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'load_model'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unload_model of class  anyone::ModelManager */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_ModelManager_unload_model00
static int tolua_anyone_anyone_ModelManager_unload_model00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::ModelManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::ModelManager* self = (anyone::ModelManager*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unload_model'", NULL);
#endif
  {
   self->unload_model(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unload_model'.",&tolua_err);
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

/* method: get_model_manager of class  anyone::Core */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_Core_get_model_manager00
static int tolua_anyone_anyone_Core_get_model_manager00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get_model_manager'", NULL);
#endif
  {
   anyone::ModelManager* tolua_ret = (anyone::ModelManager*)  self->get_model_manager();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"anyone::ModelManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get_model_manager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get_scene_manager of class  anyone::Core */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_Core_get_scene_manager00
static int tolua_anyone_anyone_Core_get_scene_manager00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get_scene_manager'", NULL);
#endif
  {
   anyone::SceneManager* tolua_ret = (anyone::SceneManager*)  self->get_scene_manager();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"anyone::SceneManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get_scene_manager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get_root_node of class  anyone::SceneManager */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_SceneManager_get_root_node00
static int tolua_anyone_anyone_SceneManager_get_root_node00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::SceneManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::SceneManager* self = (anyone::SceneManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get_root_node'", NULL);
#endif
  {
   anyone::SceneNode* tolua_ret = (anyone::SceneNode*)  self->get_root_node();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"anyone::SceneNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get_root_node'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attach_object of class  anyone::SceneNode */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_SceneNode_attach_object00
static int tolua_anyone_anyone_SceneNode_attach_object00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::SceneNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"anyone::Renderable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::SceneNode* self = (anyone::SceneNode*)  tolua_tousertype(tolua_S,1,0);
  anyone::Renderable* a = ((anyone::Renderable*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attach_object'", NULL);
#endif
  {
   self->attach_object(a);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attach_object'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: detach_object of class  anyone::SceneNode */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_SceneNode_detach_object00
static int tolua_anyone_anyone_SceneNode_detach_object00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::SceneNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"anyone::Renderable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::SceneNode* self = (anyone::SceneNode*)  tolua_tousertype(tolua_S,1,0);
  anyone::Renderable* a = ((anyone::Renderable*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'detach_object'", NULL);
#endif
  {
   self->detach_object(a);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'detach_object'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create_child_node of class  anyone::SceneNode */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_SceneNode_create_child_node00
static int tolua_anyone_anyone_SceneNode_create_child_node00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::SceneNode",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::SceneNode* self = (anyone::SceneNode*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'create_child_node'", NULL);
#endif
  {
   anyone::SceneNode* tolua_ret = (anyone::SceneNode*)  self->create_child_node(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"anyone::SceneNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create_child_node'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get_child of class  anyone::SceneNode */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_SceneNode_get_child00
static int tolua_anyone_anyone_SceneNode_get_child00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::SceneNode",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::SceneNode* self = (anyone::SceneNode*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get_child'", NULL);
#endif
  {
   anyone::SceneNode* tolua_ret = (anyone::SceneNode*)  self->get_child(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"anyone::SceneNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get_child'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: find_node of class  anyone::SceneNode */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_SceneNode_find_node00
static int tolua_anyone_anyone_SceneNode_find_node00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::SceneNode",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::SceneNode* self = (anyone::SceneNode*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'find_node'", NULL);
#endif
  {
   anyone::SceneNode* tolua_ret = (anyone::SceneNode*)  self->find_node(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"anyone::SceneNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'find_node'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: remove_child of class  anyone::SceneNode */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_SceneNode_remove_child00
static int tolua_anyone_anyone_SceneNode_remove_child00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::SceneNode",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::SceneNode* self = (anyone::SceneNode*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'remove_child'", NULL);
#endif
  {
   self->remove_child(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'remove_child'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: remove_child of class  anyone::SceneNode */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_SceneNode_remove_child01
static int tolua_anyone_anyone_SceneNode_remove_child01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::SceneNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"anyone::SceneNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  anyone::SceneNode* self = (anyone::SceneNode*)  tolua_tousertype(tolua_S,1,0);
  anyone::SceneNode* tolua_var_2 = ((anyone::SceneNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'remove_child'", NULL);
#endif
  {
   self->remove_child(tolua_var_2);
  }
 }
 return 0;
tolua_lerror:
 return tolua_anyone_anyone_SceneNode_remove_child00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: set_position of class  anyone::SceneNode */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_SceneNode_set_position00
static int tolua_anyone_anyone_SceneNode_set_position00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::SceneNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::SceneNode* self = (anyone::SceneNode*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'set_position'", NULL);
#endif
  {
   self->set_position(x,y,z);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'set_position'.",&tolua_err);
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
   tolua_cclass(tolua_S,"Attachment","anyone::Attachment","",NULL);
   tolua_beginmodule(tolua_S,"Attachment");
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Renderable","anyone::Renderable","anyone::Attachment",NULL);
   tolua_beginmodule(tolua_S,"Renderable");
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Model","anyone::Model","anyone::Renderable",NULL);
   tolua_beginmodule(tolua_S,"Model");
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"ModelManager","anyone::ModelManager","",NULL);
   tolua_beginmodule(tolua_S,"ModelManager");
    tolua_function(tolua_S,"load_model",tolua_anyone_anyone_ModelManager_load_model00);
    tolua_function(tolua_S,"unload_model",tolua_anyone_anyone_ModelManager_unload_model00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"PlatformSupport","anyone::PlatformSupport","",NULL);
   tolua_beginmodule(tolua_S,"PlatformSupport");
    tolua_function(tolua_S,"set_full_screen",tolua_anyone_anyone_PlatformSupport_set_full_screen00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Core","anyone::Core","",NULL);
   tolua_beginmodule(tolua_S,"Core");
    tolua_function(tolua_S,"get_singleton_ptr",tolua_anyone_anyone_Core_get_singleton_ptr00);
    tolua_function(tolua_S,"get_platform_support",tolua_anyone_anyone_Core_get_platform_support00);
    tolua_function(tolua_S,"get_model_manager",tolua_anyone_anyone_Core_get_model_manager00);
    tolua_function(tolua_S,"get_scene_manager",tolua_anyone_anyone_Core_get_scene_manager00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"SceneManager","anyone::SceneManager","",NULL);
   tolua_beginmodule(tolua_S,"SceneManager");
    tolua_function(tolua_S,"get_root_node",tolua_anyone_anyone_SceneManager_get_root_node00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"SceneNode","anyone::SceneNode","",NULL);
   tolua_beginmodule(tolua_S,"SceneNode");
    tolua_function(tolua_S,"attach_object",tolua_anyone_anyone_SceneNode_attach_object00);
    tolua_function(tolua_S,"detach_object",tolua_anyone_anyone_SceneNode_detach_object00);
    tolua_function(tolua_S,"create_child_node",tolua_anyone_anyone_SceneNode_create_child_node00);
    tolua_function(tolua_S,"get_child",tolua_anyone_anyone_SceneNode_get_child00);
    tolua_function(tolua_S,"find_node",tolua_anyone_anyone_SceneNode_find_node00);
    tolua_function(tolua_S,"remove_child",tolua_anyone_anyone_SceneNode_remove_child00);
    tolua_function(tolua_S,"remove_child",tolua_anyone_anyone_SceneNode_remove_child01);
    tolua_function(tolua_S,"set_position",tolua_anyone_anyone_SceneNode_set_position00);
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

