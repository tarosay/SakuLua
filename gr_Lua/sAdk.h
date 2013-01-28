//************************************************************************
// 基本命令関連
//************************************************************************

//**************************************************
// PINのモード設定: pinMode
//	pinMode(pin, mode)
//	pin: ピンの番号
//	mode:
//		0: INPUTモード
//		1: OUTPUTモード
//		3: OUTPUT_HIGH モード(高駆動出力)
//**************************************************
int adkPinMode( lua_State *LuaLinkP );

//**************************************************
// デジタルライト: digitalWrite
//	digitalWrite(pin, value)
//	pin: ピンの番号
//	mode:
//		0: LOW
//		1: HIGH
//**************************************************
int adkDigitalWrite( lua_State *LuaLinkP );

//**************************************************
// デジタルリード: digitalRead
//	digitalRead(pin)
//	pin: ピンの番号
//	
//		0:LOW
//		1:HIGH
//**************************************************
int adkDigitalRead( lua_State *LuaLinkP );

//**************************************************
// アナログライト: analogWrite
//	analogWrite(pin, value)
//	pin: ピンの番号
//  value:	出力PWM比率(0～255)
//**************************************************
int adkAnalogWrite( lua_State *LuaLinkP );

//**************************************************
// アナログリード: analogRead
//	analogRead(pin)
//	pin: ピンの番号
//	
//		10ビットの値(0～1023)
//**************************************************
int adkAnalogRead( lua_State *LuaLinkP );

//**************************************************
// アナログDAC出力: analogWriteDAC
//	analogWriteDAC(pin, value)
//	pin: ピンの番号
//	value: DAC出力10BIt(0～4095)
//**************************************************
int adkAnalogWriteDAC( lua_State *LuaLinkP );

//**************************************************
// アナログリファレンス: analogReference
//	analogReference(type)
//	type:
//		0: DEFAULT
//		1: INTERNAL
//		2: EXTERNAL
//		3: RAW12BIT
//**************************************************
int adkAnalogReference( lua_State *LuaLinkP );

//**************************************************
// アナログPWM周波数設定: analogWriteFrequency
//	analogWriteDAC(valueHz)
//	valueHz: 設定する周波数(12～184999Hz)
//**************************************************
int adkAnalogWriteFrequency( lua_State *LuaLinkP );

//**************************************************
// ピンに入力されるパルスを検出: pulseIn
//	pulseIn(pin, value[, timeout])
//	pin: ピンの番号
//	value: パルスの種類(HIGH(1)またはLOW(0))
//	timeout: timeout タイムアウトまでの時間(単位・マイクロ秒) デフォルトは1秒
//
//		パルス時間
//**************************************************
int adkPulseIn( lua_State *LuaLinkP );

//**************************************************
// 指定時間待ちます: delay
//	delay( msec )
//	msec: 時間(msec)
//**************************************************
int adkDelay( lua_State *LuaLinkP );

//**************************************************
// ミリ秒を取得します: millis
//	millis()
// 戻り値
//	起動してからのミリ秒数
//**************************************************
int adkMillis( lua_State *LuaLinkP );
