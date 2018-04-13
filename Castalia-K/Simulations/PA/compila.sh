#!/bin/sh

vezes=3

if [ $# != 0 ]; then
	vezes=$1
fi

# echo $vezes

rm *.txt

# Castalia -c ZigBeeMAC,allNodesVaryPower,General,[GTSoff,GTSon] -o saida.txt
# Castalia -c ZigBeeMAC,allNodesVaryRate,General -o saida.txt
#Castalia -c ZigBeeMAC,General,LimitesSup,LimitesInf,varyReTxNum,allNodesVaryPower -o saida.txt
#Castalia -c ZigBeeMAC,General,NodesPower,RateNodesLow -r 5 -o saida.txt
#Castalia -c ZigBeeMAC,General,setRate,setPower,setInterferenceModel,taxasPacotes,taxasCCA,taxasCCA2,varyJanelas -r 11 -o saida.txt
Castalia -c ZigBeeMAC,General,setRate,varyInterferenceModel -r $vezes -o saida$(date +%d%m%y).ttt
CastaliaResults -i saida$(date +%d%m%y).ttt -s packet -n -o 2 > temp.txt
awk -f pegaDados.awk temp.txt > temp2.txt
awk -v total="$vezes" -f pegaSoma.awk Castalia-Trace.txt >> temp2.txt
sed "s/\./,/g" temp2.txt > temp$(date +%d%m%y).fim
#CastaliaResults -i saida.txt -s received -n
#CastaliaResults -i saida.txt -s packet -n -o 2
# CastaliaResults -i saida.txt -s received -n -o 2 > temp.txt
# cp saida.txt /home/pozza/Dropbox
echo "FIM CL"
