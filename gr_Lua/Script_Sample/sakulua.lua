--GR-SAKURA TEST
Lcd.write( "SakuLua Ver."..sys.ver(), 0 )
Lcd.write( " ", 1 )
delay( 5000 )
PIN_LED0 = 100
PIN_LED1 = 101
PIN_LED2 = 102
PIN_LED3 = 103
PIN_SW = 105
INPUT = 0
OUTPUT = 1
LOW =  0
HIGH =  1
Z = 0
s0 = "Make Fair Tokyo."
s1 = "Lua Script Now."
s2 = "Blue Switch ON"
Lcd.write( s1, 1 )
pinMode( PIN_LED0,1)
pinMode( PIN_LED1,1)
pinMode( PIN_LED2,1)
pinMode( PIN_LED3,1)
pinMode( PIN_SW, INPUT )
Z = 0
function btn(Z)
	if( digitalRead(PIN_SW)==LOW and Z==0)then
		Lcd.write( s2, 1 )
		Z = 1
	elseif( digitalRead(PIN_SW)==HIGH and Z==1)then
		Lcd.write( s1, 1 )
		Z = 0
	end
	return Z
end
	
for i=1,50 do
	s0 = string.sub( s0, 2 )..string.sub(s0,1,1)
	Lcd.write( s0, 0 )
	digitalWrite( PIN_LED0, HIGH )
	digitalWrite( PIN_LED1, HIGH )
	digitalWrite( PIN_LED2, HIGH )
	digitalWrite( PIN_LED3, HIGH )
	delay( 200 )
	Z = btn(Z)
	digitalWrite( PIN_LED0, LOW )
	digitalWrite( PIN_LED1, LOW )
	digitalWrite( PIN_LED2, LOW )
	digitalWrite( PIN_LED3, LOW )
	delay( 200 )
	Z = btn(Z)
end
sys.setrun("list.lua")
