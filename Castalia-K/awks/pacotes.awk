#!/usr/bin/awk −f
BEGIN{ 
	n2=0
	n3=0
	pacotes=0
	enviados=0	
	encaminhado=0
	for(i=0;i<=3;i++){
		noS[i,1]=i
		noS[i,2]=0
		noS[i,3]=0
		noS[i,4]=0
	}
} 

{ 
	if($3 == "Received" ){ 
		tStr = $2
		gsub(/[^0-9]/,"",tStr)
		pacotes++
		noS[tStr,2]++
	}
	if($3 == "Sending"){
		tStr = $2
		gsub(/[^0-9]/,"",tStr)
		enviados++
		noS[tStr,3]++
	}
	if($3 == "Forward"){
		tStr = $2
		gsub(/[^0-9]/,"",tStr)
		if($8 == 2){
			n2++
		}else{
			n3++
		}
		encaminhado++
		noS[tStr,4]++
	}	
}
END{
	print "pacotes recebidos pelo sink " pacotes
	print "pacotes enviados " enviados
	print "pacotes encaminhados " encaminhado
	for(i=0;i<=3;i++){
                print "No " i " Enviado " noS[i,3] " pacotes, recebido " noS[i,2] ", Encaminhado " noS[i,4]
        }
	print "encaminhados 2 " n2 " e 3 "n3
} 
