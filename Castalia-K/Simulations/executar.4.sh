#! /bin/sh

repeticao=30

echo "SIMULAÇÃO P10 RATE 06 A 10"
cp omnetpp.ini  P10Rate21a25/
cd P10Rate21a25/
rm *txt
rm *csv
Castalia -c General,ZigBeeMAC,varyInterferenceModel,comTaxaBuffer,traceFromApp,packetRate21a25,TxPotenciaDez -r $repeticao  -o saida.txt

cd ..
echo "FIM SIMULAÇÃO P10"


echo "SIMULAÇÃO P 15 RATE 06 A 10"
cp omnetpp.ini  P15Rate21a25/
cd P15Rate21a25/
rm *txt
rm *csv
Castalia -c General,ZigBeeMAC,varyInterferenceModel,comTaxaBuffer,traceFromApp,packetRate21a25,TxPotenciaQuinze -r $repeticao -o saida.txt

cd ..
echo "FIM SIMULAÇÃO P 15"


echo "SIMULAÇÃO P 20 RATE 06 A 10"
cp omnetpp.ini  P20Rate21a25/
cd P20Rate21a25/
rm *txt
rm *csv
Castalia -c General,ZigBeeMAC,varyInterferenceModel,comTaxaBuffer,traceFromApp,packetRate21a25,TxPotenciaVinte -r $repeticao -o saida.txt

cd ..

echo "FIM SIMULAÇÃO P 20"

echo "SIMULAÇÃO P25 RATE 06 A 10"
cp omnetpp.ini  P25Rate21a25/
cd P25Rate21a25/
rm *txt
rm *csv
Castalia -c General,ZigBeeMAC,varyInterferenceModel,comTaxaBuffer,traceFromApp,packetRate21a25,TxPotenciaVinteECinco -r $repeticao -o saida.txt

cd ..
echo "FIM SIMULAÇÃO"


echo "fim"


./analisar.sh
