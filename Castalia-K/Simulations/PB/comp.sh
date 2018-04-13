#!/bin/sh

rm *.txt

Castalia -c General -r 3 -o saida.txt
#Castalia -c BaselineMAC,General,setRate,setPower,varyInterferenceModel,setPotencia1 -r 3 -o saida.txt
# CastaliaResults -i saida.txt -s packet -n
# CastaliaResults -i saida.txt -s received -n -o 2 > temp.txt
