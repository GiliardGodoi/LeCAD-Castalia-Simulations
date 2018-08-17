#!/bin/sh

rm *.txt

Castalia -c ZigBeeMAC,General,setRate,setInterferenceModel,setPower -r 1 -o saida.txt

