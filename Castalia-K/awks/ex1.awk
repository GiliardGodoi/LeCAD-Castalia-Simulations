#!/usr/bin/awk −f
BEGIN{ 
} 

{ 

	if($3 == "ModelCollision"){ 
		print $4		 
	}


	if($3 == "SpentEnergy"){
		tStr = $2
		gsub(/[^0-9]/,"",tStr)	
		print tStr" "$4" "$6
	}

}
END{
} 
