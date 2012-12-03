//************************************************************************
// SakuLuaの呼び出し実行モジュールプログラム 2012.12.4 v1.06
//************************************************************************
#include <rxduino.h>
#include <string.h>

volatile char	ProgVer[] = {"1.06"};

#include "../gr_sakura_sdmmc/sdmmc.h"
#include "sExec.h"
#include "sSystem.h"
#include "sAdk.h"
#include "sI2cLcd.h"
#include "sSerial.h"
#include "sWire.h"
#include "sRTC.h"
#include "../i2clcd.h"

lua_State	*LuaLinkP;

//実行するLuaファイル名が格納される。
extern char LuaStartFileName[];
extern char LuaFilename[];
extern char ExeFilename[];
extern SDMMC MicroSD;
extern File SdFile;

static const luaL_Reg RTCTbl[] = {
 	{"begin", adkRTCbegin },
	{"set", adkRTCsetDateTime },
 	{"get", adkRTCgetDateTime },
	{NULL,NULL}
};

static const luaL_Reg WireTbl[] = {
	{"beginT", WireBeginTran },
	{"writeB", WireWriteByte },
	{"writeI", WireWriteInt },
	{"writeT", WireWriteText },
	{"writeA", WireWriteArray },
	{"endT", WireEndTran },
	{"SdaScl", WireAssignSdaScl },
	{"master", WireMaster },
	{NULL,NULL}
};

static const luaL_Reg I2CLcdTbl[] = {
	{"write", i2clcdWriteLine },
	{NULL,NULL}
};

static const luaL_Reg SerialTbl[] = {
	{"print", serialPrint },
	{"println", serialPrintln },
	{"XBee", serialXBee },
	{"USB", serialUSB },
	{"setDef", serialSetDefault },
	{NULL,NULL}
};

static const luaL_Reg SystemTbl[] = {
	{"setrun", setRun },
	{"ver", ver },
	{"exit", systemExit },
	{NULL,NULL}
};

//**************************************************
//  Lua言語を実行します
//**************************************************
bool LuaRun( void )
{
char *str;
bool LuaStartFlg = true;

	//Lua Open
	LuaLinkP = lua_open();
	luaL_openlibs( LuaLinkP );

	//基本コマンド
	lua_register( LuaLinkP, "digitalWrite", adkDigitalWrite );
	lua_register( LuaLinkP, "analogWrite", adkAnalogWrite );
	lua_register( LuaLinkP, "digitalRead", adkDigitalRead );
	lua_register( LuaLinkP, "analogRead", adkAnalogRead );
	lua_register( LuaLinkP, "analogWriteDAC", adkAnalogWriteDAC );
	lua_register( LuaLinkP, "analogWriteFrequency", adkAnalogWriteFrequency );
	lua_register( LuaLinkP, "pulseIn", adkPulseIn );
	lua_register( LuaLinkP, "pinMode", adkPinMode );
	lua_register( LuaLinkP, "analogReference", adkAnalogReference );
	lua_register( LuaLinkP, "delay", adkDelay );

	//ライブラリコマンド
	luaL_register( LuaLinkP, "sys", SystemTbl );
	luaL_register( LuaLinkP, "RTC", RTCTbl );
	luaL_register( LuaLinkP, "Lcd", I2CLcdTbl );
	luaL_register( LuaLinkP, "Serial", SerialTbl );
	luaL_register( LuaLinkP, "Wire", WireTbl );

	strcpy( ExeFilename, (char*)LuaFilename );		//実行するLuaファイルをexeLuafile[]に入れる。
	strcpy( (char*)LuaFilename, LuaStartFileName );	//とりあえず、LuaFilename[]をLuaStartFileName[]に初期化する。

	//Luaファイルを実行
	//実行前にファイルをオープンします
	SdFile = MicroSD.open( (const char*)ExeFilename, FILE_READ );

	int err = luaL_loadfile( LuaLinkP, ExeFilename );

	//char az[16];
	//sprintf( az, "err=%d", err );
	//Serial.println( az );
	//WriteLine( az, 0 );
	
	//読み込みファイルを閉じます
	SdFile.close();

	if( err==LUA_ERRSYNTAX ){
		//Serial.println("Syntax Error: ");
		str = (char*)lua_tostring( LuaLinkP, -1);
		LuaStartFlg = false;
	}
	else if( err==LUA_ERRMEM ){
		//Serial.println("Memory Error Under Compile: ");
		str = (char*)lua_tostring( LuaLinkP, -1);
		LuaStartFlg = false;
	}
	else{
		err = lua_pcall( LuaLinkP, 0, LUA_MULTRET, 0 );
		if( err==LUA_ERRRUN ){
			//Serial.println("Run Error: ");
			str = (char*)lua_tostring( LuaLinkP, -1);
			LuaStartFlg = false;
		}
		else if( err==LUA_ERRMEM ){
			//Serial.println("Memory Secured Error: ");
			str = (char*)lua_tostring( LuaLinkP, -1);
			LuaStartFlg = false;
		}
		else if( err==LUA_ERRERR ){
			//Serial.println("Handler Function Error: ");
			str = (char*)lua_tostring( LuaLinkP, -1);
			LuaStartFlg = false;
		}
	}

	if( LuaStartFlg==false ){
		Serial.println( str );
		WriteLine( str, 1 );
	}

	//Luaファイルを閉じる
	lua_close( LuaLinkP );

	return LuaStartFlg;
}

//**************************************************
//  エラーメッセージ
//**************************************************
void LuaErrorMes( lua_State *LuaLinkP, char* mes, int type )
{
char mess[128];

	strcpy( mess, ExeFilename );
	strcat( mess, ":" );
	strcat( mess, mes );
	//strcpy( mess, mes );
	if( type==0 ){
		strcat( mess, "() : Not Enough Arguments" );
	}
	lua_settop(LuaLinkP, 0);
	lua_pushstring( LuaLinkP, mess );
	lua_error( LuaLinkP );
}