#! usr/bin/awk -f

# Filtra os registros para BUFFER_INFO

# Formato esperado do trace:
#12.606478786238     SN.node[5].Application                   BUFFER_INFO    3.125    POTENCIA    -25\n
BEGIN{
    flag = 1 # flag para marcar qual a repetição que os dados se referem
    anterior = 0.0
}
{
    if( $3 == "BUFFER_INFO" ) {
        # tempo = $1
        # if(tempo < anterior){
        #     flag++
        # }
        # anterior = tempo
        # #gsub("\.",",",tempo)

        # node = $2
	    # gsub(/[^0-9]/,"",node)

        print $0
    }
}
END{

}