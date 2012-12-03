//************************************************************************
// I2C関連 2012.12.4
//************************************************************************
#include <rxduino.h>
#include <Wire.h>

#include "sExec.h"

//**************************************************
// I2C送信開始準備: Wire.beginT
//  Wire.beginT(address)
//	address: ターゲットデバイスのアドレス
//    0～0x7Fまでの純粋なアドレスを与えること
//**************************************************
int WireBeginTran( lua_State *LuaLinkP )
{
    int n = lua_gettop( LuaLinkP );
	if( n<1 ){
		LuaErrorMes( LuaLinkP, (char*)"Wire.beginT", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	int add = lua_tonumber( LuaLinkP, 1 );
	Wire.beginTransmission( add );

	lua_settop(LuaLinkP, 0);
	return( 0 );		//戻り値は無しですよ。
}

//**************************************************
// 送信する1byteのセット: Wire.writeB
//  Wire.writeB(byte)
//	byte: 送信したいデータ
//
//  戻り値
//		成功: 1
//		失敗: 0
//**************************************************
int WireWriteByte( lua_State *LuaLinkP )
{
    int n = lua_gettop( LuaLinkP );
	if( n<1 ){
		LuaErrorMes( LuaLinkP, (char*)"Wire.writeB", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	unsigned char dat = lua_tonumber( LuaLinkP, 1 );
	int ret = Wire.write( dat );

	lua_settop(LuaLinkP, 0);			//スタックのクリア
	lua_pushnumber( LuaLinkP, ret );

	return( 1 );		//戻り値は1つですよ。
}

//**************************************************
// 送信するデータのセット: Wire.writeI
//  Wire.writeI(int)
//	int: 送信したいデータ
//
//  戻り値
//		成功: 送信したバイト数
//		失敗: 0
//**************************************************
int WireWriteInt( lua_State *LuaLinkP )
{
	int n = lua_gettop( LuaLinkP );
	if( n<1 ){
		LuaErrorMes( LuaLinkP, (char*)"Wire.writeI", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	int dat = lua_tonumber( LuaLinkP, 1 );
	int ret = Wire.write( dat );

	lua_settop(LuaLinkP, 0);			//スタックのクリア
	lua_pushnumber( LuaLinkP, ret );

	return( 1 );		//戻り値は1つですよ。
}

//**************************************************
// 送信する文字列のセット: Wire.writeT
//  Wire.writeT(text)
//	text: 文字列
//
//  戻り値
//		成功: 送信したバイト数
//		失敗: 0
//**************************************************
int WireWriteText( lua_State *LuaLinkP )
{
char *str;

	int n = lua_gettop( LuaLinkP );
	if( n<1 ){
		LuaErrorMes( LuaLinkP, (char*)"Wire.writeT", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	str = (char*)luaL_checklstring( LuaLinkP, 1, NULL );

	int ret = Wire.write( str );

	lua_settop(LuaLinkP, 0);			//スタックのクリア
	lua_pushnumber( LuaLinkP, ret );

	return( 1 );		//戻り値は1つですよ。
}

//**************************************************
// 送信するデータブロックのセット: Wire.writeA
//  Wire.writeA(array, length)
//	array: データ配列
//  length: データサイズ
//
//  戻り値
//		成功: 送信したバイト数
//		失敗: 0
//**************************************************
int WireWriteArray( lua_State *LuaLinkP )
{
unsigned char *str;

	int n = lua_gettop( LuaLinkP );
	if( n<2 ){
		LuaErrorMes( LuaLinkP, (char*)"Wire.writeA", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	str = (unsigned char*)luaL_checklstring( LuaLinkP, 1, NULL );
	int len = lua_tonumber( LuaLinkP, 2 );

	int ret = Wire.write( str, len );

	lua_settop(LuaLinkP, 0);			//スタックのクリア
	lua_pushnumber( LuaLinkP, ret );

	return( 1 );		//戻り値は1つですよ。
}

//**************************************************
// I2Cに送信する: Wire.endT
//  Wire.endT()
//
//	戻り値:
//		0: 成功
//		1: 送信バッファ溢れ
//		2: スレーブアドレス送信時にNACKを受信
//		3: データ送信時にNACKを受信
//		4: その他のエラー
//**************************************************
int WireEndTran( lua_State *LuaLinkP )
{
	int ret = Wire.endTransmission();

	lua_settop(LuaLinkP, 0);			//スタックのクリア
	lua_pushnumber( LuaLinkP, ret );

	return( 1 );		//戻り値は1つですよ。
}

//**************************************************
// SDA,SCLピンの割り当て任意のピンに変更する: Wire.SdaScl
//  Wire.SdaScl(sda, scl)
//  sda: データ端子ピン番号
//  scl: クロック端子ピン番号
//**************************************************
int WireAssignSdaScl( lua_State *LuaLinkP )
{
	int n = lua_gettop( LuaLinkP );
	if( n<2 ){
		LuaErrorMes( LuaLinkP, (char*)"Wire.SdaScl", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	int sda = lua_tonumber( LuaLinkP, 1 );
	int scl = lua_tonumber( LuaLinkP, 2 );

	Wire.assignSdaScl( sda, scl );

	lua_settop(LuaLinkP, 0);
	return( 0 );		//戻り値は無しですよ。
}

//**************************************************
// I2Cマスターとして初期化する: Wire.master
//  Wire.master()
//**************************************************
int WireMaster( lua_State *LuaLinkP )
{
	Wire.begin();

	lua_settop(LuaLinkP, 0);
	return( 0 );		//戻り値は無しですよ。
}
