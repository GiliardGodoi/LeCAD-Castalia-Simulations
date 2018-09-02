#!/usr/bin/awk −f
BEGIN{
# print total
a=0 
interferencia[1]=0
interferencia[2]=0
interferencia[3]=0
interferencia[4]=0
interferencia[5]=0
semInterferencia[1]=0
semInterferencia[2]=0
semInterferencia[3]=0
semInterferencia[4]=0
semInterferencia[5]=0
} 
{ 
	if($3 == "Pacotestransmitidos"){ 		
		tStr = $2
		gsub(/[^0-9]/,"",tStr)
		if(tStr=="0"){
			a=a+1
#			print a 
		}else if(a<=total){
			semInterferencia[tStr]=semInterferencia[tStr]+$6			
			}else{
				interferencia[tStr]=interferencia[tStr]+$6
			}
	}
}
END{
	for(i=1;i<=5;i++)
		print i" "semInterferencia[i]/total
	
	for(i=1;i<=5;i++)
		print i" "interferencia[i]/total
} 
