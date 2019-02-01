#include <stdio.h>
#include <cstdlib>

#include "lua.hpp"

int l_add(lua_State *lua)
{
	int a = luaL_checkinteger(lua, -2);
	int b = luaL_checkinteger(lua, -1);

	int result = a + b;

	printf("luaからの呼び出し\n");

	lua_pushnumber(lua, result);

	return 1;	//戻り値の数h
}


int main()
{
	lua_State *lua = luaL_newstate();

	luaL_openlibs(lua);

	lua_register(lua, "c_add", l_add);	//lua内で使用する名前は適当

	const char *filename = "from_lua.lua";
	if( luaL_loadfile(lua, filename) || lua_pcall(lua, 0,0,0) )
	{
		printf("ファイル[%s]が開けませんでした\n", filename);
		printf("error[%s]\n", lua_tostring(lua, -1));
	}

	lua_close(lua);

	return 0;
}