//************************************************************************
// SDカード読み込みアクセス関係
//************************************************************************
#if defined __cplusplus
extern "C" {
#endif

#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

typedef struct LoadF {
	int n;  /* number of pre-read characters */
	int extraline;
	FILE *f;
	char buff[LUAL_BUFFERSIZE];
} LoadF;

	
//**********************************
// lauxlib.c の getF関数の代用関数
//**********************************
void sdgetF( LoadF *lf, size_t *size );		//.cから参照するものは、extern "C"に入れときましょう。

//void sdcheck( LoadF *lf, size_t *size, int x );

#if defined __cplusplus
}
#endif

//**********************************
//Sakulua の起動初期化を行います
//**********************************
void init_sakulua( void );
