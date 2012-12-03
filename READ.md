SakuLua Ver 1.06
　SakuLuaは GR-SAKURA 単体で Luaスクリプトを実行するためのプログラムです。

ビルド方法
　Luaに関しては、Lua-5.1.5を元に作成しています。下記のURLより、Lua-5.1.5のソースを入手してください。
http://www.lua.org/versions.html#5.1
The current release is Lua 5.1.5, released on 17 Feb 2012. [NEW]

 Lua-5.1.5を解凍した後、srcフォルダから以下のファイルを取り出して、gr_Lua/luaフォルダに置いた後、lua-5.1.5.patchを当ててください。

gr_Lua/lua/ に下記のファイルを置く。
	lapi.c
	lapi.h
	lauxlib.c
	lauxlib.h
	lbaselib.c
	lcode.c
	lcode.h
	ldebug.c
	ldebug.h
	ldo.c
	ldo.h
	ldump.c
	lfunc.c
	lfunc.h
	lgc.c
	lgc.h
	linit.c
	llex.c
	llex.h
	llimits.h
	lmathlib.c
	lmem.c
	lmem.h
	lobject.c
	lobject.h
	lopcodes.c
	lopcodes.h
	lparser.c
	lparser.h
	lstate.c
	lstate.h
	lstring.c
	lstring.h
	lstrlib.c
	ltable.c
	ltable.h
	ltablib.c
	ltm.c
	ltm.h
	lua.h
	luaconf.h
	lualib.h
	lundump.c
	lundump.h
	lvm.c
	lvm.h
	lzio.c
	lzio.h

$ patch < lua-5.1.5.patch

　Luaの準備は以上です。

　SakuLuaをbuildするには、SDMMC Library for GR-SAKURA と I2C Library for GR-SAKURA が必要です。
　これらをImportした後、buildしてください。

