
#include <stdio.h>

#include <lua5.1/lauxlib.h>
#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>

#include "at/random.h"

static struct at_xorshift x;

static int seed(lua_State *L)
{
        at_xorshift_seed(&x, (uint32_t)luaL_checkinteger(L, 1));
        return 0;
}

static int rand(lua_State *L)
{
        lua_pushnumber(L, (lua_Number)at_xorshift_get_next(&x));
        return 1;
}

static const luaL_Reg atlib[] =
{
        {"seed", seed},
        {"rand", rand},
        {NULL, NULL},
};

LUALIB_API int luaopen_at(lua_State *L)
{
        lua_newtable(L);
        luaL_register(L, NULL, atlib);
        return 1;
}
