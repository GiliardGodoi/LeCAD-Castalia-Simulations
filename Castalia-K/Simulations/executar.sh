#! /bin/sh

executar_awk()
{
    awk -f ../../awks/bufferData.awk Castalia-Trace.txt > bufferData.csv
    awk -f ../../awks/APPtaxaMAC.awk Castalia-Trace.txt > taxaMACData.csv
}

listar_dados()
{
    CastaliaResults -i saida.txt -s "Packet Breakdown" -n -p -o2 > packet_breakdown.txt
    CastaliaResults -i saida.txt -s "Packets reception rate" -n -p -o2 > packets_reception_rate.txt
    CastaliaResults -i saida.txt -s "Packets received per node" -n -p -o2 > packets_received_per_node.txt
    CastaliaResults -i saida.txt -s "Packets loss rate" -n -p -o2 > packets_loss_rate.txt

    CastaliaResults -i saida.txt -s "Estimated network lifetime" -p -o2 > estimated_network_lifetime.txt
    CastaliaResults -i saida.txt -s "Energy nJ/bit" -n -p -o2 > energy_NJ_per_bit.txt
    CastaliaResults -i saida.txt -s "Consumed Energy" -n -p -o2 > energy_consumed.txt
    CastaliaResults -i saida.txt -s "Remaining Energy" -n -p -o2 > energy_remaining.txt
}

repeticao=3

# for estrategia in CLBinomial CL2 CL4 PA PB
# do
#     for taxa in setRateLow setRateMedium setRateHigh
#     do
#         diretorio=$estrategia$taxa
#         echo  "Executando simulação $diretorio "
#     done
# done

# echo "SIMULAÇÃO CL Binomial"
# mkdir CLBinomial
# cp omnetpp.ini  CLBinomial/
# cd CLBinomial/
# Castalia -c General,CLBinomial,setRateHigh,varyInterferenceModel,collectTrace -r $repeticao  -o saida.txt
# listar_dados
# cd ..
# echo "...fim simulação"


# echo "SIMULAÇÃO CL CL4"
# mkdir CL4
# cp omnetpp.ini  CL4/
# cd CL4/
# Castalia -c General,CL4,setRateHigh,varyInterferenceModel,collectTrace -r $repeticao  -o saida.txt
# listar_dados
# cd ..
# echo "...fim simulação"

# echo "SIMULAÇÃO CL CL2"
# mkdir CL2
# cp omnetpp.ini  CL2/
# cd CL2/
# Castalia -c General,CL2,setRateHigh,varyInterferenceModel,collectTrace -r $repeticao  -o saida.txt
# listar_dados
# cd ..
# echo "...fim simulação"

echo "SIMULAÇÃO PA"
mkdir PA
cp omnetpp.ini  PA/
cd PA/
Castalia -c General,PA,setRateHigh,varyInterferenceModel,collectTrace -r $repeticao  -o saida.txt --debug
listar_dados
cd ..
echo "...fim simulação"

echo "SIMULAÇÃO PB"
mkdir PB
cp omnetpp.ini  PB/
cd PB/
Castalia -c General,PB,setRateHigh,varyInterferenceModel,collectTrace -r $repeticao  -o saida.txt --debug
listar_dados
cd ..
echo "...fim simulação"
