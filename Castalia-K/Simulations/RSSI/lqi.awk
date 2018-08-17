#!/usr/bin/awk −f
BEGIN{ 
} 

{ 

	if($4 == "recebido"){ 
		tStr = $2
		gsub(/[^0-9]/,"",tStr)
		print tStr"\t"$7;
	}

}
END{
} 
