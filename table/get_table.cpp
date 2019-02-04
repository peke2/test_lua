#include <stdio.h>
#include <cstdlib>

#include "lua.hpp"


void output(lua_State *lua)
{
	//スタックに積まれたパラメータ数を取得
	//スタックの先頭(最初に積まれた要素)からアクセス
	//タイプによって取得結果を表示
/*	int type = lua_getglobal(lua, name);

	printf("type=[%s]\n", lua_typename(lua, type));

	const char *type_name = "none";
	switch(type)
	{
	case LUA_TBOOLEAN:
		type_name = "boolean";
		break;

	case LUA_TNUMBER:
		type_name = "number";
		break;

	case LUA_TTABLE:
		type_name = "table";
		break;
	}

	printf("type[%d]=[%s]\n", type, type_name);*/
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

	//	int num = lua_tointeger(lua, i);
	//	printf("index[%d]=%d\n", i, num);
	}
}



int main()
{
	lua_State *lua = luaL_newstate();

	luaL_openlibs(lua);

	const char *filename = "table.lua";
	if( luaL_loadfile(lua, filename) || lua_pcall(lua, 0,0,0) )
	{
		printf("ファイル[%s]が開けませんでした\n", filename);
		printf("error[%s]\n", lua_tostring(lua, -1));
	}
	else
	{
	/*	lua_pushinteger(lua, 123);
		lua_pushstring(lua, "Hello");
		output(lua);
		*/

		lua_getglobal(lua, "Table");
		lua_pushinteger(lua, 1);
		lua_gettable(lua, -2);
		output(lua);
		printf("table=%s\n", lua_tostring(lua, -1));

		//[2]type=(string) / value=Hello
		//[1]type=(table) / value=

		lua_pop(lua, 1);	//	戻り値をpopしないと[2]の内容が残ったままになる
		//output(lua);

		printf("\n");

		lua_getglobal(lua, "Stage");
		lua_pushliteral(lua, "stages");
		output(lua);
		//	スタックの内容を見ると、テーブル参照のために指定した引数はpopされて、戻り値がpushされてくる
		//stack top=3
		//[3]type=(string) / value=stages
		//[2]type=(table) / value=
		//[1]type=(table) / value=

		lua_gettable(lua, -2);
		output(lua);
		//stack top=3
		//[3]type=(table) / value=
		//[2]type=(table) / value=
		//[1]type=(table) / value=


		lua_pushinteger(lua, 3);	//	戻り値の「テーブル」がスタックに残っているので、インデックスを積んで参照可能
		lua_gettable(lua, -2);
		output(lua);

		lua_pushliteral(lua, "name");
		lua_gettable(lua, -2);
		output(lua);

		printf("--------\n");
		lua_getglobal(lua, "Stage");
		lua_pushnil(lua);
		lua_next(lua, -2);
		output(lua);

	}

	lua_close(lua);

	return 0;
}