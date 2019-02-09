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


int fromLua(lua_State *lua)
{
	output_stack(lua);

	//	戻り値は3つ、対象のテーブルは引数の先頭
	//	arg3	<TOP
	//	arg2
	//	arg1
	//	目的の「arg1」を取得するため、スタックの先頭2つを取り除く
	lua_pop(lua, 2);

	//	テーブルの中のそれぞれのキーの値を取得
	float x , y;
	lua_pushliteral(lua, "x");
	lua_gettable(lua, -2);
	x = lua_tonumber(lua, -1);
	lua_pop(lua, 1);
	lua_pushliteral(lua, "y");
	lua_gettable(lua, -2);
	y = lua_tonumber(lua, -1);
	lua_pop(lua, 1);

	printf("[%1.3f,%1.3f]\n", x, y);

	return 0;
}

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
		lua_register(lua, "fromLua", fromLua);
		lua_getglobal(lua, "callWithTable");
		if(!lua_pcall(lua, 0, 0, 0))
		{
		}
	}

	//プログラムが終了するなら、呼び出さずに終わっても良い？
	lua_close(lua);

	return 0;
}