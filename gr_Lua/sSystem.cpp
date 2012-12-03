//************************************************************************
// システム・ハード関連 2012.12.4
//************************************************************************
#include <rxduino.h>

#include "sExec.h"

extern char LuaFilename[];
extern volatile char ProgVer[];

//**************************************************
// setRun( ファイル名 )
// 次に実行するLuafileをLuaFilenameにセットします。
//**************************************************
int setRun( lua_State *LuaLinkP )
{
const char *str;
lua_Number	lnum = 0;

    int n = lua_gettop( LuaLinkP );
	if( n<1 ){
		LuaErrorMes( LuaLinkP, (char*)"sys.setrun", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	str = luaL_checklstring( LuaLinkP, 1, NULL );

	strcpy( (char*)LuaFilename, (char*)str );

	lua_settop(LuaLinkP, 0);			//スタックのクリア
	return( 0 );	//戻り値は無しですよ。
}

//**************************************************
// システムのバージョンを取得します
//**************************************************
int ver( lua_State *LuaLinkP )
{
	lua_settop(LuaLinkP, 0);			//スタックのクリア
	lua_pushstring( LuaLinkP, (char*)ProgVer );
	return( 1 );						//戻り値は1つですよ
}

//**************************************************
// 終了します
//**************************************************
int systemExit( lua_State *LuaLinkP )
{
	lua_settop(LuaLinkP, 0);			//スタックのクリア
	lua_pushstring( LuaLinkP, "Exit" );
	lua_error( LuaLinkP );
	return( 1 );						//戻り値は1つですよ
}