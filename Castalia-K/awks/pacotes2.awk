#!/usr/bin/awk −f
BEGIN{
#	if(ARGC<2){
#		print "usage: <command> file nodes" > "/dev/stderr"
#		exit 1
#	}
#	print ARGV[1]"\t" ARGC 
	pacotes=0
	enviados=0	
#	nodes=ARGV[2]
	for(i=1;i<10;i++){
		noS[i,1]=i
		noS[i,2]=0
		noS[i,3]=0
	}
	
} 
{ 
	if($3 == "Received" ){ 
		str=$5
		pacotes++
		gsub(/#/, "",str)
		noS[$8,2]++
	}
	if($3 == "Sending"){
		tStr = $2
		gsub(/[^0-9]/,"",tStr)
		enviados++
		noS[tStr,3]++
	}
	
}
END{
	print "Nos\tEnviados\tRecebidos"
	for(i=1;i<10;i++){
                print  i"\t"noS[i,3]"\t" noS[i,2]
        }
	print "Totais\t"enviados"\t"pacotes
} 
