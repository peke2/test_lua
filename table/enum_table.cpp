#include <stdio.h>
#include <cstdlib>

#include "lua.hpp"


void output_stack(lua_State *lua)
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


#define KEY_INDEX (-2)
#define VALUE_INDEX (-1)


void enumerateTableRecur(lua_State *lua, int depth)
{
	lua_pushnil(lua);	//	最初の要素
	while(lua_next(lua, -2) != 0)
	{
		int key_type = lua_type(lua, KEY_INDEX);
		int value_type = lua_type(lua, VALUE_INDEX);

		//	lua_tostring() はスタック上のデータを変更するので注意！！！
		//printf("%*s%s[type=%s]\n", depth*2, " ", lua_tostring(lua, KEY_INDEX), lua_typename(lua, key_type));

		printf("%*s", depth*2, " ");
		if( lua_isnumber(lua, KEY_INDEX) )
		{
			printf("[%d]=", lua_tointeger(lua, KEY_INDEX));
		}
		else if( lua_isstring(lua, KEY_INDEX) )
		{
			printf("[%s]=", lua_tostring(lua, KEY_INDEX));
		}
		else
		{
			printf("[unknown]=");
		}

		if( lua_isnumber(lua, VALUE_INDEX) )
		{
			printf("%d", lua_tointeger(lua, VALUE_INDEX));
		}
		else if( lua_isstring(lua, VALUE_INDEX) )
		{
			printf("%s", lua_tostring(lua, VALUE_INDEX));
		}
		else if( lua_istable(lua, VALUE_INDEX) )
		{
			printf("<table>");
		}
		else
		{
			printf("(other)");
		}

		printf("\n");


		//printf("%*s%s[type=%s]\n", depth*2, " ", lua_tostring(lua, KEY_INDEX), lua_typename(lua, key_type));
//		output_stack(lua);

		//	テーブルならば階層を下げて続ける
		if( value_type == LUA_TTABLE )
		{
			enumerateTableRecur(lua, depth+1);
//			printf("--------[back]\n");
//			output_stack(lua);
		}

		lua_pop(lua, 1);
//		printf("--------[次の要素へ]\n");
//		output_stack(lua);
	}
//	printf("--------[階層終了]\n");
//	output_stack(lua);
}

void enumerateTable(lua_State *lua, const char *name)
{
	lua_getglobal(lua, name);
	enumerateTableRecur(lua, 0);
}



int main()
{
	lua_State *lua = luaL_newstate();

	luaL_openlibs(lua);

	const char *filename = "info.lua";
	if( luaL_loadfile(lua, filename) || lua_pcall(lua, 0,0,0) )
	{
		printf("ファイル[%s]が開けませんでした\n", filename);
		printf("error[%s]\n", lua_tostring(lua, -1));
	}
	else
	{
		enumerateTable(lua, "stages");
#if 0
		lua_getglobal(lua, "stages");
		lua_pushnil(lua);
		lua_next(lua, -2);
		output_stack(lua);

		lua_pushnil(lua);
		lua_next(lua, -2);
		output_stack(lua);

		lua_pushnil(lua);
		lua_next(lua, -2);
		output_stack(lua);
		lua_pop(lua, 1);

		lua_next(lua, -2);
		output_stack(lua);
		lua_pushnil(lua);

		lua_next(lua, -2);
		output_stack(lua);
		lua_pop(lua, 1);

		lua_next(lua, -2);
		output_stack(lua);
		lua_pop(lua, 1);

		lua_next(lua, -2);
		output_stack(lua);
		lua_pop(lua, 1);
#endif
		/*
		lua_getglobal(lua, "stages");
		lua_pushnil(lua);
		while(lua_next(lua, -2)!=0)
		{
			output_stack(lua);
			lua_pop(lua,1);			//	次のイテレーションのため、キーを残して数値のみ除去する
			printf("--------\n");
		}
		*/

#if 0
		lua_getglobal(lua, "stages");
		lua_pushnil(lua);
		lua_next(lua, -2);
		output_stack(lua);
		lua_pop(lua,1);			//	次のイテレーションのため、キーを残して数値のみ除去する
		printf("--------\n");

		lua_next(lua, -2);
		output_stack(lua);
		lua_pop(lua,1);
		printf("--------\n");

		lua_next(lua, -2);
		output_stack(lua);
		lua_pop(lua,1);
		printf("--------\n");

		if( lua_next(lua, -2) == 0 )
		{
			printf("列挙終了\n");
		}
#endif

	#if 0
		//	以下を実行するとスタック上で「number」から「string」に変更されていることが分かる
		lua_pushnumber(lua, 123);
		output_stack(lua);
		lua_tostring(lua, -1);
		output_stack(lua);

		//	stack top=1
		//	[1]type=(number) / value=123.000000
		//	stack top=1
		//	[1]type=(string) / value=123.0
	#endif
	}

	lua_close(lua);

	return 0;
}