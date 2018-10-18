#! /bin/sh

repeticao=30

echo "SIMULAÇÃO P10"
cp omnetpp.ini  P10Rate16a20/
cd P10Rate16a20/
Castalia -c General,ZigBeeMAC,varyInterferenceModel,comTaxaBuffer,traceFromApp,packetRate16a20,TxPotenciaDez -r $repeticao  -o saida.txt

cd ..
echo "FIM SIMULAÇÃO P10"


echo "SIMULAÇÃO P 15"
cp omnetpp.ini  P15Rate16a20/
cd P15Rate16a20/
Castalia -c General,ZigBeeMAC,varyInterferenceModel,comTaxaBuffer,traceFromApp,packetRate16a20,TxPotenciaQuinze -r $repeticao -o saida.txt

cd ..
echo "FIM SIMULAÇÃO P 15"


echo "SIMULAÇÃO P 20"
cp omnetpp.ini  P20Rate16a20/
cd P20Rate16a20/
Castalia -c General,ZigBeeMAC,varyInterferenceModel,comTaxaBuffer,traceFromApp,packetRate16a20,TxPotenciaVinte -r $repeticao -o saida.txt

cd ..

echo "FIM SIMULAÇÃO P 20"

echo "SIMULAÇÃO P25"
cp omnetpp.ini  P25Rate16a20/
cd P25Rate16a20/
Castalia -c General,ZigBeeMAC,varyInterferenceModel,comTaxaBuffer,traceFromApp,packetRate16a20,TxPotenciaVinteECinco -r $repeticao -o saida.txt

cd ..
echo "FIM SIMULAÇÃO"


echo "fim"


./executar.4.sh