#! /bin/sh

echo "SIMULAÇÃO P10 RATE 06 A 10"
cp omnetpp.ini  P10Rate11a15/
cd P10Rate11a15/
rm *txt
Castalia -c General,ZigBeeMAC,varyInterferenceModel,comTaxaBuffer,traceFromApp,packetRate11a15,TxPotenciaDez -r $repeticao  -o saida.txt

cd ..
echo "FIM SIMULAÇÃO P10"


echo "SIMULAÇÃO P 15 RATE 06 A 10"
cp omnetpp.ini  P15Rate11a15/
cd P15Rate11a15/
rm *txt
Castalia -c General,ZigBeeMAC,varyInterferenceModel,comTaxaBuffer,traceFromApp,packetRate11a15,TxPotenciaQuinze -r $repeticao -o saida.txt

cd ..
echo "FIM SIMULAÇÃO P 15"


echo "SIMULAÇÃO P 20 RATE 06 A 10"
cp omnetpp.ini  P20Rate11a15/
cd P20Rate11a15/
rm *txt
Castalia -c General,ZigBeeMAC,varyInterferenceModel,comTaxaBuffer,traceFromApp,packetRate11a15,TxPotenciaVinte -r $repeticao -o saida.txt

cd ..
echo "FIM SIMULAÇÃO P 20"

echo "SIMULAÇÃO P25 RATE 06 A 10"
cp omnetpp.ini  P25Rate11a15/
cd P25Rate11a15/
rm *txt
Castalia -c General,ZigBeeMAC,varyInterferenceModel,comTaxaBuffer,traceFromApp,packetRate11a15,TxPotenciaVinteECinco -r $repeticao -o saida.txt
cd ..
echo "FIM SIMULAÇÃO"

echo "fim"

./executar.3.sh