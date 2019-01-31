#include <stdio.h>
#include <cstdlib>

#include "lua.hpp"


int main()
{
	lua_State *lua = luaL_newstate();

	printf("Hello Lua\n");

	return 0;
}