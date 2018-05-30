#!/usr/bin/awk −f
BEGIN{
} 
{ 
	if($5 == "RSSI"){ 
		print $1"\t"$4"\t"$6"\t"$8
	}	
}
END{
} 
