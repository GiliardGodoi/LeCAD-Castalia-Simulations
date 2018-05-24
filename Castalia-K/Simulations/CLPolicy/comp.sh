#!/bin/sh

rm *.txt
rm *.csv
echo "Iniciando a simulação\n"

#Castalia -c ZigBeeMAC,General,setRate,varyInterferenceModel -r 1 -o saida.txt
Castalia -c ZigBeeMAC,General,setRate,setInterferenceModel,traceFromApp -r 100 -o saida.txt

echo "EXECUTANDO awk\n"

echo "Coletando taxa MAC..."
awk -f taxamac.awk Castalia-Trace.txt > dataTaxaMacFromAppLayer.csv
echo "Coletando dados da potencia..."
awk -f random.awk Castalia-Trace.txt > dataRandomNumberFromAppLayer.csv
echo "Coletando dados dos numeros randomicos..."
awk -f potencia.awk Castalia-Trace.txt > dataPowerFromAppLayer.csv
echo "\n\n"
echo "FIM DA SIMULAÇÃO"
