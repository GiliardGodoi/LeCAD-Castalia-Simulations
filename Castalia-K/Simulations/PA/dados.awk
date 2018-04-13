#!/usr/bin/awk −f
BEGIN{
print "Dados enviados"
} 

{ 
	if($3 == "Send" && $5 == "humidity"){ 
		tStr = $4
		gsub(/[^0-9]/,"",tStr)
		split($1, array, ".") 
		print $1"\t"tStr"\t"$6
	}	
}
END{
} 
