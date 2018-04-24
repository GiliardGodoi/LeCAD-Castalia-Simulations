#!/bin/sh

rm *.txt

#Castalia -c ZigBeeMAC,General,setRate,varyInterferenceModel -r 33 -o saida.txt
Castalia -c ZigBeeMAC,General,setRate,setInterferenceModel -r 33 -o saida.txt

CastaliaResults -i saida.txt -s packets -n -o2 > packets.txt
CastaliaResults -i saida.txt -s energy -n -o2 > energy.txt
CastaliaResults -i saida.txt -s breakdown -n -o2 > breakdown.txt

destino="/home/giliard/Documentos/resultado-simulacoes/resultado"

mv *.txt $destino

rm *.txt

Castalia -c ZigBeeMAC,General,setRate,varyInterferenceModel -r 33 -o saida.txt
