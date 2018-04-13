#!/bin/sh

vezes=3

if [ $# != 0 ]; then
	vezes=$1
fi

rm *.txt

Castalia -c ZigBeeMAC,General,setRate,varyInterferenceModel -r $vezes -o saida$(date +%d%m%y)$vezes.ttt
CastaliaResults -i saida$(date +%d%m%y)$vezes.ttt -s packet -n -o 2 > temp.txt
awk -f pegaDados.awk temp.txt > temp2.txt
awk -v total="$vezes" -f pegaSoma.awk Castalia-Trace.txt >> temp2.txt
sed "s/\./,/g" temp2.txt > temp$(date +%d%m%y)$vezes.fim

cp saida$(date +%d%m%y)$vezes.ttt resultados
cp temp$(date +%d%m%y)$vezes.fim resultados

echo "FIM CL"
