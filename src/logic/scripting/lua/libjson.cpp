#include "api_lua.hpp"
#include "lua_commons.hpp"
#include "LuaState.hpp"

#include "../../../coders/json.hpp"
#include "../../../data/dynamic.hpp"

namespace scripting {
    extern lua::LuaState* state;
}

static int l_json_stringify(lua_State* L) {
    auto value = scripting::state->tovalue(1);

    if (auto mapptr = std::get_if<dynamic::Map_sptr>(&value)) {
        bool nice = lua_toboolean(L, 2);
        auto string = json::stringify(mapptr->get(), nice, "  ");
        lua_pushstring(L, string.c_str());
        return 1;
    } else {
        luaL_error(L, "table expected");
        return 0;
    }
}

static int l_json_parse(lua_State* L) {
    auto string = lua_tostring(L, 1);
    auto element = json::parse("<string>", string);
    auto value = std::make_unique<dynamic::Value>(
        dynamic::Map_sptr(element.release())
    );
    scripting::state->pushvalue(*value);
    return 1;
}

const luaL_Reg jsonlib [] = {
    {"stringify", lua_wrap_errors<l_json_stringify>},
    {"parse", lua_wrap_errors<l_json_parse>},
    {NULL, NULL}
};