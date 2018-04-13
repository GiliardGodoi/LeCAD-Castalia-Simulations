#!/usr/bin/awk −f
BEGIN{
print "Dados recebidos"
} 
{ 
	if($3 == "received" && $5 == "humidity"){ 
		print $1"\t"$4"\t"$6
	}	
}
END{
} 
