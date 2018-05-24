#!/bin/sh

rm *.txt
rm *.csv

echo "Executando simulação\n"
# Castalia -c General -r 3 -o saida.txt
# Castalia -c BaselineMAC,General,setRate,setPower,varyInterferenceModel,setPotencia1 -r 3 -o saida.txt
# CastaliaResults -i saida.txt -s packet -n
# CastaliaResults -i saida.txt -s received -n -o 2 > temp.txt

Castalia -c General,ZigBeeMAC,setRate,setInterferenceModel,traceFromApp,traceFromMac -r 100 -o saida.txt

echo "EXECUTANDO awk\n"
awk -f janelaMAC.awk Castalia-Trace.txt > dataTaxaMacFromMacLayer.csv
awk -f taxamac.awk Castalia-Trace.txt > dataTaxaMacFromAppLayer.csv

echo "FIM DA SIMULAÇÃO PA"