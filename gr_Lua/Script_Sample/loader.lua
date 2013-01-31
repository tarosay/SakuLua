----LuaLoader
fm=""
Serial.print("\nInput Lua filename>")
while(true)do
	repeat 
		k = Serial.read()
	until(k>0)
	if(k==10)then break end
	fm=fm..string.format("%c",k)
	Serial.print(string.format("%c",k))
end
fm = fm:gsub("^%s*(.-)%s*$", "%1")
Serial.println("\nFilename:["..fm.."]")

fp = 0
SD.open( fp, fm, 2 )
SD.write( fp, "--"..fm.."\n", fm:len()+3 )
eflg=0
while(true)do
	t=millis()+1000
	repeat 
		k = Serial.read()
		if(t<millis())then
			Serial.println("Close?(Enter)")
			repeat 
				l = Serial.read()
			until(l>0)
			if(l==10)then
				eflg = 1
				break
			else
				k=l
			end
			t=millis()+1000
		end
		if(k==0)then k=10 end
	until(k>0)
	if(eflg==1)then break end
	SD.write( fp, string.format("%c",k), 1 )
	Serial.print(string.format("%c",k))
end
SD.close( fp ) 
sys.setrun(fm)
