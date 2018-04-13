#!/bin/bash

cont=0
#echo $cont

csplit -k -f simula Castalia-Trace.txt "/CollisionModel00/" {99}

for i in $(ls simula*); do
	arquivo="dados$cont.txt"
#	echo $arquivo
	cont=$(expr $cont + 1)
	awk -f limpa1.awk $i > $arquivo
done
