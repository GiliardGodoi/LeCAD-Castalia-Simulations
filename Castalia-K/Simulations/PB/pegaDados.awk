#!/usr/bin/awk −f

function circulo(num) {
	return num%5 ;
}

BEGIN{
linha=0

recebSem[1]=0
recebSem[2]=0
recebSem[3]=0
recebSem[4]=0
recebSem[5]=0

recebCom[1]=0
recebCom[2]=0
recebCom[3]=0
recebCom[4]=0
recebCom[5]=0

}
{
	linha=linha+1
        
	if(linha == 11){
		recebSem[1]=$3
		recebSem[2]=$5
		recebSem[3]=$7
		recebSem[4]=$9
		recebSem[5]=$11
	}

	if(linha == 12){
		recebCom[1]=$3
		recebCom[2]=$5
		recebCom[3]=$7
		recebCom[4]=$9
		recebCom[5]=$11
        }

	if(linha == 23){
		breakdown[1,1]=$3
		breakdown[1,2]=$5
		breakdown[1,3]=$7
		breakdown[1,4]=$9
		breakdown[1,5]=$11
	}
	if(linha == 24){
                breakdown[2,1]=$3
                breakdown[2,2]=$5
                breakdown[2,3]=$7
                breakdown[2,4]=$9
                breakdown[2,5]=$11
        }

	if(linha == 25){
                breakdown[3,1]=$3
                breakdown[3,2]=$5
                breakdown[3,3]=$7
                breakdown[3,4]=$9
                breakdown[3,5]=$11
        }

	if(linha == 26){
                breakdown[4,1]=$3
                breakdown[4,2]=$5
                breakdown[4,3]=$7
                breakdown[4,4]=$9
                breakdown[4,5]=$11
        }

	if(linha == 27){
                breakdown[5,1]=$3
                breakdown[5,2]=$5
                breakdown[5,3]=$7
                breakdown[5,4]=$9
                breakdown[5,5]=$11
        }

	if(linha == 28){
                breakdown[6,1]=$3
                breakdown[6,2]=$5
                breakdown[6,3]=$7
                breakdown[6,4]=$9
                breakdown[6,5]=$11
        }

	if(linha == 29){
                breakdown[7,1]=$3
                breakdown[7,2]=$5
                breakdown[7,3]=$7
                breakdown[7,4]=$9
                breakdown[7,5]=$11
        }

	if(linha == 30){
                breakdown[8,1]=$3
                breakdown[8,2]=$5
                breakdown[8,3]=$7
                breakdown[8,4]=$9
                breakdown[8,5]=$11
        }

	if(linha == 31){
                breakdown[9,1]=$3
                breakdown[9,2]=$5
                breakdown[9,3]=$7
                breakdown[9,4]=$9
                breakdown[9,5]=$11
        
	}	

	if(linha == 32){
                breakdown[10,1]=$3
                breakdown[10,2]=$5
                breakdown[10,3]=$7
                breakdown[10,4]=$9
                breakdown[10,5]=$11
        }

}
END{

	for(i=1;i<=5;i++){
		print i" "recebSem[i]
	}
	for(i=1;i<=5;i++){
		print i" "recebCom[i]
	}
	for(i=0;i<=9;i++){
		print circulo(i)+1" "breakdown[i+1,1]" "breakdown[i+1,2]" "breakdown[i+1,3]" "breakdown[i+1,4]" "breakdown[i+1,5]
	}

}

