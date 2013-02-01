//************************************************************************
// RTC関連 2013.1.29
//************************************************************************
#include <rxduino.h>
#include <rtc.h>

#include "sExec.h"

//**************************************************
// RTCの時計をセットする: RTC.set
//	RTC.set( year, mon, day, hour, min, sec)
//	year: 西暦
//	mon: 月
//	day: 日
//	hour: 時
//	min: 分
//	sec: 秒
//**************************************************
int adkRTCsetDateTime( lua_State *LuaLinkP )
{
    int n = lua_gettop( LuaLinkP );
	if( n<6 ){
		LuaErrorMes( LuaLinkP, (char*)"RTC.set", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	int year = lua_tonumber( LuaLinkP, 1 );
	int mon = (unsigned long)lua_tonumber( LuaLinkP, 2 );
	int day = (unsigned long)lua_tonumber( LuaLinkP, 3 );
	int hour = (unsigned long)lua_tonumber( LuaLinkP, 4 );
	int min = (unsigned long)lua_tonumber( LuaLinkP, 5 );
	int sec = (unsigned long)lua_tonumber( LuaLinkP, 6 );

	RTC::setDateTime( year, mon, day, hour, min, sec );
	
	lua_settop(LuaLinkP, 0);
	return( 0 );		//戻り値は無しですよ。
}

//**************************************************
// RTCの時計を取得する: RTC.get
//	RTC.get()
//
// 西暦, 月, 日, 時, 分, 秒
//**************************************************
int adkRTCgetDateTime( lua_State *LuaLinkP )
{
int year;
int mon;
int day;
int hour;
int min;
int sec;

	RTC::getDateTime( year, mon, day, hour, min, sec );

	lua_settop(LuaLinkP, 0);			//スタックのクリア

	lua_pushnumber( LuaLinkP, year );
	lua_pushnumber( LuaLinkP, mon );
	lua_pushnumber( LuaLinkP, day );
	lua_pushnumber( LuaLinkP, hour );
	lua_pushnumber( LuaLinkP, min );
	lua_pushnumber( LuaLinkP, sec );

	return( 6 );		//戻り値は6つですよ。
}
