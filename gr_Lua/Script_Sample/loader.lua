--LuaLoader
fm=""
while(true)do
	repeat 
		k = Serial.read()	--文字入力があるまで待つ
	until(k~=-1)
	if(k==10)then break end
	fm=fm..string.format("%c",k)
	Serial.print(string.format("%c",k))
end
fm = fm:gsub("^%s*(.-)%s*$", "%1")	--トリミング
Serial.println("\nFilename:["..fm.."]")

fp = 0
SD.open( fp, fm, 2 ) --新規書き込みオープン
SD.write( fp, "--"..fm.."\n", fm:len()+3 )
eflg=0
while(true)do
	t=millis()+1000
	repeat 
		k = Serial.read()	--文字入力があるまで待つ
		if(t<millis())then
			Serial.println("Contimue?(y/n)")
			repeat 
				l = Serial.read()	--文字入力があるまで待つ
			until(l~=-1)
			if(l==110)then
				eflg = 1
				break
			end
			t=millis()+1000
		end
	until(k~=-1)
	if(eflg==1)then break end
	
	SD.write( fp, string.format("%c",k), 1 )
end
SD.close( fp ) 
pinMode(100,1)
digitalWrite(100,1)	--LEDを点ける
SD.open(fp, fm) 
while(true)do
	k=SD.read(fp)
	if(k==-1)then break end
	Serial.print(string.format("%c",k))
end
SD.close( fp ) 
sys.setrun(fm)
