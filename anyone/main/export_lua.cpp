/*
** Lua binding: anyone
** Generated automatically by tolua++-1.0.93 on Tue Apr 15 11:02:29 2025.
*/

#ifndef __cplusplus
    #include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

#define tolua_iscppstring tolua_isstring
#define anyone_pushcppstring(lua_state, sz) lua_pushlstring(lua_state, sz.c_str(), sz.size())


/* Exported function */
TOLUA_API int  tolua_anyone_open (lua_State* tolua_S);

#include "main/model_manager.h"
#include "main/model.h"
#include "main/core.h"
#include "main/attachment.h"
#include "main/scene_node.h"
#include "main/scene_manager.h"
#include "main/lua_support.h"
#include "platform/api/support.h"
#include "texture_loader.h"
#include "tolua_support.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_anyone__LuaCoreEventListener(lua_State* tolua_S)
{
    anyone::LuaCoreEventListener* self = (anyone::LuaCoreEventListener*)
        tolua_tousertype(tolua_S, 1, 0);
    Mtolua_delete(self);
    return 0;
}
#endif

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "anyone::LuaCoreEventListener");
    tolua_usertype(tolua_S, "kmMat4");
    tolua_usertype(tolua_S, "anyone::VertexBuffer");
    tolua_usertype(tolua_S, "anyone::Texture2D");
    tolua_usertype(tolua_S, "anyone::Renderable");
    tolua_usertype(tolua_S, "anyone::ModelManager");
    tolua_usertype(tolua_S, "anyone::Camera");
    tolua_usertype(tolua_S, "kmVec3");
    tolua_usertype(tolua_S, "anyone::SceneNode");
    tolua_usertype(tolua_S, "anyone::Attachment");
    tolua_usertype(tolua_S, "anyone::RenderAPI");
    tolua_usertype(tolua_S, "anyone::TextureLoader");
    tolua_usertype(tolua_S, "anyone::MouseButtonEventType");
    tolua_usertype(tolua_S, "anyone::MouseWheelDirection");
    tolua_usertype(tolua_S, "anyone::KeyboardEventType");
    tolua_usertype(tolua_S, "anyone::Program");
    tolua_usertype(tolua_S, "kmScalar");
    tolua_usertype(tolua_S, "anyone::CubeMap");
    tolua_usertype(tolua_S, "anyone::IndiceBuffer");
    tolua_usertype(tolua_S, "anyone::CoreEventListener");
    tolua_usertype(tolua_S, "anyone::SceneManager");

    tolua_usertype(tolua_S, "anyone::PlatformSupport");
    tolua_usertype(tolua_S, "anyone::Model");
    tolua_usertype(tolua_S, "anyone::Core");
}

/* get function: x of class  kmVec3 */
#ifndef TOLUA_DISABLE_tolua_get_kmVec3_x
static int tolua_get_kmVec3_x(lua_State* tolua_S)
{
    kmVec3* self = (kmVec3*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
    if (!self)
        tolua_error(tolua_S, "invalid 'self' in accessing variable 'x'", NULL);
    #endif
    tolua_pushusertype(tolua_S, (void*)&self->x, "kmScalar");
    return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: x of class  kmVec3 */
#ifndef TOLUA_DISABLE_tolua_set_kmVec3_x
static int tolua_set_kmVec3_x(lua_State* tolua_S)
{
    kmVec3* self = (kmVec3*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self)
        tolua_error(tolua_S, "invalid 'self' in accessing variable 'x'", NULL);
    if ((tolua_isvaluenil(tolua_S, 2, &tolua_err)
         || !tolua_isusertype(tolua_S, 2, "kmScalar", 0, &tolua_err)))
        tolua_error(
            tolua_S, "#vinvalid type in variable assignment.", &tolua_err);
    #endif
    self->x = *((kmScalar*)tolua_tousertype(tolua_S, 2, 0));
    return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: y of class  kmVec3 */
#ifndef TOLUA_DISABLE_tolua_get_kmVec3_y
static int tolua_get_kmVec3_y(lua_State* tolua_S)
{
    kmVec3* self = (kmVec3*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
    if (!self)
        tolua_error(tolua_S, "invalid 'self' in accessing variable 'y'", NULL);
    #endif
    tolua_pushusertype(tolua_S, (void*)&self->y, "kmScalar");
    return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: y of class  kmVec3 */
#ifndef TOLUA_DISABLE_tolua_set_kmVec3_y
static int tolua_set_kmVec3_y(lua_State* tolua_S)
{
    kmVec3* self = (kmVec3*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self)
        tolua_error(tolua_S, "invalid 'self' in accessing variable 'y'", NULL);
    if ((tolua_isvaluenil(tolua_S, 2, &tolua_err)
         || !tolua_isusertype(tolua_S, 2, "kmScalar", 0, &tolua_err)))
        tolua_error(
            tolua_S, "#vinvalid type in variable assignment.", &tolua_err);
    #endif
    self->y = *((kmScalar*)tolua_tousertype(tolua_S, 2, 0));
    return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: z of class  kmVec3 */
#ifndef TOLUA_DISABLE_tolua_get_kmVec3_z
static int tolua_get_kmVec3_z(lua_State* tolua_S)
{
    kmVec3* self = (kmVec3*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
    if (!self)
        tolua_error(tolua_S, "invalid 'self' in accessing variable 'z'", NULL);
    #endif
    tolua_pushusertype(tolua_S, (void*)&self->z, "kmScalar");
    return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: z of class  kmVec3 */
#ifndef TOLUA_DISABLE_tolua_set_kmVec3_z
static int tolua_set_kmVec3_z(lua_State* tolua_S)
{
    kmVec3* self = (kmVec3*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self)
        tolua_error(tolua_S, "invalid 'self' in accessing variable 'z'", NULL);
    if ((tolua_isvaluenil(tolua_S, 2, &tolua_err)
         || !tolua_isusertype(tolua_S, 2, "kmScalar", 0, &tolua_err)))
        tolua_error(
            tolua_S, "#vinvalid type in variable assignment.", &tolua_err);
    #endif
    self->z = *((kmScalar*)tolua_tousertype(tolua_S, 2, 0));
    return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: set_eye of class  anyone::Camera */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_Camera_set_eye00
static int tolua_anyone_anyone_Camera_set_eye00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "anyone::Camera", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 3, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 4, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 5, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        anyone::Camera* self = (anyone::Camera*)tolua_tousertype(tolua_S, 1, 0);
        float x = ((float)tolua_tonumber(tolua_S, 2, 0));
        float y = ((float)tolua_tonumber(tolua_S, 3, 0));
        float z = ((float)tolua_tonumber(tolua_S, 4, 0));
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'set_eye'", NULL);
    #endif
        {
            self->set_eye(x, y, z);
        }
    }
    return 0;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'set_eye'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: look_at of class  anyone::Camera */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_Camera_look_at00
static int tolua_anyone_anyone_Camera_look_at00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "anyone::Camera", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 3, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 4, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 5, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        anyone::Camera* self = (anyone::Camera*)tolua_tousertype(tolua_S, 1, 0);
        float x = ((float)tolua_tonumber(tolua_S, 2, 0));
        float y = ((float)tolua_tonumber(tolua_S, 3, 0));
        float z = ((float)tolua_tonumber(tolua_S, 4, 0));
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'look_at'", NULL);
    #endif
        {
            self->look_at(x, y, z);
        }
    }
    return 0;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'look_at'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: set_up of class  anyone::Camera */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_Camera_set_up00
static int tolua_anyone_anyone_Camera_set_up00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "anyone::Camera", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 3, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 4, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 5, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        anyone::Camera* self = (anyone::Camera*)tolua_tousertype(tolua_S, 1, 0);
        float x = ((float)tolua_tonumber(tolua_S, 2, 0));
        float y = ((float)tolua_tonumber(tolua_S, 3, 0));
        float z = ((float)tolua_tonumber(tolua_S, 4, 0));
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'set_up'", NULL);
    #endif
        {
            self->set_up(x, y, z);
        }
    }
    return 0;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'set_up'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get_view_matrix of class  anyone::Camera */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_Camera_get_view_matrix00
static int tolua_anyone_anyone_Camera_get_view_matrix00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "const anyone::Camera", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        const anyone::Camera* self = (const anyone::Camera*)tolua_tousertype(
            tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(
                tolua_S, "invalid 'self' in function 'get_view_matrix'", NULL);
    #endif
        {
            const kmMat4* tolua_ret = (const kmMat4*)self->get_view_matrix();
            tolua_pushusertype(tolua_S, (void*)tolua_ret, "const kmMat4");
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'get_view_matrix'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get_proj_matrix of class  anyone::Camera */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_Camera_get_proj_matrix00
static int tolua_anyone_anyone_Camera_get_proj_matrix00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "const anyone::Camera", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        const anyone::Camera* self = (const anyone::Camera*)tolua_tousertype(
            tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(
                tolua_S, "invalid 'self' in function 'get_proj_matrix'", NULL);
    #endif
        {
            const kmMat4* tolua_ret = (const kmMat4*)self->get_proj_matrix();
            tolua_pushusertype(tolua_S, (void*)tolua_ret, "const kmMat4");
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'get_proj_matrix'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: set_aspect of class  anyone::Camera */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_Camera_set_aspect00
static int tolua_anyone_anyone_Camera_set_aspect00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "anyone::Camera", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        anyone::Camera* self = (anyone::Camera*)tolua_tousertype(tolua_S, 1, 0);
        float a = ((float)tolua_tonumber(tolua_S, 2, 0));
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(
                tolua_S, "invalid 'self' in function 'set_aspect'", NULL);
    #endif
        {
            self->set_aspect(a);
        }
    }
    return 0;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'set_aspect'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: set_fov of class  anyone::Camera */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_Camera_set_fov00
static int tolua_anyone_anyone_Camera_set_fov00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "anyone::Camera", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        anyone::Camera* self = (anyone::Camera*)tolua_tousertype(tolua_S, 1, 0);
        float a = ((float)tolua_tonumber(tolua_S, 2, 0));
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'set_fov'", NULL);
    #endif
        {
            self->set_fov(a);
        }
    }
    return 0;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'set_fov'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: set_near_clip of class  anyone::Camera */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_Camera_set_near_clip00
static int tolua_anyone_anyone_Camera_set_near_clip00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "anyone::Camera", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        anyone::Camera* self = (anyone::Camera*)tolua_tousertype(tolua_S, 1, 0);
        float a = ((float)tolua_tonumber(tolua_S, 2, 0));
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(
                tolua_S, "invalid 'self' in function 'set_near_clip'", NULL);
    #endif
        {
            self->set_near_clip(a);
        }
    }
    return 0;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'set_near_clip'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: set_far_clip of class  anyone::Camera */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_Camera_set_far_clip00
static int tolua_anyone_anyone_Camera_set_far_clip00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "anyone::Camera", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        anyone::Camera* self = (anyone::Camera*)tolua_tousertype(tolua_S, 1, 0);
        float a = ((float)tolua_tonumber(tolua_S, 2, 0));
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(
                tolua_S, "invalid 'self' in function 'set_far_clip'", NULL);
    #endif
        {
            self->set_far_clip(a);
        }
    }
    return 0;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'set_far_clip'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: apply of class  anyone::Camera */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_Camera_apply00
static int tolua_anyone_anyone_Camera_apply00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "anyone::Camera", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        anyone::Camera* self = (anyone::Camera*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'apply'", NULL);
    #endif
        {
            self->apply();
        }
    }
    return 0;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'apply'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get_eye of class  anyone::Camera */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_Camera_get_eye00
static int tolua_anyone_anyone_Camera_get_eye00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "const anyone::Camera", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        const anyone::Camera* self = (const anyone::Camera*)tolua_tousertype(
            tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'get_eye'", NULL);
    #endif
        {
            const kmVec3* tolua_ret = (const kmVec3*)self->get_eye();
            tolua_pushusertype(tolua_S, (void*)tolua_ret, "const kmVec3");
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'get_eye'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pan of class  anyone::Camera */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_Camera_pan00
static int tolua_anyone_anyone_Camera_pan00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "anyone::Camera", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 3, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 4, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        anyone::Camera* self = (anyone::Camera*)tolua_tousertype(tolua_S, 1, 0);
        float x = ((float)tolua_tonumber(tolua_S, 2, 0));
        float y = ((float)tolua_tonumber(tolua_S, 3, 0));
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'pan'", NULL);
    #endif
        {
            self->pan(x, y);
        }
    }
    return 0;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'pan'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: load_cube_map_png of class  anyone::TextureLoader */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_TextureLoader_load_cube_map_png00
static int tolua_anyone_anyone_TextureLoader_load_cube_map_png00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"anyone::TextureLoader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* uri = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   anyone::CubeMap* tolua_ret = (anyone::CubeMap*)  anyone::TextureLoader::load_cube_map_png(uri);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"anyone::CubeMap");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'load_cube_map_png'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  anyone::LuaCoreEventListener */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_LuaCoreEventListener_new00
static int tolua_anyone_anyone_LuaCoreEventListener_new00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(
            tolua_S, 1, "anyone::LuaCoreEventListener", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            anyone::LuaCoreEventListener* tolua_ret
                = (anyone::LuaCoreEventListener*)Mtolua_new(
                    (anyone::LuaCoreEventListener)());
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "anyone::LuaCoreEventListener");
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'new'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  anyone::LuaCoreEventListener */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_LuaCoreEventListener_new00_local
static int
tolua_anyone_anyone_LuaCoreEventListener_new00_local(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(
            tolua_S, 1, "anyone::LuaCoreEventListener", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            anyone::LuaCoreEventListener* tolua_ret
                = (anyone::LuaCoreEventListener*)Mtolua_new(
                    (anyone::LuaCoreEventListener)());
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "anyone::LuaCoreEventListener");
            tolua_register_gc(tolua_S, lua_gettop(tolua_S));
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'new'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  anyone::LuaCoreEventListener */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_LuaCoreEventListener_delete00
static int tolua_anyone_anyone_LuaCoreEventListener_delete00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(
            tolua_S, 1, "anyone::LuaCoreEventListener", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        anyone::LuaCoreEventListener* self = (anyone::LuaCoreEventListener*)
            tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'delete'", NULL);
    #endif
        Mtolua_delete(self);
    }
    return 0;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'delete'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: set_proxy of class  anyone::LuaCoreEventListener */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_LuaCoreEventListener_set_proxy00
static int
tolua_anyone_anyone_LuaCoreEventListener_set_proxy00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(
            tolua_S, 1, "anyone::LuaCoreEventListener", 0, &tolua_err)
        || (tolua_isvaluenil(tolua_S, 2, &tolua_err)
            || !__tolua_is_lua_table(tolua_S, 2, "LUA_TABLE", 0, &tolua_err))
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        anyone::LuaCoreEventListener* self = (anyone::LuaCoreEventListener*)
            tolua_tousertype(tolua_S, 1, 0);
        LUA_TABLE table = (__tolua_create_lua_table(tolua_S, 2, 0));
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(
                tolua_S, "invalid 'self' in function 'set_proxy'", NULL);
    #endif
        {
            self->set_proxy(table);
        }
    }
    return 0;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'set_proxy'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroy_vertex_buffer of class  anyone::RenderAPI */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_RenderAPI_destroy_vertex_buffer00
static int tolua_anyone_anyone_RenderAPI_destroy_vertex_buffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::RenderAPI",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"anyone::VertexBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::RenderAPI* self = (anyone::RenderAPI*)  tolua_tousertype(tolua_S,1,0);
  anyone::VertexBuffer* vbo = ((anyone::VertexBuffer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'destroy_vertex_buffer'", NULL);
#endif
  {
   self->destroy_vertex_buffer(vbo);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroy_vertex_buffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroy_indice_buffer of class  anyone::RenderAPI */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_RenderAPI_destroy_indice_buffer00
static int tolua_anyone_anyone_RenderAPI_destroy_indice_buffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::RenderAPI",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"anyone::IndiceBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::RenderAPI* self = (anyone::RenderAPI*)  tolua_tousertype(tolua_S,1,0);
  anyone::IndiceBuffer* veo = ((anyone::IndiceBuffer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'destroy_indice_buffer'", NULL);
#endif
  {
   self->destroy_indice_buffer(veo);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroy_indice_buffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroy_texture_2d of class  anyone::RenderAPI */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_RenderAPI_destroy_texture_2d00
static int tolua_anyone_anyone_RenderAPI_destroy_texture_2d00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::RenderAPI",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"anyone::Texture2D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::RenderAPI* self = (anyone::RenderAPI*)  tolua_tousertype(tolua_S,1,0);
  anyone::Texture2D* vbo = ((anyone::Texture2D*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'destroy_texture_2d'", NULL);
#endif
  {
   self->destroy_texture_2d(vbo);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroy_texture_2d'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroy_cube_map of class  anyone::RenderAPI */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_RenderAPI_destroy_cube_map00
static int tolua_anyone_anyone_RenderAPI_destroy_cube_map00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::RenderAPI",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"anyone::CubeMap",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::RenderAPI* self = (anyone::RenderAPI*)  tolua_tousertype(tolua_S,1,0);
  anyone::CubeMap* cb = ((anyone::CubeMap*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'destroy_cube_map'", NULL);
#endif
  {
   self->destroy_cube_map(cb);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroy_cube_map'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroy_program of class  anyone::RenderAPI */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_RenderAPI_destroy_program00
static int tolua_anyone_anyone_RenderAPI_destroy_program00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::RenderAPI",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"anyone::Program",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::RenderAPI* self = (anyone::RenderAPI*)  tolua_tousertype(tolua_S,1,0);
  anyone::Program* p = ((anyone::Program*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'destroy_program'", NULL);
#endif
  {
   self->destroy_program(p);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroy_program'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

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

/* method: get_render_api of class  anyone::PlatformSupport */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_PlatformSupport_get_render_api00
static int tolua_anyone_anyone_PlatformSupport_get_render_api00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::PlatformSupport",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::PlatformSupport* self = (anyone::PlatformSupport*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get_render_api'", NULL);
#endif
  {
   anyone::RenderAPI* tolua_ret = (anyone::RenderAPI*)  self->get_render_api();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"anyone::RenderAPI");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get_render_api'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: exit of class  anyone::PlatformSupport */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_PlatformSupport_exit00
static int tolua_anyone_anyone_PlatformSupport_exit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::PlatformSupport",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::PlatformSupport* self = (anyone::PlatformSupport*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'exit'", NULL);
#endif
  {
   self->exit();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'exit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: is_full_screen of class  anyone::PlatformSupport */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_PlatformSupport_is_full_screen00
static int
tolua_anyone_anyone_PlatformSupport_is_full_screen00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(
            tolua_S, 1, "const anyone::PlatformSupport", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        const anyone::PlatformSupport* self = (const anyone::PlatformSupport*)
            tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(
                tolua_S, "invalid 'self' in function 'is_full_screen'", NULL);
    #endif
        {
            bool tolua_ret = (bool)self->is_full_screen();
            tolua_pushboolean(tolua_S, (bool)tolua_ret);
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'is_full_screen'.", &tolua_err);
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

/* method: add_core_event_listener of class  anyone::Core */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_Core_add_core_event_listener00
static int tolua_anyone_anyone_Core_add_core_event_listener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::Core",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"anyone::CoreEventListener",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::Core* self = (anyone::Core*)  tolua_tousertype(tolua_S,1,0);
  anyone::CoreEventListener* l = ((anyone::CoreEventListener*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'add_core_event_listener'", NULL);
#endif
  {
   self->add_core_event_listener(l);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'add_core_event_listener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get_camera of class  anyone::Core */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_Core_get_camera00
static int tolua_anyone_anyone_Core_get_camera00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "anyone::Core", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        anyone::Core* self = (anyone::Core*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(
                tolua_S, "invalid 'self' in function 'get_camera'", NULL);
    #endif
        {
            anyone::Camera* tolua_ret = (anyone::Camera*)self->get_camera();
            tolua_pushusertype(tolua_S, (void*)tolua_ret, "anyone::Camera");
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'get_camera'.", &tolua_err);
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

/* method: set_sky_box of class  anyone::SceneManager */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_SceneManager_set_sky_box00
static int tolua_anyone_anyone_SceneManager_set_sky_box00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::SceneManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"anyone::CubeMap",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::SceneManager* self = (anyone::SceneManager*)  tolua_tousertype(tolua_S,1,0);
  anyone::CubeMap* c = ((anyone::CubeMap*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'set_sky_box'", NULL);
#endif
  {
   self->set_sky_box(c);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'set_sky_box'.",&tolua_err);
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

/* method: rotate_by_local_z_axis of class  anyone::SceneNode */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_SceneNode_rotate_by_local_z_axis00
static int tolua_anyone_anyone_SceneNode_rotate_by_local_z_axis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::SceneNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::SceneNode* self = (anyone::SceneNode*)  tolua_tousertype(tolua_S,1,0);
  float r = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rotate_by_local_z_axis'", NULL);
#endif
  {
   self->rotate_by_local_z_axis(r);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rotate_by_local_z_axis'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rotate_by_local_x_axis of class  anyone::SceneNode */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_SceneNode_rotate_by_local_x_axis00
static int tolua_anyone_anyone_SceneNode_rotate_by_local_x_axis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::SceneNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::SceneNode* self = (anyone::SceneNode*)  tolua_tousertype(tolua_S,1,0);
  float r = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rotate_by_local_x_axis'", NULL);
#endif
  {
   self->rotate_by_local_x_axis(r);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rotate_by_local_x_axis'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rotate_by_local_y_axis of class  anyone::SceneNode */
#ifndef TOLUA_DISABLE_tolua_anyone_anyone_SceneNode_rotate_by_local_y_axis00
static int tolua_anyone_anyone_SceneNode_rotate_by_local_y_axis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anyone::SceneNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anyone::SceneNode* self = (anyone::SceneNode*)  tolua_tousertype(tolua_S,1,0);
  float r = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rotate_by_local_y_axis'", NULL);
#endif
  {
   self->rotate_by_local_y_axis(r);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rotate_by_local_y_axis'.",&tolua_err);
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
 tolua_cclass(tolua_S, "kmMat4", "kmMat4", "", NULL);
 tolua_beginmodule(tolua_S, "kmMat4");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S, "kmVec3", "kmVec3", "", NULL);
 tolua_beginmodule(tolua_S, "kmVec3");
 tolua_variable(tolua_S, "x", tolua_get_kmVec3_x, tolua_set_kmVec3_x);
 tolua_variable(tolua_S, "y", tolua_get_kmVec3_y, tolua_set_kmVec3_y);
 tolua_variable(tolua_S, "z", tolua_get_kmVec3_z, tolua_set_kmVec3_z);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S, "anyone", 0);
 tolua_beginmodule(tolua_S, "anyone");
 tolua_cclass(tolua_S, "VertexBuffer", "anyone::VertexBuffer", "", NULL);
 tolua_beginmodule(tolua_S, "VertexBuffer");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S, "IndiceBuffer", "anyone::IndiceBuffer", "", NULL);
 tolua_beginmodule(tolua_S, "IndiceBuffer");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S, "Texture2D", "anyone::Texture2D", "", NULL);
 tolua_beginmodule(tolua_S, "Texture2D");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S, "CubeMap", "anyone::CubeMap", "", NULL);
 tolua_beginmodule(tolua_S, "CubeMap");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S, "Program", "anyone::Program", "", NULL);
 tolua_beginmodule(tolua_S, "Program");
 tolua_endmodule(tolua_S);
 tolua_constant(tolua_S, "KEY_UNKNOWN", anyone::KEY_UNKNOWN);
 tolua_constant(tolua_S, "KEY_A", anyone::KEY_A);
 tolua_constant(tolua_S, "KEY_B", anyone::KEY_B);
 tolua_constant(tolua_S, "KEY_C", anyone::KEY_C);
 tolua_constant(tolua_S, "KEY_D", anyone::KEY_D);
 tolua_constant(tolua_S, "KEY_E", anyone::KEY_E);
 tolua_constant(tolua_S, "KEY_F", anyone::KEY_F);
 tolua_constant(tolua_S, "KEY_G", anyone::KEY_G);
 tolua_constant(tolua_S, "KEY_H", anyone::KEY_H);
 tolua_constant(tolua_S, "KEY_I", anyone::KEY_I);
 tolua_constant(tolua_S, "KEY_J", anyone::KEY_J);
 tolua_constant(tolua_S, "KEY_K", anyone::KEY_K);
 tolua_constant(tolua_S, "KEY_L", anyone::KEY_L);
 tolua_constant(tolua_S, "KEY_M", anyone::KEY_M);
 tolua_constant(tolua_S, "KEY_N", anyone::KEY_N);
 tolua_constant(tolua_S, "KEY_O", anyone::KEY_O);
 tolua_constant(tolua_S, "KEY_P", anyone::KEY_P);
 tolua_constant(tolua_S, "KEY_Q", anyone::KEY_Q);
 tolua_constant(tolua_S, "KEY_R", anyone::KEY_R);
 tolua_constant(tolua_S, "KEY_S", anyone::KEY_S);
 tolua_constant(tolua_S, "KEY_T", anyone::KEY_T);
 tolua_constant(tolua_S, "KEY_U", anyone::KEY_U);
 tolua_constant(tolua_S, "KEY_V", anyone::KEY_V);
 tolua_constant(tolua_S, "KEY_W", anyone::KEY_W);
 tolua_constant(tolua_S, "KEY_X", anyone::KEY_X);
 tolua_constant(tolua_S, "KEY_Y", anyone::KEY_Y);
 tolua_constant(tolua_S, "KEY_Z", anyone::KEY_Z);
 tolua_constant(tolua_S, "KEY_ESCAPE", anyone::KEY_ESCAPE);
 tolua_constant(tolua_S, "MOUSE_LEFT_BTN", anyone::MOUSE_LEFT_BTN);
 tolua_constant(tolua_S, "MOUSE_MIDDLE_BTN", anyone::MOUSE_MIDDLE_BTN);
 tolua_constant(tolua_S, "MOUSE_RIGHT_BTN", anyone::MOUSE_RIGHT_BTN);
 tolua_cclass(
     tolua_S, "KeyboardEventType", "anyone::KeyboardEventType", "", NULL);
 tolua_beginmodule(tolua_S, "KeyboardEventType");
 tolua_constant(tolua_S, "PRESS", (int)anyone::KeyboardEventType::PRESS);
 tolua_constant(tolua_S, "RELEASE", (int)anyone::KeyboardEventType::RELEASE);
 tolua_endmodule(tolua_S);
 tolua_cclass(
     tolua_S, "MouseButtonEventType", "anyone::MouseButtonEventType", "", NULL);
 tolua_beginmodule(tolua_S, "MouseButtonEventType");
 tolua_constant(tolua_S, "PRESS", (int)anyone::MouseButtonEventType::PRESS);
 tolua_constant(tolua_S, "RELEASE", (int)anyone::MouseButtonEventType::RELEASE);
 tolua_endmodule(tolua_S);
 tolua_cclass(
     tolua_S, "MouseWheelDirection", "anyone::MouseWheelDirection", "", NULL);
 tolua_beginmodule(tolua_S, "MouseWheelDirection");
 tolua_constant(tolua_S, "NORMAL", (int)anyone::MouseWheelDirection::NORMAL);
 tolua_constant(tolua_S, "FLIPPED", (int)anyone::MouseWheelDirection::FLIPPED);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S, "Camera", "anyone::Camera", "", NULL);
 tolua_beginmodule(tolua_S, "Camera");
 tolua_function(tolua_S, "set_eye", tolua_anyone_anyone_Camera_set_eye00);
 tolua_function(tolua_S, "look_at", tolua_anyone_anyone_Camera_look_at00);
 tolua_function(tolua_S, "set_up", tolua_anyone_anyone_Camera_set_up00);
 tolua_function(
     tolua_S, "get_view_matrix", tolua_anyone_anyone_Camera_get_view_matrix00);
 tolua_function(
     tolua_S, "get_proj_matrix", tolua_anyone_anyone_Camera_get_proj_matrix00);
 tolua_function(tolua_S, "set_aspect", tolua_anyone_anyone_Camera_set_aspect00);
 tolua_function(tolua_S, "set_fov", tolua_anyone_anyone_Camera_set_fov00);
 tolua_function(
     tolua_S, "set_near_clip", tolua_anyone_anyone_Camera_set_near_clip00);
 tolua_function(
     tolua_S, "set_far_clip", tolua_anyone_anyone_Camera_set_far_clip00);
 tolua_function(tolua_S, "apply", tolua_anyone_anyone_Camera_apply00);
 tolua_function(tolua_S, "get_eye", tolua_anyone_anyone_Camera_get_eye00);
 tolua_function(tolua_S, "pan", tolua_anyone_anyone_Camera_pan00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S, "TextureLoader", "anyone::TextureLoader", "", NULL);
 tolua_beginmodule(tolua_S, "TextureLoader");
 tolua_function(tolua_S,
                "load_cube_map_png",
                tolua_anyone_anyone_TextureLoader_load_cube_map_png00);
 tolua_endmodule(tolua_S);
 tolua_cclass(
     tolua_S, "CoreEventListener", "anyone::CoreEventListener", "", NULL);
 tolua_beginmodule(tolua_S, "CoreEventListener");
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,
              "LuaCoreEventListener",
              "anyone::LuaCoreEventListener",
              "anyone::CoreEventListener",
              tolua_collect_anyone__LuaCoreEventListener);
#else
 tolua_cclass(tolua_S,
              "LuaCoreEventListener",
              "anyone::LuaCoreEventListener",
              "anyone::CoreEventListener",
              NULL);
#endif
 tolua_beginmodule(tolua_S, "LuaCoreEventListener");
 tolua_function(tolua_S, "new", tolua_anyone_anyone_LuaCoreEventListener_new00);
 tolua_function(tolua_S,
                "new_local",
                tolua_anyone_anyone_LuaCoreEventListener_new00_local);
 tolua_function(
     tolua_S, ".call", tolua_anyone_anyone_LuaCoreEventListener_new00_local);
 tolua_function(
     tolua_S, "delete", tolua_anyone_anyone_LuaCoreEventListener_delete00);
 tolua_function(tolua_S,
                "set_proxy",
                tolua_anyone_anyone_LuaCoreEventListener_set_proxy00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S, "RenderAPI", "anyone::RenderAPI", "", NULL);
 tolua_beginmodule(tolua_S, "RenderAPI");
 tolua_function(tolua_S,
                "destroy_vertex_buffer",
                tolua_anyone_anyone_RenderAPI_destroy_vertex_buffer00);
 tolua_function(tolua_S,
                "destroy_indice_buffer",
                tolua_anyone_anyone_RenderAPI_destroy_indice_buffer00);
 tolua_function(tolua_S,
                "destroy_texture_2d",
                tolua_anyone_anyone_RenderAPI_destroy_texture_2d00);
 tolua_function(tolua_S,
                "destroy_cube_map",
                tolua_anyone_anyone_RenderAPI_destroy_cube_map00);
 tolua_function(tolua_S,
                "destroy_program",
                tolua_anyone_anyone_RenderAPI_destroy_program00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S, "Attachment", "anyone::Attachment", "", NULL);
 tolua_beginmodule(tolua_S, "Attachment");
 tolua_endmodule(tolua_S);
 tolua_cclass(
     tolua_S, "Renderable", "anyone::Renderable", "anyone::Attachment", NULL);
 tolua_beginmodule(tolua_S, "Renderable");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S, "Model", "anyone::Model", "anyone::Renderable", NULL);
 tolua_beginmodule(tolua_S, "Model");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S, "ModelManager", "anyone::ModelManager", "", NULL);
 tolua_beginmodule(tolua_S, "ModelManager");
 tolua_function(
     tolua_S, "load_model", tolua_anyone_anyone_ModelManager_load_model00);
 tolua_function(
     tolua_S, "unload_model", tolua_anyone_anyone_ModelManager_unload_model00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S, "PlatformSupport", "anyone::PlatformSupport", "", NULL);
 tolua_beginmodule(tolua_S, "PlatformSupport");
 tolua_function(tolua_S,
                "set_full_screen",
                tolua_anyone_anyone_PlatformSupport_set_full_screen00);
 tolua_function(tolua_S,
                "get_render_api",
                tolua_anyone_anyone_PlatformSupport_get_render_api00);
 tolua_function(tolua_S, "exit", tolua_anyone_anyone_PlatformSupport_exit00);
 tolua_function(tolua_S,
                "is_full_screen",
                tolua_anyone_anyone_PlatformSupport_is_full_screen00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S, "Core", "anyone::Core", "", NULL);
 tolua_beginmodule(tolua_S, "Core");
 tolua_function(tolua_S,
                "get_singleton_ptr",
                tolua_anyone_anyone_Core_get_singleton_ptr00);
 tolua_function(tolua_S,
                "get_platform_support",
                tolua_anyone_anyone_Core_get_platform_support00);
 tolua_function(tolua_S,
                "get_model_manager",
                tolua_anyone_anyone_Core_get_model_manager00);
 tolua_function(tolua_S,
                "get_scene_manager",
                tolua_anyone_anyone_Core_get_scene_manager00);
 tolua_function(tolua_S,
                "add_core_event_listener",
                tolua_anyone_anyone_Core_add_core_event_listener00);
 tolua_function(tolua_S, "get_camera", tolua_anyone_anyone_Core_get_camera00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S, "SceneManager", "anyone::SceneManager", "", NULL);
 tolua_beginmodule(tolua_S, "SceneManager");
 tolua_function(tolua_S,
                "get_root_node",
                tolua_anyone_anyone_SceneManager_get_root_node00);
 tolua_function(
     tolua_S, "set_sky_box", tolua_anyone_anyone_SceneManager_set_sky_box00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S, "SceneNode", "anyone::SceneNode", "", NULL);
 tolua_beginmodule(tolua_S, "SceneNode");
 tolua_function(
     tolua_S, "attach_object", tolua_anyone_anyone_SceneNode_attach_object00);
 tolua_function(
     tolua_S, "detach_object", tolua_anyone_anyone_SceneNode_detach_object00);
 tolua_function(tolua_S,
                "create_child_node",
                tolua_anyone_anyone_SceneNode_create_child_node00);
 tolua_function(
     tolua_S, "get_child", tolua_anyone_anyone_SceneNode_get_child00);
 tolua_function(
     tolua_S, "find_node", tolua_anyone_anyone_SceneNode_find_node00);
 tolua_function(
     tolua_S, "remove_child", tolua_anyone_anyone_SceneNode_remove_child00);
 tolua_function(
     tolua_S, "remove_child", tolua_anyone_anyone_SceneNode_remove_child01);
 tolua_function(
     tolua_S, "set_position", tolua_anyone_anyone_SceneNode_set_position00);
 tolua_function(tolua_S,
                "rotate_by_local_z_axis",
                tolua_anyone_anyone_SceneNode_rotate_by_local_z_axis00);
 tolua_function(tolua_S,
                "rotate_by_local_x_axis",
                tolua_anyone_anyone_SceneNode_rotate_by_local_x_axis00);
 tolua_function(tolua_S,
                "rotate_by_local_y_axis",
                tolua_anyone_anyone_SceneNode_rotate_by_local_y_axis00);
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

