#!/usr/bin/awk −f

# Analisa o log do arquivo Castalia-Trace.txt. 
# Caputa os dados referente à ocupação do buffer dos nós sensores.

# O trace analisado se encontra na função bufferPacket da classe Basic802154.
#          trace() << "CurrentBufferState    " << TXBuffer.size();

# Exemple de registro esperado:
# 1.234842480149  SN.node[5].Communication.MAC             CurrentBufferState    17
BEGIN{
    iteration = 1
    previous = 0
}
{
    if($3 == "CurrentBufferState"){
        node = $2
        gsub(/[^0-9]/,"",node)

        time = $1
        if(time < previous){
            iteration++
        }
        previous = time
        
        bufferSize = $4

        print time"|"node"|"bufferSize"|"iteration
    }
}
END{

}