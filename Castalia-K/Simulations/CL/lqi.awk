#!/usr/bin/awk −f
BEGIN{ 
} 

{ 
#	tStr = $5

#	sub("#","",tStr)

	if($9 == "RSSI"){ 
		tStr = $5
		rStr = $1
		sStr = $10
		sub("#","",tStr)
		sub(/\./,",",rStr)
		sub(/\./,",",sStr)
		print rStr" "sStr" "tStr;
	}
}
END{
} 
