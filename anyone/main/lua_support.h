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
};

} // namespace anyone