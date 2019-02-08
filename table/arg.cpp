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


//	lua内の関数に渡す引数にテーブルを指定する
void callFunctionWithTable(lua_State *lua)
{
	//	対象の関数を取得
	lua_getglobal(lua, "sample");

	//	テーブルの作成を開始
	lua_newtable(lua);
	lua_pushliteral(lua, "name");
	lua_pushstring(lua, "Hello");
	lua_pushliteral(lua, "count");
	lua_pushinteger(lua, 0);
	lua_rawset(lua, -5);		//	lua_rawsetでも同じ動作だが、こっちはイベントが発生するらしい
	//lua_settable(lua, -5);		//	lua_rawsetでも同じ動作だが、こっちはイベントが発生するらしい
	lua_settable(lua, -3);

	//	テーブル内のテーブルを作成開始
	lua_pushliteral(lua, "pos");	//	テーブルのリテラルを指定
	lua_newtable(lua);
	lua_pushliteral(lua, "x");
	lua_pushinteger(lua, 113);
	lua_rawset(lua, -3);		//	これを実行した時点でキーと値のペアがスタックから除かれてテーブルに追加される(lua_settableも同様)
	lua_pushliteral(lua, "y");
	lua_pushinteger(lua, 75);
	lua_rawset(lua, -3);

	lua_rawset(lua, -3);

	output_stack(lua);

	lua_pcall(lua, 1, 1, 0 );		//	lua_pcallは関数内でエラーが出たらスタックにエラーメッセージを返す
	//lua_call(lua, 1, 1);		//	lua_callは関数内でエラー出たらダンプを吐いて停止する

	output_stack(lua);

	if( lua_istable(lua, -1) )
	{
		lua_pushliteral(lua, "count");
		lua_gettable(lua, -2);

		int count = lua_tointeger(lua, -1);
		printf("C側で受け取ったcount=%d\n", count);
		lua_pop(lua, 1);

		output_stack(lua);
	}

	lua_pop(lua, 1);
}


//	lua内の関数に渡す引数にテーブルを指定する
void callFunctionWithTableArray(lua_State *lua)
{
	//	対象の関数を取得
	lua_getglobal(lua, "withArray");

	//	インデックスは勝手に割り振られないので設定する必要あり
		//	1から始まる連番にしないと、間があるものとして解釈されて意図しないサイズになる
		//	0はインデックスとして認識されない

	//	テーブルの作成を開始
	lua_newtable(lua);
	lua_pushinteger(lua,1);		//	インデックス指定
	lua_newtable(lua);
	lua_pushliteral(lua, "name");
	lua_pushstring(lua, "Hello");
	lua_rawset(lua, -3);

	lua_rawset(lua, -3);

	lua_pushinteger(lua,2);
	lua_newtable(lua);
	lua_pushliteral(lua, "name");
	lua_pushstring(lua, "Good");
	lua_rawset(lua, -3);

	lua_rawset(lua, -3);

	lua_pushinteger(lua,3);
	lua_newtable(lua);
	lua_pushliteral(lua, "name");
	lua_pushstring(lua, "World");
	lua_rawset(lua, -3);

	lua_rawset(lua, -3);

	printf("---- arrayセット完了\n");
	output_stack(lua);

	//lua_settable(lua, -2);
	//printf("---- 引数セット完了\n");
	//output_stack(lua);

	lua_pcall(lua, 1, 0, 0);

	output_stack(lua);
}



void callTest(lua_State *lua, int count)
{
	float x, y;
	x = 0;
	y = 0;

	lua_getglobal(lua, "update");

	//	テーブルの作成を開始
	lua_newtable(lua);

	lua_pushliteral(lua, "step");
	lua_pushinteger(lua, 0);
	lua_rawset(lua, -3);

	lua_pushliteral(lua, "count");
	lua_pushinteger(lua, count);
	lua_rawset(lua, -3);

	lua_pushliteral(lua, "pos");
	
	lua_newtable(lua);
	lua_pushliteral(lua, "x");
	lua_pushnumber(lua, x);

	//output_stack(lua);

	lua_rawset(lua, -3);

	//output_stack(lua);

	lua_pushliteral(lua, "y");
	lua_pushnumber(lua, y);
	lua_rawset(lua, -3);

	//output_stack(lua);

	lua_rawset(lua, -3);

	lua_pcall(lua, 1, 1, 0);
	//output_stack(lua);
	if( lua_istable(lua, -1) ) {
		float x, y;
		int step;

		lua_pushliteral(lua, "pos");
		lua_gettable(lua, -2);

		lua_pushliteral(lua, "x");
		lua_gettable(lua, -2);
		x = lua_tonumber(lua, -1);

	//output_stack(lua);
		lua_pop(lua, 1);

		lua_pushliteral(lua, "y");
		lua_gettable(lua, -2);
		y = lua_tonumber(lua, -1);

	//output_stack(lua);

		lua_pop(lua, 1);

		lua_pushliteral(lua, "step");
		lua_gettable(lua, -2);
		step = lua_tointeger(lua, -1);

	//	m_position.SetX(x);
	//	m_position.SetY(y);
	//	m_step = step;
		printf("(%d)[%1.3f,%1.3f]\n", count, x, y);
	}
}


#define LuaTableSetFloatArray(lua, literal, array, size) \
	{											\
		lua_pushliteral(lua, literal);			\
		lua_newtable(lua);						\
		for(int i=1; i<=size; i++){				\
			lua_pushinteger(lua, i);			\
			lua_pushnumber(lua, array[i - 1]);	\
			lua_rawset(lua, -3);				\
		}										\
		lua_rawset(lua, -3);					\
	}

#define LuaTableGetFloatArray(lua, literal, array, size) \
	{											\
		lua_pushliteral(lua, literal);			\
		lua_gettable(lua, -2);					\
		for(int i=1; i<=size; i++){				\
			lua_pushinteger(lua, i);			\
			lua_gettable(lua, -2);				\
			array[i-1] = lua_tonumber(lua, -1);	\
			lua_pop(lua,1);						\
		}										\
	}


void macroTest(lua_State *lua)
{
	float work[4];

	work[0] = 1;
	work[1] = 2;
	work[2] = 3;
	work[3] = 4;

	lua_getglobal(lua, "macroTest");
	lua_newtable(lua);
	LuaTableSetFloatArray(lua, "work", work, 4);

	output_stack(lua);

	if( !lua_pcall(lua, 1,1,0) )
	{
		float result[4];
		output_stack(lua);

		LuaTableGetFloatArray(lua, "work", result, 4);
		for(int i=0; i<4; i++)
		{
			printf("result[%d]=%1.3f\n", i, result[i]);
		}

		lua_pop(lua, 1);
	}
}


int main()
{
	lua_State *lua = luaL_newstate();

	luaL_openlibs(lua);

	const char *filename = "arg.lua";
	if( luaL_loadfile(lua, filename) || lua_pcall(lua, 0,0,0) )
	{
		printf("ファイル[%s]が開けませんでした\n", filename);
		printf("error[%s]\n", lua_tostring(lua, -1));
	}
	else
	{
		/*callFunctionWithTable(lua);
		printf("\n----------------\n");
		callFunctionWithTableArray(lua);
		printf("\n----------------\n");
		for(int i=0; i<10; i++)
		{
			callTest(lua, i*10);
		}
		printf("\n----------------\n");*/
		macroTest(lua);
		printf("\n----------------\n");
	}

	lua_close(lua);

	return 0;
}