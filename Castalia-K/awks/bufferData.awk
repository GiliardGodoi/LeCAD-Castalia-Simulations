#!/usr/bin/awk −f

# Analisa o log do arquivo Castalia-Trace.txt. 
# Caputa os dados referente à ocupação do buffer dos nós sensores.
# Filtra os registros para BUFFER_INFO

# Formato esperado do trace:
#12.606478786238     SN.node[5].Application                   BUFFER_INFO    3.125    POTENCIA    -25\n
BEGIN{
    iteration = 1
    previous = 0

    print "Tempo|Nó sensor|Taxa Buffer|Potencia|Repetição"
}
{
    if($3 == "BUFFER_INFO"){
        node = $2
        gsub(/[^0-9]/,"",node)

        time = $1
        if(time < previous){
            iteration++
        }
        previous = time
        
        bufferRate = $4
        potencia = $6

        print time"|"node"|"bufferRate"|"potencia"|"iteration
    }
}
END{

}