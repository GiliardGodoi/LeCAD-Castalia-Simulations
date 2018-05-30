#!/usr/bin/awk −f
BEGIN{ 
} 
{ 
	if($3 == "Forward"){ 		
		tStr = $2
		gsub(/[^0-9]/,"",tStr)
		print tStr" Forward "$8
	}
}
END{
} 
