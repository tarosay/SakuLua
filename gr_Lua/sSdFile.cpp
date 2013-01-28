//************************************************************************
// SDカードファイル関連 2013.1.29
//************************************************************************
#include <rxduino.h>

#include "../gr_sakura_sdmmc/sdmmc.h"
#include "sExec.h"

extern SDMMC MicroSD;

File Fp0 = MicroSD.open(__null);			//コマンド用
File Fp1 = MicroSD.open(__null);			//コマンド用

//**************************************************
// openしたファイルから1バイト読み込みます: SD.read
//	SD.read( number )
//	number: ファイル番号 0 または 1
// 戻り値
//	0x00～0xFFが返る。ファイルの最後だったら-1が返る。
//**************************************************
int sdcardRead( lua_State *LuaLinkP )
{	
	int n = lua_gettop( LuaLinkP );
	if( n<1 ){
		LuaErrorMes( LuaLinkP, (char*)"SD.read", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	int num = lua_tonumber( LuaLinkP, 1 );

	int dat = -1;
	if( num==0 ){
		dat = Fp0.read();
	}
	else if( num==1 ){
		dat = Fp1.read();
	}
	
	lua_settop(LuaLinkP, 0);			//スタックのクリア
	lua_pushnumber( LuaLinkP, dat );

	return( 1 );		//戻り値は1つですよ。
}

//**************************************************
// openしたファイルの読み出し位置を移動する: SD.seek
//**************************************************
int sSeek( File fp, lua_State *LuaLinkP )
{
	int ret = 0;
	if( lua_tonumber( LuaLinkP, 2 )==-1 ){
		if( fp.seek(fp.size()) ){
			ret = 1;
		}
	}
	else{
		unsigned long size = lua_tonumber( LuaLinkP, 2 );
		if( fp.seek(size) ){
			ret = 1;
		}
	}
	
	lua_settop(LuaLinkP, 0);			//スタックのクリア
	lua_pushnumber( LuaLinkP, ret );

	return( 1 );		//戻り値は1つですよ。
}

//**************************************************
// openしたファイルの読み出し位置を移動する: SD.seek
//	SD.seek( number, byte )
//	number: ファイル番号 0 または 1
//	byte: seekするバイト数(-1)でファイルの最後に移動する
// 戻り値
//	成功: 1, 失敗: 0
//**************************************************
int sdcardSeek( lua_State *LuaLinkP )
{
	int n = lua_gettop( LuaLinkP );
	if( n<2 ){
		LuaErrorMes( LuaLinkP, (char*)"SD.seek", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	int num = lua_tonumber( LuaLinkP, 1 );

	if( num==0 ){
		return sSeek( Fp0, LuaLinkP );
	}
	else if( num==1 ){
		return sSeek( Fp1, LuaLinkP );
	}
	
	lua_settop(LuaLinkP, 0);			//スタックのクリア
	lua_pushnumber( LuaLinkP, 0 );

	return( 1 );		//戻り値は1つですよ。
}

//**************************************************
// openしたファイルバイナリデータを書き込む: SD.write
//	SD.write( number, buf, len )
//	number: ファイル番号 0 または 1
//	buf: 書き込むデータ
//	len: 書き込むデータサイズ
// 戻り値
//	実際に書いたバイト数
//**************************************************
int sdcardWrite( lua_State *LuaLinkP )
{
	int n = lua_gettop( LuaLinkP );
	if( n<3 ){
		LuaErrorMes( LuaLinkP, (char*)"SD.write", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	int num = lua_tonumber( LuaLinkP, 1 );

	unsigned char* str = (unsigned char*)luaL_checklstring( LuaLinkP, 2, NULL );
	int len = lua_tonumber( LuaLinkP, 3 );
	int ret = 0;
	if( num==0 ){
		ret = Fp0.write( str, len );
	}
	else if( num==1 ){
		ret = Fp1.write( str, len );
	}
	
	lua_settop(LuaLinkP, 0);			//スタックのクリア
	lua_pushnumber( LuaLinkP, ret );

	return( 1 );		//戻り値は1つですよ。
}

//**************************************************
// ファイルをオープンします: SD.open
//	SD.open( number, filename[, mode] )
//	number: ファイル番号 0 または 1
//	filename: ファイル名(8.3形式)
//	mode: 0:Read, 1:Append, 2:New Create
// 戻り値
//	成功: 番号, 失敗: -1
//**************************************************
int sdcardOpen( lua_State *LuaLinkP )
{
	int n = lua_gettop( LuaLinkP );
	if( n<2 ){
		LuaErrorMes( LuaLinkP, (char*)"SD.open", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	int num = lua_tonumber( LuaLinkP, 1 );
	char *str = (char*)luaL_checklstring( LuaLinkP, 2, NULL );

	int mode = 0;
	if( n>=3 ){
		mode = lua_tonumber( LuaLinkP, 3 );
	}

	if( mode==2 ){
		//新規書き込み
		if( MicroSD.exists( str )==true){
			MicroSD.remove( str );
		}
	}

	int ret = -1;
	if( num==0 ){
		if( mode==1 || mode==2 ){
			if( Fp0 = MicroSD.open( str, FILE_WRITE )){
				ret = num;
			}
		}
		else{
			if( Fp0 = MicroSD.open( str, FILE_READ )){
				ret = num;
			}
		}
	}
	else if( num==1 ){
		if( mode==1 || mode==2 ){
			if( Fp1 = MicroSD.open( str, FILE_WRITE )){
				ret = num;
			}
		}
		else{
			if( Fp1 = MicroSD.open( str, FILE_READ )){
				ret = num;
			}
		}
	}

	lua_settop(LuaLinkP, 0);			//スタックのクリア
	lua_pushnumber( LuaLinkP, ret );

	return( 1 );		//戻り値は1つですよ。
}

//**************************************************
// ファイルをクローズします: SD.close( number )
//	SD.close( number )
//	number: ファイル番号 0 または 1
//**************************************************
int sdcardClose( lua_State *LuaLinkP )
{
	int n = lua_gettop( LuaLinkP );
	if( n<1 ){
		LuaErrorMes( LuaLinkP, (char*)"SD.close", 0 );
		return( 1 );		//戻り値は1つですよ。
    }

	int num = lua_tonumber( LuaLinkP, 1 );

	if( num==0 ){
		//Fp0.flush();
		Fp0.close();
	}
	else if( num==1 ){
		//Fp1.flush();
		Fp1.close();
	}

	lua_settop(LuaLinkP, 0);			//スタックのクリア

	return( 0 );		//戻り値は1つですよ。
}
