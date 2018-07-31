#! usr/bin/awk -f

# Utilizado para capturar os dados da taxa MAC que é informado no trace da camada MAC
# funciona se no omnetpp.ini estiver habilitada a seguinte opção:
# SN.node[*].Communication.MAC.collectTraceInfo = true

# Formato esperado do trace:
# 1.234842480149  SN.node[4].Communication.MAC             Janela MAC 40
BEGIN{
    flag = 1 # flag para marcar qual a repetição que os dados se referem
    anterior = 0.0
}
{
    if( $3 == "Janela" ) {
        tempo = $1
        if(tempo < anterior){
            flag++
        }
        anterior = tempo
        #gsub("\.",",",tempo)

        node = $2
	gsub(/[^0-9]/,"",node)

        taxaMAC = $5
        print tempo"|"node"|"taxaMAC"|"flag
    }
}
END{

}
