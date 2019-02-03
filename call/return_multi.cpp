#include <stdio.h>
#include <cstdlib>

#include "lua.hpp"


//	戻り値が複数持てるので、試しに読んでみる
int main()
{
	lua_State *lua = luaL_newstate();

	luaL_openlibs(lua);

	const char *filename = "sample.lua";

	if( luaL_loadfile(lua, filename) || lua_pcall(lua, 0,0,0) )
	{
		printf("ファイル[%s]が開けませんでした\n", filename);
		printf("error[%s]\n", lua_tostring(lua, -1));
	}
	else
	{
		lua_getglobal(lua, "calc");
		lua_pushnumber(lua, 1.23f);
		lua_pushnumber(lua, 3.45f);
		lua_pushnumber(lua, 5.6f);
		if(!lua_pcall(lua, 3, 2, 0))		//	引数:3 戻り値:2
		{
			float v0, v1;
			//	戻り値はスタックに積まれた順番になる
			//	lua
			//		return a, b
			//	C
			//		-2, -1
			v1 = lua_tonumber(lua, -1);
			v0 = lua_tonumber(lua, -2);
			printf("add = %f\n", v0);
			printf("mul = %f\n", v1);
		}
	}

	//プログラムが終了するなら、呼び出さずに終わっても良い？
	lua_close(lua);

	return 0;
}