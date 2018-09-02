#!/usr/bin/awk −f

function sum(array) {
	s = 0;
		for (i in array) {
			s += array[i];
		}
	return s ;
}


function average ( array ) {
	s = 0;
	items = 0;
	for ( i in array ) {
	s += array [i];
	if (array[i]!= 0.0) 
		items++;
	}
	if (s == 0 || items == 0)
		return 0;
	else
		return s/items ;
}

function max (array) {
	begin=1;
	for (i in array) {
		if (begin || array [i] > largest){
			largest = array [i];
			 begin = 0;

		}
	}
	return largest;
}

function min (array) {
	begin=1;
	for (i in array) {
		if (begin || array [i] < smallest) {
			smallest = array [i];
			begin = 0;
		}
	}
	return smallest;
}



BEGIN{
	j=1;
	for(i=1;i<=100;i++){
		temp[i]=i;
#		printf("temp[%d] = %d\n",i,temp[i]);
	}
#	printf("Soma = %d\n",sum(temp));

}

{
#	printf("Valor - %f\n",$1);
	temp[j++]=$1;
}

END{
	printf("Soma = %f\n",sum(temp));
	printf("Media = %f\n",average(temp));
	printf("Maior = %f\n",max(temp));
	printf("Menor = %f\n",min(temp));
}



