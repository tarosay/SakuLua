//************************************************************************
// SD�J�[�h�ǂݍ��݃A�N�Z�X�֌W
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
// lauxlib.c �� getF�֐��̑�p�֐�
//**********************************
void sdgetF( LoadF *lf, size_t *size );		//.c����Q�Ƃ�����̂́Aextern "C"�ɓ���Ƃ��܂��傤�B

//void sdcheck( LoadF *lf, size_t *size, int x );

#if defined __cplusplus
}
#endif

//**********************************
//Sakulua �̋N�����������s���܂�
//**********************************
void init_sakulua( void );
