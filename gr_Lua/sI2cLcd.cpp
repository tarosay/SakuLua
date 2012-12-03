//************************************************************************
// I2C 液晶関連 2012.12.4
//************************************************************************
#include "sExec.h"
#include "../i2clcd.h"

//**************************************************
// 液晶表示: Lcd.write
//  Lcd.write(string[,pos])
//	string: 文字
//  pos: 0:上段, 1:下段
//**************************************************
int i2clcdWriteLine( lua_State *LuaLinkP )
{
const char *str;

    int n = lua_gettop( LuaLinkP );
	if( n<1 ){
		LuaErrorMes( LuaLinkP, (char*)"Lcd.write", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	str = luaL_checklstring( LuaLinkP, 1, NULL );
	int pos = 0;
	if( n>1 ){
		pos = lua_tonumber( LuaLinkP, 2 );
	}

	WriteLine( str, pos );

	lua_settop(LuaLinkP, 0);			//スタックのクリア
	return( 0 );	//戻り値は無しですよ。
}
