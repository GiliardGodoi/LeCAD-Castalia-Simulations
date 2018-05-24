#! usr/bin/awk -f

# Script utilizado para obter os dados da taxaMAC informada na camada de Aplicação
# funciona se no omnetpp.ini estiver habilitada a opção:
# SN.node[*].Application.collectTraceInfo = true

# Formato esperado do registro no trace
# 1.234842480149  SN.node[4].Communication.MAC             TAXAMAC 40
BEGIN{
    flag = 1 # flag para marcar qual a repetição que o registro se refere
    anterior = 0.0
}
{
    if( $3 == "TAXAMAC" ) {
        tempo = $1
        if(tempo < anterior){
            flag++
        }
        anterior = tempo
        #gsub("\.",",",tempo)

        node = $2
	    gsub(/[^0-9]/,"",node)

        taxaMAC = $4

        print tempo"|"node"|"taxaMAC"|"flag
    }
}
END{

}
