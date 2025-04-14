#pragma once

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "core_event.h"

namespace anyone {

class LuaValue {
public:
    LuaValue();
    virtual ~LuaValue();

    bool is_valid() const { return ref_ > 0; }

protected:
    lua_State* L_;
    int ref_;
};

class LuaFunction : public LuaValue {
public:
    LuaFunction(lua_State* L, int slot);
    void protected_call();

    template <class... T>
    void protected_call(const T&... args)
    {
        int old_top = lua_gettop(L_);
        lua_rawgeti(L_, LUA_REGISTRYINDEX, ref_);
        int num_args = sizeof...(T);
        push_args(args...);
        lua_pcall(L_, num_args, 0, 0);
        lua_settop(L_, old_top);
    }

private:
    template <class FirstT, class... T>
    void push_args(const FirstT& first_arg, const T&... args)
    {
        push_arg(first_arg);
        push_args(args...);
    }

    void push_arg(int arg) { lua_pushinteger(L_, arg); }
    void push_arg(bool arg) { lua_pushboolean(L_, arg); }
    void push_arg(MouseWheelDirection arg) { lua_pushinteger(L_, (int)arg); }
    void push_arg(KeyboardEventType arg) { lua_pushinteger(L_, (int)arg); }
    void push_arg(MouseButtonEventType arg) { lua_pushinteger(L_, (int)arg); }

    void push_args() { }
};

class LuaTable : public LuaValue {
public:
    LuaTable(lua_State* L, int slot);

    LuaFunction* get_function(const char* field);
};

class LuaCoreEventListener : public CoreEventListener {
public:
    LuaCoreEventListener();
    ~LuaCoreEventListener();
    void set_proxy(LuaTable* table);

    void on_mouse_move(const MouseMoveEvent&) override;
    void on_mouse_button(const MouseButtonEvent&) override;
    void on_mouse_wheel(const MouseWheelEvent&) override;
    void on_keyboard(const KeyboardEvent&) override;
    void on_frame_update() override;

private:
    LuaTable* proxy_;
    LuaFunction* frame_update_;
    LuaFunction* mouse_move_;
    LuaFunction* mouse_wheel_;
    LuaFunction* mouse_button_;
    LuaFunction* keyboard_;
};

} // namespace anyone