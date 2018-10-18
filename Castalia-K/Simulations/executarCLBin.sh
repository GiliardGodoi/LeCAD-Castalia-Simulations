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

repeticao=30

echo "SIMULAÇÃO CL Binomial Sem Tentativa Sem Buffer"
mkdir CLBinSemTentativaSemBuffer
cp omnetpp.ini  CLBinSemTentativaSemBuffer/
cd CLBinSemTentativaSemBuffer/
rm *txt
rm *csv
Castalia -c General,ZigBeeMAC,AppCLBin,varyInterferenceModel,semMudancaTentativa,semTaxaBuffer,traceFromApp,packetRatePozza2015,TxPotenciaDez -r $repeticao  -o saida.txt
listar_dados
executar_awk
cd ..
echo "...fim simulação"

echo "SIMULAÇÃO CL Binomial Com Tentativa Sem Buffer"
mkdir CLBinComTentativaSemBuffer
cp omnetpp.ini  CLBinComTentativaSemBuffer/
cd CLBinComTentativaSemBuffer/
rm *txt
rm *csv
Castalia -c General,ZigBeeMAC,AppCLBin,varyInterferenceModel,comMudancaTentativa,semTaxaBuffer,traceFromApp,packetRatePozza2015,TxPotenciaDez -r $repeticao  -o saida.txt
listar_dados
executar_awk
cd ..
echo "...fim simulação"


echo "SIMULAÇÃO CL Binomial Com Tentativa Com Buffer"
mkdir CLBinComTentativaComBuffer
cp omnetpp.ini  CLBinComTentativaComBuffer/
cd CLBinComTentativaComBuffer/
rm *txt
rm *csv
Castalia -c General,ZigBeeMAC,AppCLBin,varyInterferenceModel,comMudancaTentativa,comTaxaBuffer,traceFromApp,packetRatePozza2015,TxPotenciaDez -r $repeticao  -o saida.txt
listar_dados
executar_awk
cd ..
echo "...fim simulação"