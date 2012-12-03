//*****************************************************************************
// LCD CLOCK 
//*****************************************************************************
//#include <rxduino.h>
#include <Wire.h> 

#include "i2clcd.h"

//I2Cのピン割当
#define LCD_RST     PIN_P43
#define LCD_SCL     PIN_P44
#define LCD_SDA     PIN_P45

char DispTxt[256];
//**************************************************
// コマンドを送信します。HD44780でいうRS=0に相当
//**************************************************
void i2c_cmd(unsigned char db)
{
     Wire.beginTransmission(0b0111110);
     Wire.write(0b00000000);
     Wire.write(db);
     Wire.endTransmission();
}

//**************************************************
// データを送信します。HD44780でいうRS=1に相当
//**************************************************
void i2c_data(unsigned char db)
{
     Wire.beginTransmission(0b0111110);
     Wire.write(0b01000000);
     Wire.write(db);
     Wire.endTransmission();
}

//**************************************************
// （主に）文字列を連続送信します。
//**************************************************
void i2c_puts(const char *s)
{
     while(*s){
          i2c_data(*s++);
     }
}

//**************************************************
//アイコンアドレス, 該当ビット配列宣言
//**************************************************
static unsigned char icon_data[]={
     // アイコンアドレス, 該当ビット
     0x00, 0b10000,
     0x02, 0b10000,
     0x04, 0b10000,
     0x06, 0b10000,
    
     0x07, 0b10000,
     0x07, 0b01000,
     0x09, 0b10000,
     0x0B, 0b10000,
    
     0x0D, 0b01000,
     0x0D, 0b00100,
     0x0D, 0b00010,
     0x0D, 0b10000,
    
     0x0F, 0b10000, // アンテナマーク
};
unsigned short IconBit = 0;	//アイコンのセット状態


//**************************************************
//     アイコンの表示ルーチン
//
//  それぞれのアイコンに該当するビットを立てる（クリア）します。
//  現在のアイコンの表示状態は読み取れないため、マイコン側でデータを
//  編集してからまとめて送信する必要があります。icon_buff[]
//
//  引き数：各ビットがそれぞれのアイコンに相当します。bit0〜bit12（全１３ビット）
//  bit0が右端のアイコン, bit13が左のアイコン（アンテナ）に該当します。
//  puticon(0x1FFF)で全アイコン点灯
//**************************************************
void puticon(unsigned short flg)
{
	static unsigned char icon_buff[16];	// アイコンの編集用
	unsigned char i;

	for( i=0; i<sizeof(icon_data)/2; i++ ){

		if(flg & (0x1000>>i)){			// 該当ビットが立っていたら
			icon_buff[icon_data[i*2]] |= icon_data[i*2+1];	// バッファを立てます。
		}
		else{
			icon_buff[icon_data[i*2]] &= ~icon_data[i*2+1];	// バッファをクリアします。
		}
	}

	// 一括でLCDに書き込みます。
	for( i=0; i<16; i++ ){
		i2c_cmd(0b00111001);		// コマンド
		i2c_cmd(0b01000000+i);		// アイコン領域のアドレスを設定
		i2c_data(icon_buff[i]);		// アイコンデータ
	}
}

//**************************************************
// アンテナアイコン表示
//**************************************************
void putAntIcon( bool dispFlg )
{
	if( dispFlg==true ){
		IconBit |= (1<<12);
	}
	else{
		IconBit &= (0x1FFF-(1<<12));
	}
	puticon( IconBit );
}

//**************************************************
// 電話アイコン表示
//**************************************************
void putTelIcon( bool dispFlg )
{
	if( dispFlg==true ){
		IconBit |= (1<<11);
	}
	else{
		IconBit &= (0x1FFF-(1<<11));
	}
	puticon( IconBit );
}

//**************************************************
// Wifiアイコン表示
//**************************************************
void putWifiIcon( bool dispFlg )
{
	if( dispFlg==true ){
		IconBit |= (1<<10);
	}
	else{
		IconBit &= (0x1FFF-(1<<10));
	}
	puticon( IconBit );
}

//**************************************************
// 接続アイコン表示
//**************************************************
void putConIcon( bool dispFlg )
{
	if( dispFlg==true ){
		IconBit |= (1<<9);
	}
	else{
		IconBit &= (0x1FFF-(1<<9));
	}
	puticon( IconBit );
}

//**************************************************
// 上下アイコン表示
// 0: 消灯, 1:上, 2:下, 3:両方
//**************************************************
void putUpDnIcon( int disp )
{
	switch(disp){
	case 0:
		IconBit &= (0x1FFF-(1<<7)-(1<<8));
		break;
	case 1:
		IconBit &= (0x1FFF-(1<<7));
		IconBit |= (1<<8);
		break;
	case 2:
		IconBit |= (1<<7);
		IconBit &= (0x1FFF-(1<<8));
		break;
	case 3:
		IconBit |= ((1<<7)|(1<<8));
		break;
	}
	puticon( IconBit );
}

//**************************************************
// ロックアイコン表示
//**************************************************
void putLockIcon( bool dispFlg )
{
	if( dispFlg==true ){
		IconBit |= (1<<6);
	}
	else{
		IconBit &= (0x1FFF-(1<<6));
	}
	puticon( IconBit );
}

//**************************************************
// スピーカーアイコン表示
//**************************************************
void putSpkIcon( bool dispFlg )
{
	if( dispFlg==true ){
		IconBit |= (1<<5);
	}
	else{
		IconBit &= (0x1FFF-(1<<5));
	}
	puticon( IconBit );
}

//**************************************************
// バッテリーアイコン表示
// 0:消灯, 1:空, 2, 3, 4:満タン
//**************************************************
void putBattIcon( int disp )
{
	switch(disp){
	case 0:
		IconBit &= 0x1FE1;
		break;
	case 1:
		IconBit |= (1<<2);
		IconBit &= (0x1FFF-(1<<1)-(1<<3)-(1<<4));
		break;
	case 2:
		IconBit |= ((1<<1)|(1<<2));
		IconBit &= (0x1FFF-(1<<3)-(1<<4));
		break;
	case 3:
		IconBit |= ((1<<1)|(1<<2)|(1<<4));
		IconBit &= (0x1FFF-(1<<3));
		break;
	case 4:
		IconBit |= ((1<<1)|(1<<2)|(1<<3)|(1<<4));
		break;
	}
	puticon( IconBit );
}

//**************************************************
// 玉アイコン表示
//**************************************************
void putTamaIcon( bool dispFlg )
{
	if( dispFlg==true ){
		IconBit |= 1;
	}
	else{
		IconBit &= (0x1FFF-1);
	}
	puticon( IconBit );
}

//**************************************************
// LCDの初期化を行います
//**************************************************
void lcd_setup(void)
{
	// コントラストの設定(電源電圧，温度によりかなり変化します。実際の液晶をみて調整してください。)
	unsigned char contrast = 0b1100011;     // 数値を上げると濃くなります。

	pinMode(LCD_RST, OUTPUT);
	Wire.assignSdaScl( LCD_SDA, LCD_SCL ) ;
	
	delay(500);
	
	digitalWrite(LCD_RST, LOW);				// RSTをLにします。リセット
	delay(1);
	digitalWrite(LCD_RST, HIGH);			// RSTをHにします。リセット解除
	delay(10);
	
	// ここからI2C LCDの初期化を行います。
	delay(40);
	i2c_cmd(0b00111000);					// function set
	i2c_cmd(0b00111001);					// function set
	i2c_cmd(0b00010100);					// interval osc
	i2c_cmd(0b01110000 | (contrast & 0xF));	// contrast Low

	i2c_cmd(0b01011100 | ((contrast >> 4) & 0x3));	// contast High/icon/power
	i2c_cmd(0b01101100);					// follower control
	delay(300);

	i2c_cmd(0b00111000);					// function set
	i2c_cmd(0b00001100);					// Display On

	i2c_cmd(0b00000001);					// Clear Display
	delay(2);								// Clear Displayは追加ウェイトが必要

	//アイコン表示ビットを0にする
	IconBit = 0;
	puticon(IconBit);
}

//**************************************************
// LCDに文字を表示します
//**************************************************
void WriteLine(const char *s, int d )
{
const char *sp = "                ";

	if(d==0){
		//上段に表示します
		// 1行目の左端 ADDR=0x0
		i2c_cmd(0x80);
		i2c_puts( sp );
		i2c_cmd(0x80);
	}
	else{
		//下段に表示します
		// 0xC0 = 0x80(カーソル移動) + 2行目の左端アドレス ADDR=0x40 
		i2c_cmd(0xC0);
		i2c_puts( sp );
		i2c_cmd(0xC0);
	}
	i2c_puts( s );
}
