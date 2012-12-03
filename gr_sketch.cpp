//*****************************************************************************
// SakuLua
//*****************************************************************************
#include <rxduino.h>

#include "sExec.h"
#include "i2clcd.h"
#include "sSdgetF.h"

extern char LuaStartFileName[];
extern char LuaFilename[];

//**************************************************
// セットアップします
//**************************************************
void setup(void)
{
	Serial.begin(9600);
    //Serial.begin( 9600, SCI_AUTO );	//何か押されるまで待つ
	Serial.setDefault();				//現在のシリアルポートを標準出力とするprintfでも出力する
	setvbuf(stdout,NULL,_IONBF,0);

	//sakuluaの初期化
	init_sakulua();

	//lcdの初期化
	lcd_setup();

	//Serial.println( "SakuLua Start\n" );
}

//***************************************************************************
// 無限ループ
//***************************************************************************
void loop()
{
	if( LuaRun()==false ){

		//終了する
		//while(true);
	}
}
