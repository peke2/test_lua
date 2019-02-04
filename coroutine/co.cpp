#include <stdio.h>
#include "lua.hpp"

void output_stack(lua_State *lua)
{
/*
#define LUA_TNIL		0
#define LUA_TBOOLEAN		1
#define LUA_TLIGHTUSERDATA	2
#define LUA_TNUMBER		3
#define LUA_TSTRING		4
#define LUA_TTABLE		5
#define LUA_TFUNCTION		6
#define LUA_TUSERDATA		7
#define LUA_TTHREAD		8
*/

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


int kfunc(lua_State *L, int status, lua_KContext ctx)
{
	printf("called\n");
}

/*int my_sub(lua_State *lua)
{
	printf("luaからの呼び出し");
	return lua_yield(lua, );
}*/


int main()
{
	lua_State *lua = luaL_newstate();

	luaL_openlibs(lua);

	const char *filename = "co_forc.lua";

	if( luaL_loadfile(lua, filename) || lua_pcall(lua, 0,0,0) )
	{
		printf("ファイル[%s]が開けませんでした\n", filename);
		printf("error[%s]\n", lua_tostring(lua, -1));
	}
	else
	{
		lua_State *lua1 = lua_newthread(lua);
		luaL_openlibs(lua1);
		//lua_register(lua1, "sub", my_sub);
		lua_getglobal(lua1, "flow");

		bool result;
		result = lua_resume(lua1, 0, 0);
		printf("結果[%d] 戻り値=[%s]\n",result, lua_tostring(lua1, lua_gettop(lua1)));
		result = lua_resume(lua1, 0, 0);
		printf("結果[%d] 戻り値=[%s]\n",result, lua_tostring(lua1, lua_gettop(lua1)));
		result = lua_resume(lua1, 0, 0);
		printf("結果[%d] 戻り値=[%s]\n",result, lua_tostring(lua1, lua_gettop(lua1)));
		//	コルーチンが動いていなければ関数の戻り値は「false」 → luaスクリプト内と挙動が違う？
		result = lua_resume(lua1, 0, 0);
		printf("結果[%d] 戻り値=[%s]\n",result, lua_tostring(lua1, lua_gettop(lua1)));
	}

	//プログラムが終了するなら、呼び出さずに終わっても良い？
	lua_close(lua);

	return 0;
}
