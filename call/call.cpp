#include <stdio.h>
#include <cstdlib>

#include "lua.hpp"
//#include "lua.h"
//#include "lualib.h"
//#include "lauxlib.h"


int main()
{
	lua_State *lua = luaL_newstate();

	printf("Hello Lua\n");

	luaL_openlibs(lua);

	const char *filename = "sample.lua";
	//const char *filename = "sample2.lua";

	if( luaL_loadfile(lua, filename) || lua_pcall(lua, 0,0,0) )
	{
		printf("ファイル[%s]が開けませんでした\n", filename);
		printf("error[%s]\n", lua_tostring(lua, -1));
	}
	else
	{
		lua_getglobal(lua, "Value");
		lua_getglobal(lua, "Name");
		if( !lua_isnumber(lua, -2) || !lua_isstring(lua, -1) )
		{
			printf("値が正しく取得できません\n");
		}
		else
		{
			printf("Name=[%s]\n", lua_tostring(lua,-1));
			printf("Value=[%d]\n", lua_tointeger(lua,-2));
		}

		//内部では実数扱い？
			//小数点以下の数値が無ければ「integer」？
		//戻り値は複数持てる？

		int a = 3;
		int b = 67;
		lua_getglobal(lua, "mul");
		lua_pushnumber(lua, a);
		lua_pushnumber(lua, b);
		if( lua_pcall(lua, 2, 1, 0) )	//引数:2 戻り値:1 「0」は何？
		{
			printf("関数の呼び出し失敗\n");
			printf("error[%s]\n", lua_tostring(lua, -1));
		}
		else
		{
			if( lua_isnumber(lua, -1) )
			{
				printf("%d*%d=%d\n", a, b, lua_tointeger(lua,-1));
				lua_pop(lua,1);	//popしないとどうなる？ スタックオーバーフロー？ 関数呼び出しとスタックのpopは対になる？
			}
		}

	}

	//プログラムが終了するなら、呼び出さずに終わっても良い？
	lua_close(lua);

	return 0;
}