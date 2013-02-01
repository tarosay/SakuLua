--Multi Lines Run
repeat k=Serial.read() until(k<0)
Serial.println("Input end with [Ctrl-z]")
m=""
while(true)do
	repeat
		k = Serial.read()
	until(k>0)
	if(k==26)then break end
	if(k==8)then
		m=m:sub(1,m:len()-1)
	else
		m=m..string.format("%c",k)
	end
	Serial.print(string.format("%c",k))
end
Serial.print("\n")
if(m:len()==0)then
	Serial.println("\n loader.lua Running...")
	sys.setrun("loader.lua")
else
	m = m:gsub("^%s*(.-)%s*$", "%1")
	SD.open( 0, "linesrus.lua", 2 )
	SD.write(0, m, m:len())
	m=";if(a~=nil)then Serial.println(a) end;"
	SD.write(0, m, m:len())
	SD.close(0) 
	sys.setrun("linesrus.lua")
end
