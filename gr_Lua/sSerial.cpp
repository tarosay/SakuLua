//************************************************************************
// シリアル通信関連 2013.1.29
//************************************************************************
#include <rxduino.h>

#include "sExec.h"

//**************************************************
// XBee通信セット: Serial.XBee
//  Serial.XBee([baudrate])
//	baudrate: ボーレート
//   省略時は9600bpsです
//**************************************************
int serialXBee( lua_State *LuaLinkP )
{
int br = 9600;

    int n = lua_gettop( LuaLinkP );
	if( n>=1 ){
		br = lua_tonumber( LuaLinkP, 1 );
    }

    Serial.begin( br, SCI_SCI2B );	// SCI_SCI2B       ピン24(TxD)、ピン26(RxD)を使う。XBeeアクセスに使用
    pinMode(PIN_P51, OUTPUT);
    digitalWrite(PIN_P51, 0);		// XBeeをリセット
    delay(10);
    digitalWrite(PIN_P51, 1);		// XBeeをリセット解除
    delay(10);

	lua_settop(LuaLinkP, 0);
	return( 0 );		//戻り値は無しですよ。
}

//**************************************************
// USB通信初期化: Serial.USB
//  Serial.USB([baudrate])
//	baudrate: ボーレート
//   省略時は9600bpsです
//**************************************************
int serialUSB( lua_State *LuaLinkP )
{
int br = 9600;

    int n = lua_gettop( LuaLinkP );
	if( n>=1 ){
		br = lua_tonumber( LuaLinkP, 1 );
    }

	Serial.begin( br );

	lua_settop(LuaLinkP, 0);
	return( 0 );		//戻り値は無しですよ。
}

//**************************************************
// 標準出力に対応させます: Serial.setDef
//  Serial.setDef()
//**************************************************
int serialSetDefault( lua_State *LuaLinkP )
{
	Serial.setDefault();				//現在のシリアルポートを標準出力とするprintfでも出力する
	setvbuf(stdout,NULL,_IONBF,0);

	lua_settop(LuaLinkP, 0);
	return( 0 );		//戻り値は無しですよ。
}

//**************************************************
// シリアルに出力します
//**************************************************
int serialp(int sw, lua_State *LuaLinkP )
{
const char *str;

    int n = lua_gettop( LuaLinkP );

	if( n>=1 ){
		str = luaL_checklstring( LuaLinkP, 1, NULL );
		if( sw==0 ){
			Serial.print( str );
		}
		else{
			Serial.println( str );
		}
    }

	lua_settop(LuaLinkP, 0);
	return( 0 );		//戻り値は無しですよ。
}

//**************************************************
// シリアルに出力します: Serial.print
//  Serial.print([str])
//  str: 文字列
//    省略時は何も出力しません
//**************************************************
int serialPrint( lua_State *LuaLinkP )
{
	return serialp( 0, LuaLinkP );
}

//**************************************************
// シリアルに\r\n付きで出力します: Serial.println
//  Serial.println([str])
//  str: 文字列
//    省略時は何も出力しません
//**************************************************
int serialPrintln( lua_State *LuaLinkP )
{
	return serialp( 1, LuaLinkP );
}

//**************************************************
// シリアルから1バイト取得します: Serial.read
//  Serial.read()
// 戻り値
//	0x00～0xFFの値、データが無いときは-1が返ります
//**************************************************
int serialRead( lua_State *LuaLinkP )
{
int ret = -1;	

	if(Serial.available()){

		ret = Serial.read(); //1文字取得
	}

	lua_settop(LuaLinkP, 0);			//スタックのクリア
	lua_pushnumber( LuaLinkP, ret );

	return( 1 );		//戻り値は1つですよ。
}

//**************************************************
// シリアルにデータを出力します: Serial.write
//  Serial.write( buf, len )
//	buf: 出力データ
//	len: 出力データサイズ
// 戻り値
//	出力したバイト数
//**************************************************
int serialWrite( lua_State *LuaLinkP )
{
	int n = lua_gettop( LuaLinkP );
	if( n<2 ){
		LuaErrorMes( LuaLinkP, (char*)"Serial.write", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	unsigned char* str = (unsigned char*)luaL_checklstring( LuaLinkP, 1, NULL );
	int len = lua_tonumber( LuaLinkP, 2 );

	int ret = Serial.write( (const unsigned char *)str, len );
	
	lua_settop(LuaLinkP, 0);			//スタックのクリア
	lua_pushnumber( LuaLinkP, ret );

	return( 1 );		//戻り値は1つですよ。
}