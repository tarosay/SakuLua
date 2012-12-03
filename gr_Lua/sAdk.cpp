//************************************************************************
// 基本命令関連 2012.12.4
//************************************************************************
#include <rxduino.h>

#include "sExec.h"

//**************************************************
// PINのモード設定: pinMode
//	pinMode(pin, mode)
//	pin: ピンの番号
//	mode:
//		0: INPUTモード
//		1: OUTPUTモード
//		3: OUTPUT_HIGH モード(高駆動出力)
//**************************************************
int adkPinMode( lua_State *LuaLinkP )
{
    int n = lua_gettop( LuaLinkP );
	if( n<2 ){
		LuaErrorMes( LuaLinkP, (char*)"pinMode", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	int num = lua_tonumber( LuaLinkP, 1 );
	int mode = lua_tonumber( LuaLinkP, 2 );

	pinMode( num, mode);

	lua_settop(LuaLinkP, 0);
	return( 0 );		//戻り値は無しですよ。
}

//**************************************************
// デジタルライト: digitalWrite
//	digitalWrite(pin, value)
//	pin: ピンの番号
//	mode:
//		0: LOW
//		1: HIGH
//**************************************************
int adkDigitalWrite( lua_State *LuaLinkP )
{
    int n = lua_gettop( LuaLinkP );
	if( n<2 ){
		LuaErrorMes( LuaLinkP, (char*)"digitalWrite", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	int num = lua_tonumber( LuaLinkP, 1 );
	int mode = lua_tonumber( LuaLinkP, 2 );

	digitalWrite(num, mode);

	lua_settop(LuaLinkP, 0);
	return( 0 );		//戻り値は無しですよ。
}

//**************************************************
// デジタルリード: digitalRead
//	digitalRead(pin)
//	pin: ピンの番号
//	
//		0:LOW
//		1:HIGH
//**************************************************
int adkDigitalRead( lua_State *LuaLinkP )
{
    int n = lua_gettop( LuaLinkP );
	if( n<1 ){
		LuaErrorMes( LuaLinkP, (char*)"digitalRead", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	int num = lua_tonumber( LuaLinkP, 1 );

	lua_settop(LuaLinkP, 0);			//スタックのクリア
	int l = digitalRead( num );

	lua_pushnumber( LuaLinkP, l );

	return( 1 );		//戻り値は1つですよ。
}

//**************************************************
// アナログライト: analogWrite
//	analogWrite(pin, value)
//	pin: ピンの番号
//  value:	出力PWM比率(0～255)
//**************************************************
int adkAnalogWrite( lua_State *LuaLinkP )
{

    int n = lua_gettop( LuaLinkP );
	if( n<2 ){
		LuaErrorMes( LuaLinkP, (char*)"analogWrite", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	int num = lua_tonumber( LuaLinkP, 1 );
	int vale = lua_tonumber( LuaLinkP, 2 );
	if( vale>=0 && vale<256 ){
		analogWrite( num, vale );
	}
	else{
		analogWrite( num, 0 );
	}

	lua_settop(LuaLinkP, 0);
	return( 0 );		//戻り値は無しですよ。
}

//**************************************************
// アナログリード: analogRead
//	analogRead(pin)
//	pin: ピンの番号
//	
//		10ビットの値(0～1023)
//**************************************************
int adkAnalogRead( lua_State *LuaLinkP )
{
    int n = lua_gettop( LuaLinkP );
	if( n<1 ){
		LuaErrorMes( LuaLinkP, (char*)"analogRead", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	int num = lua_tonumber( LuaLinkP, 1 );
	
	lua_settop(LuaLinkP, 0);			//スタックのクリア
	int l = analogRead( num );
	lua_pushnumber( LuaLinkP, l );

	return( 1 );		//戻り値は1つですよ。
}

//**************************************************
// アナログリファレンス: analogReference
//	analogReference(type)
//	type:
//		0: DEFAULT
//		1: INTERNAL
//		2: EXTERNAL
//		3: RAW12BIT
//**************************************************
int adkAnalogReference( lua_State *LuaLinkP )
{
    int n = lua_gettop( LuaLinkP );
	if( n<1 ){
		LuaErrorMes( LuaLinkP, (char*)"analogReference", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	int num = lua_tonumber( LuaLinkP, 1 );
	analogReference( num );

	lua_settop(LuaLinkP, 0);
	return( 0 );		//戻り値は無しですよ。
}

//**************************************************
// アナログDAC出力: analogWriteDAC
//	analogWriteDAC(pin, value)
//	pin: ピンの番号
//	value: DAC出力10BIt(0～4095)
//**************************************************
int adkAnalogWriteDAC( lua_State *LuaLinkP )
{
    int n = lua_gettop( LuaLinkP );
	if( n<2 ){
		LuaErrorMes( LuaLinkP, (char*)"analogWriteDAC", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	int num = lua_tonumber( LuaLinkP, 1 );
	int v = (unsigned long)lua_tonumber( LuaLinkP, 2 );
	if( v<0 ){ v = 0; }
	if( v>4095 ){ v = 4095; }

	analogWriteDAC( num, v );

	lua_settop(LuaLinkP, 0);
	return( 0 );		//戻り値は無しですよ。
}

//**************************************************
// アナログPWM周波数設定: analogWriteFrequency
//	analogWriteDAC(valueHz)
//	valueHz: 設定する周波数(12～184999Hz)
//**************************************************
int adkAnalogWriteFrequency( lua_State *LuaLinkP )
{
    int n = lua_gettop( LuaLinkP );
	if( n<1 ){
		LuaErrorMes( LuaLinkP, (char*)"analogWriteFrequency", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	unsigned long hz = (unsigned long)lua_tonumber( LuaLinkP, 1 );
	if( hz<12 ){ hz = 12; }
	if( hz>184999 ){ hz = 184999; }

	analogWriteFrequency( hz );

	lua_settop(LuaLinkP, 0);
	return( 0 );		//戻り値は無しですよ。
}

//**************************************************
// ピンに入力されるパルスを検出: pulseIn
//	pulseIn(pin, value[, timeout])
//	pin: ピンの番号
//	value: パルスの種類(HIGH(1)またはLOW(0))
//	timeout: timeout タイムアウトまでの時間(単位・マイクロ秒) デフォルトは1秒
//
//		パルス時間
//**************************************************
int adkPulseIn( lua_State *LuaLinkP )
{
    int n = lua_gettop( LuaLinkP );
	if( n<2 ){
		LuaErrorMes( LuaLinkP, (char*)"pulseIn", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	int num = lua_tonumber( LuaLinkP, 1 );
	int pl = lua_tonumber( LuaLinkP, 2 );
	unsigned long tim = 1000000;
	if(n>2){
		tim = (unsigned long)lua_tonumber( LuaLinkP, 3 );
	}

	tim = pulseIn( num, pl, tim );
	
	lua_pushnumber( LuaLinkP, tim );

	return( 1 );		//戻り値は1つですよ。
}

//**************************************************
// 指定時間待ちます: delay
//	delay( msec )
//	msec: 時間(msec)
//**************************************************
int adkDelay( lua_State *LuaLinkP )
{
    int n = lua_gettop( LuaLinkP );
	if( n<1 ){
		LuaErrorMes( LuaLinkP, (char*)"delay", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	unsigned long msec = (unsigned long)lua_tonumber( LuaLinkP, 1 );

	delay( msec );
	
	lua_settop(LuaLinkP, 0);
	return( 0 );		//戻り値は無しですよ。
}
