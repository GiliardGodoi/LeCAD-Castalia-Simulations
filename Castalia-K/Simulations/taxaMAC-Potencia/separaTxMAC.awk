#!/usr/bin/awk −f
BEGIN{ 
	anterior = 1.0
} 


{ 

		
	if($3 == "Janela"){
		tStr = $2
		gsub(/[^0-9]/,"",tStr)
		print tStr" "$5
		atual = $1
		if(atual < anterior)
			print "="
		anterior = atual
	}
}

END{

} 

