#!/bin/sh

rm *.txt


Castalia -c ZigBeeMAC,General,setRate,setInterferenceModel -r 1 -o saida.txt

CastaliaResults -i saida.txt -s breakdown -n -o2 > breakdown.txt
