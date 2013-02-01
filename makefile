OBJFILES = ./gr_sketch.o ./gr_sakura_wire/instwire.o ./gr_common/intvect.o ./gr_common/lowlevel.o \
			./i2clcd.o \
			./gr_Lua/lua/lapi.o ./gr_Lua/lua/lauxlib.o ./gr_Lua/lua/lbaselib.o ./gr_Lua/lua/lcode.o \
			./gr_Lua/lua/ldebug.o ./gr_Lua/lua/ldo.o ./gr_Lua/lua/ldump.o ./gr_Lua/lua/lfunc.o ./gr_Lua/lua/lgc.o \
			./gr_Lua/lua/linit.o ./gr_Lua/lua/llex.o ./gr_Lua/lua/lmathlib.o ./gr_Lua/lua/lmem.o \
			./gr_Lua/lua/lobject.o ./gr_Lua/lua/lopcodes.o \
			./gr_Lua/lua/lparser.o ./gr_Lua/lua/lstate.o ./gr_Lua/lua/lstring.o ./gr_Lua/lua/lstrlib.o ./gr_Lua/lua/ltable.o \
			./gr_Lua/lua/ltablib.o ./gr_Lua/lua/ltm.o ./gr_Lua/lua/lundump.o ./gr_Lua/lua/lvm.o ./gr_Lua/lua/lzio.o \
			./gr_Lua/sExec.o ./gr_Lua/sI2cLcd.o ./gr_Lua/sSdgetF.o ./gr_Lua/sSystem.o ./gr_Lua/sAdk.o \
			./gr_Lua/sSerial.o ./gr_Lua/sRTC.o ./gr_Lua/sWire.o ./gr_Lua/sSdFile.o

#			./gr_Lua/lua/loadlib.o \
#			./gr_Lua/lua/ldblib.o \
#			./gr_Lua/lua/liolib.o \
#			./gr_Lua/lua/loslib.o \

LIBFILES = ./gr_common/lib/libc.a ./gr_common/lib/libg.a ./gr_common/lib/libgcc.a ./gr_common/lib/libm.a ./gr_common/lib/librxduino.a \
			./gr_common/lib/libsim.a ./gr_common/lib/libstdc++.a ./gr_common/lib/libsupc++.a ./gr_common/lib/libtkdnhal.a \
			./gr_common/lib/libtkdnip.a ./gr_sakura_wire/libwire.a ./gr_sakura_sdmmc/libsdmmc.a ./gr_sakura_eeprom/libeeprom.a 

CCINC = -I./gr_build -I./gr_common -I./gr_common/include -I./gr_common/include/rxduino -I./gr_common/include/tkdnhal \
		-I./gr_common/lib -I./gr_sakura_wire -I./gr_Lua/lua -I./gr_Lua -I./gr_sakura_sdmmc -I./gr_sakura_eeprom 

CPPINC = -I./gr_build -I./gr_common -I./gr_common/include -I./gr_common/include/rxduino -I./gr_common/include/tkdnhal \
		-I./gr_common/lib -I./gr_sakura_wire -I./gr_Lua/lua -I./gr_Lua -I./gr_sakura_sdmmc -I./gr_sakura_eeprom 


TARGET = sketch
CC  = $(CCPATH)rx-elf-gcc -Wall -g -O2 $(CCINC)
CPP = $(CCPATH)rx-elf-gcc -Wall -g -O2 $(CPPINC)
AS  = $(CCPATH)rx-elf-as 
LNK = $(CCPATH)rx-elf-ld
#CNV = $(CCPATH)rx-elf-objcopy --srec-forceS3 --srec-len 32 -O srec
CNV = $(CCPATH)rx-elf-objcopy -O binary
DMP = $(CCPATH)rx-elf-objdump
OBJS = ./gr_common/gstart.o $(OBJFILES) $(LIBFILES) 
LFLAGS = -L./gr_common/lib/ -lrxduino -lstdc++ -lsupc++ -lc -lsim -lgcc -lm -ltkdnhal -nostartfiles
MAKEFILE = makefile
ROMSCRIPT=./gr_common/gr_sakura.gsi

make = make --no-print-directory 
RMOO = rm -R -f *.o

all:	rom

clean:
	find . -name '*.o' -type f -print0 | xargs -0 rm
	rm -f $(TARGET).elf
	cp gr_sakura_wire/instwire.o.copy gr_sakura_wire/instwire.o
	cp gr_common/gstart.o.copy gr_common/gstart.o


rom:	$(OBJS) $(MAKEFILE) $(ROMSCRIPT)
	$(LNK) -Map ./gr_build/$(TARGET).map $(OBJS) -T $(ROMSCRIPT) $(LFLAGS) -o $(TARGET).elf
	$(CNV) $(TARGET).elf  $(TARGET).bin
	rm -f *.o
	rm -f $(TARGET).elf

#gstart.o:	gstart.s
#	$(AS) -o gstart.o gstart.s

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.cpp.o:
	$(CPP) $(CFLAGS) -c $< -o $@
