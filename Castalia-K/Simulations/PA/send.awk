#!/usr/bin/awk −f
BEGIN{ 
	t1=0;

} 

{ 
	tStr = $2
	gsub(/[^0-9]/,"",tStr)
	
	if($3 == "Sending" && tStr == "4"){ 
		t1++	
	}
}
END{
	print " Total enviados "t1
} 
