//	seedの初期化入れてないけど、以下を確認してみた
	//	一度スクリプトを実行
	//	同じスクリプトを読み込みなおし
	//	同じスクリプトを実行
	//	randomの内容が同じになるか？
	//【結果】違う数値になった
	//seedはどこに保持されている？

#include <stdio.h>
#include <cstdlib>

#include "lua.hpp"

void output_stack(lua_State *lua)
{
	int top = lua_gettop(lua);
	printf("stack top=%d\n", top);

	for(int i=top; i>=1; i--)
	{
		int type = lua_type(lua, i);
		printf("[%d]type=(%s) / ", i, lua_typename(lua, type));
		printf("value=");

		switch(type)
		{
		case LUA_TBOOLEAN:
			printf("%s", (lua_toboolean(lua, i)==1)? "true":"false");
			break;
		case LUA_TNUMBER:
			printf("%f", lua_tonumber(lua, i));
			break;
		case LUA_TSTRING:
			printf("%s", lua_tostring(lua, i));
			break;
		default:
			break;
		}
		printf("\n");
	}
}


void update(lua_State *lua)
{
	lua_getglobal(lua, "update");
	if(!lua_pcall(lua, 0, 0, 0))
	{
	}
	printf("--------\n");
	lua_getglobal(lua, "update");
	if(!lua_pcall(lua, 0, 0, 0))
	{
	}
	printf("--------\n");
	lua_getglobal(lua, "update");
	if(!lua_pcall(lua, 0, 0, 0))
	{
	}
	printf("--------\n");
}


//	戻り値が複数持てるので、試しに読んでみる
int main()
{
	lua_State *lua = luaL_newstate();
	luaL_openlibs(lua);

	const char *filename = "random.lua";

	if( luaL_loadfile(lua, filename) || lua_pcall(lua, 0,0,0) )
	{
		printf("ファイル[%s]が開けませんでした\n", filename);
		printf("error[%s]\n", lua_tostring(lua, -1));
	}
	else
	{
		printf("====[seed2] 1回目\n");
		update(lua);

		lua_close(lua);

		lua = luaL_newstate();
		luaL_openlibs(lua);
		luaL_loadfile(lua, filename);
		lua_pcall(lua, 0,0,0);
		printf("====[seed2] 2回目\n");
		update(lua);
	}

	//プログラムが終了するなら、呼び出さずに終わっても良い？
	lua_close(lua);

	return 0;
}

