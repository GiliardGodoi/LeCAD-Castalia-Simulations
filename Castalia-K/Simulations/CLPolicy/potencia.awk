#! usr/bin/awk -f


# funciona se no omnetpp.ini estiver habilitada a opção:
# SN.node[*].Application.collectTraceInfo = true

# Formato esperado do registro no trace:
# 1.265778361932  SN.node[2].Application                   RANDOMICO    2    POTENCIA    -15
BEGIN{
    flag = 1 # flag para marcar qual a repetição que o registro se refere
    anterior = 0.0
}
{
    if( $5 == "POTENCIA" ) {
        tempo = $1
        if(tempo < anterior){
            flag++
        }
        anterior = tempo
        #gsub("\.",",",tempo)

        node = $2
	    gsub(/[^0-9]/,"",node)

        potencia = $6

        print tempo"|"node"|"potencia"|"flag
    }
}
END{

}
