#include <stdio.h>
#include <cstdlib>
#include <algorithm>

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


int getXorshift(lua_State *lua)
{
	int min = luaL_checkinteger(lua, -2);
	int max = luaL_checkinteger(lua, -1);

/*	static uint32_t x = 123456789;
	static uint32_t y = 362436069;
	static uint32_t z = 521288629;
	static uint32_t w = 88675123;*/
	static uint32_t x = 1;
	static uint32_t y = 2;
	static uint32_t z = 3;
	static uint32_t w = 4;

	uint32_t t;
	t = x ^ (x<<11);
	x = y; y = z; z = w;
	w = (w ^ (w>>19)) ^ (t ^ (t>>8));

	uint32_t v = (w % (max+1 - min) + min);

	lua_pushnumber(lua, v);

	return 1;	//戻り値の数
}


int getXorshift32(lua_State *lua)
{
	int v1 = luaL_checkinteger(lua, -2);
	int v0 = luaL_checkinteger(lua, -1);

	int min, max;

	min = std::min(v0, v1);
	max = std::max(v0, v1);

	static uint32_t y = 2;

	y = y ^ (y << 13);
	y = y ^ (y >> 17);
	y = y ^ (y << 5);

	int d = abs(max+1-min);

	int v = (y % d) + min;
	lua_pushnumber(lua, v);

	return 1;	//戻り値の数
}



//	戻り値が複数持てるので、試しに読んでみる
int main()
{
	lua_State *lua = luaL_newstate();
	luaL_openlibs(lua);

	const char *filename = "xorshift.lua";

	lua_register(lua, "getXorshift", getXorshift);
	lua_register(lua, "getXorshift32", getXorshift32);

	if( luaL_loadfile(lua, filename) || lua_pcall(lua, 0,0,0) )
	{
		printf("ファイル[%s]が開けませんでした\n", filename);
		printf("error[%s]\n", lua_tostring(lua, -1));
	}
	else
	{
	/*	lua = luaL_newstate();
		luaL_openlibs(lua);
		luaL_loadfile(lua, filename);
		lua_pcall(lua, 0,0,0);
		printf("==== 2回目\n");
		update(lua);*/
	}

	//プログラムが終了するなら、呼び出さずに終わっても良い？
	lua_close(lua);

	return 0;
}

