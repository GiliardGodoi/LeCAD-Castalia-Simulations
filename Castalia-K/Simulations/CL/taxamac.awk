#!/usr/bin/awk −f
BEGIN{
} 
{ 
	if($3 == "Janela"){ 
		tStr = $2
		gsub(/[^0-9]/,"",tStr)
		print tStr"\t"$5
	}	
}
END{
} 
