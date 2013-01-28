//************************************************************************
// ��{���ߊ֘A
//************************************************************************

//**************************************************
// PIN�̃��[�h�ݒ�: pinMode
//	pinMode(pin, mode)
//	pin: �s���̔ԍ�
//	mode:
//		0: INPUT���[�h
//		1: OUTPUT���[�h
//		3: OUTPUT_HIGH ���[�h(���쓮�o��)
//**************************************************
int adkPinMode( lua_State *LuaLinkP );

//**************************************************
// �f�W�^�����C�g: digitalWrite
//	digitalWrite(pin, value)
//	pin: �s���̔ԍ�
//	mode:
//		0: LOW
//		1: HIGH
//**************************************************
int adkDigitalWrite( lua_State *LuaLinkP );

//**************************************************
// �f�W�^�����[�h: digitalRead
//	digitalRead(pin)
//	pin: �s���̔ԍ�
//	
//		0:LOW
//		1:HIGH
//**************************************************
int adkDigitalRead( lua_State *LuaLinkP );

//**************************************************
// �A�i���O���C�g: analogWrite
//	analogWrite(pin, value)
//	pin: �s���̔ԍ�
//  value:	�o��PWM�䗦(0�`255)
//**************************************************
int adkAnalogWrite( lua_State *LuaLinkP );

//**************************************************
// �A�i���O���[�h: analogRead
//	analogRead(pin)
//	pin: �s���̔ԍ�
//	
//		10�r�b�g�̒l(0�`1023)
//**************************************************
int adkAnalogRead( lua_State *LuaLinkP );

//**************************************************
// �A�i���ODAC�o��: analogWriteDAC
//	analogWriteDAC(pin, value)
//	pin: �s���̔ԍ�
//	value: DAC�o��10BIt(0�`4095)
//**************************************************
int adkAnalogWriteDAC( lua_State *LuaLinkP );

//**************************************************
// �A�i���O���t�@�����X: analogReference
//	analogReference(type)
//	type:
//		0: DEFAULT
//		1: INTERNAL
//		2: EXTERNAL
//		3: RAW12BIT
//**************************************************
int adkAnalogReference( lua_State *LuaLinkP );

//**************************************************
// �A�i���OPWM���g���ݒ�: analogWriteFrequency
//	analogWriteDAC(valueHz)
//	valueHz: �ݒ肷����g��(12�`184999Hz)
//**************************************************
int adkAnalogWriteFrequency( lua_State *LuaLinkP );

//**************************************************
// �s���ɓ��͂����p���X�����o: pulseIn
//	pulseIn(pin, value[, timeout])
//	pin: �s���̔ԍ�
//	value: �p���X�̎��(HIGH(1)�܂���LOW(0))
//	timeout: timeout �^�C���A�E�g�܂ł̎���(�P�ʁE�}�C�N���b) �f�t�H���g��1�b
//
//		�p���X����
//**************************************************
int adkPulseIn( lua_State *LuaLinkP );

//**************************************************
// �w�莞�ԑ҂��܂�: delay
//	delay( msec )
//	msec: ����(msec)
//**************************************************
int adkDelay( lua_State *LuaLinkP );

//**************************************************
// �~���b���擾���܂�: millis
//	millis()
// �߂�l
//	�N�����Ă���̃~���b��
//**************************************************
int adkMillis( lua_State *LuaLinkP );
