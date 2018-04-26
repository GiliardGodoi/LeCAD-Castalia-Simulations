#!/bin/sh

rm *.txt

#Castalia -c ZigBeeMAC,General,setRate,varyInterferenceModel -r 33 -o saida.txt
#Castalia -c ZigBeeMAC,General,setRate,setInterferenceModel -r 1 -o saida.txt
#Castalia -c ZigBeeMAC,General,setRate,setInterferenceModel,diffPolicyAndPowerRange -r 1 -o saida.txt
#Castalia -c ZigBeeMAC,General,setRate,setInterferenceModel,setPolicyAndPowerRangeOk -r 1 -o saida.txt
Castalia -c ZigBeeMAC,General,setRate,setInterferenceModel,setPowerRangeDiffPolicy -r 1 -o saida.txt

CastaliaResults -i saida.txt -s packets -n -o2 > packets.txt
CastaliaResults -i saida.txt -s energy -n -o2 > energy.txt
CastaliaResults -i saida.txt -s breakdown -n -o2 > breakdown.txt
