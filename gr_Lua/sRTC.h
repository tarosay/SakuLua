//************************************************************************
// RTC関連
//************************************************************************

////**************************************************
//// 32.768KHz水晶を発振させてRTCを起動する: RTC.begin
////	RTC.begin()
////
//// 結果が返る
////**************************************************
//int adkRTCbegin( lua_State *LuaLinkP );

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
int adkRTCsetDateTime( lua_State *LuaLinkP );

//**************************************************
// RTCの時計を取得する: RTC.get
//	RTC.get()
//
// 西暦, 月, 日, 時, 分, 秒
//**************************************************
int adkRTCgetDateTime( lua_State *LuaLinkP );
