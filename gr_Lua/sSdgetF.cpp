//************************************************************************
// SDカード読み込みアクセス関係 2013.1.28
//************************************************************************
#include <rxduino.h>

#include "sSdgetf.h"
#include "../gr_sakura_sdmmc/sdmmc.h"

#define XML_FILENAME  "sakulua.xml"
#define LUA_FILENAME  "sakulua.lua"
#define LUA_FILENAME_SIZE 32

char LuaStartFileName[LUA_FILENAME_SIZE];	//xmlに指定された最初に起動するLuaファイル名
char LuaFilename[LUA_FILENAME_SIZE];
char ExeFilename[LUA_FILENAME_SIZE];		//現在実行されているファイルのパス名

SDMMC MicroSD;								//SDカードクラス
File SdFile = MicroSD.open(__null);			//システム用

//**********************************
//Sakulua の起動初期化を行います
//**********************************
void init_sakulua( void )
{
char dat[4];
int en;
int i;

	//SDカード関連の初期化
	MicroSD.begin();

	//スタートLuaファイルを読み込みます
	if( MicroSD.exists(XML_FILENAME)==false ){
	
		strcpy( LuaStartFileName, LUA_FILENAME );
	}
	else{
		
		LuaStartFileName[0] = 0;

		//スタートファイル名を読み込みます
		File fxml = MicroSD.open( XML_FILENAME, FILE_READ );

		//file= が出るまでひたすら読み込みます
		unsigned long pos = 0;
		while( fxml.available() ){
			fxml.seek( pos );

			dat[0] = 0;
			dat[1] = 0;
			dat[2] = 0;
			dat[3] = 0;
			for( i=0; i< 4; i++ ){
				en = fxml.read();
				if( en<0 ){ break; }
				dat[i] = (char)en;
			}

			if( dat[0]=='f' && dat[1]=='i' && dat[2]=='l' && dat[3]=='e'  ){

				//見つかったので " or ' まで読み飛ばす
				while( fxml.available() ){
					en = fxml.read();
					if( en<0 ){ break; }
					if( (char)en==0x22 || (char)en==0x27 ){

						//見つかったので " or ' まで取り込みます
						for( i=0; i<FILENAME_SIZE; i++ ){
							en = fxml.read();
							if( en<0 ){
								LuaStartFileName[0] = 0;
								break;
							}

							if( (char)en==0x22 || (char)en==0x27 ){
								LuaStartFileName[i] = 0;
								break;
							}
							LuaStartFileName[i] = (char)en;
						}
						break;
					}
				}

				break;
			}
			pos++;
		}
		fxml.close();

		if( LuaStartFileName[0]==0 ){
			strcpy( LuaStartFileName, LUA_FILENAME );
		}
	}

	//LuaFilenameにスタートファイル名をコピーします
	strcpy( LuaFilename, LuaStartFileName );

	//char az[100];
	//sprintf( az, "LuaStartFileName= %s\n", LuaStartFileName );
	//Serial.println( az );
}

/*
void sdcheck( LoadF *lf, size_t *size, int x )
{
	char az[30];
	Serial.println( "void sdcheck( char *buff, size_t *size )" );
	sprintf( az, "s = %d x = %d\n", (int)*size, x );
	Serial.println( az );
	Serial.println( lf->buff );
}
*/

//**********************************
// lauxlib.c の getF関数の代用関数
//**********************************
void sdgetF( LoadF *lf, size_t *size )
{
int	i;
int en = 0;
int len = (int)*size;

	if( SdFile.available()==false ){
		*size = 0;
		return;
	}

	*size = sizeof(lf->buff) > FILE_BUFFER_SIZE ? FILE_BUFFER_SIZE : sizeof(lf->buff);

	for(i=0; i<len; i++){
		en = SdFile.read();
		if( en<0 ){
			*size = i;
			break;
		}
		lf->buff[i] = (char)en;
	}
}
