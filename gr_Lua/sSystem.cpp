//************************************************************************
// システム・ハード関連 2013.2.1
//************************************************************************
#include <rxduino.h>
#include <eeprom.h>

#include "sExec.h"

extern char LuaFilename[];
extern volatile char ProgVer[];

//**************************************************
//Luaファイルを実行します: sys.setrun
//sys.setrun( filename )
//  filename: 実行するLuaファイル名
//　このコマンドを呼べは直ぐにLuaファイルが実行されるわけではない。
//　今動いているLuaスクリプトを終了させたときに呼び出される。
//**************************************************
int sysSetrun( lua_State *LuaLinkP )
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
//バージョンを取得します: sys.ver
//sys.ver()
// 戻り値
//   SakuLuaのバージョン
//**************************************************
int sysVer( lua_State *LuaLinkP )
{
	lua_settop(LuaLinkP, 0);			//スタックのクリア
	lua_pushstring( LuaLinkP, (char*)ProgVer );
	return( 1 );						//戻り値は1つですよ
}

//**************************************************
//終了します: sys.exit
//sys.exit()
//   現在走っているLuaスクリプトを強制終了させるのですが、
//   SakuLuaは続けてsys.setrun()で設定されたLuaスクリプトを実行します。
//   本当に止めたいときは、while(true)do end として無限ループにしてください。
//**************************************************
int sysExit( lua_State *LuaLinkP )
{
	lua_settop(LuaLinkP, 0);			//スタックのクリア
	lua_pushstring( LuaLinkP, "Exit" );
	lua_error( LuaLinkP );
	return( 1 );						//戻り値は1つですよ
}

//**************************************************
//フラッシュメモリに書き込みます: sys.push
//sys.push(address, buf, length)
//	address: 書き込み開始アドレス(0x0000～0x7fff)
//  buf: 書き込むデータ
//  length: 書き込むサイズ
// 戻り値
//  1:成功, 0:失敗
//**************************************************
int sysPush( lua_State *LuaLinkP )
{
EEPROM myeep;

	int n = lua_gettop( LuaLinkP );
	if( n<3 ){
		LuaErrorMes( LuaLinkP, (char*)"sys.push", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	unsigned long add = lua_tonumber( LuaLinkP, 1 );
	unsigned char* str = (unsigned char*)luaL_checklstring( LuaLinkP, 2, NULL );
	int len = lua_tonumber( LuaLinkP, 3 );
	int ret = 1;
	for(int i=0; i<len; i++){
		ret = myeep.write( add, str[i] );
		if(ret==-1){
			ret = 0;
			break;
		}
		add++;
	}
	
	//tkdn_dflash_erase( 0x7F00, 0x20 );
	//len = tkdn_dflash_write( 0x7F00, c, 1 );
	//int len = tkdn_dflash_read( 0x7F00, c, 2);
	//tkdn_dflash_erase( 0x7F00, 0x20 );
	//len = tkdn_dflash_write( 0x7F00, c, 1 );
	//tkdn_dflash_terminate();

	lua_settop(LuaLinkP, 0);			//スタックのクリア
	lua_pushnumber( LuaLinkP, ret );

	return( 1 );		//戻り値は1つですよ。
}

//**************************************************
//フラッシュメモリから読み出します: sys.pop
//sys.pop(address, length)
//	address: 読み込みアドレス(0x0000～0x7fff)
//  length: 読み込みサイズ(MAX 32バイト)
// 戻り値
//  読み込んだデータ
//**************************************************
int sysPop( lua_State *LuaLinkP )
{
EEPROM myeep;
unsigned char str[32];

	int n = lua_gettop( LuaLinkP );
	if( n<2 ){
		LuaErrorMes( LuaLinkP, (char*)"sys.pop", 0 );
		return( 1 );		//戻り値は1つですよ。
    }
	unsigned long add = lua_tonumber( LuaLinkP, 1 );
	int len = lua_tonumber( LuaLinkP, 2 );
	if(len>32){
		len = 32;
	}
	for(int i=0; i<len; i++){
		str[i] = myeep.read( add );
		add++;
	}
	
	lua_settop(LuaLinkP, 0);				//スタックのクリア
	lua_pushlstring(LuaLinkP, (const char*)str, len);	//1番目の戻り値
	return( 1 );							//戻り値は1つですよ。
}