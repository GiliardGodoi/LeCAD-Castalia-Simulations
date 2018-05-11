#!/bin/sh

rm *.txt

#Castalia -c ZigBeeMAC,General,setRate,varyInterferenceModel -r 1 -o saida.txt
Castalia -c ZigBeeMAC,General,setRate,setInterferenceModel -r 1 -o saida.txt



