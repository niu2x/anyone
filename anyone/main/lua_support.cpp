#include "lua_support.h"
#include "core.h"

namespace anyone {

LuaValue::LuaValue() : L_(nullptr), ref_(0) { }
LuaValue::~LuaValue()
{
    if (ref_)
        luaL_unref(L_, LUA_REGISTRYINDEX, ref_);
}

LuaFunction::LuaFunction(lua_State* L, int slot)
{
    L_ = L;

    if (lua_isfunction(L_, slot)) {
        lua_pushvalue(L_, slot);
        ref_ = luaL_ref(L_, LUA_REGISTRYINDEX);
    } else {
        LOG("LuaFunction: is not a lua function");
    }
}

void LuaFunction::protected_call()
{
    int old_top = lua_gettop(L_);
    lua_rawgeti(L_, LUA_REGISTRYINDEX, ref_);
    lua_pcall(L_, 0, 0, 0);
    lua_settop(L_, old_top);
}

LuaTable::LuaTable(lua_State* L, int slot)
{
    L_ = L;
    if (lua_istable(L_, slot)) {
        lua_pushvalue(L_, slot);
        ref_ = luaL_ref(L_, LUA_REGISTRYINDEX);
    } else {
        LOG("LuaTable: is not a lua table");
    }
}

LuaFunction* LuaTable::get_function(const char* field)
{
    LuaFunction* value = nullptr;
    int old_top = lua_gettop(L_);
    lua_rawgeti(L_, LUA_REGISTRYINDEX, ref_);
    lua_getfield(L_, -1, field);
    value = new LuaFunction(L_, -1);
    lua_settop(L_, old_top);
    return value;
}

void LuaCoreEventListener::set_proxy(LuaTable* table)
{
    DELETE_AND_SET_NULL(frame_update_);
    DELETE_AND_SET_NULL(mouse_move_);
    DELETE_AND_SET_NULL(mouse_wheel_);
    DELETE_AND_SET_NULL(mouse_button_);
    DELETE_AND_SET_NULL(keyboard_);

    delete proxy_;

    proxy_ = table;

    if (proxy_ && proxy_->is_valid()) {
        frame_update_ = proxy_->get_function("onFrameUpdate");
        mouse_move_ = proxy_->get_function("onMouseMove");
        mouse_wheel_ = proxy_->get_function("onMouseWheel");
        mouse_button_ = proxy_->get_function("onMouseButton");
        keyboard_ = proxy_->get_function("onKeyboard");
    }
}

LuaCoreEventListener::LuaCoreEventListener()
: proxy_(nullptr)
, frame_update_(nullptr)
, mouse_move_(nullptr)
, mouse_wheel_(nullptr)
, mouse_button_(nullptr)
, keyboard_(nullptr)
{
}

LuaCoreEventListener::~LuaCoreEventListener()
{
    delete proxy_;
    delete frame_update_;
    delete mouse_move_;
    delete mouse_wheel_;
    delete mouse_button_;
    delete keyboard_;
}

void LuaCoreEventListener::on_mouse_move(const MouseMoveEvent& e)
{
    if (mouse_move_ && mouse_move_->is_valid()) {
        // mouse_move_->protected_call();
        mouse_move_->protected_call(e.x, e.y, e.rel_x, e.rel_y);
    }
}

void LuaCoreEventListener::on_mouse_button(const MouseButtonEvent& e)
{
    if (mouse_button_ && mouse_button_->is_valid()) {
        mouse_button_->protected_call(e.type, e.x, e.y, e.button);
    }
}

void LuaCoreEventListener::on_mouse_wheel(const MouseWheelEvent& e)
{
    if (mouse_wheel_ && mouse_wheel_->is_valid()) {
        mouse_wheel_->protected_call(e.direction, e.x, e.y);
    }
}

void LuaCoreEventListener::on_keyboard(const KeyboardEvent& e)
{
    if (keyboard_ && keyboard_->is_valid()) {
        keyboard_->protected_call(e.type, e.key_code, e.repeat);
    }
}

void LuaCoreEventListener::on_frame_update()
{
    if (frame_update_ && frame_update_->is_valid())
        frame_update_->protected_call();
}

} // namespace anyone