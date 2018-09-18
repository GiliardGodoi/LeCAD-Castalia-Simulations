#! /bin/sh

plot_packet_breakdown()
{
    CastaliaResults -i saida.txt -s "packet break" -n -p | CastaliaPlot -o packet-breakdown.png -s stacked -l "outside width-7" --yrange 1.05 --order-columns 1,2,3,4 --colors dg,g,r,pi,b --xrotate 90    
}

plot_latency()
{
    CastaliaResults -i saida.txt -s latency  | CastaliaPlot -o latency.png -l outside --xrotate 90 -s histogram
}


cd P10/
# ./comp.sh
plot_packet_breakdown
plot_latency
python ../../pyscripts/bufferData.py 
cd ..

cd P15/
# ./comp.sh
plot_packet_breakdown
plot_latency
python ../../pyscripts/bufferData.py 
cd ..

cd P20/
# ./comp.sh
plot_packet_breakdown
plot_latency
python ../../pyscripts/bufferData.py 
cd ..

cd P25/
# ./comp.sh
plot_packet_breakdown
plot_latency
python ../../pyscripts/bufferData.py 
cd ..



echo "fim"
