#!/bin/sh

rm *.txt

#Castalia -c ZigBeeMAC,General,setRate,varyInterferenceModel,varyJanela -r 13 -o saida.txt
Castalia -c ZigBeeMAC,General,setRate,setInterferenceModel -r 33 -o saida.txt

