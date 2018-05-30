#!/usr/bin/awk −f
BEGIN{ 
} 

{ 

	if($3 == "ModelCollision"){ 
		print $4		 
	}

	if($3 == "Pacotesrecebidos"){
		print $4" "$7" "$5" "$9
	}

	if($4 == "prioridade"){
		tStr = $2
		gsub(/[^0-9]/,"",tStr)	
		print tStr" "$4" "$6
	}

}
END{
} 
