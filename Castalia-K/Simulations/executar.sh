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

listar_dados_all()
{
    CastaliaResults -i saida.txt -s "Packet Breakdown" -n -p -o2 --all > packet_breakdown_all.txt
    CastaliaResults -i saida.txt -s "Packets reception rate" -n -p -o2 --all > packets_reception_rate_all.txt
    CastaliaResults -i saida.txt -s "Packets received per node" -n -p -o2 --all > packets_received_per_node_all.txt
    CastaliaResults -i saida.txt -s "Packets loss rate" -n -p -o2 --all > packets_loss_rate_all.txt

    CastaliaResults -i saida.txt -s "Estimated network lifetime" -p -o2 > estimated_network_lifetime.txt
    CastaliaResults -i saida.txt -s "Energy nJ/bit" -n -p -o2 --all > energy_NJ_per_bit_all.txt
    CastaliaResults -i saida.txt -s "Consumed Energy" -n -p -o2 --all > energy_consumed_all.txt
    CastaliaResults -i saida.txt -s "Remaining Energy" -n -p -o2 --all > energy_remaining_all.txt
}

repeticao=3

# for estrategia in CLBinomial CL2 CL4 PA PB
# do
#     for taxa[setRateLow,setRateMedium,setRateHigh] in setRateLow setRateMedium
#     do
#         diretorio=$estrategia$taxa
#         echo  "Executando simulação $diretorio "
#     done
# done

echo "SIMULAÇÃO CL Binomial"
mkdir CLBinomial
cp omnetpp.ini  CLBinomial/
cd CLBinomial/
Castalia -c General,CLBinomial,varyInterferenceModel,collectTrace[setRateLow,setRateMedium,setRateHigh] -r $repeticao  -o saida.txt
listar_dados
listar_dados_all
cd ..
echo "...fim simulação"


echo "SIMULAÇÃO CL CL4"
mkdir CL4
cp omnetpp.ini  CL4/
cd CL4/
Castalia -c General,CL4,varyInterferenceModel,collectTrace[setRateLow,setRateMedium,setRateHigh] -r $repeticao  -o saida.txt
listar_dados
listar_dados_all
cd ..
echo "...fim simulação"

echo "SIMULAÇÃO CL CL2"
mkdir CL2
cp omnetpp.ini  CL2/
cd CL2/
Castalia -c General,CL2,varyInterferenceModel,collectTrace[setRateLow,setRateMedium,setRateHigh] -r $repeticao  -o saida.txt
listar_dados
listar_dados_all
cd ..
# echo "...fim simulação"

echo "SIMULAÇÃO PA"
mkdir PA
cp omnetpp.ini  PA/
cd PA/
Castalia -c General,PA,varyInterferenceModel,collectTrace[setRateLow,setRateMedium,setRateHigh] -r $repeticao  -o saida.txt
listar_dados
listar_dados_all
cd ..
echo "...fim simulação"

echo "SIMULAÇÃO PB"
mkdir PB
cp omnetpp.ini  PB/
cd PB/
Castalia -c General,PB,varyInterferenceModel,collectTrace[setRateLow,setRateMedium,setRateHigh] -r $repeticao  -o saida.txt
listar_dados
listar_dados_all
cd ..
echo "...fim simulação"
