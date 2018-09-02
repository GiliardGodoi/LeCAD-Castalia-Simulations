#!/usr/bin/awk −f
BEGIN{ 
} 

{ 
#	tStr = $5

#	sub("#","",tStr)

	if($3 == "Valor"){ 
		tStr = $2
		gsub(/[^0-9]/,"",tStr)
		print tStr" "$6;
	}
}
END{
} 
