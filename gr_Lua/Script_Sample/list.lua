p = {
" "
,"--GR-SAKURA TEST"
,"PIN_LED0 = 100"
,"PIN_LED1 = 101"
,"PIN_LED2 = 102"
,"PIN_LED3 = 103"
,"PIN_SW = 105"
,"INPUT = 0"
,"LOW =  0"
,"HIGH = 1"
,"Z = 0"
,'s0 = "Make Fair '
,'s1 = "Lua Script'
,'s2 = "Blue Switc'
,"Lcd.write( s1, 1"
,"pinMode( PIN_LED"
,"pinMode( PIN_LED"
,"pinMode( PIN_LED"
,"pinMode( PIN_LED"
,"pinMode( PIN_SW,"
,'Lcd.write( "'
,'Lcd.write( "'
,"Z = 0"
,"function btn(Z)"
,"  if( digitalRe"
,"    Lcd.write( "
,"    Z = 1"
,"  elseif( digit"
,"    Lcd.write( "
,"    Z = 0"
,"  end"
,"  return Z"
,"end"
,"for i=1,50 do"
,"  s0 = string.su"
,"  Lcd.write( s0,"
,"  digitalWrite( "
,"  digitalWrite( "
,"  digitalWrite( "
,"  digitalWrite( "
,"  delay( 20 )"
,"  Z = btn(Z)"
,"  digitalWrite( "
,"  digitalWrite( "
,"  digitalWrite( "
,"  digitalWrite( "
,"  delay( 20 )"
,"  Z = btn(Z)"
,"end"
,'sys.setrun("list'
}
t = ""
for i,txt in pairs(p) do
	Lcd.write( t, 0 )
	Lcd.write( txt, 1 )
	t = txt
	delay( 1000 )
end
sys.setrun("sakulua.lua")
