----Calc
sys.setrun("calc.lua")
while(true)do
	Serial.print(">")
	m=""
	while(true)do
		repeat 
			k = Serial.read()
		until(k~=-1)
		if(k==10)then break end
		if(k==8)then
			m=m:sub(1,m:len()-1)
		else
			m=m..string.format("%c",k)
		end
		Serial.print(string.format("%c",k))
	end
	if(m:len()==0)then break end
	m = m:gsub("^%s*(.-)%s*$", "%1")
	ans = loadstring( "return {"..m.."}" )()[1]
	if(ans~=nill)then
		Serial.println("\n"..ans)
	else
		Serial.println("")
	end
end
Serial.println("\n loader.lua Running...")
sys.setrun("loader.lua")
