#! usr/bin/awk -f

#6.749769952772	SN.node[2].Application                   TAXAMAC_INFO    80    BUFFER_INFO    0
BEGIN{
    flag = 1 # flag para marcar qual a repetição que os dados se referem
    anterior = 0.0
    print "Tempo|Nó sensor|TaxaMAC|Buffer|Repeticao"
}
{
    if( $3 == "TAXAMAC_INFO" ) {
        tempo = $1
        if(tempo < anterior){
            flag++
        }
        anterior = tempo
        #gsub("\.",",",tempo)

        node = $2
	    gsub(/[^0-9]/,"",node)

        taxaMAC = $4
        buffer = $6

        print tempo"|"node"|"taxaMAC"|"buffer"|"flag
    }
}
END{

}