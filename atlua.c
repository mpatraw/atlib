
#include <stdio.h>

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

static int print(lua_State *L)
{
    printf("Hello, world\n");
    return 0;
}

static const luaL_Reg atlib[] =
{
    {"print", print},
    {NULL, NULL},
};

LUALIB_API int luaopen_at(lua_State *L)
{
    lua_newtable(L);
    luaL_register(L, NULL, atlib);
    return 1;
}
