#!/bin/sh
# apaga arquivos anteriores
rm simulacao-no*
rm temp.txt

# Separar os valores de taxaMAC por simulação 
# Utiliza um sinal de "=" para indicar o final da simulacao
awk -f separaTxMAC.awk Castalia-Trace.txt | sort > temp.txt

# Separa os arquivos por simulacao utilizando o sinal de "="
# Serao gerados o numero de arquivos da repeticao das simulacoes
#csplit -f simulacao. temp.txt "/=/" {100} -k

# Ordena os arquivos separados por no sensor
#cont=1
#for i in $(ls simulacao.*);
#do	
#	sort $i > simulacao$cont.txt
#	cont=$(($cont+1))
#done
# Apaga os arquivos comecados por simulacao.* porque não vai usar mais
#rm simulacao.*

# Separa os arquivos por no sensor
# simulacao-Taxa-Potencia-Janela-Colisao-tempo
#cont=1
#for i in $(ls simulacao*);
#do
	echo item: $i
	for j in $(seq 5);
	do
		echo $j
		sed -n /$j' /{p}' temp.txt > simulacao-5-15-40-10-3000-no$j.txt
	done
	#cont=$(($cont+1))
#done

