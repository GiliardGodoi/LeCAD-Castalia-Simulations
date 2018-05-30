#!/usr/bin/awk −f
BEGIN{
	a12 = 0
	a20 = 0 
} 

{ 
#	tStr = $5

#	sub("#","",tStr)

	if($3 == "Aumenta"){ 
		tStr = $2
		gsub(/[^0-9]/,"",tStr)
		if($4 == "12"){a12=a12+1}
		else{a20=a20+1}
		print tStr" "$3" "$4;
	}
	if($4 =="sending"){
		print "a12 = "a12" a20 = "a20
		a12 = 0
		a20 = 0
	}
}
END{
	print "a12 = "a12" a20 = "a20
} 
