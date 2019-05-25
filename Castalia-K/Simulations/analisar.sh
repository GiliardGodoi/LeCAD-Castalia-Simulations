#!/bin/sh

plot_latency()
{
    for rate in $@
    do
        CastaliaResults -i saida.txt -s latency -f packetRate=$rate | CastaliaPlot -o latency-R$rate.png -l outside --xrotate 90 -s histogram
    done
    
}

plot_packet_breakdown()
{
    # CastaliaResults -i saida.txt -s "packet break" -n -p | CastaliaPlot -o packet-breakdown.png -s stacked -l "outside width-7" --yrange 1.05 --order-columns 1,2,3,4 --colors dg,g,r,pi,b --xrotate 90    
    for rate in $@
    do
        CastaliaResults -i saida.txt -s "packet break" -n -p -f InterfModel=0,packetRate=$rate | CastaliaPlot -o packet-breakdown-R$rate-interf0.png -s stacked -l "outside width-7" --yrange 1.05 --xrotate 90
        CastaliaResults -i saida.txt -s "packet break" -n -p -f InterfModel=1,packetRate=$rate | CastaliaPlot -o packet-breakdown-R$rate-interf1.png -s stacked -l "outside width-7" --yrange 1.05 --xrotate 90
        CastaliaResults -i saida.txt -s "packet break" -n -p -f InterfModel=1,packetRate=$rate | CastaliaPlot -o packet-breakdown-R$rate-interf2.png -s stacked -l "outside width-7" --yrange 1.05 --xrotate 90
    done
}

plot_reception_rate()
{
    CastaliaResults -i saida.txt  -s 'reception' | CastaliaPlot -o reception-rate.png
    CastaliaResults -i saida.txt  -s 'reception' | CastaliaPlot -o reception-rate-hist.png -s histogram
}

plot_buffer_overflow()
{
    CastaliaResults -i saida.txt  -s 'packet break' -p --filter-columns buffer -n | CastaliaPlot -o buffer-overflow.png --invert -s histogram
}

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

for diretorio in  P10Rate6a10 P15Rate6a10 P20Rate6a10 P25Rate6a10
do
    cd $diretorio
    echo $diretorio
    executar_awk
    listar_dados
    # plot_latency 6 7 8 9 10
    # plot_packet_breakdown 6 7 8 9 10
    # plot_reception_rate
    # plot_buffer_overflow
    cd ../
done

for diretorio in P10Rate11a15 P15Rate11a15 P20Rate11a15 P25Rate11a15
do
    cd $diretorio
    echo $diretorio
    executar_awk
    listar_dados
    # plot_latency 11 12 13 14 15
    # plot_packet_breakdown 11 12 13 14 15
    # plot_reception_rate
    # plot_buffer_overflow
    cd ../
done

for diretorio in P10Rate16a20 P15Rate16a20 P20Rate16a20 P25Rate16a20
do
    cd $diretorio
    echo $diretorio
    executar_awk
    listar_dados
    # plot_latency 16 17 18 19 20
    # plot_packet_breakdown 16 17 18 19 20
    # plot_reception_rate
    # plot_buffer_overflow
    cd ../
done

for diretorio in P10Rate21a25 P15Rate21a25 P20Rate21a25 P25Rate21a25
do
    cd $diretorio
    echo $diretorio
    executar_awk
    listar_dados
    # plot_latency 21 22 23 24 25
    # plot_packet_breakdown 21 22 23 24 25
    # plot_reception_rate
    # plot_buffer_overflow
    cd ../
done

shutdown