#!/bin/sh

rm *.txt
rm *.csv

echo "Executando simulação\n"
# Castalia -c General -r 3 -o saida.txt
# Castalia -c BaselineMAC,General,setRate,setPower,varyInterferenceModel,setPotencia1 -r 3 -o saida.txt
# CastaliaResults -i saida.txt -s packet -n
# CastaliaResults -i saida.txt -s received -n -o 2 > temp.txt

Castalia -c General,ZigBeeMAC,setRate,setInterferenceModel,traceFromMac -r 100 -o saida.txt
#Castalia -c General,ZigBeeMAC,setRate,varyInterferenceModel,traceFromApp,traceFromMac -r 1 -o saida.txt

echo "EXECUTANDO awk\n"
# awk -f janelaMAC.awk Castalia-Trace.txt > dataTaxaMacFromMacLayer.csv
# awk -f taxamac.awk Castalia-Trace.txt > dataTaxaMacFromAppLayer.csv

awk -f ../../awks/buffer.awk Castalia-Trace.txt > bufferData.csv
awk -f ../../awks/janelaMAC.awk Castalia-Trace.txt > taxaMACData.csv

# echo "CAPTURANDO DADOS CastaliaResults\n"

# CastaliaResults -i saida.txt -s "Packet Breakdown" -n --all -o2 > packet_breakdown.txt
# CastaliaResults -i saida.txt -s "Packets reception rate" -n --all -o2 > packets_reception_rate.txt
# CastaliaResults -i saida.txt -s "Packets received per node" -n --all -o2 > packets_received_per_node.txt
# CastaliaResults -i saida.txt -s "Packets loss rate" -n --all -o2 > packets_loss_rate.txt

# CastaliaResults -i saida.txt -s "Estimated network lifetime" --all -o2 > estimated_network_lifetime.txt
# CastaliaResults -i saida.txt -s "Energy nJ/bit" -n --all -o2 > energy_NJ_per_bit.txt
# CastaliaResults -i saida.txt -s "Consumed Energy" -n --all -o2 > energy_consumed.txt
# CastaliaResults -i saida.txt -s "Remaining Energy" -n --all -o2 > energy_remaining.txt


echo "FIM DA SIMULAÇÃO P-15"