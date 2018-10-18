#! /bin/sh

repeticao=30

export repeticao

echo "SIMULAÇÃO P10 RATE 06 A 10"
cp omnetpp.ini  P10Rate6a10/
cd P10Rate6a10/
rm *txt
rm *csv
Castalia -c General,ZigBeeMAC,varyInterferenceModel,comTaxaBuffer,traceFromApp,packetRate6a10,TxPotenciaDez -r $repeticao -o saida.txt

cd ..
echo "FIM SIMULAÇÃO P10"


echo "SIMULAÇÃO P 15 RATE 06 A 10"
cp omnetpp.ini  P15Rate6a10/
cd P15Rate6a10/
rm *txt
rm *csv
Castalia -c General,ZigBeeMAC,varyInterferenceModel,comTaxaBuffer,traceFromApp,packetRate6a10,TxPotenciaQuinze -r $repeticao -o saida.txt

cd ..
echo "FIM SIMULAÇÃO P 15"


echo "SIMULAÇÃO P 20 RATE 06 A 10"
cp omnetpp.ini  P20Rate6a10/
cd P20Rate6a10/
rm *txt
rm *csv
Castalia -c General,ZigBeeMAC,varyInterferenceModel,comTaxaBuffer,traceFromApp,packetRate6a10,TxPotenciaVinte -r $repeticao -o saida.txt

cd ..

echo "FIM SIMULAÇÃO P 20"

echo "SIMULAÇÃO P25 RATE 06 A 10"
cp omnetpp.ini  P25Rate6a10/
cd P25Rate6a10/
rm *txt
rm *csv
Castalia -c General,ZigBeeMAC,varyInterferenceModel,comTaxaBuffer,traceFromApp,packetRate6a10,TxPotenciaVinteECinco -r $repeticao -o saida.txt

cd ..
echo "FIM SIMULAÇÃO"


echo "fim"


./executar.2.sh
