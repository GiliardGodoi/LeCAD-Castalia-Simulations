#! usr/bin/awk -f

#6.749769952772	SN.node[2].Application                   RANDOMICO    2    POTENCIA    -15
BEGIN{
    flag = 1 # flag para marcar qual a repetição que os dados se referem
    anterior = 0.0
    print "Tempo|Nó sensor|TaxaMAC|Buffer|Repeticao"
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