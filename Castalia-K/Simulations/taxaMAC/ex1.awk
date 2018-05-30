#!/usr/bin/awk −f
BEGIN{ 
} 

{ 

	#if($3 == "ack1"){ 
	#	print $1"\t"$4		 
	#}

	if($3 == "Janela"){ 
		print $5		 
	}

}
END{
} 
