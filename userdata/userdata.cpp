#include <stdio.h>
#include <cstdlib>

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

	int value;

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

class UserData
{
	public:
		int value;
		char text[64];

	public:
		UserData()
		{
			value = 0;
			text[0] = '\n';
		}
		~UserData()
		{
		}
};


int callback(lua_State *lua)
{
	output_stack(lua);

	if( lua_isuserdata(lua, -1) )
	{
		UserData *ud = (UserData *)lua_touserdata(lua, -1);
		printf("value=%d, text=%s\n", ud->value, ud->text);
	}

	return 0;
}


int main()
{
	lua_State *lua = luaL_newstate();

	luaL_openlibs(lua);

	const char *filename = "proc.lua";
	if( luaL_loadfile(lua, filename) || lua_pcall(lua, 0,0,0) )
	{
		printf("ファイル[%s]が開けませんでした\n", filename);
		printf("error[%s]\n", lua_tostring(lua, -1));
	}
	else
	{
		UserData userData;
		userData.value = 12345;
		sprintf(userData.text, "Hello");

		lua_register(lua, "Callback", callback);

		lua_getglobal(lua, "control");
		lua_pushlightuserdata(lua, &userData);
		lua_call(lua, 1, 0);

	}

	lua_close(lua);

	return 0;
}