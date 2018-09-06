#!/bin/sh

rm *.txt

Castalia -c ZigBeeMAC,General,setRate,setInterferenceModel,setPower,setJanela -r 1 -o saida.txt

# para usar o arquivo mostra-taxaMAC.awk
# awk -f mostra-taxaMAC.awk Castalia-Trace.txt 
